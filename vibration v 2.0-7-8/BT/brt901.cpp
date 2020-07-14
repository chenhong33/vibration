#include "brt901.h"
#include<QThread>
#include<QDataStream>
#include<QDateTime>
#include "ui_bt.h"
#include"bwtcommand.h"
#include<QMessageBox>
#include<QTimer>
#include <unistd.h>    //linux 下延时函数


const int ComPackLen = 11; //内容包长度
const int FrameLen = 33;  //数据帧长度=ComPackLen*个数
const int InternalDiv = 15;  //

BRT901::BRT901(QObject *parent) : QObject(parent)
{
    qDebug() << "BRT901()";
    readHeadFlag = false;
    saveHeadFlag = false;
}

BRT901::BRT901(QString address, QString name, QObject *parent): QObject(parent)
{
    this->BTaddress = address;
    this->moduleName = name;
    this->readHeadFlag = false;
    this->saveHeadFlag = false;
    this->displayFlag = false;
    this->socket = nullptr;
    internal = 0;
    AxTemp = 0;
    AyTemp = 0;
    AzTemp = 0;
}

BRT901::~BRT901()
{
    qDebug() << moduleName << "~BRT901()";
    f.close();
}

//发起连接
void BRT901:: slot_brtconnect()
{
    if (this->socket == nullptr) {
        qDebug() << moduleName << " slot_brtconnect ";
        QString serviceUuid("00001101-0000-1000-8000-00805F9B34FB");
        //实例化一个socket对象 用于管理通信连接 协议采用 RfcommProtocol
        this->socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol, this);
        //通过connectToService 发起连接  BTaddress为从设备的地址  serviceUuid为从设备的服务  该连接开启发送接收功能
        this->socket->connectToService(QBluetoothAddress(BTaddress), QBluetoothUuid(serviceUuid),
                                       QIODevice::ReadWrite);
        connect(socket, &QBluetoothSocket::readyRead, this, &BRT901::readBluetoothDataEvent);
        connect(socket, &QBluetoothSocket::connected, this, &BRT901::bluetoothConnectedEvent);
        connect(socket, &QBluetoothSocket::disconnected, this, &BRT901::bluetoothDisconnectedEvent);
    }
    qDebug() << " moduleName:" << moduleName << QThread::currentThreadId();
}
//数据存入文件前的处理
void BRT901::slot_saveDataPre(structFileName fileName)
{
    QString fileNameUrl;
    if (this->moduleName == "模块1")
        fileNameUrl = fileName.sensorOne;
    else if (this->moduleName == "模块2")
        fileNameUrl = fileName.sensorTwo;
    else if (this->moduleName == "模块3")
        fileNameUrl = fileName.sensorThree;
    else if (this->moduleName == "模块4")
        fileNameUrl = fileName.sensorFour;
    if (fileNameUrl != NULL) {
        //打开文件
        qDebug() << "------------slot_saveDataPre------------------";
        saveHeadFlag = false;
        fileNameUrl = fileName.path + fileNameUrl + ".csv";
        f.setFileName(fileNameUrl);
        f.open(QIODevice::ReadWrite | QIODevice::Truncate);
        disconnect(socket, &QBluetoothSocket::readyRead, this, &BRT901::readBluetoothDataEvent);
        connect(socket, &QBluetoothSocket::readyRead, this, &BRT901::saveBluetoothDataEvent);
    }
}





//数据存入文件完毕
void BRT901::slot_saveDataFinished()
{
    readHeadFlag = false;
    f.close();
    disconnect(socket, &QBluetoothSocket::readyRead, this, &BRT901::saveBluetoothDataEvent);
    connect(socket, &QBluetoothSocket::readyRead, this, &BRT901::readBluetoothDataEvent);
    qDebug() << "slot_saveDataFinished";
}

//数据存入文件
void BRT901::saveBluetoothDataEvent()
{
    if (!saveHeadFlag) {
        QTextStream out(&f);
        out << "Ax,Ay,Az,Wx,Wy,Wz,Roll,Pitch,Yaw" << "\r\n"; //表头
        saveHeadFlag = true;
    }
    //找到帧头
    int len = socket->bytesAvailable();
    int headIndex = 0;
    if (len >= FrameLen) {
        QByteArray head = socket->peek(33);
        for (int i = 0; i < FrameLen - 1; i++) {
            //'U'的ascii 为 0x55  'Q'的ascii 为 0x51
            if (head[i] == 'U' && head[i + 1] == 'Q') { // 找到帧头
                headIndex = i;
                break;
            }
        }
        if (headIndex > 0) {
            qDebug() << "---------------------------";
            socket->read(headIndex);
            this->internal++;
            if ((this->displayFlag) && (internal % InternalDiv == 0)) {
                emit sig_dataDisplay(AxTemp, AyTemp, AzTemp);
            }
        }
    }
    //读取数据
    len = socket->bytesAvailable();
    if (len >= FrameLen) {
        int frameNum = len / FrameLen;     //帧数
        QByteArray data = socket->read(frameNum * FrameLen);
        QTextStream out(&f);
        for (int i = 0; i < frameNum; i++) {
            //加速度
            float Ax = (((short)data[i * FrameLen + 3] << 8) | (uchar)data[i * FrameLen + 2]) / 32768.0 * 2;
            float Ay = (((short)data[i * FrameLen + 5] << 8) | (uchar)data[i * FrameLen + 4]) / 32768.0 * 2;
            float Az = (((short)data[i * FrameLen + 7] << 8) | (uchar)data[i * FrameLen + 6]) / 32768.0 * 2;

            unsigned short sum = 0;
            for(int j = 0; j < 10; j++)
                sum += (unsigned char)data[i * FrameLen + j];

            if((unsigned char)(sum & 0x00FF) != (unsigned char)data[10 + i * FrameLen])
                continue;

            //qDebug()<<Ax<<"    "<<Ay<<"    "<<Az<<"    "<<endl;
            //角速度
            float Wx = (((short)data[i * FrameLen + ComPackLen + 3] << 8) | (uchar)data[i * FrameLen +
                        ComPackLen + 2]) / 32768.0 * 2000;
            float Wy = (((short)data[i * FrameLen + ComPackLen + 5] << 8) | (uchar)data[i * FrameLen +
                        ComPackLen + 4]) / 32768.0 * 2000;
            float Wz = (((short)data[i * FrameLen + ComPackLen + 7] << 8) | (uchar)data[i * FrameLen +
                        ComPackLen + 6]) / 32768.0 * 2000;
            //qDebug()<<Wx<<"    "<<Wy<<"    "<<Wz<<"    "<<endl;
            //角度
            float Roll = (float)(((short)data[i * FrameLen + ComPackLen * 2 + 3] << 8) |
                                 (uchar)data[i * FrameLen + ComPackLen * 2 + 2]) / 32768.0 * 180;
            float Pitch = (float)(((short)data[i * FrameLen + ComPackLen * 2 + 5] << 8) |
                                  (uchar)data[i * FrameLen + ComPackLen * 2 + 4]) / 32768.0 * 180;
            float Yaw  = (float)(((short)data[i * FrameLen + ComPackLen * 2 + 7] << 8) |
                                 (uchar)data[i * FrameLen + ComPackLen * 2 + 6]) / 32768.0 * 180;
            //qDebug()<<Roll<<"    "<<Pitch<<"    "<<Yaw<<"    "<<endl;
            //写入文件
            AxTemp = Ax;
            AyTemp = Ay;
            AzTemp = Az;
            out << Ax << "," << Ay << "," << Az << "," << Wx << "," << Wy << "," << Wz << "," << Roll << "," <<
                Pitch << "," << Yaw << "\r\n";
            this->internal++;
            if ((this->displayFlag) && (internal % 20 == 0)) {
                emit sig_dataDisplay(Ax, Ay, Az);
            }
        }
    }
}



//数据显示/读走
void BRT901::readBluetoothDataEvent()
{
    //找到帧头
    int len = socket->bytesAvailable();
    int headIndex = 0;
    if (len >= FrameLen) {
        QByteArray head = socket->peek(33);
        for (int i = 0; i < FrameLen - 1; i++) {
            //'U'的ascii 为 0x55  'Q'的ascii 为 0x51
            if (head[i] == 'U' && head[i + 1] == 'Q') { // 找到帧头
                headIndex = i;
                break;
            }
        }
        if (headIndex > 0) {
            qDebug() << "---------------------------" << moduleName;
            socket->read(headIndex);
            this->internal++;
            if ((this->displayFlag) && (internal % InternalDiv == 0)) {
                emit sig_dataDisplay(AxTemp, AyTemp, AzTemp);
            }
        }
    }
    len = socket->bytesAvailable();
    if (len >= FrameLen) {
        int frameNum = len / FrameLen;     //帧数
        QByteArray data = socket->read(frameNum * FrameLen);
        for (int i = 0; i < frameNum; i++) {
            //加速度
            float Ax = (((short)data[i * FrameLen + 3] << 8) | (uchar)data[i * FrameLen + 2]) / 32768.0 * 2;
            float Ay = (((short)data[i * FrameLen + 5] << 8) | (uchar)data[i * FrameLen + 4]) / 32768.0 * 2;
            float Az = (((short)data[i * FrameLen + 7] << 8) | (uchar)data[i * FrameLen + 6]) / 32768.0 * 2;

            unsigned short sum = 0;
            for(int j = 0; j < 10; j++)
                sum += (unsigned char)data[i * FrameLen + j];

            if((unsigned char)(sum & 0x00FF) != (unsigned char)data[10 + i * FrameLen])
                continue;

            AxTemp = Ax;
            AyTemp = Ay;
            AzTemp = Az;
            this->internal++;
            if ((this->displayFlag) && (internal % 20 == 0)) {
                emit sig_dataDisplay(Ax, Ay, Az);
            }
        }
    }
}

//连接成功
void BRT901::bluetoothConnectedEvent()
{
    qDebug() << BTaddress << " has Connected " << "       localPort" << socket->localPort();
    if (this->socket->isOpen()) {
        emit sig_connected(BTaddress);
        qDebug() << BTaddress << "is Open-----------------------";
        this->socket->write(unlockedCmd);
    } else {
        this->socket->abort();
        qDebug() << BTaddress << "is aborted";
    }
}




//断开连接
void BRT901::bluetoothDisconnectedEvent()
{
    qDebug() << BTaddress << " has Disconnected !!!";
    emit sig_disconnected(BTaddress);
}





//自动校准
void BRT901::slot_accCalibration()
{
    accCalibrationCmd[3] = 0x01;
    this->socket->write(accCalibrationCmd);
}

//结束自动校准
void BRT901::slot_accCalibrationTimeout()
{
    accCalibrationCmd[3] = 0x00;
    this->socket->write(accCalibrationCmd);
    qDebug() << "结束自动校准";
}

//保存配置指令
void BRT901::slot_saveSetting()
{
    this->socket->write(saveCmd);
}

//解锁指令
void BRT901::slot_unlock()
{
    this->socket->write(unlockedCmd);
}

//默认配置 一次写入多条指令 采用定时器，避免多条指令一次发送
void BRT901::slot_defaultSetting()
{
    this->socket->write(unlockedCmd);
    QTimer::singleShot(100, this, SLOT(slot_rate()));
    QTimer::singleShot(200, this, SLOT(slot_autoCalibration()));
    QTimer::singleShot(300, this, SLOT(slot_directHorizon()));
    QTimer::singleShot(400, this, SLOT(slot_saveSetting()));
    QTimer::singleShot(500, this, SLOT(slot_defaultXAccZero()));
    QTimer::singleShot(600, this, SLOT(slot_defaultYAccZero()));
    QTimer::singleShot(700, this, SLOT(slot_defaultZAccZero()));
    qDebug() << "默认配置";
}

//设置零偏前准备
void BRT901::slot_preAccZero()
{
    XAccZero = 0;
    YAccZero = 0;
    ZAccZero = 0;
    frameSum = 0;
    readHeadFlag = false;
    qDebug() << "slot_preAccZero";
    disconnect(socket, &QBluetoothSocket::readyRead, this, &BRT901::saveBluetoothDataEvent);
    disconnect(socket, &QBluetoothSocket::readyRead, this, &BRT901::readBluetoothDataEvent);
    connect(socket, &QBluetoothSocket::readyRead, this, &BRT901::slot_AccZero);
}

//设置X轴零偏
void BRT901::slot_AccZero()
{
    int len = this->socket->bytesAvailable();
    int headIndex = 0;
    if (len >= FrameLen) {
        QByteArray head = this->socket->peek(33);
        for (int i = 0; i < FrameLen; i++) {
            //'U'的ascii 为 0x55  'Q'的ascii 为 0x51
            if (head[i] == 'U' && head[i + 1] == 'Q') { // 找到帧头
                headIndex = i;
                break;
            }
        }
        if (headIndex > 0) qDebug() << "---------------------------" << moduleName;
        socket->read(headIndex);
    }
    len = socket->bytesAvailable();
    if (len >= FrameLen) {
        int frameNum = len / FrameLen;     //帧数
        frameSum += frameNum;
        QByteArray data = socket->read(frameNum * FrameLen);
        for (int i = 0; i < frameNum; i++) {
            //加速度
            short Ax = (((short)data[i * FrameLen + 3] << 8) | (uchar)data[i * FrameLen + 2]);
            short Ay = (((short)data[i * FrameLen + 5] << 8) | (uchar)data[i * FrameLen + 4]);
            short Az = (((short)data[i * FrameLen + 7] << 8) | (uchar)data[i * FrameLen + 6]);
            XAccZero += Ax;
            YAccZero += Ay;
            ZAccZero += Az;
        }
        if (frameSum > 1000) {
            readHeadFlag = false;
            qDebug() << XAccZero << "  " << YAccZero << "  " << ZAccZero;
            XAccZero /= frameSum;
            YAccZero /= frameSum;
            ZAccZero /= frameSum;
            qDebug() << XAccZero << "  " << YAccZero << "  " << ZAccZero;
            short Ax = (short)XAccZero;
            short Ay = (short)YAccZero;
            short Az = (short)ZAccZero;
            qDebug() << Ax << "  " << Ay << "  " << Az;
            char AxL = (char)(Ax & 0xff);
            char AxH = (char)((Ax & 0xff00) >> 8);
            //设置X轴零偏
            XAccZeroCmd[3] = AxL;
            XAccZeroCmd[4] = AxH;
            this->socket->write(XAccZeroCmd);
            QTimer::singleShot(100, this, SLOT(slot_YAccZero()));
            QTimer::singleShot(200, this, SLOT(slot_ZAccZero()));
            disconnect(socket, &QBluetoothSocket::readyRead, this, &BRT901::slot_AccZero);
            connect(socket, &QBluetoothSocket::readyRead, this, &BRT901::readBluetoothDataEvent);
        }
    }
}

//设置Y轴零偏
void BRT901::slot_YAccZero()
{
    short Ay = (short)YAccZero;
    char AyL = (char)(Ay & 0xff);
    char AyH = (char)((Ay & 0xff00) >> 8);
    YAccZeroCmd[3] = AyL;
    YAccZeroCmd[4] = AyH;
    this->socket->write(YAccZeroCmd);
    qDebug() << "设置Y轴零偏";
}

//设置Z轴零偏
void BRT901::slot_ZAccZero()
{
    short Az = (short)ZAccZero;
    char AzL = (char)(Az & 0xff);
    char AzH = (char)((Az & 0xff00) >> 8);
    ZAccZeroCmd[3] = AzL;
    ZAccZeroCmd[4] = AzH;
    this->socket->write(ZAccZeroCmd);
    qDebug() << "设置Z轴零偏";
}


//默认配置 默认选择 自动校准 水平安装方向 回传速率200Hz
void BRT901::slot_autoCalibration()
{
    autoCalibrationCmd[3] = 0x00;
    this->socket->write(autoCalibrationCmd);
}

void BRT901::slot_directHorizon()
{
    setDirectionCmd[3] = 0x00;
    this->socket->write(setDirectionCmd);
}

void BRT901::slot_rate()
{
    rateCmd[3] = 0x0b;
    this->socket->write(rateCmd);
}

void BRT901::slot_defaultXAccZero()
{
    XAccZeroCmd[3] = 0x00;
    XAccZeroCmd[4] = 0x00;
    this->socket->write(XAccZeroCmd);
}

void BRT901::slot_defaultYAccZero()
{
    YAccZeroCmd[3] = 0x00;
    YAccZeroCmd[4] = 0x00;
    this->socket->write(YAccZeroCmd);
}

void BRT901::slot_defaultZAccZero()
{
    ZAccZeroCmd[3] = 0x00;
    ZAccZeroCmd[4] = 0x00;
    this->socket->write(ZAccZeroCmd);
}










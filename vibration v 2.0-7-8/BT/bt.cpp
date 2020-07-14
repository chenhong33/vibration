#include "bt.h"
#include "ui_bt.h"
//#include"bwtcommand.h"
#include<QTimer>

#include<QFileDialog>

#include <QCloseEvent>
#include <QTime>

#include "fileconfigwindow.h"
#include"ui_fileconfigwindow.h"

#include <unistd.h>    //linux 下延时函数

#include <QPen>
#include "../vibration.h"

BT::BT(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BT)
{
    ui->setupUi(this);
    m_connFlag = {false, false, false, false, false, false};
    QDesktopWidget *desktop = QApplication::desktop(); // =qApp->desktop();也可以
    move((desktop->width() - this->width()) / 2, (desktop->height() - this->height()) / 2);
    fileConf = NULL;
    //获取配置文件的信息

    QString profileName = QCoreApplication::applicationDirPath()+"/profile.txt";
    qDebug()<<"profileName"<<profileName;
    QFile file(profileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug()<<"Can't open the file!"<<endl;
        }
    QTextStream in(&file);
    if(!in.atEnd()){
        modulesAddress.module_1_name = in.readLine();
        modulesAddress.module_2_name = in.readLine();
        modulesAddress.module_3_name = in.readLine();
        modulesAddress.module_4_name = in.readLine();
    }



    m_x = 2.6;
    //设置控件不使能时 字体颜色
    QCheckBox *checkBox = new QCheckBox;
    QPalette palette = checkBox->palette();
    palette.setColor(QPalette::Disabled, QPalette::WindowText, Qt::lightGray);
    ui->module1State->setPalette(palette);
    ui->module2State->setPalette(palette);
    ui->module3State->setPalette(palette);
    ui->module4State->setPalette(palette);
    ui->module5State->setPalette(palette);
    ui->module6State->setPalette(palette);
    ui->module1State->setVisible(false);
    ui->module2State->setVisible(false);
    ui->module3State->setVisible(false);
    ui->module4State->setVisible(false);
    ui->module5State->setVisible(false);
    ui->module6State->setVisible(false);
    /*****************曲线显示设置******************/
    mychart = new QChart();
    //X轴加速度曲线
    mx_series = new QSplineSeries(this);
//    mx_series=new QLineSeries(this);
    QPen xgreen(Qt::red);
    xgreen.setWidth(1);
    mx_series->setPen(xgreen);           //设置曲线样式
    mx_series->setName("X");             //设置从曲线名称
    mx_series->setUseOpenGL(true);
    //Y轴加速度曲线
    my_series = new QSplineSeries(this);
//    my_series=new QLineSeries(this);
    QPen ygreen(Qt::green);
    ygreen.setWidth(1);
    my_series->setPen(ygreen);
    my_series->setName("Y");
    my_series->setUseOpenGL(true);
    //Z轴加速度曲线
    mz_series = new QSplineSeries(this);
//    mz_series=new QLineSeries(this);
    QPen zgreen(Qt::blue);
    zgreen.setWidth(1);
    mz_series->setPen(zgreen);
    mz_series->setName("Z");
    mz_series->setUseOpenGL(true);
    //画笔绑定曲线
    mychart->addSeries(mx_series);
    mychart->addSeries(my_series);
    mychart->addSeries(mz_series);
    //设置X坐标轴
    m_axisX = new QValueAxis;
    m_axisX->setRange(0, 3);      //范围
    m_axisX->setTickCount(6);     //主要刻度
    m_axisX->setTitleText("time/(s)");//标题
    //设置y坐标轴
    m_axisY = new QValueAxis;
    m_axisY->setRange(-2, 2);
    m_axisY->setTickCount(5);                    //轴上有多少个标记数目
    m_axisY->setTitleText("Acceleration/(g)");
    //画笔添加坐标轴
    mychart->addAxis(m_axisX, Qt::AlignBottom);  //将坐标轴加到chart上，居下
    mychart->addAxis(m_axisY, Qt::AlignLeft);    //居左
    //曲线关联坐标轴
    mx_series->attachAxis(m_axisX);
    mx_series->attachAxis(m_axisY);
    my_series->attachAxis(m_axisX);
    my_series->attachAxis(m_axisY);
    mz_series->attachAxis(m_axisX);
    mz_series->attachAxis(m_axisY);
    //
    mychart->legend()->setVisible(true);                    //设置图例可见
    mychart->legend()->setLayoutDirection(Qt::LeftToRight);
    mychart->legend()->setAlignment(Qt::AlignBottom);
    mychart->setTitle(tr("加速度曲线图"));                    //设置图表标题
    //画布设置
    ui->dataView->setChart(mychart);                        //画布绑定画笔
    ui->dataView->setRenderHint(QPainter::Antialiasing);    //设置抗锯齿
    ui->dataView->setContentsMargins(0, 0, 0, 0);
    ui->dataView->show();
    //定义一个扫描实例
    discoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);
    connect(discoveryAgent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)), this,
            SLOT(discoverBlueTooth(QBluetoothDeviceInfo)));
    connect(discoveryAgent, SIGNAL(finished()), this, SLOT(discoveryFinished()));
    //开始扫描
    discoveryAgent->start();
    //提示  无法自定义大小
    msg = new QMessageBox(this);
    msg->setWindowTitle("提示");
    msg->setText("传感器自动连接中...\n请不要进行其它操作等待连接完成");
    msg->setIcon(QMessageBox::Warning);
    msg->setStandardButtons(0);
    //msg->setWindowModality(Qt::ApplicationModal);  //设置模态
    //msg->setModal(true);
    msg->show();
    int x = msg->x() + msg->width() / 2 - this->width() / 2;
    int y = msg->y() + msg->height() / 2 - this->height() / 2;
    this->move(x, y);
    //qDebug() << "main thread:" << QThread::currentThreadId();
}

BT::~BT()
{
    delete mx_series;
    delete my_series;
    delete mz_series;
    delete m_axisX;
    delete m_axisY;
    delete ui;
    QList<QThread *>::iterator i;
    for (i = qThreadList.begin(); i != qThreadList.end(); i++) {
        (*i)->quit();
        (*i)->wait();
    }
    qDebug() << "~BT()";
}


void BT::closeEvent(QCloseEvent *event)
{

    endDataDisplay();
    hide();
    event->ignore();
}


void BT::endDataDisplay()
{
     QList<BRT901 *>::iterator i;
    for (i = BRTList.begin(); i != BRTList.end(); i++)
        (*i)->displayFlag = false;
}
void BT::startDataDisplay()
{

    QString name = ui->moduleComboBox->currentText();
    QList<BRT901 *>::iterator i;
    for (i = BRTList.begin(); i != BRTList.end(); i++) {
        (*i)->displayFlag = false;
        if ((*i)->moduleName == name) {
            qDebug() << (*i)->BTaddress;
            (*i)->displayFlag = true;
        }
    }




}

















void BT::conn_mianThread_to_subThread(const QObject *receiver)
{
    connect(this, SIGNAL(sig_brtconnect()), receiver, SLOT(slot_brtconnect()), Qt::QueuedConnection);
    //指令发送
    connect(this, SIGNAL(sig_saveDataFinished()), receiver, SLOT(slot_saveDataFinished()),
            Qt::QueuedConnection);
    connect(this, SIGNAL(sig_accCalibration()), receiver, SLOT(slot_accCalibration()),
            Qt::QueuedConnection);
    connect(this, SIGNAL(sig_accCalibrationTimeout()), receiver, SLOT(slot_accCalibrationTimeout()),
            Qt::QueuedConnection);
    connect(this, SIGNAL(sig_saveSetting()), receiver, SLOT(slot_saveSetting()), Qt::QueuedConnection);
    connect(this, SIGNAL(sig_unlock()), receiver, SLOT(slot_unlock()), Qt::QueuedConnection);
    connect(this, SIGNAL(sig_defaultSetting()), receiver, SLOT(slot_defaultSetting()),
            Qt::QueuedConnection);
    connect(this, SIGNAL(sig_AccZero()), receiver, SLOT(slot_preAccZero()), Qt::QueuedConnection);
    connect(this, SIGNAL(sig_saveDataPre(structFileName)), receiver,
            SLOT(slot_saveDataPre(structFileName)), Qt::DirectConnection);
}

void BT::conn_subThread_to_mianThread(const QObject *sender)
{
    //连接状态显示
    connect(sender, SIGNAL(sig_connected(QString)), this, SLOT(slot_connected(QString)),
            Qt::QueuedConnection);
    connect(sender, SIGNAL(sig_disconnected(QString)), this, SLOT(slot_disconnected(QString)),
            Qt::QueuedConnection);
    //数据显示
    connect(sender, SIGNAL(sig_dataDisplay(float, float, float)), this, SLOT(slot_dataDisplay(float,
            float, float)), Qt::QueuedConnection);
}

//每扫描到一个设备 discoveryAgent 会发出 deviceDiscovered信号  有储存上次扫描的结果
void BT::discoverBlueTooth(QBluetoothDeviceInfo info)
{
    QString macAddress = info.address().toString();
    QString label = QString("%1 %2").arg(macAddress).arg(info.name());
    qDebug() << label;
}
//扫描完成
void BT::discoveryFinished()
{
    //判断有多少个传感器 创建多少个实例
    //获得所有扫描到的蓝牙模块
    QList<QBluetoothDeviceInfo> devicelist = discoveryAgent->discoveredDevices();
    QList<QBluetoothDeviceInfo> ::iterator i;
    for (i = devicelist.begin(); i != devicelist.end(); i++) {
        QString address = i->address().toString();
        qDebug() << address << "  " << i->rssi();
        if (address == modulesAddress.module_1_name) {   //模块1
            //判断蓝牙模块模块的信号强度
            if (abs(i->rssi()) > 0) {
                ui->connComboBox->addItem("模块1");
                BRTList << new BRT901(address, "模块1");
                qThreadList << new QThread();
            }
        } else if (address == modulesAddress.module_2_name) { //模块2
            if (abs(i->rssi()) > 0) {
                ui->connComboBox->addItem("模块2");
                qDebug() << i->rssi();
                BRTList << new BRT901(address, "模块2"); //不能有 parent=this
                //QObject::moveToThread: Cannot move objects with a parent
                qThreadList << new QThread();
            }
        } else if (address == modulesAddress.module_3_name) { //模块3
            if (abs(i->rssi()) > 0) {
                ui->connComboBox->addItem("模块3");
                qDebug() << i->rssi();
                BRTList << new BRT901(address, "模块3");
                qThreadList << new QThread();
            }
        } else if (address == modulesAddress.module_4_name) { //模块4
            if (abs(i->rssi()) > 0) {
                ui->connComboBox->addItem("模块4");
                qDebug() << i->rssi();
                BRTList << new BRT901(address, "模块4");
                qThreadList << new QThread();
            }
        }
    }
    //分配线程，开启线程
    if (!BRTList.isEmpty()) {
        QList<BRT901 *>::iterator i;
        int qThreadListIndex = 0;
        for (i = BRTList.begin(); i != BRTList.end(); i++) {
            (*i)->moveToThread(qThreadList[qThreadListIndex]);
            connect(qThreadList[qThreadListIndex], &QThread::finished, (*i), &QObject::deleteLater);
            conn_mianThread_to_subThread(*i);
            conn_subThread_to_mianThread(*i);
            qThreadListIndex++;
        }
        //开启线程
        QList<QThread *>::iterator j;
        for (j = qThreadList.begin(); j != qThreadList.end(); j++) {
            (*j)->start();
            emit sig_brtconnect();
        }
    }
    delete msg;
}

//动态显示
void BT::slot_dataDisplay(float x, float y, float z)
{
    qreal crolltemp = mychart->plotArea().width() / m_axisX->tickCount() / 5 * 0.75;
    qreal xInterval = (m_axisX->max() - m_axisX->min()) / m_axisX->tickCount() / 5 * 0.75;
    m_x += xInterval;
    mx_series->append(m_x, x);
    my_series->append(m_x, y);
    mz_series->append(m_x, z);
    mychart->scroll(crolltemp, 0);
    if (mx_series->count() > 500)
        mx_series->remove(0);
    if (my_series->count() > 500)
        my_series->remove(0);
    if (mz_series->count() > 500)
        mz_series->remove(0);
}




//连接状态显示（连接）
void BT::slot_connected(QString macAddr)
{
    if (macAddr == modulesAddress.module_1_name) {   //模块1
        ui->module1State->setChecked(true);
        ui->moduleComboBox->addItem("模块1");
        ui->connComboBox->removeItem(ui->connComboBox->findText("模块1"));
        m_connFlag.sensorOne = true;
    } else if (macAddr == modulesAddress.module_2_name) { //模块2
        ui->module2State->setChecked(true);
        ui->moduleComboBox->addItem("模块2");
        ui->connComboBox->removeItem(ui->connComboBox->findText("模块2"));
        m_connFlag.sensorTwo = true;
    } else if (macAddr == modulesAddress.module_3_name) { //模块3
        ui->module3State->setChecked(true);
        ui->moduleComboBox->addItem("模块3");
        ui->connComboBox->removeItem(ui->connComboBox->findText("模块3"));
        m_connFlag.sensorThree = true;
    } else if (macAddr == modulesAddress.module_4_name) { //模块4
        ui->module4State->setChecked(true);
        ui->moduleComboBox->addItem("模块4");
        ui->connComboBox->removeItem(ui->connComboBox->findText("模块4"));
        m_connFlag.sensorFour = true;
    }
}
//连接状态显示（断开连接）
void BT::slot_disconnected(QString macAddr)
{
    if (macAddr == modulesAddress.module_1_name) {   //模块1
        ui->module1State->setChecked(false);
        ui->moduleComboBox->removeItem(ui->moduleComboBox->findText("模块1"));
        if (ui->connComboBox->findText("模块1") == -1) //判断是否已经存在
            ui->connComboBox->addItem("模块1");
        m_connFlag.sensorOne = false;
        QMessageBox::warning(NULL, tr("警告"), tr("模块1断开连接"));
    } else if (macAddr == modulesAddress.module_2_name) { //模块2
        ui->module2State->setChecked(false);
        ui->moduleComboBox->removeItem(ui->moduleComboBox->findText("模块2"));
        if (ui->connComboBox->findText("模块2") == -1) //判断是否已经存在
            ui->connComboBox->addItem("模块2");
        m_connFlag.sensorTwo = false;
        QMessageBox::warning(NULL, tr("警告"), tr("模块2断开连接"));
    } else if (macAddr == modulesAddress.module_3_name) { //模块3
        ui->module3State->setChecked(false);
        ui->moduleComboBox->removeItem(ui->moduleComboBox->findText("模块3"));
        if (ui->connComboBox->findText("模块3") == -1) //判断是否已经存在
            ui->connComboBox->addItem("模块3");
        m_connFlag.sensorThree = false;
        QMessageBox::warning(NULL, tr("警告"), tr("模块3断开连接"));
    } else if (macAddr == modulesAddress.module_4_name) { //模块4
        ui->module4State->setChecked(false);
        ui->moduleComboBox->removeItem(ui->moduleComboBox->findText("模块4"));
        if (ui->connComboBox->findText("模块4") == -1) //判断是否已经存在
            ui->connComboBox->addItem("模块4");
        m_connFlag.sensorFour = false;
        QMessageBox::warning(NULL, tr("警告"), tr("模块4断开连接"));
    }
    QList<BRT901 *>::iterator i;
    int Index = 0;
    for (i = BRTList.begin(); i != BRTList.end(); i++) {
        qDebug() << (*i)->BTaddress;
        if ((*i)->BTaddress == macAddr)
            break;
        Index++;
    }
    //删除未连接成功的实例
    if (Index < BRTList.size()) {
        qThreadList[Index]->quit();
        qThreadList[Index]->wait();
        BRTList.removeAt(Index);
        qThreadList.removeAt(Index);
    }
}



//手动连接
void BT::on_manualConnBtn_clicked()
{
    QString name = ui->connComboBox->currentText();
    QString addr;
    if (name == "模块1")  addr = modulesAddress.module_1_name;
    else if (name == "模块2")  addr = modulesAddress.module_2_name;
    else if (name == "模块3")  addr = modulesAddress.module_3_name;
    else if (name == "模块4")  addr = modulesAddress.module_4_name;
    QList<BRT901 *>::iterator i;
    int Index = 0;
    for (i = BRTList.begin(); i != BRTList.end(); i++) {
        qDebug() << (*i)->moduleName;
        if ((*i)->moduleName == name) {
            addr = (*i)->BTaddress;
            break;
        }
        Index++;
    }
    //删除未连接成功的实例
    if (Index < BRTList.size()) {
        qThreadList[Index]->quit();
        qThreadList[Index]->wait();
        BRTList.removeAt(Index);
        qThreadList.removeAt(Index);
    }
    //新建实例与线程
    BRT901 *BRTtemp = new BRT901(addr, name);
    QThread *qThread = new QThread();
    //加入列表便于管理
    BRTList.append(BRTtemp);
    qThreadList.append(qThread);
    //分配线程
    BRTtemp->moveToThread(qThread);
    //信号与槽的绑定
    connect(qThread, &QThread::finished, BRTtemp, &QObject::deleteLater);
    conn_mianThread_to_subThread(BRTtemp);
    conn_subThread_to_mianThread(BRTtemp);
    //开启线程
    qThread->start();
    emit sig_brtconnect();
}


//选泽哪个模块数据显示
void BT::on_moduleComboBox_currentTextChanged(const QString &arg1)
{
    QString name = arg1;
    QList<BRT901 *>::iterator i;
    for (i = BRTList.begin(); i != BRTList.end(); i++) {
        (*i)->displayFlag = false;
        if ((*i)->moduleName == name) {
            qDebug() << (*i)->BTaddress;
            (*i)->displayFlag = true;
        }
    }
}

void BT::on_moduleComboBox_activated(const QString &arg1)
{
    QString name = arg1;
    QList<BRT901 *>::iterator i;
    for (i = BRTList.begin(); i != BRTList.end(); i++) {
        (*i)->displayFlag = false;
        if ((*i)->moduleName == name) {
            qDebug() << (*i)->BTaddress;
            (*i)->displayFlag = true;
        }
    }
}



//数据记录
void BT::on_saveDataBtn_clicked()
{
    if (fileConf == NULL)
        fileConf = new FileConfigWindow();
    fileConf->model = false ;
    //fileConf->setWindowModality(Qt::WindowModal);
    //fileConf->setModal(true);
    fileConf->sensorFlagChages(&m_connFlag);
    fileConf->LineSetEnabled();
    //fileConf->show();
    fileConf->exec();
//    while (!fileConf->model) {
//    }
    qDebug() << fileConf->recordflag;
    if (fileConf->recordflag) {
        qDebug() << "------------recordflag==1------------------";
        fileConf->recordflag = false;
        ui->saveDataBtn->setEnabled(false);
        ui->defaultBtn->setEnabled(false);
        ui->saveBtn->setEnabled(false);
        ui->AccZero->setEnabled(false);
        ui->accCalibrationBtn->setEnabled(false);
        emit sig_saveDataPre(fileConf->fileNameQstirng);
        int recordTime;
        int index = ui->recordTimeCBox->currentIndex();
        switch (index) {
        case 0:
            recordTime = 60 * 1000;
            break;
        case 1:
            recordTime = 90 * 1000;
            break;
        case 2:
            recordTime = 120 * 1000;
            break;
        default:
            recordTime = 60 * 1000;
            break;
        }
        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(saveDataTimeout()));
        timer->start(recordTime);
        timer->setSingleShot(true);

    }
}

void BT::saveDataTimeout()
{
    emit sig_saveDataFinished();
    QMessageBox::information(NULL, tr("提示"), tr("操作已完成"));
    ui->saveDataBtn->setEnabled(true);
    ui->defaultBtn->setEnabled(true);
    ui->saveBtn->setEnabled(true);
    ui->AccZero->setEnabled(true);
    ui->accCalibrationBtn->setEnabled(true);
}

void BT::on_selfCheck_clicked()
{
    ui->selfCheck->setEnabled(false);
    ui->saveDataBtn->setEnabled(false);
    ui->defaultBtn->setEnabled(false);
    ui->saveBtn->setEnabled(false);
    ui->AccZero->setEnabled(false);
    ui->accCalibrationBtn->setEnabled(false);
    structFileName fileName;

    fileName.path = QProcessEnvironment::systemEnvironment().value("HOME")+ "/";
    if(m_connFlag.sensorOne)
        fileName.sensorOne =  "1fdsafdsa";

    if(m_connFlag.sensorTwo)
        fileName.sensorTwo =   "21fdsafdsa";

    if(m_connFlag.sensorThree)
        fileName.sensorThree =  "31fdsafdsa";

    if(m_connFlag.sensorFour)
        fileName.sensorFour =  "41fdsafdsa";

    if(m_connFlag.sensorFive)
        fileName.sensorFive =  "51fdsafdsa";

    if(m_connFlag.sensorSix)
        fileName.sensorSix =   "61fdsafdsa";

    emit sig_saveDataPre(fileName);
    int recordTime;
    recordTime = 3 * 1000;
    QTimer::singleShot(recordTime, this, SLOT(saveDataTimeout()));

    QTime dieTime = QTime::currentTime().addMSecs(3*1000+200);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

    if(m_connFlag.sensorOne){
        if(!(dataTest(fileName.path +fileName.sensorOne + ".csv",620,0) &&
            dataTest(fileName.path +fileName.sensorOne + ".csv",620,1) &&
            dataTest(fileName.path +fileName.sensorOne + ".csv",620,2)))
            QMessageBox::warning(NULL, QStringLiteral("警告"),
                                QStringLiteral("传感器1自校错误!"),
                                QMessageBox::Yes );
    }

    if(m_connFlag.sensorTwo){
        if(!(dataTest(fileName.path +fileName.sensorTwo + ".csv",620,0) &&
            dataTest(fileName.path +fileName.sensorTwo + ".csv",620,1) &&
            dataTest(fileName.path +fileName.sensorTwo + ".csv",620,2)))
            QMessageBox::warning(NULL, QStringLiteral("警告"),
                                QStringLiteral("传感器2自校错误!"),
                                QMessageBox::Yes );
    }

    if(m_connFlag.sensorThree){
        if(!(dataTest(fileName.path +fileName.sensorThree + ".csv",620,0) &&
            dataTest(fileName.path +fileName.sensorThree + ".csv",620,1) &&
            dataTest(fileName.path +fileName.sensorThree + ".csv",620,2)))
            QMessageBox::warning(NULL, QStringLiteral("警告"),
                                QStringLiteral("传感器3自校错误!"),
                                QMessageBox::Yes );
    }

    if(m_connFlag.sensorFour){
        if(!(dataTest(fileName.path +fileName.sensorFour + ".csv",620,0) &&
            dataTest(fileName.path +fileName.sensorFour + ".csv",620,1) &&
            dataTest(fileName.path +fileName.sensorFour + ".csv",620,2)))
            QMessageBox::warning(NULL, QStringLiteral("警告"),
                                QStringLiteral("传感器4自校错误!"),
                                QMessageBox::Yes );
    }

    if(m_connFlag.sensorFive){
        if(!(dataTest(fileName.path +fileName.sensorFive + ".csv",620,0) &&
            dataTest(fileName.path +fileName.sensorFive + ".csv",620,1) &&
            dataTest(fileName.path +fileName.sensorFive + ".csv",620,2)))
            QMessageBox::warning(NULL, QStringLiteral("警告"),
                                QStringLiteral("传感器5自校错误!"),
                                QMessageBox::Yes );
    }

    if(m_connFlag.sensorSix){
        if(!(dataTest(fileName.path +fileName.sensorSix + ".csv",620,0) &&
            dataTest(fileName.path +fileName.sensorSix + ".csv",620,1) &&
            dataTest(fileName.path +fileName.sensorSix + ".csv",620,2)))
            QMessageBox::warning(NULL, QStringLiteral("警告"),
                                QStringLiteral("传感器6自校错误!"),
                                QMessageBox::Yes );
    }

    ui->selfCheck->setEnabled(true);
    ui->saveDataBtn->setEnabled(true);
    ui->defaultBtn->setEnabled(true);
    ui->saveBtn->setEnabled(true);
    ui->AccZero->setEnabled(true);
    ui->accCalibrationBtn->setEnabled(true);

}


bool BT::dataTest(QString filename,int data_size,int indx)
{
    double *selfCheckData = new double[data_size];
    for(int i = 0; i < data_size; i++)
        selfCheckData[i] = 0;
    FileToData(filename,indx,selfCheckData,data_size);
    float min = 999999;
    float max = -999999;
    int lose = 0;


    for(int i = 0; i < data_size; i++){
        if(selfCheckData[i] == 0){
            continue;
        }
        lose++;
        min = min < selfCheckData[i] ? min : selfCheckData[i];
        max = max > selfCheckData[i] ? max : selfCheckData[i];

    }

    delete[] selfCheckData;

    if(max - min > 0.2 || lose < 580)
        return false;
    else
        return true;

}





























/*******************响应用户按键***********************/

//保存配置
void BT::on_saveBtn_clicked()
{
    emit sig_saveSetting();
}

//恢复默认配置
void BT::on_defaultBtn_clicked()
{
    emit sig_defaultSetting();
}

//加计较准
void BT::on_accCalibrationBtn_clicked()
{
    emit sig_accCalibration();
    QTimer::singleShot(3500, this, SLOT(accCalibrationTimeout()));
    ui->saveBtn->setEnabled(false);
    ui->accCalibrationBtn->setEnabled(false);
    ui->defaultBtn->setEnabled(false);
    ui->saveDataBtn->setEnabled(false);
    ui->AccZero->setEnabled(false);
}

//结束加计较准
void BT::accCalibrationTimeout()
{
    emit sig_accCalibrationTimeout();
    ui->saveBtn->setEnabled(true);
    ui->accCalibrationBtn->setEnabled(true);
    ui->defaultBtn->setEnabled(true);
    ui->saveDataBtn->setEnabled(true);
    ui->AccZero->setEnabled(true);
    qDebug() << "accCalibrationTimeout";
}


//手动扫描
void BT::on_scanBtn_clicked()
{
    disconnect(discoveryAgent, SIGNAL(finished()), this, SLOT(discoveryFinished()));
    connect(discoveryAgent, SIGNAL(finished()), this, SLOT(manualScanFinished()));
    discoveryAgent->start();
    ui->scanBtn->setEnabled(false);
    ui->connComboBox->clear();
}

void BT::manualScanFinished()
{
    QList<QBluetoothDeviceInfo> devicelist = discoveryAgent->discoveredDevices();
    QList<QBluetoothDeviceInfo> ::iterator i;
    for (i = devicelist.begin(); i != devicelist.end(); i++) {
        QString address = i->address().toString();
        if (address == modulesAddress.module_1_name) {   //模块1
            //判断蓝牙模块模块的信号强度
            if (abs(i->rssi()) > 0) {
                if (ui->connComboBox->findText("模块1") == -1
                        && !ui->module1State->isChecked()) //判断是否已经存在
                    ui->connComboBox->addItem("模块1");
            }
        } else if (address == modulesAddress.module_2_name) { //模块2
            if (abs(i->rssi()) > 0) {
                if (ui->connComboBox->findText("模块2") == -1
                        && !ui->module2State->isChecked()) //判断是否已经存在
                    ui->connComboBox->addItem("模块2");
            }
        } else if (address == modulesAddress.module_3_name) { //模块3
            if (abs(i->rssi()) > 0) {
                if (ui->connComboBox->findText("模块3") == -1
                        && !ui->module3State->isChecked()) //判断是否已经存在
                    ui->connComboBox->addItem("模块3");
            }
        } else if (address == modulesAddress.module_4_name) { //模块4
            if (abs(i->rssi()) > 0) {
                if (ui->connComboBox->findText("模块4") && !ui->module4State->isChecked())
                    ui->connComboBox->addItem("模块4");
            }
        }
    }
    ui->scanBtn->setEnabled(true);
}




//设置零偏
void BT::on_AccZero_clicked()
{
    emit sig_AccZero();
    qDebug() << "on_AccZero_clicked";
}

//解锁
//void BT::on_unlockBtn_clicked()
//{moduleComboBox
//    emit sig_unlock();
//}

void BT::on_suspendRecord_clicked(){
    if(!ui->saveDataBtn->isEnabled()){
        timer->stop();
        delete timer;
        saveDataTimeout();
    }
}



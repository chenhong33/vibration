#ifndef BRT901_H
#define BRT901_H

#include <QObject>
#include "fileconfigwindow.h"
/***************************蓝牙相关*****************************/
#include <QtBluetooth/QBluetoothDeviceInfo>  //存储关于蓝牙设备的信息
#include <QtBluetooth/QBluetoothDeviceDiscoveryAgent>  //发现附近的蓝牙设备
#include <qbluetoothglobal.h>
#include <qbluetoothlocaldevice.h>
#include <QBluetoothSocket>  //允许连接到运行蓝牙服务器的蓝牙设备
#include <QBluetoothUuid>
#include <QBluetoothAddress>
/**************************************************************/

//读写文件相关
#include <QIODevice>
#include<QFile>
#include<QList>


class BRT901 : public QObject
{
    Q_OBJECT
public:
    explicit BRT901(QObject *parent = nullptr);
    BRT901(QString address, QString name, QObject *parent = nullptr);
    ~BRT901();

private:
    int internal;                  //用于动态显示曲线的分频
    QFile f;                       //写入的文件
    QBluetoothSocket *socket;      //管理通信连接
    QList<QString> fileNameList;
    bool readHeadFlag;             //找到帧头标志（保存文件）
    bool saveHeadFlag;             //找到帧头标志（动态显示）
    float XAccZero;                //用于X轴加速度零偏
    float YAccZero;                //用于X轴加速度零偏
    float ZAccZero;                //用于X轴加速度零偏
    int frameSum;                  //数据帧数


    float AxTemp;
    float AyTemp;
    float AzTemp;

public:
    QString moduleName;            //模块名
    QString BTaddress;             //外围设备的mac地址
    bool displayFlag;              //是否以曲线显示标志

signals:
    void sig_connected(QString macAddr);
    void sig_disconnected(QString macAddr);
    void sig_connectedAgain();
    void sig_dataDisplay(float x, float y, float z);


public slots:
    void bluetoothConnectedEvent();     //连接成功
    void bluetoothDisconnectedEvent();  //断开连接
    void slot_brtconnect();             //发起连接


    //void slot_filenNameSetting(struct fileName);             //文件命名




    void readBluetoothDataEvent();      //显示数据
    void saveBluetoothDataEvent();      //记录数据
    void slot_saveDataPre(structFileName fileName);
    void slot_saveDataFinished();
    //发送指令给模块

    void slot_accCalibration();         //自动校准
    void slot_accCalibrationTimeout();  //结束校准
    void slot_saveSetting();            //保存配置
    void slot_unlock();                 //解锁
    void slot_defaultSetting();         //默认配置
    void slot_preAccZero();             //零偏预处理
    void slot_AccZero();                //设置零偏（X轴）
    void slot_YAccZero();               //设置Y轴零偏
    void slot_ZAccZero();               //设置Z轴零偏

//默认配置
    void slot_autoCalibration();
    void slot_directHorizon();
    void slot_rate();
    void slot_defaultXAccZero();
    void slot_defaultYAccZero();
    void slot_defaultZAccZero();




    //void brtSlotOffset(float x,float y,float z);






};

#endif // BRT901_H

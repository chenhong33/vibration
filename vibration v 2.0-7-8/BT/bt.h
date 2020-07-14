#ifndef BT_H
#define BT_H

#include <QMainWindow>
#include <QThread>
#include <QList>
#include "brt901.h"
#include<QMessageBox>

//数据动态显示
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QPointF>
#include <QtCharts/QSplineSeries> //曲线
#include <QtCharts/QValueAxis>    //坐标轴

#include <QtCharts/QLineSeries>
#include "fileconfigwindow.h"

//typedef struct allModulesConnFlag{
//    bool sensorOne;
//    bool sensorTwo;
//    bool sensorThree;
//    bool sensorFour;
//    bool sensorFive;
//    bool sensorSix;
//}connFlag;

typedef struct ModulesAddress{
    QString module_1_name;
    QString module_2_name;
    QString module_3_name;
    QString module_4_name;

}MAddr;


namespace Ui {
class BT;
}

QT_CHARTS_USE_NAMESPACE



class BT : public QMainWindow
{
    Q_OBJECT

public:
    explicit BT(QWidget *parent = 0);
    ~BT();
    QString name;     //储存路径 供外部访问
    FileConfigWindow *fileConf;
    connFlag m_connFlag;
    MAddr modulesAddress;


    void endDataDisplay();
    void startDataDisplay();


private:
    Ui::BT *ui;
    QBluetoothDeviceDiscoveryAgent *discoveryAgent;   //扫描代理
    QList<BRT901 *>  BRTList;                         //管理模块
    QList<QThread *> qThreadList;                     //管理模块对应的线程
    QTimer *timer;




    QMessageBox *msg;

private:
    QChart *mychart;                                 //相当于”画笔“
    QSplineSeries *mx_series;                        //x轴加速度曲线
    QSplineSeries *my_series;                        //y轴加速度曲线
    QSplineSeries *mz_series;                        //z轴加速度曲线

//    QLineSeries *mx_series;                        //x轴加速度曲线
//    QLineSeries *my_series;                        //y轴加速度曲线
//    QLineSeries *mz_series;                        //z轴加速度曲线


    QValueAxis    *m_axisX;                          //图表的x轴
    QValueAxis    *m_axisY;                          //图表的y轴
    qreal m_x;                                       //图表的x轴坐标
    bool dataTest(QString ,int ,int );


private slots:
    void discoverBlueTooth(QBluetoothDeviceInfo info);
    void discoveryFinished();
    void manualScanFinished();

    void slot_connected(QString macAddr);
    void slot_disconnected(QString macAddr);

    void slot_dataDisplay(float x, float y, float z);


//响应按键的槽
    void on_saveBtn_clicked();
    void on_defaultBtn_clicked();
    void on_accCalibrationBtn_clicked();
    void on_saveDataBtn_clicked();
    void saveDataTimeout();
    void accCalibrationTimeout();
    void on_moduleComboBox_currentTextChanged(const QString &arg1);
    void on_scanBtn_clicked();
    void on_AccZero_clicked();
    //void on_unlockBtn_clicked();
    void on_manualConnBtn_clicked();
    void on_moduleComboBox_activated(const QString &arg1);
    void on_selfCheck_clicked();
    void on_suspendRecord_clicked();


//在主线程只发出信号 指令的发送在各个子线程处理
//信号在对应槽内发出
signals:
    void sig_brtconnect();
    void sig_saveData(QString url);
    void sig_saveDataFinished();
    void sig_accCalibration();
    void sig_accCalibrationTimeout();
    void sig_saveSetting();
    void sig_unlock();
    void sig_defaultSetting();
    void sig_AccZero();
    void sig_saveDataPre(structFileName fileName);


protected :
    void closeEvent(QCloseEvent *event);    //重写关闭事件
    void conn_mianThread_to_subThread(const QObject *receiver);
    void conn_subThread_to_mianThread(const QObject *sender);







};

#endif // BT_H

#ifndef BWTCOMMAND_H
#define BWTCOMMAND_H


#include<QByteArray>

//解锁指令
unsigned char c_unlockedCmd[] = {0xFF, 0xAA, 0x69, 0x88, 0xB5};
QByteArray unlockedCmd((char *)&c_unlockedCmd, 5);

//设置回传速率
//  0x01|0x02|0x03|0x04|0x05|0x06|0x07|0x08| 0x09 | 0x0a | 0x0b | 0x0c |
//  0.1   0.5  1    2     5   10   20   50    100    无     200   单次输出
unsigned char c_rateCmd[] = {0xFF, 0xAA, 0x03, 0x0b, 0x00};
QByteArray rateCmd((char *)&c_rateCmd, 5);

//保持配置
unsigned char c_saveCmd[] = {0xFF, 0xAA, 0x00, 0x00, 0x00};
QByteArray saveCmd((char *)&c_saveCmd, 5);

//陀螺仪自动校准
// 0x00  选择陀螺仪自动校准    default
// 0x01  去掉陀螺仪自动校准
unsigned char c_autoCalibrationCmd[] = {0xFF, 0xAA, 0x63, 0x00, 0x00};
QByteArray autoCalibrationCmd((char *)&c_autoCalibrationCmd, 5);

// 设置校准
// 0x00  退出校准模式
// 0x01  进入加速度计校准模式   default
// 0x02  进入磁场校准模式
// 0x03  高度置 0
unsigned char c_accCalibrationCmd[] = {0xFF, 0xAA, 0x01, 0x01, 0x00};
QByteArray accCalibrationCmd((char *)&c_accCalibrationCmd, 5);

//设置安装方向
// 0x00  设置为水平安装    default
// 0x01  设置为垂直安装
unsigned char c_setDirectionCmd[] = {0xFF, 0xAA, 0x23, 0x00, 0x00};
QByteArray setDirectionCmd((char *)&c_setDirectionCmd, 5);

//休眠与解休眠
unsigned char c_sleepOrAwakeCmd[] = {0xFF, 0xAA, 0x22, 0x01, 0x00};
QByteArray sleepOrAwakeCmd((char *)&c_sleepOrAwakeCmd, 5);

//设置 X 轴加速度零偏
unsigned char c_XAccZeroCmd[] = {0xFF, 0xAA, 0x05, 0x00, 0x00};
QByteArray XAccZeroCmd((char *)&c_XAccZeroCmd, 5);

//设置 Y 轴加速度零偏
unsigned char c_YAccZeroCmd[] = {0xFF, 0xAA, 0x06, 0x00, 0x00};
QByteArray YAccZeroCmd((char *)&c_YAccZeroCmd, 5);

//设置 Z 轴加速度零偏
unsigned char c_ZAccZeroCmd[] = {0xFF, 0xAA, 0x07, 0x00, 0x00};
QByteArray ZAccZeroCmd((char *)&c_ZAccZeroCmd, 5);


//设置回传内容
//0x07  名称 0x57包 | 0x56包 | 0x55包 | 0x54包 | 0x53包 | 0x52包 | 0x51包 | 0x50包
//           0         0        0        0        1       1        1        0
//0x00
unsigned char c_contentCmd[] = {0xFF, 0xAA, 0x02, 0x0E, 0x00};
QByteArray contentCmd((char *)&c_contentCmd, 5);








#endif // BWTCOMMAND_H

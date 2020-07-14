/********************************************************************************
** Form generated from reading UI file 'bt.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BT_H
#define UI_BT_H

#include <QtCharts>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BT
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *connectState;
    QCheckBox *module1State;
    QCheckBox *module2State;
    QCheckBox *module3State;
    QCheckBox *module4State;
    QCheckBox *module5State;
    QCheckBox *module6State;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_2;
    QChartView *dataView;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label_2;
    QComboBox *connComboBox;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label;
    QComboBox *moduleComboBox;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_3;
    QComboBox *recordTimeCBox;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QPushButton *scanBtn;
    QSpacerItem *verticalSpacer_11;
    QPushButton *manualConnBtn;
    QSpacerItem *verticalSpacer_10;
    QPushButton *selfCheck;
    QSpacerItem *verticalSpacer_9;
    QPushButton *defaultBtn;
    QSpacerItem *verticalSpacer_8;
    QPushButton *saveBtn;
    QSpacerItem *verticalSpacer_4;
    QPushButton *AccZero;
    QSpacerItem *verticalSpacer_7;
    QPushButton *accCalibrationBtn;
    QSpacerItem *verticalSpacer_13;
    QPushButton *saveDataBtn;
    QSpacerItem *verticalSpacer_3;
    QPushButton *suspendRecord;
    QStatusBar *statusBar;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *BT)
    {
        if (BT->objectName().isEmpty())
            BT->setObjectName(QStringLiteral("BT"));
        BT->resize(654, 579);
        BT->setMinimumSize(QSize(500, 500));
        centralWidget = new QWidget(BT);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        connectState = new QHBoxLayout();
        connectState->setSpacing(6);
        connectState->setObjectName(QStringLiteral("connectState"));
        module1State = new QCheckBox(centralWidget);
        module1State->setObjectName(QStringLiteral("module1State"));
        module1State->setEnabled(false);

        connectState->addWidget(module1State);

        module2State = new QCheckBox(centralWidget);
        module2State->setObjectName(QStringLiteral("module2State"));
        module2State->setEnabled(false);

        connectState->addWidget(module2State);

        module3State = new QCheckBox(centralWidget);
        module3State->setObjectName(QStringLiteral("module3State"));
        module3State->setEnabled(false);

        connectState->addWidget(module3State);

        module4State = new QCheckBox(centralWidget);
        module4State->setObjectName(QStringLiteral("module4State"));
        module4State->setEnabled(false);

        connectState->addWidget(module4State);

        module5State = new QCheckBox(centralWidget);
        module5State->setObjectName(QStringLiteral("module5State"));
        module5State->setEnabled(false);
        module5State->setContextMenuPolicy(Qt::DefaultContextMenu);

        connectState->addWidget(module5State);

        module6State = new QCheckBox(centralWidget);
        module6State->setObjectName(QStringLiteral("module6State"));
        module6State->setEnabled(false);

        connectState->addWidget(module6State);


        gridLayout->addLayout(connectState, 2, 0, 1, 1);

        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        gridLayout_2 = new QGridLayout(groupBox_3);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        dataView = new QChartView(groupBox_3);
        dataView->setObjectName(QStringLiteral("dataView"));

        gridLayout_2->addWidget(dataView, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox_3, 1, 0, 1, 1);

        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setLayoutDirection(Qt::LeftToRight);
        horizontalLayout = new QHBoxLayout(groupBox_2);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(45, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        connComboBox = new QComboBox(groupBox_2);
        connComboBox->setObjectName(QStringLiteral("connComboBox"));

        horizontalLayout->addWidget(connComboBox);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        label = new QLabel(groupBox_2);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        moduleComboBox = new QComboBox(groupBox_2);
        moduleComboBox->setObjectName(QStringLiteral("moduleComboBox"));

        horizontalLayout->addWidget(moduleComboBox);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout->addWidget(label_3);

        recordTimeCBox = new QComboBox(groupBox_2);
        recordTimeCBox->setObjectName(QStringLiteral("recordTimeCBox"));

        horizontalLayout->addWidget(recordTimeCBox);


        gridLayout->addWidget(groupBox_2, 0, 0, 1, 1);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setLayoutDirection(Qt::LeftToRight);
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer_2 = new QSpacerItem(20, 16, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        scanBtn = new QPushButton(groupBox);
        scanBtn->setObjectName(QStringLiteral("scanBtn"));

        verticalLayout->addWidget(scanBtn);

        verticalSpacer_11 = new QSpacerItem(20, 16, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_11);

        manualConnBtn = new QPushButton(groupBox);
        manualConnBtn->setObjectName(QStringLiteral("manualConnBtn"));

        verticalLayout->addWidget(manualConnBtn);

        verticalSpacer_10 = new QSpacerItem(20, 16, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_10);

        selfCheck = new QPushButton(groupBox);
        selfCheck->setObjectName(QStringLiteral("selfCheck"));

        verticalLayout->addWidget(selfCheck);

        verticalSpacer_9 = new QSpacerItem(20, 16, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_9);

        defaultBtn = new QPushButton(groupBox);
        defaultBtn->setObjectName(QStringLiteral("defaultBtn"));

        verticalLayout->addWidget(defaultBtn);

        verticalSpacer_8 = new QSpacerItem(20, 16, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_8);

        saveBtn = new QPushButton(groupBox);
        saveBtn->setObjectName(QStringLiteral("saveBtn"));

        verticalLayout->addWidget(saveBtn);

        verticalSpacer_4 = new QSpacerItem(20, 16, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);

        AccZero = new QPushButton(groupBox);
        AccZero->setObjectName(QStringLiteral("AccZero"));

        verticalLayout->addWidget(AccZero);

        verticalSpacer_7 = new QSpacerItem(20, 16, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_7);

        accCalibrationBtn = new QPushButton(groupBox);
        accCalibrationBtn->setObjectName(QStringLiteral("accCalibrationBtn"));

        verticalLayout->addWidget(accCalibrationBtn);

        verticalSpacer_13 = new QSpacerItem(20, 12, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_13);

        saveDataBtn = new QPushButton(groupBox);
        saveDataBtn->setObjectName(QStringLiteral("saveDataBtn"));

        verticalLayout->addWidget(saveDataBtn);

        verticalSpacer_3 = new QSpacerItem(20, 12, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        suspendRecord = new QPushButton(groupBox);
        suspendRecord->setObjectName(QStringLiteral("suspendRecord"));

        verticalLayout->addWidget(suspendRecord);


        gridLayout->addWidget(groupBox, 0, 1, 3, 1);

        BT->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(BT);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        BT->setStatusBar(statusBar);
        mainToolBar = new QToolBar(BT);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        BT->addToolBar(Qt::TopToolBarArea, mainToolBar);

        retranslateUi(BT);

        QMetaObject::connectSlotsByName(BT);
    } // setupUi

    void retranslateUi(QMainWindow *BT)
    {
        BT->setWindowTitle(QApplication::translate("BT", "BT", Q_NULLPTR));
        module1State->setText(QApplication::translate("BT", "\346\250\241\345\235\2271", Q_NULLPTR));
        module2State->setText(QApplication::translate("BT", "\346\250\241\345\235\2272", Q_NULLPTR));
        module3State->setText(QApplication::translate("BT", "\346\250\241\345\235\2273", Q_NULLPTR));
        module4State->setText(QApplication::translate("BT", "\346\250\241\345\235\2274", Q_NULLPTR));
        module5State->setText(QApplication::translate("BT", "\346\250\241\345\235\2275", Q_NULLPTR));
        module6State->setText(QApplication::translate("BT", "\346\250\241\345\235\2276", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("BT", "\345\256\236\346\227\266\346\230\276\347\244\272", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("BT", "\344\274\240\346\204\237\345\231\250", Q_NULLPTR));
        label_2->setText(QApplication::translate("BT", "\346\234\252\350\277\236\346\216\245", Q_NULLPTR));
        label->setText(QApplication::translate("BT", "\345\267\262\350\277\236\346\216\245", Q_NULLPTR));
        label_3->setText(QApplication::translate("BT", "\350\256\260\345\275\225\346\227\266\351\227\264", Q_NULLPTR));
        recordTimeCBox->clear();
        recordTimeCBox->insertItems(0, QStringList()
         << QApplication::translate("BT", "   1\357\274\23200", Q_NULLPTR)
         << QApplication::translate("BT", "   1\357\274\23230", Q_NULLPTR)
         << QApplication::translate("BT", "   2\357\274\23200", Q_NULLPTR)
        );
        groupBox->setTitle(QApplication::translate("BT", "\345\212\237\350\203\275", Q_NULLPTR));
        scanBtn->setText(QApplication::translate("BT", "\346\211\253\346\217\217", Q_NULLPTR));
        manualConnBtn->setText(QApplication::translate("BT", "\346\211\213\345\212\250\350\277\236\346\216\245", Q_NULLPTR));
        selfCheck->setText(QApplication::translate("BT", "\350\256\276\345\244\207\350\207\252\346\243\200", Q_NULLPTR));
        defaultBtn->setText(QApplication::translate("BT", "\351\273\230\350\256\244\351\205\215\347\275\256", Q_NULLPTR));
        saveBtn->setText(QApplication::translate("BT", "\344\277\235\345\255\230\351\205\215\347\275\256", Q_NULLPTR));
        AccZero->setText(QApplication::translate("BT", "\350\256\276\347\275\256\351\233\266\345\201\217", Q_NULLPTR));
        accCalibrationBtn->setText(QApplication::translate("BT", "\345\212\240\350\256\241\346\240\241\345\207\206", Q_NULLPTR));
        saveDataBtn->setText(QApplication::translate("BT", "\350\256\260\345\275\225\346\225\260\346\215\256", Q_NULLPTR));
        suspendRecord->setText(QApplication::translate("BT", "\345\201\234\346\255\242\350\256\260\345\275\225", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class BT: public Ui_BT {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BT_H

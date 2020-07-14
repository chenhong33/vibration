/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "QtCharts/QChartView"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QTabWidget *tabWidget;
    QWidget *MainTab;
    QGridLayout *gridLayout_8;
    QGridLayout *gridLayout_7;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout;
    QComboBox *comboBox_2;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButton_2;
    QSpacerItem *verticalSpacer_5;
    QPushButton *pushButton_3;
    QSpacerItem *verticalSpacer_6;
    QPushButton *pushButton;
    QSpacerItem *verticalSpacer_7;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *verticalSpacer_4;
    QVBoxLayout *verticalLayout_6;
    QtCharts::QChartView *chartsView;
    QtCharts::QChartView *chartsView_2;
    QHBoxLayout *horizontalLayout_14;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_40;
    QLabel *label_41;
    QLabel *label_42;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_7;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEditAccS;
    QLabel *label;
    QLineEdit *lineEditAccX;
    QLabel *label_2;
    QLineEdit *lineEditAccY;
    QLabel *label_3;
    QLineEdit *lineEditAccZ;
    QLabel *label_25;
    QHBoxLayout *horizontalLayout_6;
    QLineEdit *lineEditStdS;
    QLabel *label_22;
    QLineEdit *lineEditStdX;
    QLabel *label_23;
    QLineEdit *lineEditStdY;
    QLabel *label_24;
    QLineEdit *lineEditStdZ;
    QHBoxLayout *horizontalLayout_8;
    QHBoxLayout *horizontalLayout_9;
    QLineEdit *lineEditPeaS;
    QLabel *label_26;
    QLineEdit *lineEditPeaX;
    QLabel *label_27;
    QLineEdit *lineEditPeaY;
    QLabel *label_28;
    QLineEdit *lineEditPeaZ;
    QLabel *label_29;
    QHBoxLayout *horizontalLayout_10;
    QLineEdit *lineEditRmsS;
    QLabel *label_30;
    QLineEdit *lineEditRmsX;
    QLabel *label_31;
    QLineEdit *lineEditRmsY;
    QLabel *label_32;
    QLineEdit *lineEditRmsZ;
    QHBoxLayout *horizontalLayout_11;
    QHBoxLayout *horizontalLayout_12;
    QLineEdit *lineEditMarS;
    QLabel *label_33;
    QLineEdit *lineEditMarX;
    QLabel *label_34;
    QLineEdit *lineEditMarY;
    QLabel *label_35;
    QLineEdit *lineEditMarZ;
    QLabel *label_36;
    QHBoxLayout *horizontalLayout_13;
    QLineEdit *lineEditPulS;
    QLabel *label_37;
    QLineEdit *lineEditPulX;
    QLabel *label_38;
    QLineEdit *lineEditPulY;
    QLabel *label_39;
    QLineEdit *lineEditPulZ;
    QWidget *tab;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout_15;
    QComboBox *comboBox_3;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_2;
    QtCharts::QChartView *chartsView_4;
    QtCharts::QChartView *chartsView_5;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_43;
    QLineEdit *lineEdit_All;
    QLabel *label_4;
    QLineEdit *lineEdit_X;
    QLabel *label_5;
    QLineEdit *lineEdit_Y;
    QLabel *label_6;
    QLineEdit *lineEdit_Z;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_46;
    QLineEdit *lineEdit_DAll;
    QLabel *label_47;
    QLineEdit *lineEdit_Dx;
    QLabel *label_48;
    QLineEdit *lineEdit_Dy;
    QLabel *label_49;
    QLineEdit *lineEdit_Dz;
    QVBoxLayout *verticalLayout_9;
    QWidget *tab_2;
    QGridLayout *gridLayout_4;
    QVBoxLayout *verticalLayout_3;
    QtCharts::QChartView *chartsView_7;
    QtCharts::QChartView *chartsView_8;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1264, 794);
        QIcon icon;
        QString iconThemeName = QStringLiteral("vibration");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon = QIcon::fromTheme(iconThemeName);
        } else {
            icon.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        MainWindow->setWindowIcon(icon);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setFocusPolicy(Qt::ClickFocus);
        MainTab = new QWidget();
        MainTab->setObjectName(QStringLiteral("MainTab"));
        gridLayout_8 = new QGridLayout(MainTab);
        gridLayout_8->setSpacing(6);
        gridLayout_8->setContentsMargins(11, 11, 11, 11);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        gridLayout_7 = new QGridLayout();
        gridLayout_7->setSpacing(6);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        comboBox_2 = new QComboBox(MainTab);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));

        verticalLayout->addWidget(comboBox_2);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        pushButton_2 = new QPushButton(MainTab);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        verticalLayout->addWidget(pushButton_2);

        verticalSpacer_5 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_5);

        pushButton_3 = new QPushButton(MainTab);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        verticalLayout->addWidget(pushButton_3);

        verticalSpacer_6 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_6);

        pushButton = new QPushButton(MainTab);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout->addWidget(pushButton);

        verticalSpacer_7 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_7);

        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        verticalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        verticalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);


        horizontalLayout_4->addLayout(verticalLayout);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        chartsView = new QtCharts::QChartView(MainTab);
        chartsView->setObjectName(QStringLiteral("chartsView"));

        verticalLayout_6->addWidget(chartsView);

        chartsView_2 = new QtCharts::QChartView(MainTab);
        chartsView_2->setObjectName(QStringLiteral("chartsView_2"));

        verticalLayout_6->addWidget(chartsView_2);


        horizontalLayout_4->addLayout(verticalLayout_6);


        gridLayout_7->addLayout(horizontalLayout_4, 0, 0, 1, 1);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        label_40 = new QLabel(MainTab);
        label_40->setObjectName(QStringLiteral("label_40"));

        verticalLayout_5->addWidget(label_40);

        label_41 = new QLabel(MainTab);
        label_41->setObjectName(QStringLiteral("label_41"));

        verticalLayout_5->addWidget(label_41);

        label_42 = new QLabel(MainTab);
        label_42->setObjectName(QStringLiteral("label_42"));

        verticalLayout_5->addWidget(label_42);


        horizontalLayout_14->addLayout(verticalLayout_5);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        lineEditAccS = new QLineEdit(MainTab);
        lineEditAccS->setObjectName(QStringLiteral("lineEditAccS"));
        lineEditAccS->setReadOnly(true);

        horizontalLayout->addWidget(lineEditAccS);

        label = new QLabel(MainTab);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        lineEditAccX = new QLineEdit(MainTab);
        lineEditAccX->setObjectName(QStringLiteral("lineEditAccX"));
        lineEditAccX->setReadOnly(true);

        horizontalLayout->addWidget(lineEditAccX);

        label_2 = new QLabel(MainTab);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        lineEditAccY = new QLineEdit(MainTab);
        lineEditAccY->setObjectName(QStringLiteral("lineEditAccY"));
        lineEditAccY->setReadOnly(true);

        horizontalLayout->addWidget(lineEditAccY);

        label_3 = new QLabel(MainTab);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout->addWidget(label_3);

        lineEditAccZ = new QLineEdit(MainTab);
        lineEditAccZ->setObjectName(QStringLiteral("lineEditAccZ"));
        lineEditAccZ->setReadOnly(true);

        horizontalLayout->addWidget(lineEditAccZ);


        horizontalLayout_7->addLayout(horizontalLayout);

        label_25 = new QLabel(MainTab);
        label_25->setObjectName(QStringLiteral("label_25"));

        horizontalLayout_7->addWidget(label_25);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        lineEditStdS = new QLineEdit(MainTab);
        lineEditStdS->setObjectName(QStringLiteral("lineEditStdS"));
        lineEditStdS->setReadOnly(true);

        horizontalLayout_6->addWidget(lineEditStdS);

        label_22 = new QLabel(MainTab);
        label_22->setObjectName(QStringLiteral("label_22"));

        horizontalLayout_6->addWidget(label_22);

        lineEditStdX = new QLineEdit(MainTab);
        lineEditStdX->setObjectName(QStringLiteral("lineEditStdX"));
        lineEditStdX->setReadOnly(true);

        horizontalLayout_6->addWidget(lineEditStdX);

        label_23 = new QLabel(MainTab);
        label_23->setObjectName(QStringLiteral("label_23"));

        horizontalLayout_6->addWidget(label_23);

        lineEditStdY = new QLineEdit(MainTab);
        lineEditStdY->setObjectName(QStringLiteral("lineEditStdY"));
        lineEditStdY->setReadOnly(true);

        horizontalLayout_6->addWidget(lineEditStdY);

        label_24 = new QLabel(MainTab);
        label_24->setObjectName(QStringLiteral("label_24"));

        horizontalLayout_6->addWidget(label_24);

        lineEditStdZ = new QLineEdit(MainTab);
        lineEditStdZ->setObjectName(QStringLiteral("lineEditStdZ"));
        lineEditStdZ->setReadOnly(true);

        horizontalLayout_6->addWidget(lineEditStdZ);


        horizontalLayout_7->addLayout(horizontalLayout_6);


        gridLayout->addLayout(horizontalLayout_7, 0, 0, 1, 1);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        lineEditPeaS = new QLineEdit(MainTab);
        lineEditPeaS->setObjectName(QStringLiteral("lineEditPeaS"));
        lineEditPeaS->setReadOnly(true);

        horizontalLayout_9->addWidget(lineEditPeaS);

        label_26 = new QLabel(MainTab);
        label_26->setObjectName(QStringLiteral("label_26"));

        horizontalLayout_9->addWidget(label_26);

        lineEditPeaX = new QLineEdit(MainTab);
        lineEditPeaX->setObjectName(QStringLiteral("lineEditPeaX"));
        lineEditPeaX->setReadOnly(true);

        horizontalLayout_9->addWidget(lineEditPeaX);

        label_27 = new QLabel(MainTab);
        label_27->setObjectName(QStringLiteral("label_27"));

        horizontalLayout_9->addWidget(label_27);

        lineEditPeaY = new QLineEdit(MainTab);
        lineEditPeaY->setObjectName(QStringLiteral("lineEditPeaY"));
        lineEditPeaY->setReadOnly(true);

        horizontalLayout_9->addWidget(lineEditPeaY);

        label_28 = new QLabel(MainTab);
        label_28->setObjectName(QStringLiteral("label_28"));

        horizontalLayout_9->addWidget(label_28);

        lineEditPeaZ = new QLineEdit(MainTab);
        lineEditPeaZ->setObjectName(QStringLiteral("lineEditPeaZ"));
        lineEditPeaZ->setReadOnly(true);

        horizontalLayout_9->addWidget(lineEditPeaZ);


        horizontalLayout_8->addLayout(horizontalLayout_9);

        label_29 = new QLabel(MainTab);
        label_29->setObjectName(QStringLiteral("label_29"));

        horizontalLayout_8->addWidget(label_29);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        lineEditRmsS = new QLineEdit(MainTab);
        lineEditRmsS->setObjectName(QStringLiteral("lineEditRmsS"));
        lineEditRmsS->setReadOnly(true);

        horizontalLayout_10->addWidget(lineEditRmsS);

        label_30 = new QLabel(MainTab);
        label_30->setObjectName(QStringLiteral("label_30"));

        horizontalLayout_10->addWidget(label_30);

        lineEditRmsX = new QLineEdit(MainTab);
        lineEditRmsX->setObjectName(QStringLiteral("lineEditRmsX"));
        lineEditRmsX->setReadOnly(true);

        horizontalLayout_10->addWidget(lineEditRmsX);

        label_31 = new QLabel(MainTab);
        label_31->setObjectName(QStringLiteral("label_31"));

        horizontalLayout_10->addWidget(label_31);

        lineEditRmsY = new QLineEdit(MainTab);
        lineEditRmsY->setObjectName(QStringLiteral("lineEditRmsY"));
        lineEditRmsY->setReadOnly(true);

        horizontalLayout_10->addWidget(lineEditRmsY);

        label_32 = new QLabel(MainTab);
        label_32->setObjectName(QStringLiteral("label_32"));

        horizontalLayout_10->addWidget(label_32);

        lineEditRmsZ = new QLineEdit(MainTab);
        lineEditRmsZ->setObjectName(QStringLiteral("lineEditRmsZ"));
        lineEditRmsZ->setReadOnly(true);

        horizontalLayout_10->addWidget(lineEditRmsZ);


        horizontalLayout_8->addLayout(horizontalLayout_10);


        gridLayout->addLayout(horizontalLayout_8, 1, 0, 1, 1);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        lineEditMarS = new QLineEdit(MainTab);
        lineEditMarS->setObjectName(QStringLiteral("lineEditMarS"));
        lineEditMarS->setReadOnly(true);

        horizontalLayout_12->addWidget(lineEditMarS);

        label_33 = new QLabel(MainTab);
        label_33->setObjectName(QStringLiteral("label_33"));

        horizontalLayout_12->addWidget(label_33);

        lineEditMarX = new QLineEdit(MainTab);
        lineEditMarX->setObjectName(QStringLiteral("lineEditMarX"));
        lineEditMarX->setReadOnly(true);

        horizontalLayout_12->addWidget(lineEditMarX);

        label_34 = new QLabel(MainTab);
        label_34->setObjectName(QStringLiteral("label_34"));

        horizontalLayout_12->addWidget(label_34);

        lineEditMarY = new QLineEdit(MainTab);
        lineEditMarY->setObjectName(QStringLiteral("lineEditMarY"));
        lineEditMarY->setReadOnly(true);

        horizontalLayout_12->addWidget(lineEditMarY);

        label_35 = new QLabel(MainTab);
        label_35->setObjectName(QStringLiteral("label_35"));

        horizontalLayout_12->addWidget(label_35);

        lineEditMarZ = new QLineEdit(MainTab);
        lineEditMarZ->setObjectName(QStringLiteral("lineEditMarZ"));
        lineEditMarZ->setReadOnly(true);

        horizontalLayout_12->addWidget(lineEditMarZ);


        horizontalLayout_11->addLayout(horizontalLayout_12);

        label_36 = new QLabel(MainTab);
        label_36->setObjectName(QStringLiteral("label_36"));

        horizontalLayout_11->addWidget(label_36);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        lineEditPulS = new QLineEdit(MainTab);
        lineEditPulS->setObjectName(QStringLiteral("lineEditPulS"));
        lineEditPulS->setReadOnly(true);

        horizontalLayout_13->addWidget(lineEditPulS);

        label_37 = new QLabel(MainTab);
        label_37->setObjectName(QStringLiteral("label_37"));

        horizontalLayout_13->addWidget(label_37);

        lineEditPulX = new QLineEdit(MainTab);
        lineEditPulX->setObjectName(QStringLiteral("lineEditPulX"));
        lineEditPulX->setReadOnly(true);

        horizontalLayout_13->addWidget(lineEditPulX);

        label_38 = new QLabel(MainTab);
        label_38->setObjectName(QStringLiteral("label_38"));

        horizontalLayout_13->addWidget(label_38);

        lineEditPulY = new QLineEdit(MainTab);
        lineEditPulY->setObjectName(QStringLiteral("lineEditPulY"));
        lineEditPulY->setReadOnly(true);

        horizontalLayout_13->addWidget(lineEditPulY);

        label_39 = new QLabel(MainTab);
        label_39->setObjectName(QStringLiteral("label_39"));

        horizontalLayout_13->addWidget(label_39);

        lineEditPulZ = new QLineEdit(MainTab);
        lineEditPulZ->setObjectName(QStringLiteral("lineEditPulZ"));
        lineEditPulZ->setReadOnly(true);

        horizontalLayout_13->addWidget(lineEditPulZ);


        horizontalLayout_11->addLayout(horizontalLayout_13);


        gridLayout->addLayout(horizontalLayout_11, 2, 0, 1, 1);


        horizontalLayout_14->addLayout(gridLayout);


        gridLayout_7->addLayout(horizontalLayout_14, 1, 0, 1, 1);


        gridLayout_8->addLayout(gridLayout_7, 0, 0, 1, 1);

        tabWidget->addTab(MainTab, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        gridLayout_3 = new QGridLayout(tab);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        comboBox_3 = new QComboBox(tab);
        comboBox_3->setObjectName(QStringLiteral("comboBox_3"));

        horizontalLayout_15->addWidget(comboBox_3);

        horizontalSpacer = new QSpacerItem(1058, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer);


        gridLayout_3->addLayout(horizontalLayout_15, 0, 0, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        chartsView_4 = new QtCharts::QChartView(tab);
        chartsView_4->setObjectName(QStringLiteral("chartsView_4"));

        verticalLayout_2->addWidget(chartsView_4);

        chartsView_5 = new QtCharts::QChartView(tab);
        chartsView_5->setObjectName(QStringLiteral("chartsView_5"));

        verticalLayout_2->addWidget(chartsView_5);


        gridLayout_3->addLayout(verticalLayout_2, 1, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_43 = new QLabel(tab);
        label_43->setObjectName(QStringLiteral("label_43"));

        horizontalLayout_2->addWidget(label_43);

        lineEdit_All = new QLineEdit(tab);
        lineEdit_All->setObjectName(QStringLiteral("lineEdit_All"));
        lineEdit_All->setReadOnly(true);

        horizontalLayout_2->addWidget(lineEdit_All);

        label_4 = new QLabel(tab);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_2->addWidget(label_4);

        lineEdit_X = new QLineEdit(tab);
        lineEdit_X->setObjectName(QStringLiteral("lineEdit_X"));
        lineEdit_X->setReadOnly(true);

        horizontalLayout_2->addWidget(lineEdit_X);

        label_5 = new QLabel(tab);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_2->addWidget(label_5);

        lineEdit_Y = new QLineEdit(tab);
        lineEdit_Y->setObjectName(QStringLiteral("lineEdit_Y"));
        lineEdit_Y->setReadOnly(true);

        horizontalLayout_2->addWidget(lineEdit_Y);

        label_6 = new QLabel(tab);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_2->addWidget(label_6);

        lineEdit_Z = new QLineEdit(tab);
        lineEdit_Z->setObjectName(QStringLiteral("lineEdit_Z"));
        lineEdit_Z->setReadOnly(true);

        horizontalLayout_2->addWidget(lineEdit_Z);

        horizontalSpacer_2 = new QSpacerItem(80, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        label_46 = new QLabel(tab);
        label_46->setObjectName(QStringLiteral("label_46"));

        horizontalLayout_2->addWidget(label_46);

        lineEdit_DAll = new QLineEdit(tab);
        lineEdit_DAll->setObjectName(QStringLiteral("lineEdit_DAll"));
        lineEdit_DAll->setReadOnly(true);

        horizontalLayout_2->addWidget(lineEdit_DAll);

        label_47 = new QLabel(tab);
        label_47->setObjectName(QStringLiteral("label_47"));

        horizontalLayout_2->addWidget(label_47);

        lineEdit_Dx = new QLineEdit(tab);
        lineEdit_Dx->setObjectName(QStringLiteral("lineEdit_Dx"));
        lineEdit_Dx->setReadOnly(true);

        horizontalLayout_2->addWidget(lineEdit_Dx);

        label_48 = new QLabel(tab);
        label_48->setObjectName(QStringLiteral("label_48"));

        horizontalLayout_2->addWidget(label_48);

        lineEdit_Dy = new QLineEdit(tab);
        lineEdit_Dy->setObjectName(QStringLiteral("lineEdit_Dy"));
        lineEdit_Dy->setReadOnly(true);

        horizontalLayout_2->addWidget(lineEdit_Dy);

        label_49 = new QLabel(tab);
        label_49->setObjectName(QStringLiteral("label_49"));

        horizontalLayout_2->addWidget(label_49);

        lineEdit_Dz = new QLineEdit(tab);
        lineEdit_Dz->setObjectName(QStringLiteral("lineEdit_Dz"));
        lineEdit_Dz->setReadOnly(true);

        horizontalLayout_2->addWidget(lineEdit_Dz);


        gridLayout_3->addLayout(horizontalLayout_2, 2, 0, 1, 1);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));

        gridLayout_3->addLayout(verticalLayout_9, 3, 0, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        gridLayout_4 = new QGridLayout(tab_2);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        chartsView_7 = new QtCharts::QChartView(tab_2);
        chartsView_7->setObjectName(QStringLiteral("chartsView_7"));

        verticalLayout_3->addWidget(chartsView_7);

        chartsView_8 = new QtCharts::QChartView(tab_2);
        chartsView_8->setObjectName(QStringLiteral("chartsView_8"));

        verticalLayout_3->addWidget(chartsView_8);


        gridLayout_4->addLayout(verticalLayout_3, 0, 0, 1, 1);

        tabWidget->addTab(tab_2, QString());

        gridLayout_2->addWidget(tabWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\346\214\257\345\212\250\345\210\206\346\236\220", Q_NULLPTR));
        comboBox_2->clear();
        comboBox_2->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "\344\274\240\346\204\237\345\231\2501", Q_NULLPTR)
         << QApplication::translate("MainWindow", "\344\274\240\346\204\237\345\231\2502", Q_NULLPTR)
         << QApplication::translate("MainWindow", "\344\274\240\346\204\237\345\231\2503", Q_NULLPTR)
         << QApplication::translate("MainWindow", "\344\274\240\346\204\237\345\231\2504", Q_NULLPTR)
         << QApplication::translate("MainWindow", "\344\274\240\346\204\237\345\231\2505", Q_NULLPTR)
         << QApplication::translate("MainWindow", "\344\274\240\346\204\237\345\231\2506", Q_NULLPTR)
        );
        pushButton_2->setText(QApplication::translate("MainWindow", "\344\274\240\346\204\237\345\231\250\350\277\236\346\216\245", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("MainWindow", "\351\200\211\346\213\251\346\226\207\344\273\266", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "\345\274\200\345\247\213\350\256\241\347\256\227", Q_NULLPTR));
        label_40->setText(QApplication::translate("MainWindow", "\345\212\240\351\200\237\345\272\246\345\271\263\345\235\207\345\200\274", Q_NULLPTR));
        label_41->setText(QApplication::translate("MainWindow", "\345\263\260-\345\263\260\345\200\274", Q_NULLPTR));
        label_42->setText(QApplication::translate("MainWindow", "\350\243\225\345\272\246\345\233\240\345\255\220", Q_NULLPTR));
        lineEditAccS->setText(QString());
        label->setText(QApplication::translate("MainWindow", "x:", Q_NULLPTR));
        lineEditAccX->setText(QString());
        label_2->setText(QApplication::translate("MainWindow", "y:", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "z\357\274\232", Q_NULLPTR));
        label_25->setText(QApplication::translate("MainWindow", "\346\240\207\345\207\206\345\267\256\357\274\232", Q_NULLPTR));
        lineEditStdS->setText(QString());
        label_22->setText(QApplication::translate("MainWindow", "x:", Q_NULLPTR));
        lineEditStdX->setText(QString());
        label_23->setText(QApplication::translate("MainWindow", "y:", Q_NULLPTR));
        label_24->setText(QApplication::translate("MainWindow", "z\357\274\232", Q_NULLPTR));
        lineEditPeaS->setText(QString());
        label_26->setText(QApplication::translate("MainWindow", "x:", Q_NULLPTR));
        lineEditPeaX->setText(QString());
        label_27->setText(QApplication::translate("MainWindow", "y:", Q_NULLPTR));
        label_28->setText(QApplication::translate("MainWindow", "z\357\274\232", Q_NULLPTR));
        label_29->setText(QApplication::translate("MainWindow", "\345\235\207\346\226\271\346\240\271\357\274\232", Q_NULLPTR));
        lineEditRmsS->setText(QString());
        label_30->setText(QApplication::translate("MainWindow", "x:", Q_NULLPTR));
        lineEditRmsX->setText(QString());
        label_31->setText(QApplication::translate("MainWindow", "y:", Q_NULLPTR));
        label_32->setText(QApplication::translate("MainWindow", "z\357\274\232", Q_NULLPTR));
        lineEditMarS->setText(QString());
        label_33->setText(QApplication::translate("MainWindow", "x:", Q_NULLPTR));
        lineEditMarX->setText(QString());
        label_34->setText(QApplication::translate("MainWindow", "y:", Q_NULLPTR));
        label_35->setText(QApplication::translate("MainWindow", "z\357\274\232", Q_NULLPTR));
        label_36->setText(QApplication::translate("MainWindow", "\350\204\211\345\206\262\345\272\246\357\274\232", Q_NULLPTR));
        lineEditPulS->setText(QString());
        label_37->setText(QApplication::translate("MainWindow", "x:", Q_NULLPTR));
        lineEditPulX->setText(QString());
        label_38->setText(QApplication::translate("MainWindow", "y:", Q_NULLPTR));
        label_39->setText(QApplication::translate("MainWindow", "z\357\274\232", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(MainTab), QApplication::translate("MainWindow", "\344\270\273\347\225\214\351\235\242", Q_NULLPTR));
        comboBox_3->clear();
        comboBox_3->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "\346\250\241\345\274\217\344\270\200", Q_NULLPTR)
         << QApplication::translate("MainWindow", "\346\250\241\345\274\217\344\272\214", Q_NULLPTR)
         << QApplication::translate("MainWindow", "\346\250\241\345\274\217\344\270\211", Q_NULLPTR)
        );
        label_43->setText(QApplication::translate("MainWindow", "\345\271\205\345\200\274:", Q_NULLPTR));
        lineEdit_All->setText(QString());
        label_4->setText(QApplication::translate("MainWindow", "x:", Q_NULLPTR));
        lineEdit_X->setText(QString());
        label_5->setText(QApplication::translate("MainWindow", "y:", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "z\357\274\232", Q_NULLPTR));
        label_46->setText(QApplication::translate("MainWindow", "\345\271\205\345\200\274:", Q_NULLPTR));
        lineEdit_DAll->setText(QString());
        label_47->setText(QApplication::translate("MainWindow", "x:", Q_NULLPTR));
        lineEdit_Dx->setText(QString());
        label_48->setText(QApplication::translate("MainWindow", "y:", Q_NULLPTR));
        label_49->setText(QApplication::translate("MainWindow", "z\357\274\232", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "\351\242\221\345\237\237\350\260\261", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "\345\212\237\347\216\207\350\260\261", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

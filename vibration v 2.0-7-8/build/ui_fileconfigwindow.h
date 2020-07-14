/********************************************************************************
** Form generated from reading UI file 'fileconfigwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILECONFIGWINDOW_H
#define UI_FILECONFIGWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>

QT_BEGIN_NAMESPACE

class Ui_FileConfigWindow
{
public:
    QStatusBar *statusbar;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout_2;
    QLineEdit *lineEdit_9;
    QPushButton *pushButton_4;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_8;
    QLineEdit *lineEdit_one;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_9;
    QLineEdit *lineEdit_two;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_10;
    QLineEdit *lineEdit_three;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_11;
    QLineEdit *lineEdit_four;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_12;
    QLineEdit *lineEdit_five;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_14;
    QLineEdit *lineEdit_six;
    QSpacerItem *horizontalSpacer_7;
    QLabel *label;
    QLineEdit *lineEdit_path;
    QPushButton *pushButton;

    void setupUi(QDialog *FileConfigWindow)
    {
        if (FileConfigWindow->objectName().isEmpty())
            FileConfigWindow->setObjectName(QStringLiteral("FileConfigWindow"));
        FileConfigWindow->resize(600, 400);
        FileConfigWindow->setMinimumSize(QSize(600, 400));
        FileConfigWindow->setMaximumSize(QSize(600, 400));
        statusbar = new QStatusBar(FileConfigWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        statusbar->setGeometry(QRect(0, 0, 3, 22));
        gridLayout_3 = new QGridLayout(FileConfigWindow);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        lineEdit_9 = new QLineEdit(FileConfigWindow);
        lineEdit_9->setObjectName(QStringLiteral("lineEdit_9"));

        gridLayout_2->addWidget(lineEdit_9, 1, 0, 1, 1);

        pushButton_4 = new QPushButton(FileConfigWindow);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        gridLayout_2->addWidget(pushButton_4, 1, 1, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(156, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_8, 1, 2, 1, 1);

        pushButton_2 = new QPushButton(FileConfigWindow);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        gridLayout_2->addWidget(pushButton_2, 1, 3, 1, 1);

        pushButton_3 = new QPushButton(FileConfigWindow);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        gridLayout_2->addWidget(pushButton_3, 1, 4, 1, 1);

        groupBox = new QGroupBox(FileConfigWindow);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayout->addWidget(label_8);

        lineEdit_one = new QLineEdit(groupBox);
        lineEdit_one->setObjectName(QStringLiteral("lineEdit_one"));

        horizontalLayout->addWidget(lineEdit_one);

        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 2);
        horizontalLayout->setStretch(2, 1);

        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QStringLiteral("label_9"));

        horizontalLayout_2->addWidget(label_9);

        lineEdit_two = new QLineEdit(groupBox);
        lineEdit_two->setObjectName(QStringLiteral("lineEdit_two"));

        horizontalLayout_2->addWidget(lineEdit_two);

        horizontalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 2);
        horizontalLayout_2->setStretch(2, 1);

        gridLayout->addLayout(horizontalLayout_2, 1, 0, 1, 3);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QStringLiteral("label_10"));

        horizontalLayout_3->addWidget(label_10);

        lineEdit_three = new QLineEdit(groupBox);
        lineEdit_three->setObjectName(QStringLiteral("lineEdit_three"));

        horizontalLayout_3->addWidget(lineEdit_three);

        horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        horizontalLayout_3->setStretch(0, 1);
        horizontalLayout_3->setStretch(1, 2);
        horizontalLayout_3->setStretch(2, 1);

        gridLayout->addLayout(horizontalLayout_3, 2, 0, 1, 3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QStringLiteral("label_11"));

        horizontalLayout_4->addWidget(label_11);

        lineEdit_four = new QLineEdit(groupBox);
        lineEdit_four->setObjectName(QStringLiteral("lineEdit_four"));

        horizontalLayout_4->addWidget(lineEdit_four);

        horizontalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        horizontalLayout_4->setStretch(0, 1);
        horizontalLayout_4->setStretch(1, 2);
        horizontalLayout_4->setStretch(2, 1);

        gridLayout->addLayout(horizontalLayout_4, 3, 0, 1, 3);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_12 = new QLabel(groupBox);
        label_12->setObjectName(QStringLiteral("label_12"));

        horizontalLayout_5->addWidget(label_12);

        lineEdit_five = new QLineEdit(groupBox);
        lineEdit_five->setObjectName(QStringLiteral("lineEdit_five"));

        horizontalLayout_5->addWidget(lineEdit_five);

        horizontalSpacer_5 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);

        horizontalLayout_5->setStretch(0, 1);
        horizontalLayout_5->setStretch(1, 2);
        horizontalLayout_5->setStretch(2, 1);

        gridLayout->addLayout(horizontalLayout_5, 4, 0, 1, 3);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_14 = new QLabel(groupBox);
        label_14->setObjectName(QStringLiteral("label_14"));

        horizontalLayout_7->addWidget(label_14);

        lineEdit_six = new QLineEdit(groupBox);
        lineEdit_six->setObjectName(QStringLiteral("lineEdit_six"));

        horizontalLayout_7->addWidget(lineEdit_six);

        horizontalSpacer_7 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_7);

        horizontalLayout_7->setStretch(0, 1);
        horizontalLayout_7->setStretch(1, 2);
        horizontalLayout_7->setStretch(2, 1);

        gridLayout->addLayout(horizontalLayout_7, 5, 0, 1, 3);

        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 6, 0, 1, 1);

        lineEdit_path = new QLineEdit(groupBox);
        lineEdit_path->setObjectName(QStringLiteral("lineEdit_path"));

        gridLayout->addWidget(lineEdit_path, 6, 1, 1, 1);

        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 6, 2, 1, 1);


        gridLayout_2->addWidget(groupBox, 0, 0, 1, 5);


        gridLayout_3->addLayout(gridLayout_2, 0, 0, 1, 1);


        retranslateUi(FileConfigWindow);

        QMetaObject::connectSlotsByName(FileConfigWindow);
    } // setupUi

    void retranslateUi(QDialog *FileConfigWindow)
    {
        FileConfigWindow->setWindowTitle(QApplication::translate("FileConfigWindow", "\346\226\207\344\273\266\345\221\275\345\220\215", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("FileConfigWindow", "\350\207\252\345\212\250\345\221\275\345\220\215", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("FileConfigWindow", "\351\200\200\345\207\272", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("FileConfigWindow", "\347\241\256\345\256\232", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("FileConfigWindow", "\344\277\235\345\255\230\350\267\257\345\276\204\345\222\214\346\226\207\344\273\266\345\221\275\345\220\215", Q_NULLPTR));
        label_8->setText(QApplication::translate("FileConfigWindow", "\344\274\240\346\204\237\345\231\2501\357\274\232", Q_NULLPTR));
        label_9->setText(QApplication::translate("FileConfigWindow", "\344\274\240\346\204\237\345\231\2502\357\274\232", Q_NULLPTR));
        label_10->setText(QApplication::translate("FileConfigWindow", "\344\274\240\346\204\237\345\231\2503\357\274\232", Q_NULLPTR));
        label_11->setText(QApplication::translate("FileConfigWindow", "\344\274\240\346\204\237\345\231\2504\357\274\232", Q_NULLPTR));
        label_12->setText(QApplication::translate("FileConfigWindow", "\344\274\240\346\204\237\345\231\2505\357\274\232", Q_NULLPTR));
        label_14->setText(QApplication::translate("FileConfigWindow", "\344\274\240\346\204\237\345\231\2506\357\274\232", Q_NULLPTR));
        label->setText(QApplication::translate("FileConfigWindow", "\346\226\207\344\273\266\344\277\235\345\255\230\350\267\257\345\276\204\357\274\232", Q_NULLPTR));
        pushButton->setText(QApplication::translate("FileConfigWindow", "\346\265\217\350\247\210", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class FileConfigWindow: public Ui_FileConfigWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILECONFIGWINDOW_H

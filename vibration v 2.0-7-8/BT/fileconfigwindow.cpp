#include "fileconfigwindow.h"
#include "ui_fileconfigwindow.h"
#include <QApplication>
#include <QPushButton>
#include <QFont>
#include <QProcessEnvironment>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <QDesktopWidget>
#include "bt.h"

FileConfigWindow::FileConfigWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileConfigWindow)
{
    ui->setupUi(this);
    QString path = QProcessEnvironment::systemEnvironment().value("HOME");
    ui->lineEdit_path->setText(path);
    ui->lineEdit_path->setFocusPolicy(Qt::NoFocus);
    QDesktopWidget *desktop = QApplication::desktop();
    move((desktop->width() - this->width()) / 2, (desktop->height() - this->height()) / 2);
    recordflag = false;
    setWindowModality(Qt::WindowModal);
}

FileConfigWindow::~FileConfigWindow()
{
    delete ui;
}

void FileConfigWindow::on_pushButton_2_clicked()
{
    this->close();
}

void FileConfigWindow::on_pushButton_3_clicked()
{
    fileNameQstirng.sensorOne = ui->lineEdit_one->text();
    fileNameQstirng.sensorTwo = ui->lineEdit_two->text();
    fileNameQstirng.sensorThree = ui->lineEdit_three->text();
    fileNameQstirng.sensorFour = ui->lineEdit_four->text();
    fileNameQstirng.sensorFive = ui->lineEdit_five->text();
    fileNameQstirng.sensorSix = ui->lineEdit_six->text();
    fileNameQstirng.path = ui->lineEdit_path->text() + "/";
    QFileInfo one(fileNameQstirng.path + fileNameQstirng.sensorOne + ".csv");
    QFileInfo two(fileNameQstirng.path + fileNameQstirng.sensorTwo + ".csv");
    QFileInfo three(fileNameQstirng.path + fileNameQstirng.sensorThree + ".csv");
    QFileInfo four(fileNameQstirng.path + fileNameQstirng.sensorFour + ".csv");
    QFileInfo five(fileNameQstirng.path + fileNameQstirng.sensorFive + ".csv");
    QFileInfo six(fileNameQstirng.path + fileNameQstirng.sensorSix + ".csv");
    if (one.isFile() || two.isFile() || three.isFile() || four.isFile() || five.isFile()
            || six.isFile()) {
        QMessageBox::StandardButton result = QMessageBox::information(this, "警告",
                                             "存在同名文件，确定覆盖么？",
                                             QMessageBox::Yes | QMessageBox::No);
        switch (result) {
        case QMessageBox::Yes:
            recordflag = true;
            close();
            break;
        case QMessageBox::No:
            return;
            break;
        default:
            return;
            break;
        }
    } else {
        close();
    }
    recordflag = true;
    if (fileNameQstirng.sensorOne.isEmpty() && fileNameQstirng.sensorTwo.isEmpty()
            && fileNameQstirng.sensorThree.isEmpty() &&
            fileNameQstirng.sensorFour.isEmpty() && fileNameQstirng.sensorFive.isEmpty()
            && fileNameQstirng.sensorSix.isEmpty())
        recordflag = false;
    model = true;
}

void FileConfigWindow::on_pushButton_4_clicked()
{
    QString filename = ui->lineEdit_9->text();
    if (sensorFlag.sensorOne)
        ui->lineEdit_one->setText(filename + "_module1");
    if (sensorFlag.sensorTwo)
        ui->lineEdit_two->setText(filename + "_module2");
    if (sensorFlag.sensorThree)
        ui->lineEdit_three->setText(filename + "_module3");
    if (sensorFlag.sensorFour)
        ui->lineEdit_four->setText(filename + "_module4");
    if (sensorFlag.sensorFive)
        ui->lineEdit_five->setText(filename + "_module5");
    if (sensorFlag.sensorSix)
        ui->lineEdit_six->setText(filename + "_module6");
}

void FileConfigWindow::on_pushButton_clicked()
{
    QString path = QFileDialog::getExistingDirectory(this, "请选择文件保存路径...", "./");
    ui->lineEdit_path->setText(path);
}


void FileConfigWindow::sensorFlagChages(connFlag *temp)
{
    sensorFlag = *temp;

}

void FileConfigWindow::LineSetEnabled()
{
    ui->lineEdit_one->setEnabled(true);
    ui->lineEdit_two->setEnabled(true);
    ui->lineEdit_three->setEnabled(true);
    ui->lineEdit_four->setEnabled(true);
    ui->lineEdit_five->setEnabled(true);
    ui->lineEdit_six->setEnabled(true);

    if (!sensorFlag.sensorOne){
        ui->lineEdit_one->setEnabled(false);
        ui->lineEdit_one->setText("");
    }

    if (!sensorFlag.sensorTwo){
        ui->lineEdit_two->setEnabled(false);
        ui->lineEdit_two->setText("");
    }

    if (!sensorFlag.sensorThree){
        ui->lineEdit_three->setEnabled(false);
        ui->lineEdit_three->setText("");
    }

    if (!sensorFlag.sensorFour){
        ui->lineEdit_four->setEnabled(false);
        ui->lineEdit_four->setText("");
    }

    if (!sensorFlag.sensorFive){
        ui->lineEdit_five->setEnabled(false);
        ui->lineEdit_five->setText("");
    }

    if (!sensorFlag.sensorSix){
        ui->lineEdit_six->setEnabled(false);
        ui->lineEdit_six->setText("");
    }
}

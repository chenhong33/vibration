#ifndef FILECONFIGWINDOW_H
#define FILECONFIGWINDOW_H

#include <QMainWindow>
#include <QDialog>

typedef struct fileName {
    QString path;
    QString sensorOne;
    QString sensorTwo;
    QString sensorThree;
    QString sensorFour;
    QString sensorFive;
    QString sensorSix;
} structFileName;

typedef struct allModulesConnFlag {
    bool sensorOne;
    bool sensorTwo;
    bool sensorThree;
    bool sensorFour;
    bool sensorFive;
    bool sensorSix;
} connFlag;




namespace Ui {
class FileConfigWindow;
}

class FileConfigWindow : public QDialog
{
    Q_OBJECT

public:
    explicit FileConfigWindow(QWidget *parent = 0);
    ~FileConfigWindow();
    structFileName fileNameQstirng;
    connFlag sensorFlag;
    bool recordflag;
    void sensorFlagChages(connFlag *);
    void LineSetEnabled(void);
    bool model;
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

private:
    Ui::FileConfigWindow *ui;
};

#endif // FILECONFIGWINDOW_H

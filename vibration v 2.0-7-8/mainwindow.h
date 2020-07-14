#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts/QChartGlobal>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGraphicsWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGraphicsGridLayout>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <formwindow.h>
#include <vibration.h>
#include <BT/bt.h>
#include <viball.h>
#include <time.h>


QT_CHARTS_USE_NAMESPACE
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QChart *chart_1, *chart_2, *chart_3, *chart_4;

private slots:

    void handleMarkerClicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_comboBox_2_currentIndexChanged(int index);

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    void addSeries(QChart *, int, int, QString);
    void addFftSeries(QChart *, int, int, QString);
    void setToTitle(QChart *, QString);
    void setAcceleration(QChartView *, int, QString);
    void setFft(QChartView *, int, QString);
    void connectMarkers(QChart *);
    void disconnectMarkers(QChart *);
    void setAnalyze(struct analyze, struct analyze, struct analyze);
    void comSetSeries(viball *);
    void ButtonsetEnabled();
    void saveDataToText(QString ,viball *);
    FormWindow *formwindow;
    QTextStream *file;
    QString fileName;
    BT *ret;
    viball *vibration_1;
    viball *vibration_2;
    viball *vibration_3;
    viball *vibration_4;
    QTimer *timer;


protected:


};



#endif // MAINWINDOW_H

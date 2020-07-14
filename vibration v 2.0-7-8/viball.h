#ifndef VIBALL_H
#define VIBALL_H

#include <vibration.h>
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

#define FREQUENCY 200

class viball
{
public:
    viball(QString);
    ~viball();
    void addSeries(int, int, QString, double *);
    void addFftSeries(int, int, QString, double *);
    void dataToSeries(QSplineSeries *, double *, int, bool, int);
    double *data_seriesAcceleration_X;
    double *data_seriesAngular_X;
    double *data_seriesAccelerationFft_X;
    double *data_seriesAngularFft_X;
    double *data_seriesAcceleration_Y;
    double *data_seriesAngular_Y;
    double *data_seriesAccelerationFft_Y;
    double *data_seriesAngularFft_Y;
    double *data_seriesAcceleration_Z;
    double *data_seriesAngular_Z;
    double *data_seriesAccelerationFft_Z;
    double *data_seriesAngularFft_Z;
    struct analyze *vibrationX;
    struct analyze *vibrationY;
    struct analyze *vibrationZ;
    struct analyze *vibrationAll;
    struct analyzeFft *vibrationAccFft;
    struct analyzeFft *vibrationAngFft;
    int fileGetLine;


};

#endif // VIBALL_H

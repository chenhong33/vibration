#ifndef FORMWINDOW_H
#define FORMWINDOW_H

#include <QMainWindow>
#include <QChart>
#include <QChartView>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <view.h>

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class FormWindow;
}

class FormWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormWindow(QWidget *parent = 0);
    ~FormWindow();
    QChart *chart_1, *chart_2, *chart_3, *chart_4;

//private:
    Ui::FormWindow *ui;

private:
    void addSeries(QChart *, int, int, QString);
    void addFftSeries(QChart *, int, int, QString);
    void setToTitle(QChart *, QString);
    void setAcceleration(QChartView *, int, QString);
    void setFft(QChartView *, int, QString);
    void connectMarkers(QChart *);
    void disconnectMarkers(QChart *);
    double gauss();
    FormWindow *formwindow;
    void paintEvent(QPaintEvent *);
    QGraphicsLineItem *m_coordX;
    QGraphicsLineItem *m_coordY;
    QGraphicsScene *scene;
    View *chartview;



protected slots:
    void handleMarkerClicked();
};

#endif // FORMWINDOW_H

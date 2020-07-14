#include "mainwindow.h"
#include <QApplication>
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
#include <QTranslator>
#include <QTextCodec>
#include <QSharedMemory>

QT_CHARTS_USE_NAMESPACE

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
    QApplication a(argc, argv);
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);
    MainWindow w;
    //w.setWindowState(Qt::WindowMaximized);
    w.setGeometry(0,0,1920,1000);
    w.show();

    QSharedMemory shared("MainWindow");
    if(shared.attach())//共享内存被占用则直接返回
    {
        return 0;
    }
    shared.create(1);
    return a.exec();
}

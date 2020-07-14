#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <fftw3.h>
#include "vibration.h"
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
#include <QTextStream>
#include <QLegendMarker>
#include <QDebug>
#include <QList>
#include <QLineSeries>
#include <QTime>
#include <QtGlobal>
#include <cmath>
#include <QValueAxis>
#include <QChart>
#include <string.h>
#include <QFileDialog>
#include <QStringList>
#include "BT/bt.h"
#include <QMessageBox>
#include <viball.h>
#include <QFileInfo>
#include <QTimer>


/*
 * 软件由四个功能模块组成：1.基础支持模块
 *                      2.打开文件功能模块
 *                      3.选择传感器模块
 *                      4.开始计算模块
 *
 * 基础支持模块：是最主要的软件功能实现，包括读取加速度和角速度的数据，并进行傅里叶变换、分析时域数据和频域数据，然后进行数据显示
 *           1. 读取文件数据：传感器的数据包括 X、Y、Z三个方向的加速度数据和X、Y、Z三个方向的角速度数据，数据存储于 .csv 文件中，格式为：
 *             -0.0334473,-0.0610352,-0.772949,2.68555,6.89697,-1.70898,-179.528,-3.99353,-11.1237。
 *              前面6个数据分别为：加速度x方向、加速度y方向、加速度z方向、角速度x方向、角速度y方向、角速度z方向
 *              读取加速度和角速度数据的函数为addSeries()，将数据绑定到chart上
 *              读取加速度和角速度数据并进行傅里叶变换的函数为addFftSeries()将数据绑定到chart上;
 *
 *           2.图表配置：画图的流程是 qlineseries -> qchart -> chartsview 。图表有大量属性：包括线的大小和颜色、标题和图例等，
 *             主要有setToTitle()设置表的标题和图例及图例的方向，其他功能的代码为了方便，都写在了不同的函数中
 *             点击图例单选曲线功能包括了connectMarkers()、disconnectMarkers()、handleMarkerClicked()三个函数
 *
 *           3.显示数据曲线和结果：是由setAcceleration()、setFft()实现的,它们分别是调用了addSeries(),addFftSeries()
 *              vibrationAnalyze()是进行时域分析的函数与其配合的数据结构是struct analyze  、setAnalyze()是设置时域分析的结果到ui上
 *              频域分析的结果设置到ui上是addFftSeries()实现的
 *
 *打开文件功能模块：
 *              这个模块的功能比较简单，使用了基础支持模块的功能
 *
 *
 *
 * 选择传感器模块：
 *             这个模块的具体实现不明，与主程序的通信的是结构体structFileName，structFileName.path 是传感器数据的保存路径，其他的是
 *             传感器数据的文件名 接口时BT::fileConf->fileNameQstirng;
 *
 *
 *
 * 开始计算功能：
 *             on_pushButton_clicked();
 *             这个模块最主要的是根据结构体structFileName中的文件路径和名称,获取文件中的加速度和角速度的数据，并进行数据的分析和计算。
 *             数据分析的功能是由viball类实现的，向viball中传入文件完整路径和名称，调用构造函数即可。
 *             viball类包括函数addSeries()、addFftSeries()、dataToSeries()。调用了vibration.h 中的函数，vibration.h 主要是读取数据
 *             和进行分析的函数
 *
 *
 *
 *
 *
 *
 *
 */

QT_CHARTS_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent) : //初始化
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    chart_1 = new QChart();  //从一到四分别是加速度时域图、角加速度时域图、加速度频谱图、角加速度频谱图
    chart_2 = new QChart();  //画图的流程是 qlineseries -> qchart -> chartsview
    chart_3 = new QChart();
    chart_4 = new QChart();
    ret = NULL;              //ret 是加速度传感器模块的指针
    vibration_1 = NULL;      //vibration 是加速度传感器的数据 包括-> 特定时长的X、Y、Z加速度数据和角速度数据；X、Y、Z
    vibration_2 = NULL;      //加速度和角速度傅立叶变换后的数据，加速度时域分析结果和频域分析的结果
    vibration_3 = NULL;      //一到四代表现在支持四个传感器
    vibration_4 = NULL;
    ui->chartsView->setChart(chart_1);
    ui->chartsView->setRenderHint(QPainter::Antialiasing);
    ui->chartsView_2->setChart(chart_2);
    ui->chartsView_2->setRenderHint(QPainter::Antialiasing);
    ui->chartsView_4->setChart(chart_3);
    ui->chartsView_4->setRenderHint(QPainter::Antialiasing);
    ui->chartsView_5->setChart(chart_4);
    ui->chartsView_5->setRenderHint(QPainter::Antialiasing);
    ui->tabWidget->removeTab(2);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::addSeries(QChart *chart, int count, int ii,
                           QString tmpStr) //绑定加速度到chart
{
    QSplineSeries *series = new QSplineSeries();
    QString str;
    if (ii == 0)
        str = "x";
    if (ii == 1)
        str = "y";
    if (ii == 2)
        str = "z";
    series->setName(QString(tmpStr + str));
    int N = FileLine(fileName) - FileLine(fileName) % FREQUENCY;
    QList<QPointF> data;
    QFile sunSpots(fileName);
    if (!sunSpots.open(QIODevice::ReadOnly | QIODevice::Text)) {
    }
    QTextStream stream(&sunSpots);
    QString line = stream.readLine();
    for (int i = 0; i < N; i++) {
        line = stream.readLine();
        QStringList values = line.split(",", QString::SkipEmptyParts);
        data.append(QPointF((double)i / FREQUENCY, values[count + ii].toDouble()));
    }
    sunSpots.close();
    series->append(data);
    while (!data.isEmpty())
        data.removeLast();
    switch (ii) { //设置颜色和线大小
    case 0:
        series->setPen(QPen(Qt::red, 0.5, Qt::SolidLine));
        break;
    case 1:
        series->setPen(QPen(Qt::blue, 0.5, Qt::SolidLine));
        break;
    case 2:
        series->setPen(QPen(Qt::darkGreen, 0.5, Qt::SolidLine));
        break;
    case 3:
        series->setPen(QPen(Qt::black, 0.5, Qt::SolidLine));
        break;
    }
    chart->addSeries(series); //添加曲线到m_chart
    if (ii == 0)
        chart->createDefaultAxes();
}

void MainWindow::setToTitle(QChart *tmpchart, QString tmpStr) //设置表的标题和图例
{
    // Set the title and show legend
    tmpchart->setTitle(tmpStr); //表的标题
    tmpchart->legend()->setVisible(true);
    tmpchart->setLocalizeNumbers(true);
    tmpchart->legend()->setAlignment(Qt::AlignBottom); //设置图例在下方
}

void MainWindow::connectMarkers(QChart *chart)  //绑定信号
{
//![1]
    // Connect all markers to handler
    const auto markers = chart->legend()->markers();
    for (QLegendMarker *marker : markers) {
        // Disconnect possible existing connection to avoid multiple connections
        QObject::disconnect(marker, &QLegendMarker::clicked,
                            this, &MainWindow::handleMarkerClicked);
        QObject::connect(marker, &QLegendMarker::clicked, this, &MainWindow::handleMarkerClicked);
    }
//![1]
}

void MainWindow::disconnectMarkers(QChart *chart)  //解除信号绑定
{
//![2]
    const auto markers = chart->legend()->markers();
    for (QLegendMarker *marker : markers) {
        QObject::disconnect(marker, &QLegendMarker::clicked,
                            this, &MainWindow::handleMarkerClicked);
    }
//![2]
}

void MainWindow::handleMarkerClicked()
{
//![3]
    QLegendMarker *marker = qobject_cast<QLegendMarker *> (sender()); //得到谁发出的信号
    Q_ASSERT(marker); //调试，不为NULL什么也不做
//![3]
//![4]
    switch (marker->type())
//![4]
    {
    case QLegendMarker::LegendMarkerTypeXY: {
//![5]
        // Toggle visibility of series
        marker->series()->setVisible(!marker->series()->isVisible()); //可见和不可见反转
        // Turn legend marker back to visible, since hiding series also hides the marker
        // and we don't want it to happen now.
        marker->setVisible(true); //设置图例可见
//![5]
//![6]
        // Dim the marker, if series is not visible
        qreal alpha = 1.0;
        if (!marker->series()->isVisible())
            alpha = 0.5;
        QColor color;
        QBrush brush = marker->labelBrush();
        color = brush.color();
        color.setAlphaF(alpha);
        brush.setColor(color);
        marker->setLabelBrush(brush); //字体透明
        brush = marker->brush();
        color = brush.color();
        color.setAlphaF(alpha);
        brush.setColor(color);
        marker->setBrush(brush); //图例透明
        QPen pen = marker->pen();
        color = pen.color();
        color.setAlphaF(alpha);
        pen.setColor(color);
        marker->setPen(pen);
//![6]
        break;
    }
    default: {
        qDebug() << "Unknown marker type";
        break;
    }
    }
}

void MainWindow::setAcceleration(QChartView *chartsView, int count,
                                 QString str) //设置加速度曲线
{
    QChart *chart;
    if (count == 0)
        chart = chart_1;
    else
        chart = chart_2;
    addSeries(chart, count * 3, 0, str);     //添加QSplineSeries到chart
    addSeries(chart, count * 3, 1, str);
    addSeries(chart, count * 3, 2, str);
    setToTitle(chart, str);                  //设置标题
    chartsView->setChart(chart);
    chartsView->setRenderHint(QPainter::Antialiasing);
    connectMarkers(chart);                   //绑定槽，实现点击隐藏功能
}

void MainWindow::setFft(QChartView *chartsView, int count, QString str) //设置fft变换曲线
{
    QChart *chart;
    if (count == 0)
        chart = chart_3;
    else
        chart = chart_4;
    addFftSeries(chart, count * 3, 0, str);
    addFftSeries(chart, count * 3, 1, str);
    addFftSeries(chart, count * 3, 2, str);
    setToTitle(chart, str);
    chartsView->setChart(chart);
    chartsView->setRenderHint(QPainter::Antialiasing);
    connectMarkers(chart);
}

void MainWindow::addFftSeries(QChart *chart, int count, int ii,
                              QString tmpStr) //绑定fft曲线到chart
{
    QSplineSeries *series = new QSplineSeries();
    QString str;
    if (ii == 0)
        str = "x";
    if (ii == 1)
        str = "y";
    if (ii == 2)
        str = "z";
    series->setName(QString(tmpStr + str));
    int N = FileLine(fileName) - FileLine(fileName) % FREQUENCY;  //采样点数
    //qDebug() << N;
    double f = FREQUENCY; //采样频率
    double *in;
    fftw_complex *out; //傅立叶变换数组
    in = (double *)malloc(sizeof(double) * N);
    out = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * N);
    fftw_plan p = fftw_plan_dft_r2c_1d(N, in, out, FFTW_ESTIMATE);
    double fftmean = 0.0;
    QList<QPointF> data; //series 需要的点集格式
    QFile sunSpots(fileName);
    if (!sunSpots.open(QIODevice::ReadOnly | QIODevice::Text)) {
        exit(1);
    }
    QTextStream stream(&sunSpots);
    QString line = stream.readLine();
    for (int i = 0; (!stream.atEnd()) && (i < N); i++) {
        line = stream.readLine();
        QStringList values = line.split(",", QString::SkipEmptyParts);
        in[i] = values.at(count + ii).toDouble();
        fftmean += in[i];
    }
    sunSpots.close();
    for (int i = 0; i < N; i++) //去掉直流分量
        in[i] = in[i] - fftmean / N;
    fftw_execute(p); //傅立叶变换
    double *fftdata;
    fftdata = new double[N / 2];
    fftdata[0] = sqrt(out[0][0] * out[0][0] + out[0][1] * out[0][1]) / N ;
    for (int i = 1; i < N / 2 ; i++) {
        data.append(QPointF(i * f / N, sqrt(out[i][0]*out[i][0] + out[i][1]*out[i][1]) / N * 2));
        fftdata[i] = sqrt(out[i][0] * out[i][0] + out[i][1] * out[i][1]) / N * 2;
    }
    if (count == 0) //只有加速度要 *9.8
        for (int i = 0; i < N / 2; i++)
            fftdata[i] = fftdata[i] * 9.8;
    fftw_destroy_plan(p);
    free(in);
    fftw_free(out);
    series->append(data);
    while (!data.isEmpty())
        data.removeLast();
    if (ii == 0 && count == 0)
        ui->lineEdit_X->setText(QString::number(findMax(fftdata, N / 2)));
    if (ii == 1 && count == 0)
        ui->lineEdit_Y->setText(QString::number(findMax(fftdata, N / 2)));
    if (ii == 2 && count == 0) {
        ui->lineEdit_Z->setText(QString::number(findMax(fftdata, N / 2)));
        double vectorSum = 0.0;
        vectorSum += ui->lineEdit_X->text().toDouble() * ui->lineEdit_X->text().toDouble();
        vectorSum += ui->lineEdit_Y->text().toDouble() * ui->lineEdit_Y->text().toDouble();
        vectorSum += ui->lineEdit_Z->text().toDouble() * ui->lineEdit_Z->text().toDouble();
        vectorSum = sqrt(vectorSum);
        ui->lineEdit_All->setText(QString::number(vectorSum));
    }
    if (ii == 0 && count == 3)
        ui->lineEdit_Dx->setText(QString::number(findMax(fftdata, N / 2)));
    if (ii == 1 && count == 3)
        ui->lineEdit_Dy->setText(QString::number(findMax(fftdata, N / 2)));
    if (ii == 2 && count == 3) {
        ui->lineEdit_Dz->setText(QString::number(findMax(fftdata, N / 2)));
        double vectorSum = 0.0;
        vectorSum += ui->lineEdit_Dx->text().toDouble() * ui->lineEdit_Dx->text().toDouble();
        vectorSum += ui->lineEdit_Dy->text().toDouble() * ui->lineEdit_Dy->text().toDouble();
        vectorSum += ui->lineEdit_Dz->text().toDouble() * ui->lineEdit_Dz->text().toDouble();
        vectorSum = sqrt(vectorSum);
        ui->lineEdit_DAll->setText(QString::number(vectorSum));
    }
    delete fftdata;
    switch (ii) {
    //设置颜色和线大小
    case 0:
        series->setPen(QPen(Qt::red, 0.5, Qt::SolidLine));
        break;
    case 1:
        series->setPen(QPen(Qt::blue, 0.5, Qt::SolidLine));
        break;
    case 2:
        series->setPen(QPen(Qt::darkGreen, 0.5, Qt::SolidLine));
        break;
    case 3:
        series->setPen(QPen(Qt::black, 0.5, Qt::SolidLine));
        break;
    }
    chart->addSeries(series);
    if (ii == 0) {
        chart->createDefaultAxes();
    }
}




void MainWindow::setAnalyze(struct analyze dataAnalyzeX, struct analyze dataAnalyzeY,
                            struct analyze dataAnalyzeZ)
{
    ui->lineEditAccX->setText(QString::number(dataAnalyzeX.mean));
    ui->lineEditAccY->setText(QString::number(dataAnalyzeY.mean));
    ui->lineEditAccZ->setText(QString::number(dataAnalyzeZ.mean));
    ui->lineEditAccS->setText(QString::number(
                                  (fabs(dataAnalyzeX.mean) + fabs(dataAnalyzeY.mean) + fabs(dataAnalyzeZ.mean)) / 3));
    ui->lineEditStdX->setText(QString::number(dataAnalyzeX.st));
    ui->lineEditStdY->setText(QString::number(dataAnalyzeY.st));
    ui->lineEditStdZ->setText(QString::number(dataAnalyzeZ.st));
    ui->lineEditStdS->setText(QString::number(
                                  (fabs(dataAnalyzeX.st) + fabs(dataAnalyzeY.st) + fabs(dataAnalyzeZ.st)) / 3));
    ui->lineEditPeaX->setText(QString::number(dataAnalyzeX.maxMin));
    ui->lineEditPeaY->setText(QString::number(dataAnalyzeY.maxMin));
    ui->lineEditPeaZ->setText(QString::number(dataAnalyzeZ.maxMin));
    ui->lineEditPeaS->setText(QString::number(
                                  (fabs(dataAnalyzeX.maxMin) + fabs(dataAnalyzeY.maxMin) + fabs(dataAnalyzeZ.maxMin)) / 3));
    ui->lineEditRmsX->setText(QString::number(dataAnalyzeX.rms));
    ui->lineEditRmsY->setText(QString::number(dataAnalyzeY.rms));
    ui->lineEditRmsZ->setText(QString::number(dataAnalyzeZ.rms));
    ui->lineEditRmsS->setText(QString::number(
                                  (fabs(dataAnalyzeX.rms) + fabs(dataAnalyzeY.rms) + fabs(dataAnalyzeZ.rms)) / 3));
    ui->lineEditMarX->setText(QString::number(dataAnalyzeX.mar));
    ui->lineEditMarY->setText(QString::number(dataAnalyzeY.mar));
    ui->lineEditMarZ->setText(QString::number(dataAnalyzeZ.mar));
    ui->lineEditMarS->setText(QString::number(
                                  (fabs(dataAnalyzeX.mar) + fabs(dataAnalyzeY.mar) + fabs(dataAnalyzeZ.mar)) / 3));
    ui->lineEditPulX->setText(QString::number(dataAnalyzeX.Impulse));
    ui->lineEditPulY->setText(QString::number(dataAnalyzeY.Impulse));
    ui->lineEditPulZ->setText(QString::number(dataAnalyzeZ.Impulse));
    ui->lineEditPulS->setText(QString::number(
                                  (fabs(dataAnalyzeX.Impulse) + fabs(dataAnalyzeY.Impulse) + fabs(dataAnalyzeZ.Impulse)) / 3));
}


void MainWindow::on_pushButton_2_clicked()
{   {
        if (ret == NULL) {
            ret = new BT(this);
            ret->startDataDisplay();
            ret->setWindowTitle("传感器连接");
            //ret->setWindowModality(Qt::ApplicationModal);
        }
        ret->show();
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    fileName = QFileDialog::getOpenFileName(this, tr("打开文件"), "",
                                            tr("txt Files (*.csv);;csv Files (*.txt)"));
    if (fileName.isEmpty()) {
        QMessageBox::about(NULL, "文件错误", "重新选择文件！");
        return;
    }
    chart_1->removeAllSeries();
    chart_2->removeAllSeries();
    chart_3->removeAllSeries();
    chart_4->removeAllSeries();
    setAcceleration(ui->chartsView, 0, "加速度");
    setAcceleration(ui->chartsView_2, 1, "角速度");
    setFft(ui->chartsView_4, 0, "加速度");
    setFft(ui->chartsView_5, 1, "角速度");
    int N = FileLine(fileName) - FileLine(fileName) % FREQUENCY;
    struct analyze dataAnalyzeX, dataAnalyzeY, dataAnalyzeZ;
    vibrationAnalyze(&dataAnalyzeX, N, 0, fileName);
    vibrationAnalyze(&dataAnalyzeY, N, 1, fileName);
    vibrationAnalyze(&dataAnalyzeZ, N, 2, fileName);
    setAnalyze(dataAnalyzeX, dataAnalyzeY, dataAnalyzeZ);
}


void MainWindow::on_comboBox_2_currentIndexChanged(int index)
{
    if (index == 0) {
        if (vibration_1 != NULL)
            comSetSeries(vibration_1);
        else {
            chart_1->removeAllSeries();
            chart_2->removeAllSeries();
            chart_3->removeAllSeries();
            chart_4->removeAllSeries();
        }
    }
    if (index == 1) {
        if (vibration_2 != NULL)
            comSetSeries(vibration_2);
        else {
            chart_1->removeAllSeries();
            chart_2->removeAllSeries();
            chart_3->removeAllSeries();
            chart_4->removeAllSeries();
        }
    }
    if (index == 2) {
        if (vibration_3 != NULL)
            comSetSeries(vibration_3);
        else {
            chart_1->removeAllSeries();
            chart_2->removeAllSeries();
            chart_3->removeAllSeries();
            chart_4->removeAllSeries();
        }
    }
    if (index == 3) {
        if (vibration_4 != NULL)
            comSetSeries(vibration_4);
        else {
            chart_1->removeAllSeries();
            chart_2->removeAllSeries();
            chart_3->removeAllSeries();
            chart_4->removeAllSeries();
        }
    }
    if (index == 4)
        qDebug() << 4;
    if (index == 5)
        qDebug() << 5;
}

void MainWindow::comSetSeries(viball *vibration)
{
    chart_1->removeAllSeries();
    chart_2->removeAllSeries();
    chart_3->removeAllSeries();
    chart_4->removeAllSeries();
    QSplineSeries *seriesAcceleration_X = new QSplineSeries();
    QSplineSeries *seriesAcceleration_Y = new QSplineSeries();
    QSplineSeries *seriesAcceleration_Z = new QSplineSeries();
    vibration->dataToSeries(seriesAcceleration_X, vibration->data_seriesAcceleration_X,
                            vibration->fileGetLine, true, 0);
    seriesAcceleration_X->setName("加速度x");
    vibration->dataToSeries(seriesAcceleration_Y, vibration->data_seriesAcceleration_Y,
                            vibration->fileGetLine, true, 1);
    seriesAcceleration_Y->setName("加速度y");
    vibration->dataToSeries(seriesAcceleration_Z, vibration->data_seriesAcceleration_Z,
                            vibration->fileGetLine, true, 2);
    seriesAcceleration_Z->setName("加速度z");
    chart_1->addSeries(seriesAcceleration_X);
    chart_1->createDefaultAxes();
    chart_1->addSeries(seriesAcceleration_Y);
    chart_1->addSeries(seriesAcceleration_Z);
    connectMarkers(chart_1);
    QSplineSeries *seriesAngular_X = new QSplineSeries();
    QSplineSeries *seriesAngular_Y = new QSplineSeries();
    QSplineSeries *seriesAngular_Z = new QSplineSeries();
    vibration->dataToSeries(seriesAngular_X, vibration->data_seriesAngular_X, vibration->fileGetLine,
                            true, 0);
    seriesAngular_X->setName("角速度x");
    vibration->dataToSeries(seriesAngular_Y, vibration->data_seriesAngular_Y, vibration->fileGetLine,
                            true, 1);
    seriesAngular_Y->setName("角速度y");
    vibration->dataToSeries(seriesAngular_Z, vibration->data_seriesAngular_Z, vibration->fileGetLine,
                            true, 2);
    seriesAngular_Z->setName("角速度z");
    chart_2->addSeries(seriesAngular_X);
    chart_2->createDefaultAxes();
    chart_2->addSeries(seriesAngular_Y);
    chart_2->addSeries(seriesAngular_Z);
    connectMarkers(chart_2);
    QSplineSeries *seriesAccelerationFft_X = new QSplineSeries();
    QSplineSeries *seriesAccelerationFft_Y = new QSplineSeries();
    QSplineSeries *seriesAccelerationFft_Z = new QSplineSeries();
    vibration->dataToSeries(seriesAccelerationFft_X, vibration->data_seriesAccelerationFft_X,
                            vibration->fileGetLine, false, 0);
    seriesAccelerationFft_X->setName("加速度x");
    vibration->dataToSeries(seriesAccelerationFft_Y, vibration->data_seriesAccelerationFft_Y,
                            vibration->fileGetLine, false, 1);
    seriesAccelerationFft_Y->setName("加速度y");
    vibration->dataToSeries(seriesAccelerationFft_Z, vibration->data_seriesAccelerationFft_Z,
                            vibration->fileGetLine, false, 2);
    seriesAccelerationFft_Z->setName("加速度z");
    chart_3->addSeries(seriesAccelerationFft_X);
    chart_3->createDefaultAxes();
    chart_3->addSeries(seriesAccelerationFft_Y);
    chart_3->addSeries(seriesAccelerationFft_Z);
    connectMarkers(chart_3);
    QSplineSeries *seriesAngularFft_X = new QSplineSeries();
    QSplineSeries *seriesAngularFft_Y = new QSplineSeries();
    QSplineSeries *seriesAngularFft_Z = new QSplineSeries();
    vibration->dataToSeries(seriesAngularFft_X, vibration->data_seriesAngularFft_X,
                            vibration->fileGetLine, false, 0);
    seriesAngularFft_X->setName("角速度x");
    vibration->dataToSeries(seriesAngularFft_Y, vibration->data_seriesAngularFft_Y,
                            vibration->fileGetLine, false, 1);
    seriesAngularFft_Y->setName("角速度y");
    vibration->dataToSeries(seriesAngularFft_Z, vibration->data_seriesAngularFft_Z,
                            vibration->fileGetLine, false, 2);
    seriesAngularFft_Z->setName("角速度z");
    chart_4->addSeries(seriesAngularFft_X);
    chart_4->createDefaultAxes();
    chart_4->addSeries(seriesAngularFft_Y);
    chart_4->addSeries(seriesAngularFft_Z);
    connectMarkers(chart_4);
    setToTitle(chart_1, "加速度");
    setToTitle(chart_2, "角速度");
    setToTitle(chart_3, "加速度");
    setToTitle(chart_4, "角速度");
    ui->lineEditAccX->setText(QString::number(vibration->vibrationX->mean));
    ui->lineEditAccY->setText(QString::number(vibration->vibrationY->mean));
    ui->lineEditAccZ->setText(QString::number(vibration->vibrationZ->mean));
    ui->lineEditAccS->setText(QString::number(
                                  (fabs(vibration->vibrationX->mean) + fabs(vibration->vibrationY->mean) + fabs(
                                       vibration->vibrationZ->mean)) / 3));
    ui->lineEditStdX->setText(QString::number(vibration->vibrationX->st));
    ui->lineEditStdY->setText(QString::number(vibration->vibrationY->st));
    ui->lineEditStdZ->setText(QString::number(vibration->vibrationZ->st));
    ui->lineEditStdS->setText(QString::number(
                                  (fabs(vibration->vibrationX->st) + fabs(vibration->vibrationY->st) + fabs(
                                       vibration->vibrationZ->st)) / 3));
    ui->lineEditPeaX->setText(QString::number(fabs(vibration->vibrationX->maxMin)));
    ui->lineEditPeaY->setText(QString::number(fabs(vibration->vibrationY->maxMin)));
    ui->lineEditPeaZ->setText(QString::number(fabs(vibration->vibrationZ->maxMin)));
    ui->lineEditPeaS->setText(QString::number(
                                  (fabs(vibration->vibrationX->maxMin) + fabs(vibration->vibrationY->maxMin) + fabs(
                                       vibration->vibrationZ->maxMin)) / 3));
    ui->lineEditRmsX->setText(QString::number(vibration->vibrationX->rms));
    ui->lineEditRmsY->setText(QString::number(vibration->vibrationY->rms));
    ui->lineEditRmsZ->setText(QString::number(vibration->vibrationZ->rms));
    ui->lineEditRmsS->setText(QString::number(
                                  (fabs(vibration->vibrationX->rms) + fabs(vibration->vibrationY->rms) + fabs(
                                       vibration->vibrationZ->rms)) / 3));
    ui->lineEditMarX->setText(QString::number(vibration->vibrationX->mar));
    ui->lineEditMarY->setText(QString::number(vibration->vibrationY->mar));
    ui->lineEditMarZ->setText(QString::number(vibration->vibrationZ->mar));
    ui->lineEditMarS->setText(QString::number(
                                  (fabs(vibration->vibrationX->mar) + fabs(vibration->vibrationY->mar) + fabs(
                                       vibration->vibrationZ->mar)) / 3));
    ui->lineEditPulX->setText(QString::number(vibration->vibrationX->Impulse));
    ui->lineEditPulY->setText(QString::number(vibration->vibrationY->Impulse));
    ui->lineEditPulZ->setText(QString::number(vibration->vibrationZ->Impulse));
    ui->lineEditPulS->setText(QString::number(
                                  (fabs(vibration->vibrationX->Impulse) + fabs(vibration->vibrationY->Impulse) + fabs(
                                       vibration->vibrationZ->Impulse)) / 3));

    ui->lineEdit_Dx->setText(QString::number(vibration->vibrationAngFft->FftAmsX));
    ui->lineEdit_Dy->setText(QString::number(vibration->vibrationAngFft->FftAmsY));
    ui->lineEdit_Dz->setText(QString::number(vibration->vibrationAngFft->FftAmsZ));
    ui->lineEdit_DAll->setText(QString::number(vibration->vibrationAngFft->FftAmsAll));

    ui->lineEdit_X->setText(QString::number(vibration->vibrationAccFft->FftAmsX));
    ui->lineEdit_Y->setText(QString::number(vibration->vibrationAccFft->FftAmsY));
    ui->lineEdit_Z->setText(QString::number(vibration->vibrationAccFft->FftAmsZ));
    ui->lineEdit_All->setText(QString::number(vibration->vibrationAccFft->FftAmsAll));



    qDebug() << "end";
    return;
}
static bool isFastClick(QObject *target, int delayTimeMil)
{
    qlonglong lastTick = (target->property("tick").toLongLong());
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    qlonglong tick =  (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
    target->setProperty("tick", tick);
    if (tick - lastTick > delayTimeMil)
    {
        return true;
    }
    return false;
}

void MainWindow::on_pushButton_clicked()
{

    bool flag = isFastClick(ui->pushButton,1000);
    if(flag == false)
    {
        return;
    }
    qDebug() << "运行槽函数";
    structFileName filename;
    if (ret != NULL && ret->fileConf != NULL) {
        filename = ret->fileConf->fileNameQstirng;
    }
    if (!filename.path.isEmpty()) {
        if (vibration_1 != NULL) {
            delete vibration_1;
            vibration_1 = NULL;
        }
        if (vibration_2 != NULL) {
            delete vibration_2;
            vibration_2 = NULL;
        }
        if (vibration_3 != NULL) {
            delete vibration_3;
            vibration_3 = NULL;
        }
        if (vibration_4 != NULL) {
            delete vibration_4;
            vibration_4 = NULL;
        }
        QFileInfo modlue1(filename.path + filename.sensorOne + ".csv");
        if (modlue1.isFile() && modlue1.size() > 10240 && vibration_1 == NULL) {
            vibration_1 = new viball(filename.path + filename.sensorOne + ".csv");
            saveDataToText(filename.path + filename.sensorOne,vibration_1);
        }
        QFileInfo modlue2(filename.path + filename.sensorTwo + ".csv");
        if (modlue2.isFile() && modlue2.size() > 10240 && vibration_2 == NULL){
            vibration_2 = new viball(filename.path + filename.sensorTwo + ".csv");
            saveDataToText(filename.path + filename.sensorTwo,vibration_2);
        }
        QFileInfo modlue3(filename.path + filename.sensorThree + ".csv");
        if (modlue3.isFile() && modlue3.size() > 10240 && vibration_3 == NULL){
            vibration_3 = new viball(filename.path + filename.sensorThree + ".csv");
            saveDataToText(filename.path + filename.sensorThree,vibration_3);
        }
        QFileInfo modlue4(filename.path + filename.sensorFour + ".csv");
        if (modlue4.isFile() && modlue4.size() > 10240 && vibration_4 == NULL){
            vibration_4 = new viball(filename.path + filename.sensorFour + ".csv");
            saveDataToText(filename.path + filename.sensorFour,vibration_4);
        }

        ui->comboBox_2->setCurrentIndex(5);
        if (vibration_1 != NULL) {
            ui->comboBox_2->setCurrentIndex(0);
            return;
        }
        if (vibration_2 != NULL) {
            ui->comboBox_2->setCurrentIndex(1);
            return;
        }
        if (vibration_3 != NULL) {
            ui->comboBox_2->setCurrentIndex(2);
            return;
        }
        if (vibration_4 != NULL) {
            ui->comboBox_2->setCurrentIndex(3);
            return;
        }
    }
}

void MainWindow::ButtonsetEnabled(){
    ui->pushButton->setEnabled(true);
}

void MainWindow::saveDataToText(QString filename,viball *vib){
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy.MM.dd hh:mm:ss.zzz ddd");
    QFile file(filename + "-结果数据.csv");
    if(!file.open(QIODevice::WriteOnly  | QIODevice::Text|QIODevice::Append))
    {
        return;
    }
    QTextStream in(&file);
    in << current_date << endl;
    in << tr("项目") << "," << tr("x方向") << "," << tr("y方向") << "," << tr("z方向") << "," << tr("平均值") << endl;
    in << tr("加速度平均值") << "," << vib->vibrationX->mean << "," <<  "," <<vib->vibrationY->mean << ","
       << vib->vibrationZ->mean << "," << vib->vibrationAll->mean << "," << endl;
    in << tr("加速度均方根") << "," << vib->vibrationX->rms << "," << vib->vibrationY->rms << ","
       << vib->vibrationZ->rms << "," << vib->vibrationAll->rms <<  "," << endl;
    in << tr("加速度标准差") << "," << vib->vibrationX->st << "," << vib->vibrationY->st << ","
       << vib->vibrationZ->st << "," << vib->vibrationAll->st <<  "," << endl;
    in << tr("加速度峰-峰值") << "," << vib->vibrationX->maxMin << "," << vib->vibrationY->maxMin << ","
       << vib->vibrationZ->maxMin << "," << vib->vibrationAll->maxMin <<  "," << endl;
    in << tr("加速度脉冲度") << "," << vib->vibrationX->Impulse << "," << vib->vibrationY->Impulse << ","
       << vib->vibrationZ->Impulse << "," << vib->vibrationAll->Impulse <<  "," << endl;
    in << tr("加速度裕度因子") << "," << vib->vibrationX->mar << "," << vib->vibrationY->mar << ","
       << vib->vibrationZ->mar << "," << vib->vibrationAll->mar <<  "," << endl;
    in << tr("频谱幅值") << "," << vib->vibrationAccFft->FftAmsX << "," << vib->vibrationAccFft->FftAmsY << ","
       << vib->vibrationAccFft->FftAmsZ << "," << vib->vibrationAccFft->FftAmsAll <<  "," << endl;
    file.close();
}








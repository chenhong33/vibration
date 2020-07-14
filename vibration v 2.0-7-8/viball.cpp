#include "viball.h"
#include "fftw3.h"
#include <QDebug>
QT_CHARTS_USE_NAMESPACE

viball::viball(QString filename)
{
    vibrationX = new struct analyze;
    vibrationY = new struct analyze;
    vibrationZ = new struct analyze;
    vibrationAll = new struct analyze;
    vibrationAccFft = new struct analyzeFft;
    vibrationAngFft = new struct analyzeFft;
    int N = FileLine(filename) - FileLine(filename) % FREQUENCY;
    fileGetLine = N;
    data_seriesAcceleration_X = new double[N];
    data_seriesAcceleration_Y = new double[N];
    data_seriesAcceleration_Z = new double[N];
    data_seriesAngular_X = new double[N];
    data_seriesAngular_Y = new double[N];
    data_seriesAngular_Z = new double[N];
    data_seriesAccelerationFft_X = new double[N / 2];
    data_seriesAccelerationFft_Y = new double[N / 2];
    data_seriesAccelerationFft_Z = new double[N / 2];
    data_seriesAngularFft_X = new double[N / 2];
    data_seriesAngularFft_Y = new double[N / 2];
    data_seriesAngularFft_Z = new double[N / 2];
    addSeries(0, 0, filename, data_seriesAcceleration_X);
    addSeries(0, 1, filename, data_seriesAcceleration_Y);
    addSeries(0, 2, filename, data_seriesAcceleration_Z);
    addSeries(3, 0, filename, data_seriesAngular_X);
    addSeries(3, 1, filename, data_seriesAngular_Y);
    addSeries(3, 2, filename, data_seriesAngular_Z);
    addFftSeries(0, 0, filename, data_seriesAccelerationFft_X);
    addFftSeries(0, 1, filename, data_seriesAccelerationFft_Y);
    addFftSeries(0, 2, filename, data_seriesAccelerationFft_Z);
    addFftSeries(3, 0, filename, data_seriesAngularFft_X);
    addFftSeries(3, 1, filename, data_seriesAngularFft_Y);
    addFftSeries(3, 2, filename, data_seriesAngularFft_Z);
    vibrationAnalyze(vibrationX, N, 0, filename); //设置加速度
    vibrationAnalyze(vibrationY, N, 1, filename);
    vibrationAnalyze(vibrationZ, N, 2, filename);
}

viball::~viball()
{
    delete vibrationX;
    delete vibrationY;
    delete vibrationZ;
    delete vibrationAll;
    delete vibrationAccFft;
    delete vibrationAngFft;
    delete data_seriesAccelerationFft_X;
    delete data_seriesAccelerationFft_Y;
    delete data_seriesAccelerationFft_Z;
    delete data_seriesAcceleration_X;
    delete data_seriesAcceleration_Y;
    delete data_seriesAcceleration_Z;
    delete data_seriesAngularFft_X;
    delete data_seriesAngularFft_Y;
    delete data_seriesAngularFft_Z;
    delete data_seriesAngular_X;
    delete data_seriesAngular_Y;
    delete data_seriesAngular_Z;
}

void viball::addSeries(int count, int ii, QString fileName,
                       double *seriesData) //绑定加速度到chart
{
    int N = FileLine(fileName) - FileLine(fileName) % FREQUENCY;
    QFile sunSpots(fileName);
    if (!sunSpots.open(QIODevice::ReadOnly | QIODevice::Text)) {
    }
    QTextStream stream(&sunSpots);
    QString line = stream.readLine();
    for (int i = 0; i < N; i++) {
        line = stream.readLine();
        QStringList values = line.split(",", QString::SkipEmptyParts);
        seriesData[i] = values[count + ii].toDouble();
    }
    sunSpots.close();
}

void viball::addFftSeries(int count, int ii, QString fileName,
                          double *seriesData) //绑定加速度到chart
{
    int N = FileLine(fileName) - FileLine(fileName) % FREQUENCY;  //采样点数
    double *in;
    fftw_complex *out; //傅立叶变换数组
    in = (double *)malloc(sizeof(double) * N);
    out = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * N);
    fftw_plan p = fftw_plan_dft_r2c_1d(N, in, out, FFTW_ESTIMATE);
    double fftmean = 0.0;
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
        //in[i][1] = 0;
    }
    //
    sunSpots.close();
    for (int i = 0; i < N; i++) //去掉直流分量
        in[i] = in[i] - fftmean / N;
    fftw_execute(p); //傅立叶变换
    //double Maxfft =0.0;
    double *fftdata;
    fftdata = new double[N / 2];
    if (count == 0) {
        fftdata[0] = sqrt(out[0][0] * out[0][0] + out[0][1] * out[0][1]) / N * 9.8;
        seriesData[0] = fftdata[0];
    } else {
        fftdata[0] = sqrt(out[0][0] * out[0][0] + out[0][1] * out[0][1]) / N ;
        seriesData[0] = fftdata[0];
    }
    for (int i = 1; i < N / 2 ; i++) {
        if (count == 0) {
            fftdata[i] = sqrt(out[i][0] * out[i][0] + out[i][1] * out[i][1]) / N * 2 * 9.8;
            seriesData[i] = fftdata[i];
        } else {
            fftdata[i] = sqrt(out[i][0] * out[i][0] + out[i][1] * out[i][1]) / N * 2;
            seriesData[i] = fftdata[i];
        }
    }
    if (ii == 0 && count == 0)
        vibrationAccFft->FftAmsX = findMax(fftdata, N / 2);
    if (ii == 1 && count == 0)
        vibrationAccFft->FftAmsY = findMax(fftdata, N / 2);
    if (ii == 2 && count == 0) {
        vibrationAccFft->FftAmsZ = findMax(fftdata, N / 2);
        vibrationAccFft->FftAmsAll = sqrt(vibrationAccFft->FftAmsX * vibrationAccFft->FftAmsX
                                          + vibrationAccFft->FftAmsY * vibrationAccFft->FftAmsY
                                          + vibrationAccFft->FftAmsZ * vibrationAccFft->FftAmsZ);
    }
    if (ii == 0 && count == 3)
        vibrationAngFft->FftAmsX = findMax(fftdata, N / 2);
    if (ii == 1 && count == 3)
        vibrationAngFft->FftAmsY = findMax(fftdata, N / 2);
    if (ii == 2 && count == 3) {
        vibrationAngFft->FftAmsZ = findMax(fftdata, N / 2);
        vibrationAngFft->FftAmsAll = sqrt(vibrationAngFft->FftAmsX * vibrationAngFft->FftAmsX
                                          + vibrationAngFft->FftAmsY * vibrationAngFft->FftAmsY
                                          + vibrationAngFft->FftAmsZ * vibrationAngFft->FftAmsZ);
    }
    fftw_destroy_plan(p);
    free(in);
    fftw_free(out);
    delete fftdata;
}

void viball::dataToSeries(QSplineSeries *series, double *data, int N, bool flag, int colour)
{
    QList<QPointF> Sdata;
    if (flag)
        for (int i = 0; i < N; ++i) {
            Sdata.append(QPointF((double)i / FREQUENCY, data[i]));
        } else
        for (int i = 0; i < N / 2; ++i) {
            Sdata.append(QPointF((double)i * FREQUENCY / N, data[i]));
        }
    series->append(Sdata);
    switch (colour) { //设置颜色和线大小
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
    while (!Sdata.isEmpty())
        Sdata.removeLast();
}

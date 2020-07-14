#ifndef VIBRATION_H
#define VIBRATION_H

#include <stdio.h>
#include <stdlib.h>
#include <QString>
#include <QFile>
#include <QList>
#include <QTextStream>
#include <QStringList>
#include <iostream>
#include <math.h>
#include <QChart>

struct analyze {
    double mean;
    double maxMin;
    double st;
    double rms;
    double Impulse;
    double mar;
};

struct analyzeFft {
    double FftAmsX;
    double FftAmsY;
    double FftAmsZ;
    double FftAmsAll;
};

inline bool FileToData(QString filename, int count, double *data, int dataSize)
{
    QFile sunSpots(filename);
    if (!sunSpots.open(QIODevice::ReadOnly | QIODevice::Text)) {
    }
    QTextStream stream(&sunSpots);
    QString line = stream.readLine();
    for (int i = 0; !stream.atEnd() && (i < dataSize); i++) {
        line = stream.readLine();
        QStringList values = line.split(",", QString::SkipEmptyParts);
        data[i] = values[count].toDouble();
    }
    bool tmp;
    tmp = !stream.atEnd();
    sunSpots.close();
    return tmp;
}

inline int FileLine(QString filename)
{
    int fileLine = 0;
    QFile sunSpots(filename);
    if (!sunSpots.open(QIODevice::ReadOnly | QIODevice::Text)) {
    }
    QTextStream stream(&sunSpots);
    stream.readLine();
    for (int i = 0; !stream.atEnd(); i++) {
        stream.readLine();
        fileLine++;
    }
    sunSpots.close();
    return fileLine;
}

inline double margin(double *data, int i, int count)
{
    double sum = 0.0;
    for (int j = 0; j < count; j += i)
        sum += sqrt(fabs(data[j]));
    return (sum / count) * (sum / count);
}



inline double gsl_stats_mean(double *data, int i, int count)
{
    double mean = 0.0;
    for (int j = 0; j < count; j += i)
        mean = mean + data[j];
    return mean / count ;
}

inline double gsl_stats_max(double *data, int i, int count)
{
    double max = 0.0;
    for (int j = 0; j < count; j += i)
        max = data[j] > max ? data[j] : max;
    return max;
}

inline double gsl_stats_min(double *data, int i, int count)
{
    double min = 0.0;
    for (int j = 0; j < count; j += i)
        min = data[j] < min ? data[j] : min;
    return min;
}

inline double gsl_stats_sd_m(double *data, int i, int count, double mean)
{
    double std = 0.0;
    for (int j = 0; j < count; j += i)
        std += (data[j] - mean) * (data[j] - mean);
    return sqrt(std / (count - 1));
}

inline double gsl_stats_absdev(double *data, int i, int count)
{
    double mean = 0.0;
    for (int j = 0; j < count; j += i)
        mean = mean + fabs(data[j]);
    return mean / count ;
}

inline double gsl_stats_tss(double *data, int i, int count)
{
    double mean = 0.0;
    for (int j = 0; j < count; j += i)
        mean = mean + data[j] * data[j];
    return sqrt(mean / count) ;
}

inline int vibrationAnalyze(struct analyze *analyzeData, int N, int count, QString filename)
{
    double *data = (double *)malloc(sizeof(double) * N);
    FileToData(filename, count, data, N);
    double mean = gsl_stats_mean(data, 1, N); //平均值
    double max = gsl_stats_max(data, 1, N);
    double min = gsl_stats_min(data, 1, N);
    double st = gsl_stats_sd_m(data, 1, N, mean); //标准差
    double r = gsl_stats_absdev(data, 1, N); //整流平均值
    double rms =  gsl_stats_tss(data, 1, N); //均方根
    double maxMin = fabs(max > fabs(min) ? max : min);
    double Impulse = maxMin / r;   //脉冲因子
    double mar = maxMin / margin(data, 1, N); //裕度因子
    analyzeData->mean = mean;
    analyzeData->maxMin = maxMin;
    analyzeData->st = st;
    analyzeData->rms = rms;
    analyzeData->Impulse = Impulse;
    analyzeData->mar = mar;
    free(data);
    return 1;
}

inline double findMax(double *data, int dataSize)
{
    double Max = 0.0;
    for (int i = 0; i < dataSize; i++)
        Max = Max > data[i] ? Max : data[i];
    return Max;
}



#endif // VIBRATION_H

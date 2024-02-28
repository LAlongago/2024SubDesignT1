#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_SubDesignT1.h"
#include <string>
#include <vector>
#include <QTextBrowser>
#include <QtCharts>

using namespace std;

class SubDesignT1 : public QMainWindow
{
    Q_OBJECT

public:
    SubDesignT1(QWidget *parent = nullptr);
    ~SubDesignT1();

private:
    Ui::SubDesignT1Class ui;
    int dataSize;
    int timeConsumed;
    string currentfd;
    string targetfd;
    vector<int> sortedData;
    QChart* chart;
    QChartView* chartView;
    void displayVectorInTextBrowser(vector<int>& sortedData, QTextBrowser* textBrowser);
    void updateChartData(const QString& sortName, long long timeConsumed);

private slots:
    void showSettingDialog();
    void on_Generate_triggered();
    void on_Open_triggered();
    void on_Save_triggered();
    void on_ShellSort_clicked();
    void on_QuickSort_clicked();
    void on_HeapSort_clicked();
    void on_MergeSort_clicked();
};

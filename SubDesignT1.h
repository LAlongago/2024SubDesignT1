#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_SubDesignT1.h"
#include <string>
#include <vector>
#include <QTextBrowser>

using namespace std;

class SubDesignT1 : public QMainWindow
{
    Q_OBJECT

public:
    SubDesignT1(QWidget *parent = nullptr);
    ~SubDesignT1();

private:
    Ui::SubDesignT1Class ui;
    string currentfd;
    string targetfd;
    vector<int> sortedData;
    void displayVectorInTextBrowser(vector<int>& sortedData, QTextBrowser* textBrowser);

private slots:
    void on_Generate_triggered();
    void on_Open_triggered();
    void on_Save_triggered();
    void on_ShellSort_clicked();
    void on_QuickSort_clicked();
    void on_HeapSort_clicked();
    void on_MergeSort_clicked();
};

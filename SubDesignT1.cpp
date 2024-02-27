#include "SubDesignT1.h"
#include "DataGenerator.h"
#include "Sorter.h"
#include "qfiledialog.h"
#include "qfile.h"
#include "qtextstream.h"
#include "qtextbrowser.h"
#include "qstatusbar.h"
#include "qstring.h"
#include "settingdialog.h"

SubDesignT1::SubDesignT1(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    connect(ui.ShellSort, &QPushButton::clicked, this, &SubDesignT1::on_ShellSort_clicked);
    connect(ui.QuickSort, &QPushButton::clicked, this, &SubDesignT1::on_QuickSort_clicked);
    connect(ui.HeapSort, &QPushButton::clicked, this, &SubDesignT1::on_HeapSort_clicked);
    connect(ui.MergeSort, &QPushButton::clicked, this, &SubDesignT1::on_MergeSort_clicked);
    connect(ui.Generate, &QAction::triggered, this, &SubDesignT1::on_Generate_triggered);
    connect(ui.Open, &QAction::triggered, this, &SubDesignT1::on_Open_triggered);
    connect(ui.Save, &QAction::triggered, this, &SubDesignT1::on_Save_triggered);
	connect(ui.Set, &QAction::triggered, this, &SubDesignT1::showSettingDialog);
}

SubDesignT1::~SubDesignT1()
{
}

void SubDesignT1::displayVectorInTextBrowser(vector<int>& sortedData, QTextBrowser* textBrowser)
{
	QString content;
	int i = 0;
	for (int value : sortedData) 
	{
		content += QString::number(value) + " "; // 将每个元素添加到字符串中，元素之间用空格分隔
	}
	textBrowser->setText(content); // 将构建好的字符串设置到 QTextBrowser 中显示
}

void SubDesignT1::showSettingDialog()
{
	SettingDialog dialog(this);
	if (dialog.exec() == QDialog::Accepted) // 如果对话框被接受
	{
		dataSize = dialog.getSize(); // 获取对话框中的数据大小
		statusBar()->showMessage("样本量已设置为 " + QString::number(dataSize), 2000); // 在状态栏中显示数据大小
		ui.sizeNumber->setText(QString::number(dataSize)); // 在界面上显示数据大小
	}
	else
	{
		statusBar()->showMessage("样本量未设置", 2000); // 在状态栏中显示数据大小未设置
	}
}

void SubDesignT1::on_Generate_triggered()
{
    QString filepath = QFileDialog::getSaveFileName(this, tr("生成数据文件"), "", tr("Text Files (*.txt)")); // 选择保存文件的路径
    if(filepath.isEmpty()) // 如果没有选择文件则返回
	{
		statusBar()->showMessage("未生成数据文件", 2000);
		return;
	}
    currentfd = filepath.toStdString();
	DataGenerator dg(dataSize,100000,currentfd); // 生成 dataSize 个 1-100000 之间的随机数
	dg.generate();
    QFile data(filepath);
    if (data.open(QIODevice::ReadOnly | QIODevice::Text)) // 以只读方式打开文件
    {
        QTextStream in(&data);
        QString content = in.readAll();
        ui.textBrowser->setText(content); 
        data.close();
    }
	statusBar()->showMessage("成功生成数据文件", 2000);
}

void SubDesignT1::on_Open_triggered()
{
	QString filepath = QFileDialog::getOpenFileName(this, tr("打开数据文件"), "", tr("Text Files (*.txt)"));
	if (filepath.isEmpty())
	{
		statusBar()->showMessage("未选择数据文件", 2000);
		return;
	}
	currentfd = filepath.toStdString();
	QFile data(filepath);
	if (data.open(QIODevice::ReadOnly | QIODevice::Text)) 
	{
		QTextStream in(&data);
		QString content = in.readAll();
		ui.textBrowser->setText(content); 
		data.close();
	}
	statusBar()->showMessage("成功打开数据文件", 2000);
}

void SubDesignT1::on_Save_triggered()
{
	QString filepath = QFileDialog::getSaveFileName(this, tr("保存数据文件"), "", tr("Text Files (*.txt)"));
	if(filepath.isEmpty()) 
	{
		statusBar()->showMessage("未保存数据文件", 2000);
		return;
	}
	currentfd = filepath.toStdString();
	QFile data(filepath);
	if (data.open(QIODevice::WriteOnly | QIODevice::Text)) 
	{
		QTextStream out(&data);
		out << ui.textBrowser->toPlainText();
		data.close();
	}
	statusBar()->showMessage("成功保存数据文件", 2000);
}

void SubDesignT1::on_ShellSort_clicked()
{
    ShellSort ss(currentfd); // 创建 ShellSort 对象
	ss.readData(); // 读取数据
	timeConsumed = ss.sort();
	sortedData = ss.getSortedData();
	displayVectorInTextBrowser(sortedData, ui.textBrowser);
	statusBar()->showMessage("希尔排序已完成", 2000);
	ui.methodText->setText("希尔排序");
	ui.timeNumber->setText(QString::number(timeConsumed) + "ms");
}

void SubDesignT1::on_QuickSort_clicked()
{
	QuickSort qs(currentfd);
	qs.readData();
	timeConsumed = qs.sort();
	sortedData = qs.getSortedData();
	displayVectorInTextBrowser(sortedData, ui.textBrowser);
	statusBar()->showMessage("快速排序已完成", 2000);
	ui.methodText->setText("快速排序");
	ui.timeNumber->setText(QString::number(timeConsumed) + "ms");
}

void SubDesignT1::on_HeapSort_clicked()
{
	HeapSort hs(currentfd);
	hs.readData();
	timeConsumed = hs.sort();
	sortedData = hs.getSortedData();
	displayVectorInTextBrowser(sortedData, ui.textBrowser);
	statusBar()->showMessage("堆排序已完成", 2000);
	ui.methodText->setText("堆排序");
	ui.timeNumber->setText(QString::number(timeConsumed) + "ms");
}

void SubDesignT1::on_MergeSort_clicked()
{
	MergeSort ms(currentfd);
	ms.readData();
	timeConsumed = ms.sort();
	sortedData = ms.getSortedData();
	displayVectorInTextBrowser(sortedData, ui.textBrowser);
	statusBar()->showMessage("归并排序已完成", 2000);
	ui.methodText->setText("归并排序");
	ui.timeNumber->setText(QString::number(timeConsumed) + "ms");
}

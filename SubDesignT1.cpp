#include "SubDesignT1.h"
#include "DataGenerator.h"
#include "Sorter.h"
#include "qfiledialog.h"
#include "qfile.h"
#include "qtextstream.h"
#include "qtextbrowser.h"
#include "qstatusbar.h"
#include "qstring.h"

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
		if (i++ % 10 == 0) 
		{
			content += "\n"; // 每 10 个元素换行
		}
	}
	textBrowser->setText(content); // 将构建好的字符串设置到 QTextBrowser 中显示
}

void SubDesignT1::on_Generate_triggered()
{
    QString filepath = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("Text Files (*.txt)")); // 选择保存文件的路径
    if(filepath.isEmpty()) // 如果没有选择文件则返回
	{
		statusBar()->showMessage("File not selected", 2000);
		return;
	}
    currentfd = filepath.toStdString();
	DataGenerator dg(10000,100000,currentfd); // 生成 10000 个 1-100000 之间的随机数
	dg.generate();
    QFile data(filepath);
    if (data.open(QIODevice::ReadOnly | QIODevice::Text)) // 以只读方式打开文件
    {
        QTextStream in(&data);
        QString content = in.readAll();
        ui.textBrowser->setText(content); 
        data.close();
    }
	statusBar()->showMessage("File generated successfully", 2000);
}

void SubDesignT1::on_Open_triggered()
{
	QString filepath = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Text Files (*.txt)"));
	if (filepath.isEmpty())
	{
		statusBar()->showMessage("File not selected", 2000);
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
	statusBar()->showMessage("File opened successfully", 2000);
}

void SubDesignT1::on_Save_triggered()
{
	QString filepath = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("Text Files (*.txt)"));
	if(filepath.isEmpty()) 
	{
		statusBar()->showMessage("File not selected", 2000);
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
	statusBar()->showMessage("File saved successfully", 2000);
}

void SubDesignT1::on_ShellSort_clicked()
{
    ShellSort ss(currentfd); // 创建 ShellSort 对象
	ss.sort();
	sortedData = ss.getSortedData();
	displayVectorInTextBrowser(sortedData, ui.textBrowser);
	statusBar()->showMessage("Shell sort completed", 2000);
}

void SubDesignT1::on_QuickSort_clicked()
{
	QuickSort qs(currentfd);
	qs.sort();
	sortedData = qs.getSortedData();
	displayVectorInTextBrowser(sortedData, ui.textBrowser);
	statusBar()->showMessage("Quick sort completed", 2000);
}

void SubDesignT1::on_HeapSort_clicked()
{
	HeapSort hs(currentfd);
	hs.sort();
	sortedData = hs.getSortedData();
	displayVectorInTextBrowser(sortedData, ui.textBrowser);
	statusBar()->showMessage("Heap sort completed", 2000);
}

void SubDesignT1::on_MergeSort_clicked()
{
	MergeSort ms(currentfd);
	ms.sort();
	sortedData = ms.getSortedData();
	displayVectorInTextBrowser(sortedData, ui.textBrowser);
	statusBar()->showMessage("Merge sort completed", 2000);
}

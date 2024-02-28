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
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>

QT_BEGIN_NAMESPACE
class QChartView;
class QChart;
QT_END_NAMESPACE

SubDesignT1::SubDesignT1(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	QVBoxLayout* layout = new QVBoxLayout(ui.widget);
	ui.widget->setLayout(layout); // 设置布局为水平布局
    //connect(ui.ShellSort, &QPushButton::clicked, this, &SubDesignT1::on_ShellSort_clicked);
    //connect(ui.QuickSort, &QPushButton::clicked, this, &SubDesignT1::on_QuickSort_clicked);
    //connect(ui.HeapSort, &QPushButton::clicked, this, &SubDesignT1::on_HeapSort_clicked);
    //connect(ui.MergeSort, &QPushButton::clicked, this, &SubDesignT1::on_MergeSort_clicked);
  /*  connect(ui.Generate, &QAction::triggered, this, &SubDesignT1::on_Generate_triggered);
    connect(ui.Open, &QAction::triggered, this, &SubDesignT1::on_Open_triggered);
    connect(ui.Save, &QAction::triggered, this, &SubDesignT1::on_Save_triggered);*/
	connect(ui.Set, &QAction::triggered, this, &SubDesignT1::showSettingDialog);

	dataSize = 0;
	timeConsumed = 0;
	currentfd = "";
	targetfd = "";
	sortedData = vector<int>();
	chart = new QChart();
	chartView = new QChartView(chart, this);
	ui.widget->layout()->addWidget(chartView);

	chart->setMargins(QMargins(0, 0, 0, 0));
	chart->legend()->setContentsMargins(QMargins(0, 0, 0, 0));
}

SubDesignT1::~SubDesignT1()
{
}

void SubDesignT1::updateChartData(const QString& sortName, long long timeConsumed)
{
	// 查找是否已有该排序算法的数据
	QBarSet* set = nullptr;
	for (QAbstractSeries* series : chart->series()) {
		QBarSeries* barSeries = static_cast<QBarSeries*>(series);
		for (QBarSet* existingSet : barSeries->barSets()) {
			if (existingSet->label() == sortName) {
				set = existingSet;
				break;
			}
		}
	}

	// 如果没有找到，创建新的BarSet
	if (!set) {
		set = new QBarSet(sortName);
		QBarSeries* series = new QBarSeries();
		series->append(set);
		chart->addSeries(series);

		// 检查是否已经添加了X轴和Y轴，如果没有，则添加
		if (chart->axes(Qt::Horizontal).isEmpty()) 
		{
			QBarCategoryAxis* axisX = new QBarCategoryAxis();
			QStringList categories;
			// 假设您所有的排序算法名称都应该在这里列出
			categories << "希尔排序" << "快速排序" << "堆排序" << "归并排序";
			axisX->append(categories);
			chart->addAxis(axisX, Qt::AlignBottom);
			static_cast<QBarSeries*>(chart->series().first())->attachAxis(axisX);
		}

		if (chart->axes(Qt::Vertical).isEmpty()) 
		{
			QValueAxis* axisY = new QValueAxis();
			axisY->setTitleText("耗时 (ms)");
			chart->addAxis(axisY, Qt::AlignLeft);
			static_cast<QBarSeries*>(chart->series().first())->attachAxis(axisY);
		}

		// 更新Y轴的范围以确保所有数据都可见
		QValueAxis* axisY = static_cast<QValueAxis*>(chart->axes(Qt::Vertical).first());
		long long maxTime = 0;
		for (QAbstractSeries* series : chart->series()) 
		{
			for (QBarSet* barSet : static_cast<QBarSeries*>(series)->barSets()) 
			{
				for (int i = 0; i < barSet->count(); ++i) 
				{
					maxTime = std::max(maxTime, static_cast<long long>(barSet->at(i)));
				}
			}
		}
		axisY->setRange(0, maxTime + (maxTime * 0.1)); // 添加10%的空间以避免柱形紧贴上边界
	}

	// 更新数据
	set->append(timeConsumed);

	// 重新设置图表以适应新数据
	chart->createDefaultAxes();
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

	updateChartData("希尔排序", timeConsumed);
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

	updateChartData("快速排序", timeConsumed);
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

	updateChartData("堆排序", timeConsumed);
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

	updateChartData("归并排序", timeConsumed);
}

#include "SubDesignT1.h"
#include <QtWidgets/QApplication>
#include "DataGenerator.h"
#include "Sorter.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SubDesignT1 w;
    w.show();
    return a.exec();
}
#include <QtGui/QApplication>
#include <QtCore/QTextCodec>
#include <QtCore/QTranslator>
#include "lhcwinwidget.h"
#include <qtsingleapplication.h>

int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
    QtSingleApplication a(argc, argv);
    if (a.IsRunning()) {
        return 0;
    }

    QTranslator translator;
    translator.load(qApp->applicationDirPath() + "/qt_zh_CN.qm");
    a.installTranslator(&translator);

    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());

    QCoreApplication::addLibraryPath(qApp->applicationDirPath() + "/plugins");

    LHCWinWidget w;
    a.SetActWindow(&w);
    w.show();
    
    return a.exec();
}

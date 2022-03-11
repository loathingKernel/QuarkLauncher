#include "quarklauncher.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QStyleFactory>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "QuarkLauncher_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    a.setStyle(QStyleFactory::create("Fusion"));
    QFile f(":/stylesheets/Quark/stylesheet.qss");
    if (f.open(QFile::ReadOnly)) {
        QString stylesheet(f.readAll());
        a.setStyleSheet(stylesheet);
    }

    a.setOrganizationName("QuarkLauncher");
    a.setApplicationName("QuarkLauncher");

    QuarkLauncher w;
    w.show();
    return a.exec();
}

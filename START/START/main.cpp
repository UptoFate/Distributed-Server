#include "START.h"
#include <QtWidgets/QApplication>
#include <QFile>
#include "util/Properties.h"

int main(int argc, char *argv[])
{
#ifdef Q_OS_LINUX
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QApplication a(argc, argv);
    QFile qss(":/style/stylesheet.qss");

    if (qss.open(QFile::ReadOnly))
    {
        qDebug("open success");
        QString style = QLatin1String(qss.readAll());
        a.setStyleSheet(style);
        qss.close();
    }
    else {
        qDebug("Open failed");
    }
    CREATE_PROPERTIES(prop, conf);
    string gate_host = prop.getProperty("host");
    string gate_port = prop.getProperty("port");
    gate_url_prefix = QString::fromStdString("https://" + gate_host + ":" + gate_port);
    START w;
    w.setWindowFlag(Qt::FramelessWindowHint);
    w.setAttribute(Qt::WA_TranslucentBackground);
    w.show();
    return a.exec();
}

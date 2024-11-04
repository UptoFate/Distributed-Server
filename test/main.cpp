#include "stdafx.h"
#include "login.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    //cout << secure::device::GetDeviceID::GetCpuID() << endl;
    //cout << secure::device::GetDeviceID::GetBiosID()<<endl;
    QApplication a(argc, argv);
    Login w;
    w.show();
    return a.exec();
}

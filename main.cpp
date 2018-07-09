#include <QCoreApplication>

bool debugLib();

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    debugLib();

    return a.exec();
}

bool debugLib(){
    return true;
}

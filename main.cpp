#include <QCoreApplication>
#include <QTextStream>
#include <QString>
#include "consolecount.h"

QString message()
{
    QString string;
    string.append("Run in the following format");
    string.append("\ncount [-ab -c] filename [filename ...]");
    return string;
}

int main(int argc, char *argv[])
{
    QTextStream out(stdout);

    if (argc == 1)
    {
        out << message() << Qt::endl;
    }
    else
    {
        QStringList args;
        for (int a=1; a<argc; a++)
        {
            args.append(argv[a]);
        }
        ConsoleCount consoleCount(args);
        out << consoleCount.doCount() << Qt::endl;
    }

    return 0;
}

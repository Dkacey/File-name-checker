#ifndef CONSOLECOUNT_H
#define CONSOLECOUNT_H

#include <QStringList>
#include <QRegularExpression>

class ConsoleCount
{
public:
    ConsoleCount();
    ConsoleCount(QStringList args);
    QString doCount();
private:
    bool aFlag, bFlag, cFlag, dFlag;
    QStringList filenames;
    QRegularExpression removeStr;

    QString processFile(QString f);
    QString process(char flag, QString contents);
};

#endif // CONSOLECOUNT_H

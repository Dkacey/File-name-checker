#include "consolecount.h"
#include <QRegularExpression>
#include <QFile>
#include <QTextStream>

ConsoleCount::ConsoleCount()
{
    aFlag = false;
    bFlag = false;
    cFlag = false;
    dFlag = false;
}

ConsoleCount::ConsoleCount(QStringList args)
{
    aFlag = false;
    bFlag = false;
    cFlag = false;
    dFlag = false;

    foreach (QString s, args)
    {
        if (s.at(0) == '-')
        {
            s.remove(0, 1);  //remove -
            while (s.length()>0)
            {
                switch (s.at(0).toLatin1())
                {
                case 'a': aFlag = true; break;
                case 'b': bFlag = true; break;
                case 'c': cFlag = true; break;
                case 'd': dFlag = true;
                }
                s.remove(0, 1);
            }
        }
        else
            filenames.append(s);
    }

    if (!aFlag && !bFlag && !cFlag && !dFlag) // no flags passed
    {
        aFlag = true;
        bFlag = true;
        cFlag = true;
        dFlag = true;
    }
}

QString ConsoleCount::doCount()
{
    QString result;
    if (filenames.size() > 0)
    {
        foreach (QString filename, filenames)
        {
            result.append(processFile(filename));
            result.append("\n");
        }
    }
    else
        result = QString("No files to process");
    return result;
}

QString ConsoleCount::processFile(QString f)
{
    QString result;

    QFile file(f);
    if (!file.open(QIODevice::ReadOnly))
    {
        result = QString("%1 did not open sucessfully").arg(f);
    }
    else
    {
        QTextStream in(&file);
        QString contents = in.readAll();
        file.close();

        result.append(QString("***" + f + "***\n"));
        QString str = contents.trimmed();
        removeStr.setPattern("[.,?!;:]");
        str.remove(removeStr);

        if (aFlag) result.append(process('a', str));
        if (bFlag) result.append(process('b', str));
        if (cFlag) result.append(process('c', str));
        if (dFlag) result.append(process('d', str));
    }

    return result;
}

QString ConsoleCount::process(char flag, QString contents)
{
    QRegularExpression regExp;
    QString message;
    switch (flag)
    {
    case 'a': regExp.setPattern("[A-Z][A-Za-z]{4,}");
              message.append("Number of words longer than 4 letters that start with a capital: ");
              break;
    case 'b': regExp.setPattern("[A-Za-z]+[-][A-Za-z]+");
              message.append("Number of hyphenated words: ");
              break;
    case 'c': regExp.setPattern("^([a-zA-Z])[a-zA-Z]*\\1$");
              message.append("Number of words that start and end on the same letter: ");
              break;
    case 'd': regExp.setPattern("^[^aeiouAEIOU].*$");
              message.append("Number of words that do not start with a vowel: ");
              break;
    }

    int position = 0;
    int count = 0;
    QString word;
    while (position < contents.length())
    {
        int next = contents.indexOf(" ", position);
        if (next == -1)
        {
            word = contents.mid(position, contents.length()-1);
            next = contents.length();
        }
        else
            word = contents.mid(position, next-position);
        if (regExp.match(word).hasMatch())
            count++;
        position = next+1;
    }

    message.append(QString::number(count));
    message.append("\n");
    return message;
}

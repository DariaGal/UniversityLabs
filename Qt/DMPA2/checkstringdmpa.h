#ifndef CHECKSTRINGDMPA_H
#define CHECKSTRINGDMPA_H
#include <QMap>
#include <QStringList>
class CheckStringDMPA
{
public:
    CheckStringDMPA(QMap<QString, QStringList> r,QString str,QString s,QStringList f,QStringList symbols,QString stackstart);
    QStringList Start();
private:
     QMap<QString,QStringList> rules;
     QString checkString,startState,stack,OutString;
     QStringList result,finishState,Symbols;
     void ChangeStack(QString s,QString sumbStack);
};

#endif // CHECKSTRINGDMPA_H

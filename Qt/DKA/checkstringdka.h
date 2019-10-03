#ifndef CHECKSTRINGDKA_H
#define CHECKSTRINGDKA_H
#include <QString>
#include <QStringList>
#include <QMap>
class CheckStringDKA
{
public:
    CheckStringDKA();
    void SetParameters(QMap<QString,QStringList> tableDKA,QStringList States,QStringList Symbols,QString StartState,QStringList FinishState,QString CheckString);
    QStringList Start();
private:
    QStringList States,Symbols,FinishState;
    QString StartState,CheckString;
    QString CurrentState;
    QMap<QString,QStringList> tableDKA;
    QStringList Result;
};

#endif // CHECKSTRINGDKA_H

#ifndef GRAMMARCONVERTER_H
#define GRAMMARCONVERTER_H
#include <QMap>
#include <QStringList>
class GrammarConverter
{
public:
    GrammarConverter(QMap<QString,QStringList> Rules,QString StartTerm,QStringList Term,QStringList NoTerm);
    QMap<QString,QStringList> RemoveUselessSymbols(QStringList &result);
    QMap<QString,QStringList> RemoveUnattainableSymbols(QStringList &result);
    QMap<QString,QStringList> RemoveEmptyRules(QStringList &result);
    QMap<QString,QStringList> RemoveLoopRules(QStringList &result);
    QMap<QString,QStringList> GetNewGram(QString &StartTerm,QStringList &NoTerm);
private:
    QMap<QString,QStringList> rules;
    QString StartTerm,tr;
    QStringList Term,NoTerm;
    QStringList Sub;
    void SubStrings(QString str,QStringList W);
    QMap<QString,QStringList> RemoveRules(QMap<QString,QStringList> R,QStringList Del);
    QStringList res(QMap<QString,QStringList> R);
};

#endif // GRAMMARCONVERTER_H

#ifndef STRINGSGENERATOR_H
#define STRINGSGENERATOR_H

#include <QObject>
#include <QStringList>
#include <QMap>
#include <QStack>
class StringsGenerator : public QObject
{
    Q_OBJECT
public:
    explicit StringsGenerator(QObject *parent = 0);
    void SetParemeters(QStringList t,QStringList n,QMap<QString,QStringList> r,QString s,int n1,int n2);
    void Start(QStringList NotermsEmpty);
    QStringList Print();
private:
    QStringList VT;
    QStringList VN;
    QString RuleArray[10][2];
    QString StartT;
    int RuleCount;
    QMap <QString,QStringList> Rules;
    struct step{
        QString currentString;
        QString nextRule;
        QStringList alternativeRules;
    };
    QStack<step> Generator;
    int CheckTermNumber(QString str,QStringList NotermsEmpty);
    void StopGenerate();
    bool StepBack;
    QStringList Result;
    int fromN,toN;
    QString EmptyS;

signals:

public slots:

};

#endif // STRINGSGENERATOR_H

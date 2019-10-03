#include "grammarconverter.h"
#include <QDebug>
GrammarConverter::GrammarConverter(QMap<QString,QStringList> Rules,QString StartTerm,QStringList Term,QStringList NoTerm)
{
    rules = Rules;
    this->StartTerm = StartTerm;
    this->Term = Term;
    this->NoTerm = NoTerm;
    qDebug()<<Term;
    foreach(QString s, Term)
    {
        tr.append(s+",");
    }

    qDebug()<<tr;
    tr.remove(tr.size()-1,1);
}
QMap<QString,QStringList> GrammarConverter::RemoveUselessSymbols(QStringList &result)
{
    result.append("Этап 1. Удаление бесплодных символов.");
    int k = 0;
    result.append(QString::number(k+1)+". Y"+QString::number(k)+"=O"+", i="+QString::number(k+1));
    k++;
    QStringList Y;
    QMap<QString,QStringList> R = rules;
    while(1)
    {

        QStringList Del,oldY = Y;
        for(auto r : R.keys())
        {
              QStringList list = R.value(r);
              for(int i=0;i<list.size();i++)
              {
                  QString s = list.at(i);
                  bool f = true;
                  for(int j=0;j<s.size();j++)
                  {
                      QString c = s.at(j);
                      if(!Term.contains(c)&&c!="~")
                      {
                          if(!Y.contains(c))
                          {
                              f = false;
                              break;
                          }
                      }
                  }
                  if(f)
                  {
                      Y.append(r);
                      break;
                  }
              }
            Del.append(r);
        }

        foreach (QString t, Y) {
            R.remove(t);
        }
        QString y;
        foreach(QString s, Y){
            y.append(s+",");
        }
        y.remove(y.size()-1,1);
        if(oldY == Y)
        {
            foreach (QString t, Del) {
                rules.remove(t);
            }
            R = rules;
            rules = RemoveRules(R,Del);
            result.append(QString::number(k+1)+". Y"+QString::number(k)+"={"+y+"}, Y"+QString::number(k)+"==Y"+QString::number(k-1)+", i="+QString::number(k+1));
            break;
        }
        else
        {

            result.append(QString::number(k+1)+". Y"+QString::number(k)+"={"+y+"}, Y"+QString::number(k)+"!=Y"+QString::number(k-1)+", i="+QString::number(k+1));
            k++;
        }
    }
    result = result + res(rules);
    return rules;
}


QMap<QString,QStringList> GrammarConverter::RemoveUnattainableSymbols(QStringList &result)
{
    result.append("Этап 2. Удаление недостижимых символов.");
    QStringList V,temp;
    V.append(StartTerm);
    temp = V;
    QMap<QString,QStringList> R;
    int k = 0;
    result.append(QString::number(k+1)+". V"+QString::number(k)+"="+StartTerm+", i="+QString::number(k+1));
    k++;
    while(1)
    {

        QStringList oldV = V;
        QStringList appV;
        foreach(QString v, temp)
        {
            for(int i=0;i<rules.value(v).size();i++)
            {
                QString s = rules.value(v).at(i);
                for(int j=0;j<s.size();j++)
                {
                    if(NoTerm.contains(s.at(j))&&!V.contains(s.at(j)))
                    {
                        appV.append(s.at(j));
                    }
                }
            }
        }
        appV.removeDuplicates();
        V +=appV;
        QString y;
        foreach(QString s, V){
            y.append(s+",");
        }
        y.remove(y.size()-1,1);
        if(oldV == V)
        {
           // QStringList Del;
            for(auto r : rules.keys())
            {
                if(V.contains(r))
                {
                    R[r] = rules.value(r);
                }
            }
            rules = R;
            result.append(QString::number(k+1)+". V"+QString::number(k)+"={"+y+"}, V"+QString::number(k)+"==V"+QString::number(k-1)+", i="+QString::number(k+1));

            break;
        }
        else
        {
            foreach (QString s, V) {
                if(!oldV.contains(s)) temp.append(s);
            }
            result.append(QString::number(k+1)+". V"+QString::number(k)+"={"+y+"}, V"+QString::number(k)+"!=V"+QString::number(k-1)+", i="+QString::number(k+1));
            k++;
        }
    }
    result = result + res(rules);
    return rules;
}
QMap<QString,QStringList>  GrammarConverter::RemoveEmptyRules(QStringList &result)
{

    result.append("Этап 3. Удаление пустых правил.");
    QStringList W,Del;
    QMap<QString,QStringList> R = rules;
    QString str;
    for(auto r : R.keys())
    {
        if(R.value(r).contains("~"))
        {
            W.append(r);
            str.append(r+",");
            QStringList l = R.value(r);
            l.removeOne("~");
            if(l.isEmpty())
            {
               R.remove(r);
               Del.append(r);
            }else R[r] = l;
        }
    }
    str.remove(str.size()-1,1);
    int k = 0;
    result.append(QString::number(k+1)+". W"+QString::number(k)+"={"+str+"}, i="+QString::number(k+1));
    k++;
    while(1)
    {
        QStringList oldW = W;
        for(auto r : R.keys())
        {
            for(int i=0;i<R.value(r).size();i++)
            {
                QString s = R.value(r).at(i);
                bool f = true;
                for(int j=0;j<s.size();j++)
                {
                    if(!W.contains(s.at(j)))
                    {
                        f = false;
                        break;
                    }
                }
                if(f)
                {
                    W.append(r);
                    W.removeDuplicates();
                    break;
                }
            }
        }
        QString y;
        foreach(QString s,W){
            y.append(s+",");
        }
        y.remove(y.size()-1,1);
        if(oldW == W)
        {   
            result.append(QString::number(k+1)+". W"+QString::number(k)+"={"+y+"}, W"+QString::number(k)+"==W"+QString::number(k-1)+", i="+QString::number(k+1));
            break;
        } else
        {
            result.append(QString::number(k+1)+". W"+QString::number(k)+"={"+y+"}, W"+QString::number(k)+"!=W"+QString::number(k-1)+", i="+QString::number(k+1));
            k++;
        }
    }

    for(auto r : R.keys())
    {
        Sub.clear();
        QStringList list = R.value(r);
        foreach(QString s, R.value(r))
        {
            SubStrings(s,W);
            list = list + Sub;
            list.removeDuplicates();
        }
        list.removeOne(r);
        R[r] = list;
        result.append("из правил "+r+" Исключим все правила W получим");
        result.append(list);
    }
    if(W.contains(StartTerm))
    {
        QStringList l;
        l.append("~");
        l.append(StartTerm);
        result.append(StartTerm+" принадоежит W, добавим правила I->~|"+StartTerm);
        R["I"] = l;
        StartTerm = "I";
    }

    rules = R;
    while(1)
    {
        rules = R;
        for(auto r : R.keys())
        {
            QStringList l = R.value(r);
            if(l.isEmpty())
            {
               R.remove(r);
               Del.append(r);
            }
        }
        R = RemoveRules(R,Del);
        if(rules == R) break;
    }
    rules = R;
    result = result + res(rules);
    return R;
}
void GrammarConverter::SubStrings(QString str,QStringList W)
{
    int n = str.size();
    QString sub_str;
    for(int i=0;i<n;i++)
    {
        sub_str = str;
        if(sub_str!="")
        {
            if(W.contains(sub_str.at(i)))
            {
                sub_str.remove(i,1);
                if(sub_str!="")
                    Sub.append(sub_str);
                SubStrings(sub_str,W);
            }
        }
    }
}

QMap<QString,QStringList>  GrammarConverter::RemoveRules(QMap<QString,QStringList> R,QStringList Del)
{
    QMap<QString,QStringList> ru = R;
    for(auto r : ru.keys())
    {
        QStringList list =   R.value(r);
        qDebug()<<"list:"<<list;
            foreach (const QString &str, ru.value(r)) {
                for(int i=0;i<str.size();i++)
                {
                    QString c = str.at(i);
                    if(Del.contains(c))
                    {
                        list.removeOne(str);
                        break;
                    }
                }
        }
        R[r] = list;
    }
    return R;
}
QMap<QString,QStringList> GrammarConverter::RemoveLoopRules(QStringList &result)
{

    result.append("Этап 4. Удаление цепных правил.");
    QMap<QString,QStringList> R = rules;
    QMap<QString,QStringList> N;
    int k=1;
    for(auto r : R.keys())
    {
        QStringList list;
        list.append(r);
        int i=1;
        result.append(QString::number(k)+". N"+r+"={"+r+"}, i="+QString::number(i));
        i++; k++;
        for(auto n : rules.keys())
        {
            if(list.contains(n))
            {
                foreach (QString str, rules.value(n))
                {
                    if(NoTerm.contains(str))
                    {
                        list.append(str);
                        list.removeDuplicates();
                        QString l;
                        foreach (QString s, list) {
                            l.append(s+",");
                        }
                        l.remove(l.size()-1,1);
                        result.append(QString::number(k)+". N"+r+"={"+l+"}, i="+QString::number(i));
                        i++; k++;
                    }
                }
            }
        }
        list.removeDuplicates();
        list.removeOne(r);
        if(!list.isEmpty())
            N[r] = list;
    }
    QString l;
    for(auto n : N.keys())
    {
       QStringList list = rules.value(n);;
       foreach (QString str, N.value(n))
       {
           list = list + R.value(str);
           if(list.contains(str))
             list.removeOne(str);
       }
       rules[n] = list;
       l.append(n+",");
    }
    result.append("Имеем новые правила для "+l);
    result = result + res(rules);
    return rules;
}
QStringList GrammarConverter::res(QMap<QString,QStringList> R)
{
    QStringList result;
    result.append("Результат");
    QString nt;
    NoTerm.clear();
    for(auto r : R.keys())
    {
        NoTerm.append(r);
        nt.append(r+",");
    }
    nt.remove(nt.size()-1,1);
    result.append("G`({"+tr+"}, {"+nt+"}, "+StartTerm+", R`)");
    for(auto r : R.keys())
    {
        QString s;
        s.append(r+"->");
        foreach(QString str, R.value(r))
        {
            s.append(str+"|");
        }
        s.remove(s.size()-1,1);
        result.append(s);
    }
    result.append("\n");
    return result;
}

QMap<QString,QStringList> GrammarConverter::GetNewGram(QString &StartTerm,QStringList &NoTerm)
{
    StartTerm = this->StartTerm;
    NoTerm = this->NoTerm;
    return rules;
}

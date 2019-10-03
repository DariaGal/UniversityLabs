#include "checkstringdmpa.h"
#include <QDebug>
CheckStringDMPA::CheckStringDMPA(QMap<QString, QStringList> r,QString str,QString s,QStringList f,QStringList symbols,QString stackstart)
{
    rules = r;
    startState = s;
    finishState = f;
    checkString = str;
    Symbols = symbols;
    stack.append(stackstart);
}
QStringList CheckStringDMPA::Start()
{
    QString r,s;
    QString currentState = startState;
    QString sumbStack,sumbString;
    QString l;
    result.append("("+currentState+", "+checkString+", "+stack+", "+OutString+")");
    while(1)
    {
       if(stack.size()==0)
       {
           sumbStack="-";
       }
       else sumbStack=stack.at(0);
       if(checkString.size()==0)
       {
           sumbString="-";
       } else sumbString = checkString.at(0);
        if(!Symbols.contains(sumbString) && sumbString!="-")
        {
            l = "символ "+sumbString+" не пренадлежит алфавиту";
        }
       r = currentState+" "+sumbString+" "+sumbStack;

       if(rules.contains(r))
       {
            currentState = rules[r].at(0);
            s = rules[r].at(1);
            ChangeStack(s,sumbStack);
            if(rules[r].at(2)!="-")
                OutString+=rules[r].at(2);
            if(checkString.size()>0)
            {
                 checkString.remove(0,1);
            }
       }
       else
       {
           r = currentState+" "+"-"+" "+sumbStack;
           if(rules.contains(r))
           {
               currentState = rules[r].at(0);
               s = rules[r].at(1);
               if(rules[r].at(2)!="-")
                   OutString+=rules[r].at(2);
               ChangeStack(s,sumbStack);
           }
           else {result.append("не найдено подходяшее правило");result.append(l); break;}
       }

       result.append("("+currentState+", "+checkString+", "+stack+", "+OutString+")");
       if(checkString.isEmpty() && stack.isEmpty() && finishState.contains(currentState))
       {
           result.append("цепочка принадлежит языку");
           result.append("Выходная цепочка: "+OutString);
           break;
       }

    }

    return result;
}

void CheckStringDMPA::ChangeStack(QString s,QString sumbStack)
{
    int len = s.size();
    if(s.at(len-1)==sumbStack)
    {
        if(len>1)
        {
            s.remove(len-1,1);
            stack.insert(0,s);
        }
    } else{
        if(sumbStack!="-")
        {
            if(s == "-")
            {
                stack.remove(0,1);
            } else {
                        stack.remove(0,1);
                        stack.insert(0,s);
                    }
        }
    }
}

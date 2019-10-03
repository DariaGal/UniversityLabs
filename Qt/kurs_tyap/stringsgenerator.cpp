#include "stringsgenerator.h"
#include <QDebug>
StringsGenerator::StringsGenerator(QObject *parent) :
    QObject(parent)
{
}
void StringsGenerator::SetParemeters(QStringList t, QStringList n, QMap<QString,QStringList> r, QString s,int n1,int n2)
{
    VT=t;
    VN=n;
    Rules = r;
    StartT=s;
    fromN=n1;
    toN=n2;
    qDebug()<<VT<<" "<<VN;
    EmptyS = "~";

}
void StringsGenerator::Start(QStringList NotermsEmpty)
{
    bool foundN;
    Result.clear();
    StepBack=false;
    QStringList list;
    step Step;
    Step.currentString = StartT;
    list = Rules[StartT];
    Step.nextRule=list.at(0);
    list.removeAt(0);
    Step.alternativeRules=list;
    Generator.push(Step);
    step Step1;
    Step1 = Generator.top();
    qDebug()<<"\n CurStr: "<<Step1.currentString<<" NR: "<<Step1.nextRule<<" AlR: "<<Step1.alternativeRules;
    int k=0;
    while(1)
    {
    QString cS,nR;
    step StepOld,StepNew;
    StepOld = Generator.top();
    cS=StepOld.currentString;
    nR=StepOld.nextRule;
   // qDebug()<<"cS: "<<cS<<"nR: "<<nR;
    for(int i=0;i<cS.length();i++)
    {
      if(VN.contains(cS.at(i)))
      {
          if(nR==EmptyS)
          {
              nR="";
          }
          cS.replace(i,1,nR);
          for(int j=i;j<cS.length();j++)
          {
              if(VN.contains(cS.at(j)))
              {

                  StepNew.currentString=cS;
                  qDebug()<<"cS : "<<cS;
                  list = Rules[cS.at(j)];
                  StepNew.nextRule=list.at(0);
                  list.removeAt(0);
                  StepNew.alternativeRules=list;
                  Generator.push(StepNew);
                  foundN = true;
                  break;
              }
              i=j;
          }
      }
      if(foundN)
      {
          int len = CheckTermNumber(cS,NotermsEmpty);
          if(len>toN)
               {StepBack=true;
               Generator.pop();}
          break;
      }
    }
  /*  Step1 = Generator.top();
    qDebug()<<" CurStr: "<<Step1.currentString<<" NR: "<<Step1.nextRule<<" AlR: "<<Step1.alternativeRules<<"\n";*/
    if(!foundN)
    {
        StepBack=true;
        if(cS.length()>=fromN && cS.length()<=toN)
        {
            if(!Result.contains(cS))
            Result.append(cS);
        }
    }
    if(StepBack)
    {
         while(1)
        {
            if(!Generator.empty())
            {
            step S,S2;
           // Generator.pop();
            S=Generator.top();
            if(!S.alternativeRules.empty())
            {
                S2.currentString=S.currentString;
                S2.nextRule=S.alternativeRules.at(0);
                S.alternativeRules.removeAt(0);
                S2.alternativeRules=S.alternativeRules;
                Generator.pop();
                Generator.push(S2);
                StepBack = false;
                break;
            }
            else Generator.pop();
            }
            else return;
        }
    }

    k++;
    foundN=false;
    }

}

int StringsGenerator::CheckTermNumber(QString str,QStringList NotermsEmpty)
{
    int countT=0;
    for(int i=0;i<str.length();i++)
    {
        if(!NotermsEmpty.contains(str.at(i)))
        {
            countT++;
        }
    }
    return countT;
}
QStringList StringsGenerator::Print()
{
    return Result;
}

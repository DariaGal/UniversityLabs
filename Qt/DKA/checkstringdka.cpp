#include "checkstringdka.h"
#include <QDebug>
CheckStringDKA::CheckStringDKA()
{

}

void CheckStringDKA::SetParameters(QMap<QString,QStringList> tableDKA, QStringList States, QStringList Symbols, QString StartState, QStringList FinishState, QString CheckString)
{
    this->CheckString=CheckString;
    this->FinishState=FinishState;
    this->StartState=StartState;
    this->States=States;
    this->Symbols=Symbols;
    this->tableDKA=tableDKA;
   /* this->tableDKA = new QString *[States.size()+1];
    for (int i = 0; i < States.size()+1; i++)
        this->tableDKA[i] = new QString [Symbols.size()+1];

     for (int i = 0; i < States.size()+1; i++)
         for(int j = 0; j<Symbols.size()+1;j++)
             this->tableDKA[i][j]=tableDKA[i][j];*/
}
QStringList CheckStringDKA::Start()
{
    CurrentState = StartState;
    Result.append("("+CurrentState+",'"+CheckString+"')");
    int StrLen = CheckString.size();
    for(int i=0;i<StrLen;i++)
    {
        if(Symbols.contains(CheckString.at(0)))
        {
            int p = Symbols.indexOf(CheckString.at(0));
            QString str =tableDKA[CurrentState].at(p);
            if(str=="-"||str=="")
            {
                Result.append("Цепочка не принадлежит языку: из состояния "+CurrentState+" нет перехода по символу "+CheckString.at(0));
                return Result;
            }else{
                    CurrentState=str;
                 }

        }else {
                 Result.append("Цепочка не принадлежит языку: присутствуют посторонние символы");
                 return Result;
              }
        CheckString.remove(0,1);
        Result.append("("+CurrentState+",'"+CheckString+"')");
    }
    if(FinishState.contains(CurrentState))
    {
         Result.append("Цепочка принадлежит языку!");
    }
    else
    {
        Result.append("Цепочка не принадлежит языку: состояние "+CurrentState+" не является конечным");
    }
    return Result;
}

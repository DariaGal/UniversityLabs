#include "lab1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <map>
#include <math.h>

using namespace std;
long long ModExp(long long a,long long x, long long p)
{
    long long result = 1;
    long long s;
    s=a;
    while(x>0)
    {
        if(x&1)
        {
            result=result*s%p;
        }
    s=s*s%p;
    x>>=1;
    }
    return result;
};
void Euclid(long long a, long long b, long long &x, long long &y, long long &gcd)
{
    long long U[3] = {a,1,0};
    long long V[3] = {b,0,1};
    long q;
    while(V[0]!=0)
    {
        q = U[0]/V[0];
        long long T[3]={ U[0]%V[0], U[1]-q*V[1], U[2]-q*V[2] };
        memcpy(U,V,sizeof(V));
        memcpy(V,T,sizeof(T));
    }
    gcd=U[0];
    x=U[1];
    y=U[2];
};
long long Random()
{
    return rand()+rand();
};
long long GCD(long long a,long long b)
{
    long long r;
    while(b!=0)
    {
        r=a%b;
        a=b;
        b=r;
    }
    return a;
};
bool Ferma(long long x)
{
    for (int i = 0; i < 100; i++)
    {
        long long a = (rand() % (x - 2)) + 2;
        if (ModExp(a, x-1,x) != 1)
            return false;
    }
    return true;

};
long long GetSimple()
{
    long long r;
    while(1)
    {
        r=Random();
        if(Ferma(r)) return r;

    }

};
void DiffiHellman()
{
    long long q,p,g;
    long long Ya,Xa,Yb,Xb, Zab, Zba;

    while(1)
    {
        q=GetSimple();
        p=q*2+1;
        if(Ferma(p))
        {
            g = (rand() % (p - 2)) + 2;
            if(ModExp(g, q,p) != 1)
            {
                break;
            }

        }
    }
    printf("q=%lli, p=%lli, g=%lli\n",q,p,g);

    Xa=Random();
    Ya=ModExp(g,Xa,p);

    Xb=Random();
    Yb=ModExp(g,Xb,p);

    printf("Ya=%lli, Yb=%lli\n",Ya,Yb);

    Zab=ModExp(Yb,Xa,p); //A
    Zba=ModExp(Ya,Xb,p); //B

    if(Zab==Zba)
    printf("\nZab=Zba=%lli\n",Zab);

};

long long Step(long long a, long long p, long long y)
{
    long long m,k;
    int I,J;

    map <long long,int> babyStep;

    m=sqrt(p)+2;
    k=m;

    for(int j=0;j<m;j++)
    {
        long long t=pow(a,j);
        t=t*y%p;
        babyStep.insert (pair<long long,int>(t,j));
    }
/*	map<long long,int>::iterator it;
     for (it = babyStep.begin(); it != babyStep.end(); ++it)
  {
      printf("%lli %lli\n",it->first,it->second);
  }*/
    for(int i=1;i<=k;i++)
    {
        long long s=ModExp(a,i*m,p);
        map<long long,int>::iterator it = babyStep.find(s);
        if(it!=babyStep.end())
        {
            J=it->second;
            I=i;
            break;
        }
    }
    printf("\nI=%d, J=%d",I,J);

    return I*m-J;

};

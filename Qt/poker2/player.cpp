#include "player.h"
#include <stdlib.h>
#include <string.h>
#include <QDebug>
using namespace std;
Player::Player()
{

}

void Player::Init(long long p)
{
    this->p=p;
    GetCD(p-1,c,d);
}

long long Player::ModExp(long long a,long long x, long long p)
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
}
void Player::GetCD(long long p, long long &c, long long &d)
{
    while(1)
    {
        c = (rand() % (p - 2)) + 2;
        if(GCD(c, p)==1) break;
    }
    long long x,gcd;
    Euclid(p,c,x,d,gcd);
    if(d<0)
    {
        d=d+p;
    }
}
int * Player::CryptAndMix(int* k, int n)
{
    int *u = new int [n];

    for(int i=0;i<n;i++)
    {
        u[i]=ModExp(k[i],c,p);
    }
    for (int i=0; i<n; i++)
    {
        std::swap(u[i], u[rand() % n]);
    }
    return u;
}
long long Player::GCD(long long a,long long b)
{
    long long r;
    while(b!=0)
    {
        r=a%b;
        a=b;
        b=r;
    }
    return a;
}
void Player::SetKards(int k)
{
    kards.append(k);
}
void Player::SetKards(QList<int> k)
{
    kards.clear();
    kards = k;
}
QList<int> Player::GetKards()
{
    return kards;
}

QList<int> Player::EncryptKards(QList<int> k)
{
    QList<int> u;
    for(int i=0;i<k.size();i++)
    {
        u.append(ModExp(k.at(i),d,p));
    }
    return u;
}

void Player::Euclid(long long a, long long b, long long &x, long long &y, long long &gcd)
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
}

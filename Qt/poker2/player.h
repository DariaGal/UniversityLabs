#ifndef PLAYER_H
#define PLAYER_H
#include <QList>
class Player
{
public:
    Player();
    void Init(long long p);
    int* CryptAndMix(int* k,int n);
    void SetKards(int k);
    void SetKards(QList<int> k);
    QList<int> GetKards();
    QList<int> EncryptKards(QList<int> k);
    long long p;
private:
    void GetCD(long long p, long long &c, long long &d);
    long long GCD(long long a,long long b);
    void Euclid(long long a, long long b, long long &x, long long &y, long long &gcd);
    long long ModExp(long long a,long long x, long long p);
    long long c;
    long long d;
    QList<int> kards;
};

#endif // PLAYER_H

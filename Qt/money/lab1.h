
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <map>
#include <math.h>


long long ModExp(long long a,long long x, long long p);
void Euclid(long long a, long long b, long long &x, long long &y, long long &gcd);
long long Random();
long long GCD(long long a,long long b);
bool Ferma(long long x);
long long GetSimple();
void DiffiHellman();
long long Step(long long a, long long p, long long y);

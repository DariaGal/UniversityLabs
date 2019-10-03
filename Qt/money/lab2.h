
#include <stdio.h>
#include <stdlib.h>
#include "lab1.h"
#include <string>
using namespace std;

void GetCD(long long p, long long &c, long long &d);
void Shamir(int m);
void ElGamal_parameters(long long &p,long long &g, long long &c, long long &d);
string ElGamal_encryption(string filename,long long p, long long g, long long d);
void ElGamal_decryption(string encryptFilename,long long p, long long g, long long c);
void RSA_parameters(long long &N,long long &d, long long &c);
string RSA_encryption(string filename,long long N, long long d);
void RSA_decryption(string encryptFilename,long long N, long long c);
string Vernam_encryption(string filename);
void Vernam_decryption(string encryptFilename);

#include "lab2.h"

void GetCD(long long p, long long &c, long long &d)
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
};
void Shamir(int m)
{
    long long p,Ca,Da,Cb,Db;
    p=GetSimple();
    printf("p=%lli\n",p);
    GetCD(p-1,Ca,Da);
    printf("Ca=%lli  Da=%lli\n",Ca,Da);
    GetCD(p-1,Cb,Db);
    printf("Cb=%lli  Db=%lli\n",Cb,Db);
    long long x1 = ModExp(m,Ca,p);
    long long x2 = ModExp(x1,Cb,p);
    long long x3 = ModExp(x2,Da,p);
    long long x4 = ModExp(x3,Db,p);
    printf("m=%lli  x4=%lli\n",m,x4);
};

void ElGamal_parameters(long long &p,long long &g, long long &c, long long &d)
{
    bool find=false;
    while(1)
    {
        long long q=GetSimple();
        p=q*2+1;
        if(Ferma(p))
        {
            while(1)
            {
                g = (rand() % (p - 2)) + 2;
                if(ModExp(g, q,p) != 1)
                {
                    find=true;
                    break;
                }

            }

        }
        if(find) break;
    }
    c=(rand() % (p - 2)) + 2;
    d=ModExp(g,c,p);
};

string ElGamal_encryption(string filename,long long p, long long g, long long d)
{
    FILE * file = fopen(filename.c_str(), "rb");
    if (file == NULL) {perror ("can't open file");return 0;}
    string enfilename="encrypt_"+filename;
    FILE * encryptFile = fopen(enfilename.c_str(), "wb+");
    if (encryptFile == NULL) {perror ("can't open enfile");return 0;}
    while(1)
    {
      int c = fgetc(file);
      if(c!=EOF)
      {
        long long k=(rand() % (p - 2)) + 2;
        long r=ModExp(g,k,p);
        long e=ModExp(d,k,p)*c%p;
        fwrite(&r, sizeof(long), 1, encryptFile);
        fwrite(&e, sizeof(long), 1, encryptFile);
      }else break;
    }
    fclose (file);
    fclose (encryptFile);
    return enfilename;
};
void ElGamal_decryption(string encryptFilename,long long p, long long g, long long c)
{
    string decfilename=encryptFilename;
    int f = decfilename.find("encrypt");
    decfilename.replace(f, std::string("encrypt").length(), "decrypt");
    FILE * encryptFile = fopen(encryptFilename.c_str(), "rb");
    if (encryptFile != NULL) {
        FILE * file = fopen("newfile.txt", "wb");
        long e,r;
        while(1)
        {
            fread(&r, sizeof(long), 1, encryptFile);
            fread(&e, sizeof(long), 1, encryptFile);
            if(feof(encryptFile))break;

            long m=ModExp(r,p-1-c,p)*e%p;
            fputc(m,file);
        }

        fclose (file);
    }else perror ("can't open file");
        fclose (encryptFile);


};
void RSA_parameters(long long &N,long long &d, long long &c)
{
    long long P=GetSimple();
    long long Q=GetSimple();
    N=P*Q;
    long long f=(P-1)*(Q-1);
    GetCD(f,d,c);
}
string RSA_encryption(string filename,long long N, long long d)
{
    FILE * file = fopen(filename.c_str(), "rb");
    if (file == NULL) {perror ("can't open file");return 0;}
    string enfilename="encrypt_"+filename;
    FILE * encryptFile = fopen(enfilename.c_str(), "wb+");
    if (encryptFile == NULL) {perror ("can't open enfile");return 0;}
    while(1)
    {
      int m = fgetc(file);
      if(m!=EOF)
      {
        long e = ModExp(m,d,N);
        fwrite(&e, sizeof(long), 1, encryptFile);
      }else break;
    }
    fclose (file);
    fclose (encryptFile);
    return enfilename;
};
void RSA_decryption(string encryptFilename,long long N, long long c)
{
    string decfilename=encryptFilename;
    int f = decfilename.find("encrypt");
    decfilename.replace(f, std::string("encrypt").length(), "decrypt");
    FILE * encryptFile = fopen(encryptFilename.c_str(), "rb");
    if (encryptFile != NULL) {
        FILE * file = fopen(decfilename.c_str(), "wb");
        long e,r;
        while(1)
        {
            fread(&e, sizeof(long), 1, encryptFile);
            if(feof(encryptFile))break;
            long long m = ModExp(e,c,N);
            fputc(m,file);
        }

        fclose (file);
    }else perror ("can't open file");
        fclose (encryptFile);
};
string Vernam_encryption(string filename)
{
    string enfilename="encrypt_"+filename;
    FILE * file = fopen(filename.c_str(), "rb");
    if (file == NULL) {perror ("can't open file");return 0;}
    FILE * keyfile = fopen("keys.txt", "wb");
    if (keyfile == NULL) {perror ("can't open file");return 0;}
    FILE * encryptFile = fopen(enfilename.c_str(), "wb+");
    if (encryptFile == NULL) {perror ("can't open file");return 0;}
    while(1)
    {
     int c = fgetc(file);
      if(c!=EOF)
      {
        int k=rand()%255;
        int e=c^k;
        fputc(k,keyfile);
        fputc(e,encryptFile);
      }
     else break;
    }

    fclose (file);
    fclose (keyfile);
    fclose (encryptFile);
    return enfilename;
};
void Vernam_decryption(std::string encryptFilename)
{
    string decfilename=encryptFilename;
    int f = decfilename.find("encrypt");
    decfilename.replace(f, std::string("encrypt").length(), "decrypt");

    FILE * encryptFile = fopen(encryptFilename.c_str(), "rb");
    if (encryptFile != NULL) {

        FILE * keyfile = fopen("keys.txt", "rb");
        FILE * file = fopen(decfilename.c_str(), "wb");
        while(1)
        {
            int k = fgetc(keyfile);
            int	e = fgetc(encryptFile);
            if(feof(keyfile))break;
            int m=e^k;
            fputc(m,file);
        }
        fclose (file);
        fclose (keyfile);
    }
    fclose (encryptFile);
};

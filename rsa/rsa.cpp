#include "stdafx.h"
#include <cmath>
#include <ctime>
#include <IOSTREAM>
using namespace std;
int e, d, n;//全局变量
bool IsPrime(long prime)//是否素数
{
	for (int i=2;i<sqrt(prime);i++)
	{
		if(prime%i==0)
		{
			return false;
		}
	}
	return true;
}
void GeneratePrime(long* primeArr,int arrLen)//生成素数
{
	srand(time(NULL));
	int r,i;
	for (i=0;i<arrLen;i++)
	{
		while(true)
		{
			r=rand();
			if (IsPrime(r))
			{
				primeArr[i]=r;
				break;
			}
			else continue;
		}	
	}
}
//欧几里得扩展算法
int Exgcd(int m,int n,int &x)
{
    int x1,y1,x0,y0, y;
    x0=1; y0=0;
    x1=0; y1=1;
    x=0; y=1;
    int r=m%n;
    int q=(m-r)/n;
    while(r)
    {
        x=x0-q*x1; y=y0-q*y1;
        x0=x1; y0=y1;
        x1=x; y1=y;
        m=n; n=r; r=m%n;
        q=(m-r)/n;
    }
    return n;
}
void RSAEncrypt(char * plainText,long long * encryptText,int len)//RSA加密
{
	for (int i = 0; i<len; i++)
	{
		encryptText[i] = (long long)pow((int)plainText[i], e) % n;
	}
}
void RSADecrypt(long long * encryptText,char *plainText)
{
	for (int k = 0; k<(sizeof(encryptText) / sizeof(long long)); k++)//RSA解密
	{
		plainText[k] = (char)(pow(encryptText[k], d)) % n;
	}
}
int main(int argc, char* argv[])
{
	long primeArr[2]={0};
	GeneratePrime(primeArr,sizeof(primeArr)/sizeof(long));
	//用欧几里德扩展算法求e,d
	n=primeArr[0]*primeArr[1];
	int f=(primeArr[0]-1)*(primeArr[1]-1);
    for(int j = 3; j < f; j+=1331)
    {
        int gcd = Exgcd(j, f, d);
        if( gcd == 1 && d > 0)
        {
            e = j;
            break;
        }
    }
	char plainText[11]={0};
	long long* encryText=NULL;
	strcpy(plainText,"我的学号是：3150604027");
	cout << "明文：" << plainText << endl;
	cout << "p：" << primeArr[0] << endl;
	cout << "q：" << primeArr[1] << endl;
	cout << "n：" << n << endl;
	cout << "e：" << e << endl;
	cout << "d：" << d << endl;
	int len = strlen(plainText);
	encryText=new long long[len];
	RSAEncrypt(plainText, encryText, len);
	cout<<"密文：" << (char*)encryText<<endl;
	RSADecrypt(encryText, plainText);
	cout<<"解密为："<<plainText<<endl;
	system("pause");
	return 0;
}

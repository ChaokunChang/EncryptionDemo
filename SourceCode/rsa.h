#ifndef RSA_H
#define RSA_H

#include<iostream>
#include<gmp.h>
#include<gmpxx.h>
#include<time.h>
#include<ctime>

using namespace std;

class RSA{
private:
    mpz_class d; //私钥
    mpz_class p,q; //两个大质数
    mpz_class euclidean; //欧拉函数（n）
public:
    RSA();
    ~RSA();
    mpz_class n,e;
    gmp_randstate_t state;
    //void fast_powm(mpz_t result, const mpz_t base, const mpz_t exponent, const mpz_t n);
    int randomPrime(mpz_t rand, int len);
    void init(int len); //生成p,q,n,euclidean;
    //void getExponent(int len); //计算e,d
    int rsaEncrypt(mpz_t c,mpz_t m); //加密
    int rsaDecrypt(mpz_t m, mpz_t c); //解密
    int fast_rsaDecrypt(mpz_t m, mpz_t c);// 使用CRT进行快速解密
    int rsaSign(mpz_t sc, mpz_t s); //签名
    int rsaAuthenticate(mpz_t sa, mpz_t s); //签名认证
    mpz_class get_d(){return d;}
    //void done();
};
void fast_powm(mpz_t result, const mpz_t base, const mpz_t exponent, const mpz_t n);
#endif // RSA_H

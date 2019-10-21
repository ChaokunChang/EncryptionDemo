#ifndef DES8_H
#define DES8_H

#include<iostream>
#include<fstream>
#include<bitset>
#include<string>
#include<time.h>
#include<stdlib.h>

using namespace std;

class DES8{
    /*
    本程序 实现8轮DES加密算法，加密模式为CBC模式。
    */
    /*其他变量*/
    //bitset<64> initVec; //CBC模式的初始化向量

    public:
    DES8(){}
    bitset<32> f_func(const bitset<32> &R, const bitset<48> &K);//f函数
    //bitset<64> string2bitset(const char *s);

    /*子密钥生成*/
    bitset<28> shiftLeft(bitset<28> bits, int count);//左移函数
    void getSubKey(const bitset<64> &Key);//循环生成8个生成子密钥

    /*最终算法*/
    bitset<64> encrypt(const bitset<64> &plaintext); //加密算法
    bitset<64> decrypt(const bitset<64> &ciphertext); //解密算法

};

#endif

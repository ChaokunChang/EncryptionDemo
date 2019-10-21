#include<rsa.h>

using namespace std;

void fast_powm(mpz_t result, const mpz_t base, const mpz_t exponent, const mpz_t n){
    //char exp[128 + 10];
    string exp;
    mpz_class exponentc(exponent);
    mpz_class nc(n);
    mpz_class basec(base);
    exp = exponentc.get_str(2);
    mpz_class tmpresult,power;
    tmpresult = 1;
    power = basec%nc;
    for(int i=exp.size()-1;i>=0;i--){
        if(exp[i] == '1'){
            tmpresult *= power;
            tmpresult %= nc;
        }
        power *= power;
        power %= nc;
    }
    mpz_set(result, tmpresult.get_mpz_t());
}

RSA::RSA(){
    gmp_randinit_default(state);
    gmp_randseed_ui(state, time(NULL)); //设置随机化种子为当前时间
}
RSA::~RSA(){
    gmp_randclear(state);
}

int RSA::randomPrime(mpz_t rand, int len){
    int reps=15;
    do{
        mpz_t randt;
        mpz_init(randt);

        mpz_rrandomb(randt,state,len);
        int st = mpz_probab_prime_p(randt,reps);
        if(st == 1 || st ==2) {
            mpz_set(rand,randt);
            break;
        }
        mpz_clear(randt);
    }while(1);
    char *str=NULL;
    str = mpz_get_str(str,10,rand);
    //cout<<"random result:"<<str<<endl;
    cout.flush();
    return 1;
}

void RSA::init(int len){

    while(1){
        /*随机生成p,q*/
        randomPrime(p.get_mpz_t(),len);
        randomPrime(q.get_mpz_t(),len);
        mpz_class threholdL("100000000000000000000000000000000000000");
        mpz_class threholdD("100000000000");
        if(mpz_cmp(p.get_mpz_t(),threholdL.get_mpz_t())<0) continue;
        if(mpz_cmp(q.get_mpz_t(),threholdL.get_mpz_t())<0) continue;
        mpz_class difpq = p - q;
        mpz_t absdif;
        mpz_init(absdif);
        mpz_abs(absdif,difpq.get_mpz_t());
        if(mpz_cmp(absdif,threholdD.get_mpz_t())<0) continue;
        n = p*q;
        //gmp_printf("the p is %Zd \n the q is %Zd \n",p.get_mpz_t(),q.get_mpz_t());
        /*
        cout<<"p is:"<<p.get_str()<<endl;
        cout<<"q is:"<<q.get_str()<<endl;
        cout<<"Convert to binary is"<<endl;
        cout<<p.get_str(10)<<endl<<q.get_str(10)<<endl<<n.get_str(10)<<endl;
        cout<<p.get_str(2)<<endl<<q.get_str(2)<<endl<<n.get_str(2)<<endl;
        */
        euclidean = (p-1)*(q-1);
        //cout<<"euclidean is :"<<euclidean.get_str()<<endl;
        e = 65537;
        unsigned long one=1;
        mpz_class gcds;
        mpz_gcd(gcds.get_mpz_t(),e.get_mpz_t(),euclidean.get_mpz_t());
        if(mpz_cmp_ui(gcds.get_mpz_t(),one)!=0) continue;
        if(mpz_invert(d.get_mpz_t(),e.get_mpz_t(),euclidean.get_mpz_t())==0){
            cout<<"Error ed = 1!"<<endl;
            break;
        }
        else{
            break;
        }


        //getExponent(len);
    }
}

/*
void RSA::getExponent(int len){
    unsigned long one=1;
    do{
        randomPrime(e.get_mpz_t(),16);
        cout<<"e is:"<<e.get_str()<<endl;
        mpz_class gcds;
        mpz_gcd(gcds.get_mpz_t(),e.get_mpz_t(),euclidean.get_mpz_t());
        if(mpz_cmp_ui(gcds.get_mpz_t(),one)==0) break;
    }while(1);
    if(mpz_invert(d.get_mpz_t(),e.get_mpz_t(),euclidean.get_mpz_t())==0){
        cout<<"Error ed = 1!"<<endl;
    }
}*/

int RSA::rsaEncrypt(mpz_t c,mpz_t m){
    fast_powm(c,m,e.get_mpz_t(),n.get_mpz_t());
    return 1;
}

int RSA::fast_rsaDecrypt(mpz_t m, mpz_t c){
    mpz_class c0(c),m0;
    mpz_class c1,c2,d1,d2,m1,m2,y1,y2;
    //mpz_class M1,M2,M;//M=n,M1=q,M2=p;
    c1 = c0 % p;
    c2 = c0 % q;
    d1 = d % (p-1);
    d2 = d % (q-1);
    fast_powm(m1.get_mpz_t(),c1.get_mpz_t(),d1.get_mpz_t(),p.get_mpz_t());
    fast_powm(m2.get_mpz_t(),c2.get_mpz_t(),d2.get_mpz_t(),q.get_mpz_t());
    //M = p*q;
    //M1 = q;
    //M2 = p;
    mpz_invert(y1.get_mpz_t(),q.get_mpz_t(),p.get_mpz_t());
    mpz_invert(y2.get_mpz_t(),p.get_mpz_t(),q.get_mpz_t());
    m0 = (m1*q*y1 + m2*p*y2)%n;

    mpz_set(m,m0.get_mpz_t());

}

int RSA::rsaDecrypt(mpz_t m, mpz_t c){
    fast_powm(m,c,d.get_mpz_t(),n.get_mpz_t());
    return 1;
}

int RSA::rsaSign(mpz_t sc, mpz_t s){
    fast_powm(sc,s,d.get_mpz_t(),n.get_mpz_t());
    return 1;
}

int RSA::rsaAuthenticate(mpz_t sa, mpz_t s){
    fast_powm(sa,s,e.get_mpz_t(),n.get_mpz_t());
    return 1;
}
/*
void RSA::done(){
    mpz_clears(p,q,e,d,n,euclidean,NULL);
}*/

#include "des8ui.h"
#include "ui_des8ui.h"

DES8UI::DES8UI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DES8UI)
{
    ui->setupUi(this);
    ui->InputVec->setText("Serenade");
    filesize = 0;

    /*
    cout<<"Below is for test and debug!"<<endl;
    RSA rsa;
    rsa.init(130);
    cout<<"HHH"<<endl;
    gmp_printf("%s is an mpz %Zd %Zd \n", "here",(rsa.e).get_mpz_t(),(rsa.n).get_mpz_t());
    cout<<"SSS"<<endl;
    mpz_class m1(100),m2(21),m3(5),m4(3),m5,m6;
    m5 = m1*m2;
    cout<<m5.get_str()<<endl;
    m5 = (m1-1)*(m2-1);
    cout<<m5.get_str()<<endl;
    m5 = (m1%m3);
    cout<<m5.get_str()<<endl;
    mpz_powm(m5.get_mpz_t(),m3.get_mpz_t(),m4.get_mpz_t(),m2.get_mpz_t());
    fast_powm(m6.get_mpz_t(),m3.get_mpz_t(),m4.get_mpz_t(),m2.get_mpz_t());
    cout<<"Origin one:"<<m5.get_str()<<endl;
    cout<<"Fast one:"<<m6.get_str()<<endl;
    mpz_class tmpsrc;
    mpz_class tmp;
    mpz_class tmpdst,tmpdst2;
    tmpsrc = "12345678";
    cout<<"tmpsrc_class is:"<<tmpsrc.get_str(10)<<endl;
    //cout<<"String of it:"<<tmpsrc.get_str(2)<<endl;
    rsa.rsaEncrypt(tmp.get_mpz_t(),tmpsrc.get_mpz_t());
    rsa.rsaDecrypt(tmpdst.get_mpz_t(),tmp.get_mpz_t());
    rsa.fast_rsaDecrypt(tmpdst2.get_mpz_t(),tmp.get_mpz_t());
    cout<<"tmpdst_class is:"<<tmpdst.get_str(10)<<endl;
    //cout<<"String of it:"<<tmpdst.get_str(2)<<endl;
    cout<<"tmpdst2_class is:"<<tmpdst2.get_str(10)<<endl;
    //cout<<"String of it:"<<tmpdst2.get_str(2)<<endl;

    cout<<"Test mpz_powm()"<<endl;
    mpz_class a,b,c,d,n,r;
    a = "39"; //m
    c = "19"; //e=11
    n = "77"; //n=77
    d = "19";// d=11
    cout<<a.get_str(10)<<endl;
    mpz_powm(b.get_mpz_t(),a.get_mpz_t(),c.get_mpz_t(),n.get_mpz_t());
    cout<<b.get_str(10)<<endl;
    mpz_powm(r.get_mpz_t(),b.get_mpz_t(),d.get_mpz_t(),n.get_mpz_t());
    cout<<r.get_str(10)<<endl;
    cout<<"Test mpz_powm end."<<endl;
    cout<<"Test and debudg end!"<<endl;
    */
}

DES8UI::~DES8UI()
{
    delete ui;
}

std::bitset<64> DES8UI::string2bitset(string s){
    bitset<64> result;
    while(s.size()<8){
        s.push_back('x');
    }
    for(int i=0;i<8;i++) for(int j=0;j<8;j++) result[i*8 + j] = ( (s[i]>>j) & 0x01);
    return result;
}

std::bitset<64> getinitvec(string s){
    bitset<64> result;
    if(s.size()<8){
        result = getinitvec("Serenade");
        QMessageBox::warning(NULL,"Error","Init vector invalid!");
        return result;
    }
    for(int i=0;i<8;i++) for(int j=0;j<8;j++) result[i*8 + j] = ( (s[i]>>j) & 0x01);
    return result;
}

string DES8UI::bitset2string(std::bitset<64> b){
    string str;
    for(int i=0;i<8;i++){
        bitset<8> tmp;
        for(int j=0;j<8;j++){
            tmp[j] = b[i*8 + j];
        }
        unsigned int tmp2 = (unsigned int)(tmp.to_ulong());
        str.push_back((char)tmp2);
    }
    return str;
}
/*
void DES8UI::fast_powm(mpz_t result, const mpz_t base, const mpz_t exponent, const mpz_t n){
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
}*/

void DES8UI::loadFile(){
    string cfile = filename.toStdString();
    inputfile.open(cfile,ios::in|ios::binary);
    /*
    if(!inputfile.open(cfile,ios::in|ios::binary)){
        QMessageBox::warning(this,"Error","File not-found or illegal!");
    }*/
}

void DES8UI::saveFile(int s){
    string name;
    QString filepath;
    if(s==1){
        //加密过程
        name = "./encrypt_tmp.txt";
        filepath = QFileDialog::getSaveFileName(this,"Save Path",QString("./%1").arg("EResult.txt"));//"Text files (*.txt)"
    }
    else{
        //解密过程
        name = "./decrypt_tmp.txt";
        filepath = QFileDialog::getSaveFileName(this,"Save Path",QString("./%1").arg("DResult.txt"));//"Text files (*.txt)"
    }
    //QString filepath = QFileDialog::getSaveFileName(this,"Save Path",QString("./%1").arg("Result.txt"));//"Text files (*.txt)"
    if(filepath.isNull()){
        QMessageBox::warning(this,"Attention","You haven't selected a file path to save!");
        return;
    }
    outputfile.open(filepath.toStdString(),ios::out|ios::binary);

    fstream ftmp;
    ftmp.open(name,ios::in|ios::binary);

    char c;
    while(ftmp.read(&c,sizeof(char))){
        outputfile.write(&c,sizeof(char));
    }

    ftmp.close();
    outputfile.close();

}

void DES8UI::FileEncrypt(fstream &fin){
    ofstream fout("./encrypt_tmp.txt",ios::binary);

    DES8 des;

    bitset<64> key = string2bitset(SKey);
    des.getSubKey(key);

    bitset<64> plain,cipher;
    bitset<64> lastcode;
    lastcode.reset();
    if(!(ui->RandomGet->isChecked())) initVec = string2bitset(SVec);
    lastcode = des.encrypt(initVec);
    fout.write((char *)&lastcode,sizeof(lastcode));
    while( fin.read((char *)&plain, sizeof(plain)) ){
        cipher = des.encrypt(plain ^ lastcode);
        lastcode = cipher;
        fout.write((char *)&cipher, sizeof(cipher) );
        filesize++;
        plain.reset();
        /*
        string tmpstr = bitset2string(cipher);
        QString tmpqs = QString::fromStdString(tmpstr);
        ui->CipherTextArea->textCursor().insertText(tmpqs);
        */
        //string tmpstr = cipher.to_string();
        //QString tmpqs = QString::fromStdString(tmpstr);
        //ui->CipherTextArea->textCursor().insertText(tmpqs);

    }
    fin.close();
    fout.close();

}

void DES8UI::FileDecrypt(fstream &fin){
    ofstream fout("./decrypt_tmp.txt",ios::binary);

    DES8 des;
    //string s_key = "Serenade";//Romantic
    //bitset<64> key = string2bitset(s_key);

    bitset<64> key = string2bitset(SKey);
    des.getSubKey(key);

    bitset<64> plain,cipher;

    bitset<64> lastcode(0);
    fin.read((char *)&cipher, sizeof(cipher));
    lastcode = cipher;
    int count=0;
    while( fin.read((char *)&cipher, sizeof(cipher)) ){
        plain = des.decrypt(cipher) ^ lastcode;
        lastcode = cipher;
        //fout.write((char *)&plain, sizeof(plain) );
        //cipher.reset();

        //string tmpstr = bitset2string(plain);
        //QString tmpqs = QString::fromStdString(tmpstr);
        //ui->PlainTextArea->textCursor().insertText(tmpqs);
        if(count<filesize-1){
            fout.write((char *)&plain, sizeof(plain) );
            count++;
            cipher.reset();
        }
        else{
            string laststr = bitset2string(plain);
            int num = laststr[7]-'0';
            if(num>=8 || num<=0){
                cout<<"error num!"<<endl;
                break;
            }
            fout.write((char*)&plain,(8-num)*sizeof(char));
            //break;
        }
    }
    fin.close();
    fout.close();

}

void DES8UI::Refresh(){
    ui->ContentA->clear();
    ui->ContentB->clear();
    //ui->
}

void DES8UI::on_FileButton_clicked()
{
    QString filepath;
    filepath= QFileDialog::getOpenFileName(this,"myfile",".");
    if(filepath.isNull()) return;
    filename = filepath;
    ui->FilePath->setText(filename);
    Refresh();
}

bool DES8UI::Check(){
    if(SKey.empty()) {
        QMessageBox::warning(this,"Error","You must input a key first!");
        return false;
    }

    if(SKey.size() != 8 ){
        QMessageBox::warning(this,"Error","The key's size must be 8 Bytes!",QMessageBox::Yes,QMessageBox::Yes);
        return false;
    }

    if(!ui->RandomGet->isChecked()){
        if(SVec.empty()){
            QMessageBox::warning(this,"Error","You must input a init vector first!");
            return false;
        }
        if(SVec.size() != 8){
            QMessageBox::warning(this,"Error","The init _vector's size must be 8 Bytes!");
            return false;
        }
    }
    return true;

}

void DES8UI::on_EncryptButton_clicked()
{
    if(!Check()) return;
    loadFile();
    fstream tmpfile("./input.tmp",ios::binary | ios::trunc | ios::out);
    //tmpfile.open(ios::binary | ios::app);
    string text;
    char c;
    int count = 0;
    while(inputfile.read(&c,sizeof(char))){
        count ++;
        text.push_back(c);
        tmpfile.write(&c,sizeof(char));
    }
    ui->ContentA->append("Below is the input file's content:\n");
    ui->ContentA->append(QString::fromStdString(text));

    inputfile.close();

    //文件大小是否为8的倍数，如果不是，则在末尾加‘X’字符补全
    if(count%8 != 0){
        //string cfile = filename.toStdString();
        //inputfile.open(cfile,ios::binary | ios::app);
        char x = 'X';
        int num = (8- count%8);
        for(int i=0;i<num-1;i++){
            //inputfile.write(&x,sizeof(char));
            tmpfile.write(&x,sizeof(char));
        }
        char numc = '0'+num;
        //inputfile.write(&numc,sizeof(char));

        tmpfile.write(&numc,sizeof(char));
        //inputfile.close();
        tmpfile.close();
    }
    filename = "./input.tmp";
    loadFile();

    DWORD start_t,stop_t;
    start_t = GetTickCount();
    FileEncrypt(inputfile);
    stop_t = GetTickCount();
    int gap = int(stop_t - start_t);
    ui->lcdNumber->display(gap);

    QMessageBox::information(NULL, "Success", "Encryption completed!", QMessageBox::Yes, QMessageBox::Yes);
    QMessageBox::StandardButton qm = QMessageBox::question(this,"SAVE","Do you want to save the result?", QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
    if(qm == QMessageBox::Yes){
        saveFile(1);
        type = 1;
    }
}

void DES8UI::on_DecryptButton_clicked()
{
    QMessageBox::warning(this,"Error oprations!","Please use Client B as the reciever.",QMessageBox::Yes,QMessageBox::Yes);
    return;

    Check();

    loadFile();
    string text;
    char c;
    while(inputfile.get(c)){
        text.push_back(c);
    }
    ui->ContentB->append("Below is the input file's content:");
    ui->ContentB->append(QString::fromStdString(text));

    inputfile.close();
    loadFile();

    DWORD start_t,stop_t;
    start_t = GetTickCount();
    FileDecrypt(inputfile);
    stop_t = GetTickCount();
    int gap = int(stop_t - start_t);
    ui->lcdNumber_2->display(gap);

    QMessageBox::information(NULL, "Success", "Dncryption completed!", QMessageBox::Yes, QMessageBox::Yes);
    QMessageBox::StandardButton qm = QMessageBox::question(this,"SAVE","Do you want to save the result?", QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
    if(qm == QMessageBox::Yes){
        saveFile(0);
        type = 0;
    }

}


void DES8UI::on_InputKey_editingFinished()
{
    string tmps = ui->InputKey->text().toStdString();
    /*
    while(tmps.size() != 8){
        QMessageBox::warning(this,"Error","The key's size must be 8 Bytes!",QMessageBox::Yes,QMessageBox::Yes);
        return;
    }
    */
    SKey = tmps;
}


void DES8UI::on_InputVec_editingFinished()
{
    SVec = ui->InputVec->text().toStdString();
    initVec.reset();
    /*
    while(tmps.size() != 8){
        QMessageBox::warning(this,"Error","The init_vector's size must be 8 Bytes!",QMessageBox::Yes,QMessageBox::Yes);
        return;
    }
    */
    //initVec = getinitvec(tmps);
}

void DES8UI::on_SaveButton_clicked()
{
    saveFile(type);
}

void DES8UI::on_RandomGet_pressed()
{
    //ui->InputVec->clear();
    unsigned long r;
    for(int i=0;i<64;i++){
        r = rand()%2;
        initVec[i] = r;
    }
    ui->InputVec->setText("********");
    SVec.clear();
}

void DES8UI::on_ManualGet_pressed()
{
    ui->InputVec->clear();
}

void DES8UI::on_GenRSAKey_clicked()
{
    //string SKey;
    DWORD start_t,stop_t;
    start_t = GetTickCount();
    rsaA.init(128);
    stop_t = GetTickCount();
    int gap = int(stop_t - start_t);
    ui->lcdNumber->display(gap);

    QMessageBox::information(NULL, "Success", "RSA keys of Client A has generated!", QMessageBox::Yes, QMessageBox::Yes);
    //display and save;
    string str = rsaA.e.get_str(16);
    //string strn = rsaA.n.get_str(16);
    //cout<<"The public key of Client A is: "<<str<<endl;
    //cout<<"The choosen n of Client A is: "<<strn<<endl;

    ui->ContentA->append("The public key of Client A is: ");
    ui->ContentA->append(QString::fromStdString(str) );
    ui->ContentA->append("The choosen n of Client A is: ");
    ui->ContentA->append(QString::fromStdString(rsaA.n.get_str(16)));
    ui->ContentA->append("The private key of Client A is: ");
    ui->ContentA->append(QString::fromStdString(rsaA.get_d().get_str(16)));


    QFile rsa_pub("rsaA.public");
    QFile rsa_key("rsaA.private");
    if(rsa_pub.open(QIODevice::WriteOnly | QIODevice::Text) && rsa_key.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream out(&rsa_pub);
        QTextStream outp(&rsa_key);
        out<<QString::fromStdString(str)<<endl;
        outp<<QString::fromStdString(rsaA.get_d().get_str(16))<<endl;
    }
    rsa_pub.close();
    rsa_key.close();
}

void DES8UI::on_GenRSAKey_2_clicked()
{
    DWORD start_t,stop_t;
    start_t = GetTickCount();
    rsaB.init(128);
    stop_t = GetTickCount();
    int gap = int(stop_t - start_t);
    ui->lcdNumber_2->display(gap);
    QMessageBox::information(NULL, "Success", "RSA keys of Client B has generated!", QMessageBox::Yes, QMessageBox::Yes);
    //display and save
    string str = rsaB.e.get_str(16);
    //string strn = rsaB.n.get_str(16);
    //cout<<"The public key of Client B is: "<<str<<endl;
    //cout<<"The choosen n of Client B is: "<<strn<<endl;
    ui->ContentB->append("The public key of Client B is: ");
    ui->ContentB->append(QString::fromStdString(str));
    ui->ContentB->append("The choosen n of Client B is: ");
    ui->ContentB->append(QString::fromStdString(rsaB.n.get_str(16)));
    ui->ContentB->append("The private key of Client B is: ");
    ui->ContentB->append(QString::fromStdString(rsaB.get_d().get_str(16)));

    QFile rsa_pub("rsaB.public");
    QFile rsa_key("rsaB.private");
    if(rsa_pub.open(QIODevice::WriteOnly | QIODevice::Text) && rsa_key.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream out(&rsa_pub);
        QTextStream outp(&rsa_key);
        out<<QString::fromStdString(str);
        outp<<QString::fromStdString(rsaB.get_d().get_str(16));
    }
    rsa_pub.close();
    rsa_key.close();
}



void DES8UI::on_pushButton_clicked()
{
    Check();
    //传送密钥，需要选择ClientB的公钥作为参数使用RSA加密
    QString filepath;
    filepath= QFileDialog::getOpenFileName(this,"myfile",".");
    if(filepath.isNull()) return;

    QFile pubkeyf(filepath);
    if(!pubkeyf.open(QIODevice::ReadOnly | QIODevice::Text)){
        //cout<<"Error open file public key of B!"<<endl;
        QMessageBox::warning(this,"Error Files!","This file is invalid. Maybe a null file.",QMessageBox::Yes,QMessageBox::Yes);
    }
    QTextStream in(&pubkeyf);
    QString tskey = in.readLine();
    //cout<<"tskey is:"<<tskey.toStdString()<<endl;

    string bin_tskey = tskey.toStdString();
    string bin_SKey = string2bitset(SKey).to_string();
    mpz_class ekeyB(bin_tskey,16); //实际上ekeyB 应该等于rsaB.e
    //cout<<"ekeyB is"<<ekeyB.get_str(16)<<endl;
    mpz_class mpz_SKey(bin_SKey,2);
    //cout<<"mpz_SKey is"<<mpz_SKey.get_str(16)<<endl;

    if(mpz_cmp(ekeyB.get_mpz_t(),rsaB.e.get_mpz_t())!=0){
        QMessageBox::warning(this,"Error key!","The public key of Client B doesn't match, please check your file again.",QMessageBox::Yes,QMessageBox::Yes);
        //cout<<"Error for Debug! The public key of B is not correct!"<<endl;
        //cout<<ekeyB.get_str()<<endl;
        //cout<<rsaB.e.get_str()<<endl;
    }
    //mpz_powm(RsaSKey.get_mpz_t(),mpz_SKey.get_mpz_t(),ekeyB.get_mpz_t(),rsaB.n.get_mpz_t());
    rsaB.rsaEncrypt(RsaSKey.get_mpz_t(),mpz_SKey.get_mpz_t());
    QMessageBox::information(NULL, "Success", "The secret key of them has been send out from Client A!", QMessageBox::Yes, QMessageBox::Yes);
}

void DES8UI::on_pushButton_2_clicked()
{
    //根据传来的RsaSkey，转换成SKey2
    mpz_class m;
    //cout<<"m is:"<<m<<endl;
    //rsaB.rsaDecrypt(m.get_mpz_t(),RsaSKey.get_mpz_t());
    rsaB.fast_rsaDecrypt(m.get_mpz_t(),RsaSKey.get_mpz_t());
    bitset<64> b(m.get_str(2));
    //cout<<"bitset of m is: "<<b<<endl;
    //cout<<"bitset of SKey is"<<string2bitset(SKey)<<endl;
    SKey2 = bitset2string(b);

    if(SKey != SKey2 ){
        QMessageBox::warning(this,"Error Key!","RSA transfer errors. The secret key of DES doesn't match after transport. Please check your Keys",QMessageBox::Yes,QMessageBox::Yes);
        //cout<<"SKey is:"<<SKey<<endl;
        //cout<<"SKey2 is:"<<SKey2<<endl;
    }
    else{
        ui->InputKey2->setText(QString::fromStdString(SKey2));
        ui->InputVec_2->setText(QString::fromStdString(SVec));
    }
    QMessageBox::information(NULL, "Success", "The secret key of them has recieved by Client B!", QMessageBox::Yes, QMessageBox::Yes);

}

void DES8UI::on_EncryptButton_2_clicked()
{
    QMessageBox::warning(this,"Error operations!","Please use Client A as the sender.",QMessageBox::Yes,QMessageBox::Yes);
    return;
}

void DES8UI::on_DecryptButton_2_clicked()
{
    Check();
    Refresh();
    loadFile();
    string text;
    char c;
    while(inputfile.get(c)){
        text.push_back(c);
    }
    ui->ContentB->append("Below is the input file's content:");
    ui->ContentB->append(QString::fromStdString(text));

    inputfile.close();
    loadFile();

    DWORD start_t,stop_t;
    start_t = GetTickCount();
    FileDecrypt(inputfile);
    stop_t = GetTickCount();
    int gap = int(stop_t - start_t);
    ui->lcdNumber_2->display(gap);

    QMessageBox::information(NULL, "Success", "Dncryption completed!", QMessageBox::Yes, QMessageBox::Yes);
    QMessageBox::StandardButton qm = QMessageBox::question(this,"SAVE","Do you want to save the result?", QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
    if(qm == QMessageBox::Yes){
        saveFile(0);
        type = 0;
    }

}

void DES8UI::on_ContentA_destroyed()
{
    ui->ContentA->moveCursor(QTextCursor::End);
}

void DES8UI::on_ContentB_destroyed()
{
    ui->ContentB->moveCursor(QTextCursor::End);
}

void DES8UI::on_ALLOP_clicked()
{
    on_GenRSAKey_clicked();
    on_GenRSAKey_2_clicked();
    QMessageBox::information(NULL, "Next Operation:", "You will input secrect Key (and init vector is generated randomly).", QMessageBox::Yes, QMessageBox::Yes);
    /*while(1){
        QMessageBox::information(NULL, "Next Operation:", "Please input your secrect Key and init vector.", QMessageBox::Yes, QMessageBox::Yes);
        if(Check()) break;
    }*/
    on_RandomGet_pressed();
    SKey = "Security";
    ui->InputKey->setText("Security");
    bool ok = FALSE;
    QString text = QInputDialog::getText(this,tr( "SKey input" ),tr( "Please enter your secret key:" ),QLineEdit::Normal,"Security", &ok);
    if ( ok && !text.isEmpty() )
        SKey = text.toStdString();
    else {
        QMessageBox::warning(this,"You didn't enter Skey","Please press Button again.",QMessageBox::Yes,QMessageBox::Yes);
        return;
    }

    if(!Check()){
        QMessageBox::warning(this,"Error operations!","SKey or initvec invalid.",QMessageBox::Yes,QMessageBox::Yes);
    }
    QMessageBox::information(NULL, "Next Operation:", "Please Choose the file: rsaB.public.", QMessageBox::Yes, QMessageBox::Yes);
    on_pushButton_clicked();
    on_pushButton_2_clicked();

    QMessageBox::information(NULL, "Next Operation:", "Please Choose your input file.", QMessageBox::Yes, QMessageBox::Yes);
    on_FileButton_clicked();
    on_EncryptButton_clicked();
    QMessageBox::information(NULL, "Next Operation:", "Please Choose the result of encrption(your can choose encrypt_tmp.txt or EResult.txt).", QMessageBox::Yes, QMessageBox::Yes);
    on_FileButton_clicked();
    on_DecryptButton_2_clicked();
    QMessageBox::information(NULL, "End", "All operations done successfully!", QMessageBox::Yes, QMessageBox::Yes);
}

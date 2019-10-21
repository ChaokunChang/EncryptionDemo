#ifndef DES8UI_H
#define DES8UI_H

#include <QMainWindow>
#include <DES8.h>
#include <rsa.h>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFileDialog>
#include <windows.h>
#include <QInputDialog>

namespace Ui {
class DES8UI;
}

class DES8UI : public QMainWindow
{
    Q_OBJECT

public:
    explicit DES8UI(QWidget *parent = 0);
    ~DES8UI();
    std::bitset<64> string2bitset(string s);
    string bitset2string(std::bitset<64> b);


private slots:
    void on_FileButton_clicked();

    void on_EncryptButton_clicked();

    void on_DecryptButton_clicked();

    void on_InputKey_editingFinished();

    void on_InputVec_editingFinished();

    void on_SaveButton_clicked();

    void on_RandomGet_pressed();

    void on_ManualGet_pressed();

    void on_GenRSAKey_clicked();

    void on_GenRSAKey_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_EncryptButton_2_clicked();

    void on_DecryptButton_2_clicked();

    void on_ContentA_destroyed();

    void on_ContentB_destroyed();

    void on_ALLOP_clicked();

private:
    Ui::DES8UI *ui;
    std::bitset<64> initVec;
    QString filename;
    int filesize;
    fstream inputfile,outputfile;
    string SKey,SVec,SKey2;

    RSA rsaA,rsaB;
    mpz_class RsaSKey;
    int type=1;
    void loadFile();
    void saveFile(int s);
    void FileEncrypt(fstream &fin);
    void FileDecrypt(fstream &fin);
    void Refresh();
    bool Check();

};

#endif // DES8UI_H

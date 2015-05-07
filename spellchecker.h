#ifndef SPELLCHECKER_H_INCLUDED
#define SPELLCHECKER_H_INCLUDED
#include <iostream>
#include <stdlib.h>
#include <conio.h>
using namespace std;

struct dataKamus{
    string kamus;
    dataKamus* next_kamus;
};

struct treeSpell{
    char catalog;
    treeSpell *left;
    treeSpell *right;
    dataKamus* anak_tree;
};

treeSpell *akar=NULL; //untuk menampung kamus
dataKamus *rekomen=NULL; //untuk menampung data rekomendasi

bool status=false; //status digunakan untuk penanda update
const string username = "admin"; //constanta password dan username
const string password = "admin";
string tampungSem; //variabel menampung data temporary update


string makeTolower(string a); //mengebalikan string ke uppercase
bool cekloginadmin(string user,string pass); //singkronisasi login admin

bool masukKatalog(char key); //memasukkanKatalog (a-z
bool masukKatalog(char key,treeSpell *leaf);
void masukKanDataBase(); // memasukkan database
void grepKamus(string kamus); //menangkap pohon katalog
treeSpell *masukKamus(treeSpell *leaf,string kamus,int pil); // multi fungsi ,ada inseert update delete
treeSpell *grepKamus(treeSpell *leaf,char kat); //mengembalikan pohon katalog

void destroyTree(treeSpell *leaf); //untuk menghancurkan pohon katalog

dataKamus *inputkanKamus(string kamus,dataKamus *isianak); // untuk menambahkan kamus baru
dataKamus *makeNewData(string data); //buat data baru
dataKamus *deleteKamus(string kamus,dataKamus *isianak); //menghapus kamus
dataKamus *updateKamus(string kamus,dataKamus *isianak); // mengupdate kamus

void masukKannewKamus(string kamus);
void hapusKamus(string kamus);
void updatedataKamus(string kamus);
void DisplayDict();
void DisplayDict(treeSpell *leaf); //menampilkan secara inorder pohon , agar terurut
void DisplayRecom();
void DisplayRecomendation(dataKamus *isianak); //menampilkan rekomendasi yang sesuai jika tidak ada di kamus
void HapusRekomendation(); //menghapus rekomendasi data
void saveRecom(string kamus); // menyimpan rekomendasi data

dataKamus *saveRecomendation(string kamus,dataKamus *isianak);
dataKamus *deleteAllrekomen(dataKamus *isianak); //menghapus semua rekomendasi data

bool cekTree(string kamus,treeSpell *leaf); //melihat isi pohon
bool cekAnakTree(string kamus,dataKamus *isianak); //melihat anak isi pohon
bool cekAvailblekamus(string kamus);


#endif // SPELLCHECKER_H_INCLUDED

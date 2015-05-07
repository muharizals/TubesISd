#include "spellchecker.h"

/*
    fungsi ini kita gunakan untuk membuat string menjadi uppercase
*/
string makeTolower(string a)
{
   locale loc;
   for (string::size_type i=0; i<a.length(); ++i){
        a[i]=tolower(a[i],loc);
   }
   return a;
}

/*
mengecek login administrator , jika sesui maka akan mengembalikan nilai true,
jika tidak maka akan mengembalikan nilai false

*/
bool cekloginadmin(string user,string pass)
{
    if ( makeTolower(user) == username && makeTolower(pass) == password)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*
    memasukkan katalog pada pohon tree,
    menggunakan rekursif ,katalog berisi A-Z
*/
bool masukKatalog(char key,treeSpell *leaf)
{
    if (leaf->catalog == key)
    {
        return false;
    }
    else
        if ( key < leaf->catalog )
        {
            if (leaf->left == NULL)
            {
            leaf->left = new treeSpell;
            leaf->left->catalog = key;
            leaf->left->left = NULL;
            leaf->left->right = NULL;
            leaf->left->anak_tree = NULL;
            return true;
            }
            else
             masukKatalog(key,leaf->left);
        }
        else
        {
            if (leaf->right == NULL)
            {
            leaf->right = new treeSpell;
            leaf->right->catalog = key;
            leaf->right->left = NULL;
            leaf->right->right = NULL;
            leaf->right->anak_tree = NULL;
            return true;
            }
            else
                masukKatalog(key,leaf->right);
        }
}

bool masukKatalog(char key)
{
    if ( akar == NULL)
    {
        akar = new treeSpell;
        akar->catalog = key;
        akar->left = NULL;
        akar->right =NULL;
        akar->anak_tree = NULL;
        return true;
    }
    else
        masukKatalog(key,akar);
}

/*
    fungsi untuk membuat data baru
*/
dataKamus *makeNewData(string data)
{
    dataKamus *baru= new dataKamus;
    baru->kamus = data;
    baru->next_kamus = NULL;
    return baru;
}

/*
    menggunakan insert depan pada saat memasukkan data anak pohon kataloh
*/

dataKamus *inputkanKamus(string kamus,dataKamus *isianak)
{
    dataKamus *newData=makeNewData(kamus);
    if ( isianak==NULL )
    {
        newData->next_kamus=NULL;
    }
    else
    {
        newData->next_kamus=isianak;
    }
    return newData;
}

/*
    untuk menghapus kamus,kami gunakan rekursif
*/
dataKamus *deleteKamus(string kamus,dataKamus *isianak)
{
    if ( !isianak )
    {
        return NULL;
    }
    if ( kamus == isianak->kamus )
    {
        dataKamus *save=isianak->next_kamus;
        delete isianak;
        cout << "The Dictionary '"<<kamus<<"' have been removed .."<<endl;
        return save;
    }
    isianak->next_kamus=deleteKamus(kamus,isianak->next_kamus);
    return isianak;
}

/*
    untuk mengupdate kamus,kami gunakan rekursif
    algoritma untuk mengupdate kamus agar bisa terurut adalah
    dengan menaruh data temporary pada tampungan , kemudian kita hapus
    data yang tadi,kemudian kita masukan lagi data baru ,maka data akan terkelompok sesuai
    kelompoknya
*/

dataKamus *updateKamus(string kamus,dataKamus *isianak)
{
    if ( !isianak )
    {
        return NULL;
    }
    if ( kamus == isianak->kamus )
    {
        cout << "available : " << isianak->kamus <<endl;
        cout << "Enter new update : "; cin >>  tampungSem;
        if ( cekAvailblekamus(makeTolower(tampungSem)) )
        {
            cout << "The Dictionary Data already exists .."<<endl;
            status=false;
        }
        else
        {
            dataKamus* save = isianak->next_kamus;
            delete isianak;
            cout << "The Dictionary `"<<kamus<<"' have been update to be `" <<tampungSem<<"'.."<<endl;
            status=true;
            return save;
        }
        return isianak;
    }
    isianak->next_kamus=updateKamus(kamus,isianak->next_kamus);
    return isianak;
}

/*
    ini adalah fungsi untuk menyimpan rekomendasi jika
    yang di inputkan tidak ada yang cocok maka akan dikeluarkan
    sesui instonasi yang ada,agak mirip
*/
dataKamus *saveRecomendation(string kamus,dataKamus *isianak)
{
    if ( isianak==NULL)
    {
        return NULL;
    }
    if ( kamus[0]==isianak->kamus[0] && kamus[1]==isianak->kamus[1] && kamus[2]==isianak->kamus[2])
    {
        rekomen=inputkanKamus(isianak->kamus,rekomen);
    }
    isianak->next_kamus=saveRecomendation(kamus,isianak->next_kamus);
    return isianak;
}

/*
    ini adalah multi fungsi ,dimana saya bisa menambhakan data baru, menghapus data , mengupdate data , dan
    menampung data rekomendasi .
*/
treeSpell *masukKamus(treeSpell *leaf,string kamus,int pil)
{
    if(leaf!=NULL)
    {
        if(kamus[0]==leaf->catalog)
        {
            switch(pil)
            {
                case 1 :leaf->anak_tree=inputkanKamus(kamus,leaf->anak_tree);break; //input data
                case 2 :leaf->anak_tree=deleteKamus(kamus,leaf->anak_tree);break; // deelete data
                case 3 :leaf->anak_tree=updateKamus(kamus,leaf->anak_tree);break; // update data
                case 4 :leaf->anak_tree=saveRecomendation(kamus,leaf->anak_tree);break; //menyimpan rekomendasi
            }
            return leaf;
        }
        if(kamus[0] < leaf->catalog)
        {
            leaf->left=masukKamus(leaf->left,kamus,pil);
            return leaf;
        }
        else
            leaf->right=masukKamus(leaf->right,kamus,pil);
            return leaf;
    }
    else
        return NULL;
}

/*
    adalah fungsi untuk menangkap katalog,
    dimana jika user hanya menginputkan satu karater saja maka
    akan ditampikan katalog dengan kamusnya juga
*/

treeSpell *grepKamus(treeSpell *leaf,char kat)
{
    if(leaf!=NULL)
    {
        if(kat==leaf->catalog)
        {
            return leaf;
        }
        if(kat < leaf->catalog)
        {
            return grepKamus(leaf->left,kat);
        }
        else
            return grepKamus(leaf->right,kat);
    }
    else return NULL;
}

/*
    fungsi ini digunakan untuk menghapus pohon
    tree kita,destroy,i like it
    jika anak dari tree yang kita gunakan ternyata memiliki data
    maka kita harus menhapusnya dengan fungsi delete all
*/
void destroyTree(treeSpell *leaf)
{
    if(leaf!=NULL)
    {
        destroyTree(leaf->left);
        destroyTree(leaf->right);
        if ( leaf->anak_tree!=NULL )
        {
            leaf->anak_tree=deleteAllrekomen(leaf->anak_tree);
        }
        delete leaf;
    }
}

/*
    pada fungsi ini digunakan untuk menangkap , menampilkan,dan mendestroy tree
    jika si user memasukkan satu karakter saja
*/

void grepKamus(string kamus)
{
    treeSpell *grepkamus;
    grepkamus=NULL;
    grepkamus=grepKamus(akar,kamus[0]);
    if (grepkamus!=NULL)
    {
        cout << "|- " << grepkamus->catalog << " -|"<<endl;
        dataKamus *cur=grepkamus->anak_tree;
        while (cur!=NULL)
        {
           cout << cur->kamus << "   ";
           cur = cur->next_kamus;
        }

        grepkamus=NULL;
    }

}

/*
menyimpan rekomendasi
*/
void saveRecom(string kamus)
{
    akar=masukKamus(akar,kamus,4);
}

/*
    memaasukkan kamus baru;
*/

void masukKannewKamus(string kamus)
{
    akar=masukKamus(akar,kamus,1);
}

/*
    menghapus kamus
*/
void hapusKamus(string kamus)
{
    akar=masukKamus(akar,kamus,2);
}
/*
    mengupadte kamus
*/
void updatedataKamus(string kamus)
{
    akar=masukKamus(akar,kamus,3);
}

/*
    menampikan data secara inorder agar terurut;
*/

void DisplayDict(treeSpell *leaf)
{
    if ( leaf!=NULL )
    {
            DisplayDict(leaf->left);
            cout <<"\n\n\n|- "<<leaf->catalog<<" -|"  <<endl;
            dataKamus *cur=leaf->anak_tree;
            while ( cur!=NULL )
            {
                cout << "\t" << cur->kamus << " ";
                cur = cur->next_kamus;
            }
            DisplayDict(leaf->right);

    }
}
 // menampikan data
void DisplayDict()
{
    if ( akar==NULL )
    {
        cout << "No dictionary found"<<endl;
    }
    else
        DisplayDict(akar);
}

// cek data tree
bool cekAvailblekamus(string kamus)
{
    return cekTree(kamus,akar);
}
//cek anaknya
bool cekAnakTree(string kamus,dataKamus *isianak)
{
    if ( !isianak )
    {
        return false;
    }
    if ( kamus == isianak->kamus )
    {
        return true;
    }
    return cekAnakTree(kamus,isianak->next_kamus);
}

//cek pohon tree
bool cekTree(string kamus,treeSpell *leaf)
{
    if(leaf!=NULL)
    {
        if(kamus[0]==leaf->catalog)
        {
            return cekAnakTree(kamus,leaf->anak_tree);
        }
        if(kamus[0]<leaf->catalog)
        {
            return cekTree(kamus,leaf->left);
        }
        else
            return cekTree(kamus,leaf->right);
    }
    else
        return false;
}

//menmapikan rekomendari data
void DisplayRecomendation(dataKamus *isianak)
{
    dataKamus *cur=isianak;
    cout << "\n\t\t\t|-----Recomendation-----|"<<endl;
    while ( cur!=NULL)
    {
        cout << cur->kamus << " ";
        cur=cur->next_kamus;
    }
}

void DisplayRecom()
{
    if (rekomen==NULL)
    {
        cout << "no recommendation is right for the verb"<<endl;
    }
    else{
        DisplayRecomendation(rekomen);
    }
}

/*
    menghapus semua data pada anaknya,
    pada hapus ini gunakan rekursif agar lebih oke
*/
dataKamus *deleteAllrekomen(dataKamus *isianak)
{
    if ( isianak!=NULL )
    {
        dataKamus *save=isianak->next_kamus;
        delete isianak;
        return save;
    }
    isianak->next_kamus=deleteAllrekomen(isianak->next_kamus);
    return isianak;
}

void HapusRekomendation()
{
    if( rekomen==NULL)
    {

    }
    else
        rekomen=deleteAllrekomen(rekomen);
        rekomen=NULL;
}

/*
    nah,disini adalah tempah kita untu mengisi database kamus kita.
*/
void masukKanDataBase()
{
    //ini untuk memasukkan katalog (a-z) pada pohon katalog

    string masuk = "ngcbaiedfkjhlmtqopsrxwyuzv";
   for (string::size_type i=0; i<masuk.length(); ++i){
       masukKatalog(masuk[i]);
   }
    //dan ini adalah fungsi unutk memasukkan kamusnya pada anaka tree yang kita miliki
    //catalogue A
    akar = masukKamus(akar,"abide",1);akar = masukKamus(akar,"accelerate",1);
    akar = masukKamus(akar,"accept",1);akar = masukKamus(akar,"accomplish",1);
    akar = masukKamus(akar,"achieve",1);akar = masukKamus(akar,"acquire",1);
    akar = masukKamus(akar,"acted",1);akar = masukKamus(akar,"activate",1);
    akar = masukKamus(akar,"adapte",1);akar = masukKamus(akar,"add ",1);
    akar = masukKamus(akar,"address",1);akar = masukKamus(akar,"administer",1);
    akar = masukKamus(akar,"admire",1);akar = masukKamus(akar,"advise",1);
    akar = masukKamus(akar,"afford",1);akar = masukKamus(akar,"agree",1);
    akar = masukKamus(akar,"alert ",1);akar = masukKamus(akar,"alight",1);
    akar = masukKamus(akar,"allow",1);akar = masukKamus(akar,"altered",1);
    akar = masukKamus(akar,"amuse",1);akar = masukKamus(akar,"analyze",1);
    akar = masukKamus(akar,"announce",1);akar = masukKamus(akar,"annoy",1);
    akar = masukKamus(akar,"answer",1);akar = masukKamus(akar,"anticipate",1);
    akar = masukKamus(akar,"apologize",1);akar = masukKamus(akar,"appear",1);
    akar = masukKamus(akar,"applaud",1);akar = masukKamus(akar,"applied",1);
    akar = masukKamus(akar,"appoint",1);akar = masukKamus(akar,"appraise",1);
    akar = masukKamus(akar,"appreciate",1);akar = masukKamus(akar,"approve",1);
    akar = masukKamus(akar,"arbitrate",1);akar = masukKamus(akar,"argue",1);
    akar = masukKamus(akar,"arise",1);akar = masukKamus(akar,"arrange",1);
    akar = masukKamus(akar,"arrest",1);akar = masukKamus(akar,"arrive",1);
    akar = masukKamus(akar,"ascertain",1);akar = masukKamus(akar,"ask",1);
    akar = masukKamus(akar,"assemble",1);akar = masukKamus(akar,"assess",1);
    akar = masukKamus(akar,"assist",1);akar = masukKamus(akar,"assure",1);
    akar = masukKamus(akar,"attach",1);akar = masukKamus(akar,"attack",1);
    akar = masukKamus(akar,"attain ",1);akar = masukKamus(akar,"attempt",1);
    akar = masukKamus(akar,"attend",1);akar = masukKamus(akar,"attract",1);
    akar = masukKamus(akar,"audited",1);akar = masukKamus(akar,"avoid",1);
    akar = masukKamus(akar,"awake",1);

    //catalogue B
    akar = masukKamus(akar,"back",1);akar = masukKamus(akar,"bake",1);
    akar = masukKamus(akar,"balance",1);akar = masukKamus(akar,"ban",1);
    akar = masukKamus(akar,"bang",1);akar = masukKamus(akar,"bare",1);
    akar = masukKamus(akar,"bat",1);akar = masukKamus(akar,"bathe",1);
    akar = masukKamus(akar,"battle",1);akar = masukKamus(akar,"be ",1);
    akar = masukKamus(akar,"beam",1);akar = masukKamus(akar,"bear",1);
    akar = masukKamus(akar,"beat",1);akar = masukKamus(akar,"become",1);
    akar = masukKamus(akar,"beg",1);akar = masukKamus(akar,"begin",1);
    akar = masukKamus(akar,"behave",1);akar = masukKamus(akar,"behold",1);
    akar = masukKamus(akar,"belong",1);akar = masukKamus(akar,"bend",1);
    akar = masukKamus(akar,"beset",1);akar = masukKamus(akar,"bet",1);
    akar = masukKamus(akar,"bid",1);akar = masukKamus(akar,"bind",1);
    akar = masukKamus(akar,"bite",1);akar = masukKamus(akar,"bleach",1);
    akar = masukKamus(akar,"bleed",1);akar = masukKamus(akar,"bless",1);
    akar = masukKamus(akar,"blind",1);akar = masukKamus(akar,"blink",1);
    akar = masukKamus(akar,"blot",1);akar = masukKamus(akar,"blow",1);
    akar = masukKamus(akar,"blush",1);akar = masukKamus(akar,"boast",1);
    akar = masukKamus(akar,"boil",1);akar = masukKamus(akar,"bolt",1);
    akar = masukKamus(akar,"bomb",1);akar = masukKamus(akar,"book",1);
    akar = masukKamus(akar,"bore",1);akar = masukKamus(akar,"borrow",1);
    akar = masukKamus(akar,"bounce",1);akar = masukKamus(akar,"bow",1);
    akar = masukKamus(akar,"box",1);akar = masukKamus(akar,"brake",1);
    akar = masukKamus(akar,"branch",1);akar = masukKamus(akar,"break",1);
    akar = masukKamus(akar,"breathe",1);akar = masukKamus(akar,"breed",1);
    akar = masukKamus(akar,"brief",1);akar = masukKamus(akar,"bring",1);
    akar = masukKamus(akar,"broadcast",1);akar = masukKamus(akar,"bruise",1);
    akar = masukKamus(akar,"brush",1);akar = masukKamus(akar,"bubble",1);
    akar = masukKamus(akar,"budget",1);akar = masukKamus(akar,"build",1);
    akar = masukKamus(akar,"bump",1);akar = masukKamus(akar,"burn",1);
    akar = masukKamus(akar,"burst",1);akar = masukKamus(akar,"bury",1);
    akar = masukKamus(akar,"bust",1);akar = masukKamus(akar,"buy",1);
    akar = masukKamus(akar,"buzz",1);

    //Catalogue C , D ,E , F

    akar = masukKamus(akar,"calculate",1);akar = masukKamus(akar,"call",1);
    akar = masukKamus(akar,"camp",1);akar = masukKamus(akar,"chop",1);
    akar = masukKamus(akar,"care",1);akar = masukKamus(akar,"clean",1);
    akar = masukKamus(akar,"carry",1);akar = masukKamus(akar,"clarify",1);
    akar = masukKamus(akar,"carve",1);akar = masukKamus(akar,"clear",1);
    akar = masukKamus(akar,"catch",1);akar = masukKamus(akar,"close",1);
    akar = masukKamus(akar,"cast",1);akar = masukKamus(akar,"clothe",1);
    akar = masukKamus(akar,"catalog",1);akar = masukKamus(akar,"coach",1);
    akar = masukKamus(akar,"cause",1);akar = masukKamus(akar,"coil",1);
    akar = masukKamus(akar,"challenge",1);akar = masukKamus(akar,"collect",1);
    akar = masukKamus(akar,"change",1);akar = masukKamus(akar,"color",1);
    akar = masukKamus(akar,"charge",1);akar = masukKamus(akar,"come",1);
    akar = masukKamus(akar,"chart",1);akar = masukKamus(akar,"command",1);
    akar = masukKamus(akar,"chase",1);akar = masukKamus(akar,"compare",1);
    akar = masukKamus(akar,"cheat",1);akar = masukKamus(akar,"compete",1);
    akar = masukKamus(akar,"check",1);akar = masukKamus(akar,"complain",1);
    akar = masukKamus(akar,"cheer",1);akar = masukKamus(akar,"complate",1);
    akar = masukKamus(akar,"choose",1);akar = masukKamus(akar,"compile",1);
    akar = masukKamus(akar,"conceive",1);akar = masukKamus(akar,"continue",1);
    akar = masukKamus(akar,"conclude",1);akar = masukKamus(akar,"control",1);
    akar = masukKamus(akar,"connect",1);akar = masukKamus(akar,"convert",1);
    akar = masukKamus(akar,"confuse",1);akar = masukKamus(akar,"coordinate",1);
    akar = masukKamus(akar,"consider",1);akar = masukKamus(akar,"copy",1);
    akar = masukKamus(akar,"cost",1);akar = masukKamus(akar,"dam",1);
    akar = masukKamus(akar,"count",1);akar = masukKamus(akar,"damage",1);
    akar = masukKamus(akar,"cover",1);akar = masukKamus(akar,"dance",1);
    akar = masukKamus(akar,"crack",1);akar = masukKamus(akar,"dare",1);
    akar = masukKamus(akar,"crash",1);akar = masukKamus(akar,"deal",1);
    akar = masukKamus(akar,"create",1);akar = masukKamus(akar,"decay",1);
    akar = masukKamus(akar,"cross",1);akar = masukKamus(akar,"deceive",1);
    akar = masukKamus(akar,"crush",1);akar = masukKamus(akar,"decide",1);
    akar = masukKamus(akar,"cry",1);akar = masukKamus(akar,"decorate",1);
    akar = masukKamus(akar,"cure",1);akar = masukKamus(akar,"delegate",1);
    akar = masukKamus(akar,"curve",1);akar = masukKamus(akar,"delight",1);
    akar = masukKamus(akar,"cut",1);akar = masukKamus(akar,"deliver",1);
    akar = masukKamus(akar,"design",1);akar = masukKamus(akar,"depend",1);
    akar = masukKamus(akar,"destroy",1);akar = masukKamus(akar,"divert",1);
    akar = masukKamus(akar,"detail",1);akar = masukKamus(akar,"divide",1);
    akar = masukKamus(akar,"detect",1);akar = masukKamus(akar,"do",1);
    akar = masukKamus(akar,"develop",1);akar = masukKamus(akar,"double",1);
    akar = masukKamus(akar,"devise",1);akar = masukKamus(akar,"doubt",1);
    akar = masukKamus(akar,"diagnose",1);akar = masukKamus(akar,"draf",1);
    akar = masukKamus(akar,"dig",1);akar = masukKamus(akar,"drag",1);
    akar = masukKamus(akar,"disagree",1);akar = masukKamus(akar,"drain",1);
    akar = masukKamus(akar,"disappear",1);akar = masukKamus(akar,"dramatize",1);
    akar = masukKamus(akar,"discover",1);akar = masukKamus(akar,"draw",1);
    akar = masukKamus(akar,"dislike",1);akar = masukKamus(akar,"dream",1);
    akar = masukKamus(akar,"dispense",1);akar = masukKamus(akar,"dress",1);
    akar = masukKamus(akar,"display",1);akar = masukKamus(akar,"drink",1);
    akar = masukKamus(akar,"distribute",1);akar = masukKamus(akar,"drive",1);
    akar = masukKamus(akar,"drown",1);akar = masukKamus(akar,"drop",1);
    akar = masukKamus(akar,"dry",1);akar = masukKamus(akar,"earn",1);
    akar = masukKamus(akar,"eat",1);akar = masukKamus(akar,"enter",1);
    akar = masukKamus(akar,"edited",1);akar = masukKamus(akar,"entertain",1);
    akar = masukKamus(akar,"educate",1);akar = masukKamus(akar,"escape",1);
    akar = masukKamus(akar,"eliminate",1);akar = masukKamus(akar,"establish",1);
    akar = masukKamus(akar,"embarrass",1);akar = masukKamus(akar,"estimate",1);
    akar = masukKamus(akar,"employ",1);akar = masukKamus(akar,"evaluate",1);
    akar = masukKamus(akar,"empty",1);akar = masukKamus(akar,"exceed",1);
    akar = masukKamus(akar,"enacted",1);akar = masukKamus(akar,"excite",1);
    akar = masukKamus(akar,"end",1);akar = masukKamus(akar,"execute",1);
    akar = masukKamus(akar,"endure",1);akar = masukKamus(akar,"exhibit",1);
    akar = masukKamus(akar,"enforce",1);akar = masukKamus(akar,"exist",1);
    akar = masukKamus(akar,"engineer",1);akar = masukKamus(akar,"expect",1);
    akar = masukKamus(akar,"enhance",1);akar = masukKamus(akar,"expedite",1);
    akar = masukKamus(akar,"enjoy",1);akar = masukKamus(akar,"experiment",1);
    akar = masukKamus(akar,"enlist",1);akar = masukKamus(akar,"explain",1);
    akar = masukKamus(akar,"ensure",1);akar = masukKamus(akar,"explode",1);
    akar = masukKamus(akar,"extend",1);akar = masukKamus(akar,"extract",1);
    akar = masukKamus(akar,"face",1);akar = masukKamus(akar,"flee",1);
    akar = masukKamus(akar,"facilitate",1);akar = masukKamus(akar,"fling",1);
    akar = masukKamus(akar,"fade",1);akar = masukKamus(akar,"float",1);
    akar = masukKamus(akar,"fail",1);akar = masukKamus(akar,"flood",1);
    akar = masukKamus(akar,"fancy",1);akar = masukKamus(akar,"flower",1);
    akar = masukKamus(akar,"fear",1);akar = masukKamus(akar,"fly",1);
    akar = masukKamus(akar,"feed",1);akar = masukKamus(akar,"follow",1);
    akar = masukKamus(akar,"feel",1);akar = masukKamus(akar,"fool",1);
    akar = masukKamus(akar,"fance",1);akar = masukKamus(akar,"forbid",1);
    akar = masukKamus(akar,"fetch",1);akar = masukKamus(akar,"force",1);
    akar = masukKamus(akar,"fight",1);akar = masukKamus(akar,"forget",1);
    akar = masukKamus(akar,"file",1);akar = masukKamus(akar,"forgive",1);
    akar = masukKamus(akar,"fill",1);akar = masukKamus(akar,"form",1);
    akar = masukKamus(akar,"film",1);akar = masukKamus(akar,"formulate",1);
    akar = masukKamus(akar,"finalize",1);akar = masukKamus(akar,"forsake",1);
    akar = masukKamus(akar,"finance",1);akar = masukKamus(akar,"frame",1);
    akar = masukKamus(akar,"find",1);akar = masukKamus(akar,"freeze",1);
    akar = masukKamus(akar,"fire",1);akar = masukKamus(akar,"frighten",1);
    akar = masukKamus(akar,"fit",1);akar = masukKamus(akar,"fry",1);
    akar = masukKamus(akar,"fix",1);akar = masukKamus(akar,"flap",1);


    //Catalogue G
    akar = masukKamus(akar,"gather",1);akar = masukKamus(akar,"gaze",1);
    akar = masukKamus(akar,"generate",1);akar = masukKamus(akar,"get",1);
    akar = masukKamus(akar,"give",1);akar = masukKamus(akar,"glow",1);
    akar = masukKamus(akar,"glue",1);akar = masukKamus(akar,"go",1);
    akar = masukKamus(akar,"govern",1);akar = masukKamus(akar,"grab",1);
    akar = masukKamus(akar,"graduate",1);akar = masukKamus(akar,"grate",1);
    akar = masukKamus(akar,"grease",1);akar = masukKamus(akar,"greet",1);
    akar = masukKamus(akar,"grin",1);akar = masukKamus(akar,"grind",1);
    akar = masukKamus(akar,"grip",1);akar = masukKamus(akar,"groan",1);
    akar = masukKamus(akar,"grow",1);akar = masukKamus(akar,"guarantee",1);
    akar = masukKamus(akar,"guard",1);akar = masukKamus(akar,"guess",1);
    akar = masukKamus(akar,"guide",1);

    //Catalogue H
    akar = masukKamus(akar,"hammer",1);akar = masukKamus(akar,"hand",1);
    akar = masukKamus(akar,"handle",1);akar = masukKamus(akar,"handwrite",1);
    akar = masukKamus(akar,"hang",1);akar = masukKamus(akar,"happen",1);
    akar = masukKamus(akar,"harass",1);akar = masukKamus(akar,"harm",1);
    akar = masukKamus(akar,"hate",1);akar = masukKamus(akar,"haunt",1);
    akar = masukKamus(akar,"head",1);akar = masukKamus(akar,"heal",1);
    akar = masukKamus(akar,"heap",1);akar = masukKamus(akar,"hear",1);
    akar = masukKamus(akar,"heat",1);akar = masukKamus(akar,"help",1);
    akar = masukKamus(akar,"hide",1);akar = masukKamus(akar,"hit",1);
    akar = masukKamus(akar,"hold",1);akar = masukKamus(akar,"hook",1);
    akar = masukKamus(akar,"hop",1);akar = masukKamus(akar,"hope",1);
    akar = masukKamus(akar,"hover",1);akar = masukKamus(akar,"hug",1);
    akar = masukKamus(akar,"hum",1);akar = masukKamus(akar,"hunt",1);
    akar = masukKamus(akar,"hurry",1);akar = masukKamus(akar,"hurt",1);
    akar = masukKamus(akar,"hypothesize",1);

    //Catalogue i
    akar = masukKamus(akar,"identify",1);
    akar = masukKamus(akar,"ignore",1);akar = masukKamus(akar,"illustrate",1);
    akar = masukKamus(akar,"imagine",1);akar = masukKamus(akar,"implement",1);
    akar = masukKamus(akar,"impress",1);akar = masukKamus(akar,"improve",1);
    akar = masukKamus(akar,"improvise",1);akar = masukKamus(akar,"include",1);
    akar = masukKamus(akar,"increase",1);akar = masukKamus(akar,"induce",1);
    akar = masukKamus(akar,"influence",1);akar = masukKamus(akar,"inform",1);
    akar = masukKamus(akar,"initiate",1);akar = masukKamus(akar,"inject",1);
    akar = masukKamus(akar,"injure",1);akar = masukKamus(akar,"inlay",1);
    akar = masukKamus(akar,"innovate",1);akar = masukKamus(akar,"input",1);
    akar = masukKamus(akar,"inspect",1);akar = masukKamus(akar,"inspire",1);
    akar = masukKamus(akar,"install",1);akar = masukKamus(akar,"institute",1);
    akar = masukKamus(akar,"instruct",1);akar = masukKamus(akar,"insure",1);
    akar = masukKamus(akar,"integrate",1);akar = masukKamus(akar,"intend",1);
    akar = masukKamus(akar,"intensify",1);akar = masukKamus(akar,"interest",1);
    akar = masukKamus(akar,"interfere",1);akar = masukKamus(akar,"interlay",1);
    akar = masukKamus(akar,"interrupt",1);akar = masukKamus(akar,"interview",1);
    akar = masukKamus(akar,"introduce",1);akar = masukKamus(akar,"invent",1);
    akar = masukKamus(akar,"inventory",1);akar = masukKamus(akar,"investigate",1);
    akar = masukKamus(akar,"invite",1);akar = masukKamus(akar,"irritate",1);
    akar = masukKamus(akar,"itch",1);akar = masukKamus(akar,"inspire",1);

    //Catalogue J
    akar = masukKamus(akar,"jail",1);akar = masukKamus(akar,"jog",1);
    akar = masukKamus(akar,"join",1);akar = masukKamus(akar,"joke",1);
    akar = masukKamus(akar,"judge",1);akar = masukKamus(akar,"juggle",1);
    akar = masukKamus(akar,"jump",1);akar = masukKamus(akar,"justify",1);

    //K,L,M,N,O

    akar = masukKamus(akar,"keep",1);akar = masukKamus(akar,"kneel",1);
    akar = masukKamus(akar,"kept",1);akar = masukKamus(akar,"knit",1);
    akar = masukKamus(akar,"kick",1);akar = masukKamus(akar,"knock",1);
    akar = masukKamus(akar,"kill",1);akar = masukKamus(akar,"knot",1);
    akar = masukKamus(akar,"kiss",1);akar = masukKamus(akar,"know",1);
    akar = masukKamus(akar,"label",1);akar = masukKamus(akar,"lie",1);
    akar = masukKamus(akar,"land",1);akar = masukKamus(akar,"lifted",1);
    akar = masukKamus(akar,"laugh",1);akar = masukKamus(akar,"light",1);
    akar = masukKamus(akar,"launch",1);akar = masukKamus(akar,"lighten",1);
    akar = masukKamus(akar,"lay",1);akar = masukKamus(akar,"like",1);
    akar = masukKamus(akar,"lead",1);akar = masukKamus(akar,"list",1);
    akar = masukKamus(akar,"lean",1);akar = masukKamus(akar,"listen",1);
    akar = masukKamus(akar,"leap",1);akar = masukKamus(akar,"live",1);
    akar = masukKamus(akar,"learn",1);akar = masukKamus(akar,"load",1);
    akar = masukKamus(akar,"leave",1);akar = masukKamus(akar,"locate",1);
    akar = masukKamus(akar,"lecture",1);akar = masukKamus(akar,"lock",1);
    akar = masukKamus(akar,"led",1);akar = masukKamus(akar,"log",1);
    akar = masukKamus(akar,"lend",1);akar = masukKamus(akar,"long",1);
    akar = masukKamus(akar,"let",1);akar = masukKamus(akar,"look",1);
    akar = masukKamus(akar,"level",1);akar = masukKamus(akar,"lose",1);
    akar = masukKamus(akar,"license",1);akar = masukKamus(akar,"love",1);
    akar = masukKamus(akar,"lick",1);akar = masukKamus(akar,"maintain",1);
    akar = masukKamus(akar,"make",1);akar = masukKamus(akar,"model",1);
    akar = masukKamus(akar,"manage",1);akar = masukKamus(akar,"modify",1);
    akar = masukKamus(akar,"manipulate",1);akar = masukKamus(akar,"monitor",1);
    akar = masukKamus(akar,"manufacture",1);akar = masukKamus(akar,"motivate",1);
    akar = masukKamus(akar,"map",1);akar = masukKamus(akar,"mourn",1);
    akar = masukKamus(akar,"march",1);akar = masukKamus(akar,"move",1);
    akar = masukKamus(akar,"mark",1);akar = masukKamus(akar,"mow",1);
    akar = masukKamus(akar,"market",1);akar = masukKamus(akar,"muddle",1);
    akar = masukKamus(akar,"marry",1);akar = masukKamus(akar,"mug",1);
    akar = masukKamus(akar,"match",1);akar = masukKamus(akar,"multiply",1);
    akar = masukKamus(akar,"mate",1);akar = masukKamus(akar,"murder",1);
    akar = masukKamus(akar,"matter",1);akar = masukKamus(akar,"nail",1);
    akar = masukKamus(akar,"mean",1);akar = masukKamus(akar,"name",1);
    akar = masukKamus(akar,"measure",1);akar = masukKamus(akar,"navigate",1);
    akar = masukKamus(akar,"meddle",1);akar = masukKamus(akar,"need",1);
    akar = masukKamus(akar,"mediate",1);akar = masukKamus(akar,"negotiate",1);
    akar = masukKamus(akar,"meet",1);akar = masukKamus(akar,"nest",1);
    akar = masukKamus(akar,"melt",1);akar = masukKamus(akar,"nod",1);
    akar = masukKamus(akar,"memorize",1);akar = masukKamus(akar,"nominate",1);
    akar = masukKamus(akar,"mend",1);akar = masukKamus(akar,"normalize",1);
    akar = masukKamus(akar,"mentor",1);akar = masukKamus(akar,"note",1);
    akar = masukKamus(akar,"milk",1);akar = masukKamus(akar,"notice",1);
    akar = masukKamus(akar,"mine",1);akar = masukKamus(akar,"number",1);
    akar = masukKamus(akar,"mislead",1);akar = masukKamus(akar,"obey",1);
    akar = masukKamus(akar,"miss",1);akar = masukKamus(akar,"object",1);
    akar = masukKamus(akar,"mix",1);akar = masukKamus(akar,"observe",1);
    akar = masukKamus(akar,"moan",1);akar = masukKamus(akar,"obtain",1);
    akar = masukKamus(akar,"occur",1);akar = masukKamus(akar,"originate",1);
    akar = masukKamus(akar,"offend",1);akar = masukKamus(akar,"overcome",1);
    akar = masukKamus(akar,"offer",1);akar = masukKamus(akar,"overdo",1);
    akar = masukKamus(akar,"officiate",1);akar = masukKamus(akar,"overdraw",1);
    akar = masukKamus(akar,"open",1);akar = masukKamus(akar,"overflow",1);
    akar = masukKamus(akar,"operate",1);akar = masukKamus(akar,"overhear",1);
    akar = masukKamus(akar,"order",1);akar = masukKamus(akar,"overtake",1);
    akar = masukKamus(akar,"organize",1);akar = masukKamus(akar,"owe",1);
    akar = masukKamus(akar,"oriented",1);akar = masukKamus(akar,"own",1);


    //catalogue P,Q,R,S
    akar = masukKamus(akar,"paint",1);akar = masukKamus(akar,"pour",1);
    akar = masukKamus(akar,"park",1);akar = masukKamus(akar,"pratice",1);
    akar = masukKamus(akar,"part",1);akar = masukKamus(akar,"praised",1);
    akar = masukKamus(akar,"participate",1);akar = masukKamus(akar,"pray",1);
    akar = masukKamus(akar,"pass",1);akar = masukKamus(akar,"preach",1);
    akar = masukKamus(akar,"paste",1);akar = masukKamus(akar,"prepare",1);
    akar = masukKamus(akar,"pay",1);akar = masukKamus(akar,"present",1);
    akar = masukKamus(akar,"peep",1);akar = masukKamus(akar,"preserve",1);
    akar = masukKamus(akar,"peel",1);akar = masukKamus(akar,"preset",1);
    akar = masukKamus(akar,"perceive",1);akar = masukKamus(akar,"preside",1);
    akar = masukKamus(akar,"perfect",1);akar = masukKamus(akar,"press",1);
    akar = masukKamus(akar,"perfrom",1);akar = masukKamus(akar,"prevent",1);
    akar = masukKamus(akar,"permit",1);akar = masukKamus(akar,"print",1);
    akar = masukKamus(akar,"phone",1);akar = masukKamus(akar,"process",1);
    akar = masukKamus(akar,"photograph",1);akar = masukKamus(akar,"produce",1);
    akar = masukKamus(akar,"pilot",1);akar = masukKamus(akar,"program",1);
    akar = masukKamus(akar,"pine",1);akar = masukKamus(akar,"progress",1);
    akar = masukKamus(akar,"place",1);akar = masukKamus(akar,"project",1);
    akar = masukKamus(akar,"plan",1);akar = masukKamus(akar,"promise",1);
    akar = masukKamus(akar,"play",1);akar = masukKamus(akar,"protect",1);
    akar = masukKamus(akar,"plant",1);akar = masukKamus(akar,"propose",1);
    akar = masukKamus(akar,"plug",1);akar = masukKamus(akar,"provide",1);
    akar = masukKamus(akar,"point",1);akar = masukKamus(akar,"pull",1);
    akar = masukKamus(akar,"possess",1);akar = masukKamus(akar,"pump",1);
    akar = masukKamus(akar,"post",1);akar = masukKamus(akar,"punch",1);
    akar = masukKamus(akar,"push",1);akar = masukKamus(akar,"put",1);
    akar = masukKamus(akar,"qualify",1);akar = masukKamus(akar,"question",1);
    akar = masukKamus(akar,"queue",1);akar = masukKamus(akar,"question",1);
    akar = masukKamus(akar,"quit",1);akar = masukKamus(akar,"race",1);
    akar = masukKamus(akar,"radiate",1);akar = masukKamus(akar,"rain",1);
    akar = masukKamus(akar,"raise",1);akar = masukKamus(akar,"reach",1);
    akar = masukKamus(akar,"rank",1);akar = masukKamus(akar,"read",1);
    akar = masukKamus(akar,"rate",1);akar = masukKamus(akar,"realign",1);
    akar = masukKamus(akar,"realize",1);akar = masukKamus(akar,"reason",1);
    akar = masukKamus(akar,"receive",1);akar = masukKamus(akar,"recognize",1);
    akar = masukKamus(akar,"recommend",1);akar = masukKamus(akar,"revisi",1);
    akar = masukKamus(akar,"reconcile",1);akar = masukKamus(akar,"rhyme",1);
    akar = masukKamus(akar,"record",1);akar = masukKamus(akar,"rid",1);
    akar = masukKamus(akar,"recruit",1);akar = masukKamus(akar,"ride",1);
    akar = masukKamus(akar,"reduce",1);akar = masukKamus(akar,"ring",1);
    akar = masukKamus(akar,"refer",1);akar = masukKamus(akar,"rise",1);
    akar = masukKamus(akar,"reflect",1);akar = masukKamus(akar,"risk",1);
    akar = masukKamus(akar,"refuse",1);akar = masukKamus(akar,"rob",1);
    akar = masukKamus(akar,"regulate",1);akar = masukKamus(akar,"rock",1);
    akar = masukKamus(akar,"rehabilitate",1);akar = masukKamus(akar,"roll",1);
    akar = masukKamus(akar,"reign",1);akar = masukKamus(akar,"rot",1);
    akar = masukKamus(akar,"reinforce",1);akar = masukKamus(akar,"rub",1);
    akar = masukKamus(akar,"reject",1);akar = masukKamus(akar,"rule",1);
    akar = masukKamus(akar,"rejoice",1);akar = masukKamus(akar,"run",1);
    akar = masukKamus(akar,"relate",1);akar = masukKamus(akar,"rush",1);
    akar = masukKamus(akar,"relax",1);akar = masukKamus(akar,"sack",1);
    akar = masukKamus(akar,"release",1);akar = masukKamus(akar,"sail",1);
    akar = masukKamus(akar,"rely",1);akar = masukKamus(akar,"satisfy",1);
    akar = masukKamus(akar,"remember",1);akar = masukKamus(akar,"save",1);
    akar = masukKamus(akar,"remind",1);akar = masukKamus(akar,"saw",1);
    akar = masukKamus(akar,"remove",1);akar = masukKamus(akar,"say",1);
    akar = masukKamus(akar,"render",1);akar = masukKamus(akar,"scare",1);
    akar = masukKamus(akar,"repair",1);akar = masukKamus(akar,"scatter",1);
    akar = masukKamus(akar,"repeat",1);akar = masukKamus(akar,"schedule",1);
    akar = masukKamus(akar,"replace",1);akar = masukKamus(akar,"scold",1);
    akar = masukKamus(akar,"reply",1);akar = masukKamus(akar,"scorch",1);
    akar = masukKamus(akar,"report",1);akar = masukKamus(akar,"scrape",1);
    akar = masukKamus(akar,"represent",1);akar = masukKamus(akar,"scratch",1);
    akar = masukKamus(akar,"reproduce",1);akar = masukKamus(akar,"scream",1);
    akar = masukKamus(akar,"request",1);akar = masukKamus(akar,"screw",1);
    akar = masukKamus(akar,"research",1);akar = masukKamus(akar,"scribble",1);
    akar = masukKamus(akar,"resolve",1);akar = masukKamus(akar,"scrub",1);
    akar = masukKamus(akar,"respond",1);akar = masukKamus(akar,"seal",1);
    akar = masukKamus(akar,"restored",1);akar = masukKamus(akar,"search",1);
    akar = masukKamus(akar,"return",1);akar = masukKamus(akar,"secure",1);
    akar = masukKamus(akar,"review",1);akar = masukKamus(akar,"see",1);
    akar = masukKamus(akar,"seek",1);akar = masukKamus(akar,"shed",1);
    akar = masukKamus(akar,"select",1);akar = masukKamus(akar,"shelter",1);
    akar = masukKamus(akar,"sell",1);akar = masukKamus(akar,"shine",1);
    akar = masukKamus(akar,"send",1);akar = masukKamus(akar,"shiver",1);
    akar = masukKamus(akar,"sense",1);akar = masukKamus(akar,"shock",1);
    akar = masukKamus(akar,"separate",1);akar = masukKamus(akar,"shoe",1);
    akar = masukKamus(akar,"serve",1);akar = masukKamus(akar,"shoot",1);
    akar = masukKamus(akar,"service",1);akar = masukKamus(akar,"shop",1);
    akar = masukKamus(akar,"set",1);akar = masukKamus(akar,"show",1);
    akar = masukKamus(akar,"settle",1);akar = masukKamus(akar,"shrink",1);
    akar = masukKamus(akar,"sew",1);akar = masukKamus(akar,"shut",1);
    akar = masukKamus(akar,"shade",1);akar = masukKamus(akar,"sigh",1);
    akar = masukKamus(akar,"shake",1);akar = masukKamus(akar,"sign",1);
    akar = masukKamus(akar,"shape",1);akar = masukKamus(akar,"signal",1);
    akar = masukKamus(akar,"share",1);akar = masukKamus(akar,"simplify",1);
    akar = masukKamus(akar,"shear",1);akar = masukKamus(akar,"sin",1);
    akar = masukKamus(akar,"sink",1);akar = masukKamus(akar,"sing",1);
    akar = masukKamus(akar,"sip",1);akar = masukKamus(akar,"sleep",1);
    akar = masukKamus(akar,"sit",1);akar = masukKamus(akar,"slide",1);
    akar = masukKamus(akar,"sketch",1);akar = masukKamus(akar,"slink",1);
    akar = masukKamus(akar,"ski",1);akar = masukKamus(akar,"slip",1);
    akar = masukKamus(akar,"skip",1);akar = masukKamus(akar,"slit",1);
    akar = masukKamus(akar,"slap",1);akar = masukKamus(akar,"slow",1);
    akar = masukKamus(akar,"slay",1);akar = masukKamus(akar,"smash",1);
    akar = masukKamus(akar,"smell",1);akar = masukKamus(akar,"snow",1);
    akar = masukKamus(akar,"smile",1);akar = masukKamus(akar,"soak",1);
    akar = masukKamus(akar,"smite",1);akar = masukKamus(akar,"solve",1);
    akar = masukKamus(akar,"smoke",1);akar = masukKamus(akar,"soothe",1);
    akar = masukKamus(akar,"snatch",1);akar = masukKamus(akar,"soothsay",1);
    akar = masukKamus(akar,"sneak",1);akar = masukKamus(akar,"sort",1);
    akar = masukKamus(akar,"sneeze",1);akar = masukKamus(akar,"sound",1);
    akar = masukKamus(akar,"sniff",1);akar = masukKamus(akar,"sow",1);
    akar = masukKamus(akar,"snore",1);akar = masukKamus(akar,"spare",1);
    akar = masukKamus(akar,"sparkle",1);akar = masukKamus(akar,"spin",1);
    akar = masukKamus(akar,"speak",1);akar = masukKamus(akar,"spit",1);
    akar = masukKamus(akar,"specify",1);akar = masukKamus(akar,"split",1);
    akar = masukKamus(akar,"speed",1);akar = masukKamus(akar,"spoil",1);
    akar = masukKamus(akar,"spell",1);akar = masukKamus(akar,"spot",1);
    akar = masukKamus(akar,"spend",1);akar = masukKamus(akar,"spray",1);
    akar = masukKamus(akar,"spill",1);akar = masukKamus(akar,"spread",1);
    akar = masukKamus(akar,"spring",1);akar = masukKamus(akar,"stand",1);
    akar = masukKamus(akar,"sprout",1);akar = masukKamus(akar,"stare",1);
    akar = masukKamus(akar,"squash",1);akar = masukKamus(akar,"start",1);
    akar = masukKamus(akar,"squeal",1);akar = masukKamus(akar,"stay",1);
    akar = masukKamus(akar,"squeeze",1);akar = masukKamus(akar,"steal",1);
    akar = masukKamus(akar,"stain",1);akar = masukKamus(akar,"steer",1);
    akar = masukKamus(akar,"stamp",1);akar = masukKamus(akar,"step",1);
    akar = masukKamus(akar,"stick",1);akar = masukKamus(akar,"stretch",1);
    akar = masukKamus(akar,"stimulate",1);akar = masukKamus(akar,"stride",1);
    akar = masukKamus(akar,"sting",1);akar = masukKamus(akar,"strike",1);
    akar = masukKamus(akar,"stink",1);akar = masukKamus(akar,"string",1);
    akar = masukKamus(akar,"stir",1);akar = masukKamus(akar,"strip",1);
    akar = masukKamus(akar,"stitch",1);akar = masukKamus(akar,"strive",1);
    akar = masukKamus(akar,"stop",1);akar = masukKamus(akar,"stroke",1);
    akar = masukKamus(akar,"store",1);akar = masukKamus(akar,"structure",1);
    akar = masukKamus(akar,"strap",1);akar = masukKamus(akar,"study",1);
    akar = masukKamus(akar,"strengthen",1);akar = masukKamus(akar,"stuff",1);
    akar = masukKamus(akar,"subtract",1);akar = masukKamus(akar,"sweat",1);
    akar = masukKamus(akar,"succeed",1);akar = masukKamus(akar,"sweep",1);
    akar = masukKamus(akar,"suck",1);akar = masukKamus(akar,"swell",1);
    akar = masukKamus(akar,"suffer",1);akar = masukKamus(akar,"swim",1);
    akar = masukKamus(akar,"suggest",1);akar = masukKamus(akar,"switch",1);
    akar = masukKamus(akar,"suit",1);akar = masukKamus(akar,"symbolize",1);
    akar = masukKamus(akar,"summarize",1);akar = masukKamus(akar,"synthesize",1);
    akar = masukKamus(akar,"supervise",1);akar = masukKamus(akar,"systemize",1);
    akar = masukKamus(akar,"supply",1);akar = masukKamus(akar,"support",1);
    akar = masukKamus(akar,"suppose",1);akar = masukKamus(akar,"surprise",1);
    akar = masukKamus(akar,"surround",1);akar = masukKamus(akar,"suspend",1);
    akar = masukKamus(akar,"swear",1);

    // Kamus TUVWZYZ

    akar = masukKamus(akar,"tabulate",1);akar = masukKamus(akar,"take",1);
    akar = masukKamus(akar,"talk",1);akar = masukKamus(akar,"tame",1);
    akar = masukKamus(akar,"tap",1);akar = masukKamus(akar,"target",1);
    akar = masukKamus(akar,"taste",1);akar = masukKamus(akar,"teach",1);
    akar = masukKamus(akar,"tear",1);akar = masukKamus(akar,"tease",1);
    akar = masukKamus(akar,"telephone",1);akar = masukKamus(akar,"tell",1);
    akar = masukKamus(akar,"tempt",1);akar = masukKamus(akar,"terrify",1);
    akar = masukKamus(akar,"test",1);akar = masukKamus(akar,"thank",1);
    akar = masukKamus(akar,"thank",1);akar = masukKamus(akar,"think",1);
    akar = masukKamus(akar,"thrive",1);akar = masukKamus(akar,"throw",1);
    akar = masukKamus(akar,"thrust",1);akar = masukKamus(akar,"tick",1);
    akar = masukKamus(akar,"tickle",1);akar = masukKamus(akar,"tie",1);
    akar = masukKamus(akar,"time",1);akar = masukKamus(akar,"tip",1);
    akar = masukKamus(akar,"tire",1);akar = masukKamus(akar,"touch",1);
    akar = masukKamus(akar,"tour",1);akar = masukKamus(akar,"tow",1);
    akar = masukKamus(akar,"trace",1);akar = masukKamus(akar,"trade",1);
    akar = masukKamus(akar,"train",1);akar = masukKamus(akar,"transcribe",1);
    akar = masukKamus(akar,"transfer",1);akar = masukKamus(akar,"transform",1);
    akar = masukKamus(akar,"translate",1);akar = masukKamus(akar,"transport",1);
    akar = masukKamus(akar,"trap",1);akar = masukKamus(akar,"travel",1);
    akar = masukKamus(akar,"tread",1);akar = masukKamus(akar,"treat",1);
    akar = masukKamus(akar,"trick",1);akar = masukKamus(akar,"trip",1);
    akar = masukKamus(akar,"trot",1);akar = masukKamus(akar,"trouble",1);
    akar = masukKamus(akar,"troubleshoot",1);akar = masukKamus(akar,"trust",1);
    akar = masukKamus(akar,"try",1);akar = masukKamus(akar,"tug",1);
    akar = masukKamus(akar,"tumble",1);akar = masukKamus(akar,"turn",1);
    akar = masukKamus(akar,"tutor",1);akar = masukKamus(akar,"twist",1);
    akar = masukKamus(akar,"type",1);akar = masukKamus(akar,"undergo",1);
    akar = masukKamus(akar,"understand",1);akar = masukKamus(akar,"undertake",1);
    akar = masukKamus(akar,"undress",1);akar = masukKamus(akar,"unfasten",1);
    akar = masukKamus(akar,"unify",1);akar = masukKamus(akar,"unite",1);
    akar = masukKamus(akar,"unlock",1);akar = masukKamus(akar,"unpack",1);
    akar = masukKamus(akar,"untidy",1);akar = masukKamus(akar,"update",1);
    akar = masukKamus(akar,"upgrade",1);akar = masukKamus(akar,"uphold",1);
    akar = masukKamus(akar,"upset",1);akar = masukKamus(akar,"use",1);
    akar = masukKamus(akar,"utilize",1);akar = masukKamus(akar,"vanish",1);
    akar = masukKamus(akar,"verbalize",1);akar = masukKamus(akar,"verify",1);
    akar = masukKamus(akar,"vex",1);akar = masukKamus(akar,"visit",1);
    akar = masukKamus(akar,"wail",1);akar = masukKamus(akar,"wait",1);
    akar = masukKamus(akar,"wake",1);akar = masukKamus(akar,"walk",1);
    akar = masukKamus(akar,"wander",1);akar = masukKamus(akar,"want",1);
    akar = masukKamus(akar,"warm",1);akar = masukKamus(akar,"warn",1);
    akar = masukKamus(akar,"wash",1);akar = masukKamus(akar,"waste",1);
    akar = masukKamus(akar,"watch",1);akar = masukKamus(akar,"water",1);
    akar = masukKamus(akar,"wave",1);akar = masukKamus(akar,"wear",1);
    akar = masukKamus(akar,"weave",1);akar = masukKamus(akar,"wed",1);
    akar = masukKamus(akar,"weep",1);akar = masukKamus(akar,"weigh",1);
    akar = masukKamus(akar,"welcome",1);akar = masukKamus(akar,"wet",1);
    akar = masukKamus(akar,"whine",1);akar = masukKamus(akar,"whip",1);
    akar = masukKamus(akar,"whirl",1);akar = masukKamus(akar,"whisper",1);
    akar = masukKamus(akar,"whistle",1);akar = masukKamus(akar,"whistle",1);
    akar = masukKamus(akar,"wink",1);akar = masukKamus(akar,"wipe",1);
    akar = masukKamus(akar,"wish",1);akar = masukKamus(akar,"withdraw",1);
    akar = masukKamus(akar,"withhold",1);akar = masukKamus(akar,"withstand",1);
    akar = masukKamus(akar,"wobble",1);akar = masukKamus(akar,"wonder",1);
    akar = masukKamus(akar,"work",1);akar = masukKamus(akar,"worry",1);
    akar = masukKamus(akar,"wrap",1);akar = masukKamus(akar,"wreck",1);
    akar = masukKamus(akar,"wrestle",1);akar = masukKamus(akar,"wriggle",1);
    akar = masukKamus(akar,"wring",1);akar = masukKamus(akar,"write",1);
    akar = masukKamus(akar,"x-ray",1);akar = masukKamus(akar,"yawn",1);
    akar = masukKamus(akar,"yell",1);akar = masukKamus(akar,"zoom",1);



}

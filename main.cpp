#include "spellchecker.cpp"

using namespace std;

int main()
{
    int pil1,pil2;
    string usr,psw,lagi,newDictionary;
    masukKanDataBase();
    mainprogram:
   do{
        system("CLS");
        cout << "-------------------------------------------------------------------------------"<<endl;
        cout << "                                  SPELL CHECKER                                "<<endl;
        cout << "                                 find your spell                               "<<endl;
        cout << "-------------------------------------------------------------------------------"<<endl;
        cout << "\n\t\t\t ---------------------------"<<endl;
        cout << "\t\t\t|____________MENU___________|"<<endl;
        cout << "\t\t\t|1. ADMINISTRATOR           |"<<endl;
        cout << "\t\t\t|2. FIND SPELL              |"<<endl;
        cout << "\t\t\t|3. QUIT                    |"<<endl;
        cout << "\t\t\t-----------------------------"<<endl;
        cout << "\t\t\tYour choices are : "; cin >> pil1;
        switch(pil1)
        {
            case 1 :
                     cout << "Username : " ; cin >> usr;
                     cout << "Password : " ; cin >> psw;
                     if ( cekloginadmin(usr,psw) )
                     {
                        halamanadmin:
                         do
                         {
                         system("CLS");
                         cout << "-------------------------------------------------------------------------------"<<endl;
                         cout << "                                  SPELL CHECKER                                "<<endl;
                         cout << "                                 find your spell                               "<<endl;
                         cout << "-------------------------------------------------------------------------------"<<endl;
                         cout << "Hello Admin"<<endl;
                         cout << "\n\t\t\t ---------------------------"<<endl;
                         cout << "\t\t\t|____________MENU___________|"<<endl;
                         cout << "\t\t\t|1. MAKE NEW DICTIONARY     |"<<endl;
                         cout << "\t\t\t|2. DELETE DICTIONARY       |"<<endl;
                         cout << "\t\t\t|3. UPDATE DICTIONARY       |"<<endl;
                         cout << "\t\t\t|4. VIEW DICTIONARY         |"<<endl;
                         cout << "\t\t\t|5. HELP                    |"<<endl;
                         cout << "\t\t\t|6. FIND SPELL              |"<<endl;
                         cout << "\t\t\t|7. EXIT                    |"<<endl;
                         cout << "\t\t\t-----------------------------"<<endl;
                         cout << "\t\t\tYour choices are : "; cin >> pil2;
                         switch(pil2)
                         {
                             case 1 :
                                 cout << "Enter the New Dictionary ( ex : sleep,walking .. ) : " ; cin >> newDictionary;
                                 if ( cekAvailblekamus(makeTolower(newDictionary)) )
                                 {
                                     cout << "The Dictionary Data already exists .."<<endl;
                                 }
                                 else
                                 {
                                    masukKannewKamus(makeTolower(newDictionary));
                                    cout << "The  Dictionary '"<<newDictionary<<"' have been added .."<<endl;
                                 }
                                 break;
                             case 2 :
                                 cout << "Enter the dictionary to be removed(ex : sleep,walking ..) : ";cin >>newDictionary;
                                 if ( !cekAvailblekamus(makeTolower(newDictionary)) )
                                 {
                                     cout << "The Dictionary Data not Found .."<<endl;
                                 }
                                 else
                                 {
                                    hapusKamus(makeTolower(newDictionary));
                                 }
                                 break;
                             case 3 :
                                 cout << "Enter the dictionary to be update (ex : sleep,walking ..) : ";cin >> newDictionary;
                                 if ( !cekAvailblekamus(makeTolower(newDictionary)) )
                                 {
                                     cout << "The Dictionary Data not Found .."<<endl;
                                 }
                                 else
                                 {
                                     updatedataKamus(makeTolower(newDictionary));
                                     if ( status )
                                     {
                                          masukKannewKamus(makeTolower(tampungSem));
                                     }
                                 }
                                break;
                             case 4 :
                                DisplayDict();
                                break;
                             case 5 :
                         system("CLS");
                         cout << "-------------------------------------------------------------------------------"<<endl;
                         cout << "                            SPELL CHECKER HELP CENTER                          "<<endl;
                         cout << "-------------------------------------------------------------------------------"<<endl;
                         cout << "\t spell checker is a word checker application, the application checks a verb in the English language, where the application is matching data fed by the user and then if the data is fed is the same as in the dictionary, then the data will be released and if not it will issued his spelling words to approach the word" <<endl;
                         cout << "\n menu functionality :\n1.The function of (1) menu is to add new dictionary in application ,you just can input the new dictionary where there is does not exist in application"<<endl;
                         cout << "2.The function of (2) menu is to remove the dictionary , you can enterthe dictionary to be removed"<<endl;
                         cout << "3.The function of (3) menu is to update the dictionary , dictionary just can be update by the new different by the exist dictionary"<<endl;
                         cout << "4.The function of (4) munu is to view all dictionary by catalogue"<<endl;
                         cout << "-------------------------------------------------------------------------------"<<endl;
                               break;
                             case 6 :
                                status=true;goto temukan ;break;
                             case 7 :
                                cout << "Logout"<<endl;
                                getch();
                                goto mainprogram;
                                break;
                             default : cout << "wrong input "<<endl;break;
                         }
                         getch();
                         }while (pil2 != 6);
                     }
                     else{
                        cout << "Wrong Username or Password , contact the andministrator"<<endl;
                     }
                     break;
            case 2  :
                do{
                    temukan:
                    system("cls");
                    cout << "\t\t\tEnter Verb Spell : ";cin >> newDictionary ;
                    if (newDictionary.length() == 1)
                    {
                        grepKamus(makeTolower(newDictionary));
                    }
                    else
                    if ( cekAvailblekamus(makeTolower(newDictionary)) )
                    {
                        cout << "\n\t\t\t|--------Result--------|"<<endl;
                        cout << "\t\t\t     "<< newDictionary << " is found ..\n\t\t\t------------------------\n\t\t\t|your spell is correct |\n\t\t\t------------------------"<<endl;
                    }
                    else
                    {
                        cout << "\n\t\t\t|--------Result--------|"<<endl;
                        cout << "\t\t\t     "<< newDictionary << " is not found ..\n\t\t\t------------------------\n\t\t\t|your spell is incorrect |\n\t\t\t------------------------"<<endl;
                        cout << "\t\t\t View Recomendation ? (y/n)" ; cin>>lagi;
                        saveRecom(makeTolower(newDictionary));
                        if ( lagi[0]!='n')
                        {
                            DisplayRecom();
                        }
                        HapusRekomendation();
                    }
                    cout << "\n\t\t\t    Try Again ? " ; cin >> lagi ;
                }while (makeTolower(lagi)[0] != 'n');
                if( status ){status = false;goto halamanadmin;}
                break;
            case 3 : cout << "Thank's for using spell checker"<<endl;break;
            default :cout << "wrong input "<<endl;break;
        }
    getch();
    }while(pil1 != 3);
    return 0;
}

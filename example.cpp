#include <iostream>
#include <string>
#include "TextTable.h"
#define TEXTTABLE_ENCODE_MULTIBYTE_STRINGS
#define TEXTTABLE_USE_EN_US_UTF8

using namespace std;

class Strategie{
    private:
        string name;
        int scorePlayer1;
        int scorePlayer2;
    public:
        Strategie(string name,int scorePlayer1,int scorePlayer2){
            this->name = name;
            this->scorePlayer1 = scorePlayer1;
            this->scorePlayer2 = scorePlayer2;
        }
        string getName(){
            return this->name;
        }
        int getScorePlayer1(){
            return this->scorePlayer1;
        }
        int getscorePlayer2(){
            return this->scorePlayer2;
        }
        void setName(string name){
            this->name = name;
        }
        void setScorePlayer1(int scorePlayer1){
            this->scorePlayer1 = scorePlayer1;
        }
        void setName(int scorePlayer2){
            this->scorePlayer2 = scorePlayer1;
        }
};

int determineMDS(int player,vector<vector<Strategie>>& matJeu,int nb_strategie1,int nb_strategie2){
    int stdm = -1;
    bool b = true;
    switch (player)
    {
        case 1:{
            for (int i = 0; i < nb_strategie1; i++)
            {
                b = true;
                for (int j = 0; j < nb_strategie2; j++)
                {
                    for (int k = 0; k < nb_strategie1; k++)
                    {
                        if (k != i)
                        {
                            if (matJeu[k][j].getScorePlayer1() > matJeu[i][j].getScorePlayer1())
                            {
                                b = false;
                                break;
                            }
                            
                        }
                        
                    }
                    if (!b)
                    {
                        break;
                    }
                }
                if (b)
                {
                    return i;
                }
            }
            break;
        }
        default:{
            for (int j = 0; j < nb_strategie2; j++)
            {
                b = true;
                for (int i = 0; i < nb_strategie1; i++)
                {
                    for (int k = 0; k < nb_strategie2; k++)
                    {
                        if (k != j)
                        {
                            if (matJeu[i][k].getscorePlayer2() > matJeu[i][j].getscorePlayer2())
                            {
                                b = false;
                                break;
                            }
                        }
                        
                    }
                    if (!b)
                    {
                        break;
                    }
                }
                if (b)
                {
                    return j;
                }
            }
            break;   
        }
    }
    return -1;
}

void eissd(vector<vector<Strategie>>& matJeu,int nb_strategie1,int nb_strategie2){
    vector<int> temp;
    bool b = true;

    //for lines
    // for (int i = 0; i < nb_strategie1; i++)
    // {
    //     for (int j = 0; j < nb_strategie1; j++)
    //     {
    //         if (j != i)
    //         {
    //             b = true;
    //             for (int k = 0; k < nb_strategie2; k++)
    //             {
    //                 if (matJeu[i][k].getScorePlayer1() > matJeu[j][k].getScorePlayer1())
    //                 {
    //                     b = false;
    //                     break;
    //                 }                
    //             }
    //             if (b)
    //             {
    //                 cout << "(i,j) = " << i << "," << j <<endl;
    //                 temp.push_back(i);
    //             }
    //         }
    //     } 
    // }

    //for columns
    for (int i = 0; i < nb_strategie2; i++)
    {
        for (int j = 0; j < nb_strategie2; j++)
        {
            if (j != i)
            {
                b = true;
                for (int k = 0; k < nb_strategie1; k++)
                {
                    if (matJeu[k][i].getscorePlayer2() > matJeu[k][j].getscorePlayer2())
                    {
                        b = false;
                        break;
                    }                
                }
                if (b)
                {
                    cout << "(i,j) = " << i << "," << j <<endl;
                    temp.push_back(i);
                }
            }
        } 
    }

    for(auto& index : temp){
        cout << "i = "<< index << endl;
    }
}

// class Player{
//     private:
//         string name;
//         vector<Strategie>* strategies;
//     public:
//         Player(string name){
//             this->name = name;
//             this->strategies = new vector<Strategie>();
//         }
//         string getName(){
//             return this->name;
//         }
//         void addStrategie(Strategie s){
//             this->strategies->push_back(s);
//         }
// };

int main()
{   START:
    system("cls");

    TextTable* t = new TextTable( '-', '|', '+' );
    // Player* p1 = new Player("Player 1");
    // Player* p2 = new Player("Player 2");
    int nb_strategie1,nb_strategie2;

    cout << "How many strategies player 1 have ?" << endl << "==>" ;
    cin >> nb_strategie1;
    cout << "How many strategies player 2 have ?" << endl << "==>" ;
    cin >> nb_strategie2;

    string name;
    vector<string>* strategies = new vector<string>();
    vector<vector<Strategie>> matJeu;
    vector<Strategie> st;

    for (int i = 0; i < nb_strategie1; i++)
    {    
        cout << "Name of the startegy " << i+1 << " for player 1:" ;
        cin >> name;
        strategies->push_back(name);
    }

    for (int i = 0; i < nb_strategie2; i++)
    {
        cout << "Name of the startegy " << i+1 << " for player 2:" ;
        cin >> name;
        strategies->push_back(name);
    }

    t->add("Player 1 | Player 2");
    for (int i = nb_strategie1; i < strategies->size(); i++)
    {
        t->add(strategies->at(i));
    }
    t->endOfRow();
    system("cls");
    for (int i = 0; i < nb_strategie1; i++)
    {
        t->add(strategies->at(i));
        for (int j = nb_strategie1; j < strategies->size(); j++)
        {
            int scorePlayer1,scorePlayer2;
            cout << "When player 1 choose " << strategies->at(i) << " and player 2 choose " << strategies->at(j) <<":\n";
            cout << "Player 1 gain = ";
            cin >> scorePlayer1;
            cout << "Player 2 gain = ";
            cin >> scorePlayer2;
            string name = "("+strategies->at(i)+","+strategies->at(j)+")";
            string temp = "("+to_string(scorePlayer1)+","+to_string(scorePlayer2)+")";
            t->add(temp);
            Strategie* s = new Strategie(name,scorePlayer1,scorePlayer2); 
            st.push_back(*s);
            system("cls");
        }
        matJeu.push_back(st);
        st.clear();
        t->endOfRow();
    }
    t->setAlignment( 2, TextTable::Alignment::RIGHT );
    cout <<"The payoff matrice of the game :\n"<< *t;

    int choice;
    cout <<"if you want to continue enter 1,if you want to re-enter the details press 2"<< endl <<"==>";
    cin >> choice;
    if (choice == 2)
    {
        delete t;
        delete strategies;
        goto START;
    }
    else
    {
        system("cls");
        int sdm = determineMDS(1,matJeu,nb_strategie1,nb_strategie2);
        int sdm2 = determineMDS(2,matJeu,nb_strategie1,nb_strategie2);
        if (sdm != -1)
        {
            cout << "The strict dominant strategy for player 1 is : ";
            cout << strategies->at(sdm) << endl;
        }
        else
        {
            cout << "There is no dominant strategy for player 1!" << endl;
        }
        if (sdm2 != -1)
        {
            cout << "The strict dominant strategy for player 2 is : ";
            cout << strategies->at(sdm2+nb_strategie1) << endl;
        }
        else
        {
            cout << "There is no dominant strategy for player 2!" <<endl;
        }
        eissd(matJeu,nb_strategie1,nb_strategie2);
    }

    // t.add( "" );
    // t.add( "Sex" );
    // t.add( "Age" );
    // t.endOfRow();

    // t.add( "Moseqsddddddddddddds" );
    // t.add( "(-12,1000000)" );
    // t.add( "4556" );
    // t.endOfRow();

    // t.add( "Jesus" );
    // t.add( "male" );
    // t.add( "2016" );
    // t.endOfRow();

    // t.setAlignment( 2, TextTable::Alignment::RIGHT );
    // cout << t;
    return 0;
}

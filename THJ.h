#include <iostream>
#include <string>
#include <iterator>
#include <Windows.h>
#include <bits/stdc++.h>
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

vector<vector<Strategie>> matJeu;
int nb_strategie1,nb_strategie2;
vector<string>* strategies = new vector<string>();
vector<vector<Strategie>> v;
bool lineDel = true,colDel = true;

int determineMDS(int player){
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
                            if (matJeu[k][j].getScorePlayer1() >= matJeu[i][j].getScorePlayer1())
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
                            if (matJeu[i][k].getscorePlayer2() >= matJeu[i][j].getscorePlayer2())
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

int determineMDF(int player){
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

void delLine(){
    vector<int> temp;
    bool b = true;
    for (int i = 0; i < nb_strategie1; i++)
    {
        for (int j = 0; j < nb_strategie1; j++)
        {
            if (j != i)
            {
                b = true;
                for (int k = 0; k < nb_strategie2; k++)
                {
                    if (matJeu[i][k].getScorePlayer1() > matJeu[j][k].getScorePlayer1())
                    {
                        b = false;
                        break;
                    }                
                }
                if (b)
                {
                    cout << "Strategie " << strategies->at(i) <<" for player 1 is dominated by strategie " << strategies->at(j) <<endl;
                    temp.push_back(i);
                }
            }
        } 
    }
    if (temp.empty())
    {
        cout << "There is no  dominant strategy for player 1"<<endl;
    }
    lineDel = !temp.empty();
    vector<int>::iterator it;
    vector<Strategie> s;
    for (int i = 0; i < nb_strategie1; i++)
    {
        it = find(temp.begin(),temp.end(),i);
        if (it == temp.end())
        {
            for (int j = 0; j < nb_strategie2; j++)
            {
                s.push_back(matJeu[i][j]);
            }   
            v.push_back(s);
            s.clear();
        }
    }
    int k = 0;
    for (auto& c : temp)
    {
        c = c - k;
        strategies->erase(strategies->begin()+c);
        nb_strategie1--;
        k++;
    }
    matJeu.clear();
    matJeu = v;

    TextTable* t = new TextTable( '-', '|', '+' );
    t->add("Player 1 | Player 2");
    for (int i = nb_strategie1; i < strategies->size(); i++)
    {
        t->add(strategies->at(i));
    }
    t->endOfRow();
    for (int i = 0; i < nb_strategie1; i++)
    {
        t->add(strategies->at(i));
        for (int j = 0; j < nb_strategie2; j++)
        {
            string temp = "("+to_string(matJeu[i][j].getScorePlayer1())+","+to_string(matJeu[i][j].getscorePlayer2())+")";
            t->add(temp); 
        }
        t->endOfRow();
    }
    t->setAlignment( 2, TextTable::Alignment::RIGHT );
    cout << *t;
    v.clear();
}

void delCol(){
    vector<int> temp;
    bool b = true;
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
                    cout << "Strategie " << strategies->at(i+nb_strategie1) <<" for player 2 is dominated by strategie " << strategies->at(j+nb_strategie1) <<endl;
                    temp.push_back(i);
                }
            }
        } 
    }
    if (temp.empty())
    {
        cout << "There is no dominant strategy for player 2"<<endl;
    }
    colDel = !temp.empty();
    vector<int>::iterator it;
    vector<Strategie> s;
    for (int i = 0; i < nb_strategie1; i++)
    {
        for (int j = 0; j < nb_strategie2; j++)
        {
            it = find(temp.begin(),temp.end(),j);
            if (it == temp.end())
            {
                s.push_back(matJeu[i][j]);
            }
        }
        v.push_back(s);
        s.clear();
    }
    int k = 0;
    for (auto& c : temp)
    {
        c = c - k + nb_strategie2;
        strategies->erase(strategies->begin()+c);
        nb_strategie2--;
        k++;
    }

    matJeu.clear();
    matJeu = v;
    TextTable* t = new TextTable( '-', '|', '+' );
    t->add("Player 1 | Player 2");
    for (int i = nb_strategie1; i < strategies->size(); i++)
    {
        t->add(strategies->at(i));
    }
    t->endOfRow();
    for (int i = 0; i < nb_strategie1; i++)
    {
        t->add(strategies->at(i));
        for (int j = 0; j < nb_strategie2; j++)
        {
            string temp = "("+to_string(matJeu[i][j].getScorePlayer1())+","+to_string(matJeu[i][j].getscorePlayer2())+")";
            t->add(temp); 
        }
        t->endOfRow();
    }
    t->setAlignment( 2, TextTable::Alignment::RIGHT );
    cout << *t;
    v.clear();
}

void eissd(){
    while (lineDel || colDel)
    {
        delLine();
        delCol();
    }
    if (strategies->size() != 2)
    {
        cout << "There is no equilibria for this game!" << endl;
    }
    else
    {
        cout << "the equilibria for this game is " << matJeu[0][0].getName() << "=(" << matJeu[0][0].getScorePlayer1() << "," << matJeu[0][0].getscorePlayer2() << ")" << endl;
    }
    lineDel = true;colDel = true;
}
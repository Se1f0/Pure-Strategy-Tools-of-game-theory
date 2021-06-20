#include <iostream>
#include <string>
#include <iterator>
#include <Windows.h>
#include <bits/stdc++.h>
#include "TextTable.h"
#define TEXTTABLE_ENCODE_MULTIBYTE_STRINGS
#define TEXTTABLE_USE_EN_US_UTF8

using namespace std;

class Profile{
    private:
        string name;
        int scorePlayer1;
        int scorePlayer2;
    public:
        Profile(string name,int scorePlayer1,int scorePlayer2){
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

vector<vector<Profile>> matJeu;
int nb_strategie1,nb_strategie2;
vector<string>* strategies = new vector<string>();
vector<vector<Profile>> v;
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

void delLine(int type){
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
                    if ((type == 1 && matJeu[i][k].getScorePlayer1() > matJeu[j][k].getScorePlayer1()) || (type == 2 && matJeu[i][k].getScorePlayer1() >= matJeu[j][k].getScorePlayer1()))
                    {
                        b = false;
                        break;
                    }                
                }
                if (b)
                {
                    if (type == 1)
                    {
                        cout << "Strategie " << strategies->at(i) <<" for player 1 is dominated by strategie " << strategies->at(j) <<endl;
                    }
                    else
                    {
                        cout << "Strategie " << strategies->at(i) <<" for player 1 is strictly dominated by strategie " << strategies->at(j) <<endl;
                    }
                    temp.push_back(i);
                    goto NEXT;
                }
            }
        } 
    }
    NEXT:
    if (temp.empty())
    {
        cout << "There is no strategy that is dominated by another strategy for player 1"<<endl;
    }
    lineDel = !temp.empty();
    vector<int>::iterator it;
    vector<Profile> s;
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

void delCol(int type){
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
                    if ((type == 1 && matJeu[k][i].getscorePlayer2() > matJeu[k][j].getscorePlayer2()) || (type == 2 && matJeu[k][i].getscorePlayer2() >= matJeu[k][j].getscorePlayer2()))
                    {
                        b = false;
                        break;
                    }                
                }
                if (b)
                {
                    if (type == 1)
                    {
                        cout << "Strategie " << strategies->at(i+nb_strategie1) <<" for player 2 is dominated by strategie " << strategies->at(j+nb_strategie1) <<endl;       
                    }
                    else
                    {
                        cout << "Strategie " << strategies->at(i+nb_strategie1) <<" for player 2 is strictly dominated by strategie " << strategies->at(j+nb_strategie1) <<endl;
                    }
                    temp.push_back(i);
                    goto NEXT2;
                }
            }
        } 
    }
    NEXT2:
    if (temp.empty())
    {
        cout << "There is no strategy that is dominated by another strategy for player 2"<<endl;
    }
    colDel = !temp.empty();
    vector<int>::iterator it;
    vector<Profile> s;
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
        c = c - k + nb_strategie1;
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

void eisfd(){
    while (lineDel || colDel)
    {
        delLine(1);
        delCol(1);
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

void eissd(){
    while (lineDel || colDel)
    {
        delLine(2);
        delCol(2);
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

void nashEq(){
    vector<Profile> temp1;
    vector<Profile> temp2;
    int max,posMax,cpt=0;

    for (int j = 0; j < nb_strategie2; j++)
    {
        for (int i = 0; i < nb_strategie1; i++)
        {
            max = matJeu[i][j].getScorePlayer1();
            for (int k = 0; k < nb_strategie1; k++)
            {
                if (k != i)
                {
                    if (matJeu[k][j].getScorePlayer1() >= max)
                    {
                        max = matJeu[k][j].getScorePlayer1();
                    }
                }
            }
        }
        for (int k = 0; k < nb_strategie1; k++)
        {
            if (matJeu[k][j].getScorePlayer1() == max)
            {
                temp1.push_back(matJeu[k][j]);
            }
        }
    }

    for (int i = 0; i < nb_strategie1; i++)
    {
        for (int j = 0; j < nb_strategie2; j++)
        {
            max = matJeu[i][j].getscorePlayer2();
            for (int k = 0; k < nb_strategie2; k++)
            {
                if (k != j)
                {
                    if (matJeu[i][k].getscorePlayer2() >= max)
                    {
                        max = matJeu[i][k].getscorePlayer2();
                    }
                }
            }
        }
        for (int k = 0; k < nb_strategie2; k++)
        {
            if (matJeu[i][k].getscorePlayer2() == max)
            {
                temp2.push_back(matJeu[i][k]);               
            }
        }
    }
    cout << "Best 1 :";
    for (auto& c : temp1)
    {
        cout << c.getName();
    }
    cout << "\nBest 2 :";
    for (auto& c : temp2)
    {
        cout << c.getName();
    }

    for (auto& c : temp1)
    {
        for (auto& c2 : temp2)
        {
            if (c.getName() == c2.getName())
            {
                cpt++;
                if (cpt == 1)
                {
                    cout << "\nNash equilibrium of this game : ";
                }
                cout << c.getName() << " ";
            }
        }
    }
    if (cpt == 0)
    {
        cout << "\nThere is no Nash equilibrium in this game in pure\n";
    }
}

int securityLevelStrategy(int player,int s){
    int min;
    if (player == 1)
    {
        min = matJeu[s][0].getScorePlayer1();
        for (int j = 1; j < nb_strategie2; j++)
        {
            if (matJeu[s][j].getScorePlayer1() <= min)
            {
                min = matJeu[s][j].getScorePlayer1();
            }
        }
        return min;
    }
    else
    {
        min = matJeu[0][s].getscorePlayer2();
        for (int i = 1; i < nb_strategie1; i++)
        {
            if (matJeu[i][s].getscorePlayer2() <= min)
            {
                min = matJeu[i][s].getscorePlayer2();
            }
        }
        return min;
    }
    
}

int securityLevelPlayer(int player){
    int max;
    if (player == 1)
    {
        max = securityLevelStrategy(1,0);
        for (int i = 1; i < nb_strategie1; i++)
        {
            if (securityLevelStrategy(1,i) >= max)
            {
                max = securityLevelStrategy(1,i);
            }
        }
        return max;
    }
    else
    {
        max = securityLevelStrategy(2,0);
        for (int j = 1; j < nb_strategie2; j++)
        {
            if (securityLevelStrategy(2,j) >= max)
            {
                max = securityLevelStrategy(2,j);
            }
        }
        return max;
    }
    
}

void pareto(){
    vector<Profile> finale;
    bool b = true;
    for (int i = 0; i < nb_strategie1; i++)
    {
        for (int j = 0; j < nb_strategie2; j++)
        {
            b = true;
            for (int k = 0; k < nb_strategie1; k++)
            {
                for (int l = 0; l < nb_strategie2; l++)
                {
                    if (k != i || l != j)
                    {
                        int gain11 = matJeu[i][j].getScorePlayer1(),gain12 = matJeu[i][j].getscorePlayer2(),gain21 = matJeu[k][l].getScorePlayer1(),gain22 = matJeu[k][l].getscorePlayer2();
                        if ( ((gain21 > gain11 && gain22 >= gain12) || (gain21 >= gain11 && gain22 > gain12)) )
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
                finale.push_back(matJeu[i][j]);
            }
        }
    }
    cout << "Profiles that are Optimum pareto are : ";
    for (auto& c : finale)
    {
        cout << c.getName() << " " ;
    }
}
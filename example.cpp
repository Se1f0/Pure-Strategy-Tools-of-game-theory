#include "THJ.h"

int main()
{   
    system("cls");
    TextTable* t = new TextTable( '-', '|', '+' );
    vector<vector<Profile>> payOff;

    cout << "How many strategies player 1 have ?" << endl << "==>" ;
    cin >> nb_strategie1;
    system("cls");
    cout << "How many strategies player 2 have ?" << endl << "==>" ;
    cin >> nb_strategie2;
    system("cls");
    int nb1 = nb_strategie1,nb2 = nb_strategie2;
    string name;
    
    vector<Profile> st;

    for (int i = 0; i < nb_strategie1; i++)
    {    
        cout << "Name of the startegy " << i+1 << " for player 1:" ;
        cin >> name;
        strategies->push_back(name);
    }
    system("cls");
    for (int i = 0; i < nb_strategie2; i++)
    {
        cout << "Name of the startegy " << i+1 << " for player 2:" ;
        cin >> name;
        strategies->push_back(name);
    }
    vector<string> init = *strategies;
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
            Profile* s = new Profile(name,scorePlayer1,scorePlayer2); 
            st.push_back(*s);
            system("cls");
        }
        matJeu.push_back(st);
        st.clear();
        t->endOfRow();
    }
    MENU:
    system("cls");
    t->setAlignment( 2, TextTable::Alignment::RIGHT );
    cout <<"The payoff matrice of the game :\n"<< *t;
    payOff = matJeu;
    int choice;
    cout << "\n\nMain Menu:" << endl;
    cout << "==========" << endl;
    cout << "1 - To determine any strict dominant strategy in the entered game." << endl;
    cout << "2 - To determine any weak dominant strategy in the entered game." << endl;
    cout << "3 - To determine if there is an equilibria in the entered game (EISSD)." << endl;
    cout << "4 - To determine if there is an equilibria in the entered game (EISFD)." << endl; 
    cout << "5 - To determine if there is a Nash equilibria in the entered game." << endl;
    cout << "6 - To determine if there is Pareto profiles." << endl;
    cout << "7 - To determine security level of each player" << endl;
    cout << "8 - To determine security level of each strategy" << endl;
    cout << "0 - To exit." << endl;
    cout <<"==>";
    cin >> choice;
    if (choice == 0)
    {
        goto END;
    }
    else
    {
        if (choice == 1)
        {
            system("cls");
            int sdm = determineMDS(1);
            int sdm2 = determineMDS(2);
            if (sdm != -1)
            {
                cout << "The strict dominant strategy for player 1 is : ";
                cout << strategies->at(sdm) << endl;
            }
            else
            {
                cout << "There is no strict dominant strategy for player 1!" << endl;
            }
            if (sdm2 != -1)
            {
                cout << "The strict dominant strategy for player 2 is : ";
                cout << strategies->at(sdm2+nb_strategie1) << endl;
            }
            else
            {
                cout << "There is no strict dominant strategy for player 2!" << endl;
            }
        }
        if (choice == 2)
        {
            system("cls");
            int fdm = determineMDF(1);
            int fdm2 = determineMDF(2);
            if (fdm != -1)
            {
                cout << "The weak dominant strategy for player 1 is : ";
                cout << strategies->at(fdm) << endl;
            }
            else
            {
                cout << "There is no weak dominant strategy for player 1!" << endl;
            }
            if (fdm2 != -1)
            {
                cout << "The weak dominant strategy for player 2 is : ";
                cout << strategies->at(fdm2+nb_strategie1) << endl;
            }
            else
            {
                cout << "There is no weak dominant strategy for player 2!" << endl;
            }
        }
        if (choice == 3)
        {
            system("cls");
            eissd();
            nb_strategie1 = nb1;
            nb_strategie2 = nb2;
            *strategies = init;
            matJeu.clear();
            matJeu = payOff;
        }
        if (choice == 4)
        {
            system("cls");
            eisfd();
            nb_strategie1 = nb1;
            nb_strategie2 = nb2;
            *strategies = init;
            matJeu.clear();
            matJeu = payOff;
        }
        if (choice == 5)
        {
            system("cls");
            nashEq();
        }
        if (choice == 6)
        {
            system("cls");
            pareto();
        }
        
        if (choice == 7)
        {
            system("cls");
            cout << "Securtiy level of player 1 :" << securityLevelPlayer(1) << endl;
            cout << "Securtiy level of player 2 :" << securityLevelPlayer(2) << endl;
        }
        if (choice == 8)
        {
            system("cls");
            cout << "Securtiy level of the each strategy of player 1 :" << endl;
            for (int i = 0; i < nb_strategie1; i++)
            {
                cout << strategies->at(i) << ":" << securityLevelStrategy(1,i) << endl;
            }
            cout << "Securtiy level of the each strategy of player 2 :" << endl;
            for (int j = nb_strategie1; j < strategies->size(); j++)
            {
                cout << strategies->at(j) << ":" << securityLevelStrategy(2,j-nb_strategie1) << endl;
            }
            
        }
        
        cout << "\n\nOPTIONS:" << endl;
        cout << "========" << endl;
        cout << "1 - To go back to main menu" << endl; 
        cout << "0 - To exit" << endl;
        cout <<"==>";
        int choice2;
        cin >> choice2;
        if (choice2 == 1)
        {
            goto MENU;   
        }
    }
    END:
    system("cls");
    cout << "Closing....Goodby" ;
    Sleep(2000);
    return 0;
}
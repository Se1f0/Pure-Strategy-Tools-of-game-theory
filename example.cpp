#include "THJ.h"

int main()
{   
    system("cls");
    TextTable* t = new TextTable( '-', '|', '+' );
    vector<vector<Strategie>> payOff;

    cout << "How many strategies player 1 have ?" << endl << "==>" ;
    cin >> nb_strategie1;
    system("cls");
    cout << "How many strategies player 2 have ?" << endl << "==>" ;
    cin >> nb_strategie2;
    system("cls");
    int nb1 = nb_strategie1,nb2 = nb_strategie2;
    string name;
    
    vector<Strategie> st;

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
            Strategie* s = new Strategie(name,scorePlayer1,scorePlayer2); 
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
    cout << "1 - To determine any strict/weak dominant strategy in the entered game." << endl;
    cout << "2 - To determine if there is an equilibria in the entered game." << endl; 
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
                int fdm = determineMDF(1);
                if (fdm != -1)
                {
                    cout << "The weak dominant strategy for player 1 is : ";
                    cout << strategies->at(fdm) << endl;
                }
                else
                {
                    cout << "There is no dominant strategy for player 1!" << endl;
                }
            }
            if (sdm2 != -1)
            {
                cout << "The strict dominant strategy for player 2 is : ";
                cout << strategies->at(sdm2+nb_strategie1) << endl;
            }
            else
            {
                int fdm2 = determineMDF(2);
                if (fdm2 != -1)
                {
                    cout << "The weak dominant strategy for player 2 is : ";
                    cout << strategies->at(fdm2+nb_strategie1) << endl;
                }
                else
                {
                    cout << "There is no dominant strategy for player 2!" << endl;
                }
            }
        }
        if (choice == 2)
        {
            system("cls");
            eissd();
            nb_strategie1 = nb1;
            nb_strategie2 = nb2;
            *strategies = init;
            matJeu.clear();
            matJeu = payOff;
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
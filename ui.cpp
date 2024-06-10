#include "ui.h"
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<cstdio>
#include<fstream>
#include <string>
#include<vector>
#include "game.h"
#include "element.h"
#include "minmax.h"
using namespace std;

void ui() {
    srand(time(NULL));

    while (true) {
        int number, mode;//mode==type of stucture, number==operation
        Game *game;
        cout << "KOLKO I KRZYZYK" << endl;
        cout << "START [1]" << endl;
        cout << "ZAMKNIJ [0]" << endl << endl;
        cout << "Wybor: ";
        cin >> mode;
        cout << endl;
        bool start = true;//for closing ui
        bool s;
        switch (mode) {//making structure
            case 1: {
                int size, win;
                cout << "Podaj rozmiar planszy: ";
                cin >> size;
                cout << endl << "Podaj ilosc znakow w rzedzie do wygranej: ";
                cin >> win;
                MinMax minMax(win);
                game = new Game(size, win);
                cout<<"Wybierz znak ktorym chcesz grac: "<<endl;
                cout<<"KOLKO [0]"<<endl;
                cout<<"KRZYZYK [1]"<<endl;
                cout<<"Wybor: ";
                cin>>s;
                cout<<endl;
                int l=rand()%2;
                int x, y;
                if(l==0){
                    cout<<"Ruch komputera"<<endl;
                    game->computerMove(minMax.findBestMove(game->board));//do zmiany
                    game->printBoard(s);
                }
                else game->printBoard(s);
                while (start == 1) {
                    cout << "Twoj ruch" << endl;
                    cout << "Podaj wspolrzedne x: ";
                    cin >> y;
                    cout << "Podaj wspolrzedne y: ";
                    cin >> x;
                    game->humanMove(x-1, y-1);
                    game->printBoard(s);
                    if (game->isWin() == 1) {
                        cout << "WYGRALES" << endl<<endl;
                        start = 0;
                        break;
                    } else if (game->isWin() == 2) {
                        cout << "REMIS" << endl<<endl;
                        start = 0;
                        break;
                    }
                    cout << "Ruch komputera" << endl;
                    game->computerMove(minMax.findBestMove(game->board));//do zmiany
                    game->printBoard(s);
                    if (game->isWin() == 1) {
                        cout << "PRZEGRALES" << endl<<endl;
                        start = 0;
                        break;
                    } else if (game->isWin() == 2) {
                        cout << "REMIS" << endl<<endl;
                        start = 0;
                        break;
                    }
                }
                break;
            }
            default: {
                cout << "Program zakonczony";
                return;
            }
        }
    }
}
#include "ui.h"
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<cstdio>
#include<fstream>
#include <string>
#include<vector>
#include "game.h"
using namespace std;

void ui() {
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
                game = new Game(size, win);
                cout<<"Wybierz znak ktorym chcesz grac: "<<endl;
                cout<<"KOLKO [0]"<<endl;
                cout<<"KRZYZYK [1]"<<endl;
                cout<<"Wybor: ";
                cin>>s;
                cout<<endl;
                int l=rand()%2;
                if(l==0){
                    cout<<"Ruch komputera"<<endl;
                    game->computerMove();
                    game->printBoard(s);
                }
                game->printBoard(s);
                while (start == 1) {
                    cout << "Twoj ruch" << endl;
                    int x, y;
                    cout << "Podaj wspolrzedne x: ";
                    cin >> y;
                    cout << "Podaj wspolrzedne y: ";
                    cin >> x;
                    game->humanMove(x-1, y-1);
                    game->printBoard(s);
                    if (game->isWin() == 1) {
                        cout << "WYGRALES" << endl;
                        start = 0;
                        break;
                    } else if (game->isWin() == 2) {
                        cout << "REMIS" << endl;
                        start = 0;
                        break;
                    }
                    cout << "Ruch komputera" << endl;
                    game->computerMove();
                    game->printBoard(s);
                    if (game->isWin() == 1) {
                        cout << "WYGRAL KOMPUTER" << endl;
                        start = 0;
                        break;
                    } else if (game->isWin() == 2) {
                        cout << "REMIS" << endl;
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
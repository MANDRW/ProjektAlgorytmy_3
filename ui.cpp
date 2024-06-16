#include "ui.h"
#include<iostream>
#include<cstdlib>
#include<ctime>
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
                int size=0, win=0,depth=0;
                while(size<1) {
                    cout << "Podaj rozmiar planszy: ";
                    cin >> size;
                    if(size<1) cout<<"Podaj liczbe dodatnia"<<endl;
                }
                while(win<3) {
                    cout << "Podaj ilosc znakow w rzedzie do wygranej: ";
                    cin >> win;
                    if(win<3) cout<<"Minimalna liczba to 3"<<endl;
                }

                cout << endl << "Podaj glebokosc dzialania algorytmu (0 - auto-dobieranie): ";
                cin >> depth;
                if (depth < 1) cout << "autodobieranie" << endl;
                MinMax minMax(win, depth);
                game = new Game(size, win);
                int t;
                cout<<"Wybierz znak ktorym chcesz grac: "<<endl;
                cout<<"KOLKO [0]"<<endl;
                cout<<"KRZYZYK [1]"<<endl;
                cout<<"Wybor: ";
                cin>>t;
                s=bool(t%2);
                cout<<endl;
                int l=rand()%2;
                int x=0, y=0;
                if(l==0){
                    cout<<"Ruch komputera"<<endl<<endl;
                    game->computerMove(minMax.findBestMove(game->board));
                    game->printBoard(s);
                }
                else game->printBoard(s);
                while (start == 1) {
                    while(x<=0 or x>size and y<=0 or y>size){
                        cout<<endl<<"Podaj wspolrzedne x: ";
                        cin>>y;
                        cout<<"Podaj wspolrzedne y: ";
                        cin>>x;
                        cout<<endl;
                        if(x<=0 or x>size or y<=0 or y>size) {
                            cout<<"Takie pole nie istnieje"<<endl;
                            x=0;
                            y=0;
                        }
                        else if (game->board[x-1][y-1]!=EMPTY){
                            cout<<"Zajete pole"<<endl;
                            x=0;
                            y=0;
                        }
                    }
                    game->humanMove(x-1, y-1);
                    x=0;
                    y=0;
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
                    cout << "Ruch komputera" << endl<<endl;
                    game->computerMove(minMax.findBestMove(game->board));
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
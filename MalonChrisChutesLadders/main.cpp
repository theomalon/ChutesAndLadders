/*******************************
Name: Chris Malon
Date: 1/31/13
Description: Chutes and Ladders
*******************************/

#include "board.h"

int main()
{

    srand(time(NULL));

    int players;
    cout<<"Enter the number of players (2-4): ";
    cin>>players;
    while (players < 2 || players > 4)
    {
        cout<<"Invalid amount. Need 2-4 players to play!"<<endl;
        system("CLS");
        cout<<"Enter the number of players (2-4): ";
        cin>>players;
    }
    cin.get();
    system("CLS");
    initPlayer(players);
    initBoard();
    displayBoard();
    runGame();

    return 0;
}


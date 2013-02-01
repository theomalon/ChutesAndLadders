/*******************************
Name: Chris Malon
Date: 1/31/13
Description: Chutes and Ladders
*******************************/

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <climits>
#include <windows.h>
#define NUMINNERSPACE 5

enum COLOR{BLUE=9, GREEN=10, RED=12, YELLOW=14};

int *playerColor;
const int BOARDSIZE = 100;
int NUMPLAYERS;

using namespace std;

HANDLE console = GetStdHandle (STD_OUTPUT_HANDLE);

struct player
{
    int position;
};

player *players;

struct BoardSquare
{
    int ChutePos;
    int LadderPos;
    int posValue;
};

struct BoardSquare Board[BOARDSIZE];

void initBoard()
{
    for(int i=0; i<BOARDSIZE; i++)
    {
        Board[i].ChutePos = Board[i].LadderPos = Board[i].posValue = -1;
    }

    Board[0].LadderPos = 37;
    Board[3].LadderPos = 13;
    Board[8].LadderPos = 30;
    Board[20].LadderPos = 41;
    Board[27].LadderPos = 83;
    Board[35].LadderPos = 43;
    Board[50].LadderPos = 66;
    Board[70].LadderPos = 90;
    Board[79].LadderPos = 99;

    Board[97].ChutePos = 77;
    Board[94].ChutePos = 74;
    Board[92].ChutePos = 72;
    Board[86].ChutePos = 23;
    Board[63].ChutePos = 59;
    Board[61].ChutePos = 18;
    Board[55].ChutePos = 52;
    Board[48].ChutePos = 10;
    Board[46].ChutePos = 25;
    Board[15].ChutePos = 5;
}

void initPlayer(int numPlayers)
{
    NUMPLAYERS = numPlayers;
    players = new struct player[NUMPLAYERS];
    playerColor = new int[NUMPLAYERS];
    for (int i=0; i<NUMPLAYERS; i++)
    {
        players[i].position = -1;
        switch(i)
        {
            case 0: playerColor[i] = BLUE;
                    break;
            case 1: playerColor[i] = GREEN;
                    break;
            case 2: playerColor[i] = YELLOW;
                    break;
            case 3: playerColor[i] = RED;
                    break;
        }
    }
}

void displayBoard()
{
    int bPos = BOARDSIZE-1;
    int topNumber = 0;
    for (int i=0; i<10; i++)
    {
        if((i&1)==0)
        {
            //printing the top number
            topNumber = bPos;
            for (int j = 0; j < 10; ++j)
            {
                if ((topNumber-10) < 0)
                    cout << "   " << topNumber << "   ";
                cout << "   " << topNumber << "  ";
                topNumber--;
            }
            cout << endl << endl;
            for(int j=0; j<10; j++)
            {
                if (Board[bPos].posValue == -1)
                {
                    //if there is a ladder
                    if (Board[bPos].LadderPos > 0)
                    {
                        cout << "|__L__|";
                    }
                    //if there is a chute
                    else if (Board[bPos].ChutePos > 0)
                    {
                        cout<<"|__C__|";
                    }

                    else
                        cout<<"|_____|";
                }
                //displaying the player occuping the square
                else
                {
                    cout << "|";
                    int spaceLeft = NUMINNERSPACE;
                    for (int k = 0;k < NUMPLAYERS; k++)
                    {
                        if (players[k].position == bPos)
                        {
                            SetConsoleTextAttribute(console,playerColor[k]);
                            cout << k;
                            spaceLeft--;
                        }
                    }
                    SetConsoleTextAttribute(console,15);
                    for (int k = 0; k < spaceLeft; k++)
                        cout << "_";
                    cout << "|";
                }
                bPos--;
            }
        }

        else
        {
            topNumber = bPos;
            for (int j = topNumber-9; j <= topNumber; ++j)
            {
                if ((j-10) < 0)
                    cout << "   " << j << "   ";
                else cout << "   " << j << "  ";
            }
            cout << endl << endl;
            for(int j=bPos-9; j<=bPos; j++)
            {
                if (Board[j].posValue == -1)
                {
                    if (Board[j].LadderPos > 0)
                    {
                        cout << "|__L__|";
                    }

                    else if (Board[j].ChutePos > 0)
                    {
                        cout<<"|__C__|";
                    }

                    else
                        cout<<"|_____|";
                }

                else
                {
                    cout << "|";
                    int spaceLeft = NUMINNERSPACE;
                    for (int k = 0;k < NUMPLAYERS; k++)
                    {
                        if (players[k].position == j)
                        {
                            SetConsoleTextAttribute(console,playerColor[k]);
                            cout << k;
                            spaceLeft--;
                        }
                    }
                    SetConsoleTextAttribute(console, 15);
                    for (int k = 0; k < spaceLeft; k++)
                        cout << "_";
                    cout << "|";
                }
            }

            bPos -= 10;
        }
        cout<<endl;
    }
}

int DiceRoll()
{
    int SideRolled = (rand() % 6) + 1;
    return SideRolled;
}

void runGame()
{
    int count = 0;
    int diceNum;
    while(Board[BOARDSIZE-1].posValue == -1)
    {
        cout<<endl<<"Player "<<count<<" turn. Press enter to roll... ";
        char c;
        while((c = cin.get()) != '\n'){}
        diceNum = DiceRoll();
        cout<<"You rolled a "<<diceNum<<"."<<endl;
        //if there are multiple players on the same spot
        int sameSpotCount = 0;
        //check all the players except the one just rolled
        bool goout = false;
        for (int l = 0; l < NUMPLAYERS; l++)
        {
            for (int m = l+1; m < NUMPLAYERS; m++)
            {
                if (players[l].position == players[m].position)
                {
                    goout = true;
                }

            }
        }

        if (goout == false)
            Board[players[count].position].posValue = -1;      //clear the old position

        players[count].position += diceNum;
        if(players[count].position > BOARDSIZE-1)
        {
            players[count].position = BOARDSIZE-1;
        }
        int tempPos = players[count].position;      //player current position
        Board[tempPos].posValue = count;
        cout<<"Player "<<count<<" position is "<<tempPos<<"."<<endl;
        cout<<"Press enter to conintue."<<endl;
        //waits for the enter key
        while((c = cin.get()) != '\n'){}
        //checking for ladder and chutes
        if (Board[tempPos].LadderPos > 0)
        {
            Board[tempPos].posValue = -1;           //reset the current position
            Board[Board[tempPos].LadderPos].posValue = count;  //mark the end ladder = player number
            players[count].position = Board[tempPos].LadderPos;
            cout<<"Climb the ladder to "<<players[count].position<<endl;
            cout<<"Press enter to conintue.";
            //waits for the enter key
            while((c = cin.get()) != '\n'){}
        }

        else if (Board[tempPos].ChutePos > 0)
        {
            Board[tempPos].posValue = -1;
            Board[Board[tempPos].ChutePos].posValue = count;
            players[count].position = Board[tempPos].ChutePos;
            cout<<"You fell down the chute to "<<players[count].position<<endl;
            cout<<"Press enter to conintue.";
            //waits for the enter key
            while((c = cin.get()) != '\n'){}
        }

        system("CLS");
        displayBoard();
        count++;
        if (count == NUMPLAYERS)
        {
            count = 0;
        }
    }

    cout<<endl<<"Player "<<Board[BOARDSIZE-1].posValue<<" wins!!!"<<endl;
}

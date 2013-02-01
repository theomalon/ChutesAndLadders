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
#define NUMINNERSPACE 5

const int BOARDSIZE = 100;
int NUMPLAYERS;

using namespace std;

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
    for (int i=0; i<NUMPLAYERS; i++)
    {
        players[i].position = -1;
    }
}

void displayBoard()
{
    int bPos = BOARDSIZE-1;
    for (int i=0; i<10; i++)
    {
        if((i&1)==0)
        {
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
                    for (int k = 0;k < NUMPLAYERS; ++k)
                    {
                        if (players[k].position == bPos)
                        {
                            cout << k;
                            spaceLeft--;
                        }
                    }
                    for (int k = 0; k < spaceLeft; k++)
                        cout << "_";
                    cout << "|";
                    //cout<<Board[bPos].posValue;
                }
                bPos--;
            }
        }

        else
        {
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
                    for (int k = 0;k < NUMPLAYERS; ++k)
                    {
                        if (players[k].position == j)
                        {
                            cout << k;
                            spaceLeft--;
                        }
                    }
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
    int count = 0
    ;
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
        for (int l = 0; l < NUMPLAYERS; ++l)
        {
            for (int m = l+1; m < NUMPLAYERS; ++m)
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

/*******************************
Name: Chris Malon
Date: 1/31/13
Description: Chutes and Ladders
*******************************/

#include <iostream>
#define BOARDSIZE 100

using namespace std;

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

void displayBoard()
{
    int bPos = BOARDSIZE-1;
    for (int i=0; i<10; i++)
    {
        if((i &1)==0)
        {
            for(int j=0; j<10; j++)
            {
                if (Board[bPos--].posValue == -1)
                {
                    cout<<"-";
                }

                else
                {
                    cout<<Board[bPos--].posValue;
                }
            }
        }

        else
        {
            for(int j=bPos-10; j<bPos; j++)
            {
                if (Board[bPos].posValue == -1)
                {
                    cout<<"-";
                }

                else
                {
                    cout<<Board[bPos].posValue;
                }
            }

            bPos -= 10;
        }
        cout<<endl;
    }
}

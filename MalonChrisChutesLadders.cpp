#include<iomanip>
#include<iostream>
#include<cstdlib>
#include<cmath>
#include<ctime>

using namespace std;
const int rows=10;
const int cols=10;
void createBoard(int board[rows][cols]);
void displayBoard(int board[rows][cols]);
void runGame(int board[rows][cols]);
int CheckChutesandLadders(int);
int DiceRoll();

int main()
{
    srand(time(NULL));
    int board[rows][cols];

    cout<<"Chutes and Ladders "<<endl;
    cout<<"Welcome!!! Get ready to play! First to 100 wins!"<<endl<<endl;
    cout<<endl<<"Player1 is up. Press Enter to Roll..."<<endl<<endl;

    createBoard(board);
    runGame(board);

    return 0;
}

int DiceRoll()
{
    int SideRolled = (rand() % 6) + 1;
    return SideRolled;
}

void createBoard(int board[rows][cols])
{
    int r, c;
    for (r=0; r<rows; r++)
      for (c=0; c<cols; c++)
        board [r][c]=0;
}

void displayBoard(int board[rows][cols])
{
    int r, c;
    for (r=0; r<rows; r++)
    {
        for (c=0; c<cols; c++)
            cout<<board[r][c];
            cout << endl;
    }
}

void runGame(int board[rows][cols])
{
    int dicenum;
    int player1 = 0;
    int player2 = 0;
    int player1rolls = 0;
    int player2rolls = 0;
    int rowIndex, colIndex;

    displayBoard(board);
    cin.get();

    do
    {
        system("CLS");
        rowIndex = (player1rolls - 1)/rows;
        colIndex = (player1rolls - 1)%cols;
        board[rowIndex][colIndex] = 0;
        dicenum = DiceRoll();
        player1 = player1 + dicenum;
        cout<<"Player1 rolled a "<<dicenum<<"! ";
        player1 = CheckChutesandLadders(player1);
        cout<<"Your position is "<<player1<<". "<<endl<<endl;

        player1rolls++;
        cout<<"Player2's turn. Press Enter to roll..."<<endl<<endl;

        rowIndex = (player1 - 1)/rows;
        colIndex = (player1 - 1)%cols;
        board[rowIndex][colIndex] = 1;

        displayBoard(board);
        cin.get();

        if(player1 >= 100)
            player1 = player1 + 0;

        else
        {
            system("CLS");
            rowIndex = (player2rolls - 1)/rows;
            colIndex = (player2rolls - 1)%cols;
            board[rowIndex][colIndex] = 0;
            dicenum = DiceRoll();
            player2 = player2 + dicenum;
            cout<<"Player2 rolled a "<<dicenum<<"! ";
            player2 = CheckChutesandLadders(player2);
            cout<<"Your position is "<<player2<<". "<<endl<<endl;

            player2rolls++;
            cout<<"Player1's turn. Press Enter to roll..."<<endl<<endl;

            rowIndex = (player2 - 1)/rows;
            colIndex = (player2 - 1)%cols;
            board[rowIndex][colIndex] = 2;

            displayBoard(board);
            cin.get();

            if(player2 >= 100)
            player2 = player2 + 0;
        }
    }while(player1<100 && player2<100);

    if(player2>=100)
    {
        cout<<"Player2 wins! Congratulations!"<<endl;
    }
    else
    {
        cout<<"Player1 wins! Congratulations!"<<endl;
    }
}

int CheckChutesandLadders(int player)
{
    if(player == 1)
    {
        cout<<"Climb the ladder to 38!"<<endl;
        return player = 38;
    }
    else if(player == 4)
    {
        cout<<"Climb the ladder to 14!"<<endl;
        return player = 14;
    }
    else if(player == 9)
    {
        cout<<"Climb the ladder to 31!"<<endl;
        return player = 31;
    }
    else if(player == 16)
    {
        cout<<"You fell down a chute to 6 :("<<endl;
        return player = 6;
    }
    else if(player == 28)
    {
        cout<<"Climb the ladder to 84!"<<endl;
        return player = 84;
    }
    else if(player == 36)
    {
        cout<<"Climb the ladder to 44!"<<endl;
        return player = 44;
    }
    else if(player == 47)
    {
        cout<<"You fell down a chute to 26 :("<<endl;
        return player = 26;
    }
    else if(player == 49)
    {
        cout<<"You fell down a chute to 11 :("<<endl;
        return player = 11;
    }
    else if(player == 56)
    {
        cout<<"You fell down a chute to 53 :("<<endl;
        return player = 53;
    }
    else if(player == 62)
    {
        cout<<"You fell down a chute to 19 :("<<endl;
        return player = 19;
    }
    else if(player == 64)
    {
        cout<<"You fell down a chute to 19 :("<<endl;
        return player = 60;
    }
    else if(player == 71)
    {
        cout<<"Climb the ladder to 91!"<<endl;
        return player = 91;
    }
    else if(player == 80)
    {
        cout<<"Climb the ladder to 100!"<<endl;
        return player = 100;
    }
    else if(player == 93)
    {
        cout<<"You fell down a chute to 73 :("<<endl;
        return player = 73;
    }
    else if(player == 95)
    {
        cout<<"You fell down a chute to 75 :("<<endl;
        return player = 75;
    }
    else if(player == 98)
    {
        cout<<"You fell down a chute to 78 :("<<endl;
        return player = 78;
    }
    else
        return player;
}

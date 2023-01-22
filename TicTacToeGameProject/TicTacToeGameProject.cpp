#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include<ctype.h>

char board[3][3]; //global variables, no ptrs, 2d array of chars named board
const char PLAYER = 'X';
const char COMPUTER = 'O';

void resetBoard(); //2d character array
void printBoard(); //prints our 2d character
int checkFreeSpaces(); //return type event, if this function return zero, that means the game is over, no more places to move
void playerMove(); //player's turn to move
void computerMove(); //when it's the computer's turn to move
char checkWinner(); //different win conditions to check 
void printWinner(char); //print the winner, one single character char

int main()
{
	char winner = ' '; //declare a local variable, if winner is empty space, there's no winner
	//char response = ' ';
	char newGame;

	do
	{
		winner = ' '; //reset winner
		//response = ' '; reset response
		resetBoard();

		while (winner == ' ' && checkFreeSpaces() != 0) //if it is an empty space, that means there's no winner
		{
			printBoard();

			playerMove();

			//check to see if there's a winner


			winner = checkWinner();
			if (winner != ' ' || checkFreeSpaces() == 0)
			{
				break; //ima winner-a
			}

			computerMove();
			winner = checkWinner();
			if (winner != ' ' || checkFreeSpaces() == 0)
			{
				break; //ima winner-a
			}
		}

		printBoard();
		printWinner(winner);

		printf("\nWould you like to play again? (Y/N): ");
		//scanf_s("%c"); if there's a new line charachter within our buffer
		
		scanf_s(" %c", &newGame, 1); //accept a character after clearing our buffer
		newGame = toupper(newGame); // malo y, isto ide yes
	} while (newGame == 'Y');

	printf("Thanks for playing!");

	return 0;
}

void resetBoard() //2d character array
{
	//initialize all the special chars within our board

	for (int i = 0; i < 3; i++) //iterate 3 times, one for each row that we have, redovi
	{
		for (int j = 0; j < 3; j++) //kolone
		{
			board[i][j] = ' '; //when we call reset, there will be an empty space
		}
	}
}
void printBoard() //prints our 2d character
{
	printf(" %c | %c | %c ", board[0][0], board[0][1], board[0][2]); //format specifiers, placeholders, red nula, kolona nula, red nula, kolona jedan...
	printf("\n---|---|---\n");
	printf(" %c | %c | %c ", board[1][0], board[1][1], board[1][2]);
	printf("\n---|---|---\n");
	printf(" %c | %c | %c ", board[2][0], board[2][1], board[2][2]);
	printf("\n");
}
int checkFreeSpaces() //return type event, if this function return zero, that means the game is over, no more places to move 
{
	//local variable
	int freeSpaces = 9;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (board[i][j] != ' ') //if whatever spot that we are on is currently occupied, we'll take
			{
				freeSpaces--;
			}
		}
	}
	return freeSpaces; //if returned zero, that means there's no more places a player can move
}
void playerMove() //player's turn to move 
{
	int x;
	int y;

	do
	{
		printf("Enter row #(1-3): ");
		scanf_s("%d", &x);
		x--; //this gives us rows zero through 2 
		printf("Enter column #(1-3): ");
		scanf_s("%d", &y);
		y--;

		//we'll check if the coordinates that the user gave are occupied or not
		if (board[x][y] != ' ')
		{
			printf("Invalid move!\n");
		}
		else
		{
			board[x][y] = PLAYER;
			break;
		}
	} while (board[x][y] != ' '); //if space is occupied, ask again for coordinates

}
void computerMove() //when it's the computer's turn to move 
{
	//creates a seed based on current time
	srand((unsigned int)time(0)); //random numbers
	int x;
	int y;

	if (checkFreeSpaces() > 0)
	{
		do
		{
			x = rand() % 3;
			y = rand() % 3; //we will keep generating a random number until there's an open space 
		} while (board[x][y] != ' ');

		//if we find an open space

		board[x][y] = COMPUTER;
	}
	else
	{
		printWinner(' '); //this means that there's no winner, that's a draw
	}
}
char checkWinner() //different win conditions to check 
{
	//check rows, this for function will check all of the win conditions for each row
	for (int i = 0; i < 3; i++)
	{
		if (board[i][0] == board[i][1] && board[i][0] == board[i][2]) //top left element
		{
			return board[i][0];
		}
	}
	//check columns
	for (int i = 0; i < 3; i++)
	{
		if (board[0][i] == board[1][i] && board[0][i] == board[2][i])
		{
			return board[0][i];
		}
	}
	//check diagonals
	if (board[0][0] == board[1][1] && board[0][0] == board[2][2])
	{
		return board[0][0];
	}
	if (board[0][2] == board[1][1] && board[0][2] == board[2][0])
	{
		return board[0][2];
	}

	return ' '; //if there's no winner, return an empty char
}
void printWinner(char winner) //print the winner, one single character char 
{
	if (winner == PLAYER)
	{
		printf("YOU WIN!");
	}
	else if (winner == COMPUTER)
	{
		printf("YOU LOSE!");
	}
	else {
		printf("IT'S A TIE!");
	}
}
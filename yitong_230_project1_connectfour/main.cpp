#include<iostream>
#include<string>
#include<cstdlib>
#include<Windows.h>
using namespace std;

void StartGame();
void InsertPiece();
bool IsWon();
void SwitchPlayer();
void EndGame();
bool IsTie();
void RestartGame();
void GameSetUp();
bool IsWonSSS();

int rows, columns, num;
int top[20];
string board[20][20];
bool isPlayerOne = true;
int newx, newy;
bool stopGame = false;
bool columnFull[20];
bool restartGame = true;
bool wrap = true;

int main() {
	system("color 1f");
	
	do {
		GameSetUp();
		StartGame();
		do {
			InsertPiece();
			if (wrap == false) {
				IsWon();
			}
			else {
				cout << "hello world";
				IsWonSSS();
			}
			EndGame();
			SwitchPlayer();
		} while (stopGame == false);
		RestartGame();
	} while (restartGame == true);
	
	cout << endl;
	system("pause");
	return 0;
}

void GameSetUp() {
	bool keepAsk = false;
	do {
		cout << "How many rows do you want (4-20)?" << endl;
		cin >> rows;
		keepAsk = false;
		if (rows > 20 || rows < 4) {
			cout << "Please select from 4 to 20." << endl;
			keepAsk = true;
		}
	} while (keepAsk == true);
	do {
		cout << "How many columns do you want (4-20)?" << endl;
		cin >> columns;
		keepAsk = false;
		if (columns > 20 || columns < 4) {
			cout << "Please select from 4 to 20." << endl;
			keepAsk = true;
		}
	} while (keepAsk == true);
	do {
		cout << "How many linked pieces do you require to win (3-20)?" << endl;
		cin >> num;
		keepAsk = false;
		if (num > 20 || num < 3) {
			cout << "Please select from 3 to 20." << endl;
			keepAsk = true;
		}
	} while (keepAsk == true);
	do {
		cout << "Do you want to enable Wrap Around Mode (y/n)?" << endl;
		char yn;
		cin >> yn;
		keepAsk = false;
		if (yn == 'Y' || yn == 'y') {
			wrap = true;
		}
		else {
			cout << "Please input y or n." << endl;
			keepAsk = true;
		}
	} while (keepAsk == true);
	system("cls");
}

void StartGame() {
	for (int n = 1; n <= columns; n++) {
		cout << " " << n;
	}
	cout << endl;
	for (int i = 0; i < rows; i++) {
		cout << "|";
		for (int j = 0; j < columns; j++) {
			board[i][j] = ".";
			cout << board[i][j] << "|";
		}
		cout << endl;
	}
	for (int t = 0; t < columns; t++) {
		top[t] = 0;
	}
	for (int c = 0; c < columns; c++) {
		columnFull[c] = false;
	}
	isPlayerOne = true;
	stopGame = false;
}

void InsertPiece() {
	if (isPlayerOne == true) {
		cout << "Player X's turn! Type the column number to insert a piece." << endl;
	}
	else {
		cout << "Player O's turn! Type the column number to insert a piece." << endl;
	}
	int input, s;
	bool stopSelect = false;
	do {
		cin >> input;
		system("cls");
		s = input - 1;
		if (s >= 0 && s < columns && columnFull[s] == false) {
			for (int n = 1; n <= columns; n++) {
				cout << " " << n;
			}
			cout << endl;
			for (int i = 0; i < rows; i++) {
				cout << "|";
				for (int j = 0; j < columns; j++) {
					if (i == rows-1-top[s] && j == s) {
						if (isPlayerOne == true) {
							board[i][j] = "X";
						}
						else {
							board[i][j] = "O";
						}
						cout << board[i][j] << "|";
						newx = j;
						newy = i;
					}
					else {
						cout << board[i][j] << "|";
					}
				}
				cout << endl;
			}
			top[s] += 1;
			if (top[s] == rows) {
				columnFull[s] = true;
			}
			stopSelect = true;
		}
		else if (s >= 0 && s <= columns && columnFull[s] == true) {
			for (int n = 1; n <= columns; n++) {
				cout << " " << n;
			}
			cout << endl;
			for (int i = 0; i < rows; i++) {
				cout << "|";
				for (int j = 0; j < columns; j++) {
					if (i == rows-1-top[s] && j == s) {
						if (isPlayerOne == true) {
							board[i][j] = "X";
						}
						else {
							board[i][j] = "O";
						}
						cout << board[i][j] << "|";
						newx = j;
						newy = i;
					}
					else {
						cout << board[i][j] << "|";
					}
				}
				cout << endl;
			}
			cout << "No." << input << " line is already full." << endl;
			cout << "Please select another number from 1 to 7." << endl;
		}
		else if (input == 999) {    //testing, force to exist
			stopSelect = true;
			stopGame = true;;
		}
		else {
			for (int n = 1; n <= columns; n++) {
				cout << " " << n;
			}
			cout << endl;
			for (int i = 0; i < rows; i++) {
				cout << "|";
				for (int j = 0; j < columns; j++) {
					if (i == rows-1-top[s] && j == s) {
						if (isPlayerOne == true) {
							board[i][j] = "X";
						}
						else {
							board[i][j] = "O";
						}
						cout << board[i][j] << "|";
						newx = j;
						newy = i;
					}
					else {
						cout << board[i][j] << "|";
					}
				}
				cout << endl;
			}
			cout << "Please select a number between 1 to 7." << endl;
		}
	} while (stopSelect == false);
}

bool IsWon() {
	int count = 0;
	int winflag = 1;
	string cur ;
	int i, j;
	cur = isPlayerOne == true ? 'X' : 'O';
	
	for (i = newx - 1, j = newy; i >= 0 && count++ < num; i--)
	{
		if (board[j][i] == cur) {
			winflag++;
		}
		else
			break;
	}
	count = 0;
	for (i = newx + 1, j = newy; i < rows && count++ < num; i++) {
		if (board[j][i] == cur)
			winflag++;
		else
			break;
	}
	count = 0;
	if( winflag >= num )
		return true;
	else		
		winflag = 1;
	
	for(i = newx,j = newy + 1; j < columns && count ++ < num ; j ++ )	{		
		if(board[j][i] == cur) 			
			winflag++;		
		else 			
			break;
	}	
	count = 0;
	for(i = newx, j = newy - 1; j >= 0 && count++ < num ; j --)	{
		if(board[j][i] == cur) 			
			winflag++;		
		else 			
			break;
	}	
	count = 0;
	if( winflag >= num )
		return true;	
	else		
		winflag = 1;

	for(i = newx + 1,j = newy + 1; i < rows && j < columns && count ++ < num ; i ++ ,j ++)	{		
		if(board[j][i] == cur) 			
			winflag++;		
		else 			
			break;
	}	
	count = 0;	
	for(i = newx - 1,j = newy - 1; i >= 0 && j >= 0 && count++ < num ; i -- ,j --)	{		
		if(board[j][i] == cur) 			
			winflag++;		
		else 			
			break;
	}	
	count = 0;	
	if( winflag >= num )
		return true;
	else		
		winflag = 1;

	for(i = newx -1,j = newy + 1; i >= 0 && j < columns && count++ < num; i --,j++)	{		
		if(board[j][i] == cur) 			
			winflag++;		
		else 			
			break;
	}	
	count = 0;	
	for(i = newx + 1,j = newy -1; i < rows && newy >= 0 && count++ < num; i ++,j--)	{		
		if(board[j][i] == cur) 			
			winflag++;		
		else 			
			break;
	}	
	count = 0;
	if( winflag >= num )
		return true;
	else		
		winflag = 1;

	return false;
}

bool IsWonSSS() {
	int count = 0;
	int winflag = 1;
	string cur;
	int i, j, m, n;
	cur = isPlayerOne == true ? 'X' : 'O';

	//left or right
	//left
	if (newx == 0) {
		for (m = columns - 1, n = newy; m > newx && count++ < num; m--) {
			if (board[n][m] == cur) {
				winflag++;
			}
			else {
				break;
			}
		}
	}
	else {
		for (i = newx - 1, j = newy; i >= 0 && count++ < num; i--)
		{
			if (i == 0 && board[j][i] == cur) {
				winflag++;
				for (m = columns - 1, n = newy; m > newx && count++ < num; m--) {
					if (board[n][m] == cur) {
						winflag++;
					}
					else {
						break;
					}
				}
			}
			else if (i != 0 && board[j][i] == cur) {
				winflag++;
			}
			else {
				break;
			}
		}
	}
	count = 0;
	//right
	if (newx == columns - 1) {
		for (m = 0, n = newy; m < newx && count++ < num; m++) {
			if (board[n][m] == cur) {
				winflag++;
			}
			else {
				break;
			}
		}
	}
	else {
		for (i = newx + 1, j = newy; i < rows && count++ < num; i++) {
			if (i == columns - 1 && board[j][i] == cur) {
				winflag++;
				for (m = columns - 1, n = newy; m > newx && count++ < num; m--) {
					if (board[n][m] == cur) {
						winflag++;
					}
					else {
						break;
					}
				}
			}
			else if (i != columns - 1 && board[j][i] == cur) {
				winflag++;
			}
			else {
				break;
			}
		}
	}
	count = 0;
	if (winflag >= num) {
		return true;
	}
	else {
		winflag = 1;
	}
	
	//up or down
	for (i = newx, j = newy + 1; j < columns && count++ < num; j++) {
		if (board[j][i] == cur) {
			winflag++;
		}
		else {
			break;
		}
	}
	count = 0;
	for (i = newx, j = newy - 1; j >= 0 && count++ < num; j--) {
		if (board[j][i] == cur) {
			winflag++;
		}
		else {
			break;
		}
	}
	count = 0;
	if (winflag >= num) {
		return true;
	}
	else {
		winflag = 1;
	}

	//down-right or up-left
	//down-right
	if (newx == columns - 1) {
		for (m = 0, n = newy + 1; m < newx && n < columns && count++ < num; m++, n++) {
			if (board[n][m] == cur) {
				winflag++;
			}
			else {
				break;
			}
		}
	}
	else {
		for (i = newx + 1, j = newy + 1; i < rows && j < columns && count++ < num; i++, j++) {
			if (i == columns - 1 && board[j][i] == cur) {
				winflag++;
				for (m = 0, n = newy + 1; m < newx && n < columns && count++ < num; m++, n++) {
					if (board[n][m] == cur) {
						winflag++;
					}
					else {
						break;
					}
				}
			}
			else if (i != columns - 1 && board[j][i] == cur) {
				winflag++;
			}
			else {
				break;
			}
		}
	}
	count = 0;
	//up-left
	if (newx == 0) {
		for (m = columns - 1, n = newy - 1; m > newx && n>= 0 && count++ < num; m--, n--) {
			if (board[n][m] == cur) {
				winflag++;
			}
			else {
				break;
			}
		}
	}
	else {
		for (i = newx - 1, j = newy - 1; i >= 0 && j >= 0 && count++ < num; i--, j--)
		{
			if (i == 0 && board[j][i] == cur) {
				winflag++;
				for (m = columns - 1, n = newy - 1; m > newx && n >= 0 && count++ < num; m--, n--) {
					if (board[n][m] == cur) {
						winflag++;
					}
					else {
						break;
					}
				}
			}
			else if (i != 0 && board[j][i] == cur) {
				winflag++;
			}
			else {
				break;
			}
		}
	}
	count = 0;
	if (winflag >= num) {
		return true;
	}
	else {
		winflag = 1;
	}

	//down-left or up-right
	//down-left
	if (newx == 0) {
		for (m = columns - 1, n = newy + 1; m > newx && n < columns && count++ < num; m--, n++) {
			if (board[n][m] == cur) {
				winflag++;
			}
			else {
				break;
			}
		}
	}
	else {
		for (i = newx - 1, j = newy + 1; i >= 0 && j < columns && count++ < num; i--, j++)
		{
			if (i == 0 && board[j][i] == cur) {
				winflag++;
				for (m = columns - 1, n = newy + 1; m > newx && n < columns && count++ < num; m--, n++) {
					if (board[n][m] == cur) {
						winflag++;
					}
					else {
						break;
					}
				}
			}
			else if (i != 0 && board[j][i] == cur) {
				winflag++;
			}
			else {
				break;
			}
		}
	}
	count = 0;
	//up-right
	if (newx == columns - 1) {
		for (m = 0, n = newy - 1; m < newx && n >= 0 && count++ < num; m++, n--) {
			if (board[n][m] == cur) {
				winflag++;
			}
			else {
				break;
			}
		}
	}
	else {
		for (i = newx + 1, j = newy - 1; i < rows && newy >= 0 && count++ < num; i++, j--) {
			if (i == columns - 1 && board[j][i] == cur) {
				winflag++;
				for (m = 0, n = newy - 1; m < newx && n >= 0 && count++ < num; m++, n--) {
					if (board[n][m] == cur) {
						winflag++;
					}
					else {
						break;
					}
				}
			}
			else if (i != columns - 1 && board[j][i] == cur) {
				winflag++;
			}
			else {
				break;
			}
		}
	}
	count = 0;
	if (winflag >= num) {
		return true;
	}
	else {
		winflag = 1;
	}
	return false;
}

void SwitchPlayer() {
	if (isPlayerOne) {
		isPlayerOne = false;
	}
	else {
		isPlayerOne = true;
	}
}

bool IsTie() {
	int fullLine = 0;
	for (int i = 0; i < columns; i++) {
		if (top[i] == rows) {
			fullLine += 1;
		}
	}
	if (fullLine == columns) {
		return true;
	}
}

void EndGame() {
	if (IsTie() == true) {
		cout << "The game ended in a draw." << endl;
		stopGame = true;
	}
	else 
		if (IsWon() == true || IsWonSSS() == true) {
		if (isPlayerOne) {
			cout << "Player X won!" << endl;
			stopGame = true;
		}
		else {
			cout << "Player O won!" << endl;
			stopGame = true;
		}
	}
}

void RestartGame() {
	cout << "Do you want to play Connect Four again?" << endl;
	cout << "If yes press 'Y'," << endl;
	cout << "If no press 'N'." << endl;
	char choose;
	bool keepAsk = true;
	do {
		cin >> choose;
		if (choose == 'Y' || choose == 'y') {
			restartGame = true;
			system("cls");
			keepAsk = false;
		}
		else if (choose == 'N' || choose == 'n') {
			cout << "See you next time!" << endl;
			restartGame = false;
			keepAsk = false;
		}
		else {
			cout << "Please choose yes or no." << endl;
			keepAsk = true;
		}
	} while (keepAsk == true);
	
}
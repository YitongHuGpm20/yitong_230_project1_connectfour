#include<iostream>
#include<string>
#include<limits>
using namespace std;

void GameSetUp();
void StartGame();
void InsertOrRemove();
void IsWon();
void IsWonWrap();
void IsTie();
void WonRecord();
void StopGame();
void SwitchPlayer();
void RestartGame();

int rows, columns, num;
int top[20];
char board[20][20];
bool columnFull[20];
int newx, newy;
int keepNewX, keepNewY;
bool isPlayerOne = true;
bool isWon = false;
bool isWonWrap = false;
bool isTie = false;
bool stopGame = false;
bool restartGame = true;
bool wrap = false;
bool drop = false;
bool checkDone = false;
int xWon = 0, oWon = 0;

int main() {
	system("color 1f");
	do {
		GameSetUp();
		StartGame();
		do {
			InsertOrRemove();
			StopGame();
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
		if (yn == 'Y' || yn == 'y')
			wrap = true;
		else if (yn == 'N' || yn == 'n')
			wrap = false;
		else {
			cout << "Please input y or n." << endl;
			keepAsk = true;
		}
	} while (keepAsk == true);
	do {
		cout << "Do you want to enable Remove Bottom Mode (y/n)?" << endl;
		char yn;
		cin >> yn;
		keepAsk = false;
		if (yn == 'Y' || yn == 'y')
			drop = true;
		else if (yn == 'N' || yn == 'n')
			drop = false;
		else {
			cout << "Please input y or n." << endl;
			keepAsk = true;
		}
	} while (keepAsk == true);
	system("cls");
}

void StartGame() { 
	for (int n = 1; n <= columns; n++)
		cout << ' ' << n;
	cout << endl;
	for (int i = 0; i < rows; i++) {
		cout << '|';
		for (int j = 0; j < columns; j++) {
			board[i][j] = '.';
			cout << board[i][j] << '|';
		}
		cout << endl;
	}
	for (int t = 0; t < columns; t++)
		top[t] = 0;
	for (int c = 0; c < columns; c++)
		columnFull[c] = false;
	isPlayerOne = true;
	stopGame = false;
	isWon = false;
	isWonWrap = false;
	isTie = false;
	xWon = 0;
	oWon = 0;
}

void InsertOrRemove() {
	if (isPlayerOne == true) {
		cout << "Player X's turn! Type the column number to insert or remove a piece." << endl;
	}
	else {
		cout << "Player O's turn! Type the column number to insert or remove a piece." << endl;
	}
	int input, s;
	bool stopSelect = false;
	char cur;
	cur = isPlayerOne == true ? 'X' : 'O';
	int checkInput;
	bool validInput = false;
	do {
		cin >> input;
		while (!cin.good()) { //to avoid user input letters or words
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Please try again." << endl;
			cin >> input;
		}
		cin.ignore(10000, '\n');
		system("cls");
		s = input - 1;
		if (drop == true && board[rows - 1][s] == cur) { //Remove Mode on
			for (int n = 1; n <= columns; n++) {
				cout << ' ' << n;
			}
			cout << endl;
			for (int i = 0; i < rows; i++) {
				cout << '|';
				for (int j = 0; j < columns; j++) {
					cout << board[i][j] << '|';
				}
				cout << endl;
			}
			cout << "If you want to insert a piece on the top, type 'A'." << endl;
			cout << "If you want to remove a piece from the bottom, type 'B'." << endl;
			char select;
			bool keepAsk = false;
			do {
				cin >> select;
				system("cls");
				keepAsk = false;
				if (select == 'A' || select == 'a') { //insert a piece on the top of that column
					if (s >= 0 && s < columns && columnFull[s] == false) {
						for (int n = 1; n <= columns; n++) {
							cout << ' ' << n;
						}
						cout << endl;
						for (int i = 0; i < rows; i++) {
							cout << '|';
							for (int j = 0; j < columns; j++) {
								if (i == rows - 1 - top[s] && j == s) {
									if (isPlayerOne == true)
										board[i][j] = 'X';
									else
										board[i][j] = 'O';
									cout << board[i][j] << '|';
									newx = j;
									newy = i;
								}
								else
									cout << board[i][j] << '|';
							}
							cout << endl;
						}
						top[s] += 1;
						if (top[s] == rows)
							columnFull[s] = true;
						stopSelect = true;
					}
					else if (s >= 0 && s <= columns && columnFull[s] == true) {
						for (int n = 1; n <= columns; n++) {
							cout << ' ' << n;
						}
						cout << endl;
						for (int i = 0; i < rows; i++) {
							cout << '|';
							for (int j = 0; j < columns; j++) {
								if (i == rows - 1 - top[s] && j == s) {
									if (isPlayerOne == true)
										board[i][j] = 'X';
									else
										board[i][j] = 'O';
									cout << board[i][j] << '|';
									newx = j;
									newy = i;
								}
								else
									cout << board[i][j] << '|';
							}
							cout << endl;
						}
						cout << "No." << input << " line is already full." << endl;
						cout << "Please select another number from 1 to " << rows << "." << endl;
					}
					else {
						for (int n = 1; n <= columns; n++) {
							cout << ' ' << n;
						}
						cout << endl;
						for (int i = 0; i < rows; i++) {
							cout << '|';
							for (int j = 0; j < columns; j++) {
								if (i == rows - 1 - top[s] && j == s) {
									if (isPlayerOne == true)
										board[i][j] = 'X';
									else
										board[i][j] = 'O';
									cout << board[i][j] << '|';
									newx = j;
									newy = i;
								}
								else
									cout << board[i][j] << '|';
							}
							cout << endl;
						}
						cout << "Please select a number between 1 to " << rows << "." << endl;
					}
					checkDone = true;
				}
				else if (select == 'B' || select == 'b') { //remove a piece from the bottom of that column
					for (int n = 1; n <= columns; n++) {
						cout << ' ' << n;
					}
					cout << endl;
					//that column drops down
					for (int i = rows - 1; i >= 0; i--) {
						if (i == 0)
							board[i][s] = '.';
						else
							board[i][s] = board[i - 1][s];
					}
					for (int i = 0; i < rows; i++) {
						cout << '|';
						for (int j = 0; j < columns; j++) {
							cout << board[i][j] << '|';
						}
						cout << endl;
					}
					newx = s;
					newy = rows - 1;
					top[s] -= 1;
					columnFull[s] = false;
					stopSelect = true;
				}
				else {
					keepAsk = true;
					cout << "Please type A or B." << endl;
				}
			} while (keepAsk == true);
		}
		else { //Remove Mode Off
			if (s >= 0 && s < columns && columnFull[s] == false) {
				for (int n = 1; n <= columns; n++) {
					cout << ' ' << n;
				}
				cout << endl;
				for (int i = 0; i < rows; i++) {
					cout << '|';
					for (int j = 0; j < columns; j++) {
						if (i == rows - 1 - top[s] && j == s) {
							if (isPlayerOne == true)
								board[i][j] = 'X';
							else
								board[i][j] = 'O';
							cout << board[i][j] << '|';
							newx = j;
							newy = i;
						}
						else
							cout << board[i][j] << '|';
					}
					cout << endl;
				}
				top[s] += 1;
				if (top[s] == rows)
					columnFull[s] = true;
				stopSelect = true;
			}
			else if (s >= 0 && s <= columns && columnFull[s] == true) {
				for (int n = 1; n <= columns; n++) {
					cout << ' ' << n;
				}
				cout << endl;
				for (int i = 0; i < rows; i++) {
					cout << '|';
					for (int j = 0; j < columns; j++) {
						if (i == rows - 1 - top[s] && j == s) {
							if (isPlayerOne == true)
								board[i][j] = 'X';
							else
								board[i][j] = 'O';
							cout << board[i][j] << '|';
							newx = j;
							newy = i;
						}
						else
							cout << board[i][j] << '|';
					}
					cout << endl;
				}
				cout << "No." << input << " line is already full." << endl;
				cout << "Please select a number between 1 to " << rows << "." << endl;
			}
			else {
				for (int n = 1; n <= columns; n++) {
					cout << ' ' << n;
				}
				cout << endl;
				for (int i = 0; i < rows; i++) {
					cout << '|';
					for (int j = 0; j < columns; j++) {
						if (i == rows - 1 - top[s] && j == s) {
							if (isPlayerOne == true)
								board[i][j] = 'X';
							else
								board[i][j] = 'O';
							cout << board[i][j] << '|';
							newx = j;
							newy = i;
						}
						else
							cout << board[i][j] << '|';
					}
					cout << endl;
				}
				cout << "Please select a number between 1 to " << rows << "." << endl;
			}
			checkDone = true;
		}
	} while (stopSelect == false);
	keepNewX = newx;
	keepNewY = newy;
	IsTie();
	for (int i = 1; i <= top[s]; i++) {
		if (newy >= rows - top[s]) {
			if (wrap == false)//Wrap Around Mode On/Off
				IsWon();
			else
				IsWonWrap();
			newy--;
			WonRecord();
		}
	}
}

void IsTie() {
	int fullLine = 0;
	for (int i = 0; i < columns; i++) {
		if (top[i] == rows)
			fullLine += 1;
	}
	if (fullLine == columns)
		isTie = true;
}

void IsWon() {
	int count = 0;
	int winflag = 1;
	char cur ;
	int i, j;
	cur = board[newy][newx] == 'X' ? 'X' : 'O';
	for (i = newx - 1, j = newy; i >= 0 && count++ < num; i--)
	{
		if (board[j][i] == cur)
			winflag++;
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
		isWon = true;
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
		isWon = true;	
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
		isWon = true;
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
		isWon = true;
	else		
		winflag = 1;
}

void IsWonWrap() {
	int count = 0;
	int winflag = 1;
	char cur;
	int i, j, m, n;
	cur = board[newy][newx] == 'X' ? 'X' : 'O';

	//left or right
	//left
	if (newx == 0) {
		for (m = columns - 1, n = newy; m > newx && count++ < num; m--) {
			if (board[n][m] == cur)
				winflag++;
			else
				break;
		}
	}
	else {
		for (i = newx - 1, j = newy; i >= 0 && count++ < num; i--)
		{
			if (i == 0 && board[j][i] == cur) {
				winflag++;
				for (m = columns - 1, n = newy; m > newx && count++ < num; m--) {
					if (board[n][m] == cur)
						winflag++;
					else
						break;
				}
			}
			else if (i != 0 && board[j][i] == cur)
				winflag++;
			else 
				break;
		}
	}
	count = 0;
	//right
	if (newx == columns - 1) {
		for (m = 0, n = newy; m < newx && count++ < num; m++) {
			if (board[n][m] == cur)
				winflag++;
			else
				break;
		}
	}
	else {
		for (i = newx + 1, j = newy; i < columns && count++ < num; i++) {
			if (i == columns - 1 && board[j][i] == cur) {
				winflag++;
				for (m = 0, n = newy; m < newx && count++ < num; m++) {
					if (board[n][m] == cur)
						winflag++;
					else
						break;
				}
			}
			else if (i != columns - 1 && board[j][i] == cur)
				winflag++;
			else
				break;
		}
	}
	count = 0;
	if (winflag >= num)
		isWonWrap = true;
	else
		winflag = 1;
	
	//up or down
	for (i = newx, j = newy + 1; j < rows && count++ < num; j++) {
		if (board[j][i] == cur)
			winflag++;
		else
			break;
	}
	count = 0;
	for (i = newx, j = newy - 1; j >= 0 && count++ < num; j--) {
		if (board[j][i] == cur)
			winflag++;
		else
			break;
	}
	count = 0;
	if (winflag >= num)
		isWonWrap = true;
	else
		winflag = 1;

	//down-right or up-left
	//down-right
	if (newx == columns - 1 && newy != rows - 1) {
		for (m = 0, n = newy + 1; m < newx && n < rows && count++ < num; m++, n++) {
			if (board[n][m] == cur)
				winflag++;
			else
				break;
		}
	}
	else {
		for (i = newx + 1, j = newy + 1; i < columns && j < rows && count++ < num; i++, j++) {
			if (i == columns - 1 && board[j][i] == cur && j != rows - 1) {
				winflag++;
				for (m = 0, n = j + 1; m < newx && n < rows && count++ < num; m++, n++) {
					if (board[n][m] == cur)
						winflag++;
					else
						break;
				}
			}
			else if (i != columns - 1 && board[j][i] == cur)
				winflag++;
			else
				break;
		}
	}
	count = 0;
	//up-left
	if (newx == 0 && newy != 0) {
		for (m = columns - 1, n = newy - 1; m > newx && n>= 0 && count++ < num; m--, n--) {
			if (board[n][m] == cur)
				winflag++;
			else
				break;
		}
	}
	else {
		for (i = newx - 1, j = newy - 1; i >= 0 && j >= 0 && count++ < num; i--, j--)
		{
			if (i == 0 && board[j][i] == cur && j != 0) {
				winflag++;
				for (m = columns - 1, n = j - 1; m > newx && n >= 0 && count++ < num; m--, n--) {
					if (board[n][m] == cur)
						winflag++;
					else
						break;
				}
			}
			else if (i != 0 && board[j][i] == cur)
				winflag++;
			else
				break;
		}
	}
	count = 0;
	if (winflag >= num)
		isWonWrap = true;
	else
		winflag = 1;

	//down-left or up-right
	//down-left
	if (newx == 0 && newy != rows - 1) {
		for (m = columns - 1, n = newy + 1; m > newx && n < rows && count++ < num; m--, n++) {
			if (board[n][m] == cur)
				winflag++;
			else
				break;
		}
	}
	else {
		for (i = newx - 1, j = newy + 1; i >= 0 && j < rows && count++ < num; i--, j++)
		{
			if (i == 0 && board[j][i] == cur && j != rows - 1) {
				winflag++;
				for (m = columns - 1, n = j + 1; m > newx && n < rows && count++ < num; m--, n++) {
					if (board[n][m] == cur)
						winflag++;
					else
						break;
				}
			}
			else if (i != 0 && board[j][i] == cur)
				winflag++;
			else
				break;
		}
	}
	count = 0;
	//up-right
	if (newx == columns - 1 && newy != 0) {
		for (m = 0, n = newy - 1; m < newx && n >= 0 && count++ < num; m++, n--) {
			if (board[n][m] == cur)
				winflag++;
			else
				break;
		}
	}
	else {
		for (i = newx + 1, j = newy - 1; i < columns && newy >= 0 && count++ < num; i++, j--) {
			if (i == columns - 1 && board[j][i] == cur && j != 0) {
				winflag++;
				for (m = 0, n = j - 1; m < newx && n >= 0 && count++ < num; m++, n--) {
					if (board[n][m] == cur)
						winflag++;
					else
						break;
				}
			}
			else if (i != columns - 1 && board[j][i] == cur)
				winflag++;
			else
				break;
		}
	}
	count = 0;
	if (winflag >= num)
		isWonWrap = true;
	else
		winflag = 1;
}

void WonRecord() {
	if (isWon == true || isWonWrap == true) {
		if (board[newy][newy] == 'X')
			xWon++;
		else
			oWon++;
	}
}

void SwitchPlayer() {
	if (isPlayerOne)
		isPlayerOne = false;
	else
		isPlayerOne = true;
}


void StopGame() {
	if (xWon > 0 && oWon > 0) {
		cout << "The game ended in a draw." << endl;
		stopGame = true;
	}
	else if (xWon > 0 && oWon == 0) {
		cout << "Player X won!" << endl;
		stopGame = true;
	}
	else if (oWon > 0 && xWon == 0) {
		cout << "Player X won!" << endl;
		stopGame = true;
	}
	/*if (isWon == true || isWonWrap == true) {
		if (board[keepNewY][keepNewX] == 'X')
			cout << "Player X won!" << endl;
		else
			cout << "Player O won!" << endl;
		stopGame = true;
	}*/
	else if (isWon == false && isWonWrap == false && isTie == true) {
		cout << "The game ended in a draw." << endl;
		stopGame = true;
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
			system("cls");
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
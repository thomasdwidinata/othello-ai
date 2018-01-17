#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <iostream>

using namespace std;

void initialize();
void printBoard();
void input();
int characterParser(char x);
int checkValid(int x, int y);//this checks if it is valid and directly flips if it is

int board[8][8] = 
{
{-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1}
};

int start[8][8] = 
{
{-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,1,0,-1,-1,-1},
{-1,-1,-1,0,1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1}
};

int clock = 0;

int main (void){
	initialize();
	while(true){
		input();
	}
	return 0;
}

void initialize(){
	for(int x = 0; x<8; x++){
		for (int y = 0; y<8; y++){
			board[x][y] = start[x][y];
		}
	}
}

void printBoard(){
	char black = 177;
	char white = 219;
	cout<<"   A   B   C   D   E   F   G   H  "<<endl;
	for(int x = 0; x<8; x++){
		cout<<" +---+---+---+---+---+---+---+---+"<<endl;
		cout<<x+1;
		for(int y = 0; y<8; y++){
			cout<<"| ";
			if(board[x][y] == 0){
				cout<<white;
			} else if (board[x][y] == 1){
				cout<<black;
			} else {
				cout<<" ";
			}
			cout<<" ";
		}
		cout<<"|"<<endl;
	}
	cout<<" +---+---+---+---+---+---+---+---+"<<endl;
	return;
}

void input(){
	clock++;
	int turn = clock%2;//0 = white's turn, 1 = black's turn
	char character;
	int y;
	bool valid2 = false;//check for valid position input
	bool valid = false;//check for valid input;
	printBoard();
	while(valid2 == false){
		while(valid == false) {
			cout<<"================================================="<<endl;
			if(turn == 0){
				cout<<"WHITE PLAYER'S TURN!"<<endl;
			} else {
				cout<<"BLACK PLAYER'S TURN!"<<endl;
			}
			cout<<"================================================="<<endl;
			cout<<"Input Column (A-H) :";
			cin>>character;
			cout<<"Input Row (1-8) :";
			cin>>y;
			character = tolower(character);
			if(character>=97 && character<=104 && y>=1 && y<=8){
				valid = true;
			} else {
				system("cls");
				printBoard();
				cout<<"INVALID INPUT!"<<endl;
			}
		}
		
		int x = characterParser(character);
		y = --y;
		//cout<<"X = "<<x<<" and Y = "<<y;
		//system("pause");
		if(checkValid(x, y)){
			valid2 = true;
		} else {
			valid = false;
			system("cls");
			printBoard();
			cout<<"INVALID POSITION!"<<endl;
		}
	}
	cout<<"Valid Input!";
	system("pause");
	system("cls");
}

int characterParser(char x){
	switch(x){
		case 97:
			return 0;
		case 98:
			return 1;
		case 99:
			return 2;
		case 100:
			return 3;
		case 101:
			return 4;
		case 102:
			return 5;
		case 103:
			return 6;
		case 104:
			return 7;
		default:
			return -1;
	}
	return -1;
}

int checkValid(int x, int y){//this checks if it is valid and directly flips if it is
	int turn = clock%2;//0 = white's turn, 1 = black's turn
	int overallValid = 0;
	int enemy;
	if(turn == 0){
		enemy = 1;
	}
	int x1 = x, y1 = y;
	bool valid = false;
	if(board[x][y]==-1){
		if(++x1<=8){//NORTH
			if(board[y1][x1] == enemy){
				while(x1<=8){
					if(board[y1][x1] == turn){
						valid = true;
						overallValid = 1;
						break;
					}
					x1++;
				}
				if(valid == true){
					x1 = x;
					y1 = y;
					while(board[y1][x1] == enemy){
						board[y1][x1] = turn;
						x1++;
					}
				}
			}
		}
		x1 = x, y1 = y;
		valid = false;
		if(++x1<=8 && ++y1<=8){//NORTH EAST
			if(board[y1][x1] == enemy){
				while(x1<=8 && y1<=8){
					if(board[y1][x1] == turn){
						valid = true;
						overallValid = 1;
						break;
					}
					x1++;
					y1++;
				}
				if(valid == true){
					x1 = x;
					y1 = y;
					while(board[y1][x1] == enemy){
						board[y1][x1] = turn;
						x1++;
						y1++;
					}
				}
			}
		}
		x1 = x, y1 = y;
		valid = false;
		if(++y1<=8){//EAST
			int x1 = x, y1 = y;
			if(board[y1][x1] == enemy){
				while(y1<=8){
					if(board[y1][x1] == turn){
						valid = true;
						overallValid = 1;
						break;
					}
					y1++;
				}
				if(valid == true){
					x1 = x;
					y1 = y;
					while(board[y1][x1] == enemy){
						board[y1][x1] = turn;
						y1++;
					}
				}
			}
		}
		x1 = x, y1 = y;
		valid = false;
		if(--x1>=0 && ++y1<=8){//SOUTH EAST
			if(board[y1][x1] == enemy){
				while(x1>=0 && y1<=8){
					if(board[y1][x1] == turn){
						valid = true;
						overallValid = 1;
						break;
					}
					x1--;
					y1++;
				}
				if(valid == true){
					x1 = x;
					y1 = y;
					while(board[y1][x1] == enemy){
						board[y1][x1] = turn;
						x1--;
						y1++;
					}
				}
			}
		}
		x1 = x, y1 = y;
		valid = false;
		if(--x1>=0){//SOUTH
			if(board[y1][x1] == enemy){
				while(x1>=0){
					if(board[y1][x1] == turn){
						valid = true;
						overallValid = 1;
						break;
					}
					x1--;
				}
				if(valid == true){
					x1 = x;
					y1 = y;
					while(board[y1][x1] == enemy){
						board[y1][x1] = turn;
						x1--;
					}
				}
			}
		}
		x1 = x, y1 = y;
		valid = false;
		if(--x1>=0 && --y1>=0){//SOUTH WEST
			if(board[y1][x1] == enemy){
				while(x1>=0 && y1>=0){
					if(board[y1][x1] == turn){
						valid = true;
						overallValid = 1;
						break;
					}
					x1--;
					y1--;
				}
				if(valid == true){
					x1 = x;
					y1 = y;
					while(board[y1][x1] == enemy){
						board[y1][x1] = turn;
						x1--;
						y1--;
					}
				}
			}
		}
		x1 = x, y1 = y;
		valid = false;
		if(--y1>=0){//WEST
			if(board[y1][x1] == enemy){
				while(y1>=0){
					if(board[y1][x1] == turn){
						valid = true;
						overallValid = 1;
						break;
					}
					y1--;
				}
				if(valid == true){
					x1 = x;
					y1 = y;
					while(board[y1][x1] == enemy){
						board[y1][x1] = turn;
						y1--;
					}
				}
			}
		}
		x1 = x, y1 = y;
		valid = false;
		if(++x1<=8 && --y1>=0){//NORTH WEST;
			if(board[y1][x1] == enemy){
				while(x1<=8 && y1>=0){
					if(board[y1][x1] == turn){
						valid = true;
						overallValid = 1;
						break;
					}
					x1++;
					y1--;
				}
				if(valid == true){
					x1 = x;
					y1 = y;
					while(board[y1][x1] == enemy){
						board[y1][x1] = turn;
						x1++;
						y1--;
					}
				}
			}
		}
		if(overallValid == 1){
			board[y][x] = turn;
			//cout<<"X = "<<x<<" and Y = "<<y;
			//system("pause");
		}
		return overallValid;
	} else {
		return 0;
	}
}












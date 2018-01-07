#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <iostream>

using namespace std;

void initialize();
void printBoard();
void printArray();//debug purpose function
void input();
int characterParser(char x);
int availableMove();//lists all available moves
void flipAction(int x, int y);//flips chosen moves
void countWinner();
void addPossible(int x, int y);
void clearPossible();
int checkValid(int x, int y);//CHECKS IF THE INPUT IS AVAILABLE IN POSSIBLE MOVES

struct possibleMove{
	int x = 0;
	int y = 0;
	struct possibleMove *next;
	struct possibleMove *prev;
}*head, *tail, *temp;

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
	clock++;
	while(availableMove()){
		input();
		clock++;
	}
	countWinner();
	return 0;
}

void initialize(){
	head = tail = temp = NULL;
	for(int x = 0; x<8; x++){
		for (int y = 0; y<8; y++){
			board[x][y] = start[x][y];
		}
	}
}

void printBoard(){
	char black = 177;
	char white = 219;
	char possible = 248;
	cout<<"CLOCK = \t"<<clock<<endl;
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
			} else if (board[x][y] == 2) {
				cout<<possible;
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

void printArray(){//debug purpose function
	cout<<"\tA\tB\tC\tD\tE\tF\tG\tH"<<endl<<endl;
	for(int x = 0; x<8;x++){
		cout<<x+1<<"\t";
		for(int y = 0; y<8; y++){
			cout<<board[x][y]<<"\t";
		}
		cout<<endl<<endl;
	}
}

void input(){
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
				//cout<<"OUT OF FIRST LOOP!";
				//system("pause");
			} else if(y == 22){
				printArray();//debug
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
			flipAction(x, y);
		} else {
			valid = false;
			system("cls");
			printBoard();
			cout<<"INVALID POSITION!"<<endl;
		}
	}
	clearPossible();
	cout<<"Valid Input!"<<endl;
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

int availableMove(){//lists all available moves
	//cout<<"INSIDE CHECK VALID FUNCTION!";
	//system("pause");
	int turn = clock%2;//0 = white's turn, 1 = black's turn
	int overallValid = 0;
	int enemy = 0;
	(turn == 0) ? (enemy = 1) : (0);
	int x1, y1;
	for(int x = 0; x < 8; x++){
		for(int y = 0; y < 8; y++){
			x1 = x; y1 = y;
			if(board[y][x]==-1){
				if(--y1>=0){//NORTH
					if(board[y1][x1] == enemy){
						while(y1>=0 && board[y1][x1] != -1){
							if(board[y1][x1] == turn){
								overallValid = 1;
								board[y][x] = 2;
								addPossible(x, y);
								break;
							}
							y1--;
						}
					}
				}
				x1 = x, y1 = y;
				if(--y1>=0 && ++x1<=8){//NORTH EAST
					if(board[y1][x1] == enemy){
						while(y1>=0 && x1<=8 && board[y1][x1] != -1){
							if(board[y1][x1] == turn){
								overallValid = 1;
								board[y][x] = 2;
								addPossible(x, y);
								break;
							}
							y1--;
							x1++;
						}
					}
				}
				x1 = x, y1 = y;
				if(++x1<=8){//EAST
					if(board[y1][x1] == enemy){
						while(x1<=8 && board[y1][x1] != -1){
							if(board[y1][x1] == turn){
								overallValid = 1;
								board[y][x] = 2;
								addPossible(x, y);
								break;
							}
							x1++;
						}
					}
				}
				x1 = x, y1 = y;
				if(++y1<=8 && ++x1<=8){//SOUTH EAST
					if(board[y1][x1] == enemy){
						while(y1<=8 && x1<=8 && board[y1][x1] != -1){
							if(board[y1][x1] == turn){
								overallValid = 1;
								board[y][x] = 2;
								addPossible(x, y);
								break;
							}
							y1++;
							x1++;
						}
					}
				}
				x1 = x, y1 = y;
				if(++y1<=8){//SOUTH
					if(board[y1][x1] == enemy){
						while(y1<=8 && board[y1][x1] != -1){
							if(board[y1][x1] == turn){
								overallValid = 1;
								board[y][x] = 2;
								addPossible(x, y);
								break;
							}
							y1++;
						}
					}
				}
				x1 = x, y1 = y;
				if(++y1<=8 && --x1>=0){//SOUTH WEST
					if(board[y1][x1] == enemy){
						while(y1<=8 && x1>= 0 && board[y1][x1] != -1){
							if(board[y1][x1] == turn){
								overallValid = 1;
								board[y][x] = 2;
								addPossible(x, y);
								break;
							}
							y1++;
							x1--;
						}
					}
				}
				x1 = x, y1 = y;
				if(--x1>=0){//WEST
					if(board[y1][x1] == enemy){
						while(x1>= 0 && board[y1][x1] != -1){
							if(board[y1][x1] == turn){
								overallValid = 1;
								board[y][x] = 2;
								addPossible(x, y);
								break;
							}
							x1--;
						}
					}
				}
				x1 = x, y1 = y;
				if(--y1>=0 && --x1>=0){//NORTH WEST
					if(board[y1][x1] == enemy){
						while(y1>=0 && x1>= 0 && board[y1][x1] != -1){
							if(board[y1][x1] == turn){
								overallValid = 1;
								board[y][x] = 2;
								addPossible(x, y);
								break;
							}
							y1--;
							x1--;
						}
					}
				}
				//if(overallValid == 1){
					//cout<<"X = "<<x<<" and Y = "<<y;
					//system("pause");
				//}
				//cout<<"SUCESSSaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"<<endl;
				//system("pause");
			}
		}
	}
	return overallValid;//RETURNS 1 IF POSSIBLE MOVE EXISTS AND 0 IF NO POSITION IS POSSIBLE (A.K.A GAME OVER)
}

void flipAction(int x, int y){//this checks if it is valid and directly flips if it is
	//cout<<"INSIDE CHECK VALID FUNCTION!";
	//system("pause");
	int turn = clock%2;//0 = white's turn, 1 = black's turn
	int enemy = 0;
	if(turn == 0){	
		enemy = 1;
	}
	int x1 = x, y1 = y;
	bool valid = false;
	board[y][x] = turn;
	if(--y1>=0){//NORTH
		if(board[y1][x1] == enemy){
			while(y1>=0 && board[y1][x1] != -1){
				if(board[y1][x1] == turn){
					valid = true;
					break;
				}
				y1--;
			}
			if(valid == true){
				x1 = x;
				y1 = y;
				y1--;
				while(board[y1][x1] == enemy){
					board[y1][x1] = turn;
					y1--;
				}
			}
		}
	}
	x1 = x, y1 = y;
	valid = false;
	if(--y1>=0 && ++x1<=8){//NORTH EAST
		if(board[y1][x1] == enemy){
			while(y1>=0 && x1<=8 && board[y1][x1] != -1){
				if(board[y1][x1] == turn){
					valid = true;
					break;
				}
				y1--;
				x1++;
			}
			if(valid == true){
				x1 = x;
				y1 = y;
				y1--;
				x1++;
				while(board[y1][x1] == enemy){
					board[y1][x1] = turn;
					y1--;
					x1++;
				}
			}
		}
	}
	x1 = x, y1 = y;
	valid = false;
	if(++x1<=8){//EAST
		if(board[y1][x1] == enemy){
			while(x1<=8 && board[y1][x1] != -1){
				if(board[y1][x1] == turn){
					valid = true;
					break;
				}
				x1++;
			}
			if(valid == true){
				x1 = x;
				y1 = y;
				x1++;
				while(board[y1][x1] == enemy){
					board[y1][x1] = turn;
					x1++;
				}
			}
		}
	}
	x1 = x, y1 = y;
	valid = false;
	if(++y1<=8 && ++x1<=8){//SOUTH EAST
		if(board[y1][x1] == enemy){
			while(y1<=8 && x1<=8 && board[y1][x1] != -1){
				if(board[y1][x1] == turn){
					valid = true;
					break;
				}
				y1++;
				x1++;
			}
			if(valid == true){
				x1 = x;
				y1 = y;
				y1++;
				x1++;
				while(board[y1][x1] == enemy){
					board[y1][x1] = turn;
					y1++;
					x1++;
				}
			}
		}
	}
	x1 = x, y1 = y;
	valid = false;
	if(++y1<=8){//SOUTH
		if(board[y1][x1] == enemy){
			while(y1<=8 && board[y1][x1] != -1){
				if(board[y1][x1] == turn){
					valid = true;
					break;
				}
				y1++;
			}
			if(valid == true){
				x1 = x;
				y1 = y;
				y1++;
				while(board[y1][x1] == enemy){
					board[y1][x1] = turn;
					y1++;
				}
			}
		}
	}
	x1 = x, y1 = y;
	valid = false;
	if(++y1<=8 && --x1>=0){//SOUTH WEST
		if(board[y1][x1] == enemy){
			while(y1<=8 && x1>= 0 && board[y1][x1] != -1){
				if(board[y1][x1] == turn){
					valid = true;
					break;
				}
				y1++;
				x1--;
			}
			if(valid == true){
				x1 = x;
				y1 = y;
				y1++;
				x1--;
				while(board[y1][x1] == enemy){
					board[y1][x1] = turn;
					y1++;
					x1--;
				}
			}
		}
	}
	x1 = x, y1 = y;
	valid = false;
	if(--x1>=0){//WEST
		if(board[y1][x1] == enemy){
			while(x1>= 0 && board[y1][x1] != -1){
				if(board[y1][x1] == turn){
					valid = true;
					break;
				}
				x1--;
			}
			if(valid == true){
				x1 = x;
				y1 = y;
				x1--;
				while(board[y1][x1] == enemy){
					board[y1][x1] = turn;
					x1--;
				}
			}
		}
	}
	x1 = x, y1 = y;
	valid = false;
	if(--y1>=0 && --x1>=0){//NORTH WEST
		if(board[y1][x1] == enemy){
			while(y1>=0 && x1>= 0 && board[y1][x1] != -1){
				if(board[y1][x1] == turn){
					valid = true;
					break;
				}
				y1--;
				x1--;
			}
			if(valid == true){
				x1 = x;
				y1 = y;
				y1--;
				x1--;
				while(board[y1][x1] == enemy){
					board[y1][x1] = turn;
					y1--;
					x1--;
				}
			}
		}
	}
}

void countWinner(){
	int black = 0, white = 0, passive = 0;
	for(int x = 0; x < 8; x++){
		for(int y = 0; y < 8; y++){
			if(board[x][y] == 0){
				white++;
			} else if (board[x][y] == 1){
				black++;
			} else {
				passive++;
			}
		}
	}
	
	if(black == white){
		cout<<endl<<"Black = "<<black;
		cout<<endl<<"White = "<<white;
		cout<<endl<<"WINNER = TIE!"<<endl;
		return;
	}
	if(black < white){
		cout<<endl<<"Black = "<<black;
		cout<<endl<<"WHITE = "<<white;
		cout<<endl<<"WINNER = WHITE"<<endl;
	} else {
		cout<<endl<<"BLACK = "<<black;
		cout<<endl<<"White = "<<white;
		cout<<endl<<"WINNER = BLACK"<<endl;
	}
	
}

void addPossible(int x, int y){
	temp = new possibleMove;
	
	temp->x = x;
	temp->y = y;
	temp->next = NULL;
	temp->prev = NULL;
	
	if(head == NULL){
		head = tail = temp;
	} else {
		tail->next = temp;
		temp->prev = tail;
		tail = temp;
	}
}

void clearPossible(){
	for(int x = 0; x < 8; x++){
		for(int y = 0; y < 8; y++){
			if(board[x][y] == 2){
				board[x][y] = -1;
			}
		}
	}
	while(head!=NULL){
		temp = head;
		head = head->next;
		delete(temp);
	}
	head = tail = temp = NULL;
}

int checkValid(int x, int y){//CHECKS IF THE INPUT IS AVAILABLE IN POSSIBLE MOVES
	temp = head;
	while(temp!=NULL){
		if(temp->x == x && temp->y == y){
			return 1;
		}
		temp = temp->next;
	}
	return 0;
}












#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <iostream>
#include <cstring>
#include <limits.h>
#include <ctime>

using namespace std;

void initialize();
void printBoard();
void printArray();//debug purpose function
void twoPlayerMode();//Player Vs Player Mode
void vsAIWhite();
int characterParser(char x);
int availableMove();//lists all available moves
void flipAction(int x, int y);//flips chosen moves
void countWinner();
void addPossible(int x, int y);
void clearPossible();
int checkValid(int x, int y);//CHECKS IF THE INPUT IS AVAILABLE IN POSSIBLE MOVES
void readTraining();
void writeTraining();
void expandWeight();
int* minimax(int simulation[8][8], int depth, bool maximizingPlayer);
int evaluateBoard(int simulation[8][8], int turn);
int** availableMoveSimulation(int simulation[8][8], int turn);//lists all available moves for the simulation
int** processMoveSimulation(int board[8][8], int x, int y, int turn);//flips available move on the certain simulation
void aiMove();
void autoMoveAI();//AI vs AI
//void expandWeightSim();
//void expandWeightSim1();
void simulationToWeight();
void simulation1ToWeight();
void modifyTraining();
void trainAI();
void determineNewWeight(int winner);
void countWinnerTraining();
void printWeight();

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

float smallWeight[4][4];
float weight[8][8];

float smallWeightSim[4][4];//ORIGINAL NON GENETIC WEIGHTS
float weightSim[8][8];

float smallWeightSim1[4][4];//MODIFIED GENETIC WEIGHTS
float weightSim1[8][8];

int bestCoordinate[2];

int depthFixed = 3;
float modifyGap = 0.1;
int clockT = 0;

int main (void){
//	initialize();
//	clockT++;
//	while(availableMove()){
//		twoPlayerMode();
//		vsAIWhite();
//		autoMoveAI();
//		clockT++;
//	}
//	countWinner();
	while(true){
		initialize();
		modifyTraining();
//		printWeight();
		clockT++;
		while(availableMove()){
			trainAI();
			clockT++;
		}
		countWinnerTraining();
	}
	return 0;
}

void initialize(){
	clockT = 0;
	head = tail = temp = NULL;
	for(int x = 0; x<8; x++){
		for (int y = 0; y<8; y++){
			board[x][y] = start[x][y];
			weight[x][y] = 1;
		}
	}
	for(int x = 0; x<4; x++){
		for(int y = 0; y<4; y++){
			smallWeight[x][y] = 1;
		}
	}
	readTraining();
	for(int i = 0; i<4; i++){
		for(int j = 0; j<4; j++){
			smallWeightSim[i][j] = smallWeightSim1[i][j] = smallWeight[i][j];
		}
	}
	expandWeight();
}

void printBoard(){
	char black = 177;
	char white = 219;
	char possible = 248;
	int numBlack = 0, numWhite = 0;
	cout<<"CLOCK = \t"<<clockT<<endl;
	cout<<"   A   B   C   D   E   F   G   H  "<<endl;
	for(int x = 0; x<8; x++){
		cout<<" +---+---+---+---+---+---+---+---+"<<endl;
		cout<<x+1;
		for(int y = 0; y<8; y++){
			cout<<"| ";
			if(board[x][y] == 0){
				numWhite++;
				cout<<white;
			} else if (board[x][y] == 1){
				numBlack++;
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
	cout<<" +---+---+---+---+---+---+---+---+"<<endl<<endl;
	cout<<"Black  =  "<<numBlack<<"\t\tWhite  =  "<<numWhite<<endl<<endl;
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

void twoPlayerMode(){//Player Vs Player Mode
	int turn = clockT%2;//0 = white's turn, 1 = black's turn
	char character;
	int x, y;
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
		x = characterParser(character);
		y = --y;
		
//		cout<<"X = "<<x<<" and Y = "<<y;
//		system("pause");
		
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
//	system("pause");
	system("cls");
}

void vsAIWhite(){
	int turn = clockT%2;//0 = white's turn, 1 = black's turn
	char character;
	int x, y;
	bool valid2 = false;//check for valid position input
	bool valid = false;//check for valid input;
	printBoard();
	while(valid2 == false){
		if(turn == 1){
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
			x = characterParser(character);
			y = --y;
		} else {
			aiMove();
			x = bestCoordinate[0];
			y = bestCoordinate[1];
		}
		
//		cout<<"X = "<<x<<" and Y = "<<y;
//		system("pause");
		
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
//	system("pause");
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
	int turn = clockT%2;//0 = white's turn, 1 = black's turn
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
						while(y1>=0 && board[y1][x1] != -1 && board[y1][x1] !=2){
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
						while(y1>=0 && x1<=8 && board[y1][x1] != -1 && board[y1][x1] !=2){
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
						while(x1<=8 && board[y1][x1] != -1 && board[y1][x1] !=2){
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
						while(y1<=8 && x1<=8 && board[y1][x1] != -1 && board[y1][x1] !=2){
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
						while(y1<=8 && board[y1][x1] != -1 && board[y1][x1] !=2){
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
						while(y1<=8 && x1>= 0 && board[y1][x1] != -1 && board[y1][x1] !=2){
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
						while(x1>= 0 && board[y1][x1] != -1 && board[y1][x1] !=2){
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
	int turn = clockT%2;//0 = white's turn, 1 = black's turn
	int enemy = 0;
	if(turn == 0){	
		enemy = 1;
	}
	int x1 = x, y1 = y;
	bool valid = false;
	board[y][x] = turn;
	if(--y1>=0){//NORTH
		if(board[y1][x1] == enemy){
			while(y1>=0 && board[y1][x1] != -1 && board[y1][x1] !=2){
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
			while(y1>=0 && x1<=8 && board[y1][x1] != -1 && board[y1][x1] !=2){
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
			while(x1<=8 && board[y1][x1] != -1 && board[y1][x1] !=2){
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
			while(y1<=8 && x1<=8 && board[y1][x1] != -1 && board[y1][x1] !=2){
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
			while(y1<=8 && board[y1][x1] != -1 && board[y1][x1] !=2){
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
			while(y1<=8 && x1>= 0 && board[y1][x1] != -1 && board[y1][x1] !=2){
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
			while(x1>= 0 && board[y1][x1] != -1 && board[y1][x1] !=2){
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
			while(y1>=0 && x1>= 0 && board[y1][x1] != -1 && board[y1][x1] !=2){
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
	
	printBoard();
	
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

/**

===============================================================================
||					AI PROGRAM AND TRAINING STARTS HERE!					 ||
===============================================================================

**/

void readTraining(){
	float data;
    string word2 = "";
	
    FILE * fp;
    fp = fopen("trainingData.txt", "r");//OPEN FILE ONLY TO READ
	char word[50];
	
	string str;
	
    for(int x = 0; x < 4; x++){
    	for(int y = 0; y < 4; y++){
    		//cout<<"JAJAJAJAJA";
    		fgets(word, 50, fp)!=NULL;
    		//cout<<"TEST!";
    		//system("pause");
			//fscanf (fp, "%f", &data);
    		//fscanf(fp, "%f", word);
    		//cout<<word;
    		word2 = word;
    		
    		data = atof(word2.c_str());
    		
    		smallWeight[y][x] = data;
//    		cout<<smallWeight[y][x]<<" ";
    		//system("pause");
		}
		cout<<endl;
	}
	fclose(fp);
}

void writeTraining(){
	FILE *fp;
	fp = fopen("trainingData.txt", "w");
	
	for(int x = 0; x < 4; x++){
		for(int y = 0; y < 4; y++){
			fprintf(fp,"%f\n",smallWeight[y][x]);
		}
	}
	fclose(fp);
}

void expandWeight(){
	weight[0][0] = weight[0][7] = weight[7][7] = weight[7][0] = smallWeight[0][0];
	weight[0][1] = weight[1][7] = weight[7][6] = weight[6][0] = smallWeight[0][1];
	weight[0][2] = weight[2][7] = weight[7][5] = weight[5][0] = smallWeight[0][2];
	weight[0][3] = weight[3][7] = weight[7][4] = weight[4][0] = smallWeight[0][3];
	
	weight[1][0] = weight[0][6] = weight[6][7] = weight[7][1] = smallWeight[1][0];
	weight[1][1] = weight[1][6] = weight[6][6] = weight[6][1] = smallWeight[1][1];
	weight[1][2] = weight[2][6] = weight[6][5] = weight[5][1] = smallWeight[1][2];
	weight[1][3] = weight[3][6] = weight[6][4] = weight[4][1] = smallWeight[1][3];
	
	weight[2][0] = weight[0][5] = weight[5][7] = weight[7][2] = smallWeight[2][0];
	weight[2][1] = weight[1][5] = weight[5][6] = weight[6][2] = smallWeight[2][1];
	weight[2][2] = weight[2][5] = weight[5][5] = weight[5][2] = smallWeight[2][2];
	weight[2][3] = weight[3][5] = weight[5][4] = weight[4][2] = smallWeight[2][3];
	
	weight[3][0] = weight[0][4] = weight[4][7] = weight[7][3] = smallWeight[3][0];
	weight[3][1] = weight[1][4] = weight[4][6] = weight[6][3] = smallWeight[3][1];
	weight[3][2] = weight[2][4] = weight[4][5] = weight[5][3] = smallWeight[3][2];
	weight[3][3] = weight[3][4] = weight[4][4] = weight[4][3] = smallWeight[3][3];
}

//int test = 0, test2 =0;

int* minimax(int simulation[8][8], int depth, int turn){//assume 0 is friend, and 1 is foe
	int counter = 0;
	
	int evaluated[2] = {-1, -1};
	
	int** tempBoard = 0;
	tempBoard = new int*[8];
	for(int x = 0; x<8; x++){
		tempBoard[x] = new int [8];
		for(int y = 0; y<8; y++){
			tempBoard[x][y] = -1;
		}
	}
	
	int tempBoardBarbaric[8][8];
	
	if(depth == 0){
		evaluated[0] = evaluateBoard(simulation, turn);
		return evaluated;
	}
	if(turn == 1){//assume 1 is enemy, so we want the minimum for enemy
		int bestValue[2] = {INT_MAX, -1};
		int** moves = availableMoveSimulation(simulation, turn);
//		cout<<"Moves"<<moves[0][0]<<" ------ "<<moves[0][1];
//		system("pause");
		while(moves[counter][0]!=-1){
			int newBoard[8][8];
			for(int i = 0; i<8; i++){
				for(int j = 0; j<8; j++){
					newBoard[i][j] = simulation[i][j];
				}
			}
			tempBoard = processMoveSimulation(newBoard, moves[counter][0], moves[counter][1], turn);
			for(int i = 0; i<8; i++){
				for(int j = 0; j<8; j++){
					tempBoardBarbaric[i][j] = tempBoard[i][j];
				}
			}
			int* v = minimax(tempBoardBarbaric, depth-1, turn-1);
//			if(clockT == 17){
//				test++;
//				cout<<"Test = "<<test<<endl;
//			}
			if(v[0] < bestValue[0]){
				bestValue[0] = v[0];
				if(depth == depthFixed){
					bestCoordinate[0] = moves[counter][0];
					bestCoordinate[1] = moves[counter][1];
//					cout<<"[TURN = 1]Best Coordinate = x:"<<bestCoordinate[0]<<", y:"<<bestCoordinate[1];
//					system("pause");
				}
			}
			
			
			
			
			
			
			
			
//			if(test >= 900){
//				for(int ab = 0; ab<20; ab++){
//					cout<<"X = "<<moves[ab][0]<<", Y = "<<moves[ab][1]<<endl;
//				}
//				cout<<"Last Move Selected = x: "<<moves[counter][0]<<", y: "<<moves[counter][1]<<endl;
//				system("pause");
//			}
			counter++;
		}
		return bestValue;
	} else {
		int bestValue[2] = {INT_MIN, -1};
		int** moves = availableMoveSimulation(simulation, turn);
		while(moves[counter][0]!=-1){
			int newBoard[8][8];
			for(int i = 0; i<8; i++){
				for(int j = 0; j<8; j++){
					newBoard[i][j] = simulation[i][j];
				}
			}
			tempBoard = processMoveSimulation(newBoard, moves[counter][0], moves[counter][1], turn);
			for(int i = 0; i<8; i++){
				for(int j = 0; j<8; j++){
					tempBoardBarbaric[i][j] = tempBoard[i][j];
				}
			}
			int* v = minimax(tempBoardBarbaric, depth-1, turn+1);
//			if(clockT == 50){
//				test2++;
//				cout<<"Test2 = "<<test2<<endl;
//			}
			if(v[0] > bestValue[0]){
				bestValue[0] = v[0];
				if(depth == depthFixed){
					bestCoordinate[0] = moves[counter][0];
					bestCoordinate[1] = moves[counter][1];
//					cout<<"[TURN = 2]Best Coordinate = x:"<<bestCoordinate[0]<<", y:"<<bestCoordinate[1];
//					system("pause");
				}
			}
			counter++;
		}
		return bestValue;
	}
}

int evaluateBoard(int simulation[8][8], int turn){
	int black = 0;
	int white = 0;
	for (int x = 0; x < 8; x++){
		for(int y = 0; y < 8; y++){
			if(simulation[y][x] == 0){
				white++;
				white+=weight[y][x];
			} else if (simulation[y][x] == 1){
				black++;
				black+=weight[y][x];
			}
		}
	}
	return (turn == 0) ? white-black : black-white;
}

int** availableMoveSimulation(int simulation[8][8], int turn){//lists all available moves for the simulation
	int** result = 0;
	result = new int*[20];
	for(int x = 0; x<20; x++){
		result[x] = new int [2];
		for(int y = 0; y<2; y++){
			result[x][y] = -1;
		}
	}
	int enemy = 0;
	int total = 0;
	(turn == 0) ? (enemy = 1) : (0);
	int x1, y1;
	
	int i = 0;
	
//	cout<<endl<<endl;
//	for(int i = 0; i<8; i++){
//		for(int j = 0; j<8; j++){
//			cout<<simulation[i][j]<<"\t";
//		}
//		cout<<endl;
//	}
	
	for(int x = 0; x < 8; x++){
		for(int y = 0; y < 8; y++){
			x1 = x; y1 = y;
			if(board[y][x]==-1 || board[y][x]==2){
				if(--y1>=0){//NORTH
					if(simulation[y1][x1] == enemy){
						while(y1>=0 && simulation[y1][x1] != -1 && board[y1][x1] !=2){
							if(simulation[y1][x1] == turn){
								while(i<=20){
									if(result[i][0] == x && result[i][1] == y){
										break;
									} else if(result[i][0] == -1){
										result[total][0] = x;
										result[total][1] = y;
										total++;
										break;
									}
									i++;
								}
								break;
							}
							y1--;
						}
					}
				}
				x1 = x, y1 = y;
				if(--y1>=0 && ++x1<=8){//NORTH EAST
					if(simulation[y1][x1] == enemy){
						while(y1>=0 && x1<=8 && simulation[y1][x1] != -1 && board[y1][x1] !=2){
							if(simulation[y1][x1] == turn){
								while(i<=20){
									if(result[i][0] == x && result[i][1] == y){
										break;
									} else if(result[i][0] == -1){
										result[total][0] = x;
										result[total][1] = y;
										total++;
										break;
									}
									i++;
								}
								break;
							}
							y1--;
							x1++;
						}
					}
				}
				x1 = x, y1 = y;
				if(++x1<=8){//EAST
					if(simulation[y1][x1] == enemy){
						while(x1<=8 && simulation[y1][x1] != -1 && board[y1][x1] !=2){
							if(simulation[y1][x1] == turn){
								while(i<=20){
									if(result[i][0] == x && result[i][1] == y){
										break;
									} else if(result[i][0] == -1){
										result[total][0] = x;
										result[total][1] = y;
										total++;
										break;
									}
									i++;
								}
								break;
							}
							x1++;
						}
					}
				}
				x1 = x, y1 = y;
				if(++y1<=8 && ++x1<=8){//SOUTH EAST
					if(simulation[y1][x1] == enemy){
						while(y1<=8 && x1<=8 && simulation[y1][x1] != -1 && board[y1][x1] !=2){
							if(simulation[y1][x1] == turn){
								while(i<=20){
									if(result[i][0] == x && result[i][1] == y){
										break;
									} else if(result[i][0] == -1){
										result[total][0] = x;
										result[total][1] = y;
										total++;
										break;
									}
									i++;
								}
								break;
							}
							y1++;
							x1++;
						}
					}
				}
				x1 = x, y1 = y;
				if(++y1<=8){//SOUTH
					if(simulation[y1][x1] == enemy){
						while(y1<=8 && simulation[y1][x1] != -1 && board[y1][x1] !=2){
							if(simulation[y1][x1] == turn){
								while(i<=20){
									if(result[i][0] == x && result[i][1] == y){
										break;
									} else if(result[i][0] == -1){
										result[total][0] = x;
										result[total][1] = y;
										total++;
										break;
									}
									i++;
								}
								break;
							}
							y1++;
						}
					}
				}
				x1 = x, y1 = y;
				if(++y1<=8 && --x1>=0){//SOUTH WEST
					if(simulation[y1][x1] == enemy){
						while(y1<=8 && x1>= 0 && simulation[y1][x1] != -1 && board[y1][x1] !=2){
							if(simulation[y1][x1] == turn){
								while(i<=20){
									if(result[i][0] == x && result[i][1] == y){
										break;
									} else if(result[i][0] == -1){
										result[total][0] = x;
										result[total][1] = y;
										total++;
										break;
									}
									i++;
								}
								break;
							}
							y1++;
							x1--;
						}
					}
				}
				x1 = x, y1 = y;
				if(--x1>=0){//WEST
					if(simulation[y1][x1] == enemy){
						while(x1>= 0 && simulation[y1][x1] != -1 && board[y1][x1] !=2){
							if(simulation[y1][x1] == turn){
								while(i<=20){
									if(result[i][0] == x && result[i][1] == y){
										break;
									} else if(result[i][0] == -1){
										result[total][0] = x;
										result[total][1] = y;
										total++;
										break;
									}
									i++;
								}
								break;
							}
							x1--;
						}
					}
				}
				x1 = x, y1 = y;
				if(--y1>=0 && --x1>=0){//NORTH WEST
					if(simulation[y1][x1] == enemy){
						while(y1>=0 && x1>= 0 && simulation[y1][x1] != -1 && board[y1][x1] !=2){
							if(simulation[y1][x1] == turn){
								while(i<=20){
									if(result[i][0] == x && result[i][1] == y){
										break;
									} else if(result[i][0] == -1){
										result[total][0] = x;
										result[total][1] = y;
										total++;
										break;
									}
									i++;
								}
								break;
							}
							y1--;
							x1--;
						}
					}
				}
//				if(overallValid == 1){
//					cout<<"X = "<<x<<" and Y = "<<y;
//					system("pause");
//				}
//				cout<<"SUCESSSaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"<<endl;
//				system("pause");
			}
		}
	}
	
//	int i = 0;
//	while(result[i][0]!=-1){
//		cout<<"RESULT = X:"<<result[i][0]<<", Y:"<<result[i][1]<<endl;
//		i++;
//	}
//	system("pause");
	
	return result;//RETURNS 1 IF POSSIBLE MOVE EXISTS AND 0 IF NO POSITION IS POSSIBLE (A.K.A GAME OVER)
}

int** processMoveSimulation(int board[8][8], int x, int y, int turn){//flips available move on the certain simulation
	//cout<<"INSIDE CHECK VALID FUNCTION!";
	//system("pause");
	int** result = 0;
	result = new int*[8];
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
			while(y1>=0 && x1<=8 && board[y1][x1] != -1 && board[y1][x1] !=2){
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
			while(x1<=8 && board[y1][x1] != -1 && board[y1][x1] !=2){
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
			while(y1<=8 && x1<=8 && board[y1][x1] != -1 && board[y1][x1] !=2){
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
			while(y1<=8 && board[y1][x1] != -1 && board[y1][x1] !=2){
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
			while(y1<=8 && x1>= 0 && board[y1][x1] != -1 && board[y1][x1] !=2){
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
			while(x1>= 0 && board[y1][x1] != -1 && board[y1][x1] !=2){
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
			while(y1>=0 && x1>= 0 && board[y1][x1] != -1 && board[y1][x1] !=2){
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
	for(int x = 0; x<8; x++){
		result[x] = new int [8];
		for(int y = 0; y<8; y++){
			result[x][y] = board[x][y];
		}
	}
	return result;
}

void aiMove(){
	int turn = clockT%2;//0 for white, 1 for black
	bestCoordinate[0] = head->x;
	bestCoordinate[1] = head->y;
	minimax(board, depthFixed, turn);
}

void autoMoveAI(){//AI vs AI
	int turn = clockT%2;//0 = white's turn, 1 = black's turn
	char character;
	int x, y;
	bool valid2 = false;//check for valid position input
	bool valid = false;//check for valid input;
	printBoard();
		
	while(valid2 == false){
		cout<<"================================================="<<endl;
		if(turn == 0){
			cout<<"WHITE PLAYER'S TURN!"<<endl;
		} else {
			cout<<"BLACK PLAYER'S TURN!"<<endl;
		}
		cout<<"================================================="<<endl;
		aiMove();
		x = bestCoordinate[0];
		y = bestCoordinate[1];
		
//		if(clockT == 50 || clockT == 49){
//			cout<<"X = "<<x<<" and Y = "<<y;
//			system("pause");
//		}
		
//		cout<<"X = "<<x<<" and Y = "<<y;
//		system("pause");
		
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
//	cout<<"Valid Input!"<<endl;
//	system("pause");
	system("cls");
}

//void expandWeightSim(){
//	weightSim[0][0] = weightSim[0][7] = weightSim[7][7] = weightSim[7][0] = smallWeightSim[0][0];
//	weightSim[0][1] = weightSim[1][7] = weightSim[7][6] = weightSim[6][0] = smallWeightSim[0][1];
//	weightSim[0][2] = weightSim[2][7] = weightSim[7][5] = weightSim[5][0] = smallWeightSim[0][2];
//	weightSim[0][3] = weightSim[3][7] = weightSim[7][4] = weightSim[4][0] = smallWeightSim[0][3];
//	
//	weightSim[1][0] = weightSim[0][6] = weightSim[6][7] = weightSim[7][1] = smallWeightSim[1][0];
//	weightSim[1][1] = weightSim[1][6] = weightSim[6][6] = weightSim[6][1] = smallWeightSim[1][1];
//	weightSim[1][2] = weightSim[2][6] = weightSim[6][5] = weightSim[5][1] = smallWeightSim[1][2];
//	weightSim[1][3] = weightSim[3][6] = weightSim[6][4] = weightSim[4][1] = smallWeightSim[1][3];
//	
//	weightSim[2][0] = weightSim[0][5] = weightSim[5][7] = weightSim[7][2] = smallWeightSim[2][0];
//	weightSim[2][1] = weightSim[1][5] = weightSim[5][6] = weightSim[6][2] = smallWeightSim[2][1];
//	weightSim[2][2] = weightSim[2][5] = weightSim[5][5] = weightSim[5][2] = smallWeightSim[2][2];
//	weightSim[2][3] = weightSim[3][5] = weightSim[5][4] = weightSim[4][2] = smallWeightSim[2][3];
//	
//	weightSim[3][0] = weightSim[0][4] = weightSim[4][7] = weightSim[7][3] = smallWeightSim[3][0];
//	weightSim[3][1] = weightSim[1][4] = weightSim[4][6] = weightSim[6][3] = smallWeightSim[3][1];
//	weightSim[3][2] = weightSim[2][4] = weightSim[4][5] = weightSim[5][3] = smallWeightSim[3][2];
//	weightSim[3][3] = weightSim[3][4] = weightSim[4][4] = weightSim[4][3] = smallWeightSim[3][3];
//}
//
//void expandWeightSim1(){
//	weightSim1[0][0] = weightSim1[0][7] = weightSim1[7][7] = weightSim1[7][0] = smallWeightSim1[0][0];
//	weightSim1[0][1] = weightSim1[1][7] = weightSim1[7][6] = weightSim1[6][0] = smallWeightSim1[0][1];
//	weightSim1[0][2] = weightSim1[2][7] = weightSim1[7][5] = weightSim1[5][0] = smallWeightSim1[0][2];
//	weightSim1[0][3] = weightSim1[3][7] = weightSim1[7][4] = weightSim1[4][0] = smallWeightSim1[0][3];
//	
//	weightSim1[1][0] = weightSim1[0][6] = weightSim1[6][7] = weightSim1[7][1] = smallWeightSim1[1][0];
//	weightSim1[1][1] = weightSim1[1][6] = weightSim1[6][6] = weightSim1[6][1] = smallWeightSim1[1][1];
//	weightSim1[1][2] = weightSim1[2][6] = weightSim1[6][5] = weightSim1[5][1] = smallWeightSim1[1][2];
//	weightSim1[1][3] = weightSim1[3][6] = weightSim1[6][4] = weightSim1[4][1] = smallWeightSim1[1][3];
//	
//	weightSim1[2][0] = weightSim1[0][5] = weightSim1[5][7] = weightSim1[7][2] = smallWeightSim1[2][0];
//	weightSim1[2][1] = weightSim1[1][5] = weightSim1[5][6] = weightSim1[6][2] = smallWeightSim1[2][1];
//	weightSim1[2][2] = weightSim1[2][5] = weightSim1[5][5] = weightSim1[5][2] = smallWeightSim1[2][2];
//	weightSim1[2][3] = weightSim1[3][5] = weightSim1[5][4] = weightSim1[4][2] = smallWeightSim1[2][3];
//	
//	weightSim1[3][0] = weightSim1[0][4] = weightSim1[4][7] = weightSim1[7][3] = smallWeightSim1[3][0];
//	weightSim1[3][1] = weightSim1[1][4] = weightSim1[4][6] = weightSim1[6][3] = smallWeightSim1[3][1];
//	weightSim1[3][2] = weightSim1[2][4] = weightSim1[4][5] = weightSim1[5][3] = smallWeightSim1[3][2];
//	weightSim1[3][3] = weightSim1[3][4] = weightSim1[4][4] = weightSim1[4][3] = smallWeightSim1[3][3];
//}

void simulationToWeight(){
	for(int i = 0; i<4; i++){
		for(int j = 0; j<4; j++){
			smallWeight[i][j] = smallWeightSim[i][j];
		}
	}
	expandWeight();
//	printWeight();
}

void simulation1ToWeight(){
	for(int i = 0; i<4; i++){
		for(int j = 0; j<4; j++){
			smallWeight[i][j] = smallWeightSim1[i][j];
		}
	}
	expandWeight();
//	printWeight();
}

void modifyTraining(){
	srand(time(NULL));
	for(int i = 0; i<4; i++){
		for(int j = 0; j<4; j++){
			(rand()%2 == 0) ? smallWeightSim1[i][j] += modifyGap : smallWeightSim1[i][j] -= modifyGap;
//			cout<<smallWeightSim1[i][j]<<" ";
		}
//		cout<<endl;i
	}
//	system("pause");
}

void trainAI(){
	int turn = clockT%2;//0 = white's turn, 1 = black's turn
	char character;
	int x, y;
	bool valid2 = false;//check for valid position input
	bool valid = false;//check for valid input;
	printBoard();
	
	while(valid2 == false){
		(turn == 1) ? simulation1ToWeight() : simulationToWeight();
//		printWeight();
		cout<<"================================================="<<endl;
		if(turn == 0){
			cout<<"WHITE PLAYER'S TURN!"<<endl;
		} else {
			cout<<"BLACK PLAYER'S TURN!"<<endl;
		}
		cout<<"================================================="<<endl;
		
		aiMove();
		x = bestCoordinate[0];
		y = bestCoordinate[1];
		
//		if(clockT > 33){
//			cout<<"X = "<<x<<" and Y = "<<y;
//			system("pause");
//		}
		
//		cout<<"X = "<<x<<" and Y = "<<y;
//		system("pause");
		
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
//	cout<<"Valid Input!"<<endl;
//	system("pause");
	system("cls");
}

void determineNewWeight(int winner){
	if(winner == 1){
		simulation1ToWeight();
	} else {
		simulationToWeight();
	}
	writeTraining();
}

void countWinnerTraining(){
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
	
	printBoard();
	
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
		determineNewWeight(0);
	} else {
		cout<<endl<<"BLACK = "<<black;
		cout<<endl<<"White = "<<white;
		cout<<endl<<"WINNER = BLACK"<<endl;
		determineNewWeight(1);
	}
}

void printWeight(){
	for(int i=0; i<4; i++){
		for(int j = 0; j<4; j++){
			cout<<smallWeight[i][j]<<" ";
		}
		cout<<endl;
	}
	system("pause");
}










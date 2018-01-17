#define APP_NAME "Othello AI"
#define APP_VERSION "v1.0"
#define APP_DEVELOPER "Andre Valentino, Fenbert, Thomas Dwi Dinata"

#ifdef _WIN32
	#define BLACK_TEXT 177
	#define WHITE_TEXT 219
	#define POSSIBLE_TEXT 248
#elif __APPLE__
	#include "TargetConditionals.h"
	#if TARGET_OS_MAC
		#include <termios.h>
		#define BLACK_TEXT 'b'
		#define WHITE_TEXT 'w'
		#define POSSIBLE_TEXT '~'
	#endif
#elif __linux__
	#include <termios.h>
	#define BLACK_TEXT 'b'
	#define WHITE_TEXT 'w'
	#define POSSIBLE_TEXT '~'
#endif

void initialize();
void printBoard();
void printArray();//debug purpose function
void twoPlayerMode();//Player Vs Player Mode
void vsAIWhite();
void vsAIBlack();
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
int minimax(int simulation[8][8], int depth, bool maximizingPlayer);
int evaluateBoard(int simulation[8][8], int turn);
int** availableMoveSimulation(int simulation[8][8], int turn);//lists all available moves for the simulation
int** processMoveSimulation(int board[8][8], int x, int y, int turn);//flips available move on the certain simulation
void aiMove();
void autoMoveAI();
void simulationToWeight();
void simulation1ToWeight();
void modifyTraining();
void trainAI();
void determineNewWeight(int winner);
void countWinnerTraining();
void printWeight();
void initializeNewTraining();

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
float modifyGap = 0.5;
int clockT = 0;

int numOfTraining = 0;
int counterWrite = 0;

void startup()
{
	printf(APP_NAME);
	printf("\n");
	printf(APP_VERSION);
	printf("\n");
	printf(APP_DEVELOPER);
	printf("\n");
}

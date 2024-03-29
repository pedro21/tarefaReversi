// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

#ifndef PCH_H
#define PCH_H

#define MAX_SAVED_GAME 10
#define MAX_SAVED_NAME_LENGHT 15
typedef enum {MANUAL = 'M',AUTOMATIC = 'A'} Mode; //used to identify the mode of the game that is on the file
typedef enum {X_PLAYER = 'X',O_PLAYER = 'O'} Player; //used to identify the next player to play
typedef enum {X_BLACK = 'X',O_WHITE = 'O',EMPTY = '-',VALID_PLAY = '.', SUGESTION = '?'} Piece; //enum that composes the possible board pieces

typedef struct position {
	int line;
	int column;
} Position;

// TODO: add headers that you want to pre-compile here
typedef struct game {
	Mode mode;
	char* savedGameID;
	Player nextPlayer;
	Piece board[8][8];
} SGame, *Game;

void menu();
SGame initializeNewGame(Mode mode, Player startPLayer);
void readSavedGames(Game* savedGames, int* savedGamesCounter);
Game loadSavedGame(Game* savedGames, int index);
void startPlaying(Game* activeGame);
void printSavedGames(Game* savedGames, int savedGamesCounter);
Piece getPiece(char piece);
bool validPosition(int line, int column);
void selectSavedGameMenu(Game* savedGames, int savedGamesCounter);
#endif //PCH_H

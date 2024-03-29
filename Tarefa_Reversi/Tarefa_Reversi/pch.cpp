// pch.cpp: source file corresponding to pre-compiled header; necessary for compilation to succeed

#include "pch.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>




// In general, ignore this file, but keep it around if you are using pre-compiled headers.

//initializess a new game
SGame initializeNewGame(Mode mode, Player startPLayer)
{
	SGame game;
	game.mode = mode;
	game.nextPlayer = startPLayer;
	game.savedGameID = (char *)malloc(sizeof(char) * MAX_SAVED_NAME_LENGHT);
	strcpy_s(game.savedGameID, MAX_SAVED_NAME_LENGHT, "untitled");

	//initialize centarl pieces
	game.board[3][3] = O_WHITE;
	game.board[3][4] = X_BLACK;
	game.board[4][3] = X_BLACK;
	game.board[4][4] = O_WHITE;

	return game;
}

void printSavedGames(Game* savedGames, int savedGamesCounter) {
	int i, x, y;
	if (savedGames == NULL) {
		printf("the saved games were not loaded");
	}

	for (i = 0; i< MAX_SAVED_GAME && i < savedGamesCounter; i++) {
		printf("***** Saved game Number: %d \n", i+1);
		printf("Saved Game Name -> %s \n", (*savedGames)[i].savedGameID);
		printf("Game mode -> %c	\n", (*savedGames)[i].mode);
		printf("Next Player Move -> %c \n", (*savedGames)[i].nextPlayer);
		printf("##################\n");

		for (x = 0; x < 8; x++) {
			printf("#");
			for (y = 0; y < 8; y++) {
				printf("%c ", (*savedGames)[i].board[x][y]);
			}
			printf("#\n");
		}
		printf("##################\n\n");
	}
}

//Loads a Saved that is identified with a secific ID from the file
void readSavedGames(Game* savedGames, int* savedGamesCounter){
	FILE* file;
	char line[30];
	errno_t error;
	*savedGamesCounter = -1;
	int i,j, boardLineCount;

	if((error = fopen_s(&file, "SavedGames.txt", "r")) != 0){
		perror("Error while opening the file.\n");
		exit(EXIT_FAILURE);
	}

	if (*savedGames == NULL) {
		*savedGames = (Game)malloc(sizeof(SGame) * MAX_SAVED_GAME);
	}

	//Read all the Saved Games ID
	while (fgets(line, 30, file)) {
		//Found new Saved Game
		if (strncmp("SV_ID", line, 5) == 0){
			(*savedGamesCounter)++;
			boardLineCount = 0;
			(*savedGames)[*savedGamesCounter].savedGameID = (char *)malloc(sizeof(char) * MAX_SAVED_NAME_LENGHT);
			strncpy_s((*savedGames)[*savedGamesCounter].savedGameID, MAX_SAVED_NAME_LENGHT, &line[5], MAX_SAVED_NAME_LENGHT - 1);
			fgets(line, 30, file);

			//gets game mode
			if (line[0] == MANUAL) {
				(*savedGames)[*savedGamesCounter].mode = MANUAL;
			}
			else if (line[0] == AUTOMATIC) {
				(*savedGames)[*savedGamesCounter].mode = AUTOMATIC;
			}

			//gets next player
			if (line[2] == X_PLAYER) {
				(*savedGames)[*savedGamesCounter].nextPlayer = X_PLAYER;
			}
			else if (line[2] == O_PLAYER) {
				(*savedGames)[*savedGamesCounter].nextPlayer = O_PLAYER;
			}
			continue;
		}

		//load board game
		for(i = 0, j = 0; line[i] != '\0' && i < 30 ; i++){
			if (line[i] != ' ' && line[i] != '\n' && line[i] != '\0') {
				(*savedGames)[*savedGamesCounter].board[boardLineCount][j] = getPiece(line[i]);
				j++;
			}
		}
		boardLineCount++;
	}
	//Menu Presenting all the saved Games to choose
	//Load the Specified saved game

	printf(" ...Loaded %d Saved Games\n\n", (*savedGamesCounter)+1);
	printSavedGames(savedGames, (*savedGamesCounter) + 1);
	//add one more because for indexing reasons
	(*savedGamesCounter)++;
	fclose(file);
}

Piece getPiece(char piece) {
	Piece result;
	switch (piece)
	{
		case 'X':
			result = X_BLACK;
			break;
		case 'O':
			result = O_WHITE;
			break;
		case '-':
			result = EMPTY;
			break;
		case '.':
			result = VALID_PLAY;
			break;
		case '?':
			result = SUGESTION;
			break;
		default:
			break;
	}
	return result;
}

void startPlaying(Game* activeGame) {
}

Game loadSavedGame(Game* savedGames, int index) {
	/*Game x;
	x->mode = MANUAL;
	x->nextPlayer = X_PLAYER;
	return x;*/
	return NULL;
}

void selectSavedGameMenu(Game* savedGames, int savedGamesCounter) {
	printf("\n\n...Select the number that correspond to the saved game you want to load:::\n\n");
	printSavedGames(savedGames, savedGamesCounter);
	printf("\nSelect an option:::");
	char option = getchar();
	switch (option)
	{
		case '1':
			break;
		case '2':
			break;
		case '7':
			break;
	}
}

void savesGameStatus() 
{
}

void playPiece(Position position)
{
}

void printValidPositions() 
{
}

void printSugestion() 
{
}

void undoLatestPlay() 
{
}

void menu() {
	printf("1) Start New Game\n");
	printf("2) Load Saved Game\n");
	printf("3) Save Game\n");
	printf("4) Start Game Against Bot\n");
	printf("5) Quit\n");
}

bool validPlay(Game* savedGames, int line, int column) {
	if (savedGames == NULL) {
		return false;
	}
	//position out of borad
	if (!validPosition(line, column))
		return false;

	//Check if position in board is empty
	if ((*savedGames)->board[line][column] == X_BLACK || (*savedGames)->board[line][column] == O_WHITE) {
		return false;
	}

	//find the piece that the player will play 
	Piece playerPiece, opositePlayerPiece;
	if ((*savedGames)->nextPlayer == X_PLAYER){
		opositePlayerPiece = O_WHITE;
		playerPiece = X_BLACK;
	}
	else {
		opositePlayerPiece = X_BLACK;
		playerPiece = O_WHITE;
	}

	int aux_line, aux_column;
	//validate N
	aux_line = line - 1;
	while (validPosition(aux_line, column) && (*savedGames)->board[aux_line][column] == opositePlayerPiece)
	{
		aux_line--;
	}
	if ((*savedGames)->board[aux_line][column] == playerPiece) {
		return true;
	}
	//validate NE
	aux_line = line - 1, aux_column = column + 1;
	while (validPosition(aux_line,aux_column) && (*savedGames)->board[aux_line][aux_column] == opositePlayerPiece)
	{
		aux_line--;
		aux_column++;
	}
	if ((*savedGames)->board[aux_line][aux_column] == playerPiece) {
		return true;
	}
	//validate E
	aux_column = column + 1;
	while (validPosition(line, aux_column) && (*savedGames)->board[line][aux_column] == opositePlayerPiece)
	{
		aux_column++;
	}
	if ((*savedGames)->board[line][aux_column] == playerPiece) {
		return true;
	}
	//validate SE
	aux_line = line + 1, aux_column = column + 1;
	while (validPosition(aux_line, aux_column) && (*savedGames)->board[aux_line][aux_column] == opositePlayerPiece)
	{
		aux_line++;
		aux_column++;
	}
	if ((*savedGames)->board[aux_line][aux_column] == playerPiece) {
		return true;
	}
	//validate S
	aux_line = line + 1;
	while (validPosition(aux_line, column) && (*savedGames)->board[aux_line][column] == opositePlayerPiece)
	{
		aux_line++;
	}
	if ((*savedGames)->board[aux_line][column] == playerPiece) {
		return true;
	}
	//validate SW
	aux_line = line + 1, aux_column = column - 1;
	while (validPosition(aux_line, aux_column) && (*savedGames)->board[aux_line][aux_column] == opositePlayerPiece)
	{
		aux_line++;
		aux_column--;
	}
	if ((*savedGames)->board[aux_line][aux_column] == playerPiece) {
		return true;
	}
	//validate W
	aux_column = column - 1;
	while (validPosition(line, aux_column) && (*savedGames)->board[line][aux_column] == opositePlayerPiece)
	{
		aux_column--;
	}
	if ((*savedGames)->board[line][aux_column] == playerPiece) {
		return true;
	}
	//validate NW
	aux_line = line - 1, aux_column = column - 1;
	while (validPosition(aux_line, aux_column) && (*savedGames)->board[aux_line][aux_column] == opositePlayerPiece)
	{
		aux_line--;
		aux_column--;
	}
	if ((*savedGames)->board[aux_line][aux_column] == playerPiece) {
		return true;
	}

	return false;
}

bool validPosition(int line, int column) {
	if (line < 1 && line > 8 && column < 1 && column > 8) {
		return false;
	}
	return true;
}



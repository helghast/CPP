/*****************************************************************************************
/* File: Game.h
/* Desc: General class for the game
/*
/* gametuto.com - Javier L�pez L�pez (javilop.com)
/*
/*****************************************************************************************
/*
/* Creative Commons - Attribution 3.0 Unported
/* You are free:
/*	to Share � to copy, distribute and transmit the work
/*	to Remix � to adapt the work
/*
/* Under the following conditions:
/* Attribution. You must attribute the work in the manner specified by the author or licensor 
/* (but not in any way that suggests that they endorse you or your use of the work).
/*
/*****************************************************************************************/

#ifndef _GAME_
#define _GAME_

// ------ Includes -----
#include "Board.h"
#include "Pieces.h"
#include "IO.h"
#include <time.h>

// ------ Defines -----
#define WAIT_TIME 700			// Number of milliseconds that the piece remains before going 1 block down */ 
#define RANGE_PIECE 6
#define RANGE_ROTATION 3

// --------------------------------------------------------------------------------
//									 Game
// --------------------------------------------------------------------------------
class Game
{
public:
	Game(Board* pBoard, Pieces* pPieces, IO* pIO, const int pScreenHeight);

	void DrawScene();
	void CreateNewPiece();

	int mPosX, mPosY;				// Position of the piece that is falling down
	int mPiece, mRotation;			// Kind and rotation the piece that is falling down

private:
	int mScreenHeight;				// Screen height in pixels
	int mNextPosX, mNextPosY;		// Position of the next piece
	int mNextPiece, mNextRotation;	// Kind and rotation of the next piece

	Board* mBoard;
	Pieces* mPieces;
	IO* mIO;

	int GetRand(const int pA, const int pB);
	void InitGame();
	void DrawPiece(const int pX, const int pY, const int pPiece, const int pRotation);
	void DrawBoard();
};

#endif // _GAME_

/*****************************************************************************************
/* File: Pieces.h
/* Desc: All the Tetris pieces with their respective rotations and displacements for the hotspot
/*
/* gametuto.com - Javier López López (javilop.com)
/*
/*****************************************************************************************
/*
/* Creative Commons - Attribution 3.0 Unported
/* You are free:
/*	to Share — to copy, distribute and transmit the work
/*	to Remix — to adapt the work
/*
/* Under the following conditions:
/* Attribution. You must attribute the work in the manner specified by the author or licensor 
/* (but not in any way that suggests that they endorse you or your use of the work).
/*
/*****************************************************************************************/

#ifndef _PIECES_
#define _PIECES_

#define KIND 7
#define ROTATION 4
#define HORIZONTAL_BLOCKS 5
#define VERTICAL_BLOCKS 5
#define POSITION 2

// --------------------------------------------------------------------------------
//									 Pieces
// --------------------------------------------------------------------------------
class Pieces
{
public:
	int GetBlockType(const int pPiece, const int pRotation, const int pX, const int pY);
	int GetXInitialPosition(const int pPiece, const int pRotation);
	int GetYInitialPosition(const int pPiece, const int pRotation);
};

#endif // _PIECES_

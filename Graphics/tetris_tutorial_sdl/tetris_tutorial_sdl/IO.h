/*****************************************************************************************
/* File: IO.h
/* Desc: Class for handling inpung & drawing, it uses SDL for the rendering. Change the methods of this class
/*       in order to use a different renderer
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

#ifndef _IO_
#define _IO_

// ------ Includes -----
#ifndef LINUX
#include "SDL/include/SDL.h"							
#include "SDL/SDL_GfxPrimitives/SDL_gfxPrimitives.h"
#else
#include <SDL/SDL.h>									
#include "SDL/SDL_GfxPrimitives/sdl_gfxprimitives.h"	
#endif
#pragma comment (lib, "SDL/lib/SDL.lib")
#pragma comment (lib, "SDL/SDL_GfxPrimitives/SDL_GfxPrimitives_Static.lib")

#define VIDEO_W 640
#define VIDEO_H 480

// ------ Enums -----
enum color { BLACK, RED, GREEN, BLUE, CYAN, MAGENTA, YELLOW, WHITE, COLOR_MAX }; // Colors

// --------------------------------------------------------------------------------
//									 IO
// --------------------------------------------------------------------------------
class IO
{
public:
	IO();

	void DrawRectangle(const int pX1, const int pY1, const int pX2, const int pY2, const enum color pC);
	void ClearScreen();
	int GetScreenHeight();
	int InitGraph();
	int Pollkey();
	int Getkey();
	int IsKeyDown(const int pKey);
	void UpdateScreen();
private:
	static SDL_Surface* mScreen;	// Screen
	static Uint32 mColors[COLOR_MAX];
};

#endif // _IO_

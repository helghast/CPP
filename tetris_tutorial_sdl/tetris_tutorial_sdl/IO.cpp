/*****************************************************************************************
/* File: IO.cpp
/* Desc: Class for handling inpung & drawing, it uses SDL for the rendering. Change the methods 
/* of this class in order to use a different renderer
/*       
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

// ------ Includes -----
#include "IO.h"

SDL_Surface* IO::mScreen = nullptr;	// Screen
Uint32 IO::mColors[COLOR_MAX] = { 0x000000ff, 0xff0000ff, 0x00ff00ff, 0x0000ffff, 0x00ffffff, 0xff00ffff, 0xffff00ff, 0xffffffff }; // Colors

/* ======================================									
Init
====================================== */
IO::IO() 
{
	InitGraph();
}

/* ======================================									
Clear the screen to black
====================================== */
void IO::ClearScreen() 
{
	boxColor(mScreen, 0, 0, mScreen->w - 1, mScreen->h - 1, mColors[BLACK]);
}

/* ======================================									
Draw a rectangle of a given color

Parameters:
>> pX1, pY1: 		Upper left corner of the rectangle
>> pX2, pY2: 		Lower right corner of the rectangle
>> pC				Rectangle color
====================================== */
void IO::DrawRectangle(const int pX1, const int pY1, const int pX2, const int pY2, const enum color pC)
{
	boxColor(mScreen, pX1, pY1, pX2, pY2 - 1, mColors[pC]);
}

/* ======================================									
Return the screen height
====================================== */
int IO::GetScreenHeight()
{
	return mScreen->h;
}

/* ======================================									
Update screen
====================================== */
void IO::UpdateScreen()
{
	SDL_Flip(mScreen);
}

/* ======================================									
Keyboard Input
====================================== */
int IO::Pollkey()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) 
	{
		switch (event.type) 
		{
			case SDL_KEYDOWN:
				return event.key.keysym.sym;
			case SDL_QUIT:
				exit(3);
		}
	}
	return -1;
}

/* ======================================									
Keyboard Input
====================================== */
int IO::Getkey()
{
	SDL_Event event;
	while (true)
	{
		SDL_WaitEvent(&event);
		switch (event.type)
		{
			case SDL_KEYDOWN:
				break;
			case SDL_QUIT:
				exit(3);
		}
	};
	return event.key.keysym.sym;
}

/* ======================================									
Keyboard Input
====================================== */
int IO::IsKeyDown(const int pKey)
{
	Uint8* mKeytable;
	int mNumkeys;
	SDL_PumpEvents();
	mKeytable = SDL_GetKeyState(&mNumkeys);
	return mKeytable[pKey];
}

/* ======================================									
SDL Graphical Initialization
====================================== */
int IO::InitGraph()
{
	const SDL_VideoInfo* info;
	Uint8 video_bpp;
	Uint32 videoflags;
        
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) 
	{
		fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
		return 1;
	}
	atexit(SDL_Quit);

	// Alpha blending doesn't work well at 8-bit color
	info = SDL_GetVideoInfo();
	video_bpp = (info->vfmt->BitsPerPixel > 8) ? info->vfmt->BitsPerPixel : 16;
	videoflags = SDL_SWSURFACE | SDL_DOUBLEBUF;
	
	// Set 640x480 video mode
	if ((mScreen = SDL_SetVideoMode(VIDEO_W, VIDEO_H, video_bpp, videoflags)) == NULL)
	{
		fprintf(stderr, "Couldn't set %ix%i video mode: %s\n", VIDEO_W, VIDEO_H, SDL_GetError());
		return 2;
	}
    return 0;
}

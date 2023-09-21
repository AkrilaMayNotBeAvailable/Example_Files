#ifndef HEADER_MANAGER_H
#define HEADER_MANAGER_H
//======================================================
//  Libraries
//======================================================
#include <raylib.h>								// Main Library
#include <stdio.h>								// File management
#include "sqlite3.h"							// To include SQlite database
//=======================================================
//	Window Configurations
//=======================================================
#define HEIGHT GetScreenHeight()
#define WIDTH GetScreenWidth()
#define TITLE "Database Include Example"
#define FPS 60
//=======================================================
//	In-game Definitions
//=======================================================
#define STRING_SIZE 256
//=======================================================
//	Structures && Enums
//=======================================================
typedef enum{
	DATABASE_NOT_FOUND,
	DATABASE_NOT_CONNECTED,
	ERROR_NONE
} ERRORCODE_e;

#endif

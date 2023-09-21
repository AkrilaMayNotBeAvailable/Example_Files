#include "header_manager.h"

// Headers
//============================
// Basic Settings:
void WindowBasicSettings();
void CloseBasicSettings();

// File checking:
int FileChecking(const char *filename);
int ExecuteQuery(const char *fp, const char *query, char *str);
ERRORCODE_e DataIntegrity(char *string);

int main(){	
	char string[STRING_SIZE] = { 0 }; // This is the string we will try to fill
	ERRORCODE_e errorCheck = ERROR_NONE; // This checks error
	
	// OpenGL context starts under this function
	//============================================
	WindowBasicSettings(); 
	errorCheck = DataIntegrity(string);

	while(!WindowShouldClose()){
		// Variable Update
		//============================================
		
		
		// Graphic ambient
		//============================================
		BeginDrawing();
		ClearBackground(BLACK);
		
		if(errorCheck != ERROR_NONE){
			switch(errorCheck){
				case DATABASE_NOT_FOUND:
					DrawText("Database wasn't found! Try again!", 20, HEIGHT/2, 20, RED);
					break;
				case DATABASE_NOT_CONNECTED:
					DrawText("There was a error while connecting to Database", 20, HEIGHT/2, 20, RED);
					break;
				default:
					break;
			}
		}
		else{
			DrawText(string, 20, HEIGHT/2, 20, GREEN);
		}
		
		EndDrawing();
	}
	
	// This closes OpenGL context
	//============================================
	CloseBasicSettings();
	
	return 0;
}


// Initialize basic elements:
void WindowBasicSettings(){
	InitWindow(WIDTH, HEIGHT, TITLE);	// Initialize Window:
	SetTargetFPS(FPS);	// Set FPS:
}

// Closes window and other devices
void CloseBasicSettings(){
	CloseWindow(); // Close Window
}

// Checks if a file exists.
// Given a string, tries to open a file returns true if file was found
// else returns false.
int FileChecking(const char *filename){
	FILE *file = fopen(filename, "r");
	if(file){
		fclose(file);
		return 1; // File was found
	} else {
		return 0; // File not found
	}
}

// Checks if database exists and tries a connection to
// get a string from the database file.
// Returns a error code enum value.
// This is being hardcoded for example purposes.
ERRORCODE_e DataIntegrity(char *string){
	const char *database = "Database/example.db";
	if(!FileChecking(database)){
		return DATABASE_NOT_FOUND;
	}
	
	const char *query = "SELECT str FROM example";
	if(ExecuteQuery(database, query, string)){
		return DATABASE_NOT_CONNECTED;
	}

	return ERROR_NONE;
}


// Executes a SQL query
// Given a file path, a query, and a string
// Tries to get a string from the determined fp and query
// and fill the string on 3rd argument.
// Returns SQLite error codes.
int ExecuteQuery(const char *fp, const char *query, char *str){
  sqlite3 *db;
  sqlite3_stmt *stmt;
  int rc;

  // SQLite function to open file:
  rc = sqlite3_open(fp, &db);
  if (rc != SQLITE_OK) {
		fprintf(stderr, "Error opening database: %s\n", sqlite3_errmsg(db));
		return rc; // SQLite Error code
	}
  
  // Prepares to get data from Database file
  rc = sqlite3_prepare_v2(db, query, -1, &stmt, 0);
  if(rc != SQLITE_OK){
		fprintf(stderr, "Error preparing query: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db); // Close file if error
		return rc; // SQLite Error code
	}

  while((rc = sqlite3_step(stmt)) == SQLITE_ROW){
		const unsigned char *phrase = sqlite3_column_text(stmt, 0);    		// Gets string on column 0
		// While phrase != 0
		if(phrase){
		  snprintf(str, STRING_SIZE, "%s", phrase);
		}
  }
  
  // Something went wrong
	if(rc != SQLITE_DONE){
		fprintf(stderr, "Error while executing query: %s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return rc; // SQLite error code
	}
	
  // Free memory resources
  sqlite3_finalize(stmt);

  // SQLite function to close file
  sqlite3_close(db);

  return SQLITE_OK; // This is zero.
}


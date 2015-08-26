
#ifndef CS_32_Proj_1_utilites_h
#define CS_32_Proj_1_utilites_h

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function declarations
///////////////////////////////////////////////////////////////////////////

int decodeDirection(char dir);
bool directionToDeltas(int dir, int& rowDelta, int& colDelta);
void clearScreen();
bool destroyOneSnake(int r, int c);
int numberOfSnakesAt(int r, int c);

const char ARROW_LEFT  = 'l';
const char ARROW_RIGHT = 'r';
const char ARROW_UP    = 'u';
const char ARROW_DOWN  = 'd';

char getCharacter();

#endif

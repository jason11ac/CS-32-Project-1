
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cassert>

#include "Game.h"
#include "Pit.h"
#include "Player.h"

using namespace std;



///////////////////////////////////////////////////////////////////////////
//  main()
///////////////////////////////////////////////////////////////////////////



int main()
{
    
    // Initialize the random number generator.
    srand(static_cast<unsigned int>(time(0)));
    
    // Create a game
    // Use this instead to create a mini-game:   Game g(3, 3, 2);
    Game g(10, 10, 10);
    
    // Play the game
    g.play();
    
    
}



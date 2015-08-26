
#include <stdio.h>
#include "Game.h"
#include "globals.h"
#include "Pit.h"
#include "Player.h"
#include "utilites.h"

#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;


///////////////////////////////////////////////////////////////////////////
//  Game implementations
///////////////////////////////////////////////////////////////////////////

Game::Game(int rows, int cols, int nSnakes)
{
    if (nSnakes > MAXSNAKES)
    {
        cout << "***** Trying to create Game with " << nSnakes
        << " snakes; only " << MAXSNAKES << " are allowed!" << endl;
        exit(1);
    }
    
    // Create pit
    m_pit = new Pit(rows, cols);
    
    // Add player
    int rPlayer = 1 + rand() % rows;
    int cPlayer = 1 + rand() % cols;
    m_pit->addPlayer(rPlayer, cPlayer);
    
    // Populate with snakes
    while (nSnakes > 0)
    {
        int r = 1 + rand() % rows;
        int c = 1 + rand() % cols;
        // Don't put a snake where the player is
        if (r == rPlayer  &&  c == cPlayer)
            continue;
        m_pit->addSnake(r, c);
        nSnakes--;
    }
}

Game::~Game()
{
    delete m_pit;
}

void Game::play()
{
    Player* p = m_pit->player();
    if (p == nullptr)
    {
        m_pit->display("");
        return;
    }
    string msg = "";
    do
    {
        m_pit->display(msg);
        msg = "";
        cout << endl;
        cout << "Move (up/down/left/right//quit): ";
        char action;
        action = getCharacter();
        
        //getline(cin,action);
        if (isblank(action))
            p->stand();
        else
        {
            switch (action)
            {
                default:   // if bad move, nobody moves
                    cout << '\a' << endl;  // beep
                    continue;
                case 'q':
                    return;
                case 'u':
                case 'd':
                case 'l':
                case 'r':
                    p->move(decodeDirection(action));
                    break;
            }
        }
        m_pit->moveSnakes();
    } while ( ! m_pit->player()->isDead()  &&  m_pit->snakeCount() > 0);
    m_pit->display(msg);
}

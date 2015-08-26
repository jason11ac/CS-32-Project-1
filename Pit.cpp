
#include "Pit.h"
#include "Snake.h"
#include "Player.h"
#include "globals.h"
#include "utilites.h"

#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;


///////////////////////////////////////////////////////////////////////////
//  Pit implementations
///////////////////////////////////////////////////////////////////////////

Pit::Pit(int nRows, int nCols)
{
    if (nRows <= 0  ||  nCols <= 0  ||  nRows > MAXROWS  ||  nCols > MAXCOLS)
    {
        cout << "***** Pit created with invalid size " << nRows << " by "
        << nCols << "!" << endl;
        exit(1);
    }
    m_rows = nRows;
    m_cols = nCols;
    m_player = nullptr;
    m_nSnakes = 0;
}

Pit::~Pit()
{
    
    delete m_player;
    for (int i = 0; i < m_nSnakes; i++)
        delete m_snakes[i];
}

int Pit::rows() const
{
    return m_rows;
}

int Pit::cols() const
{
    return m_cols;
}

Player* Pit::player() const
{
    return m_player;
}

int Pit::snakeCount() const
{
    return m_nSnakes;
}

int Pit::numberOfSnakesAt(int r, int c) const
{
    int count = 0;
    for (int i = 0; i < m_nSnakes; i++)
    {
        if (m_snakes[i]->row() == r && m_snakes[i]->col() == c)
        {
            count++;
        }
    }
    return count;
}

void Pit::display(string msg) const
{
    // Position (row,col) in the pit coordinate system is represented in
    // the array element grid[row-1][col-1]
    char grid[MAXROWS][MAXCOLS];
    int r, c = 0;
    
    // Fill the grid with dots
    for (r = 0; r < rows(); r++)
        for (c = 0; c < cols(); c++)
            grid[r][c] = '.';
    
    // Indicate each snake's position
    if (m_snakes != nullptr)
    {
        for (int i = 0; i < m_nSnakes; i++)
        {
            char& gridChar = grid[m_snakes[i]->row()-1][m_snakes[i]->col()-1];
            switch (gridChar)
            {
                case '.':
                    gridChar = 'S';
                    break;
                case 'S':
                    gridChar = '2';
                    break;
                case '2':
                    gridChar = '3';
                    break;
                case '3':
                    gridChar = '4';
                    break;
                case '4':
                    gridChar = '5';
                    break;
                case '5':
                    gridChar = '6';
                    break;
                case '6':
                    gridChar = '7';
                    break;
                case '7':
                    gridChar = '8';
                    break;
                case '8':
                    gridChar = '9';
                    break;
                default:
                    gridChar = '9';
                    break;
                    
            }
        }
    }
    
    
    
    // Indicate player's position
    if (m_player != nullptr)
    {
        char& gridChar = grid[m_player->row()-1][m_player->col()-1];
        if (m_player->isDead())
            gridChar = '*';
        else
            gridChar = '@';
    }
    
    // Draw the grid
    clearScreen();
    for (r = 0; r < rows(); r++)
    {
        for (c = 0; c < cols(); c++)
            cout << grid[r][c];
        cout << endl;
    }
    cout << endl;
    
    // Write message, snake, and player info
    cout << endl;
    if (msg != "")
        cout << msg << endl;
    cout << "There are " << snakeCount() << " snakes remaining." << endl;
    if (m_player == nullptr)
        cout << "There is no player." << endl;
    else
    {
        if (m_player->age() > 0)
            cout << "The player has lasted " << m_player->age() << " steps." << endl;
        if (m_player->isDead())
            cout << "The player is dead." << endl;
    }
}

bool Pit::addSnake(int r, int c)
{
    if (m_nSnakes == MAXSNAKES)
        return false;
    
    
    m_snakes[m_nSnakes] = new Snake(this, r, c);
    m_nSnakes++;
    return true;
}

bool Pit::addPlayer(int r, int c)
{
    // Don't add a player if one already exists
    if (m_player != nullptr)
        return false;
    
    // Dynamically allocate a new Player and add it to the pit
    m_player = new Player(this, r, c);
    return true;
}

bool Pit::destroyOneSnake(int r, int c)
{
    int i = 0;
    int happen = 0;
    for (; i < m_nSnakes; i++)
    {
        if (m_snakes[i]->row() == r && m_snakes[i]->col() == c)
        {
            delete m_snakes[i];
            happen++;
            break;
        }
    }
    if (happen)
    {
        for (; i < m_nSnakes; i++)
        {
            m_snakes[i] = m_snakes[i + 1];
        }
        m_nSnakes--;
        return true;
    }
    return false;
}

bool Pit::moveSnakes()
{
    
    for (int k = 0; k < m_nSnakes; k++)
    {
        m_snakes[k]->move();
    }
    
    for (int i = 0; i < m_nSnakes; i++)
    {
        if ((m_snakes[i]->row() == player()->row()) && (m_snakes[i]->col() == player()->col()))
        {
            m_player->setDead();
            return false;
        }
    }
    
    // return true if the player is still alive, false otherwise
    return true;
}


#include "Pit.h"
#include "Player.h"
#include "globals.h"

#include <iostream>
#include <cstdlib>

using namespace std;

///////////////////////////////////////////////////////////////////////////
//  Player implementations
///////////////////////////////////////////////////////////////////////////

Player::Player(Pit* pp, int r, int c)
{
    if (pp == nullptr)
    {
        cout << "***** The player must be in some Pit!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > pp->rows()  ||  c < 1  ||  c > pp->cols())
    {
        cout << "**** Player created with invalid coordinates (" << r
        << "," << c << ")!" << endl;
        exit(1);
    }
    m_pit = pp;
    m_row = r;
    m_col = c;
    m_age = 0;
    m_dead = false;
}

int Player::row() const
{
    return m_row;
}

int Player::col() const
{
    return m_col;
}

int Player::age() const
{
    return m_age;
}

void Player::stand()
{
    m_age++;
}

void Player::move(int dir)
{
    m_age++;
    
    if (dir == UP)
    {
        if (m_row == 1)
            return;
        if (m_pit->numberOfSnakesAt(m_row - 1, m_col) == 0)
            m_row = m_row - 1;
        else
        {
            if ((m_row - 2) < 1)
            {
                return;
            }
            
            else
            {
                m_pit->destroyOneSnake((m_row - 1), m_col);
                if (m_pit->numberOfSnakesAt((m_row - 2), m_col) != 0)
                {
                    m_row = m_row - 2;
                    setDead();
                }
                else
                    m_row = m_row - 2;
                
            }
        }
    }
    if (dir == LEFT)
    {
        if (m_col == 1)
            return;
        if (m_pit->numberOfSnakesAt(m_row, m_col - 1) == 0)
            m_col = m_col - 1;
        else
        {
            if ((m_col - 2) < 1)
            {
                return;
            }
            
            else
            {
                m_pit->destroyOneSnake((m_row), (m_col - 1));
                if (m_pit->numberOfSnakesAt(m_row, (m_col - 2)) != 0)
                {
                    m_col = m_col - 2;
                    setDead();
                }
                else
                    m_col = m_col - 2;
            }
            
        }
    }
    if (dir == RIGHT)
    {
        if (m_col == (m_pit->cols()))
            return;
        if (m_pit->numberOfSnakesAt(m_row, m_col +  1) == 0)
            m_col = m_col + 1;
        else
        {
            if ((m_col + 2) > m_pit->cols())
            {
                return;
            }
            else
            {
                m_pit->destroyOneSnake((m_row), (m_col + 1));
                if (m_pit->numberOfSnakesAt(m_row, (m_col + 2)) != 0)
                {
                    m_col = m_col + 2;
                    setDead();
                }
                else
                    m_col = m_col + 2;
            }
        }
    }
    if (dir == DOWN)
    {
        if (m_row == (m_pit->rows()))
            return;
        if (m_pit->numberOfSnakesAt(m_row + 1, m_col) == 0)
            m_row = m_row + 1;
        else
        {
            if ((m_row + 2) > m_pit->rows())
            {
                return;
            }
            else
            {
                m_pit->destroyOneSnake((m_row + 1), m_col);
                if (m_pit->numberOfSnakesAt((m_row + 2), m_col) != 0)
                {
                    m_row = m_row + 2;
                    setDead();
                }
                else
                    m_row = m_row + 2;
            }
        }
    }
    
}

bool Player::isDead() const
{
    return m_dead;
}

void Player::setDead()
{
    m_dead = true;
}


#include "Pit.h"
#include "Snake.h"
#include "globals.h"

#include <iostream>
#include <cstdlib>

using namespace std;


///////////////////////////////////////////////////////////////////////////
//  Snake implementation
///////////////////////////////////////////////////////////////////////////

Snake::Snake(Pit* pp, int r, int c)
{
    if (pp == nullptr)
    {
        cout << "***** A snake must be in some Pit!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > pp->rows()  ||  c < 1  ||  c > pp->cols())
    {
        cout << "***** Snake created with invalid coordinates (" << r << ","
        << c << ")!" << endl;
        exit(1);
    }
    m_pit = pp;
    m_row = r;
    m_col = c;
}

int Snake::row() const
{
    return m_row;
}

int Snake::col() const
{
    return m_col;
}

void Snake::move()
{
    // Attempt to move in a random direction; if we can't move, don't move
    switch (rand() % 4)
    {
        case UP:
            if (m_row == 1)
                return;
            else
            {
                m_row -= 1;
                break;
            }
        case DOWN:
            if (m_row == (m_pit->rows()))
                return;
            else
            {
                m_row += 1;
                break;
            }
        case LEFT:
            if (m_col == 1)
                return;
            else
            {
                m_col -= 1;
                break;
            }
        case RIGHT:
            if (m_col == (m_pit->cols()))
                return;
            else
            {
                m_col += 1;
                break;
            }
    }
}


#ifndef CS_32_Proj_1_Game_h
#define CS_32_Proj_1_Game_h

class Pit;

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nSnakes);
    ~Game();
    
    // Mutators
    void play();
    
private:
    Pit* m_pit;
};


#endif

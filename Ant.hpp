/** Author Stephane LE BOEUF : stephane.leboeuf@digital-lab.fr **/

#pragma once

#include "Game.hpp"

class ivec2
{
public:
    ivec2(): x(0), y(0) {}
    ivec2(int i): x(i), y(i) {}
    ivec2(int xx, int yy): x(xx), y(yy) {}

    void clamp(int min, int max)
    {
        x = (x < min) ? min : ( x >= max ) ? max - 1 : x;
        y = (y < min) ? min : ( y >= max ) ? max - 1 : y;
    }

    ivec2& operator +=(ivec2 b)
    {
        x += b.x;
        y += b.y;
    }

    int x,y;
};

class Ant
{
public:
    Ant() : m_position(256,256),
            m_direction(0,1),
            m_size(512),
            m_state(0) {}

    Ant(int size) : m_position(size/2,size/2),
            m_direction(0,1),
            m_size(size),
            m_state(0) {}

    /**
      Nota (Turn) :
        1 = Forward,
        2 = Right,
        4 = U-Turn,
        8 = Left

      **/
    void turn(int direction);
    void updatePosition();
    void visit( Game * game);

private:
    ivec2 m_position;
    ivec2 m_direction;
    int m_size;
    int m_state;
};

/** Author Stephane LE BOEUF : stephane.leboeuf@digital-lab.fr **/

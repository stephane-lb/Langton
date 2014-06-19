/** Author Stephane LE BOEUF : stephane.leboeuf@digital-lab.fr **/

#pragma once

#include "CImg.h"
#define uchar unsigned char
using namespace cimg_library;

// < NEW COLOR, ANGLE, NEW STATE >
/**
  Nota (Angle) :
    1 = Forward,
    2 = Right,
    4 = U-Turn,
    8 = Left

  **/
class Triplet
{
public:
    // Default constructor : create an impossile triplet
    Triplet():
        colorIndex(-1),
        turn(0),
        antState(-1) {}

    Triplet(int colorIndex, int turn, int antState):
        colorIndex(colorIndex),
        turn(turn),
        antState(antState) {}

    int turn;
    int colorIndex;
    int antState;

};

class Game
{
public:
    Game();
    Game(const char * filename);
    ~Game();
    Triplet getTriplet(int x, int y);
    uchar* getColor(int index);
    int getIndex(uchar r, uchar g, uchar b);
    int getSize();

private:
    void spirale();

    int m_stateCard, m_colorCard, m_size ;
    Triplet **m_automate;
    uchar   **m_color;

public:
    CImg<uchar> map;
};

/** Author Stephane LE BOEUF : stephane.leboeuf@digital-lab.fr **/

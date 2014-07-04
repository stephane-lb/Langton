/** Author Stephane LE BOEUF : stephane.leboeuf@digital-lab.fr **/

#include "Game.hpp"
#include <fstream>
#include <sstream>
#include <cstdio> // sscanf
#include <vector>
#include <iostream>

Game::Game()
{
    spirale();
}

Game::Game(const char * filename)
{
    std::ifstream infile(filename);
    if (!infile.is_open())
        std::cout << "File not found" << std::endl;

    std::string line;
    std::vector<int>::iterator tableIt;

    bool colorsPlease = false;
    bool rulesPlease = false;
    bool ok = false;

    int cpt = 0; // count the number of color or the number of rules


    while(std::getline(infile, line))
    {
        // comments and new lines
        if (line[0] == '\n')
            continue;
        if (line[0] == '#')
            continue;
        // create the game

        if(!colorsPlease && !rulesPlease)
        {
            if(sscanf(line.c_str(), "size %d", &m_size) == 1)
            {
                map.resize(m_size, m_size, 1, 3);
                map.fill(255);
            }
            if(sscanf(line.c_str(), "nbstates %d", &m_stateCard) == 1)
            {
                m_automate = new Triplet*[m_stateCard];
            }
            if(sscanf(line.c_str(), "nbcolors %d", &m_colorCard) == 1)
            {

                for(int i = 0; i < m_stateCard; ++i)
                    m_automate[i] = new Triplet[m_colorCard];
                m_color = new uchar*[m_colorCard];
                colorsPlease = true;
            }
        }
        else if(colorsPlease)
        {
            int r,g,b;
            if(sscanf(line.c_str(), "%d %d %d", &r, &g, &b) == 3)
            {
                m_color[cpt]= new uchar[3];
                m_color[cpt][0] = r;
                m_color[cpt][1] = g;
                m_color[cpt][2] = b;
                cpt++;
            }

            if( cpt >= m_colorCard)
            {
                colorsPlease = false;
                rulesPlease = true;
                cpt = 0;
            }
        }
        else if(rulesPlease)
        {

            int color, turn, state;
            if(sscanf(line.c_str(), "%d %d %d", &color, &turn, &state) == 3)
            {
                int i = cpt / m_stateCard;
                int j = cpt - i * m_stateCard ;

                m_automate[i][j] = Triplet(color, turn, state);

                cpt++;
            }

            if( cpt >= m_colorCard*m_stateCard)
            {
                colorsPlease = false;
                rulesPlease = false;
                ok = true;
                break;
            }
        }
    }

    if(!ok)
        std::cout << "your config file is corrupted" << std::endl;
}

Game::~Game()
{
        for(int i = 0; i < m_stateCard; ++i)
            delete [] m_automate[i];
        delete [] m_automate;

        for(int i = 0; i < m_colorCard; ++i)
            delete [] m_color[i];
        delete [] m_color;
}

Triplet Game::getTriplet(int x, int y)
{
    return m_automate[x][y];
}

uchar* Game::getColor(int index)
{
    return m_color[index];
}

int Game::getIndex(uchar r, uchar g, uchar b)
{
    for(int i = 0; i< m_colorCard; ++i)
    {
        if ( m_color[i][0] == r && m_color[i][1] == g && m_color[i][2] == b)
            return i;
    }
    return -1;
}

int Game::getSize()
{
    return m_size;
}

void Game::spirale()
{
    map.resize(512, 512, 1, 3);
    map.fill(255);
    m_size = 512;

    m_stateCard = 2;
    m_colorCard = 2;
    m_automate = new Triplet*[m_stateCard];
    for(int i = 0; i < m_stateCard; ++i)
        m_automate[i] = new Triplet[m_colorCard];

    m_automate[0][0] = Triplet(1, 1, 1);
    m_automate[0][1] = Triplet(1, 8, 0);
    m_automate[1][0] = Triplet(1, 2, 1);
    m_automate[1][1] = Triplet(0, 1, 0);

    m_color = new uchar*[m_colorCard];
    m_color[0] = new uchar[3];
    m_color[0][0] = 255;
    m_color[0][1] = 255;
    m_color[0][2] = 255;
    m_color[1] = new uchar[3];
    m_color[1][0] = 0;
    m_color[1][1] = 0;
    m_color[1][2] = 0;
}

/** Author Stephane LE BOEUF : stephane.leboeuf@digital-lab.fr **/

/** Author Stephane LE BOEUF : stephane.leboeuf@digital-lab.fr **/

#include "Ant.hpp"

void Ant::turn(int direction)
{
    // No turn
    if (direction == 1)
    {
        return;
    }
    // Right
    else if (direction == 2)
    {
        if(m_direction.x == 0)
        {
            m_direction.x = ( m_direction.y < 0 )? -1 : 1;
            m_direction.y = 0;
        }
        else
        {
            m_direction.y = ( m_direction.x < 0 )? 1 : -1;
            m_direction.x = 0;
        }
    }
    else if (direction == 4)
    {
        m_direction.x = -m_direction.x;
        m_direction.y = -m_direction.y;
        return;
    }
    // Left
    else if (direction == 8)
    {
        if(m_direction.x == 0)
        {
            m_direction.x = ( m_direction.y < 0 )? 1 : -1;
            m_direction.y = 0;
        }
        else
        {
            m_direction.y = ( m_direction.x < 0 )? -1 : 1;
            m_direction.x = 0;
        }
    }


}

void Ant::updatePosition()
{
    m_position += m_direction;
    m_position.clamp(0, m_size);
}

void Ant::visit( Game * game)
{
    int indexColor = game->getIndex(  game->map(m_position.x,m_position.y,0,0),
                                      game->map(m_position.x,m_position.y,0,1),
                                      game->map(m_position.x,m_position.y,0,2));
    Triplet play = game->getTriplet(m_state, indexColor);
    turn(play.turn);
    uchar* color = game->getColor(play.colorIndex);
    game->map.draw_point(m_position.x, m_position.y,  color);
    m_state = play.antState;
}

/** Author Stephane LE BOEUF : stephane.leboeuf@digital-lab.fr **/

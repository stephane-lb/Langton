/** Author Stephane LE BOEUF : stephane.leboeuf@digital-lab.fr **/

#include "Ant.hpp"
#include <unistd.h>

int main(int argc, char** argv)
{ 
    int c;
    const char * config = NULL;
    const char * output = NULL;
    bool display = true;
    int iter = 0;

    while ((c = getopt (argc, argv, "i:o:dhn:")) != -1)
    {
        switch (c)
        {
            case 'i':
            {
                config = optarg;
                break;
            }
            case 'o':
            {
                output = optarg;
                break;
            }
            case 'd':
            {
                display = false;
                break;
            }
            case 'n':
            {
                iter = atoi(optarg);
                break;
            }
            case 'h':
            default:
            {
                std::cout << "-[ HELP ]-"<< std::endl;
                std::cout << "      -d          interactive display off" << std::endl;
                std::cout << "      -h          this help" << std::endl;
                std::cout << "      -i <string> use a config file ( cf gold.mpc )" << std::endl;
                std::cout << "      -o <string> output filename (PNG, JPEG ...)" << std::endl;
                std::cout << "      -n <int>    number of iteration ( 0 = infinity )" << std::endl;
                return 0;

            }
        }
    }

    Game * myGame;
    if(config)
        myGame = new Game(config);
    else
        myGame = new Game();

    Ant myAnt(myGame->getSize());

    CImgDisplay main_disp;

    if(display)
        main_disp.assign(myGame->map,"Ant");

    if( iter==0 && !display )
    {
        std::cout << "You do not display the result and you ask for an infinity simulation : somethng wrong" <<std::endl;
        return 0;
    }

    for(int i = 0; ( iter==0 || i < iter ) && (!display
                                               || !main_disp.is_closed()); ++i)
    {
        myAnt.visit(myGame);

        if(display)
            main_disp.display(myGame->map);

        myAnt.updatePosition();
        usleep(1000);
    }

    if(output)
        myGame->map.save(output);

    delete myGame;

    return 0;
}

/** Author Stephane LE BOEUF : stephane.leboeuf@digital-lab.fr **/

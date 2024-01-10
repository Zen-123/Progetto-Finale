#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include "showScoreboard.h"
#include "player.h"
#include "printScoreboard.h"



int main(int argc, char *argv[])
{

    if (argc > 1)
    {
        std::string word = argv[1];
        if (word == "H" || word == "h")     //TODO: Cambia parola iniziale
        {
            func();
            

        }
        else if (word == "C" || word == "c") //TODO: Cambia parola iniziale
        {
            std::cout << "Giocatori Computer! \n";
            ComputerPlayer P2("2");
            ComputerPlayer P3("3");
            ComputerPlayer P4("4");
        }
        else
        {
            std::cout << "Parola errata! \n";
        }
    }

    // func(P);
}

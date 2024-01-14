#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <fstream>
#include "../include/showScoreboard.h"
#include "../include/player.h"
#include "../include/printScoreboard.h"



int main(int argc, char *argv[])
{

    bool gameType = false;  //valore booleano per gestire partita con giocatore umano o con 4 giocatori computer, settato a true se si vuole giocare con un player umano
    if (argc > 1)
    {
        std::string word = argv[1];
        if (word == "H" || word == "h")     //TODO: Cambia parola iniziale
        {
            gameType =true;
            game(gameType);


        }
        else if (word == "C" || word == "c") //TODO: Cambia parola iniziale
        {

           game(gameType);

        }
        else
        {
            std::cout << "Parola errata! \n";
        }
    }

    // func(P);
}

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <fstream>
#include "../include/square.h"
#include "../include/player.h"
#include "../include/game.h"



int main(int argc, char *argv[])
{

    bool gameType = false;  //valore booleano per gestire partita con giocatore umano o con 4 giocatori computer, settato a true se si vuole giocare con un player umano
    if (argc > 1)
    {
        std::string word = argv[1];
        if (word == "Human" || word == "human")   
        {
            gameType = true;
            game(gameType);


        }
        else if (word == "Computer" || word == "computer") 
        {

           game(gameType);

        }
        else
        {
            std::cout << "Parola errata! \n";
        }
    }

}

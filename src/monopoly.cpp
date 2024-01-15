#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <fstream>
#include "../include/squareLib/square.h"
#include "../include/playerLib/player.h" 
#include "../include/gameLib/game.h"
#include "../include/position.h"




int main(int argc, char *argv[])
{

    bool gameType = false;  //valore booleano per gestire partita con giocatore umano o con 4 giocatori computer, settato a true se si vuole giocare con un player umano
    if (argc > 1)
    {
        std::string word = argv[1];
        if (word == "Human" || word == "human")   
        {

            gameType = true;
            game(gameType, 20);
        }
        else if (word == "Computer" || word == "computer") 
        {

           game(gameType, 50);


        }
        else
        {
            std::cout << "Parola errata! \n";
        }
    }

}

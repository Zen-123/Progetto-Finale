#ifndef PLAYER_H
#define PLAYER_H

#include "../../include/position.h"    

class Player : public Position
{
protected:
    int budget = 100;
    std::string playerChar;
    Position pos;
    bool bankrupt = false;
    std::vector<Position> purchasedSquare;
public:

    Player();

    Player(std::string playerChar);

    int throwDice();

    void increaseBudget(){ this->budget = this->budget + 20; }

    void increaseBudgetRent(int price){ this->budget = this->budget + price; }
        
    void decrescenteBudgetRent(int price){  this->budget = this->budget - price; }

    int getBudget() const { return this->budget; }

    std::string getChar() const { return this->playerChar; }

    void setPosition(int i, int j, std::string charSquare);

    void setBankrupt(){ this->bankrupt = true; }

    int getPositionI() const { return this->pos.getPosI(); }

    int getPositionJ() const {return this->pos.getPosJ(); }

    std::string getPositionChar() const{ return this->pos.getCharSquare();}

    Position getPosition() const{ return this->pos; }

    bool checkIfBankrupt();

    void removePlayerCharIfBankrupt(std::string board[9][9], EconomicSquare& E, StandardSquare& S, LuxurySquare& L);

    void logOutput(const std::string& txt) const;


    bool checkPurchaseSquare(std::string board[9][9], EconomicSquare& E,StandardSquare& S, LuxurySquare& L );

    bool checkPurchaseHouse( std::string board[9][9], EconomicSquare& E,StandardSquare& S, LuxurySquare& L);

    bool checkPurchaseHotel( std::string board[9][9], EconomicSquare& E,StandardSquare& S, LuxurySquare& L);

    void printStatus() const;

    std::vector<Position> getProperty() const{ return this->purchasedSquare; }

    std::string convertRowToChar() const;

    ~Player() {}
};


class ComputerPlayer : public Player{
public:

    ComputerPlayer(std::string p):Player(p){}

    bool randomChoice() const;

    ~ComputerPlayer() {}

};

class HumanPlayer : public Player {
public:
    HumanPlayer(std::string p) : Player(p) {}

    // Funzione che richiede all'utente di fare una scelta (true o false)
    bool getUserChoice(std::string board[9][9], EconomicSquare E, StandardSquare S, LuxurySquare L);

    ~HumanPlayer() {}
};

#include "player.hpp"
#endif

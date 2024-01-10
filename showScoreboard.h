#ifndef SQUARE_H
#define SQUARE_H

class Square
{
protected:
    int price;
    std::string player;
    std::string SquareType;
    char home = '*';
    char hotel = '^';
public:

    Square(){}

    char getCharHome(){
        return '*';
    }

    char getCharHotel(){
        return '^';
    }

    virtual int getPrice() = 0;

    virtual std::string ShowSquare() = 0;

    void setPlayer(std::string p){
        this->player = p;
    }

    char buyHouse(std::string p){
        setPlayer(p);
        return this->home;
    }

    char buyHotel(std::string p){
        setPlayer(p);
        return this->hotel;
    }
    
    std::string getPlayer(){
        return this->player;
    }
    ~Square() {}

};


class AngularSquare : public Square {
private:
    std::string SquareType = " ";
public:
    AngularSquare() {}

    std::string ShowSquare(){
        return this->SquareType;
    }

    int getPrice(){
        return 0;
    }
    ~AngularSquare() {}

};

class EconomicSquare : public Square {
private:
    std::string SquareType = "E";
    int price = 6;
public:
    EconomicSquare() {}

    std::string ShowSquare(){
        return this->SquareType;
    }

    int getPrice(){
        return this->price;
    }

    ~EconomicSquare() {}

  
};

class StandardSquare : public Square {
private:
    std::string SquareType = "S";
    int price = 10;
public:
    StandardSquare() {}

    int getPrice(){
        return this->price;
    }

    std::string ShowSquare(){
        return this->SquareType;
    }

    ~StandardSquare() {}
};

class LuxurySquare : public Square {
private:
    std::string SquareType = "L";
    int price = 20;
public:
    LuxurySquare() {}

    std::string ShowSquare(){
        return this->SquareType;
    }

     int getPrice(){
        return this->price;
    }

    ~LuxurySquare() {}

};

#include "player.h"

#endif
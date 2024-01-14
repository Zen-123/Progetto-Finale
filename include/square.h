#ifndef SQUARE_H
#define SQUARE_H

#include "../include/position.h"

class Square
{
protected:
    int price;
    int homePrice;
    int hotelPrice;
    int rentHomePrice;
    int rentHotelPrice;
    std::string player;
    std::string SquareType;
    std::string home = "*";
    std::string hotel = "^";
    Position playerPosition;
public:

    Square(){}

    std::string getCharHome(){
        return this->home;
    }

    std::string getCharHotel(){
        return this->hotel;
    }

    void setPrice(int price){
        this->price = price;
    }

    int getPrice(){
        return this->price;
    }

    void setSquareType(std::string type){
        this->SquareType = type;
    }

    virtual std::string ShowSquare() = 0;

    void setPlayer(std::string p, int i, int j);


    void setHomePrice(int price){
        this->homePrice = price;
    }

    int getHomePrice(){
        return this->homePrice;
    }

    void setHotelPrice(int price){
        this->hotelPrice = price;
    }

    int getHotelPrice(){
        return this->hotelPrice;
    }
    
    void setRentHome(int price){
        this->rentHomePrice  = price;
    }

    int getRentHomePrice(){
        return this->rentHomePrice;
    }

    void setRentHotel(int price){
        this->rentHotelPrice = price;
    }

    int getRentHotelPrice(){
        return this->rentHotelPrice;
    }

    void removePlayerPosition(int i, int j);

    std::string getPlayer(int i, int j);

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

    ~AngularSquare() {}

};

class EconomicSquare : public Square {
public:

    EconomicSquare();

    std::string ShowSquare(){
        return this->SquareType;
    }

    ~EconomicSquare() {}

  
};

class StandardSquare : public Square {
public:
    StandardSquare();

    int getPrice(){
        return this->price;
    }

    std::string ShowSquare(){
        return this->SquareType;
    }

    ~StandardSquare() {}
};

class LuxurySquare : public Square {
public:
    LuxurySquare();

    std::string ShowSquare(){
        return this->SquareType;
    }

     int getPrice(){
        return this->price;
    }

    ~LuxurySquare() {}

};

#include "square.hpp"

#endif
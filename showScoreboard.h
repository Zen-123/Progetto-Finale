#ifndef SQUARE_H
#define SQUARE_H

class Square
{
protected:
    int price;
    int homePrice;
    int hotelPrice;
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

    void setPlayer(std::string p){
        this->player = p;
    }

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

    ~AngularSquare() {}

};

class EconomicSquare : public Square {
public:
    EconomicSquare() {
        Square::setPrice(6);
        Square::setHomePrice(3);
        Square::setHotelPrice(3);
        Square::setSquareType("E");
    }

    std::string ShowSquare(){
        return this->SquareType;
    }

    ~EconomicSquare() {}

  
};

class StandardSquare : public Square {
public:
    StandardSquare() {
        Square::setPrice(10);
        Square::setHomePrice(5);
        Square::setHotelPrice(5);
        Square::setSquareType("S");
    }

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
    LuxurySquare() {
        Square::setPrice(20);
        Square::setHomePrice(10);
        Square::setHotelPrice(10);
        Square::setSquareType("L");
    }

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
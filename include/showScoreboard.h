#ifndef SQUARE_H
#define SQUARE_H

#include "player.hpp"

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

    void setPlayer(std::string p, int i, int j){
        this->player = p;
        this->playerPosition.i = i;
        this->playerPosition.j = j;
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

    void removePlayerPosition(int i, int j){
        this->playerPosition.i = 1;
        this->playerPosition.j = 1;
        this->player.clear();
    }

    std::string getPlayer(int i, int j){
        if(this->playerPosition.i == i && this->playerPosition.j == j)
            return this->player;
        else    
           return " ";
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
        Square::setRentHome(2);
        Square::setRentHotel(4);
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
        Square::setRentHome(4);
        Square::setRentHotel(8);
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
        Square::setRentHome(7);
        Square::setRentHotel(14);
    }

    std::string ShowSquare(){
        return this->SquareType;
    }

     int getPrice(){
        return this->price;
    }

    ~LuxurySquare() {}

};


#endif
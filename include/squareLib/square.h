#ifndef SQUARE_H
#define SQUARE_H

#include "../../include/position.h"

class Square : public Position
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

    std::string getCharHome() const { return this->home; }

    std::string getCharHotel() const{ return this->hotel; }

    void setPrice(const int price){ this->price = price; }

    int getPrice() const{ return this->price; }

    void setSquareType(const std::string& type){ this->SquareType = type; } 

    virtual std::string ShowSquare() const = 0;

    void setPlayer(const std::string& p,const int i, const int j);

    void setHomePrice(const int price){ this->homePrice = price; }

    int getHomePrice() const{ return this->homePrice; }

    void setHotelPrice(const int price){ this->hotelPrice = price; }

    int getHotelPrice() const{ return this->hotelPrice; }
    
    void setRentHome(const int price){ this->rentHomePrice  = price; }

    int getRentHomePrice() const { return this->rentHomePrice; }

    void setRentHotel(const int price){ this->rentHotelPrice = price; }

    int getRentHotelPrice() const{ return this->rentHotelPrice; }

    void removePlayerPosition(const int i,const int j);

    std::string getPlayer(const int i,const int j) const;

    ~Square() {}

};


class AngularSquare : public Square {
public:
    AngularSquare();

    std::string ShowSquare() const { return this->SquareType; }

    ~AngularSquare() {}

};

class EconomicSquare : public Square {
public:

    EconomicSquare();

    std::string ShowSquare() const { return this->SquareType; }

    ~EconomicSquare() {}

  
};

class StandardSquare : public Square {
public:
    StandardSquare();

    std::string ShowSquare() const { return this->SquareType; }

    ~StandardSquare() {}
};

class LuxurySquare : public Square {
public:
    LuxurySquare();

    std::string ShowSquare()const { return this->SquareType; }

    ~LuxurySquare() {}

};

#include "square.hpp"

#endif
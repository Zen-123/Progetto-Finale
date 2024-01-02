#ifndef SQUARE_H
#define SQUARE_H

class Square
{
protected:
    int price;
    char SquareType;
    bool checkPlayerLoss = false;
    bool checkHouse = false;
    bool checkHotel = false;
    bool checkPlayer = false;
public:

    Square(){}

    ~Square() {}

    virtual char ShowSquare() = 0;

};


class AngularSquare : public Square {
private:
    char SquareType = ' ';
public:
    AngularSquare() {}

    ~AngularSquare() {}

    char ShowSquare(){
        return this->SquareType;
    }

};

class EconomicSquare : public Square {
private:
    char SquareType = 'E';
    int price = 6;
public:
    EconomicSquare() {}

    ~EconomicSquare() {}

    char ShowSquare(){
        return this->SquareType;
    }

};

class StandardSquare : public Square {
private:
    char SquareType = 'S';
    int price = 10;
public:
    StandardSquare() {}

    ~StandardSquare() {}

    char ShowSquare(){
        return this->SquareType;
    }

};

class LuxurySquare : public Square {
private:
    char SquareType = 'L';
    int price = 20;
public:
    LuxurySquare() {}

    ~LuxurySquare() {}

    char ShowSquare(){
        return this->SquareType;
    }

};

#endif
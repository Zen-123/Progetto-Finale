//ALESSANDRO MARANGON
#ifndef POSITION_HPP
#define POSITION_HPP


struct Position{
    int i;
    int j;
    std::string charSqare;

    int getPosI() const{ return this->i; }

    int getPosJ() const{ return this->j; }
    
    std::string getCharSquare() const{ return this->charSqare; }

    bool operator== (const Position& d) const{ 
        if(this->i == d.i && this->j == d.j)
            return true;
        return false;
    }
};


#endif
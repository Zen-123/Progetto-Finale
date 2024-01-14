#ifndef POSITION_HPP
#define POSITION_HPP


struct Position{
    int i;
    int j;
    std::string charSqare;

    int getPosI(){
        return this->i;
    }

    int getPosJ(){
        return this->j;
    }
    
    std::string getCharSquare(){
        return this->charSqare;
    }

    bool operator== (const Position& d){  //overloading operatore per poter utilizzare la funzione std::find()
        if(this->i == d.i && this->j == d.j)
            return true;
        return false;
    }
};


#endif
//ALESSANDRO MARANGON
#ifndef SQUARE_HPP
#define SQUARE_HPP

void Square::setPlayer(const std::string& p,const int i,const int j){
    this->player = p;
    this->playerPosition.i = i;
    this->playerPosition.j = j;
}

void Square::removePlayerPosition(const int i,const int j){
    this->playerPosition.i = 1;
    this->playerPosition.j = 1;
    this->player.clear(); 
}

 std::string Square::getPlayer(const int i,const int j) const{
    if(this->playerPosition.getPosI() == i && this->playerPosition.getPosJ() == j)
        return this->player;
    else    
        return " ";
}

AngularSquare::AngularSquare(){
    Square::setSquareType(" ");
}

EconomicSquare::EconomicSquare(){
    Square::setPrice(6);
    Square::setHomePrice(3);
    Square::setHotelPrice(3);
    Square::setSquareType("E");
    Square::setRentHome(2);
    Square::setRentHotel(4);
}
StandardSquare::StandardSquare() {
    Square::setPrice(10);
    Square::setHomePrice(5);
    Square::setHotelPrice(5);
    Square::setSquareType("S");
    Square::setRentHome(4);
    Square::setRentHotel(8);
}

LuxurySquare::LuxurySquare() {
    Square::setPrice(20);
    Square::setHomePrice(10);
    Square::setHotelPrice(10);
    Square::setSquareType("L");
    Square::setRentHome(7);
    Square::setRentHotel(14);
}


#endif
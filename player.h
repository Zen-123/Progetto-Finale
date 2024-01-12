#ifndef PLAYER_H
#define PLAYER_H

#include "player.hpp"


class Player{
private:
    int budget = 100;
    std::string playerChar;
    Position pos;
    bool bankrupt = false;
    std::vector<Position> purchasedSquare;
public:

    Player(){
        setPosition(1,1, "P");
    }

    Player(std::string playerChar): playerChar{playerChar}{
        setPosition(1,1, "P");
    }

    int throwDice(){
        int first = std::rand()%6+1;
        int second = std::rand()%6+1;
        return (first + second);
    }

    void increaseBudget(){
        this->budget = this->budget + 20;
    }

    void increaseBudgetRent(int price){
        this->budget = this->budget + price;
    }
    void decrescenteBudgetRent(int price){
        this->budget = this->budget - price;
    }

    int getBudget(){
        return this->budget;
    }

    std::string getChar(){
        return this->playerChar;
    }

    void setPosition(int i, int j, std::string charSquare){
        if(i>0 && i<9 && j>0 && j<9 ){
            this->pos.i = i;
            this->pos.j = j;
            this->pos.charSqare = charSquare;
        }else{
            this->pos.i = 1;
            this->pos.j = 1;
            this->pos.charSqare = "P";
        }
        
    }

    void setBankrupt(){
        this->bankrupt = true;
    }

    int getPositionI(){
        return this->pos.getPosI();
    }

    int getPositionJ(){
        return this->pos.getPosJ();
    }

    std::string getPositionChar(){
        return this->pos.getCharSquare();
    }

    Position getPosition(){
        return this->pos;
    }

    bool checkIfBankrupt(){
        if(this->budget <= 0){
            this->setBankrupt();
            return true;
        }
        return false;
    }

    void removePlayerCharIfBankrupt(std::string board[9][9], EconomicSquare& E, StandardSquare& S, LuxurySquare& L) {
        int i,j;
        for(auto it = this->purchasedSquare.begin(); it != this->purchasedSquare.end(); it++){

            i = it->getPosI();
            j = it->getPosJ();

            if(board[i][j].find('*') != board[i][j].npos){
                board[i][j].erase(board[i][j].find('*'), (board[i][j].find('*'))+1);
             
            }

             if(board[i][j].find('^') != board[i][j].npos){
                board[i][j].erase(board[i][j].find('^'), (board[i][j].find('^'))+1);
                
            }
            
            if(board[i][j] == "E")
                E.removePlayerPosition(i, j);
            if(board[i][j] == "S")
                S.removePlayerPosition(i, j);
            if(board[i][j] == "L")
                L.removePlayerPosition(i, j);
        }
        
    }


    void checkPurchaseSquare(std::string board[9][9], EconomicSquare& E,StandardSquare& S, LuxurySquare& L ){

        int i = this->getPositionI();
        int j = this->getPositionJ();
        bool tmp  = false;

        if(board[i][j].substr(0,1) == "E" &&  (E.getPlayer(i,j) == " " )){  //controlla se la casella è gia posseduta da qualche altro giocatore
            if(this->budget >= E.getPrice()){
                E.setPlayer(this->playerChar, i, j);
                this->budget -= E.getPrice();
                this->setPosition(i, j, "E");
                tmp = true;
            }
         
        }else if(board[i][j].substr(0,1) == "S"  &&  (S.getPlayer(i,j) == " " )){
            if(this->budget >= S.getPrice()){
                S.setPlayer(this->playerChar, i, j);
                this->budget -= S.getPrice();
                this->setPosition(i, j, "S");
                tmp = true;
            }
                
        }else if(board[i][j].substr(0,1) == "L"  &&  (L.getPlayer(i,j) == " " )){
            if(this->budget >= L.getPrice()){
                L.setPlayer(this->playerChar, i, j);
                this->budget -= L.getPrice();
                this->setPosition(i, j, "L");
                tmp = true;
            }
        }

        if(tmp){
            std::cout<<"Il giocatore " +  this->playerChar + " ha comprato un terreno! \n";
            this->purchasedSquare.push_back(this->pos);
        }else{

            if(E.getPlayer(i,j) != " " || S.getPlayer(i,j) != " " || L.getPlayer(i,j) != " ")
                std::cout<<"Il terreno è già stato acquistato da un altro giocatore! \n";
            else    
                std::cout<<"Il giocatore " +  this->playerChar + " non ha budget a sufficienza per acquistare il terreno! \n";

        }

        
        
    }

    void checkPurchaseHouse( std::string board[9][9], EconomicSquare& E,StandardSquare& S, LuxurySquare& L){

        int i = this->getPositionI();
        int j = this->getPositionJ();
        bool tmp = false;

        if(std::find(this->purchasedSquare.begin(), this->purchasedSquare.end(), this->pos) != this->purchasedSquare.end()){

            if(board[i][j].substr(0,1) == "E" ){
                if(this->budget >= E.getHomePrice()){
                    E.setPlayer(this->playerChar, i, j);
                    this->budget -= E.getHomePrice();
                    board[i][j] += E.getCharHome();
                    this->setPosition(i, j, "E");
                    tmp = true;
                }
      
            }else if(board[i][j].substr(0,1) == "S" ){
                 if(this->budget >= S.getHomePrice()){
                    S.setPlayer(this->playerChar, i, j);
                    this->budget -= S.getHomePrice();
                    board[i][j] += S.getCharHome();
                    this->setPosition(i, j, "S");
                    tmp = true;
                 }
            }else if(board[i][j].substr(0,1) == "L"){
                 if(this->budget >= E.getHomePrice()){
                    L.setPlayer(this->playerChar, i, j);
                    this->budget -= L.getHomePrice();
                    board[i][j] += L.getCharHome();
                    this->setPosition(i, j, "L");
                    tmp = true;
                 }

            }

            if(tmp){
                std::cout<<"Il giocatore " +  this->playerChar + " ha comprato una casa! \n";
                this->purchasedSquare.push_back(this->pos);
            }else
                std::cout<<"Il giocatore " +  this->playerChar + " non ha budget sufficiente per acquistare una casa! \n";
        }else{
            this->checkPurchaseSquare(board, E, S, L);
        }




      
    }

    void checkPurchaseHotel( std::string board[9][9], EconomicSquare& E,StandardSquare& S, LuxurySquare& L){

        int i = this->getPositionI();
        int j = this->getPositionJ();
        bool tmp  = false;
        if(std::find(this->purchasedSquare.begin(), this->purchasedSquare.end(), this->pos) != this->purchasedSquare.end()){
            if(board[i][j].substr(0,1) == "E"){
                if(this->budget >= E.getHotelPrice()){
                    E.setPlayer(this->playerChar, i, j);
                    this->budget -= E.getHotelPrice();
                    this->setPosition(i, j, "E");
                    tmp = true;
                }
                    
            }else if(board[i][j].substr(0,1) == "S"){
                if(this->budget >= S.getHotelPrice()){
                    S.setPlayer(this->playerChar, i, j);
                    this->budget -= S.getHotelPrice();
                    this->setPosition(i, j, "E");
                    tmp =  true;
                }
             
            }else if(board[i][j].substr(0,1) == "L"){
                if(this->budget >= L.getHotelPrice()){
                    L.setPlayer(this->playerChar, i, j);
                    this->budget -= L.getHotelPrice();
                    this->setPosition(i, j, "E");
                    tmp =  true;
                }
            }

            if(tmp){
                std::cout<<"\nIl giocatore " + this->playerChar + " ha acquistato un albergo \n";
                this->purchasedSquare.push_back(this->pos);
                if(board[i][j].find(E.getCharHome()) != board[i][j].npos){
                    board[i][j].erase(board[i][j].find(E.getCharHome()), this->playerChar.length());
                    board[i][j] += E.getCharHotel();
                }
            }else{
                std::cout<<"Il giocatore " +  this->playerChar + " non ha budget sufficiente per acquistare un albergo! \n";
                
            }


        }else{
            this->checkPurchaseSquare(board, E, S, L);
        }
    }

    void printStatus(){
        std::cout<<"Giocatore "<<this->playerChar<<"\n";
        std::cout<<"Budget attuale: "<<this->budget<<"\n";
        std::cout<<"Caselle acquistate: \n";
        for(auto it = this->purchasedSquare.begin(); it != this->purchasedSquare.end(); it++)
            std::cout<<it->charSqare<< ":  "<<it->i<<" - "<<it->j<<"\n";

        std::cout<<"\n\n----------------------\n\n";
    
    }

    std::vector<Position> getProperty(){
        return this->purchasedSquare;
    }

    ~Player() {}
};


class ComputerPlayer : public Player{
public:

    ComputerPlayer(std::string p):Player(p){}

    bool randomChoice(){
        
        //se esce 1 si considera la scelta positiva mentre per tutti gli altri valori la scelta è negativa
        int choice = std::rand() % 4 + 1;

        if(choice == 1 )
            return true;
        else
            return false;
    }

    ~ComputerPlayer() {}

};

// bool cmpPosition(const Position& a, const Position& b){  //funzione che compara i valori interi tra due pair per ordinamento da maggiore a minore
//     return a == b;
// }



#endif

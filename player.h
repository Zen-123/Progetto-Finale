#ifndef PLAYER_H
#define PLAYER_H

struct Position{
    int i;
    int j;

    int getPosI(){
        return this->i;
    }

    int getPosJ(){
        return this->j;
    }
};

class Player{
private:
    int budget = 100;
    std::string p;
    Position pos;
public:

    Player(){
        setPosition(1,1);
    }

    Player(std::string p): p{p}{
        setPosition(1,1);
    }

    int throwDice(){
        int first = std::rand()%6+1;
        int second = std::rand()%6+1;
        return (first + second);
    }

    std::string getChar(){
        return this->p;
    }

    void setPosition(int i, int j){
        if(i>0 && j>0 ){
            this->pos.i = i;
            this->pos.j = j;
        }else{
            this->pos.i = 1;
            this->pos.j = 1;
        }
        
    }

    int getPositionI(){
        return this->pos.getPosI();
    }

    int getPositionJ(){
        return this->pos.getPosJ();
    }

    void checkPurchase(std::string square, EconomicSquare& E,StandardSquare& S, LuxurySquare& L ){

        bool tmp = false;
        if(square.substr(0,1) == "E"){
            
            if(this->budget >= E.getPrice()){
                E.setPlayer(this->p);
                this->budget -= E.getPrice();
                tmp = true;
            }else
                tmp = false;
        }else if(square.substr(0,1) == "S"){
            if(this->budget >= S.getPrice()){
                S.setPlayer(this->p);
                this->budget -= S.getPrice();
                tmp = true;
            }else   
                tmp = false;
            
        }else if(square.substr(0,1) == "L"){
            if(this->budget >= L.getPrice()){
                L.setPlayer(this->p);
                this->budget -= L.getPrice();
                tmp = true;
            }else
                tmp = false;
        }

        if(tmp)
            std::cout<<"Budget attuale: "<<this->budget<<"\n";
        else
            std::cout<<"Budget non sufficiente!!  \n";
    }

    ~Player() {}
};


class ComputerPlayer : public Player{
public:

    ComputerPlayer(std::string p):Player(p){}

    bool randomChoice(){
        
        srand(time(NULL));
        //se esce 1 si considera la scelta positiva mentre per tutti gli altri valori la scelta è negativa
        int choice = std::rand() % 4 + 1;

        if(choice == 1 )
            return true;
        else
            return false;
    }

    ~ComputerPlayer() {}

};




#endif

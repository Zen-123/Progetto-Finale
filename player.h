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
    char P = '1';
    Position pos;
public:

    Player() {
        setPosition(1,1);
    }

    int throwDice(){

        srand(time(NULL));
        int first = std::rand()%6+1;
        int second = std::rand()%6+1;


        return (first + second);

    }

    char getChar(){
        return this->P;
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


    ~Player() {}
};


    class HumanPlayer : public Player{

    public:

    HumanPlayer(){}

    ~HumanPlayer() {}
};

class ComputerPlayer : public Player{

public:

    ComputerPlayer(){}

    ~ComputerPlayer() {}

};
    void startGameHuman(){
        HumanPlayer P1;
        ComputerPlayer P2;
        ComputerPlayer P3;
        ComputerPlayer P4;
    
     }

     void startGameComputer(){
         ComputerPlayer P1;
         ComputerPlayer P2;
         ComputerPlayer P3;
         ComputerPlayer P4;
    

#endif

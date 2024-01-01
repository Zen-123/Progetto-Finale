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

const int ROW = 9;
const int COL = 9;

static int EconomicSquareNumber = 8;
static int StandardSquareNumber = 10;
static int LuxurySquareNumber = 6;


void func(){
    AngularSquare A;
    EconomicSquare E;
    StandardSquare S;
    LuxurySquare L;

    char board[ROW][COL];
    char initRows[] ={' ','A','B','C','D','E','F','G','H'};
    char initCols[] ={' ','1','2','3','4','5','6','7','8'};

    srand(time(NULL));
    for(int i = 0; i < ROW; i++){
        for(int j=0; j< COL; j++){

            /*
            Se esce 1 -- casella Standard
            Se esce 2 -- casella Economic
            Se esce 3 -- casella luxury
            */


            if(i>1 && i<ROW-1 && j>1 && j<COL-1){
                board[i][j] = ' ';
            }else if(i == 1 || i == ROW-1 && j != 0){
                int value = std::rand() % 3 +1;
            
                switch (value)
                {
                case(1):
                    if(StandardSquareNumber>0 ){
                        board[i][j] = S.ShowSquare();
                        StandardSquareNumber--;
                        break;

                    }
        
                case(2):
                    if(EconomicSquareNumber>0   ){
                        board[i][j] = E.ShowSquare();
                        EconomicSquareNumber--;
                        break;

                    }
                case(3):
                    if(LuxurySquareNumber>0){
                        board[i][j] = L.ShowSquare();
                        LuxurySquareNumber--;
                        break;
                    }
                    break;   
                default:
                    board[i][j] = A.ShowSquare();
                    break;
                }
            }
     

    

            board[0][j] = initCols[j];


        }
                 
            board[1][1] = A.ShowSquare();
            board[1][COL-1] = A.ShowSquare();
            board[ROW-1][1] = A.ShowSquare();
            board[ROW-1][COL-1] = A.ShowSquare();
        board[i][0] = initRows[i];

    }

    for(int i=0; i<ROW; i++){
        for(int j=0; j<COL; j++){
            if(i<2 && j<COL || i == ROW-1 && j<COL || j<2 && i<ROW-1 || j == COL-1 && i<ROW-1)
                std::cout<<"| "<<board[i][j]<<" |"<<"\t";
            else
                std::cout<<board[i][j]<<"\t";


        }
        std::cout<<"\n";
    }

}




#endif
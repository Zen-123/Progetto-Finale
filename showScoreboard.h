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

    
   /*
        Se esce 1 -- casella Luxury
        Se esce 2 -- casella Economic
        Se esce 3 -- casella Standard
    */
    //Riempimento prima riga
    for(int j =2; j<COL-1; j++){
        int value = std::rand() % 3 +1;
        if((value == 1 || StandardSquareNumber<0 || EconomicSquareNumber<0 )&& LuxurySquareNumber>0)
        {
            board[1][j] = L.ShowSquare();
            LuxurySquareNumber--;
        }
        else if((value == 2 || StandardSquareNumber<0 || LuxurySquareNumber<0 ) &&  EconomicSquareNumber >0)
        {
            board[1][j] = E.ShowSquare();
            EconomicSquareNumber--;
        }
        else if ((value == 3 || LuxurySquareNumber<0 || EconomicSquareNumber<0) && StandardSquareNumber>0){
            board[1][j] = S.ShowSquare();
            StandardSquareNumber--;
        }

    }

    //Riempimento ultima riga

    for(int j =2; j<COL-1; j++){
        
        int value = std::rand() % 3 +1;
        if((value == 1 || StandardSquareNumber<0 || LuxurySquareNumber<0 )&& EconomicSquareNumber>0)
        {
            board[ROW-1][j] = E.ShowSquare();
            EconomicSquareNumber--;
        }
        else if((value == 2 || EconomicSquareNumber<0 || LuxurySquareNumber<0 ) && StandardSquareNumber>0)
        {
            board[ROW-1][j] = S.ShowSquare();
            StandardSquareNumber--;
        }
        else if ((value == 3 || StandardSquareNumber<0 || EconomicSquareNumber<0) && LuxurySquareNumber>0){
            board[ROW-1][j] = L.ShowSquare();
            LuxurySquareNumber--;
        }

    }

    //riempimento prima colonna
     for(int i = 2; i<ROW-1; i++){

        int value = std::rand() % 3 +1;
        if((value == 1 || StandardSquareNumber<0 || LuxurySquareNumber<0 )&& EconomicSquareNumber>0)
        {
            board[i][1] = E.ShowSquare();
            EconomicSquareNumber--;
        }
        else if((value == 2 || EconomicSquareNumber<0 || LuxurySquareNumber<0 ) && StandardSquareNumber>0)
        {
            board[i][1] = S.ShowSquare();
            StandardSquareNumber--;
        }
        else if ((value == 3 || StandardSquareNumber<0 || EconomicSquareNumber<0) && LuxurySquareNumber>0){
            board[i][1] = L.ShowSquare();
            LuxurySquareNumber--;
        }else if(LuxurySquareNumber == 0){
            if(EconomicSquareNumber == 0){
                if(StandardSquareNumber>0){
                    board[i][1] = S.ShowSquare();
                    StandardSquareNumber--;
                }
                
            }else if(StandardSquareNumber == 0){
                if(EconomicSquareNumber>0){
                    board[i][1] = E.ShowSquare();
                    EconomicSquareNumber--;
                }
                
            }else if(StandardSquareNumber > 0 && EconomicSquareNumber>0){
                value = std::rand() % 2 +1;
                if(value == 1){
                    board[i][1] = S.ShowSquare();
                    StandardSquareNumber--;
                }else{

                    board[i][1] = E.ShowSquare();
                    EconomicSquareNumber--;
                }    

            }
        }else if(EconomicSquareNumber == 0){
            if(LuxurySquareNumber == 0){
                if(StandardSquareNumber > 0){
                    board[i][1] = S.ShowSquare();
                    StandardSquareNumber--;
                }
            }else if(StandardSquareNumber == 0){
                if(LuxurySquareNumber>0){
                    board[i][1] = L.ShowSquare();
                    LuxurySquareNumber--;
                }
            }else if(LuxurySquareNumber > 0 && StandardSquareNumber > 0){
                value = std::rand() % 2 +1;
                if(value == 1){
                    board[i][1] = S.ShowSquare();
                    StandardSquareNumber--;
                }else{
                     board[i][1] = L.ShowSquare();
                    LuxurySquareNumber--;
                }
            }   
        }else if(StandardSquareNumber == 0){
            if(EconomicSquareNumber == 0){
                 if(LuxurySquareNumber>0){
                    board[i][1] = L.ShowSquare();
                    LuxurySquareNumber--;
                }
            }else if(LuxurySquareNumber == 0){
                if(EconomicSquareNumber > 0){
                    board[i][1] = E.ShowSquare();
                    EconomicSquareNumber--;
                }
            }else if(LuxurySquareNumber > 0 && EconomicSquareNumber>0){
                value = std::rand() % 2 +1;
                if(value == 1){
                    board[i][1] = L.ShowSquare();
                    LuxurySquareNumber--;
                }else{
                    board[i][1] = E.ShowSquare();
                    EconomicSquareNumber--;
                }
            }
        }

    }

    //RISOLUZIONE RIGA 168
    /*
        }*/
//Riempimento ultima colonna
    for(int i = 2; i<ROW-1; i++){

        int value = std::rand() % 3 +1;
        if((value == 1 || StandardSquareNumber<0 || LuxurySquareNumber<0 )&& EconomicSquareNumber>0)
        {
            board[i][COL-1] = E.ShowSquare();
            EconomicSquareNumber--;
        }
        else if((value == 2 || EconomicSquareNumber<0 || LuxurySquareNumber<0 ) && StandardSquareNumber>0)
        {
            board[i][COL-1] = S.ShowSquare();
            StandardSquareNumber--;
        }
        else if ((value == 3 || StandardSquareNumber<0 || EconomicSquareNumber<0) && LuxurySquareNumber>0){
            board[i][COL-1] = L.ShowSquare();
            LuxurySquareNumber--;
        }else if(LuxurySquareNumber == 0){
            if(EconomicSquareNumber == 0){
                if(StandardSquareNumber>0){
                    board[i][COL-1] = S.ShowSquare();
                    StandardSquareNumber--;
                }
                
            }else if(StandardSquareNumber == 0){
                if(EconomicSquareNumber>0){
                    board[i][COL-1] = E.ShowSquare();
                    EconomicSquareNumber--;
                }
                
            }else if(StandardSquareNumber > 0 && EconomicSquareNumber>0){
                value = std::rand() % 2 +1;
                if(value == 1){
                    board[i][COL-1] = S.ShowSquare();
                    StandardSquareNumber--;
                }else{

                    board[i][COL-1] = E.ShowSquare();
                    EconomicSquareNumber--;
                }    

            }
        }else if(EconomicSquareNumber == 0){
            if(LuxurySquareNumber == 0){
                if(StandardSquareNumber > 0){
                    board[i][COL-1] = S.ShowSquare();
                    StandardSquareNumber--;
                }
            }else if(StandardSquareNumber == 0){
                if(LuxurySquareNumber>0){
                    board[i][COL-1] = L.ShowSquare();
                    LuxurySquareNumber--;
                }
            }else if(LuxurySquareNumber > 0 && StandardSquareNumber > 0){
                value = std::rand() % 2 +1;
                if(value == 1){
                    board[i][COL-1] = S.ShowSquare();
                    StandardSquareNumber--;
                }else{
                     board[i][COL-1] = L.ShowSquare();
                    LuxurySquareNumber--;
                }
            }   
        }else if(StandardSquareNumber == 0){
            if(EconomicSquareNumber == 0){
                 if(LuxurySquareNumber>0){
                    board[i][COL-1] = L.ShowSquare();
                    LuxurySquareNumber--;
                }
            }else if(LuxurySquareNumber == 0){
                if(EconomicSquareNumber > 0){
                    board[i][COL-1] = E.ShowSquare();
                    EconomicSquareNumber--;
                }
            }else if(LuxurySquareNumber > 0 && EconomicSquareNumber>0){
                value = std::rand() % 2 +1;
                if(value == 1){
                    board[i][COL-1] = L.ShowSquare();
                    LuxurySquareNumber--;
                }else{
                    board[i][COL-1] = E.ShowSquare();
                    EconomicSquareNumber--;
                }
            }
        }

    }
     

    std::cout<<"\nStandard"<<StandardSquareNumber;
    std::cout<<"\nEcon"<<EconomicSquareNumber;
    std::cout<<"\nLux"<<LuxurySquareNumber<<"\n";



  



    board[1][1] = A.ShowSquare();
    board[1][COL-1] = A.ShowSquare();
    board[ROW-1][1] = A.ShowSquare();
    board[ROW-1][COL-1] = A.ShowSquare();

/*
    do{

        int j =1;
            if(i>1 && i<ROW-1 ){
                board[i][j] = ' ';
            }else if(i == 1 || i == ROW-1){
                while(j < ROW-1){
                    int value = std::rand() % 3 +1;

                    switch (value)
                    {
                    case(1):
                        if(StandardSquareNumber>0 ){
                            board[i][j] = S.ShowSquare();
                            StandardSquareNumber--;
                            j++;
                            break;

                        }

            
                    case(2):
                        if(EconomicSquareNumber>0   ){
                            board[i][j] = E.ShowSquare();
                            EconomicSquareNumber--;
                            j++;
                            break;

                        }
                    case(3):
                        if(LuxurySquareNumber>0){
                            board[i][j] = L.ShowSquare();
                            LuxurySquareNumber--;
                            j++;
                            break; 

                        }
                    default:
                        board[i][j] = A.ShowSquare();
                        break;
                    }


                }
            }
            i++;
    }while(EconomicSquareNumber>0 && StandardSquareNumber>0 && LuxurySquareNumber>0);
    
    */
    // for(int i = 0; i < ROW; i++){
    //     for(int j=0; j< COL; j++){

    //      



    

    //         board[0][j] = initCols[j];


    //     }
                 
        //    
        // board[i][0] = initRows[i];

   // }


    for(int j = 1; j<COL; j++)
        board[0][j] = initCols[j];

    for(int i = 1; i<COL; i++)
        board[i][0] = initRows[i];

    for(int i =2; i<ROW-1; i++){
        for(int j =2; j<COL-1; j++){
            board[i][j] = ' ';
        }
    }

    for(int i=0; i<ROW; i++){
        for(int j=0; j<COL; j++){
            if(i==1 && j>0 || i == ROW-1 && j>0 || j==1  && i>0 || j == COL-1 && i>1)
                std::cout<<"| "<<board[i][j]<<" |"<<"\t";
            else
                std::cout<<"  "<<board[i][j]<<"  "<<"\t";


        }
        std::cout<<"\n";
    }

}




#endif
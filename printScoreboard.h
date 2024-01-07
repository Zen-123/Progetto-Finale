#ifndef PRINTSCOREBOARD_H
#define PRINTSCOREBOARD_H

const int ROW = 9;
const int COL = 9;

static int EconomicSquareNumber = 8;
static int StandardSquareNumber = 10;
static int LuxurySquareNumber = 6;

    
static AngularSquare A;
static EconomicSquare E;
static StandardSquare S;
static LuxurySquare L;

void firstRow(std::string board[ROW][COL]);
void lastRow(std::string board[ROW][COL]);
void firstCol(std::string board[ROW][COL]);
void lastCol(std::string board[ROW][COL]);

void printScoreboard(std::string board[ROW][COL]);

void fillAllSquaresColumn(std::string board[ROW][COL], int index, int position );
void fillAllSquaresRows(std::string board[ROW][COL], int index, int position );



void func(Player& p){


    std::string board[ROW][COL];
    char initRows[] ={' ','A','B','C','D','E','F','G','H'};
    char initCols[] ={' ','1','2','3','4','5','6','7','8'};

    srand(time(NULL));
    board[1][1] = "P";
    board[1][COL-1] = A.ShowSquare();
    board[ROW-1][1] = A.ShowSquare();
    board[ROW-1][COL-1] = A.ShowSquare();

    //RIEMPIMENTO CASELLE

    firstRow(board);
    lastRow(board);
    firstCol(board);
    lastCol(board);




    for(int j = 1; j<COL; j++)
        board[0][j] = initCols[j];

    for(int i = 1; i<COL; i++)
        board[i][0] = initCols[i];

    for(int i =2; i<ROW-1; i++){
        for(int j =2; j<COL-1; j++){
            board[i][j] = ' ';
        }
    }
    
    printScoreboard(board);

    std::cout<<"\n\n-------------------------\n\n";
    int move;

    //TEST SPOSTAMENTO GIOCATORE CON SUCCESSIVA VISUALIZZAZIONE

    int diffCol, diffRow;
    int n, i, j;       



    while(n != 1){
        move = p.throwDice();
        std::cout<<"Dado: "<<move<<"\n\n";
        //OK!
        if(p.getPositionI() == 1  ){
            j = p.getPositionJ();
            if((j+move+1) > COL-1 ){
                diffCol = (COL-1) - (j);
                int tmp = (COL-2)  + diffCol;
                j = move - tmp;
                if(j>0){
                    board[ROW-1][(COL-1)-j] += "1";
                    p.setPosition(ROW-1, (COL-1)-j);
                }else{
                    i =1+ (move - diffCol);
                    board[i][COL-1] += "1";
                    p.setPosition(i, COL-1);
                }
            }else{
                p.setPosition(1, j+move);
                board[1][j+move] += "1";
            }
            //OK!
        }else if(p.getPositionJ() == COL-1 ){
            i = p.getPositionI();
            if((i+move) > ROW-1){
                diffRow = move - ((COL-1) - i);
                 diffCol = (ROW-1) - diffRow;
                if(diffCol > 0){
                    board[ROW-1][diffCol] += "1";
                    p.setPosition(ROW-1, diffCol);
                }else{
                    diffRow = move - (ROW-1) - (COL-1-i-1);
                    i = (COL-1) - diffRow;
                    board[i][1] += "1";
                    p.setPosition(i, 1);
                }
                
              
            }else{
                board[i+move][COL-1] += "1";
                p.setPosition(i+move, COL-1);

            }
            
        }else if(p.getPositionI() == ROW-1){
            j = p.getPositionJ();
            if((j-move) < 1){
                diffCol =move - (j-1);
                i = (ROW-1) - diffCol;
                if(i > 0){
                    board[i][1] += "1";
                    p.setPosition(i,1);
                }else{
                    int tmp = (j-1) + (ROW-2);
                    j = move-tmp;
                    board[1][1+j] += "1";
                    p.setPosition(1, j+1);
                }
            }else{
                board[ROW-1][j-move] += "1";
                p.setPosition(ROW-1, j-move);

            }    
                
        }else if(p.getPositionJ() == 1){
            i = p.getPositionI();
            if((i-move) < 1){
                diffRow = i-2;
                int tmp = diffRow + (COL-1);
                j = diffRow+1;
                if(j > 0){
                    board[1][j] += "1";
                    p.setPosition(1, j);
                }else{
                    diffRow = move - (ROW-1) - (i-2);
                    i = diffRow+1;
                    board[i][COL-1] += "1";
                    p.setPosition(i, COL-1);
                }
            }else{
                board[i-move][1] += "1";
                p.setPosition(i-move, 1);

            }
        }
        
        printScoreboard(board);

        std::cout<<"\nContinuare?  ";
        std::cin>>n;

    
    }

   
    
    std::cout<<"\nStandard: "<<StandardSquareNumber<<"\nEconomy: "<<EconomicSquareNumber<<"\nLuxury:"<<LuxurySquareNumber<<"\n\n";

   


}

/*
        Se esce 1 -- casella Luxury
        Se esce 2 -- casella Economic
        Se esce 3 -- casella Standard
*/

void firstRow(std::string board[ROW][COL]){
    srand(time(NULL));
    for(int j =2; j<COL-1; j++){
        int value = std::rand() % 3 + 1;
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
        }else{
            int rowPosition = 1;
            fillAllSquaresRows(board, j, rowPosition);
        }

    }
}

void lastRow(std::string board[ROW][COL]){
    srand(time(NULL));
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
        }else{
            int rowPosition = ROW-1;
            fillAllSquaresRows(board, j, rowPosition);
        }

    }
}

void firstCol(std::string board[ROW][COL]){
    srand(time(NULL));
    for(int i = 2; i<ROW-1; i++){
        int value = std::rand() % 3 +1;
        if((value == 1 || StandardSquareNumber<1 || LuxurySquareNumber<1 )&& EconomicSquareNumber>0)
        {
            board[i][1] = E.ShowSquare();
            EconomicSquareNumber--;
        }
        else if((value == 2 || EconomicSquareNumber<1 || LuxurySquareNumber<1 ) && StandardSquareNumber>0)
        {
            board[i][1] = S.ShowSquare();
            StandardSquareNumber--;
        }
        else if ((value == 3 || StandardSquareNumber<1 || EconomicSquareNumber<1) && LuxurySquareNumber>0){
            board[i][1] = L.ShowSquare();
            LuxurySquareNumber--;
        }else{
            int columnPosition = 1;
            fillAllSquaresColumn(board, i, columnPosition);
        }
    }

}

void lastCol(std::string board[ROW][COL]){
    srand(time(NULL));

    for(int i = 2; i<ROW-1; i++){

        int value = std::rand() % 3 + 1;
        if((value == 1 || StandardSquareNumber<1|| LuxurySquareNumber<1 )&& EconomicSquareNumber>0)
        {
            board[i][COL-1] = E.ShowSquare();
            EconomicSquareNumber--;
        }
        else if((value == 2 || EconomicSquareNumber<1 || LuxurySquareNumber<1 ) && StandardSquareNumber>0)
        {
            board[i][COL-1] = S.ShowSquare();
            StandardSquareNumber--;
        }
        else if ((value == 3 || StandardSquareNumber<1 || EconomicSquareNumber<1) && LuxurySquareNumber>0){
            board[i][COL-1] = L.ShowSquare();
            LuxurySquareNumber--;
        }else{
            int columnPosition = COL-1;
            fillAllSquaresColumn(board, i, columnPosition);
        }
    
    }
}

void printScoreboard(std::string board[ROW][COL]){
 
    for(int i=0; i<ROW; i++){
        for(int j=0; j<COL; j++){
            if(i==1 && j>0 || i == ROW-1 && j>0 || j==1  && i>0 || j == COL-1 && i>1)
                std::cout<<"| "<<std::setw(2) <<board[i][j]<<" |"<<"\t";
            else
                std::cout<<"  "<<board[i][j]<<"  "<<"\t";


        }
        std::cout<<"\n";
    }
}

void fillAllSquaresColumn(std::string board[ROW][COL], int i, int columnPosition){
    int value;
    if(LuxurySquareNumber == 0){
            if(EconomicSquareNumber == 0){
                if(StandardSquareNumber>0){
                    board[i][columnPosition] = S.ShowSquare();
                    StandardSquareNumber--;
                }
                
            }else if(StandardSquareNumber == 0){
                if(EconomicSquareNumber>0){
                    board[i][columnPosition] = E.ShowSquare();
                    EconomicSquareNumber--;
                }
                
            }else if(StandardSquareNumber > 0 && EconomicSquareNumber>0){
                value = std::rand() % 2 +1;
                if(value == 1){
                    board[i][columnPosition] = S.ShowSquare();
                    StandardSquareNumber--;
                }else {

                    board[i][columnPosition] = E.ShowSquare();
                    EconomicSquareNumber--;
                }    

            }
        }else if(EconomicSquareNumber == 0){
            if(LuxurySquareNumber == 0){
                if(StandardSquareNumber > 0){
                    board[i][columnPosition] = S.ShowSquare();
                    StandardSquareNumber--;
                }
            }else if(StandardSquareNumber == 0){
                if(LuxurySquareNumber>0){
                    board[i][columnPosition] = L.ShowSquare();
                    LuxurySquareNumber--;
                }
            }else if(LuxurySquareNumber > 0 && StandardSquareNumber > 0){
                value = std::rand() % 2 +1;
                if(value == 1){
                    board[i][1] = S.ShowSquare();
                    StandardSquareNumber--;
                }else{
                     board[i][columnPosition] = L.ShowSquare();
                    LuxurySquareNumber--;
                }
            }   
        }else if(StandardSquareNumber == 0){
            if(EconomicSquareNumber == 0){
                 if(LuxurySquareNumber>0){
                    board[i][columnPosition] = L.ShowSquare();
                    LuxurySquareNumber--;
                }
            }else if(LuxurySquareNumber == 0){
                if(EconomicSquareNumber > 0){
                    board[i][columnPosition] = E.ShowSquare();
                    EconomicSquareNumber--;
                }
            }else if(LuxurySquareNumber > 0 && EconomicSquareNumber>0){
                value = std::rand() % 2 +1;
                if(value == 1){
                    board[i][columnPosition] = L.ShowSquare();
                    LuxurySquareNumber--;
                }else{
                    board[i][columnPosition] = E.ShowSquare();
                    EconomicSquareNumber--;
                }
            }
        }
}

void fillAllSquaresRows(std::string board[ROW][COL], int j, int position ){
   int value;
    if(LuxurySquareNumber == 0){
            if(EconomicSquareNumber == 0){
                if(StandardSquareNumber>0){
                    board[position][j] = S.ShowSquare();
                    StandardSquareNumber--;
                }
                
            }else if(StandardSquareNumber == 0){
                if(EconomicSquareNumber>0){
                    board[position][j] = E.ShowSquare();
                    EconomicSquareNumber--;
                }
                
            }else if(StandardSquareNumber > 0 && EconomicSquareNumber>0){
                value = std::rand() % 2 +1;
                if(value == 1){
                    board[position][j] = S.ShowSquare();
                    StandardSquareNumber--;
                }else {

                    board[position][j] = E.ShowSquare();
                    EconomicSquareNumber--;
                }    

            }
        }else if(EconomicSquareNumber == 0){
            if(LuxurySquareNumber == 0){
                if(StandardSquareNumber > 0){
                    board[position][j] = S.ShowSquare();
                    StandardSquareNumber--;
                }
            }else if(StandardSquareNumber == 0){
                if(LuxurySquareNumber>0){
                     board[position][j] = L.ShowSquare();
                    LuxurySquareNumber--;
                }
            }else if(LuxurySquareNumber > 0 && StandardSquareNumber > 0){
                value = std::rand() % 2 +1;
                if(value == 1){
                    board[position][j] = S.ShowSquare();
                    StandardSquareNumber--;
                }else{
                     board[position][j] = L.ShowSquare();
                    LuxurySquareNumber--;
                }
            }   
        }else if(StandardSquareNumber == 0){
            if(EconomicSquareNumber == 0){
                 if(LuxurySquareNumber>0){
                    board[position][j] = L.ShowSquare();
                    LuxurySquareNumber--;
                }
            }else if(LuxurySquareNumber == 0){
                if(EconomicSquareNumber > 0){
                     board[position][j] = E.ShowSquare();
                    EconomicSquareNumber--;
                }
            }else if(LuxurySquareNumber > 0 && EconomicSquareNumber>0){
                value = std::rand() % 2 +1;
                if(value == 1){
                    board[position][j]= L.ShowSquare();
                    LuxurySquareNumber--;
                }else{
                     board[position][j] = E.ShowSquare();
                    EconomicSquareNumber--;
                }
            }
        }  
}




#endif
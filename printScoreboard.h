#ifndef PRINTSCOREBOARD_H
#define PRINTSCOREBOARD_H

const int ROW = 9;
const int COL = 9;
const int TURN = 4;
const int MAX_TURN = 5;


static int EconomicSquareNumber = 8;
static int StandardSquareNumber = 10;
static int LuxurySquareNumber = 6;

    
static AngularSquare A;
static EconomicSquare E;
static StandardSquare S;
static LuxurySquare L;

static ComputerPlayer P1("1");
static ComputerPlayer P2("2");
static ComputerPlayer P3("3");
static ComputerPlayer P4("4");


void firstRow(std::string board[ROW][COL]);
void lastRow(std::string board[ROW][COL]);
void firstCol(std::string board[ROW][COL]);
void lastCol(std::string board[ROW][COL]);

void printScoreboard(std::string board[ROW][COL]);

void fillAllSquaresColumn(std::string board[ROW][COL], int index, int position );
void fillAllSquaresRows(std::string board[ROW][COL], int index, int position );

void setTurn(std::string order[4]);

void removePrevChar(std::string board[ROW][COL], ComputerPlayer& player);

bool cmp(std::pair<std::string, int>& a, std::pair<std::string, int>& b);

void checkDiceNumber(std::map<std::string, int>& mp);

void setPosition(ComputerPlayer& player, std::string board[ROW][COL]);

void func(){

    
    std::string board[ROW][COL];
    std::string order[TURN];
    
    setTurn(order);  //funzione per stabilire i turni

    std::cout<<"Ordine giocatori: \n";

    for(int i=0; i<TURN; i++){
        std::cout<<order[i]<<"  ";
    }
    std::cout<<"\n";



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
    //TEST SPOSTAMENTO GIOCATORE CON SUCCESSIVA VISUALIZZAZIONE

    //VARIABILI USATE PER TEST SPOSTAMENTO
    int move, n;
    int countTurn = 0;
    int countPlayerOrder = 0;
    Player p;

    int i,j;
    //GIRO GESTITO IN SENSO ORARIO PARTENDO DA POSIZIONE [1][1] = " P "
    while(n != 1){

        if(countTurn == 4)
            countTurn = 0;

        if(order[countTurn] == P1.getChar()){
            removePrevChar(board,P1);
            std::cout<<"Turno Giocatore " + P1.getChar()+ "\n";
            setPosition(P1, board);
            if(P1.randomChoice() == true){
                i = P1.getPositionI();
                j = P1.getPositionJ();

                if((board[i][j].substr(0, 1) == "E" || board[i][j].substr(0, 1) == "S" || board[i][j].substr(0, 1) == "L")){
                    if(E.getPlayer() == P1.getChar() || S.getPlayer() == P1.getChar() || L.getPlayer() == P1.getChar() ){
                        P1.checkPurchaseHouse(board,E,S,L);
                        std::cout<<"\n Il giocatore 1 ha comprato una casa! \n";
                    }else{
                        std::cout<<"\n Il giocatore 1 ha comprato un terreno! \n";
                        P1.checkPurchaseSquare(board[i][j],E,S,L);

                    }
                }
               
               
            }
            
        }else if(order[countTurn] == P2.getChar()){
            removePrevChar(board,P2);
            std::cout<<"Turno Giocatore " + P2.getChar()+ "\n";
            setPosition(P2, board);
            if(P2.randomChoice() == true){
                i = P2.getPositionI();
                j = P2.getPositionJ();
                 if((board[i][j].substr(0, 1) == "E" || board[i][j].substr(0, 1) == "S" || board[i][j].substr(0, 1) == "L")){
                    if(E.getPlayer() == P2.getChar() || S.getPlayer() == P2.getChar() || L.getPlayer() == P2.getChar() ){
                        P2.checkPurchaseHouse(board,E,S,L);
                        std::cout<<"\n Il giocatore 2 ha comprato una casa! \n";
                    }else{
                        std::cout<<"\n Il giocatore 2 ha comprato un terreno! \n";

                        P2.checkPurchaseSquare(board[i][j],E,S,L);
                    }
                }
            }
        }else if(order[countTurn] == P3.getChar()){
            removePrevChar(board,P3);
            std::cout<<"Turno Giocatore " + P3.getChar()+ "\n";
            setPosition(P3, board);
            if(P3.randomChoice() == true){
                i = P3.getPositionI();
                j = P3.getPositionJ();
                 if((board[i][j].substr(0, 1) == "E" || board[i][j].substr(0, 1) == "S" || board[i][j].substr(0, 1) == "L")){
                    if(E.getPlayer() == P3.getChar() || S.getPlayer() == P3.getChar() || L.getPlayer() == P3.getChar() ){
                        P3.checkPurchaseHouse(board,E,S,L);
                        std::cout<<"\n Il giocatore 3 ha comprato una casa! \n";
                    }else{
                        std::cout<<"\n Il giocatore 3 ha comprato un terreno! \n";

                        P3.checkPurchaseSquare(board[i][j],E,S,L);
                    }
                }
            }
        }else if(order[countTurn] == P4.getChar()){
            removePrevChar(board,P4);
            std::cout<<"Turno Giocatore " + P4.getChar()+ "\n";
            setPosition(P4, board);
            if(P4.randomChoice() == true){
                i = P4.getPositionI();
                j = P4.getPositionJ();
                if((board[i][j].substr(0, 1) == "E" || board[i][j].substr(0, 1) == "S" || board[i][j].substr(0, 1) == "L")){
                    if(E.getPlayer() == P4.getChar() || S.getPlayer() == P4.getChar() || L.getPlayer() == P4.getChar() ){
                        P4.checkPurchaseHouse(board,E,S,L);
                        std::cout<<"\n Il giocatore 4 ha comprato una casa! \n";
                    }else{
                        std::cout<<"\n Il giocatore 4 ha comprato un terreno! \n";

                        P3.checkPurchaseSquare(board[i][j],E,S,L);
                    }
            }
            }
        }else{
            std::cout<<"Altro\n";
        }
        
            
        printScoreboard(board);
        std::cout<<"\nContinuare?  ";
        std::cin>>n;
        countTurn++;
    
    }

}

/*
    Valori random associati alle varie caselle: 

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


void setPosition(ComputerPlayer& player, std::string board[ROW][COL]){
    int diffCol, diffRow, move, n, i ,j;
    move = player.throwDice(); 
    std::cout<<"Dado: "<<move<<"\n\n";
    if(player.getPositionI() == 1  ){  //GESTIONE SPOSTAMENTO PRIMA RIGA
        j = player.getPositionJ();
        if((j+move+1) > COL-1 ){
            diffCol = (COL-1) - (j);
            int tmp = (COL-2)  + diffCol;
            j = move - tmp;
            if(j>0){
                board[ROW-1][(COL-1)-j] += player.getChar();
                player.setPosition(ROW-1, (COL-1)-j);
            }else{
                i =1+ (move - diffCol);
                board[i][COL-1] += player.getChar();
                player.setPosition(i, COL-1);
            }
        }else{
            player.setPosition(1, j+move);
            board[1][j+move] += player.getChar();
        }
        
    }else if(player.getPositionJ() == COL-1 ){  //GESTIONE SPOSTAMENTO ULTIMA COLONNA
        i = player.getPositionI();
        if((i+move) > ROW-1){
            diffRow = move - ((COL-1) - i);
                diffCol = (ROW-1) - diffRow;
            if(diffCol > 0){
                board[ROW-1][diffCol] += player.getChar();
                player.setPosition(ROW-1, diffCol);
            }else{
                diffRow = move - (ROW-1) - (COL-1-i-1);
                i = (COL-1) - diffRow;
                board[i][1] += player.getChar();
                player.setPosition(i, 1);
            }
            
            
        }else{
            board[i+move][COL-1] += player.getChar();
            player.setPosition(i+move, COL-1);

        }
    }else if(player.getPositionI() == ROW-1){  //GESTIONE SPOSTAMENTO ULTIMA RIGA
        j = player.getPositionJ();
        if((j-move) < 1){
            diffCol =move - (j-1);
            i = (ROW-1) - diffCol;
            if(i > 0){
                board[i][1] += player.getChar();
                player.setPosition(i,1);
            }else{
                int tmp = (j-1) + (ROW-2);
                j = move-tmp;
                board[1][1+j] += player.getChar();
                player.setPosition(1, j+1);
            }
        }else{
            board[ROW-1][j-move] += player.getChar();
            player.setPosition(ROW-1, j-move);

        }  
    }else if(player.getPositionJ() == 1){  //GESTIONE SPOSTAMENTO PRIMA COLONNA
        i = player.getPositionI();
        if((i-move) < 1){
            diffCol = i-2;
            move -= diffCol;
            if(move > COL-1){
                move -= (COL-2);
                board[move][COL-1] += player.getChar();
                player.setPosition(move, COL-1);
            }else{
                board[1][move] += player.getChar();
                player.setPosition(1, move);
            }
        }else{
            board[i-move][1] += player.getChar();
            player.setPosition(i-move, 1);

        }
    }
}


#include "scoreBoard.hpp"

#endif
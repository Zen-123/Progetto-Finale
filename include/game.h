#ifndef GAME_H
#define GAME_H

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
static HumanPlayer HP("1");  //di default impostato su giocatore 1

//Funzioni per riempire il tabellone
void firstRow(std::string board[ROW][COL]);
void lastRow(std::string board[ROW][COL]);
void firstCol(std::string board[ROW][COL]);
void lastCol(std::string board[ROW][COL]);

//funzione che stampa a video il tabellone
void printScoreboard(std::string board[ROW][COL]);

//funzioni che gestisce l'inserimento di ogni casella di tipo economy, standard o luxury
void fillAllSquaresColumn(std::string board[ROW][COL], int index, int position );
void fillAllSquaresRows(std::string board[ROW][COL], int index, int position );

//funzione che gestisce il tiro di dati iniziale per stabilire ordine dei giocatori
void setTurn(std::string order[4], bool gameType);

//funzione che rimuove il carattere del giocatore nella casella in cui si trovava in precedenza
void removePrevChar(std::string board[ROW][COL], Player& player);

//funzione ausiliaria per poter utilizzare std::sort
bool cmp(std::pair<std::string, int>& a, std::pair<std::string, int>& b);

void checkDiceNumber(std::map<std::string, int>& mp);

void setPositionPlayer(Player& player, std::string board[ROW][COL]);

void rentComputerPlayer(Player& player, std::string board[ROW][COL]);

void rentHumanPlayer(std::string board[ROW][COL]);

void classification(std::string order[TURN], bool checkIfBankrupt, bool gameType);

void setScoreboard(std::string board[ROW][COL]);

void checkShowCommand(std::string board[ROW][COL]);



void game(bool gameType){

    std::string board[ROW][COL];
    std::string order[TURN];
    setTurn(order, gameType);


      //funzione per stabilire i turni

    std::cout<<"Ordine giocatori: \n";

    for(int i=0; i<TURN; i++)
        std::cout<<order[i]<<"  ";
    std::cout<<"\n";

    setScoreboard(board);


    //VARIABILI USATE PER TEST SPOSTAMENTO
    int move, n;
    int countTurn = 0;
    int countPlayerOrder = 0;
    int i, j;

    bool firstTurn = true;  
    int countMaxTurn = 1;
    std::string bankruptPlayer;
    bool checkIfBankrupt = false;
    std::string showCommand;


    srand(time(NULL));
    //GIRO GESTITO IN SENSO ORARIO PARTENDO DA POSIZIONE [1][1] = " P "
    do{


        
        if(order[countTurn] == P1.getChar()){

            if( gameType == false){
                removePrevChar(board,P1);
                std::cout<<"Turno Giocatore " + P1.getChar()+ "\n";
                P1.logOutput("Turno Giocatore " + P1.getChar());
                setPositionPlayer(P1, board);
                if(P1.randomChoice()){
                    i = P1.getPositionI();
                    j = P1.getPositionJ();

                    if((board[i][j].substr(0, 1) == "E" || board[i][j].substr(0, 1) == "S" || board[i][j].substr(0, 1) == "L")){
                        if(board[i][j].find('*') != board[i][j].npos)
                            P1.checkPurchaseHotel(board,E,S,L);
                        else   
                            P1.checkPurchaseHouse(board, E, S, L);
        
                    }
                
                }
                rentComputerPlayer(P1, board);

                if(P1.checkIfBankrupt()){
                    std::cout<<"Giocatore " + P1.getChar() + " è andato il bancarotta!\n";
                    P1.logOutput("Giocatore " + P1.getChar() + " è andato il bancarotta!");
                    checkIfBankrupt = true;
                    order->erase(std::remove(order->begin(), order->end(), '1'), order->end());
                    P1.removePlayerCharIfBankrupt(board,E,S,L);
                }
                P1.logOutput("Giocatore " + P1.getChar() + " ha finito il turno");
            }else{
                removePrevChar(board,HP);
                std::cout<<"Turno Giocatore " + HP.getChar()+ "\n";
                HP.logOutput("Turno Giocatore " + HP.getChar());
                setPositionPlayer(HP, board);
                std::cout<<"Posizione: " + HP.getPositionChar()<<" "<<HP.getPositionI()<<" - "<<HP.getPositionJ()<<"\n";
                checkShowCommand(board);
                std::cout<<"\n";
                if(HP.getUserChoice(board, E,S,L)){
                    i = HP.getPositionI();
                    j = HP.getPositionJ();
                     if((board[i][j].substr(0, 1) == "E" || board[i][j].substr(0, 1) == "S" || board[i][j].substr(0, 1) == "L")){
                        if(board[i][j].find('*') != board[i][j].npos)
                            HP.checkPurchaseHotel(board,E,S,L);
                        else   
                            HP.checkPurchaseHouse(board, E, S, L);

                    }
                }
                checkShowCommand(board);
                rentHumanPlayer(board); 

                if(HP.checkIfBankrupt()){
                    std::cout<<"Giocatore " + HP.getChar() + " è andato il bancarotta!\n";
                    HP.logOutput("Giocatore " + HP.getChar() + " è andato il bancarotta!");
                    checkIfBankrupt = true;
                    order->erase(std::remove(order->begin(), order->end(), '1'), order->end());
                    HP.removePlayerCharIfBankrupt(board,E,S,L);
                }

                HP.logOutput("Giocatore " +HP.getChar() + " ha finito il turno");
                
            }
            

            
        }else if(order[countTurn] == P2.getChar()){
            removePrevChar(board,P2);
            std::cout<<"Turno Giocatore " + P2.getChar()+ "\n";
            P2.logOutput("Turno Giocatore " + P2.getChar());
            setPositionPlayer(P2, board);
            if(P2.randomChoice() == true){
                i = P2.getPositionI();
                j = P2.getPositionJ();
                 if((board[i][j].substr(0, 1) == "E" || board[i][j].substr(0, 1) == "S" || board[i][j].substr(0, 1) == "L")){
                        if(board[i][j].find('*') != board[i][j].npos)
                            P2.checkPurchaseHotel(board,E,S,L);
                        else   
                            P2.checkPurchaseHouse(board, E, S, L);
                }
            }

            rentComputerPlayer(P2, board);
            if(P2.checkIfBankrupt()){
                std::cout<<"Giocatore " + P2.getChar() + " è andato il bancarotta!\n";
                P2.logOutput("Giocatore " + P2.getChar() + " è andato il bancarotta!");

                checkIfBankrupt = true;
                order->erase(std::remove(order->begin(), order->end(), '2'), order->end());
                P2.removePlayerCharIfBankrupt(board,E,S,L);

            }
            P2.logOutput("Giocatore " + P2.getChar() + " ha finito il turno");

        }else if(order[countTurn] == P3.getChar()){
            removePrevChar(board,P3);
            std::cout<<"Turno Giocatore " + P3.getChar()+ "\n";
            P3.logOutput("Turno Giocatore " + P3.getChar());
            setPositionPlayer(P3, board);
            if(P3.randomChoice() == true){
                i = P3.getPositionI();
                j = P3.getPositionJ();
                 if((board[i][j].substr(0, 1) == "E" || board[i][j].substr(0, 1) == "S" || board[i][j].substr(0, 1) == "L")){
                     if(board[i][j].find('*') != board[i][j].npos)
                        P3.checkPurchaseHotel(board,E,S,L);
                    else   
                        P3.checkPurchaseHouse(board, E, S, L);
                }
            }

            rentComputerPlayer(P3, board);
              if(P3.checkIfBankrupt()){
                std::cout<<"Giocatore " + P3.getChar() + " è andato il bancarotta!\n";
                P3.logOutput("Giocatore " + P3.getChar() + " è andato il bancarotta!");

                checkIfBankrupt = true;
                order->erase(std::remove(order->begin(), order->end(), '3'), order->end());
                P3.removePlayerCharIfBankrupt(board,E,S,L);
            }
            P3.logOutput("Giocatore " + P3.getChar() + " ha finito il turno");

        }else if(order[countTurn] == P4.getChar()){
            removePrevChar(board,P4);
            std::cout<<"Turno Giocatore " + P4.getChar()+ "\n";
            P4.logOutput("Turno Giocatore " + P4.getChar());
            setPositionPlayer(P4, board);
            if(P4.randomChoice() == true){
                i = P4.getPositionI();
                j = P4.getPositionJ();
                if((board[i][j].substr(0, 1) == "E" || board[i][j].substr(0, 1) == "S" || board[i][j].substr(0, 1) == "L")){
                    if(board[i][j].find('*') != board[i][j].npos)
                        P4.checkPurchaseHotel(board,E,S,L);
                    else   
                        P4.checkPurchaseHouse(board, E, S, L);
                    }
                }
             
            rentComputerPlayer(P4, board);
            if(P4.checkIfBankrupt()){
                std::cout<<"Giocatore " + P4.getChar() + " è andato il bancarotta!\n";
                P4.logOutput("Giocatore " + P4.getChar() + " è andato il bancarotta!");

                checkIfBankrupt = true;
                order->erase(std::remove(order->begin(), order->end(), '4'), order->end());
                P4.removePlayerCharIfBankrupt(board,E,S,L);

            }
            P4.logOutput("Giocatore " + P4.getChar() + " ha finito il turno");

        }
        //printScoreboard(board);
        countTurn++;
        if(countTurn == TURN){
            std::cout<<"\n----------------------\n";
            std::cout<<"\nFINE TURNO "<<countMaxTurn<<"\n";
            std::cout<<"\n----------------------\n";
            countMaxTurn++;
            countTurn = 0;
            firstTurn = false;
            
        }
    }while(countMaxTurn <= MAX_TURN);
    printScoreboard(board);
    classification(order, checkIfBankrupt, gameType);

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

void checkShowCommand(std::string board[ROW][COL]){

   
    std::string showCommand;
    std::cout<<"\nInserire il comando show per la visualizzazione: ";
    std::getline(std::cin, showCommand, '\n');

    if(showCommand == "SHOW" || showCommand == "show"){
        std::cout<<"\n\nTABELLONE:\n";
        printScoreboard(board);
        std::cout<<"\nLista terreni giocatori:\n";
        HP.printStatus();
        P2.printStatus();
        P3.printStatus();
        P4.printStatus();
        std::cout<<"\nBudget giocatori: \n";
        std::cout<<"Giocatore 1: "<<HP.getBudget()<<"\n";
        std::cout<<"Giocatore 2: "<<P2.getBudget()<<"\n";
        std::cout<<"Giocatore 3: "<<P3.getBudget()<<"\n";
        std::cout<<"Giocatore 4: "<<P4.getBudget()<<"\n\n";


    }
}


#include "game.hpp"

#endif

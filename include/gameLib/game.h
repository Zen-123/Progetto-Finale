#ifndef GAME_H
#define GAME_H

const int ROW = 9;
const int COL = 9;
const int TURN = 4;

static int EconomicSquareNumber = 8;
static int StandardSquareNumber = 10;
static int LuxurySquareNumber = 6;
static std::string board[ROW][COL];
    
static AngularSquare A;
static EconomicSquare E;
static StandardSquare S;
static LuxurySquare L;

static ComputerPlayer P1("1");
static ComputerPlayer P2("2");  
static ComputerPlayer P3("3");
static ComputerPlayer P4("4");
static HumanPlayer HP("1");  //giocatore umano di default impostato su giocatore 1

//Funzioni per riempire il tabellone
void firstRow();
void lastRow();
void firstCol();
void lastCol();

//funzione che stampa a video il tabellone
void printScoreboard();

//funzioni che gestisce l'inserimento di ogni casella di tipo economy, standard o luxury
void fillAllSquaresColumn(int index, int position );
void fillAllSquaresRows(int index, int position );

//funzione che gestisce il tiro di dati iniziale per stabilire ordine dei giocatori
void setTurn(std::string order[4], bool gameType);

//funzione che rimuove il carattere del giocatore nella casella in cui si trovava in precedenza
void removePrevChar(Player& player);

//funzione ausiliaria per poter utilizzare std::sort
bool cmp(std::pair<std::string, int>& a, std::pair<std::string, int>& b);

void checkDiceNumber(std::map<std::string, int>& mp);

void setPositionPlayer(Player& player);

bool rentComputerPlayer(Player& player);

void rentHumanPlayer();

void classification(std::string order[TURN], bool checkIfBankrupt, bool gameType);

void setScoreboard();

void checkShowCommand();



void game(bool gameType, const int MAX_TURN){

    std::string order[TURN];
    setTurn(order, gameType);
  
   
        

      //funzione per stabilire i turni

    std::cout<<"Ordine giocatori: \n";

    for(int i=0; i<TURN; i++)
        std::cout<<order[i]<<"  ";
    std::cout<<"\n";

    setScoreboard();


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
    bool checkPurchase = false;


    srand(time(NULL));
    //GIRO GESTITO IN SENSO ORARIO PARTENDO DA POSIZIONE [1][1] = " P "
    do{
       
       checkPurchase = false;

        
        if(order[countTurn] == P1.getChar()){

            if( gameType == false){
                removePrevChar(P1);
                std::cout<<"-Turno Giocatore " + P1.getChar()+ "\n";
                P1.logOutput("-Turno Giocatore " + P1.getChar());
                setPositionPlayer(P1);
                if(P1.randomChoice()){
                    i = P1.getPositionI();
                    j = P1.getPositionJ();

                    if((board[i][j].substr(0, 1) == "E" || board[i][j].substr(0, 1) == "S" || board[i][j].substr(0, 1) == "L")){
                        if(E.getPlayer(i,j) == P1.getChar() || L.getPlayer(i,j) == P1.getChar() || S.getPlayer(i,j) == P1.getChar()){
                            if(board[i][j].find('*') != board[i][j].npos)
                                checkPurchase = P1.checkPurchaseHotel(board,E,S,L);
                            else   
                                checkPurchase = P1.checkPurchaseHouse(board, E, S, L);
                        }else if(E.getPlayer(i,j) == " " || L.getPlayer(i,j) == " " || S.getPlayer(i,j) == " "){
                            checkPurchase = P1.checkPurchaseSquare(board, E,S,L);
                        }
                        
                    }
                
                }
                if(checkPurchase == false){

                    rentComputerPlayer(P1);
                }
                

                    

                if(P1.checkIfBankrupt()){
                    std::cout<<"-Giocatore " + P1.getChar() + " è stato elimitato\n";
                    P1.logOutput("-Giocatore " + P1.getChar() + " è stato elimitato");
                    checkIfBankrupt = true;
                    order->erase(std::remove(order->begin(), order->end(), '1'), order->end());
                    P1.removePlayerCharIfBankrupt(board,E,S,L);
                } 
                std::cout<<"-Giocatore "+ P1.getChar() + " ha finito il turno\n";
                P1.logOutput("-Giocatore " + P1.getChar() + " ha finito il turno\n");
                
            }else{
                removePrevChar(HP);
                std::cout<<"\n-Turno Giocatore " + HP.getChar()+ "\n";
                HP.logOutput("\n-Turno Giocatore " + HP.getChar());
                checkShowCommand();
                setPositionPlayer(HP);
                checkShowCommand();
                std::cout<<"\n";
                if(HP.getUserChoice(board, E,S,L)){
                    i = HP.getPositionI();
                    j = HP.getPositionJ();
                     if((board[i][j].substr(0, 1) == "E" || board[i][j].substr(0, 1) == "S" || board[i][j].substr(0, 1) == "L")){
                      if(E.getPlayer(i,j) == HP.getChar() || L.getPlayer(i,j) == HP.getChar() || S.getPlayer(i,j) == HP.getChar()){
                            if(board[i][j].find('*') != board[i][j].npos)
                                checkPurchase = HP.checkPurchaseHotel(board,E,S,L);
                            else   
                                checkPurchase = HP.checkPurchaseHouse(board, E, S, L);
                        }else if(E.getPlayer(i,j) == " " || L.getPlayer(i,j) == " " || S.getPlayer(i,j) == " "){
                            checkPurchase = HP.checkPurchaseSquare(board, E,S,L);
                        }
                    }
                }
                if(checkPurchase == false){
                    rentHumanPlayer();
                }

                checkShowCommand();
                rentHumanPlayer(); 

                if(HP.checkIfBankrupt()){
                    std::cout<<"-Giocatore " + HP.getChar() + " è stato elimitato\n";
                    HP.logOutput("-Giocatore " + HP.getChar() + " è stato elimitato\n");
                    checkIfBankrupt = true;
                    order->erase(std::remove(order->begin(), order->end(), '1'), order->end());
                    HP.removePlayerCharIfBankrupt(board,E,S,L);
                }
                std::cout<<"-Giocatore "+ HP.getChar() + " ha finito il turno\n";
                HP.logOutput("-Giocatore " +HP.getChar() + " ha finito il turno\n");
                
            }
            

            
        }else if(order[countTurn] == P2.getChar()){
            removePrevChar(P2);
            std::cout<<"-Turno Giocatore " + P2.getChar()+ "\n";
            P2.logOutput("-Turno Giocatore " + P2.getChar()+ "\n");
            setPositionPlayer(P2);
            if(P2.randomChoice() == true){
                i = P2.getPositionI();
                j = P2.getPositionJ();
                 if((board[i][j].substr(0, 1) == "E" || board[i][j].substr(0, 1) == "S" || board[i][j].substr(0, 1) == "L"  )){
                    if(E.getPlayer(i,j) == P2.getChar() || L.getPlayer(i,j) == P2.getChar() || S.getPlayer(i,j) == P2.getChar()){
                            if(board[i][j].find('*') != board[i][j].npos)
                                checkPurchase = P2.checkPurchaseHotel(board,E,S,L);
                            else   
                                checkPurchase = P2.checkPurchaseHouse(board, E, S, L);
                        }else if(E.getPlayer(i,j) == " " || L.getPlayer(i,j) == " " || S.getPlayer(i,j) == " "){
                            checkPurchase = P2.checkPurchaseSquare(board, E,S,L);
                        }
                }
            }
            if(checkPurchase == false){

                rentComputerPlayer(P2);
            }

                


            if(P2.checkIfBankrupt()){
                std::cout<<"-Giocatore " + P2.getChar() + " è stato elimitato\n";
                P2.logOutput("-Giocatore " + P2.getChar() + " è stato elimitato\n");

                checkIfBankrupt = true;
                order->erase(std::remove(order->begin(), order->end(), '2'), order->end());
                P2.removePlayerCharIfBankrupt(board,E,S,L);

            }
            std::cout<<"-Giocatore "+ P2.getChar() + " ha finito il turno\n";
            P2.logOutput("-Giocatore " + P2.getChar() + " ha finito il turno\n");

        }else if(order[countTurn] == P3.getChar()){
            removePrevChar(P3);
            std::cout<<"-Turno Giocatore " + P3.getChar()+ "\n";
            P3.logOutput("-Turno Giocatore " + P3.getChar()+ "\n");
            setPositionPlayer(P3);
            if(P3.randomChoice() == true){
                i = P3.getPositionI();
                j = P3.getPositionJ();
                 if((board[i][j].substr(0, 1) == "E" || board[i][j].substr(0, 1) == "S" || board[i][j].substr(0, 1) == "L" )){
                    if(E.getPlayer(i,j) == P3.getChar() || L.getPlayer(i,j) == P3.getChar() || S.getPlayer(i,j) == P3.getChar()){
                            if(board[i][j].find('*') != board[i][j].npos)
                                checkPurchase = P3.checkPurchaseHotel(board,E,S,L);
                            else   
                                checkPurchase = P3.checkPurchaseHouse(board, E, S, L);
                        }else if(E.getPlayer(i,j) == " " || L.getPlayer(i,j) == " " || S.getPlayer(i,j) == " "){
                            checkPurchase = P3.checkPurchaseSquare(board, E,S,L);
                        }

                }
            }
            if(checkPurchase == false){
                rentComputerPlayer(P3);

            }


              if(P3.checkIfBankrupt()){
                std::cout<<"-Giocatore " + P3.getChar() + " è stato elimitato\n";
                P3.logOutput("-Giocatore " + P3.getChar() + " è stato elimitato\n");

                checkIfBankrupt = true;
                order->erase(std::remove(order->begin(), order->end(), '3'), order->end());
                P3.removePlayerCharIfBankrupt(board,E,S,L);
            }
            std::cout<<"-Giocatore "+ P3.getChar() + " ha finito il turno\n";

            P3.logOutput("-Giocatore " + P3.getChar() + " ha finito il turno\n");

        }else if(order[countTurn] == P4.getChar()){
            removePrevChar(P4);
            std::cout<<"\n-Turno Giocatore " + P4.getChar()+ "\n";
            P4.logOutput("\nT-urno Giocatore " + P4.getChar());
            setPositionPlayer(P4);
            if(P4.randomChoice() == true){
                i = P4.getPositionI();
                j = P4.getPositionJ();
                if((board[i][j].substr(0, 1) == "E" || board[i][j].substr(0, 1) == "S" || board[i][j].substr(0, 1) == "L")){ 
                    if(E.getPlayer(i,j) == P4.getChar() || L.getPlayer(i,j) == P4.getChar() || S.getPlayer(i,j) == P4.getChar()){
                        if(board[i][j].find('*') != board[i][j].npos)
                                checkPurchase = P4.checkPurchaseHotel(board,E,S,L);
                        else   
                            checkPurchase = P4.checkPurchaseHouse(board, E, S, L);
                        }else if(E.getPlayer(i,j) == " " || L.getPlayer(i,j) == " " || S.getPlayer(i,j) == " "){
                            checkPurchase = P4.checkPurchaseSquare(board, E,S,L);
                        }
                }
            }
             if(checkPurchase == false){
                rentComputerPlayer(P4);

             }
                

            
            if(P4.checkIfBankrupt()){
                std::cout<<"-Giocatore " + P4.getChar() + " è stato elimitato\n";
                P4.logOutput("-Giocatore " + P4.getChar() + " è stato elimitato\n");

                checkIfBankrupt = true;
                order->erase(std::remove(order->begin(), order->end(), '4'), order->end());
                P4.removePlayerCharIfBankrupt(board,E,S,L);

            }
            std::cout<<"-Giocatore "+ P4.getChar() + " ha finito il turno\n";
            P4.logOutput("-Giocatore " + P4.getChar() + " ha finito il turno\n");

        }
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
    printScoreboard();
    classification(order, checkIfBankrupt, gameType);

}




#include "game.hpp"

#endif

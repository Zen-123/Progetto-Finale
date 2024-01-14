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
static HumanPlayer HP("1");  //di default impostato su giocatore 1


void firstRow(std::string board[ROW][COL]);
void lastRow(std::string board[ROW][COL]);
void firstCol(std::string board[ROW][COL]);
void lastCol(std::string board[ROW][COL]);

void printScoreboard(std::string board[ROW][COL]);

void fillAllSquaresColumn(std::string board[ROW][COL], int index, int position );
void fillAllSquaresRows(std::string board[ROW][COL], int index, int position );

void setTurn(std::string order[4], bool gameType);

void removePrevChar(std::string board[ROW][COL], Player& player);

bool cmp(std::pair<std::string, int>& a, std::pair<std::string, int>& b);

void checkDiceNumber(std::map<std::string, int>& mp);

void setPosition(Player& player, std::string board[ROW][COL]);

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
                setPosition(P1, board);
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
                setPosition(HP, board);
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
            setPosition(P2, board);
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
            setPosition(P3, board);
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
            setPosition(P4, board);
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
void classification(std::string order[TURN], bool checkIfBankrupt, bool gameType){

    std::map<std::string, int> playerClassification;
    std::cout<<"\n\nCLASSIFICA GIOCATORI\n\n";


    for(int i = 0; i < TURN; i++){
        if(order[i] == P1.getChar()){
            if(gameType == false && P1.checkIfBankrupt() == false)
                playerClassification.insert({order[i], P1.getBudget()});
            else if(gameType == true && HP.checkIfBankrupt() == false)
                playerClassification.insert({order[i], HP.getBudget()});
        }
        if(order[i] == P2.getChar() && P2.checkIfBankrupt() == false){
            playerClassification.insert({order[i], P2.getBudget()});

        }
        if(order[i] == P3.getChar() && P3.checkIfBankrupt() == false){
            playerClassification.insert({order[i], P3.getBudget()});

        }
        if(order[i] == P4.getChar() && P4.checkIfBankrupt() == false){
            playerClassification.insert({order[i], P4.getBudget()});
        }
    }

    std::vector<std::pair<std::string, int> > tmpVec;  //vettore di supporto di tipo pair (string, int)

    for(auto& it: playerClassification)
        tmpVec.push_back(it);

     std::sort(tmpVec.begin(), tmpVec.end(), cmp);

    int pos =1;    
     for(auto& it: tmpVec)
        std::cout<<pos++<<"° Giocatore n."<<it.first<<"  "<<it.second<<"\n";
     

   if(checkIfBankrupt){
        std::cout<<"\nGIOCATORI CHE HANNO PERSO: \n";
        if(P1.checkIfBankrupt())
            std::cout<<"Giocatore " +  P1.getChar()<<"\n";
        if(P2.checkIfBankrupt())
            std::cout<<"Giocatore " +  P2.getChar()<<"\n";
        if(P3.checkIfBankrupt())
            std::cout<<"Giocatore " +  P3.getChar()<<"\n";
        if(P4.checkIfBankrupt())
            std::cout<<"Giocatore " +  P4.getChar()<<"\n";

    }
    
}


void setScoreboard(std::string board[ROW][COL]){


    char initRows[] ={' ','A','B','C','D','E','F','G','H'};
    char initCols[] ={' ','1','2','3','4','5','6','7','8'};

    board[1][1] = "P";
    board[1][COL-1] = A.ShowSquare();
    board[ROW-1][1] = A.ShowSquare();
    board[ROW-1][COL-1] = A.ShowSquare();

    //RIEMPIMENTO CASELLE

    for(int j = 1; j<COL; j++)
        board[0][j] = initCols[j];

    for(int i = 1; i<COL; i++)
        board[i][0] = initCols[i];

    for(int i =2; i<ROW-1; i++){
        for(int j =2; j<COL-1; j++){
            board[i][j] = ' ';
        }
    }
    
    firstRow(board);
    lastRow(board);
    firstCol(board);
    lastCol(board);

    
}

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


void setPosition(Player& player, std::string board[ROW][COL]){
    int diffCol, diffRow, move, n, i ,j;
    bool checkFirstSquare = false;  //variabile per controllo se il giocatore passa per casella P
    move = player.throwDice(); 
    std::cout<<"Dado: "<<move<<"\n";
    if(player.getPositionI() == 1  ){  //GESTIONE SPOSTAMENTO PRIMA RIGA
        j = player.getPositionJ();
        if((j+move+1) > COL-1 ){
            diffCol = (COL-1) - (j);
            int tmp = (COL-2)  + diffCol;
            j = move - tmp;
            if(j>0){
                board[ROW-1][(COL-1)-j] += player.getChar();
                player.setPosition(ROW-1, (COL-1)-j, board[ROW-1][(COL-1)-j]);
            }else{
                i =1+ (move - diffCol);
                board[i][COL-1] += player.getChar();
                player.setPosition(i, COL-1, board[i][COL-1]);
            }
        }else{
            player.setPosition(1, j+move, board[1][j+move]);
            board[1][j+move] += player.getChar();
        }
        
    }else if(player.getPositionJ() == COL-1 ){  //GESTIONE SPOSTAMENTO ULTIMA COLONNA
        i = player.getPositionI();
        if((i+move) > ROW-1){
            diffRow = move - ((COL-1) - i);
                diffCol = (ROW-1) - diffRow;
            if(diffCol > 0){
                board[ROW-1][diffCol] += player.getChar();
                player.setPosition(ROW-1, diffCol,board[ROW-1][diffCol]);
            }else{
                diffRow = move - (ROW-1) - (COL-1-i-1);
                i = (COL-1) - diffRow;
                board[i][1] += player.getChar();
                player.setPosition(i, 1, board[i][1]);
            }
            
            
        }else{
            board[i+move][COL-1] += player.getChar();
            player.setPosition(i+move, COL-1,board[i+move][COL-1]);

        }
    }else if(player.getPositionI() == ROW-1){  //GESTIONE SPOSTAMENTO ULTIMA RIGA
        j = player.getPositionJ();
        if((j-move) < 1){
            diffCol =move - (j-1);
            i = (ROW-1) - diffCol;
            if(i > 0){
                board[i][1] += player.getChar();
                player.setPosition(i,1,board[i][1]);
            }else{
                int tmp = (j-1) + (ROW-2);
                j = move-tmp;
                board[1][1+j] += player.getChar();
                player.setPosition(1, j+1,board[1][1+j] );
                if(!checkFirstSquare){
                    player.increaseBudget();//il giocatore passa per la casella P
                    checkFirstSquare = true;
                }
            }
        }else{
            board[ROW-1][j-move] += player.getChar();
            player.setPosition(ROW-1, j-move,board[ROW-1][j-move]);

        }  
    }else if(player.getPositionJ() == 1){  //GESTIONE SPOSTAMENTO PRIMA COLONNA
        i = player.getPositionI();
        if((i-move) < 1){
            diffCol = i-2;
            move -= diffCol;
            if(move > COL-1){
                move -= (COL-2);
                board[move][COL-1] += player.getChar();
                 if(!checkFirstSquare){
                    player.increaseBudget();
                    checkFirstSquare = true;
                }
                player.setPosition(move, COL-1,board[move][COL-1]);
            }else{
                if(!checkFirstSquare){
                    player.increaseBudget();
                    checkFirstSquare = true;
                }
                board[1][move] += player.getChar();
                player.setPosition(1, move,board[1][move]);
            }
        }else{
            board[i-move][1] += player.getChar();
            player.setPosition(i-move, 1,board[i-move][1]);
            if(!checkFirstSquare && board[i-move][1].substr(0,1) ==  "P"){
                player.increaseBudget();
                checkFirstSquare = true;
            }

        }
    }
}

void rentComputerPlayer(Player& player, std::string board[ROW][COL]){
    

    std::map<std::string, std::vector<Position>> otherProperties;
    int i = player.getPositionI();
    int j = player.getPositionJ();
    if(player.getChar() == "1" ){

        std::vector<Position> tmp;

        for(auto& it : P2.getProperty())
            tmp.push_back(it);
        otherProperties["2"] = tmp;

        tmp.clear();

        for(auto& it : P3.getProperty())
            tmp.push_back(it);

        otherProperties["3"] = tmp;
        tmp.clear();

        for(auto& it : P4.getProperty())
            tmp.push_back(it);

        otherProperties["4"] = tmp;

        if(std::find(otherProperties["2"].begin(), otherProperties["2"].end(), player.getPosition()) != otherProperties["2"].end()){
            if(board[i][j].find('*') != board[i][j].npos){
                if(player.getPositionChar() == "E"){
                    int rent = E.getRentHomePrice();
                    P1.decrescenteBudgetRent(rent); 
                    P2.increaseBudgetRent(rent);
                    P1.logOutput("Giocatore " + player.getChar() + " ha pagato 2 fiorini a giocatore 2 per pernottamento nella casella "+ board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 2 fiorini a giocatore 2 per pernottamento nella casella " +board[i][j]<<"\n";
                }else if(player.getPositionChar() == "S"){
                    int rent = S.getRentHomePrice();
                    P1.decrescenteBudgetRent(rent); 
                    P2.increaseBudgetRent(rent);
                   P1.logOutput("Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 2 per pernottamento nella casella " + board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 2 per pernottamento nella casella " +board[i][j]<<"\n";
                }else if(player.getPositionChar() == "L"){
                    int rent = L.getRentHomePrice();
                    P1.decrescenteBudgetRent(rent); 
                    P2.increaseBudgetRent(rent);
                    P1.logOutput("Giocatore " + player.getChar() + " ha pagato 7 fiorini a giocatore 2 per pernottamento nella casella " + board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 7 fiorini a giocatore 2 per pernottamento nella casella "+ board[i][j]<<"\n";
                }
                
            }else if(board[i][j].find('^') != board[i][j].npos){
                 if(player.getPositionChar() == "E"){
                    int rent = E.getRentHotelPrice();
                    P1.decrescenteBudgetRent(rent); 
                    P2.increaseBudgetRent(rent);
                    P1.logOutput("Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 2 per pernottamento nella casella " + board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 2 per pernottamento nella casella " +board[i][j]<<"\n";
                }else if(player.getPositionChar() == "S"){
                    int rent = S.getRentHotelPrice();
                    P1.decrescenteBudgetRent(rent); 
                    P2.increaseBudgetRent(rent);
                    P1.logOutput("Giocatore " + player.getChar() + " ha pagato 8 fiorini a giocatore 2 per pernottamento nella casella " + board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 8 fiorini a giocatore 2 per pernottamento nella casella " +board[i][j]<<"\n";
                }else if(player.getPositionChar() == "L"){
                    int rent = L.getRentHotelPrice();
                    P1.decrescenteBudgetRent(rent); 
                    P2.increaseBudgetRent(rent);
                    P1.logOutput("Giocatore " + player.getChar() + " ha pagato 14 fiorini a giocatore 2 per pernottamento nella casella " + board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 14 fiorini a giocatore 2 per pernottamento nella casella " +board[i][j]<<"\n";
                }
            }
        }
        if(std::find(otherProperties["3"].begin(), otherProperties["3"].end(), player.getPosition()) != otherProperties["3"].end()){
            if(board[i][j].find('*') != board[i][j].npos){
                if(player.getPositionChar() == "E"){
                    int rent = E.getRentHomePrice();
                    P1.decrescenteBudgetRent(rent); 
                    P3.increaseBudgetRent(rent);
                    P1.logOutput("Giocatore " + player.getChar() + " ha pagato 2 fiorini a giocatore 3 per pernottamento nella casella " +board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 2 fiorini a giocatore 3 per pernottamento nella casella " +board[i][j]<<"\n";              
                }else if(player.getPositionChar() == "S"){
                    int rent = S.getRentHomePrice();
                    P1.decrescenteBudgetRent(rent); 
                    P3.increaseBudgetRent(rent);
                    P1.logOutput("Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 3 per pernottamento nella casella " +board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 3 per pernottamento nella casella "+board[i][j]<<"\n";
                }else if(player.getPositionChar() == "L"){
                    int rent = L.getRentHomePrice();
                    P1.decrescenteBudgetRent(rent); 
                    P3.increaseBudgetRent(rent);
                    P1.logOutput("Giocatore " + player.getChar() + " ha pagato 7 fiorini a giocatore 3 per pernottamento nella casella "+board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 7 fiorini a giocatore 3 per pernottamento nella casella " +board[i][j]<<"\n";
                }

            }else if(board[i][j].find('^') != board[i][j].npos){
                 if(player.getPositionChar() == "E"){
                    int rent = E.getRentHotelPrice();
                    P1.decrescenteBudgetRent(rent); 
                    P3.increaseBudgetRent(rent);
                    P1.logOutput("Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 3 per pernottamento nella casella " +board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 3 per pernottamento nella casella " +board[i][j]<<"\n";
                }else if(player.getPositionChar() == "S"){
                    int rent = S.getRentHotelPrice();
                    P1.decrescenteBudgetRent(rent); 
                    P3.increaseBudgetRent(rent);
                    P1.logOutput("Giocatore " + player.getChar() + " ha pagato 8 fiorini a giocatore 3 per pernottamento nella casella " +board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 8 fiorini a giocatore 3 per pernottamento nella casella " +board[i][j]<<"\n";
                }else if(player.getPositionChar() == "L"){
                    int rent = L.getRentHotelPrice();
                    P1.decrescenteBudgetRent(rent); 
                    P3.increaseBudgetRent(rent);
                    P1.logOutput("Giocatore " + player.getChar() + " ha pagato 14 fiorini a giocatore 3 per pernottamento nella casella "+ board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 14 fiorini a giocatore 3 per pernottamento nella casella "+board[i][j]<<"\n";
                }
            }
        }
         if(std::find(otherProperties["4"].begin(), otherProperties["4"].end(), player.getPosition()) != otherProperties["4"].end()){
            if(board[i][j].find('*') != board[i][j].npos){
                if(player.getPositionChar() == "E"){
                    int rent = E.getRentHomePrice();
                    P1.decrescenteBudgetRent(rent); 
                    P4.increaseBudgetRent(rent);
                    P1.logOutput("Giocatore " + player.getChar() + " ha pagato 2 fiorini a giocatore 4 per pernottamento nella casella " +board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 2 fiorini a giocatore 4 per pernottamento nella casella "+board[i][j]<<"\n";
                }else if(player.getPositionChar() == "S"){
                    int rent = S.getRentHomePrice();
                    P1.decrescenteBudgetRent(rent); 
                    P4.increaseBudgetRent(rent);
                    P1.logOutput("Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 4 per pernottamento nella casella " +board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 4 per pernottamento nella casella " +board[i][j]<<"\n";
                }else if(player.getPositionChar() == "L"){
                    int rent = L.getRentHomePrice();
                    P1.decrescenteBudgetRent(rent); 
                    P4.increaseBudgetRent(rent);
                    P1.logOutput("Giocatore " + player.getChar() + " ha pagato 7 fiorini a giocatore 4 per pernottamento nella casella "+ board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 7 fiorini a giocatore 4 per pernottamento nella casella "+board[i][j]<<"\n";
                }

            }else if(board[i][j].find('^') != board[i][j].npos){
                 if(player.getPositionChar() == "E"){
                    int rent = E.getRentHotelPrice();
                    P1.decrescenteBudgetRent(rent); 
                    P4.increaseBudgetRent(rent);
                    P1.logOutput("Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 4 per pernottamento nella casella " + board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 4 per pernottamento nella casella " +board[i][j]<< "\n";
                }else if(player.getPositionChar() == "S"){
                    int rent = S.getRentHotelPrice();
                    P1.decrescenteBudgetRent(rent); 
                    P4.increaseBudgetRent(rent);
                    P1.logOutput("Giocatore " + player.getChar() + " ha pagato 8 fiorini a giocatore 4 per pernottamento nella casella "+ board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 8 fiorini a giocatore 4 per pernottamento nella casella "+board[i][j]<<"\n";
                }else if(player.getPositionChar() == "L"){
                    int rent = L.getRentHotelPrice();
                    P1.decrescenteBudgetRent(rent); 
                    P4.increaseBudgetRent(rent);
                    P1.logOutput("Giocatore " + player.getChar() + " ha pagato 14 fiorini a giocatore 4 per pernottamento nella casella "+ board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 14 fiorini a giocatore 4 per pernottamento nella casella "+board[i][j]<<"\n";
                }
            }
        }
        P1.checkIfBankrupt();
    }else if(player.getChar() == "2"){

        std::vector<Position> tmp;

        for(auto& it : P1.getProperty())
            tmp.push_back(it);
        otherProperties["1"] = tmp;

        tmp.clear();

        for(auto& it : P3.getProperty())
            tmp.push_back(it);

        otherProperties["3"] = tmp;
        tmp.clear();

        for(auto& it : P4.getProperty())
            tmp.push_back(it);

        otherProperties["4"] = tmp;
         if(std::find(otherProperties["1"].begin(), otherProperties["1"].end(), player.getPosition()) != otherProperties["1"].end()){
            if(board[i][j].find('*') != board[i][j].npos){
                if(player.getPositionChar() == "E"){
                    int rent = E.getRentHomePrice();
                    P2.decrescenteBudgetRent(rent); 
                    P1.increaseBudgetRent(rent);
                    P2.logOutput("Giocatore " + player.getChar() + " ha pagato 2 fiorini a giocatore 1 per pernottamento nella casella " +board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 2 fiorini a giocatore 1 per pernottamento nella casella " +board[i][j]<<"\n";
                }else if(player.getPositionChar() == "S"){
                    int rent = S.getRentHomePrice();
                    P2.decrescenteBudgetRent(rent); 
                    P1.increaseBudgetRent(rent);
                    P2.logOutput("Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 1 per pernottamento nella casella " +board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 1 per pernottamento nella casella " +board[i][j]<<"\n";
                }else if(player.getPositionChar() == "L"){
                    int rent = L.getRentHomePrice();
                    P2.decrescenteBudgetRent(rent); 
                    P1.increaseBudgetRent(rent);
                    P2.logOutput("Giocatore " + player.getChar() + " ha pagato 7 fiorini a giocatore 1 per pernottamento nella casella " +board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 7 fiorini a giocatore 1 per pernottamento nella casella "+board[i][j]<<"\n";
                }

            }else if(board[i][j].find('^') != board[i][j].npos){
                 if(player.getPositionChar() == "E"){
                    int rent = E.getRentHotelPrice();
                    P2.decrescenteBudgetRent(rent); 
                    P1.increaseBudgetRent(rent);
                    P2.logOutput("Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 1 per pernottamento nella casella " +board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 1 per pernottamento nella casella " +board[i][j]<<"\n";
                }else if(player.getPositionChar() == "S"){
                    int rent = S.getRentHotelPrice();
                    P2.decrescenteBudgetRent(rent); 
                    P1.increaseBudgetRent(rent);
                    P2.logOutput("Giocatore " + player.getChar() + " ha pagato 8 fiorini a giocatore 1 per pernottamento nella casella " +board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 8 fiorini a giocatore 1 per pernottamento nella casella " +board[i][j]<<"\n";
                }else if(player.getPositionChar() == "L"){
                    int rent = L.getRentHotelPrice();
                    P2.decrescenteBudgetRent(rent); 
                    P1.increaseBudgetRent(rent);
                    P2.logOutput("Giocatore " + player.getChar() + " ha pagato 14 fiorini a giocatore 1 per pernottamento nella casella " +board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 14 fiorini a giocatore 1 per pernottamento nella casella " +board[i][j]<<"\n";
                }
            }
        }
        if(std::find(otherProperties["3"].begin(), otherProperties["3"].end(), player.getPosition()) != otherProperties["3"].end()){
            if(board[i][j].find('*') != board[i][j].npos){
                if(player.getPositionChar() == "E"){
                    int rent = E.getRentHomePrice();
                    P2.decrescenteBudgetRent(rent); 
                    P3.increaseBudgetRent(rent);
                    P2.logOutput("Giocatore " + player.getChar() + " ha pagato 2 fiorini a giocatore 3 per pernottamento nella casella " +board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 2 fiorini a giocatore 3 per pernottamento nella casella " +board[i][j]<<"\n";
                }else if(player.getPositionChar() == "S"){
                    int rent = S.getRentHomePrice();
                    P2.decrescenteBudgetRent(rent); 
                    P3.increaseBudgetRent(rent);
                    P2.logOutput("Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 3 per pernottamento nella casella " +board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 3 per pernottamento nella casella " +board[i][j]<<"\n";
                }else if(player.getPositionChar() == "L"){
                    int rent = L.getRentHomePrice();
                    P2.decrescenteBudgetRent(rent); 
                    P3.increaseBudgetRent(rent);
                    P2.logOutput("Giocatore " + player.getChar() + " ha pagato 7 fiorini a giocatore 3 per pernottamento nella casella " +board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 7 fiorini a giocatore 3 per pernottamento nella casella " +board[i][j]<<"\n";
                }

            }else if(board[i][j].find('^') != board[i][j].npos){
                 if(player.getPositionChar() == "E"){
                    int rent = E.getRentHotelPrice();
                    P2.decrescenteBudgetRent(rent); 
                    P3.increaseBudgetRent(rent);
                    P2.logOutput("Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 3 per pernottamento nella casella "+ board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 3 per pernottamento nella casella " +board[i][j]<<"\n";
                }else if(player.getPositionChar() == "S"){
                    int rent = S.getRentHotelPrice();
                    P2.decrescenteBudgetRent(rent); 
                    P3.increaseBudgetRent(rent);
                    P2.logOutput("Giocatore " + player.getChar() + " ha pagato 8 fiorini a giocatore 3 per pernottamento nella casella " +board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 8 fiorini a giocatore 3 per pernottamento nella casella " +board[i][j]<<"\n";
                }else if(player.getPositionChar() == "L"){
                    int rent = L.getRentHotelPrice();
                    P2.decrescenteBudgetRent(rent); 
                    P3.increaseBudgetRent(rent);
                    P2.logOutput("Giocatore " + player.getChar() + " ha pagato 14 fiorini a giocatore 3 per pernottamento nella casella " +board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 14 fiorini a giocatore 3 per pernottamento nella casella " +board[i][j]<<"\n";
                }
            }
        }
         if(std::find(otherProperties["4"].begin(), otherProperties["4"].end(), player.getPosition()) != otherProperties["4"].end()){
            if(board[i][j].find('*') != board[i][j].npos){
                if(player.getPositionChar() == "E"){
                    int rent = E.getRentHomePrice();
                    P2.decrescenteBudgetRent(rent); 
                    P4.increaseBudgetRent(rent);
                    P2.logOutput("Giocatore " + player.getChar() + " ha pagato 2 fiorini a giocatore 4 per pernottamento nella casella " +board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 2 fiorini a giocatore 4 per pernottamento nella casella " +board[i][j]<<"\n";
                }else if(player.getPositionChar() == "S"){
                    int rent = S.getRentHomePrice();
                    P2.decrescenteBudgetRent(rent); 
                    P4.increaseBudgetRent(rent);
                    P2.logOutput("Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 4 per pernottamento nella casella " +board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 4 per pernottamento nella casella " +board[i][j]<<"\n";
                }else if(player.getPositionChar() == "L"){
                    int rent = L.getRentHomePrice();
                    P2.decrescenteBudgetRent(rent); 
                    P4.increaseBudgetRent(rent);
                    P2.logOutput("Giocatore " + player.getChar() + " ha pagato 7 fiorini a giocatore 4 per pernottamento nella casella " +board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 7 fiorini a giocatore 4 per pernottamento nella casella " +board[i][j]<<"\n";
                }

            }else if(board[i][j].find('^') != board[i][j].npos){
                 if(player.getPositionChar() == "E"){
                    int rent = E.getRentHotelPrice();
                    P2.decrescenteBudgetRent(rent); 
                    P4.increaseBudgetRent(rent);
                    P2.logOutput("Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 4 per pernottamento nella casella " +board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 4 per pernottamento nella casella " +board[i][j]<<"\n";
                }else if(player.getPositionChar() == "S"){
                    int rent = S.getRentHotelPrice();
                    P2.decrescenteBudgetRent(rent); 
                    P4.increaseBudgetRent(rent);
                    P2.logOutput("Giocatore " + player.getChar() + " ha pagato 8 fiorini a giocatore 4 per pernottamento nella casella " +board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 8 fiorini a giocatore 4 per pernottamento nella casella " +board[i][j]<<"\n";
                }else if(player.getPositionChar() == "L"){
                    int rent = L.getRentHotelPrice();
                    P2.decrescenteBudgetRent(rent); 
                    P4.increaseBudgetRent(rent);
                    P2.logOutput("Giocatore " + player.getChar() + " ha pagato 14 fiorini a giocatore 4 per pernottamento nella casella " +board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 14 fiorini a giocatore 4 per pernottamento nella casella " +board[i][j]<<"\n";
                }
            }
        }
        P2.checkIfBankrupt();

    }else if(player.getChar() == "3"){

        std::vector<Position> tmp;

        for(auto& it : P1.getProperty())
            tmp.push_back(it);
        otherProperties["1"] = tmp;

        tmp.clear();

        for(auto& it : P2.getProperty())
            tmp.push_back(it);

        otherProperties["2"] = tmp;
        tmp.clear();

        for(auto& it : P4.getProperty())
            tmp.push_back(it);

        otherProperties["4"] = tmp;

         if(std::find(otherProperties["1"].begin(), otherProperties["1"].end(), player.getPosition()) != otherProperties["1"].end()){
            if(board[i][j].find('*') != board[i][j].npos){
                if(player.getPositionChar() == "E"){
                    int rent = E.getRentHomePrice();
                    P3.decrescenteBudgetRent(rent); 
                    P1.increaseBudgetRent(rent);
                    P3.logOutput("Giocatore " + player.getChar() + " ha pagato 2 fiorini a giocatore 1 per pernottamento nella casella " +board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 2 fiorini a giocatore 1 per pernottamento nella casella " +board[i][j]<<"\n";
                }else if(player.getPositionChar() == "S"){
                    int rent = S.getRentHomePrice();
                    P3.decrescenteBudgetRent(rent); 
                    P1.increaseBudgetRent(rent);
                    P3.logOutput("Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 1 per pernottamento nella casella " +board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 1 per pernottamento nella casella " +board[i][j]<<"\n";
                }else if(player.getPositionChar() == "L"){
                    int rent = L.getRentHomePrice();
                    P3.decrescenteBudgetRent(rent); 
                    P1.increaseBudgetRent(rent);
                    P3.logOutput("Giocatore " + player.getChar() + " ha pagato 7 fiorini a giocatore 1 per pernottamento nella casella " +board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 7 fiorini a giocatore 1 per pernottamento nella casella " +board[i][j]<<"\n";
                }

            }else if(board[i][j].find('^') != board[i][j].npos){
                 if(player.getPositionChar() == "E"){
                    int rent = E.getRentHotelPrice();
                    P3.decrescenteBudgetRent(rent); 
                    P1.increaseBudgetRent(rent);
                    P3.logOutput("Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 1 per pernottamento nella casella " +board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 1 per pernottamento nella casella " +board[i][j]<<"\n";
                }else if(player.getPositionChar() == "S"){
                    int rent = S.getRentHotelPrice();
                    P3.decrescenteBudgetRent(rent); 
                    P1.increaseBudgetRent(rent);
                    P3.logOutput("Giocatore " + player.getChar() + " ha pagato 8 fiorini a giocatore 1 per pernottamento nella casella " +board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 8 fiorini a giocatore 1 per pernottamento nella casella " +board[i][j]<<"\n";
                }else if(player.getPositionChar() == "L"){
                    int rent = L.getRentHotelPrice();
                    P3.decrescenteBudgetRent(rent); 
                    P1.increaseBudgetRent(rent);
                    P3.logOutput("Giocatore " + player.getChar() + " ha pagato 14 fiorini a giocatore 1 per pernottamento nella casella " +board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 14 fiorini a giocatore 1 per pernottamento nella casella " +board[i][j]<<"\n";
                }
            }
        }
        if(std::find(otherProperties["2"].begin(), otherProperties["2"].end(), player.getPosition()) != otherProperties["2"].end()){
            if(board[i][j].find('*') != board[i][j].npos){
                if(player.getPositionChar() == "E"){
                    int rent = E.getRentHomePrice();
                    P3.decrescenteBudgetRent(rent); 
                    P2.increaseBudgetRent(rent);
                    P3.logOutput("Giocatore " + player.getChar() + " ha pagato 2 fiorini a giocatore 2 per pernottamento nella casella " +board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 2 fiorini a giocatore 2 per pernottamento nella casella " +board[i][j]<<"\n";
                }else if(player.getPositionChar() == "S"){
                    int rent = S.getRentHomePrice();
                    P3.decrescenteBudgetRent(rent); 
                    P2.increaseBudgetRent(rent);
                   P3.logOutput("Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 2 per pernottamento nella casella " +board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 2 per pernottamento nella casella " +board[i][j]<< "\n";
                }else if(player.getPositionChar() == "L"){
                    int rent = L.getRentHomePrice();
                    P3.decrescenteBudgetRent(rent); 
                    P2.increaseBudgetRent(rent);
                    P3.logOutput("Giocatore " + player.getChar() + " ha pagato 7 fiorini a giocatore 2 per pernottamento nella casella " +board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 7 fiorini a giocatore 2 per pernottamento nella casella "+ board[i][j]<< "\n";
                }
                
            }else if(board[i][j].find('^') != board[i][j].npos){
                 if(player.getPositionChar() == "E"){
                    int rent = E.getRentHotelPrice();
                    P3.decrescenteBudgetRent(rent); 
                    P2.increaseBudgetRent(rent);
                    P3.logOutput("Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 2 per pernottamento nella casella "+ board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 2 per pernottamento nella casella " +board[i][j]<< "\n";
                }else if(player.getPositionChar() == "S"){
                    int rent = S.getRentHotelPrice();
                    P3.decrescenteBudgetRent(rent); 
                    P2.increaseBudgetRent(rent);
                    P3.logOutput("Giocatore " + player.getChar() + " ha pagato 8 fiorini a giocatore 2 per pernottamento nella casella " +board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 8 fiorini a giocatore 2 per pernottamento nella casella "+board[i][j]<< "\n";
                }else if(player.getPositionChar() == "L"){
                    int rent = L.getRentHotelPrice();
                    P3.decrescenteBudgetRent(rent); 
                    P2.increaseBudgetRent(rent);
                    P3.logOutput("Giocatore " + player.getChar() + " ha pagato 14 fiorini a giocatore 2 per pernottamento nella casella " +board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 14 fiorini a giocatore 2 per pernottamento nella casella " +board[i][j]<< "\n";
                }
            }
        }
         if(std::find(otherProperties["4"].begin(), otherProperties["4"].end(), player.getPosition()) != otherProperties["4"].end()){
            if(board[i][j].find('*') != board[i][j].npos){
                if(player.getPositionChar() == "E"){
                    int rent = E.getRentHomePrice();
                    P3.decrescenteBudgetRent(rent); 
                    P4.increaseBudgetRent(rent);
                    P3.logOutput("Giocatore " + player.getChar() + " ha pagato 2 fiorini a giocatore 4 per pernottamento nella casella " +board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 2 fiorini a giocatore 4 per pernottamento nella casella " +board[i][j]<< "\n";
                }else if(player.getPositionChar() == "S"){
                    int rent = S.getRentHomePrice();
                    P3.decrescenteBudgetRent(rent); 
                    P4.increaseBudgetRent(rent);
                    P3.logOutput("Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 4 per pernottamento nella casella "+ board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 4 per pernottamento nella casella "+ board[i][j]<< "\n";
                }else if(player.getPositionChar() == "L"){
                    int rent = L.getRentHomePrice();
                    P3.decrescenteBudgetRent(rent); 
                    P4.increaseBudgetRent(rent);
                    P3.logOutput("Giocatore " + player.getChar() + " ha pagato 7 fiorini a giocatore 4 per pernottamento nella casella "+ board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 7 fiorini a giocatore 4 per pernottamento nella casella " +board[i][j]<< "\n";
                }

            }else if(board[i][j].find('^') != board[i][j].npos){
                 if(player.getPositionChar() == "E"){
                    int rent = E.getRentHotelPrice();
                    P3.decrescenteBudgetRent(rent); 
                    P4.increaseBudgetRent(rent);
                    P3.logOutput("Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 4 per pernottamento nella casella "+ board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 4 per pernottamento nella casella "+ board[i][j]<< "\n";
                }else if(player.getPositionChar() == "S"){
                    int rent = S.getRentHotelPrice();
                    P3.decrescenteBudgetRent(rent); 
                    P4.increaseBudgetRent(rent);
                    P3.logOutput("Giocatore " + player.getChar() + " ha pagato 8 fiorini a giocatore 4 per pernottamento nella casella " +board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 8 fiorini a giocatore 4 per pernottamento nella casella " +board[i][j]<< "\n";
                }else if(player.getPositionChar() == "L"){
                    int rent = L.getRentHotelPrice();
                    P3.decrescenteBudgetRent(rent); 
                    P4.increaseBudgetRent(rent);
                    P3.logOutput("Giocatore " + player.getChar() + " ha pagato 14 fiorini a giocatore 4 per pernottamento nella casella "+ board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 14 fiorini a giocatore 4 per pernottamento nella casella "+ board[i][j]<< "\n";
                }
            }
        }
        P3.checkIfBankrupt();

    }else{

        std::vector<Position> tmp;

        for(auto& it : P1.getProperty())
            tmp.push_back(it);
        otherProperties["1"] = tmp;

        tmp.clear();

        for(auto& it : P2.getProperty())
            tmp.push_back(it);

        otherProperties["2"] = tmp;
        tmp.clear();

        for(auto& it : P3.getProperty())
            tmp.push_back(it);

        otherProperties["3"] = tmp;


         if(std::find(otherProperties["1"].begin(), otherProperties["1"].end(), player.getPosition()) != otherProperties["1"].end()){
            if(board[i][j].find('*') != board[i][j].npos){
                if(player.getPositionChar() == "E"){
                    int rent = E.getRentHomePrice();
                    P4.decrescenteBudgetRent(rent); 
                    P1.increaseBudgetRent(rent);
                    P4.logOutput("Giocatore " + player.getChar() + " ha pagato 2 fiorini a giocatore 1 per pernottamento nella casella " +board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 2 fiorini a giocatore 1 per pernottamento nella casella " +board[i][j]<<"\n";
                }else if(player.getPositionChar() == "S"){
                    int rent = S.getRentHomePrice();
                    P4.decrescenteBudgetRent(rent); 
                    P1.increaseBudgetRent(rent);
                    P4.logOutput("Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 1 per pernottamento nella casella " +board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 1 per pernottamento nella casella " +board[i][j]<<"\n";
                }else if(player.getPositionChar() == "L"){
                    int rent = L.getRentHomePrice();
                    P4.decrescenteBudgetRent(rent); 
                    P1.increaseBudgetRent(rent);
                     P4.logOutput("Giocatore " + player.getChar() + " ha pagato 7 fiorini a giocatore 1 per pernottamento nella casella "+ board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 7 fiorini a giocatore 1 per pernottamento nella casella " +board[i][j]<<"\n";
                }

            }else if(board[i][j].find('^') != board[i][j].npos){
                 if(player.getPositionChar() == "E"){
                    int rent = E.getRentHotelPrice();
                    P4.decrescenteBudgetRent(rent); 
                    P1.increaseBudgetRent(rent);
                    P4.logOutput("Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 1 per pernottamento nella casella " +board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 1 per pernottamento nella casella " +board[i][j]<<"\n";
                }else if(player.getPositionChar() == "S"){
                    int rent = S.getRentHotelPrice();
                    P4.decrescenteBudgetRent(rent); 
                    P1.increaseBudgetRent(rent);
                    P4.logOutput("Giocatore " + player.getChar() + " ha pagato 8 fiorini a giocatore 1 per pernottamento nella casella " +board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 8 fiorini a giocatore 1 per pernottamento nella casella " +board[i][j]<<"\n";
                }else if(player.getPositionChar() == "L"){
                    int rent = L.getRentHotelPrice();
                    P4.decrescenteBudgetRent(rent); 
                    P1.increaseBudgetRent(rent);
                    P4.logOutput("Giocatore " + player.getChar() + " ha pagato 14 fiorini a giocatore 1 per pernottamento nella casella " +board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 14 fiorini a giocatore 1 per pernottamento nella casella " +board[i][j]<<"\n";
                }
            }
        }
        if(std::find(otherProperties["2"].begin(), otherProperties["2"].end(), player.getPosition()) != otherProperties["2"].end()){
            if(board[i][j].find('*') != board[i][j].npos){
                if(player.getPositionChar() == "E"){
                    int rent = E.getRentHomePrice();
                    P4.decrescenteBudgetRent(rent); 
                    P2.increaseBudgetRent(rent);
                    P4.logOutput("Giocatore " + player.getChar() + " ha pagato 2 fiorini a giocatore 2 per pernottamento nella casella " +board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 2 fiorini a giocatore 2 per pernottamento nella casella " +board[i][j]<<"\n";
                }else if(player.getPositionChar() == "S"){
                    int rent = S.getRentHomePrice();
                    P4.decrescenteBudgetRent(rent); 
                    P2.increaseBudgetRent(rent);
                   P4.logOutput("Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 2 per pernottamento nella casella " +board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 2 per pernottamento nella casella " +board[i][j]<< "\n";
                }else if(player.getPositionChar() == "L"){
                    int rent = L.getRentHomePrice();
                    P4.decrescenteBudgetRent(rent); 
                    P2.increaseBudgetRent(rent);
                    P4.logOutput("Giocatore " + player.getChar() + " ha pagato 7 fiorini a giocatore 2 per pernottamento nella casella " +board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 7 fiorini a giocatore 2 per pernottamento nella casella " +board[i][j]<< "\n";
                }
                
            }else if(board[i][j].find('^') != board[i][j].npos){
                 if(player.getPositionChar() == "E"){
                    int rent = E.getRentHotelPrice();
                    P4.decrescenteBudgetRent(rent); 
                    P2.increaseBudgetRent(rent);
                    P4.logOutput("Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 2 per pernottamento nella casella " +board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 2 per pernottamento nella casella " +board[i][j]<< "\n";
                }else if(player.getPositionChar() == "S"){
                    int rent = S.getRentHotelPrice();
                    P4.decrescenteBudgetRent(rent); 
                    P2.increaseBudgetRent(rent);
                    P4.logOutput("Giocatore " + player.getChar() + " ha pagato 8 fiorini a giocatore 2 per pernottamento nella casella " +board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 8 fiorini a giocatore 2 per pernottamento nella casella " +board[i][j]<< "\n";
                }else if(player.getPositionChar() == "L"){
                    int rent = L.getRentHotelPrice();
                    P4.decrescenteBudgetRent(rent); 
                    P2.increaseBudgetRent(rent);
                    P4.logOutput("Giocatore " + player.getChar() + " ha pagato 14 fiorini a giocatore 2 per pernottamento nella casella " +board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 14 fiorini a giocatore 2 per pernottamento nella casella " +board[i][j]<< "\n";
                }
            }
        }
         if(std::find(otherProperties["3"].begin(), otherProperties["3"].end(), player.getPosition()) != otherProperties["3"].end()){
            if(board[i][j].find('*') != board[i][j].npos){
                if(player.getPositionChar() == "E"){
                    int rent = E.getRentHomePrice();
                    P4.decrescenteBudgetRent(rent); 
                    P3.increaseBudgetRent(rent);
                    P4.logOutput("Giocatore " + player.getChar() + " ha pagato 2 fiorini a giocatore 3 per pernottamento nella casella " +board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 2 fiorini a giocatore 3 per pernottamento nella casella " +board[i][j]<< "\n";
                }else if(player.getPositionChar() == "S"){
                    int rent = S.getRentHomePrice();
                    P4.decrescenteBudgetRent(rent); 
                    P3.increaseBudgetRent(rent);
                    P4.logOutput("Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 3 per pernottamento nella casella " +board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 3 per pernottamento nella casella " +board[i][j]<< "\n";
                }else if(player.getPositionChar() == "L"){
                    int rent = L.getRentHomePrice();
                    P4.decrescenteBudgetRent(rent); 
                    P3.increaseBudgetRent(rent);
                    P4.logOutput("Giocatore " + player.getChar() + " ha pagato 7 fiorini a giocatore 3 per pernottamento nella casella " +board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 7 fiorini a giocatore 3 per pernottamento nella casella " +board[i][j]<< "\n";
                }

            }else if(board[i][j].find('^') != board[i][j].npos){
                 if(player.getPositionChar() == "E"){
                    int rent = E.getRentHotelPrice();
                    P4.decrescenteBudgetRent(rent); 
                    P3.increaseBudgetRent(rent);
                     P4.logOutput("Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 3 per pernottamento nella casella " +board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 3 per pernottamento nella casella "+ board[i][j]<< "\n";
                }else if(player.getPositionChar() == "S"){
                    int rent = S.getRentHotelPrice();
                    P4.decrescenteBudgetRent(rent); 
                    P3.increaseBudgetRent(rent);
                    P4.logOutput("Giocatore " + player.getChar() + " ha pagato 8 fiorini a giocatore 3 per pernottamento nella casella "+ board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 8 fiorini a giocatore 3 per pernottamento nella casella " +board[i][j]<< "\n";
                }else if(player.getPositionChar() == "L"){
                    int rent = L.getRentHotelPrice();
                    P4.decrescenteBudgetRent(rent); 
                    P3.increaseBudgetRent(rent);
                    P4.logOutput("Giocatore " + player.getChar() + " ha pagato 14 fiorini a giocatore 3 per pernottamento nella casella "+ board[i][j]);
                    std::cout << "Giocatore " + player.getChar() + " ha pagato 14 fiorini a giocatore 3 per pernottamento nella casella "+ board[i][j]<< "\n";
                }
            }
        }
        
    }
    P4.checkIfBankrupt();










}


void rentHumanPlayer(std::string board[ROW][COL]){

    std::map<std::string, std::vector<Position>> otherProperties;
    int i = HP.getPositionI();
    int j = HP.getPositionJ();
     std::vector<Position> tmp;

        for(auto& it : P2.getProperty())
            tmp.push_back(it);
        otherProperties["2"] = tmp;

        tmp.clear();

        for(auto& it : P3.getProperty())
            tmp.push_back(it);

        otherProperties["3"] = tmp;
        tmp.clear();

        for(auto& it : P4.getProperty())
            tmp.push_back(it);

        otherProperties["4"] = tmp;
        

        if(std::find(otherProperties["2"].begin(), otherProperties["2"].end(), HP.getPosition()) != otherProperties["2"].end()){
            if(board[i][j].find('*') != board[i][j].npos){
                if(HP.getPositionChar() == "E"){
                    int rent = E.getRentHomePrice();
                    HP.decrescenteBudgetRent(rent); 
                    P2.increaseBudgetRent(rent);
                    HP.logOutput("Giocatore " + HP.getChar() + " ha pagato 2 fiorini a giocatore 2 per pernottamento nella casella "+ board[i][j]);
                    std::cout << "Giocatore " + HP.getChar() + " ha pagato 2 fiorini a giocatore 2 per pernottamento nella casella " +board[i][j]<<"\n";
                }else if(HP.getPositionChar() == "S"){
                    int rent = S.getRentHomePrice();
                    HP.decrescenteBudgetRent(rent); 
                    P2.increaseBudgetRent(rent);
                   HP.logOutput("Giocatore " + HP.getChar() + " ha pagato 4 fiorini a giocatore 2 per pernottamento nella casella " + board[i][j]);
                    std::cout << "Giocatore " + HP.getChar() + " ha pagato 4 fiorini a giocatore 2 per pernottamento nella casella " +board[i][j]<<"\n";
                }else if(HP.getPositionChar() == "L"){
                    int rent = L.getRentHomePrice();
                    HP.decrescenteBudgetRent(rent); 
                    P2.increaseBudgetRent(rent);
                    HP.logOutput("Giocatore " + HP.getChar() + " ha pagato 7 fiorini a giocatore 2 per pernottamento nella casella " + board[i][j]);
                    std::cout << "Giocatore " + HP.getChar() + " ha pagato 7 fiorini a giocatore 2 per pernottamento nella casella "+ board[i][j]<<"\n";
                }
                
            }else if(board[i][j].find('^') != board[i][j].npos){
                 if(HP.getPositionChar() == "E"){
                    int rent = E.getRentHotelPrice();
                    HP.decrescenteBudgetRent(rent); 
                    P2.increaseBudgetRent(rent);
                    HP.logOutput("Giocatore " + HP.getChar() + " ha pagato 4 fiorini a giocatore 2 per pernottamento nella casella " + board[i][j]);
                    std::cout << "Giocatore " + HP.getChar() + " ha pagato 4 fiorini a giocatore 2 per pernottamento nella casella " +board[i][j]<<"\n";
                }else if(HP.getPositionChar() == "S"){
                    int rent = S.getRentHotelPrice();
                    HP.decrescenteBudgetRent(rent); 
                    P2.increaseBudgetRent(rent);
                    HP.logOutput("Giocatore " + HP.getChar() + " ha pagato 8 fiorini a giocatore 2 per pernottamento nella casella " + board[i][j]);
                    std::cout << "Giocatore " + HP.getChar() + " ha pagato 8 fiorini a giocatore 2 per pernottamento nella casella " +board[i][j]<<"\n";
                }else if(HP.getPositionChar() == "L"){
                    int rent = L.getRentHotelPrice();
                    HP.decrescenteBudgetRent(rent); 
                    P2.increaseBudgetRent(rent);
                    HP.logOutput("Giocatore " + HP.getChar() + " ha pagato 14 fiorini a giocatore 2 per pernottamento nella casella " + board[i][j]);
                    std::cout << "Giocatore " + HP.getChar() + " ha pagato 14 fiorini a giocatore 2 per pernottamento nella casella " +board[i][j]<<"\n";
                }
            }
        }
        if(std::find(otherProperties["3"].begin(), otherProperties["3"].end(), HP.getPosition()) != otherProperties["3"].end()){
            if(board[i][j].find('*') != board[i][j].npos){
                if(HP.getPositionChar() == "E"){
                    int rent = E.getRentHomePrice();
                    HP.decrescenteBudgetRent(rent); 
                    P3.increaseBudgetRent(rent);
                    HP.logOutput("Giocatore " + HP.getChar() + " ha pagato 2 fiorini a giocatore 3 per pernottamento nella casella " +board[i][j]);
                    std::cout << "Giocatore " + HP.getChar() + " ha pagato 2 fiorini a giocatore 3 per pernottamento nella casella " +board[i][j]<<"\n";              
                }else if(HP.getPositionChar() == "S"){
                    int rent = S.getRentHomePrice();
                    HP.decrescenteBudgetRent(rent); 
                    P3.increaseBudgetRent(rent);
                    HP.logOutput("Giocatore " + HP.getChar() + " ha pagato 4 fiorini a giocatore 3 per pernottamento nella casella " +board[i][j]);
                    std::cout << "Giocatore " + HP.getChar() + " ha pagato 4 fiorini a giocatore 3 per pernottamento nella casella "+board[i][j]<<"\n";
                }else if(HP.getPositionChar() == "L"){
                    int rent = L.getRentHomePrice();
                    HP.decrescenteBudgetRent(rent); 
                    P3.increaseBudgetRent(rent);
                    HP.logOutput("Giocatore " + HP.getChar() + " ha pagato 7 fiorini a giocatore 3 per pernottamento nella casella "+board[i][j]);
                    std::cout << "Giocatore " + HP.getChar() + " ha pagato 7 fiorini a giocatore 3 per pernottamento nella casella " +board[i][j]<<"\n";
                }

            }else if(board[i][j].find('^') != board[i][j].npos){
                 if(HP.getPositionChar() == "E"){
                    int rent = E.getRentHotelPrice();
                    HP.decrescenteBudgetRent(rent); 
                    P3.increaseBudgetRent(rent);
                    HP.logOutput("Giocatore " + HP.getChar() + " ha pagato 4 fiorini a giocatore 3 per pernottamento nella casella " +board[i][j]);
                    std::cout << "Giocatore " + HP.getChar() + " ha pagato 4 fiorini a giocatore 3 per pernottamento nella casella " +board[i][j]<<"\n";
                }else if(HP.getPositionChar() == "S"){
                    int rent = S.getRentHotelPrice();
                    HP.decrescenteBudgetRent(rent); 
                    P3.increaseBudgetRent(rent);
                    HP.logOutput("Giocatore " + HP.getChar() + " ha pagato 8 fiorini a giocatore 3 per pernottamento nella casella " +board[i][j]);
                    std::cout << "Giocatore " + HP.getChar() + " ha pagato 8 fiorini a giocatore 3 per pernottamento nella casella " +board[i][j]<<"\n";
                }else if(HP.getPositionChar() == "L"){
                    int rent = L.getRentHotelPrice();
                    HP.decrescenteBudgetRent(rent); 
                    P3.increaseBudgetRent(rent);
                    HP.logOutput("Giocatore " + HP.getChar() + " ha pagato 14 fiorini a giocatore 3 per pernottamento nella casella "+ board[i][j]);
                    std::cout << "Giocatore " + HP.getChar() + " ha pagato 14 fiorini a giocatore 3 per pernottamento nella casella "+board[i][j]<<"\n";
                }
            }
        }
         if(std::find(otherProperties["4"].begin(), otherProperties["4"].end(), HP.getPosition()) != otherProperties["4"].end()){
            if(board[i][j].find('*') != board[i][j].npos){
                if(HP.getPositionChar() == "E"){
                    int rent = E.getRentHomePrice();
                    HP.decrescenteBudgetRent(rent); 
                    P4.increaseBudgetRent(rent);
                    HP.logOutput("Giocatore " + HP.getChar() + " ha pagato 2 fiorini a giocatore 4 per pernottamento nella casella " +board[i][j]);
                    std::cout << "Giocatore " + HP.getChar() + " ha pagato 2 fiorini a giocatore 4 per pernottamento nella casella "+board[i][j]<<"\n";
                }else if(HP.getPositionChar() == "S"){
                    int rent = S.getRentHomePrice();
                    HP.decrescenteBudgetRent(rent); 
                    P4.increaseBudgetRent(rent);
                    HP.logOutput("Giocatore " + HP.getChar() + " ha pagato 4 fiorini a giocatore 4 per pernottamento nella casella " +board[i][j]);
                    std::cout << "Giocatore " + HP.getChar() + " ha pagato 4 fiorini a giocatore 4 per pernottamento nella casella " +board[i][j]<<"\n";
                }else if(HP.getPositionChar() == "L"){
                    int rent = L.getRentHomePrice();
                    HP.decrescenteBudgetRent(rent); 
                    P4.increaseBudgetRent(rent);
                    HP.logOutput("Giocatore " + HP.getChar() + " ha pagato 7 fiorini a giocatore 4 per pernottamento nella casella "+ board[i][j]);
                    std::cout << "Giocatore " + HP.getChar() + " ha pagato 7 fiorini a giocatore 4 per pernottamento nella casella "+board[i][j]<<"\n";
                }

            }else if(board[i][j].find('^') != board[i][j].npos){
                 if(HP.getPositionChar() == "E"){
                    int rent = E.getRentHotelPrice();
                    HP.decrescenteBudgetRent(rent); 
                    P4.increaseBudgetRent(rent);
                    HP.logOutput("Giocatore " + HP.getChar() + " ha pagato 4 fiorini a giocatore 4 per pernottamento nella casella " + board[i][j]);
                    std::cout << "Giocatore " + HP.getChar() + " ha pagato 4 fiorini a giocatore 4 per pernottamento nella casella " +board[i][j]<< "\n";
                }else if(HP.getPositionChar() == "S"){
                    int rent = S.getRentHotelPrice();
                    HP.decrescenteBudgetRent(rent); 
                    P4.increaseBudgetRent(rent);
                    HP.logOutput("Giocatore " + HP.getChar() + " ha pagato 8 fiorini a giocatore 4 per pernottamento nella casella "+ board[i][j]);
                    std::cout << "Giocatore " + HP.getChar() + " ha pagato 8 fiorini a giocatore 4 per pernottamento nella casella "+board[i][j]<<"\n";
                }else if(HP.getPositionChar() == "L"){
                    int rent = L.getRentHotelPrice();
                    HP.decrescenteBudgetRent(rent); 
                    P4.increaseBudgetRent(rent);
                    HP.logOutput("Giocatore " + HP.getChar() + " ha pagato 14 fiorini a giocatore 4 per pernottamento nella casella "+ board[i][j]);
                    std::cout << "Giocatore " + HP.getChar() + " ha pagato 14 fiorini a giocatore 4 per pernottamento nella casella "+board[i][j]<<"\n";
                }
            }
        }
        HP.checkIfBankrupt();
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


#include "scoreBoard.hpp"

#endif

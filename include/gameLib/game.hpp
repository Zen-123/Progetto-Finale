#ifndef GAME_HPP
#define GAME_HPP

bool cmp(std::pair<std::string, int>& a, std::pair<std::string, int>& b){  //funzione che compara i valori interi tra due pair per ordinamento da maggiore a minore
    return a.second  > b.second;
}

void checkDiceNumber(std::map<std::string, int>& mp){
    std::string tmp[4] = {"1", "2", "3", "4"};
    bool check = false;

    for(int i = 0; i<TURN; i++){
        for(int j = 0; j<TURN; j++){
            check = false;
            if(i != j){
                if((mp.at(tmp[i]) == mp.at(tmp[j]) )){
                    while(check == false){  //rilancio dadi quando due giocatori ottengono lo stesso valore
                        if(mp.at(tmp[j]) == mp.at(tmp[i]))
                        {
                            mp[tmp[i]] = P1.throwDice();
                            mp[tmp[j]] = P2.throwDice();
                            check = false;
                        }
                        if(mp.at(tmp[i]) != mp.at(tmp[j])){
                            check = true;
                        }

                        if(mp.at("1") == mp.at("2")){
                            mp["1"] = P1.throwDice();
                            mp["2"] = P2.throwDice();
                            check = false;
                        }

                        if( mp.at("1") == mp.at("3")){
                            mp["1"] = P1.throwDice();
                            mp["3"] = P2.throwDice();
                            check = false;
                        }

                         if( mp.at("2") == mp.at("3")){
                            mp["1"] = P1.throwDice();
                            mp["3"] = P2.throwDice();
                            check = false;
                        }
                        
                    }
                }
            }
            
        }
    }

    
}

void setTurn(std::string order[4], bool gameType){  

    std::map<std::string, int> mp;  //mappa che crea entry (string, int) dove la string identifica il player, int il valore di dado lanciato
    
    bool check = false;
    srand(time(NULL));

    if(gameType)
        mp["1"] = HP.throwDice();
    else
        mp["1"] = P1.throwDice();

    
    mp["2"] = P2.throwDice();
    mp["3"] = P3.throwDice();
    mp["4"] = P4.throwDice();
    
    // FUNZIONE CONTROLLA SE I VALORI SONO TUTTI DIVERSI OPPURE NO
    checkDiceNumber(mp);


    // for(auto it = mp.cbegin(); it != mp.cend(); ++it)  //test stampa entry mappa con uso di std::iterator
    // {
    //     std::cout << it->first << " " << it->second <<"\n";
    // }


    std::vector<std::pair<std::string, int> > A;  //vettore di supporto di tipo pair (string, int)

    for(auto& it : mp)
        A.push_back(it);


    std::sort(A.begin(), A.end(), cmp); //utilizzo di std::sort con funzione ausiliaria cmp per ordinare in modo decrescente i valori int della map

    int i=0;

    for(auto it = A.cbegin(); it != A.cend(); ++it)
        order[i++] = it->first;     //salvataggio delle posizioni dei giocatori in una string  passata come parametro da funzione func
    


}

void printScoreboard(){
 
    for(int i=0; i<ROW; i++){
        for(int j=0; j<COL; j++){
            if(i==1 && j>0 || i == ROW-1 && j>0 || j==1  && i>0 || j == COL-1 && i>1)
                std::cout<<"|"<<std::setw(5) <<board[i][j]<<"|"<<"\t";
            else
                std::cout<<"  "<<board[i][j]<<"  "<<"\t";


        }
        std::cout<<"\n";
    }
}

void removePrevChar(Player& player){
     for(int i=0; i<ROW; i++){
        for(int j=0; j<COL; j++){
            if(i==1 && j>0 || i == ROW-1 && j>0 || j==1  && i>0 || j == COL-1 && i>1)
                if(board[i][j].find(player.getChar()) != board[i][j].npos ){
                    board[i][j].erase(board[i][j].find(player.getChar()), player.getChar().length());
                }
        }
    }
    std::cout<<"\n\n";
}

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

     for(auto& it: tmpVec){
        if(pos == 1){
            std::cout<<"-Giocatore "<<it.first<<" ha vinto la partita\n";
            std::cout<<pos<<"° Giocatore n."<<it.first<<"  "<<it.second<<"\n";
            P1.logOutput("-Giocatore " + it.first + " ha vinto la partita\n");
        }else
            std::cout<<pos<<"° Giocatore n."<<it.first<<"  "<<it.second<<"\n";
        
        pos++;
     }
       
     

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

void setScoreboard(){


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
        board[i][0] = initRows[i];

    for(int i =2; i<ROW-1; i++){
        for(int j =2; j<COL-1; j++){
            board[i][j] = ' ';
        }
    }
    
    firstRow();
    lastRow();
    firstCol();
    lastCol();

    
}

void setPositionPlayer(Player& player){
    int diffCol, diffRow, move, n, i ,j;
    bool checkFirstSquare = false;  //variabile per controllo se il giocatore passa per casella P
    move = player.throwDice(); 
    std::cout<<"-Giocatore " + player.getChar() + " ha tirato i dati ottenendo un valore di "<<move<<"\n";
    player.logOutput("-Giocatore " + player.getChar() + " ha tirato i dati ottenendo un valore di " + std::to_string(move) + "\n");

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

    std::cout<<"-Giocatore " + player.getChar() + " è arrivato alla casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
    player.logOutput("-Giocatore " + player.getChar() + " è arrivato alla casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+ "\n");

    if(checkFirstSquare){
        std::cout<<"-Giocatore "<<player.getChar()<<" è passato dal via e ha ritirato 20 fiorini.\n";
        player.logOutput("-Giocatore " + player.getChar() + " è passato dal via e ha ritirato 20 fiorini.\n");
    }
}

bool rentComputerPlayer(Player& player){
    

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
        tmp.clear();

        if(std::find(otherProperties["2"].begin(), otherProperties["2"].end(), player.getPosition()) != otherProperties["2"].end()){
            if(board[i][j].find("*") != board[i][j].npos){
                if(player.getPositionChar() == "E"){
                    int rent = E.getRentHomePrice();
                    P1.decrescenteBudgetRent(rent); 
                    P2.increaseBudgetRent(rent);
                    P1.logOutput("-Giocatore " + player.getChar() + " ha pagato 2 fiorini a giocatore 2 per pernottamento nella casella "+ player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 2 fiorini a giocatore 2 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                    return true;
                }else if(player.getPositionChar() == "S"){
                    int rent = S.getRentHomePrice();
                    P1.decrescenteBudgetRent(rent); 
                    P2.increaseBudgetRent(rent);
                   P1.logOutput("-Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 2 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout <<"-Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 2 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                    return true;
                }else if(player.getPositionChar() == "L"){
                    int rent = L.getRentHomePrice();
                    P1.decrescenteBudgetRent(rent); 
                    P2.increaseBudgetRent(rent);
                    P1.logOutput("-Giocatore " + player.getChar() + " ha pagato 7 fiorini a giocatore 2 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 7 fiorini a giocatore 2 per pernottamento nella casella "+ player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                    return true;
                }
            }else if(board[i][j].find('^') != board[i][j].npos){
                 if(player.getPositionChar() == "E"){
                    int rent = E.getRentHotelPrice();
                    P1.decrescenteBudgetRent(rent); 
                    P2.increaseBudgetRent(rent);
                    P1.logOutput("-Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 2 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 2 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                    return true;
                }else if(player.getPositionChar() == "S"){
                    int rent = S.getRentHotelPrice();
                    P1.decrescenteBudgetRent(rent); 
                    P2.increaseBudgetRent(rent);
                    P1.logOutput("-Giocatore " + player.getChar() + " ha pagato 8 fiorini a giocatore 2 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 8 fiorini a giocatore 2 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                    return true;
                }else if(player.getPositionChar() == "L"){
                    int rent = L.getRentHotelPrice();
                    P1.decrescenteBudgetRent(rent); 
                    P2.increaseBudgetRent(rent);
                    P1.logOutput("-Giocatore " + player.getChar() + " ha pagato 14 fiorini a giocatore 2 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 14 fiorini a giocatore 2 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                    return true;
                }
            }else{
                return true;
            }
        }
        if(std::find(otherProperties["3"].begin(), otherProperties["3"].end(), player.getPosition()) != otherProperties["3"].end()){
            if(board[i][j].find('*') != board[i][j].npos){
                if(player.getPositionChar() == "E"){
                    int rent = E.getRentHomePrice();
                    P1.decrescenteBudgetRent(rent); 
                    P3.increaseBudgetRent(rent);
                    P1.logOutput("-Giocatore " + player.getChar() + " ha pagato 2 fiorini a giocatore 3 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 2 fiorini a giocatore 3 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";              
                return true;
                }else if(player.getPositionChar() == "S"){
                    int rent = S.getRentHomePrice();
                    P1.decrescenteBudgetRent(rent); 
                    P3.increaseBudgetRent(rent);
                    P1.logOutput("-Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 3 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 3 per pernottamento nella casella "+ player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                return true;
                }else if(player.getPositionChar() == "L"){
                    int rent = L.getRentHomePrice();
                    P1.decrescenteBudgetRent(rent); 
                    P3.increaseBudgetRent(rent);
                    P1.logOutput("-Giocatore " + player.getChar() + " ha pagato 7 fiorini a giocatore 3 per pernottamento nella casella "+ player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 7 fiorini a giocatore 3 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                return true;
                }
            }else if(board[i][j].find('^') != board[i][j].npos){
                 if(player.getPositionChar() == "E"){
                    int rent = E.getRentHotelPrice();
                    P1.decrescenteBudgetRent(rent); 
                    P3.increaseBudgetRent(rent);
                    P1.logOutput("-Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 3 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 3 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                return true;
                }else if(player.getPositionChar() == "S"){
                    int rent = S.getRentHotelPrice();
                    P1.decrescenteBudgetRent(rent); 
                    P3.increaseBudgetRent(rent);
                    P1.logOutput("-Giocatore " + player.getChar() + " ha pagato 8 fiorini a giocatore 3 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 8 fiorini a giocatore 3 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                return true;
                }else if(player.getPositionChar() == "L"){
                    int rent = L.getRentHotelPrice();
                    P1.decrescenteBudgetRent(rent); 
                    P3.increaseBudgetRent(rent);
                    P1.logOutput("-Giocatore " + player.getChar() + " ha pagato 14 fiorini a giocatore 3 per pernottamento nella casella "+ board[i][j]);
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 14 fiorini a giocatore 3 per pernottamento nella casella "+ player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                return true;
                }
            }else{
                return true;
            }

        }
         if(std::find(otherProperties["4"].begin(), otherProperties["4"].end(), player.getPosition()) != otherProperties["4"].end()){
            if(board[i][j].find('*') != board[i][j].npos){
                if(player.getPositionChar() == "E"){
                    int rent = E.getRentHomePrice();
                    P1.decrescenteBudgetRent(rent); 
                    P4.increaseBudgetRent(rent);
                    P1.logOutput("-Giocatore " + player.getChar() + " ha pagato 2 fiorini a giocatore 4 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 2 fiorini a giocatore 4 per pernottamento nella casella "+ player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                    return true;
                }else if(player.getPositionChar() == "S"){
                    int rent = S.getRentHomePrice();
                    P1.decrescenteBudgetRent(rent); 
                    P4.increaseBudgetRent(rent);
                    P1.logOutput("-Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 4 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 4 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                 return true;
                }else if(player.getPositionChar() == "L"){
                    int rent = L.getRentHomePrice();
                    P1.decrescenteBudgetRent(rent); 
                    P4.increaseBudgetRent(rent);
                    P1.logOutput("-Giocatore " + player.getChar() + " ha pagato 7 fiorini a giocatore 4 per pernottamento nella casella " +player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 7 fiorini a giocatore 4 per pernottamento nella casella "+ player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                return true;
                }
            }else if(board[i][j].find('^') != board[i][j].npos){
                 if(player.getPositionChar() == "E"){
                    int rent = E.getRentHotelPrice();
                    P1.decrescenteBudgetRent(rent); 
                    P4.increaseBudgetRent(rent);
                    P1.logOutput("-Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 4 per pernottamento nella casella " +player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 4 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";;
                    return true;
                }else if(player.getPositionChar() == "S"){
                    int rent = S.getRentHotelPrice();
                    P1.decrescenteBudgetRent(rent); 
                    P4.increaseBudgetRent(rent);
                    P1.logOutput("-Giocatore " + player.getChar() + " ha pagato 8 fiorini a giocatore 4 per pernottamento nella casella "+player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 8 fiorini a giocatore 4 per pernottamento nella casella "+ player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                    return true;
                }else if(player.getPositionChar() == "L"){
                    int rent = L.getRentHotelPrice();
                    P1.decrescenteBudgetRent(rent); 
                    P4.increaseBudgetRent(rent);
                    P1.logOutput("-Giocatore " + player.getChar() + " ha pagato 14 fiorini a giocatore 4 per pernottamento nella casella "+player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 14 fiorini a giocatore 4 per pernottamento nella casella "+ player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                return true;
                }
            }else{
                return true;
            }

        }
        return false;

    }
    if(player.getChar() == "2"){

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
        tmp.clear();

         if(std::find(otherProperties["1"].begin(), otherProperties["1"].end(), player.getPosition()) != otherProperties["1"].end()){
            if(board[i][j].find('*') != board[i][j].npos){
                if(player.getPositionChar() == "E"){
                    int rent = E.getRentHomePrice();
                    P2.decrescenteBudgetRent(rent); 
                    P1.increaseBudgetRent(rent);
                    P2.logOutput("-Giocatore " + player.getChar() + " ha pagato 2 fiorini a giocatore 1 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 2 fiorini a giocatore 1 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                    return true;
                }else if(player.getPositionChar() == "S"){
                    int rent = S.getRentHomePrice();
                    P2.decrescenteBudgetRent(rent); 
                    P1.increaseBudgetRent(rent);
                    P2.logOutput("-Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 1 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 1 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                    return true;
                }else if(player.getPositionChar() == "L"){
                    int rent = L.getRentHomePrice();
                    P2.decrescenteBudgetRent(rent); 
                    P1.increaseBudgetRent(rent);
                    P2.logOutput("-Giocatore " + player.getChar() + " ha pagato 7 fiorini a giocatore 1 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 7 fiorini a giocatore 1 per pernottamento nella casella "+ player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                return true;
                }

            }else if(board[i][j].find('^') != board[i][j].npos){
                 if(player.getPositionChar() == "E"){
                    int rent = E.getRentHotelPrice();
                    P2.decrescenteBudgetRent(rent); 
                    P1.increaseBudgetRent(rent);
                    P2.logOutput("-Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 1 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 1 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                return true;
                }else if(player.getPositionChar() == "S"){
                    int rent = S.getRentHotelPrice();
                    P2.decrescenteBudgetRent(rent); 
                    P1.increaseBudgetRent(rent);
                    P2.logOutput("-Giocatore " + player.getChar() + " ha pagato 8 fiorini a giocatore 1 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 8 fiorini a giocatore 1 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                return true;
                }else if(player.getPositionChar() == "L"){
                    int rent = L.getRentHotelPrice();
                    P2.decrescenteBudgetRent(rent); 
                    P1.increaseBudgetRent(rent);
                    P2.logOutput("-Giocatore " + player.getChar() + " ha pagato 14 fiorini a giocatore 1 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 14 fiorini a giocatore 1 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                return true;
                }

            }else{
                return true;
            }


        }

        if(std::find(otherProperties["3"].begin(), otherProperties["3"].end(), player.getPosition()) != otherProperties["3"].end()){
            if(board[i][j].find('*') != board[i][j].npos){
                if(player.getPositionChar() == "E"){
                    int rent = E.getRentHomePrice();
                    P2.decrescenteBudgetRent(rent); 
                    P3.increaseBudgetRent(rent);
                    P2.logOutput("-Giocatore " + player.getChar() + " ha pagato 2 fiorini a giocatore 3 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 2 fiorini a giocatore 3 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                return true;
                }else if(player.getPositionChar() == "S"){
                    int rent = S.getRentHomePrice();
                    P2.decrescenteBudgetRent(rent); 
                    P3.increaseBudgetRent(rent);
                    P2.logOutput("Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 3 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 3 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                return true;
                }else if(player.getPositionChar() == "L"){
                    int rent = L.getRentHomePrice();
                    P2.decrescenteBudgetRent(rent); 
                    P3.increaseBudgetRent(rent);
                    P2.logOutput("-Giocatore " + player.getChar() + " ha pagato 7 fiorini a giocatore 3 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 7 fiorini a giocatore 3 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                return true;
                }

            }else if(board[i][j].find('^') != board[i][j].npos){
                 if(player.getPositionChar() == "E"){
                    int rent = E.getRentHotelPrice();
                    P2.decrescenteBudgetRent(rent); 
                    P3.increaseBudgetRent(rent);
                    P2.logOutput("-Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 3 per pernottamento nella casella "+player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 3 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                return true;
                }else if(player.getPositionChar() == "S"){
                    int rent = S.getRentHotelPrice();
                    P2.decrescenteBudgetRent(rent); 
                    P3.increaseBudgetRent(rent);
                    P2.logOutput("-Giocatore " + player.getChar() + " ha pagato 8 fiorini a giocatore 3 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 8 fiorini a giocatore 3 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                return true;
                }else if(player.getPositionChar() == "L"){
                    int rent = L.getRentHotelPrice();
                    P2.decrescenteBudgetRent(rent); 
                    P3.increaseBudgetRent(rent);
                    P2.logOutput("-Giocatore " + player.getChar() + " ha pagato 14 fiorini a giocatore 3 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 14 fiorini a giocatore 3 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                return true;
                }

            }else{
                return true;
            }



        }
         if(std::find(otherProperties["4"].begin(), otherProperties["4"].end(), player.getPosition()) != otherProperties["4"].end()){
            if(board[i][j].find('*') != board[i][j].npos){
                if(player.getPositionChar() == "E"){
                    int rent = E.getRentHomePrice();
                    P2.decrescenteBudgetRent(rent); 
                    P4.increaseBudgetRent(rent);
                    P2.logOutput("-Giocatore " + player.getChar() + " ha pagato 2 fiorini a giocatore 4 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 2 fiorini a giocatore 4 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                return true;
                }else if(player.getPositionChar() == "S"){
                    int rent = S.getRentHomePrice();
                    P2.decrescenteBudgetRent(rent); 
                    P4.increaseBudgetRent(rent);
                    P2.logOutput("-Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 4 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 4 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                return true;
                }else if(player.getPositionChar() == "L"){
                    int rent = L.getRentHomePrice();
                    P2.decrescenteBudgetRent(rent); 
                    P4.increaseBudgetRent(rent);
                    P2.logOutput("-Giocatore " + player.getChar() + " ha pagato 7 fiorini a giocatore 4 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 7 fiorini a giocatore 4 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                return true;
                }

            }else if(board[i][j].find('^') != board[i][j].npos){
                 if(player.getPositionChar() == "E"){
                    int rent = E.getRentHotelPrice();
                    P2.decrescenteBudgetRent(rent); 
                    P4.increaseBudgetRent(rent);
                    P2.logOutput("-Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 4 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 4 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                    return true;
                }else if(player.getPositionChar() == "S"){
                    int rent = S.getRentHotelPrice();
                    P2.decrescenteBudgetRent(rent); 
                    P4.increaseBudgetRent(rent);
                    P2.logOutput("-Giocatore " + player.getChar() + " ha pagato 8 fiorini a giocatore 4 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 8 fiorini a giocatore 4 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                    return true;
                }else if(player.getPositionChar() == "L"){
                    int rent = L.getRentHotelPrice();
                    P2.decrescenteBudgetRent(rent); 
                    P4.increaseBudgetRent(rent);
                    P2.logOutput("-Giocatore " + player.getChar() + " ha pagato 14 fiorini a giocatore 4 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 14 fiorini a giocatore 4 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                return true;
                }

            }else{
                return true;
            }




        }
        return false;

    }
    if(player.getChar() == "3"){

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
                    P3.logOutput("-Giocatore " + player.getChar() + " ha pagato 2 fiorini a giocatore 1 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 2 fiorini a giocatore 1 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                    return true;
                }else if(player.getPositionChar() == "S"){
                    int rent = S.getRentHomePrice();
                    P3.decrescenteBudgetRent(rent); 
                    P1.increaseBudgetRent(rent);
                    P3.logOutput("-Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 1 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 1 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                    return true;
                }else if(player.getPositionChar() == "L"){
                    int rent = L.getRentHomePrice();
                    P3.decrescenteBudgetRent(rent); 
                    P1.increaseBudgetRent(rent);
                    P3.logOutput("-Giocatore " + player.getChar() + " ha pagato 7 fiorini a giocatore 1 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 7 fiorini a giocatore 1 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                    return true;
                }

            }else if(board[i][j].find('^') != board[i][j].npos){
                 if(player.getPositionChar() == "E"){
                    int rent = E.getRentHotelPrice();
                    P3.decrescenteBudgetRent(rent); 
                    P1.increaseBudgetRent(rent);
                    P3.logOutput("-Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 1 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 1 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                    return true;
                }else if(player.getPositionChar() == "S"){
                    int rent = S.getRentHotelPrice();
                    P3.decrescenteBudgetRent(rent); 
                    P1.increaseBudgetRent(rent);
                    P3.logOutput("-Giocatore " + player.getChar() + " ha pagato 8 fiorini a giocatore 1 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 8 fiorini a giocatore 1 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                    return true;
                }else if(player.getPositionChar() == "L"){
                    int rent = L.getRentHotelPrice();
                    P3.decrescenteBudgetRent(rent); 
                    P1.increaseBudgetRent(rent);
                    P3.logOutput("-Giocatore " + player.getChar() + " ha pagato 14 fiorini a giocatore 1 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 14 fiorini a giocatore 1 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                    return true;
                }

            }else{
                return true;
            }


               
        }

        if(std::find(otherProperties["2"].begin(), otherProperties["2"].end(), player.getPosition()) != otherProperties["2"].end()){
            if(board[i][j].find('*') != board[i][j].npos){
                if(player.getPositionChar() == "E"){
                    int rent = E.getRentHomePrice();
                    P3.decrescenteBudgetRent(rent); 
                    P2.increaseBudgetRent(rent);
                    P3.logOutput("-Giocatore " + player.getChar() + " ha pagato 2 fiorini a giocatore 2 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 2 fiorini a giocatore 2 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                    return true;
                }else if(player.getPositionChar() == "S"){
                    int rent = S.getRentHomePrice();
                    P3.decrescenteBudgetRent(rent); 
                    P2.increaseBudgetRent(rent);
                   P3.logOutput("-Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 2 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 2 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                    return true;
                }else if(player.getPositionChar() == "L"){
                    int rent = L.getRentHomePrice();
                    P3.decrescenteBudgetRent(rent); 
                    P2.increaseBudgetRent(rent);
                    P3.logOutput("-Giocatore " + player.getChar() + " ha pagato 7 fiorini a giocatore 2 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 7 fiorini a giocatore 2 per pernottamento nella casella "+ board[i][j]<< "\n";
                    return true;
                }
                
            }else if(board[i][j].find('^') != board[i][j].npos){
                 if(player.getPositionChar() == "E"){
                    int rent = E.getRentHotelPrice();
                    P3.decrescenteBudgetRent(rent); 
                    P2.increaseBudgetRent(rent);
                    P3.logOutput("-Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 2 per pernottamento nella casella "+player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 2 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                    return true;
                }else if(player.getPositionChar() == "S"){
                    int rent = S.getRentHotelPrice();
                    P3.decrescenteBudgetRent(rent); 
                    P2.increaseBudgetRent(rent);
                    P3.logOutput("-Giocatore " + player.getChar() + " ha pagato 8 fiorini a giocatore 2 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 8 fiorini a giocatore 2 per pernottamento nella casella "+ player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                    return true;
                }else if(player.getPositionChar() == "L"){
                    int rent = L.getRentHotelPrice();
                    P3.decrescenteBudgetRent(rent); 
                    P2.increaseBudgetRent(rent);
                    P3.logOutput("-Giocatore " + player.getChar() + " ha pagato 14 fiorini a giocatore 2 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 14 fiorini a giocatore 2 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                    return true;
                }

            }else{
                return true;
            }



        }

         if(std::find(otherProperties["4"].begin(), otherProperties["4"].end(), player.getPosition()) != otherProperties["4"].end()){
            if(board[i][j].find('*') != board[i][j].npos){
                if(player.getPositionChar() == "E"){
                    int rent = E.getRentHomePrice();
                    P3.decrescenteBudgetRent(rent); 
                    P4.increaseBudgetRent(rent);
                    P3.logOutput("-Giocatore " + player.getChar() + " ha pagato 2 fiorini a giocatore 4 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 2 fiorini a giocatore 4 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                    return true;
                }else if(player.getPositionChar() == "S"){
                    int rent = S.getRentHomePrice();
                    P3.decrescenteBudgetRent(rent); 
                    P4.increaseBudgetRent(rent);
                    P3.logOutput("-Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 4 per pernottamento nella casella "+player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 4 per pernottamento nella casella "+ player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                    return true;
                }else if(player.getPositionChar() == "L"){
                    int rent = L.getRentHomePrice();
                    P3.decrescenteBudgetRent(rent); 
                    P4.increaseBudgetRent(rent);
                    P3.logOutput("-Giocatore " + player.getChar() + " ha pagato 7 fiorini a giocatore 4 per pernottamento nella casella "+ player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 7 fiorini a giocatore 4 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                    return true;
                }


            }else if(board[i][j].find('^') != board[i][j].npos){
                 if(player.getPositionChar() == "E"){
                    int rent = E.getRentHotelPrice();
                    P3.decrescenteBudgetRent(rent); 
                    P4.increaseBudgetRent(rent);
                    P3.logOutput("-Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 4 per pernottamento nella casella "+player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 4 per pernottamento nella casella "+ player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                    return true;
                }else if(player.getPositionChar() == "S"){
                    int rent = S.getRentHotelPrice();
                    P3.decrescenteBudgetRent(rent); 
                    P4.increaseBudgetRent(rent);
                    P3.logOutput("-Giocatore " + player.getChar() + " ha pagato 8 fiorini a giocatore 4 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 8 fiorini a giocatore 4 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                    return true;
                }else if(player.getPositionChar() == "L"){
                    int rent = L.getRentHotelPrice();
                    P3.decrescenteBudgetRent(rent); 
                    P4.increaseBudgetRent(rent);
                    P3.logOutput("-Giocatore " + player.getChar() + " ha pagato 14 fiorini a giocatore 4 per pernottamento nella casella "+player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 14 fiorini a giocatore 4 per pernottamento nella casella "+ player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                    return true;
                }

            }else{
                return true;
            }



        }
        return false;

    }
    if(player.getChar() == "4"){

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
                    P4.logOutput("-Giocatore " + player.getChar() + " ha pagato 2 fiorini a giocatore 1 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 2 fiorini a giocatore 1 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                    return true;
                }else if(player.getPositionChar() == "S"){
                    int rent = S.getRentHomePrice();
                    P4.decrescenteBudgetRent(rent); 
                    P1.increaseBudgetRent(rent);
                    P4.logOutput("-Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 1 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 1 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                    return true;
                }else if(player.getPositionChar() == "L"){
                    int rent = L.getRentHomePrice();
                    P4.decrescenteBudgetRent(rent); 
                    P1.increaseBudgetRent(rent);
                     P4.logOutput("-Giocatore " + player.getChar() + " ha pagato 7 fiorini a giocatore 1 per pernottamento nella casella "+ player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 7 fiorini a giocatore 1 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                return true;
                }

            }else if(board[i][j].find('^') != board[i][j].npos){
                 if(player.getPositionChar() == "E"){
                    int rent = E.getRentHotelPrice();
                    P4.decrescenteBudgetRent(rent); 
                    P1.increaseBudgetRent(rent);
                    P4.logOutput("-Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 1 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 1 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                    return true;
                }else if(player.getPositionChar() == "S"){
                    int rent = S.getRentHotelPrice();
                    P4.decrescenteBudgetRent(rent); 
                    P1.increaseBudgetRent(rent);
                    P4.logOutput("-Giocatore " + player.getChar() + " ha pagato 8 fiorini a giocatore 1 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 8 fiorini a giocatore 1 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                    return true;
                }else if(player.getPositionChar() == "L"){
                    int rent = L.getRentHotelPrice();
                    P4.decrescenteBudgetRent(rent); 
                    P1.increaseBudgetRent(rent);
                    P4.logOutput("-Giocatore " + player.getChar() + " ha pagato 14 fiorini a giocatore 1 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 14 fiorini a giocatore 1 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                return true;
                }

            }else{
                return true;
            }


        }
        if(std::find(otherProperties["2"].begin(), otherProperties["2"].end(), player.getPosition()) != otherProperties["2"].end()){
            if(board[i][j].find('*') != board[i][j].npos){
                if(player.getPositionChar() == "E"){
                    int rent = E.getRentHomePrice();
                    P4.decrescenteBudgetRent(rent); 
                    P2.increaseBudgetRent(rent);
                    P4.logOutput("-Giocatore " + player.getChar() + " ha pagato 2 fiorini a giocatore 2 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 2 fiorini a giocatore 2 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                    return true;
                }else if(player.getPositionChar() == "S"){
                    int rent = S.getRentHomePrice();
                    P4.decrescenteBudgetRent(rent); 
                    P2.increaseBudgetRent(rent);
                   P4.logOutput("-Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 2 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 2 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                     return true;
                }else if(player.getPositionChar() == "L"){
                    int rent = L.getRentHomePrice();
                    P4.decrescenteBudgetRent(rent); 
                    P2.increaseBudgetRent(rent);
                    P4.logOutput("-Giocatore " + player.getChar() + " ha pagato 7 fiorini a giocatore 2 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 7 fiorini a giocatore 2 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                return true;
                }
                
            }else if(board[i][j].find('^') != board[i][j].npos){
                 if(player.getPositionChar() == "E"){
                    int rent = E.getRentHotelPrice();
                    P4.decrescenteBudgetRent(rent); 
                    P2.increaseBudgetRent(rent);
                    P4.logOutput("-Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 2 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 2 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                    return true;
                }else if(player.getPositionChar() == "S"){
                    int rent = S.getRentHotelPrice();
                    P4.decrescenteBudgetRent(rent); 
                    P2.increaseBudgetRent(rent);
                    P4.logOutput("-Giocatore " + player.getChar() + " ha pagato 8 fiorini a giocatore 2 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 8 fiorini a giocatore 2 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                    return true;
                }else if(player.getPositionChar() == "L"){
                    int rent = L.getRentHotelPrice();
                    P4.decrescenteBudgetRent(rent); 
                    P2.increaseBudgetRent(rent);
                    P4.logOutput("-Giocatore " + player.getChar() + " ha pagato 14 fiorini a giocatore 2 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 14 fiorini a giocatore 2 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                return true;
                }

            }else{
                return true;
            }



        }
         if(std::find(otherProperties["3"].begin(), otherProperties["3"].end(), player.getPosition()) != otherProperties["3"].end()){
            if(board[i][j].find('*') != board[i][j].npos){
                if(player.getPositionChar() == "E"){
                    int rent = E.getRentHomePrice();
                    P4.decrescenteBudgetRent(rent); 
                    P3.increaseBudgetRent(rent);
                    P4.logOutput("-Giocatore " + player.getChar() + " ha pagato 2 fiorini a giocatore 3 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 2 fiorini a giocatore 3 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                    return true;
                }else if(player.getPositionChar() == "S"){
                    int rent = S.getRentHomePrice();
                    P4.decrescenteBudgetRent(rent); 
                    P3.increaseBudgetRent(rent);
                    P4.logOutput("-Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 3 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 3 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                    return true;
                }else if(player.getPositionChar() == "L"){
                    int rent = L.getRentHomePrice();
                    P4.decrescenteBudgetRent(rent); 
                    P3.increaseBudgetRent(rent);
                    P4.logOutput("-Giocatore " + player.getChar() + " ha pagato 7 fiorini a giocatore 3 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 7 fiorini a giocatore 3 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                return true;
                }


            }else if(board[i][j].find('^') != board[i][j].npos){
                 if(player.getPositionChar() == "E"){
                    int rent = E.getRentHotelPrice();
                    P4.decrescenteBudgetRent(rent); 
                    P3.increaseBudgetRent(rent);
                     P4.logOutput("-Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 3 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 4 fiorini a giocatore 3 per pernottamento nella casella "+ player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                    return true;

                }else if(player.getPositionChar() == "E") {
                    int rent = S.getRentHotelPrice();
                    P4.decrescenteBudgetRent(rent); 
                    P3.increaseBudgetRent(rent);
                    P4.logOutput("-Giocatore " + player.getChar() + " ha pagato 8 fiorini a giocatore 3 per pernottamento nella casella "+ player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 8 fiorini a giocatore 3 per pernottamento nella casella " + player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                    return true;

                }else if(player.getPositionChar() == "L"){
                    int rent = L.getRentHotelPrice();
                    P4.decrescenteBudgetRent(rent); 
                    P3.increaseBudgetRent(rent);
                    P4.logOutput("-Giocatore " + player.getChar() + " ha pagato 14 fiorini a giocatore 3 per pernottamento nella casella "+ player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + player.getChar() + " ha pagato 14 fiorini a giocatore 3 per pernottamento nella casella "+ player.convertRowToChar() + std::to_string(player.getPositionJ())+"\n";
                    return true;
                }

            }else{
                return true;
            }


        }

        return false;
        
    }

    return false;



}

void rentHumanPlayer(){

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
                    HP.logOutput("-Giocatore " + HP.getChar() + " ha pagato 2 fiorini a giocatore 2 per pernottamento nella casella "+ HP.convertRowToChar() + std::to_string(HP.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + HP.getChar() + " ha pagato 2 fiorini a giocatore 2 per pernottamento nella casella " + HP.convertRowToChar() + std::to_string(HP.getPositionJ())+"\n";
                }else if(HP.getPositionChar() == "S"){
                    int rent = S.getRentHomePrice();
                    HP.decrescenteBudgetRent(rent); 
                    P2.increaseBudgetRent(rent);
                   HP.logOutput("-Giocatore " + HP.getChar() + " ha pagato 4 fiorini a giocatore 2 per pernottamento nella casella " +  HP.convertRowToChar() + std::to_string(HP.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + HP.getChar() + " ha pagato 4 fiorini a giocatore 2 per pernottamento nella casella " + HP.convertRowToChar() + std::to_string(HP.getPositionJ())+"\n";
                }else if(HP.getPositionChar() == "L"){
                    int rent = L.getRentHomePrice();
                    HP.decrescenteBudgetRent(rent); 
                    P2.increaseBudgetRent(rent);
                    HP.logOutput("-Giocatore " + HP.getChar() + " ha pagato 7 fiorini a giocatore 2 per pernottamento nella casella " + HP.convertRowToChar() + std::to_string(HP.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + HP.getChar() + " ha pagato 7 fiorini a giocatore 2 per pernottamento nella casella "+ HP.convertRowToChar() + std::to_string(HP.getPositionJ())+"\n";
                }
                
            }else if(board[i][j].find('^') != board[i][j].npos){
                 if(HP.getPositionChar() == "E"){
                    int rent = E.getRentHotelPrice();
                    HP.decrescenteBudgetRent(rent); 
                    P2.increaseBudgetRent(rent);
                    HP.logOutput("-Giocatore " + HP.getChar() + " ha pagato 4 fiorini a giocatore 2 per pernottamento nella casella " + HP.convertRowToChar() + std::to_string(HP.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + HP.getChar() + " ha pagato 4 fiorini a giocatore 2 per pernottamento nella casella " + HP.convertRowToChar() + std::to_string(HP.getPositionJ())+"\n";
                }else if(HP.getPositionChar() == "S"){
                    int rent = S.getRentHotelPrice();
                    HP.decrescenteBudgetRent(rent); 
                    P2.increaseBudgetRent(rent);
                    HP.logOutput("-Giocatore " + HP.getChar() + " ha pagato 8 fiorini a giocatore 2 per pernottamento nella casella " + HP.convertRowToChar() + std::to_string(HP.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + HP.getChar() + " ha pagato 8 fiorini a giocatore 2 per pernottamento nella casella " + HP.convertRowToChar() + std::to_string(HP.getPositionJ())+"\n";
                }else if(HP.getPositionChar() == "L"){
                    int rent = L.getRentHotelPrice();
                    HP.decrescenteBudgetRent(rent); 
                    P2.increaseBudgetRent(rent);
                    HP.logOutput("-Giocatore " + HP.getChar() + " ha pagato 14 fiorini a giocatore 2 per pernottamento nella casella " + HP.convertRowToChar() + std::to_string(HP.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + HP.getChar() + " ha pagato 14 fiorini a giocatore 2 per pernottamento nella casella " + HP.convertRowToChar() + std::to_string(HP.getPositionJ())+"\n";
                }
            }
        }
        if(std::find(otherProperties["3"].begin(), otherProperties["3"].end(), HP.getPosition()) != otherProperties["3"].end()){
            if(board[i][j].find('*') != board[i][j].npos){
                if(HP.getPositionChar() == "E"){
                    int rent = E.getRentHomePrice();
                    HP.decrescenteBudgetRent(rent); 
                    P3.increaseBudgetRent(rent);
                    HP.logOutput("-Giocatore " + HP.getChar() + " ha pagato 2 fiorini a giocatore 3 per pernottamento nella casella " + HP.convertRowToChar() + std::to_string(HP.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + HP.getChar() + " ha pagato 2 fiorini a giocatore 3 per pernottamento nella casella " + HP.convertRowToChar() + std::to_string(HP.getPositionJ())+"\n";              
                }else if(HP.getPositionChar() == "S"){
                    int rent = S.getRentHomePrice();
                    HP.decrescenteBudgetRent(rent); 
                    P3.increaseBudgetRent(rent);
                    HP.logOutput("-Giocatore " + HP.getChar() + " ha pagato 4 fiorini a giocatore 3 per pernottamento nella casella " + HP.convertRowToChar() + std::to_string(HP.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + HP.getChar() + " ha pagato 4 fiorini a giocatore 3 per pernottamento nella casella "+ HP.convertRowToChar() + std::to_string(HP.getPositionJ())+"\n";
                }else if(HP.getPositionChar() == "L"){
                    int rent = L.getRentHomePrice();
                    HP.decrescenteBudgetRent(rent); 
                    P3.increaseBudgetRent(rent);
                    HP.logOutput("-Giocatore " + HP.getChar() + " ha pagato 7 fiorini a giocatore 3 per pernottamento nella casella "+ HP.convertRowToChar() + std::to_string(HP.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + HP.getChar() + " ha pagato 7 fiorini a giocatore 3 per pernottamento nella casella " + HP.convertRowToChar() + std::to_string(HP.getPositionJ())+"\n";
                }

            }else if(board[i][j].find('^') != board[i][j].npos){
                 if(HP.getPositionChar() == "E"){
                    int rent = E.getRentHotelPrice();
                    HP.decrescenteBudgetRent(rent); 
                    P3.increaseBudgetRent(rent);
                    HP.logOutput("-Giocatore " + HP.getChar() + " ha pagato 4 fiorini a giocatore 3 per pernottamento nella casella " + HP.convertRowToChar() + std::to_string(HP.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + HP.getChar() + " ha pagato 4 fiorini a giocatore 3 per pernottamento nella casella " + HP.convertRowToChar() + std::to_string(HP.getPositionJ())+"\n";
                }else if(HP.getPositionChar() == "S"){
                    int rent = S.getRentHotelPrice();
                    HP.decrescenteBudgetRent(rent); 
                    P3.increaseBudgetRent(rent);
                    HP.logOutput("-Giocatore " + HP.getChar() + " ha pagato 8 fiorini a giocatore 3 per pernottamento nella casella " + HP.convertRowToChar() + std::to_string(HP.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + HP.getChar() + " ha pagato 8 fiorini a giocatore 3 per pernottamento nella casella " + HP.convertRowToChar() + std::to_string(HP.getPositionJ())+"\n";
                }else if(HP.getPositionChar() == "L"){
                    int rent = L.getRentHotelPrice();
                    HP.decrescenteBudgetRent(rent); 
                    P3.increaseBudgetRent(rent);
                    HP.logOutput("-Giocatore " + HP.getChar() + " ha pagato 14 fiorini a giocatore 3 per pernottamento nella casella "+ HP.convertRowToChar() + std::to_string(HP.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + HP.getChar() + " ha pagato 14 fiorini a giocatore 3 per pernottamento nella casella "+ HP.convertRowToChar() + std::to_string(HP.getPositionJ())+"\n";
                }
            }
        }
         if(std::find(otherProperties["4"].begin(), otherProperties["4"].end(), HP.getPosition()) != otherProperties["4"].end()){
            if(board[i][j].find('*') != board[i][j].npos){
                if(HP.getPositionChar() == "E"){
                    int rent = E.getRentHomePrice();
                    HP.decrescenteBudgetRent(rent); 
                    P4.increaseBudgetRent(rent);
                    HP.logOutput("-Giocatore " + HP.getChar() + " ha pagato 2 fiorini a giocatore 4 per pernottamento nella casella " + HP.convertRowToChar() + std::to_string(HP.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + HP.getChar() + " ha pagato 2 fiorini a giocatore 4 per pernottamento nella casella "+ HP.convertRowToChar() + std::to_string(HP.getPositionJ())+"\n";
                }else if(HP.getPositionChar() == "S"){
                    int rent = S.getRentHomePrice();
                    HP.decrescenteBudgetRent(rent); 
                    P4.increaseBudgetRent(rent);
                    HP.logOutput("-Giocatore " + HP.getChar() + " ha pagato 4 fiorini a giocatore 4 per pernottamento nella casella " + HP.convertRowToChar() + std::to_string(HP.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + HP.getChar() + " ha pagato 4 fiorini a giocatore 4 per pernottamento nella casella " + HP.convertRowToChar() + std::to_string(HP.getPositionJ())+"\n";
                }else if(HP.getPositionChar() == "L"){
                    int rent = L.getRentHomePrice();
                    HP.decrescenteBudgetRent(rent); 
                    P4.increaseBudgetRent(rent);
                    HP.logOutput("-Giocatore " + HP.getChar() + " ha pagato 7 fiorini a giocatore 4 per pernottamento nella casella " + HP.convertRowToChar() + std::to_string(HP.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + HP.getChar() + " ha pagato 7 fiorini a giocatore 4 per pernottamento nella casella "+ HP.convertRowToChar() + std::to_string(HP.getPositionJ())+"\n";
                }

            }else if(board[i][j].find('^') != board[i][j].npos){
                 if(HP.getPositionChar() == "E"){
                    int rent = E.getRentHotelPrice();
                    HP.decrescenteBudgetRent(rent); 
                    P4.increaseBudgetRent(rent);
                    HP.logOutput("-Giocatore " + HP.getChar() + " ha pagato 4 fiorini a giocatore 4 per pernottamento nella casella " + HP.convertRowToChar() + std::to_string(HP.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + HP.getChar() + " ha pagato 4 fiorini a giocatore 4 per pernottamento nella casella " + HP.convertRowToChar() + std::to_string(HP.getPositionJ())+"\n";;
                }else if(HP.getPositionChar() == "S"){
                    int rent = S.getRentHotelPrice();
                    HP.decrescenteBudgetRent(rent); 
                    P4.increaseBudgetRent(rent);
                    HP.logOutput("-Giocatore " + HP.getChar() + " ha pagato 8 fiorini a giocatore 4 per pernottamento nella casella " + HP.convertRowToChar() + std::to_string(HP.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + HP.getChar() + " ha pagato 8 fiorini a giocatore 4 per pernottamento nella casella "+ HP.convertRowToChar() + std::to_string(HP.getPositionJ())+"\n";
                }else if(HP.getPositionChar() == "L"){
                    int rent = L.getRentHotelPrice();
                    HP.decrescenteBudgetRent(rent); 
                    P4.increaseBudgetRent(rent);
                    HP.logOutput("-Giocatore " + HP.getChar() + " ha pagato 14 fiorini a giocatore 4 per pernottamento nella casella " + HP.convertRowToChar() + std::to_string(HP.getPositionJ())+"\n");
                    std::cout << "-Giocatore " + HP.getChar() + " ha pagato 14 fiorini a giocatore 4 per pernottamento nella casella "+ HP.convertRowToChar() + std::to_string(HP.getPositionJ())+"\n";
                }
            }
        }
        HP.checkIfBankrupt();
}

void checkShowCommand(){

   
    std::string showCommand;
    std::cout<<"\nInserire il comando show per la visualizzazione: ";
    std::getline(std::cin, showCommand, '\n');

    if(showCommand == "SHOW" || showCommand == "show"){
        std::cout<<"\n\nTABELLONE:\n";
        printScoreboard();
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
    std::cout<<"\n";

}

/*
    Valori random associati alle varie caselle: 

    Se esce 1 -- casella Luxury
    Se esce 2 -- casella Economic
    Se esce 3 -- casella Standard

*/
void firstRow(){
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
            fillAllSquaresRows (j, rowPosition);
        }

    }
}

void lastRow(){
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
            fillAllSquaresRows(j, rowPosition);
        }

    }
}

void firstCol(){
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
            fillAllSquaresColumn(i, columnPosition);
        }
    }

}

void lastCol(){
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
            fillAllSquaresColumn(i, columnPosition);
        }
    
    }
}
void fillAllSquaresColumn(int i, int columnPosition){
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
void fillAllSquaresRows(int j, int position ){
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
#ifndef SCOREBOARD_HPP
#define SCOREBOARD_HPP


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

void printScoreboard(std::string board[ROW][COL]){
 
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

void removePrevChar(std::string board[ROW][COL], Player& player){
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



#endif
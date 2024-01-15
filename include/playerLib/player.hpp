#ifndef player_hpp
#define player_hpp

Player::Player(){
    setPosition(1,1, "P");
}

Player::Player(std::string playerChar): playerChar{playerChar}{
      setPosition(1,1, "P");
}


int Player::throwDice(){
    int first = std::rand()%6+1;
    int second = std::rand()%6+1;
    return (first + second);
}

void Player::setPosition(int i, int j, std::string charSquare){
    if(i>0 && i<9 && j>0 && j<9 ){
        this->pos.i = i;
        this->pos.j = j;
        this->pos.charSqare = charSquare;
    }else{
        this->pos.i = 1;
        this->pos.j = 1;
        this->pos.charSqare = "P";
    }
    
}


bool Player::checkIfBankrupt(){
    if(this->budget <= 0){
        this->setBankrupt();
        return true;
    }
    return false;
}

void  Player::removePlayerCharIfBankrupt(std::string board[9][9],EconomicSquare& E, StandardSquare& S, LuxurySquare& L) {
    int i,j;
    for(auto it = this->purchasedSquare.begin(); it != this->purchasedSquare.end(); it++){

        i = it->getPosI();
        j = it->getPosJ();

        if(board[i][j].find('*') != board[i][j].npos){
            board[i][j].erase(board[i][j].find('*'), (board[i][j].find('*'))+1);
            
        }

            if(board[i][j].find('^') != board[i][j].npos){
            board[i][j].erase(board[i][j].find('^'), (board[i][j].find('^'))+1);
            
        }
        
        if(board[i][j] == "E")
            E.removePlayerPosition(i, j);
        if(board[i][j] == "S")
            S.removePlayerPosition(i, j);
        if(board[i][j] == "L")
            L.removePlayerPosition(i, j);
    }
    
}

void Player::logOutput(const std::string& txt) const{
    // Apri il file di log in modalità appendd
    std::ofstream fileDiLog ("logFile.txt", std::ios::app);
    try
    {
        fileDiLog.is_open();
        fileDiLog << txt << std::endl;
        fileDiLog.clear();
        fileDiLog.close();
    }
    catch(const std::ofstream::failure& e)
    {
      std::cerr << "Errore: Impossibile aprire il file di log." <<e.what()<<"\n";
    }
    
}

bool Player::checkPurchaseSquare(std::string board[9][9], EconomicSquare& E,StandardSquare& S, LuxurySquare& L){

    int i = this->getPositionI();
    int j = this->getPositionJ();
    this->setPosition(i, j, board[i][j].substr(0,1));

    bool tmp  = false;

        if(board[i][j].substr(0,1) == "E" &&  (E.getPlayer(i,j) == " "  || E.getPlayer(i,j) == this->playerChar)){  //controlla se la casella è gia posseduta da qualche altro giocatore
            if(this->budget >= E.getPrice()){
                E.setPlayer(this->playerChar, i, j);
                this->budget -= E.getPrice();
                tmp = true;
            }
            
        }else if(board[i][j].substr(0,1) == "S"  &&  (S.getPlayer(i,j) == " " || S.getPlayer(i,j) == this->playerChar)){
            if(this->budget >= S.getPrice()){
                S.setPlayer(this->playerChar, i, j);
                this->budget -= S.getPrice();
                tmp = true;
            }
                
        }else if(board[i][j].substr(0,1) == "L"  &&  (L.getPlayer(i,j) == " "  || L.getPlayer(i,j) == this->playerChar)){
            if(this->budget >= L.getPrice()){
                L.setPlayer(this->playerChar, i, j);
                this->budget -= L.getPrice();
                tmp = true;
            }
        }

        if(tmp){
            std::cout<<"-Giocatore " +  this->playerChar + " ha acquistato il terreno in " + this->convertRowToChar() + std::to_string(j) + " di tipo " + board[i][j].substr(0,1) + "\n";
            this->logOutput("-Giocatore " +  this->playerChar + " ha acquistato il terreno in " + this->convertRowToChar() +  std::to_string(j) + " di tipo " + board[i][j].substr(0,1) + "\n");
            this->purchasedSquare.push_back(this->pos);
            return true;
        }else{

            if(E.getPlayer(i,j) != " " || S.getPlayer(i,j) != " " || L.getPlayer(i,j) != " "){
                std::cout<<"Il terreno è già stato acquistato da un altro giocatore! \n";
                this->logOutput("Il terreno è già stato acquistato da un altro giocatore! \n");
                return false;
                
            }else{
                std::cout<<"Il giocatore " +  this->playerChar + " non ha budget a sufficienza per acquistare il terreno! \n";
                this->logOutput("Il giocatore " +  this->playerChar + " non ha budget a sufficienza per acquistare il terreno! \n");
                return false;

            }

        }

    return false;
    
}

bool Player::checkPurchaseHouse( std::string board[9][9], EconomicSquare& E,StandardSquare& S, LuxurySquare& L){

    int i = this->getPositionI();
    int j = this->getPositionJ();
    this->setPosition(i, j, board[i][j].substr(0, 1));
    bool tmp = false;

    if(std::find(this->purchasedSquare.begin(), this->purchasedSquare.end(), this->pos) != this->purchasedSquare.end()){

        if(board[i][j].substr(0,1) == "E" && (E.getPlayer(i,j) == " "  || E.getPlayer(i,j) == this->playerChar)){
            if(this->budget >= E.getHomePrice()){
                E.setPlayer(this->playerChar, i, j);
                this->budget -= E.getHomePrice();
                board[i][j] += E.getCharHome();
                tmp = true;
            }
    
        }else if(board[i][j].substr(0,1) == "S" &&  (S.getPlayer(i,j) == " " || S.getPlayer(i,j) == this->playerChar)){
            if(this->budget >= S.getHomePrice()){
                S.setPlayer(this->playerChar, i, j);
                this->budget -= S.getHomePrice();
                board[i][j] += S.getCharHome();
                tmp = true;
            }
        }else if(board[i][j].substr(0,1) == "L"   &&  (L.getPlayer(i,j) == " "  || L.getPlayer(i,j) == this->playerChar)){
            if(this->budget >= E.getHomePrice()){
                L.setPlayer(this->playerChar, i, j);
                this->budget -= L.getHomePrice();
                board[i][j] += L.getCharHome();
                tmp = true;
            }

        }

        if(tmp == true){
           std::cout<<"-Giocatore " +  this->playerChar + " ha acquistato una casa sul terreno " + this->convertRowToChar() + std::to_string(j) + " di tipo " + board[i][j].substr(0,1) + "\n";
            this->logOutput("-Giocatore " +  this->playerChar + " ha acquistato una casa sul terreno " + this->convertRowToChar() +  std::to_string(j) + " di tipo " + board[i][j].substr(0,1) + "\n");
            this->purchasedSquare.push_back(this->pos);
            return true;
        }else{
          
            if(E.getPlayer(i,j) != " " || S.getPlayer(i,j) != " " || L.getPlayer(i,j) != " "){
                std::cout<<"Il terreno è già stato acquistato da un altro giocatore! \n";
                this->logOutput("Il terreno è già stato acquistato da un altro giocatore! \n");
                return false;
                
            }else{
                std::cout<<"Il giocatore " +  this->playerChar + " non ha budget a sufficienza per acquistare il terreno! \n";
                this->logOutput("Il giocatore " +  this->playerChar + " non ha budget a sufficienza per acquistare il terreno! \n");
                return false;
                

            }
        }
            
    }else{
        return this->checkPurchaseSquare(board, E, S, L);
    }

    return false;
    
}

bool Player::checkPurchaseHotel( std::string board[9][9], EconomicSquare& E,StandardSquare& S, LuxurySquare& L){

    int i = this->getPositionI();
    int j = this->getPositionJ();
    this->setPosition(i, j, board[i][j].substr(0, 1));

    bool tmp  = false;
    if(std::find(this->purchasedSquare.begin(), this->purchasedSquare.end(), this->pos) != this->purchasedSquare.end()){
        if(board[i][j].substr(0,1) == "E" && (E.getPlayer(i,j) == " "  || E.getPlayer(i,j) == this->playerChar)){
            if(this->budget >= E.getHotelPrice()){
                E.setPlayer(this->playerChar, i, j);
                this->budget -= E.getHotelPrice();
                tmp = true;
            }
                
        }else if(board[i][j].substr(0,1) == "S" && (S.getPlayer(i,j) == " " || S.getPlayer(i,j) == this->playerChar)){
            if(this->budget >= S.getHotelPrice()){
                S.setPlayer(this->playerChar, i, j);
                this->budget -= S.getHotelPrice();
                tmp =  true;
            }
            
        }else if(board[i][j].substr(0,1) == "L"  && (L.getPlayer(i,j) == " "  || L.getPlayer(i,j) == this->playerChar)) {
            if(this->budget >= L.getHotelPrice()){
                L.setPlayer(this->playerChar, i, j);
                this->budget -= L.getHotelPrice();
                tmp =  true;
            }
        }

        if(tmp == true){
            std::cout<<"-Giocatore " +  this->playerChar + " ha migliorato una casa in albergo sul terreno " + this->convertRowToChar() + std::to_string(j) + " di tipo " + board[i][j].substr(0,1) + "\n";
            this->logOutput("-Giocatore " +  this->playerChar + " ha migliorato una casa in albergo sul terreno " + this->convertRowToChar() +  std::to_string(j) + " di tipo " + board[i][j].substr(0,1) + "\n");
            this->purchasedSquare.push_back(this->pos);
            if(board[i][j].find(E.getCharHome()) != board[i][j].npos){
                board[i][j].erase(board[i][j].find(E.getCharHome()), this->playerChar.length());
                board[i][j] += E.getCharHotel();
            }
            return true;
        }else{
            
            if(E.getPlayer(i,j) != " " || S.getPlayer(i,j) != " " || L.getPlayer(i,j) != " "){
                std::cout<<"Il terreno è già stato acquistato da un altro giocatore! \n";
                this->logOutput("Il terreno è già stato acquistato da un altro giocatore! \n");
                return false;
                
            }else{
                std::cout<<"Il giocatore " +  this->playerChar + " non ha budget a sufficienza per acquistare il terreno! \n";
                this->logOutput("Il giocatore " +  this->playerChar + " non ha budget a sufficienza per acquistare il terreno! \n");
                return false;

            }
        }
    }else{
         return this->checkPurchaseSquare(board, E, S, L);

    }

    return false;
}

void Player::printStatus() const{
    std::cout<<"Giocatore "<<this->playerChar<<": ";
    for(auto it = this->purchasedSquare.begin(); it != this->purchasedSquare.end(); it++){
        switch (it->i)
        {
        case 1:
            std::cout<<"A"<<it->j<<" ";;
            break;
        case 2:
            std::cout<<"B"<<it->j<<" ";;
            break;
        case 3:
            std::cout<<"C"<<it->j<<" ";;
            break;
        case 4:
            std::cout<<"D"<<it->j<<" ";;
            break;
        case 5:
            std::cout<<"E"<<it->j<<" ";;
            break;
        case 6:
            std::cout<<"F"<<it->j<<" ";;
            break;
        case 7:
            std::cout<<"G"<<it->j<<" ";;
            break;
        case 8:
            std::cout<<"H"<<it->j<<" ";
            break;
        default:
            break;
        }
    }
std::cout<<"\n";
}

bool ComputerPlayer::randomChoice() const{
    
    //se esce 1 si considera la scelta positiva mentre per tutti gli altri valori la scelta è negativa
    int choice = std::rand() % 4 + 1;

    if(choice == 1 )
        return true;
    else
        return false;
}

bool HumanPlayer::getUserChoice(std::string board[9][9], EconomicSquare E, StandardSquare S, LuxurySquare L) {
        int i = this->getPositionI();
        int j = this->getPositionJ();
        char userInput;

        if((board[i][j].substr(0, 1) == "E" || board[i][j].substr(0, 1) == "S" || board[i][j].substr(0, 1) == "L")){
            if(std::find(this->purchasedSquare.begin(), this->purchasedSquare.end(), this->pos) != this->purchasedSquare.end()){

                if(board[i][j].find('*') != board[i][j].npos){
                    std::cout << "Vuoi costruire un albergo? (S per sì, N per no): ";

                }else{
                    std::cout << "Vuoi costruire una casa? (S per sì, N per no): ";

                } 
            }else if(E.getPlayer(i, j) == " " || S.getPlayer(i, j) == " " || L.getPlayer(i, j) == " "){
                std::cout << "Vuoi acquistare il terreno? (S per sì, N per no): ";
            }
            std::cin >> userInput;
        }else{
            std::cout<<"Ti trovi su una casella angolare!\n";
        }
        std::string temp;
        std::getline(std::cin, temp);
        // Converte l'input dell'utente in minuscolo per gestire sia 'S' che 's'
        return (std::tolower(userInput) == 's');
    }

std::string Player::convertRowToChar() const{

    switch (this->getPositionI())
    {
    case 1:
        return "A";
        break;
    case 2:
        return "B";
        break;
    case 3:
        return "C";
        break;
    case 4:
        return "D";
        break;
    case 5:
        return "E";
        break;
    case 6:
        return "F";
        break;
    case 7: 
        return "G";
        break;
    case 8:
        return "H";
        break;
    default:
        return " ";
        break;
    }
}

#endif
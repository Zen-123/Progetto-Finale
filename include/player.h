#ifndef PLAYER_H
#define PLAYER_H



class Player{
protected:
    int budget = 100;
    std::string playerChar;
    Position pos;
    bool bankrupt = false;
    std::vector<Position> purchasedSquare;
public:

    Player(){
        setPosition(1,1, "P");
    }

    Player(std::string playerChar): playerChar{playerChar}{
        setPosition(1,1, "P");
    }

    int throwDice(){
        int first = std::rand()%6+1;
        int second = std::rand()%6+1;
        return (first + second);
    }

    void increaseBudget(){
        this->budget = this->budget + 20;
    }

    void increaseBudgetRent(int price){
        this->budget = this->budget + price;
    }
    void decrescenteBudgetRent(int price){
        this->budget = this->budget - price;
    }

    int getBudget(){
        return this->budget;
    }

    std::string getChar(){
        return this->playerChar;
    }

    void setPosition(int i, int j, std::string charSquare){
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

    void setBankrupt(){
        this->bankrupt = true;
    }

    int getPositionI(){
        return this->pos.getPosI();
    }

    int getPositionJ(){
        return this->pos.getPosJ();
    }

    std::string getPositionChar(){
        return this->pos.getCharSquare();
    }

    Position getPosition(){
        return this->pos;
    }

    bool checkIfBankrupt(){
        if(this->budget <= 0){
            this->setBankrupt();
            return true;
        }
        return false;
    }

    void removePlayerCharIfBankrupt(std::string board[9][9], EconomicSquare& E, StandardSquare& S, LuxurySquare& L) {
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

    void logOutput(const std::string& txt) {
        // Apri il file di log in modalità appendd
        std::ofstream fileDiLog ("logFile.txt", std::ios::app);
        
        // Verifica se il file è aperto prima di scrivere
        if (fileDiLog.is_open()) {
            fileDiLog << txt << std::endl;
            fileDiLog.clear();
            fileDiLog.close();
        } else {
            // Gestisci l'errore se il file non può essere aperto
            std::cerr << "Errore: Impossibile aprire il file di log." << std::endl;
        }



    }


    void checkPurchaseSquare(std::string board[9][9], EconomicSquare& E,StandardSquare& S, LuxurySquare& L ){

        int i = this->getPositionI();
        int j = this->getPositionJ();
        bool tmp  = false;

        if(board[i][j].substr(0,1) == "E" &&  (E.getPlayer(i,j) == " " )){  //controlla se la casella è gia posseduta da qualche altro giocatore
            if(this->budget >= E.getPrice()){
                E.setPlayer(this->playerChar, i, j);
                this->budget -= E.getPrice();
                tmp = true;
            }
         
        }else if(board[i][j].substr(0,1) == "S"  &&  (S.getPlayer(i,j) == " " )){
            if(this->budget >= S.getPrice()){
                S.setPlayer(this->playerChar, i, j);
                this->budget -= S.getPrice();
                tmp = true;
            }
                
        }else if(board[i][j].substr(0,1) == "L"  &&  (L.getPlayer(i,j) == " " )){
            if(this->budget >= L.getPrice()){
                L.setPlayer(this->playerChar, i, j);
                this->budget -= L.getPrice();
                tmp = true;
            }
        }

        if(tmp){
            std::cout<<"Il giocatore " +  this->playerChar + " ha acquistato il terreno in "<<i<<" - "<<j<<" di tipo " + board[i][j] <<"\n";
            logOutput("Il giocatore " +  this->playerChar + " ha acquistato il terreno in " + board[i][j]);
            this->purchasedSquare.push_back(this->pos);
        }else{

            if(E.getPlayer(i,j) != " " || S.getPlayer(i,j) != " " || L.getPlayer(i,j) != " ")
                std::cout<<"Il terreno è già stato acquistato da un altro giocatore! \n";
            else    
                std::cout<<"Il giocatore " +  this->playerChar + " non ha budget a sufficienza per acquistare il terreno! \n";

        }

        this->setPosition(i, j, board[i][j].substr(0,1));

        
        
    }

    void checkPurchaseHouse( std::string board[9][9], EconomicSquare& E,StandardSquare& S, LuxurySquare& L){

        int i = this->getPositionI();
        int j = this->getPositionJ();
        bool tmp = false;

        if(std::find(this->purchasedSquare.begin(), this->purchasedSquare.end(), this->pos) != this->purchasedSquare.end()){

            if(board[i][j].substr(0,1) == "E" ){
                if(this->budget >= E.getHomePrice()){
                    E.setPlayer(this->playerChar, i, j);
                    this->budget -= E.getHomePrice();
                    board[i][j] += E.getCharHome();
                    this->setPosition(i, j, "E");
                    tmp = true;
                }
      
            }else if(board[i][j].substr(0,1) == "S" ){
                 if(this->budget >= S.getHomePrice()){
                    S.setPlayer(this->playerChar, i, j);
                    this->budget -= S.getHomePrice();
                    board[i][j] += S.getCharHome();
                    this->setPosition(i, j, "S");
                    tmp = true;
                 }
            }else if(board[i][j].substr(0,1) == "L"){
                 if(this->budget >= E.getHomePrice()){
                    L.setPlayer(this->playerChar, i, j);
                    this->budget -= L.getHomePrice();
                    board[i][j] += L.getCharHome();
                    this->setPosition(i, j, "L");
                    tmp = true;
                 }

            }

            if(tmp){
                std::cout<<"Il giocatore " +  this->playerChar + " ha acquistato una casa sul terreno "<<i<<" - "<<j<<" di tipo " + board[i][j] <<"\n";
                logOutput("Il giocatore " +  this->playerChar + " ha costruito una casa sul terreno " + board[i][j]);
                this->purchasedSquare.push_back(this->pos);
            }else
                std::cout<<"Il giocatore " +  this->playerChar + " non ha budget sufficiente per acquistare una casa! \n";
        }else{
            this->checkPurchaseSquare(board, E, S, L);
        }




      
    }

    void checkPurchaseHotel( std::string board[9][9], EconomicSquare& E,StandardSquare& S, LuxurySquare& L){

        int i = this->getPositionI();
        int j = this->getPositionJ();
        bool tmp  = false;
        if(std::find(this->purchasedSquare.begin(), this->purchasedSquare.end(), this->pos) != this->purchasedSquare.end()){
            if(board[i][j].substr(0,1) == "E"){
                if(this->budget >= E.getHotelPrice()){
                    E.setPlayer(this->playerChar, i, j);
                    this->budget -= E.getHotelPrice();
                    this->setPosition(i, j, "E");
                    tmp = true;
                }
                    
            }else if(board[i][j].substr(0,1) == "S"){
                if(this->budget >= S.getHotelPrice()){
                    S.setPlayer(this->playerChar, i, j);
                    this->budget -= S.getHotelPrice();
                    this->setPosition(i, j, "E");
                    tmp =  true;
                }
             
            }else if(board[i][j].substr(0,1) == "L"){
                if(this->budget >= L.getHotelPrice()){
                    L.setPlayer(this->playerChar, i, j);
                    this->budget -= L.getHotelPrice();
                    this->setPosition(i, j, "E");
                    tmp =  true;
                }
            }

            if(tmp){
                std::cout<<"\nIl giocatore " + this->playerChar + " ha migliorato una casa in albergo sul terreno " <<i<<" - "<<j<<" di tipo " + board[i][j] <<"\n";
                logOutput("Il giocatore " + this->playerChar + " ha migliorato una casa in albergo sul terreno " + board[i][j]);
                this->purchasedSquare.push_back(this->pos);
                if(board[i][j].find(E.getCharHome()) != board[i][j].npos){
                    board[i][j].erase(board[i][j].find(E.getCharHome()), this->playerChar.length());
                    board[i][j] += E.getCharHotel();
                }
            }else{
                std::cout<<"Il giocatore " +  this->playerChar + " non ha budget sufficiente per acquistare un albergo! \n";
                
            }


        }else{
            this->checkPurchaseSquare(board, E, S, L);
        }
    }

    void printStatus(){
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

    std::vector<Position> getProperty(){
        return this->purchasedSquare;
    }

    ~Player() {}
};


class ComputerPlayer : public Player{
public:

    ComputerPlayer(std::string p):Player(p){}

    bool randomChoice(){
        
        //se esce 1 si considera la scelta positiva mentre per tutti gli altri valori la scelta è negativa
        int choice = std::rand() % 4 + 1;

        if(choice == 1 )
            return true;
        else
            return false;
    }

    ~ComputerPlayer() {}

};

class HumanPlayer : public Player {
public:
    HumanPlayer(std::string p) : Player(p) {}

    // Funzione che richiede all'utente di fare una scelta (true o false)
    bool getUserChoice(std::string board[9][9], EconomicSquare E, StandardSquare S, LuxurySquare L) {
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

    // Override della funzione randomChoice con la logica di input da parte dell'utente
    // bool randomChoice() override {
    //     return getUserChoice();
    // }

    ~HumanPlayer() {}
};

#include "player.hpp"



#endif

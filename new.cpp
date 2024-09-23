#include"Game_one.h"
#include<iostream>
//using namespace sf
int main(){
    //init srand
    std::srand(static_cast<unsigned>(NULL));
   Game game;
while(game.running() && !game.getEndGame()){
//event polling
                
    //update 
    game.update();
    //render
    game.render();
}//endd of application
}
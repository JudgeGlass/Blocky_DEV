#include <iostream>

#include <game/blocky.hpp>

int main(){
    std::cout << "Staring Blocky..." << std::endl;

    Blocky game(1024, 768);

    game.init();
    game.loop();

    return 0;
}
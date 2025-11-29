#include <iostream>
#include <string>
#include <cstdlib>
#include <thread>
#include <chrono>

std::string strat(std::string a) {
    int fir = std::stoi(a.substr(1, 1));
    fir = 1 - fir;
    std::string b = std::to_string(fir) + a.substr(0, a.size() - 1);
    return b;
}

void games(std::string a, std::string b) {
    int winner = 0;
    int loser = 0;
    std::string game;
    std::string next;
    while (true) {
        next = std::to_string (std::rand() % 2);
        game += next;
        std::cout << next;
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        if (game.size() >= a.size() && game.substr(game.size() - a.size()) == a){
            loser += 1;
            game.clear();
            std::cout << std::endl;
            std::cout << "RESULT:" << std::endl;
            std::cout << winner << "  " << loser << std::endl;
        } else if (game.size() >= b.size() && game.substr(game.size() - b.size()) == b) {
            winner += 1;
            game.clear();
            std::cout << std::endl;
            std::cout << "RESULT:" << std::endl;
            std::cout << winner << "  " << loser << std::endl;
        }
    }
}

int main() {
    std::string a;
    std::cin >> a;
    std::string b = strat(a);
    games(a, b);
    return 0;
}

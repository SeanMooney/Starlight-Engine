#include <core/core.hpp>
#include <example/game.hpp>

using Game = starlight::example::Game;

int main(int argc, char* args[]) {
    Game game(args[0]);
    game.run();
    /* sucessful exit */
    return 0;
}
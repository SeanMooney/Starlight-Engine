#include <core/core.hpp>
#include <example/game.hpp>

using Game = starlight::example::Game;

int main(int argc, char* args[]) {
    SUPPRESS_UNUSED(argc);
    Game game(args[0]);
    game.run();
    /* sucessful exit */
    return 0;
}
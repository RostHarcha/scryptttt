#pragma once
#include <string>
struct Settings {
    int size_x = 15; 
    int size_y = 25;
    int seed = 0; 
};

enum class Action {
    Open,
    Flag,
    RemoveFlag,
    OpenAround,
    Stop,
    Help,
    NONE
};

struct Command {
    Action action = Action::NONE;
    int x = -1;
    int y = -1;
};

enum class CellState {
    Closed,
    Oppened,
    Flag,
    Triggered
};

enum class GameState {
    game,
    loss,
    win
};
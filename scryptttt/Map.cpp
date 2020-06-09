#include <vector>
#include "Map.h"

int Map::cell(int x, int y) {
    return y * set.size_x + x;
}

CellState Map::get_state(const int x, const int y) {
    return state[cell(x, y)];
}

void Map::set_state(const int x, const int y, CellState _state) {
    state[cell(x, y)] = _state;
}

void Map::create_vectors() {
    auto m_size = set.size_x * set.size_y;
    mine.resize(m_size);
    state.resize(m_size);
}

void Map::create_mines(const int first_x, const int first_y) {
    int mines_planted = 0;
    while (mines_planted <= set.mines) {
        int rand_cell = rand() % (set.size_x * set.size_y);
        if (rand_cell == cell(first_x, first_y)) {
            continue;
        }

        if (mine[rand_cell] == 0) {
            mine[rand_cell] = 1;
            mines_planted++;
        }
    }
}

void Map::clear_mines() {
    for (auto i = 0; i < mine.size(); i++) {
        mine[i] = false;
    }
}

void Map::clear_map() {
    for (int i = 0; i < state.size(); i++) {
        state[i] = CellState::Closed;
    }
}

void Map::create(Settings _set) {
        set = _set;
        game_state = GameState::game;
        create_vectors();
        clear_map();
        clear_mines();
        create_mines(first_x, first_y);
        set_state(first_x, first_y, CellState::Oppened);
        cells_oppened++;
        cell_sign = create_cell_signs();
        open_empty_cells(cell_sign[cell(first_x, first_y)]);
 }

std::vector<CellState> Map::get_current_state() {
    return state;
}

bool Map::on_map(int x, int y) {
    if (x < set.size_x and x >= 0 and y < set.size_y and y >= 0) return 1;
    else return 0;
}

int Map::mines_around(int _x, int _y) {
    int output = 0;
    if (mine[cell(_x, _y)]) return 9;

    for (int y = _y - 1; y <= _y + 1; y++) {
        for (int x = _x - 1; x <= _x + 1; x++) {
            if (on_map(x, y)) if (mine[cell(x, y)]) output++;
        }
    }
    return output;
}

std::vector<int> Map::create_cell_signs() {
    std::vector<int> output;
    for (int y = 0; y < set.size_y; y++) {
        for (int x = 0; x < set.size_x; x++) {
            output.push_back(mines_around(x, y));
        }
    }   
    return output;
}

std::vector<int> Map::get_cell_signs() {
    return cell_sign;
}

void Map::flag(const int x, const int y) {
    if (get_state(x, y) != CellState::Closed) {
        return;
    }
    set_state(x, y, CellState::Flag);
}

void Map::remove_flag(const int x, const int y) {
    if (get_state(x, y) != CellState::Flag) {
        return;
    }
    set_state(x, y, CellState::Closed);
}

void Map::open_map() {
    for (int i = 0; i < state.size(); i++) {
        state[i] = CellState::Oppened;
    }
    cells_oppened = set.size_x * set.size_y;
}

void Map::trigger_mine(int x, int y) {
    game_state = GameState::loss;
    open_map();
    set_state(x, y, CellState::Triggered);
}

void Map::open_around(const int x, const int y) {
    for (int _y = y - 1; _y <= y + 1; _y++) {
        for (int _x = x - 1; _x <= x + 1; _x++) {
            if (on_map(_x, _y) and get_state(_x, _y) == CellState::Closed) {
                if (mine[cell(_x, _y)]) {
                    trigger_mine(_x, _y);
                    return;
                }
                set_state(_x, _y, CellState::Oppened);
                cells_oppened++;
            }
        }
    }
}

void Map::open_empty_cells(int cell_sign) {
    if (cell_sign != 0) {
        return;
    }
    for (int i = 0; i < 10; i++) {
        for (int y = 0; y < set.size_y; y++) {
            for (int x = 0; x < set.size_x; x++) {
                if (get_state(x, y) == CellState::Oppened) {
                    if (this->cell_sign[cell(x, y)] == 0) {
                        open_around(x, y);
                    }
                }
            }
        }
    }
}

void Map::open(int x, int y) {
    if (mine[cell(x, y)]) {
        trigger_mine(x, y);
        return;
    } 
    if (get_state(x, y) != CellState::Closed) {
        return;
    }
    set_state(x, y, CellState::Oppened);
    cells_oppened++;
    open_empty_cells(cell_sign[cell(x, y)]);
}

void Map::process_tick(Action action, int x, int y) {
    if (!on_map(x, y)) {
        return;
    }

    switch (action) {
    case Action::Open:
        open(x, y);
        break;
    case Action::Flag:
        flag(x, y);
        break;
    case Action::RemoveFlag:
        remove_flag(x, y);
        break;
    case Action::OpenAround:
        open_around(x, y);
        break;
    }

    if (cells_oppened == set.size_x * set.size_y - (set.mines + 1)) {
        game_state = GameState::win;
    }
}
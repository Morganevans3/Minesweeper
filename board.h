//
// Created by Morgan Evans on 4/10/23.
//

#ifndef PROJECT3_BOARD_H
#define PROJECT3_BOARD_H

#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <map>
using namespace std;



bool time_sort(pair<string, string> const& a, pair<string, string> const& b) {
    if (a.first != b.first) {
        if (a.first.substr(0, 2) != b.first.substr(0, 2)) {
            return a.first.substr(0, 2) < b.first.substr(0, 2);
        }
        else {
            return a.first.substr(3, 2) < b.first.substr(3, 2);
        }
    }
    return a.second < b.second;
}

void leaderboard_window(int columns, int rows, sf::Font font, string player_name, string time, bool finish) {
    vector<pair<string, string>> leaders;
    vector<pair<string, string>> write_leaders;
    string data_line;
    fstream leader_file("files/leaderboard.txt", ios::in);
    while (std::getline(leader_file, data_line)) {
        int comma = data_line.find(',');
        string loaded_time;
        loaded_time = data_line.substr(0, comma);
        string loaded_players = data_line.substr(comma + 1);
        leaders.push_back(make_pair(loaded_time, loaded_players));
        write_leaders.push_back(make_pair(loaded_time, loaded_players));
    }
    string top5 = "";
    sort(leaders.begin(), leaders.end(), time_sort);
    sort(write_leaders.begin(), write_leaders.end(), time_sort);
    if (finish) {
        //ofstream leader_file("files/leaderboard.txt", ios::out);
        //leader_file << endl;
        //leader_file << time << "," << player_name;
        //leader_file.close();
        write_leaders.push_back(make_pair(time, player_name));

        player_name += "*";
        leaders.push_back(make_pair(time, player_name));

        sort(leaders.begin(), leaders.end(), time_sort);
        sort(write_leaders.begin(), write_leaders.end(), time_sort);

        leaders.pop_back();
        write_leaders.pop_back();

    }

    ofstream new_leader("files/leaderboard.txt", ios::out);
    for (auto const& pair : write_leaders) {
        new_leader << pair.first << "," << pair.second << endl;
    }
    new_leader.close();




    int to5 = 1;
    for (auto const& pair : leaders) {
        if (to5 == 6) {
            break;
        }

        top5 += to_string(to5) + ".\t" + pair.first + "\t" + pair.second + "\n\n";
        to5++;
    }



    int wid = columns * 16;
    int hei = rows * 16 + 50;

    sf::RenderWindow window_leaderboard(sf::VideoMode(wid, hei), "Minesweeper");

    sf::Text l_text("LEADERBOARD", font, 20);
    l_text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    l_text.setFillColor(sf::Color::White);
    l_text.setPosition(wid / 2.0f - l_text.getLocalBounds().width / 2, (hei / 2.0f) - 120 - l_text.getLocalBounds().height/2.0f);

    sf::Text leaders_text(top5, font, 18);
    leaders_text.setStyle(sf::Text::Bold);
    leaders_text.setFillColor(sf::Color::White);
    leaders_text.setPosition(wid / 2.0f - leaders_text.getLocalBounds().width / 2, (hei / 2.0f) + 20 - leaders_text.getLocalBounds().height/2.0f);


    while (window_leaderboard.isOpen()) {
        sf::Event event;
        while (window_leaderboard.pollEvent(event)){
            if (event.type == sf::Event::Closed) {
                window_leaderboard.close();
            }

        }
        window_leaderboard.clear(sf::Color::Blue);
        window_leaderboard.draw(l_text);
        window_leaderboard.draw(leaders_text);
        window_leaderboard.display();
    }

}

vector<vector<int>> random_mines(int num_mines, int columns, int rows) {
    vector<int> mines;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, columns * rows - 1);
    std::shuffle(mines.begin(), mines.end(), rd);
    while (mines.size() < num_mines) {
        int position = dist(gen);
        if (find(mines.begin(), mines.end(), position) == mines.end()) {
            mines.push_back(position);
        }
    }

    vector<vector<int>> mines_2D(rows, vector<int>(columns, 0));
    for (int i = 0; i < num_mines; i++) {
        mines_2D[(mines[i] / columns)][(mines[i] % columns)] = 9;
    }
    return mines_2D;
}

vector<vector<int>> complete_mines(vector<vector<int>> mines, int columns, int rows) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (mines[i][j] == 9 | i < 0 | i >= rows | j < 0 | j >= columns) {
                continue;
            }
            if (i == 0 && j == 0) {
                if (mines[i][j+1] == 9) {
                    mines[i][j] += 1;
                }
                if (mines[i+1][j+1] == 9) {
                    mines[i][j] += 1;
                }
                if (mines[i+1][j] == 9) {
                    mines[i][j] += 1;
                }
            }
            else if (i == 0 && j == columns - 1) {
                if (mines[i][j-1] == 9) {
                    mines[i][j] += 1;
                }
                if (mines[i+1][j-1] == 9) {
                    mines[i][j] += 1;
                }
                if (mines[i+1][j] == 9) {
                    mines[i][j] += 1;
                }
            }
            else if (i == rows - 1 && j == 0) {
                if (mines[i][j+1] == 9) {
                    mines[i][j] += 1;
                }
                if (mines[i-1][j+1] == 9) {
                    mines[i][j] += 1;
                }
                if (mines[i-1][j] == 9) {
                    mines[i][j] += 1;
                }
            }
            else if (i == rows - 1 && j == columns - 1) {
                if (mines[i][j-1] == 9) {
                    mines[i][j] += 1;
                }
                if (mines[i-1][j-1] == 9) {
                    mines[i][j] += 1;
                }
                if (mines[i-1][j] == 9) {
                    mines[i][j] += 1;
                }
            }
            else if (i == 0) {
                if (mines[i][j+1] == 9) {
                    mines[i][j] += 1;
                }
                if (mines[i+1][j+1] == 9) {
                    mines[i][j] += 1;
                }
                if (mines[i+1][j] == 9) {
                    mines[i][j] += 1;
                }
                if (mines[i][j-1] == 9) {
                    mines[i][j] += 1;
                }
                if (mines[i+1][j-1] == 9) {
                    mines[i][j] += 1;
                }
            }
            else if (i == rows - 1) {
                if (mines[i][j+1] == 9) {
                    mines[i][j] += 1;
                }
                if (mines[i-1][j+1] == 9) {
                    mines[i][j] += 1;
                }
                if (mines[i-1][j] == 9) {
                    mines[i][j] += 1;
                }
                if (mines[i][j-1] == 9) {
                    mines[i][j] += 1;
                }
                if (mines[i-1][j-1] == 9) {
                    mines[i][j] += 1;
                }
            }
            else if (j == 0) {
                if (mines[i+1][j+1] == 9) {
                    mines[i][j] += 1;
                }
                if (mines[i-1][j+1] == 9) {
                    mines[i][j] += 1;
                }
                if (mines[i][j+1] == 9) {
                    mines[i][j] += 1;
                }
                if (mines[i-1][j] == 9) {
                    mines[i][j] += 1;
                }
                if (mines[i+1][j] == 9) {
                    mines[i][j] += 1;
                }
            }
            else if (j == columns - 1) {
                if (mines[i+1][j-1] == 9) {
                    mines[i][j] += 1;
                }
                if (mines[i-1][j-1] == 9) {
                    mines[i][j] += 1;
                }
                if (mines[i][j-1] == 9) {
                    mines[i][j] += 1;
                }
                if (mines[i-1][j] == 9) {
                    mines[i][j] += 1;
                }
                if (mines[i+1][j] == 9) {
                    mines[i][j] += 1;
                }
            }
            else {
                if (mines[i+1][j-1] == 9) {
                    mines[i][j] += 1;
                }
                if (mines[i-1][j-1] == 9) {
                    mines[i][j] += 1;
                }
                if (mines[i][j-1] == 9) {
                    mines[i][j] += 1;
                }
                if (mines[i-1][j] == 9) {
                    mines[i][j] += 1;
                }
                if (mines[i+1][j] == 9) {
                    mines[i][j] += 1;
                }
                if (mines[i+1][j+1] == 9) {
                    mines[i][j] += 1;
                }
                if (mines[i-1][j+1] == 9) {
                    mines[i][j] += 1;
                }
                if (mines[i][j+1] == 9) {
                    mines[i][j] += 1;
                }
            }
        }
    }
    return mines;
}

vector<vector<int>> no_mines(vector<vector<int>> comp_mines, int columns, int rows, int x, int y) {
    // already know location clicked is 0
    vector<vector<int>> none_touching = comp_mines;
    vector<pair<int, int>> spread_out_check;
    none_touching[y][x] = 10;
    // changed to 10 so that it will be updated as blank tile in if statement
    spread_out_check.push_back(make_pair(x, y));

    while (!spread_out_check.empty()) {
        pair<int, int> curr0 = spread_out_check.back();
        spread_out_check.pop_back();

        int X = curr0.first;
        int Y = curr0.second;

        if (none_touching[Y][X] != 10) {
            continue;
        }

        for (int i = -1; i < 2; i++) {
            for (int j = -1; j < 2; j++) {
                if (X + j < 0 || X + j >= columns || Y + i < 0 || Y + i >= rows) {
                    continue;
                }
                if (none_touching[Y + i][X + j] == 0) {
                    spread_out_check.push_back(make_pair(X + j, Y + i));
                    none_touching[Y + i][X + j] = 10;
                }
                else if (none_touching[Y + i][X + j] < 9) {
                    none_touching[Y + i][X + j] += 10;
                }

            }
        }

    }
    return none_touching;
}


void game_window(int columns, int rows, int num_mines, sf::Font font, string player_name, map<string, sf::Texture> texture_map, map<int, sf::Texture> digits) {
    int width = columns * 32;
    int height = rows * 32 + 100;

    sf::RenderWindow game_window(sf::VideoMode(width, height), "Minesweeper");
/*
    sf::Text welcome_text("WELCOME TO MINESWEEPER!", font, 24);
    welcome_text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    welcome_text.setFillColor(sf::Color::Blue);
    welcome_text.setPosition(0, 0);*/

    bool game_stop = false;
    while (!game_stop) {
        int count = num_mines;
        bool debugging = false;
        bool new_game = false;
        bool paused = false;
        bool winner = false;
        bool loser = false;
        bool neg = false;
        bool leader = false;
        bool winner_window = false;

        string player_time = "";


        sf::Sprite default_tile(texture_map["hidden"]);
        default_tile.setOrigin(0, 0);

        auto start_time = std::chrono::high_resolution_clock::now();
        auto curr_time = std::chrono::high_resolution_clock::now();
        auto pause_time = std::chrono::high_resolution_clock::now();
        auto win_lose_time = std::chrono::duration_cast<std::chrono::seconds>(pause_time - start_time);
        auto not_paused = std::chrono::high_resolution_clock::now();
        auto time_paused = std::chrono::duration_cast<std::chrono::seconds>(not_paused - pause_time);
        //start_time += time_paused;
        auto correct_time = std::chrono::duration_cast<std::chrono::seconds>(curr_time - start_time);





        vector<vector<sf::Sprite>> tiles(rows, vector<sf::Sprite>(columns, default_tile));
        for (int y = 0; y < rows; y++) {
            for (int x = 0; x < columns; x++) {
                tiles[y][x].setPosition(32 * x, 32 * y);
            }
        }
        // tiles [columns][rows]
        vector<vector<sf::Sprite>> changed_tiles;
        changed_tiles = tiles;

        vector<vector<sf::Sprite>> debug_bottom;
        debug_bottom = tiles;

        vector<vector<sf::Sprite>> lose_bottom;
        lose_bottom = tiles;

        vector<vector<sf::Sprite>> paused_tiles;
        paused_tiles = tiles;

        vector<vector<sf::Sprite>> under_flags;
        under_flags = tiles;

        for (int y = 0; y < rows; y++) {
            for (int x = 0; x < columns; x++) {
                paused_tiles[y][x].setTexture(texture_map["revealed"]);
            }
        }

        vector<vector<int>> mines;
        mines = random_mines(num_mines, columns, rows);

        vector<vector<int>> filled_mines;
        filled_mines = complete_mines(mines, columns, rows);



        sf::Sprite happy_face(texture_map["happy"]);
        happy_face.setPosition((columns / 2.0f) * 32 - 32, 32 * (rows + .5f));
        //happy_face.setPosition(0, 0);
        sf::Sprite face = happy_face;

        sf::Sprite win_face(texture_map["win"]);


        sf::Sprite lose_face(texture_map["lose"]);


        //sf::Sprite digits(dig);

        sf::Sprite position1(digits[count / 100]);
        position1.setPosition(33, 32 * (rows + .5f) + 16);
        //position1.setPosition(0, 0);

        sf::Sprite position2(digits[count / 10 % 10]);
        position2.setPosition(54, 32 * (rows + .5f) + 16);
        //position2.setPosition(21, 0);

        sf::Sprite position3(digits[count % 10]);
        position3.setPosition(75, 32 * (rows + .5f) + 16);
        //position3.setPosition(42, 0);

        sf::Sprite position_neg(digits[10]);
        position_neg.setPosition(12, 32 * (rows + .5f) + 16);


        sf::Sprite time1(digits[0]);
        time1.setPosition((columns * 32) - 97, 32 * (rows + .5f) + 16);

        sf::Sprite time2(digits[0]);
        time2.setPosition((columns * 32) - 76, 32 * (rows + .5f) + 16);

        sf::Sprite time3(digits[0]);
        time3.setPosition((columns * 32) - 54, 32 * (rows + .5f) + 16);

        sf::Sprite time4(digits[0]);
        time4.setPosition((columns * 32) - 33, 32 * (rows + .5f) + 16);


        sf::Sprite debug(texture_map["debug"]);
        debug.setPosition(columns * 32 - 304, 32 * (rows + .5f));


        sf::Sprite pause(texture_map["pause"]);
        pause.setPosition(columns * 32 - 240, 32 * (rows + .5f));


        sf::Sprite play(texture_map["play"]);


        sf::Sprite leaderboard(texture_map["leaderboard"]);
        leaderboard.setPosition(columns * 32 - 176, 32 * (rows + .5f));


        while (game_window.isOpen()) {
            sf::Event event;
            while (game_window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    game_window.close();
                    game_stop = true;
                }
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        int X, Y;
                        try {
                            X = event.mouseButton.x / 32;
                            // x = columns * 32 = width
                            Y = event.mouseButton.y / 32;
                        }
                        catch (...){
                            cout << "error";
                        }
                        // y = rows * 32 != height = rows * 32 + 100
                        if (X >= 0 && X < width && Y >= 0 && Y < rows && !winner && !loser && !paused && !debugging) {
                            if (tiles[Y][X].getTexture() == &texture_map["flag"]) {
                                continue;
                            }
                            else if (filled_mines[Y][X] == 0 && tiles[Y][X].getTexture() == &texture_map.at("hidden")) {
                                vector<vector<int>> mines10;
                                mines10 = no_mines(filled_mines, columns, rows, X, Y);
                                for (int y = 0; y < rows; y++) {
                                    for (int x = 0; x < columns; x++) {
                                        if (mines10[y][x] == 10 && tiles[y][x].getTexture() != &texture_map.at("flag")) {
                                            tiles[y][x].setTexture(texture_map["revealed"]);
                                        }
                                        else if (mines10[y][x] > 10 && tiles[y][x].getTexture() != &texture_map.at("flag")) {
                                            tiles[y][x].setTexture(texture_map[to_string(mines10[y][x] % 10)]);
                                        }
                                    }
                                }
                            }
                            else if (filled_mines[Y][X] == 1 && tiles[Y][X].getTexture() == &texture_map.at("hidden")) {
                                tiles[Y][X].setTexture(texture_map["1"]);
                            }

                            else if (filled_mines[Y][X] == 2 && tiles[Y][X].getTexture() == &texture_map.at("hidden")) {
                                tiles[Y][X].setTexture(texture_map["2"]);
                            }

                            else if (filled_mines[Y][X] == 3 && tiles[Y][X].getTexture() == &texture_map.at("hidden")) {
                                tiles[Y][X].setTexture(texture_map["3"]);
                            }

                            else if (filled_mines[Y][X] == 4 && tiles[Y][X].getTexture() == &texture_map.at("hidden")) {
                                tiles[Y][X].setTexture(texture_map["4"]);
                            }

                            else if (filled_mines[Y][X] == 5 && tiles[Y][X].getTexture() == &texture_map.at("hidden")) {
                                tiles[Y][X].setTexture(texture_map["5"]);
                            }

                            else if (filled_mines[Y][X] == 6 && tiles[Y][X].getTexture() == &texture_map.at("hidden")) {
                                tiles[Y][X].setTexture(texture_map["6"]);
                            }

                            else if (filled_mines[Y][X] == 7 && tiles[Y][X].getTexture() == &texture_map.at("hidden")) {
                                tiles[Y][X].setTexture(texture_map["7"]);
                            }

                            else if (filled_mines[Y][X] == 8 && tiles[Y][X].getTexture() == &texture_map.at("hidden")) {
                                tiles[Y][X].setTexture(texture_map["8"]);
                            }

                            else if (filled_mines[Y][X] == 9 && tiles[Y][X].getTexture() == &texture_map.at("hidden")) {
                                lose_bottom = tiles;
                                changed_tiles = tiles;
                                for (int y = 0; y < rows; y++) {
                                    for (int x = 0; x < columns; x++) {
                                        if (filled_mines[y][x] == 9) {
                                            //changed_tiles[y][x].setTexture(texture_map["hidden"]);
                                            changed_tiles[y][x].setTexture(texture_map["mine_image"]);

                                        }
                                    }
                                }
                                loser = true;
                                pause_time = std::chrono::high_resolution_clock::now();
                                win_lose_time = std::chrono::duration_cast<std::chrono::seconds>(pause_time - start_time);
                                //curr_time = std::chrono::high_resolution_clock::now();
                                //elapsed += curr_time - start_time;
                                face.setTexture(texture_map["lose"]);

                            }
                            if (count < 0) {
                                break;
                            }
                            bool cont = false;
                            for (int y = 0; y < rows; y++) {
                                for (int x = 0; x < columns; x++) {
                                    if (filled_mines[y][x] == 9) {
                                        continue;
                                    }
                                    else if (tiles[y][x].getTexture() == &texture_map["hidden"] || tiles[y][x].getTexture() == &texture_map["flag"]) {
                                        cont = true;
                                        winner = false;
                                        break;
                                    }
                                    winner = true;
                                }
                                if (cont) {
                                    winner = false;
                                    break;
                                }
                            }
                            if (winner) {
                                for (int y = 0; y < rows; y++) {
                                    for (int x = 0; x < columns; x++) {
                                        if (filled_mines[y][x] == 9) {
                                            tiles[y][x].setTexture(texture_map["flag"]);
                                        }
                                    }
                                }

                                face.setTexture(texture_map["win"]);
                                pause_time = std::chrono::high_resolution_clock::now();
                                win_lose_time = std::chrono::duration_cast<std::chrono::seconds>(pause_time - start_time);
                                //curr_time = std::chrono::high_resolution_clock::now();
                                //elapsed += curr_time - start_time;
                                player_time = "";
                                int win_time = win_lose_time.count();
                                player_time += to_string(win_time / 600);
                                player_time += to_string(win_time % 600 / 60);
                                player_time += ":";
                                player_time += to_string(win_time % 60 / 10);
                                player_time += to_string(win_time % 10);

                                winner_window = true;

                            }



                        }


                        if (float(event.mouseButton.x) > (columns / 2.0f) * 32 - 32 && float(event.mouseButton.x) < (columns / 2.0f) * 32 + 32 && float(event.mouseButton.y) > 32 * (rows + .5f) && float(event.mouseButton.y && !paused && !debugging) < 32 * (rows + .5f) + 64) {
                            // face
                            new_game = true;
                            break;
                        }
                        if (float(event.mouseButton.x) > columns * 32 - 304 && float(event.mouseButton.x) < columns * 32 - 240 && float(event.mouseButton.y) > 32 * (rows + .5f) && float(event.mouseButton.y) < 32 * (rows + .5f) + 64 && !winner && !loser && !paused) {
                            //debug
                            if (!debugging) {
                                pause_time = std::chrono::high_resolution_clock::now();

                                //curr_time = std::chrono::high_resolution_clock::now();
                                //elapsed += std::chrono::high_resolution_clock::now() - start_time;

                                debug_bottom = tiles;
                                changed_tiles = tiles;
                                for (int y = 0; y < rows; y++) {
                                    for (int x = 0; x < columns; x++) {
                                        if (filled_mines[y][x] == 9) {
                                            //changed_tiles[y][x].setTexture(texture_map["hidden"]);
                                            changed_tiles[y][x].setTexture(texture_map["mine_image"]);

                                        }
                                    }
                                }
                                debugging = true;
                            }
                            else {
                                //start_time = std::chrono::high_resolution_clock::now();
                                not_paused = std::chrono::high_resolution_clock::now();
                                time_paused = std::chrono::duration_cast<std::chrono::seconds>(not_paused - pause_time);
                                start_time += time_paused;
                                debugging = false;
                            }
                        }
                        if (float(event.mouseButton.x) > columns * 32 - 176 && float(event.mouseButton.x) < columns * 32 - 112 && float(event.mouseButton.y) > 32 * (rows + .5f) && float(event.mouseButton.y) < 32 * (rows + .5f) + 64) {
                            // leaderboard

                            pause_time = std::chrono::high_resolution_clock::now();

                            for (int i = 0; i < rows; i++) {
                                for (int j = 0; j < columns; j++) {
                                    game_window.draw(paused_tiles[i][j]);
                                }
                            }
                            leader = true;



                        }
                        if (float(event.mouseButton.x) > columns * 32 - 240 && float(event.mouseButton.x) < columns * 32 - 176 && float(event.mouseButton.y) > 32 * (rows + .5f) && float(event.mouseButton.y) < 32 * (rows + .5f) + 64 && !winner && !loser && !debugging) {
                            // pause / play
                            if (!paused) {
                                paused = true;
                                pause.setTexture(texture_map["play"]);
                                pause_time = std::chrono::high_resolution_clock::now();
                                //curr_time = std::chrono::high_resolution_clock::now();
                                //elapsed += curr_time - start_time;

                            }
                            else {
                                paused = false;
                                pause.setTexture(texture_map["pause"]);
                                not_paused = std::chrono::high_resolution_clock::now();
                                time_paused = std::chrono::duration_cast<std::chrono::seconds>(not_paused - pause_time);
                                start_time += time_paused;
                                //start_time = std::chrono::high_resolution_clock::now();
                            }
                        }


                    }
                    if (event.mouseButton.button == sf::Mouse::Right) {
                        int X = event.mouseButton.x / 32;
                        // x = columns * 32 = width
                        int Y = event.mouseButton.y / 32;
                        // y = rows * 32 != height = rows * 32 + 100
                        if (X >= 0 && X < width && Y >= 0 && Y < rows && !winner && !loser && !paused && !debugging) {
                            if (tiles[Y][X].getTexture() == &texture_map.at("hidden")) {
                                tiles[Y][X].setTexture(texture_map["flag"]);
                                count -= 1;
                                if (count < 0) {
                                    neg = true;
                                }
                            }
                            else if (tiles[Y][X].getTexture() == &texture_map.at("flag")){
                                count += 1;
                                if (count >= 0) {
                                    neg = false;
                                }

                                tiles[Y][X].setTexture(texture_map["hidden"]);
                            }

                            if (count < 0) {
                                break;
                            }

                            bool cont = false;
                            for (int y = 0; y < rows; y++) {
                                for (int x = 0; x < columns; x++) {
                                    if (filled_mines[y][x] == 9) {
                                        //checks if it is mine
                                        continue;
                                    }
                                    //this statement could not possibly have a mine!!
                                    else if (tiles[y][x].getTexture() == &texture_map["hidden"] || tiles[y][x].getTexture() == &texture_map["flag"]) {
                                        cont = true;
                                        winner = false;
                                        break;
                                    }
                                    winner = true;
                                }
                                if (cont) {
                                    winner = false;
                                    break;
                                }
                            }
                            if (winner) {
                                for (int y = 0; y < rows; y++) {
                                    for (int x = 0; x < columns; x++) {
                                        if (filled_mines[y][x] == 9) {
                                            tiles[y][x].setTexture(texture_map["flag"]);
                                        }
                                    }
                                }
                                face.setTexture(texture_map["win"]);
                                pause_time = std::chrono::high_resolution_clock::now();
                                win_lose_time = std::chrono::duration_cast<std::chrono::seconds>(pause_time - start_time);
                                //curr_time = std::chrono::high_resolution_clock::now();
                                //elapsed += curr_time - start_time;
                                player_time = "";
                                int win_time = win_lose_time.count();
                                player_time += to_string(win_time / 600);
                                player_time += to_string(win_time % 600 / 60);
                                player_time += ":";
                                player_time += to_string(win_time % 60 / 10);
                                player_time += to_string(win_time % 10);
                            }
                        }
                    }
                }
                if (new_game) {
                    break;
                }


            }

            if (new_game) {
                break;
            }

            for (int y = 0; y < rows; y++) {
                for (int x = 0; x < columns; x++) {
                    if (tiles[y][x].getTexture() == &texture_map["flag"]) {
                        under_flags[y][x].setTexture(texture_map["hidden"]);
                    }
                    else {
                        under_flags[y][x].setTexture(texture_map["revealed"]);
                    }
                }
            }

            game_window.clear(sf::Color::White);
            if (winner) {
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < columns; j++) {
                        game_window.draw(under_flags[i][j]);
                        game_window.draw(tiles[i][j]);
                    }
                }
                vector<int> player_finish;
                for (char i : player_time) {
                    if (isdigit(i)) {
                        int value = i - '0';
                        player_finish.push_back(value);
                    }
                }

                time1.setTexture(digits[player_finish[0]]);
                time2.setTexture(digits[player_finish[1]]);
                time3.setTexture(digits[player_finish[2]]);
                time4.setTexture(digits[player_finish[3]]);

                position1.setTexture(digits[0]);

                position2.setTexture(digits[0]);

                position3.setTexture(digits[0]);
            }
            else if (loser) {
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < columns; j++) {
                        game_window.draw(under_flags[i][j]);
                        game_window.draw(lose_bottom[i][j]);

                        game_window.draw(changed_tiles[i][j]);
                    }
                }

                time1.setTexture(digits[win_lose_time.count() / 600]);
                time2.setTexture(digits[win_lose_time.count() % 600 / 60]);
                time3.setTexture(digits[win_lose_time.count() % 60 / 10]);
                time4.setTexture(digits[win_lose_time.count() % 10]);
                /*
                time1.setTexture(digits[elapsed.count() / 600]);
                time2.setTexture(digits[elapsed.count() % 600 / 60]);
                time3.setTexture(digits[elapsed.count() % 60 / 10]);
                time4.setTexture(digits[elapsed.count() % 10]);*/
            }
            else if (leader) {
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < columns; j++) {
                        game_window.draw(paused_tiles[i][j]);
                    }
                }


            }
            else if (!debugging && !paused) {

                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < columns; j++) {
                        game_window.draw(under_flags[i][j]);

                        game_window.draw(tiles[i][j]);
                    }
                }
                curr_time = std::chrono::high_resolution_clock::now();
                correct_time = std::chrono::duration_cast<std::chrono::seconds>(curr_time - start_time);

                time1.setTexture(digits[correct_time.count() / 600]);
                time2.setTexture(digits[correct_time.count() % 600 / 60]);
                time3.setTexture(digits[correct_time.count() % 60 / 10]);
                time4.setTexture(digits[correct_time.count() % 10]);
                /*
                curr_time = std::chrono::high_resolution_clock::now();
                elapsed += curr_time - start_time;
                time1.setTexture(digits[elapsed.count() / 600]);
                time2.setTexture(digits[elapsed.count() % 600 / 60]);
                time3.setTexture(digits[elapsed.count() % 60 / 10]);
                time4.setTexture(digits[elapsed.count() % 10]);*/
            }
            else if (paused) {
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < columns; j++) {
                        game_window.draw(paused_tiles[i][j]);
                    }
                }

                correct_time = std::chrono::duration_cast<std::chrono::seconds>(pause_time - start_time);

                time1.setTexture(digits[correct_time.count() / 600]);
                time2.setTexture(digits[correct_time.count() % 600 / 60]);
                time3.setTexture(digits[correct_time.count() % 60 / 10]);
                time4.setTexture(digits[correct_time.count() % 10]);
                /*
                time1.setTexture(digits[elapsed.count() / 600]);
                time2.setTexture(digits[elapsed.count() % 600 / 60]);
                time3.setTexture(digits[elapsed .count() % 60 / 10]);
                time4.setTexture(digits[elapsed.count() % 10]);*/

            }
            else if (debugging){
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < columns; j++) {
                        game_window.draw(under_flags[i][j]);
                        //game_window.draw(debug_bottom[i][j]);
                        game_window.draw(tiles[i][j]);
                        game_window.draw(changed_tiles[i][j]);
                    }
                }
                correct_time = std::chrono::duration_cast<std::chrono::seconds>(pause_time - start_time);

                time1.setTexture(digits[correct_time.count() / 600]);
                time2.setTexture(digits[correct_time.count() % 600 / 60]);
                time3.setTexture(digits[correct_time.count() % 60 / 10]);
                time4.setTexture(digits[correct_time.count() % 10]);
                /*
                time1.setTexture(digits[elapsed.count() / 600]);
                time2.setTexture(digits[elapsed.count() % 600 / 60]);
                time3.setTexture(digits[elapsed.count() % 60 / 10]);
                time4.setTexture(digits[elapsed.count() % 10]);*/
            }

            if (neg) {
                game_window.draw(position_neg);

                int made_pos = count * (-1);

                position1.setTexture(digits[made_pos / 100]);

                position2.setTexture(digits[made_pos / 10 % 10]);

                position3.setTexture(digits[made_pos % 10]);
            }
            else if (!neg && !winner) {
                position1.setTexture(digits[count / 100]);

                position2.setTexture(digits[count / 10 % 10]);

                position3.setTexture(digits[count % 10]);
            }


            game_window.draw(time1);
            game_window.draw(time2);
            game_window.draw(time3);
            game_window.draw(time4);


            game_window.draw(face);
            game_window.draw(debug);
            game_window.draw(pause);
            game_window.draw(leaderboard);
            game_window.draw(position1);
            game_window.draw(position2);
            game_window.draw(position3);
            //game_window.draw(welcome_text);
            game_window.display();
            if (leader) {
                leaderboard_window(columns, rows, font, player_name, "00:00", false);

                not_paused = std::chrono::high_resolution_clock::now();
                time_paused = std::chrono::duration_cast<std::chrono::seconds>(not_paused - pause_time);
                start_time += time_paused;
                leader = false;

                curr_time = std::chrono::high_resolution_clock::now();
                correct_time = std::chrono::duration_cast<std::chrono::seconds>(curr_time - start_time);

                time1.setTexture(digits[correct_time.count() / 600]);
                time2.setTexture(digits[correct_time.count() % 600 / 60]);
                time3.setTexture(digits[correct_time.count() % 60 / 10]);
                time4.setTexture(digits[correct_time.count() % 10]);
            }
            if (winner_window) {
                leaderboard_window(columns, rows, font, player_name, player_time, true);
                winner_window = false;
            }

        }
        if (new_game) {
            continue;
        }
    }


}


#endif //PROJECT3_BOARD_H
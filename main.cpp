
#include <iostream>
#include <SFML/Graphics.hpp>
#include "welcome_window.h"
#include "board.h"

using namespace std;


int main()
{
    sf::Font font;
    font.loadFromFile("files/font.ttf");


    fstream file("files/board_config.cfg", ios_base::in);
    string col;
    std::getline(file, col);
    string row;
    std::getline(file, row);
    int columns = stoi(col);
    int rows = stoi(row);
    string num_mine;
    std::getline(file, num_mine);
    int num_mines = stoi(num_mine);
    //test(columns, rows, font);
    string player = "name";
    player = welcome_window(columns, rows, font);

    if (player == "0") {
        return 1;
    }
    //cout << player;
/*
    vector<vector<int>> mines;
    mines = random_mines(2, 4, 5);
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 4; j++) {
            cout << mines[i][j] << "  ";
        }
        cout << endl;
    }
    cout << endl;
    vector<vector<int>> mines_numbers;
    mines_numbers = complete_mines(mines, 4, 5);
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 4; j++) {
            cout << mines_numbers[i][j] << "  ";
        }
        cout << endl;
    }

    cout << endl;
    vector<vector<int>> touching;
    touching = no_mines(mines_numbers, 4, 5, 1, 3);
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 4; j++) {
            cout << touching[i][j] << "  ";
        }
        cout << endl;
    }
*/

    map<string, sf::Texture> textured_map;

    sf::Texture mine_image;
    mine_image.loadFromFile("files/images/mine.png");
    mine_image.setSmooth(true);
    mine_image.setRepeated(false);
    textured_map.emplace("mine_image", mine_image);

    sf::Texture flag;
    flag.loadFromFile("files/images/flag.png");
    textured_map.emplace("flag", flag);

    sf::Texture tile_hide;
    tile_hide.loadFromFile("files/images/tile_hidden.png");
    textured_map.emplace("hidden", tile_hide);

    sf::Texture tile_rev;
    tile_rev.loadFromFile("files/images/tile_revealed.png");
    textured_map.emplace("revealed", tile_rev);

    sf::Texture num_1;
    num_1.loadFromFile("files/images/number_1.png");
    textured_map.emplace("1", num_1);

    sf::Texture num_2;
    num_2.loadFromFile("files/images/number_2.png");
    textured_map.emplace("2", num_2);

    sf::Texture num_3;
    num_3.loadFromFile("files/images/number_3.png");
    textured_map.emplace("3", num_3);

    sf::Texture num_4;
    num_4.loadFromFile("files/images/number_4.png");
    textured_map.emplace("4", num_4);

    sf::Texture num_5;
    num_5.loadFromFile("files/images/number_5.png");
    textured_map.emplace("5", num_5);

    sf::Texture num_6;
    num_6.loadFromFile("files/images/number_6.png");
    textured_map.emplace("6", num_6);

    sf::Texture num_7;
    num_7.loadFromFile("files/images/number_7.png");
    textured_map.emplace("7", num_7);

    sf::Texture num_8;
    num_8.loadFromFile("files/images/number_8.png");
    textured_map.emplace("8", num_8);

    sf::Texture face_happy;
    face_happy.loadFromFile("files/images/face_happy.png");
    textured_map.emplace("happy", face_happy);

    sf::Texture face_win;
    face_win.loadFromFile("files/images/face_win.png");
    textured_map.emplace("win", face_win);

    sf::Texture face_lose;
    face_lose.loadFromFile("files/images/face_lose.png");
    textured_map.emplace("lose", face_lose);



    sf::Texture debug_image;
    debug_image.loadFromFile("files/images/debug.png");
    textured_map.emplace("debug", debug_image);

    sf::Texture pause_image;
    pause_image.loadFromFile("files/images/pause.png");
    textured_map.emplace("pause", pause_image);

    sf::Texture play_image;
    play_image.loadFromFile("files/images/play.png");
    textured_map.emplace("play", play_image);

    sf::Texture leaderboard_image;
    leaderboard_image.loadFromFile("files/images/leaderboard.png");
    sf::Sprite leaderboard(leaderboard_image);
    textured_map.emplace("leaderboard", leaderboard_image);

    map<int, sf::Texture> digit_map;

    sf::Texture d0;
    d0.loadFromFile("files/images/digits.png", sf::IntRect(0, 0, 21, 32));
    digit_map.emplace(0, d0);

    sf::Texture d1;
    d1.loadFromFile("files/images/digits.png", sf::IntRect(21, 0, 21, 32));
    digit_map.emplace(1, d1);

    sf::Texture d2;
    d2.loadFromFile("files/images/digits.png", sf::IntRect(42, 0, 21, 32));
    digit_map.emplace(2, d2);

    sf::Texture d3;
    d3.loadFromFile("files/images/digits.png", sf::IntRect(63, 0, 21, 32));
    digit_map.emplace(3, d3);

    sf::Texture d4;
    d4.loadFromFile("files/images/digits.png", sf::IntRect(84, 0, 21, 32));
    digit_map.emplace(4, d4);

    sf::Texture d5;
    d5.loadFromFile("files/images/digits.png", sf::IntRect(105, 0, 21, 32));
    digit_map.emplace(5, d5);

    sf::Texture d6;
    d6.loadFromFile("files/images/digits.png", sf::IntRect(126, 0, 21, 32));
    digit_map.emplace(6, d6);

    sf::Texture d7;
    d7.loadFromFile("files/images/digits.png", sf::IntRect(147, 0, 21, 32));
    digit_map.emplace(7, d7);

    sf::Texture d8;
    d8.loadFromFile("files/images/digits.png", sf::IntRect(168, 0, 21, 32));
    digit_map.emplace(8, d8);

    sf::Texture d9;
    d9.loadFromFile("files/images/digits.png", sf::IntRect(189, 0, 21, 32));
    digit_map.emplace(9, d9);

    sf::Texture d10;
    d10.loadFromFile("files/images/digits.png", sf::IntRect(210, 0, 21, 32));
    digit_map.emplace(10, d10);




    game_window(columns, rows, num_mines, font, player, textured_map, digit_map);
    //test(columns, rows, font);


    return 0;
}
//
// Created by Morgan Evans on 4/10/23.
//

#ifndef PROJECT3_WELCOME_WINDOW_H
#define PROJECT3_WELCOME_WINDOW_H

#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <random>
#include <algorithm>

using namespace std;

string change_char(string input_name) {
    input_name[0] = std::toupper(input_name[0]);
    for (int i = 1; i < input_name.length(); i++) {
        input_name[i] = std::tolower(input_name[i]);
    }
    return input_name;
}


string welcome_window(int columns, int rows, sf::Font font) {
    int width = columns * 32;
    int height = rows * 32 + 100;

    sf::RenderWindow window(sf::VideoMode(width, height), "Minesweeper");
    window.clear(sf::Color::Blue);

    sf::Text welcome_text("WELCOME TO MINESWEEPER!", font, 24);
    welcome_text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    welcome_text.setFillColor(sf::Color::White);
    //float new_width = width / 2.0f;
    //float new_height = height / 2.0f - 150;
    //welcome_text.setPosition(new_width, new_height);
    welcome_text.setPosition(width/2.0f - welcome_text.getLocalBounds().width/2.0f, height/2.0f - 150 - welcome_text.getLocalBounds().height/2.0f);
    //welcome_text.setPosition(0, 0);

    sf::Text input_prompt("Enter your name:", font, 20);
    input_prompt.setStyle(sf::Text::Bold);
    input_prompt.setFillColor(sf::Color::White);
    //new_height += 75.0f;
    //welcome_text.setPosition(new_width, new_height);
    input_prompt.setPosition(width/2.0f - input_prompt.getLocalBounds().width/2.0f, height/2.0f - 75 - input_prompt.getLocalBounds().height/2.0f);


    sf::Text input_name("|", font, 18);
    input_name.setStyle(sf::Text::Bold);
    input_name.setFillColor(sf::Color::Yellow);
    //new_height += 30.0f;
    //input_name.setPosition(new_width, new_height);
    input_name.setPosition(width/2.0f - input_name.getLocalBounds().width/2.0f, height/2.0f - input_name.getLocalBounds().height/2.0f);


    string player = "";


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed) {
                window.close();
                return "0";
            }
            if (event.type == sf::Event::TextEntered) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace) && player.size() > 0) {
                    string new_str = input_name.getString().substring(0, input_name.getString().getSize() - 2);
                    player = new_str;
                    //what about empty strings
                }
                if (isalpha(event.text.unicode) && player.size() < 10) {
                    player += static_cast<char>(event.text.unicode);

                }
                input_name.setString(player + "|");

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && player.size() > 0) {
                    player = change_char(player);
                    window.close();
                    return player;
                }
                input_name.setPosition(width/2 - input_name.getLocalBounds().width/2, height/2);
            }


        }
        window.clear(sf::Color::Blue);
        window.draw(welcome_text);
        window.draw(input_prompt);
        window.draw(input_name);
        window.display();
    }
    return player;

}
#endif //PROJECT3_WELCOME_WINDOW_H
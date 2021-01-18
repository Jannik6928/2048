#include <iostream>
#include <sstream>

#include "Board.h"

#include <SFML/Graphics.hpp>

using namespace std;

int main() {

    srand(time(0));

    sf::RenderWindow window(sf::VideoMode(800, 500), "Rainbow 2048!");
    sf::RectangleShape background(sf::Vector2f(800, 500));
    background.setFillColor(sf::Color(210, 180, 140));

    window.setFramerateLimit(30);

    //----------------------------------------//

    Board board(4, 4);

    map<int, sf::Color> rand_map;
    for (int i = 0; i < 32; i++) {
        rand_map.insert(pair<int, sf::Color>(pow(2, i), sf::Color(rand() % 128 + 128, rand() % 128 + 128, rand() % 128 + 128)));
    }
    rand_map.insert(pair<int, sf::Color>(0, sf::Color::White));

    board.set_colors(sf::Color::Black, rand_map);
    board.set_edge_length(100);
    board.set_position(50, 50);

    sf::Font sansation;
    if (!sansation.loadFromFile("sansation.ttf")) {
        cout << "couldn't load text resources" << endl;
    };
    board.set_font(sansation);

    board.reset();
    board.add();

    //----------------------------------------//

    sf::View view;

    

    sf::Text score_label;
    score_label.setFont(sansation);
    score_label.setFillColor(sf::Color::Black);
    score_label.setString("Score: " + to_string(board.score()));
    score_label.setCharacterSize(40);
    score_label.setPosition(500, 100);

    sf::Text directions;
    directions.setFont(sansation);
    directions.setFillColor(sf::Color::Black);
    directions.setString("Use the arrow keys to move.\nPress 'm' to reset.");
    directions.setCharacterSize(20);
    directions.setPosition(500, 150);

    while (window.isOpen())
    {
        view.setSize(sf::Vector2f(window.getSize()));
        view.setCenter(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));

        background.setSize(sf::Vector2f(window.getSize()));


        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) {
            case (sf::Event::Closed): {
                window.close();
                break;
            }
            case (sf::Event::KeyPressed): {
                switch (event.key.code) {

                case (sf::Keyboard::Up): {
                    board.update(Direction::Up);
                    break;
                }
                case (sf::Keyboard::Left): {
                    board.update(Direction::Left);
                    break;
                }
                case (sf::Keyboard::Down): {
                    board.update(Direction::Down);
                    break;
                }
                case (sf::Keyboard::Right): {
                    board.update(Direction::Right);
                    break;
                }
                case (sf::Keyboard::M): {
                    board.reset();
                    board.add();

                    for (int i = 0; i < 32; i++) {
                        rand_map.insert_or_assign(pow(2, i), sf::Color(rand() % 128 + 128, rand() % 128 + 128, rand() % 128 + 128));
                    }
                    rand_map.insert_or_assign(0, sf::Color::White);

                    board.set_colors(sf::Color::Black, rand_map);

                    break;
                }
                case(sf::Keyboard::Escape): {
                    window.close();
                    break;
                }

                }
                break;
            }

            }
        }

        window.clear();

        vector<sf::Shape*> sprites;
        vector<sf::Text*> text;

        vector<sf::Shape*> board_sprites = board.sprites();
        sprites.insert(sprites.end(), board_sprites.begin(), board_sprites.end());

        vector<sf::Text*> board_text = board.text();
        text.insert(text.end(), board_text.begin(), board_text.end());

        window.setView(view);

        window.draw(background);

        for (auto spr : sprites) {
            window.draw(*spr);
        }

        for (auto tx : text) {
            window.draw(*tx);
        }

        score_label.setString("Score: " + to_string(board.score()));
        window.draw(score_label);
        window.draw(directions);

        window.display();

    }

}
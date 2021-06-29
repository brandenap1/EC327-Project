// Copyright 2021 Branden Applewhite bja955@bu.edu | Chris Gough cwgough@bu.edu



#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <ctime>
#include <string>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>

using std::string;
using std::to_string;


int main() {

    // window
    sf::RenderWindow window(sf::VideoMode(810, 1080), "bja955@bu.edu | cwgough@bu.edu");

    // border
    sf::Vector2f borderSize;
    float borderEndx = 40.f;
    float borderEndy = 40.f;
    borderSize.x = window.getSize().x - 80;
    borderSize.y = window.getSize().y - 80;
    sf::RectangleShape gameBorder(sf::Vector2f(borderSize.x,borderSize.y));
    gameBorder.setPosition(borderEndx, borderEndy);
    gameBorder.setFillColor(sf::Color::Black);
    gameBorder.setOutlineThickness(5);
    gameBorder.setOutlineColor(sf::Color::White);

    // sprite
    sf::Texture spritesheet;
    spritesheet.loadFromFile("charspritescropped.png");
    sf::IntRect SourceSprite(0,0, 210, 200);
    sf::Sprite sprite(spritesheet,SourceSprite);
    sprite.setScale(0.8,0.8);

    // ???
    sf::Clock clock;
    // Animation charanimation(spritesheet, sf::Vector2u(6,0), 0.3f);
    std::cout.precision(18);
    char direction = 'f';

    // point counter
    // border
    sf::RectangleShape pointCounter(sf::Vector2f(100, 50));
    pointCounter.setPosition(660, 50);
    pointCounter.setFillColor(sf::Color::Black);
    pointCounter.setOutlineThickness(5);
    pointCounter.setOutlineColor(sf::Color::White);
    // points
    sf::Font font;
    font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf");
    sf::Text points;
    points.setFont(font);
    points.setCharacterSize(40);
    points.setFillColor(sf::Color::Red);
    points.setOrigin(30, 20);
    points.setPosition(735, 70);

    while (window.isOpen())
    {

        //Character moves
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            sprite.move(2.f,0.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            sprite.move(-2.f,0.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            sprite.move(0.f,-2.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            sprite.move(0.f,2.f);
        }

        //Border Collisions
        if (sprite.getPosition().x <=  borderEndx) {
            sprite.move(2.f,0.f);
        }
        if (sprite.getPosition().y <= borderEndy ) {
            sprite.move(0.f,2.f);
        }
        if (sprite.getPosition().x + sprite.getLocalBounds().width >= borderSize.x ) {
            sprite.move(-2.f,0.f);
        }
        if (sprite.getPosition().y + sprite.getLocalBounds().height >= borderSize.y ) {
            sprite.move(0.f,-2.f);
        }


        //     case time 
        if (clock.getElapsedTime().asSeconds() > 0.1f) {
            if(SourceSprite.left == 1050) {
                // SourceSprite.left -= 210;
                // direction = 'b';
                SourceSprite.left = 0;
            }
            else {
                // if(direction == 'f') {
                // SourceSprite.left += 210;
                // }
                // else if (direction == 'b') {
                //     if(SourceSprite.left == 0){
                        SourceSprite.left += 210;
            //             direction = 'f';
            //         }
            //         SourceSprite.left -= 210;
            //     }
            }

            
            sprite.setTextureRect(SourceSprite);
            clock.restart();
        }

        // adding points
        int collisions = 0;
        // if (borders_collide == true)
        //   collisions += (amount of points)
        string numpoints = to_string(collisions);
        if (numpoints.size() < 2)
            numpoints = "0" + numpoints;
        points.setString(numpoints);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // left foot full extension
             sf::IntRect lffe(0,0, 200, 200);
             sf::Sprite charmove1(spritesheet,lffe);
             // left foot half extension
             sf::IntRect lfhe(220, 0, 210, 200);
             sf::Sprite charmove2(spritesheet,lfhe);
             // right foot forward
             sf::IntRect rff(415,0, 210, 200);
             sf::Sprite charmove3(spritesheet,rff);
             // right foot half extension
             sf::IntRect rfhe(645,0, 210, 200);
             sf::Sprite charmove4(spritesheet,rfhe);
             // right foot full extension
             sf::IntRect rffe(870,0, 210, 200);
             sf::Sprite charmove5(spritesheet,rffe);
             // Idle
             sf::IntRect idle(1090,0, 210, 200);
             sf::Sprite charmove6(spritesheet, idle);
        }
     
        //draw sprites  
        window.clear(); 
        window.draw(gameBorder);
        window.draw(pointCounter);
        window.draw(sprite);
        window.draw(points);
        window.display();
    }
    return 0;
}

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

using std::cout; //Used for displaying time info in terminal 
using std::cin;  //Adjusting time
using std::string; //temps for time info


int main() {

    sf::RenderWindow window(sf::VideoMode(810, 1080), "bja955@bu.edu | cwgough@bu.edu");
    sf::Vector2f borderSize;
    float borderEndx = 80.f;
    float borderEndy = 80.f;
    borderSize.x = window.getSize().x - 160;
    borderSize.y = window.getSize().y - 160;

    //spritesheet for char animations
    sf::Texture spritesheet;
    spritesheet.loadFromFile("charspritescropped.png");
    sf::IntRect SourceSprite(0,0, 210, 200);
    sf::Sprite sprite(spritesheet,SourceSprite);
    sprite.setPosition(310,1000);
    sprite.setScale(0.8,0.8);
    //spritesheet for game items
    sf::Texture itemsheet;
    itemsheet.loadFromFile("itemsspritesheetcropped.png");


    //Items to be moved
    // //clock item
    sf::IntRect itemSourceSprite(30,185,90,90);
    // //heart item
    // sf::IntRect itemSourceSprite(145,185,90,90);
    // //boulder item
    // sf::IntRect itemSourceSprite(620,185,110,110);
    // //stump item
    // sf::IntRect itemSourceSprite(760,185,110,110);
    //red scroll item (least points - slowest)
    // sf::IntRect itemSourceSprite(920,175,70,105);
    // //green scroll item (more points - faster)
    // sf::IntRect itemSourceSprite(1005,175,70,105);
    // //yellow scroll item (most points - fastest)
    // sf::IntRect itemSourceSprite(1090,175,70,105);
    
    sf::Sprite itemsprite(itemsheet,itemSourceSprite);


    //dimensions for gamescreen border
    sf::RectangleShape gameBorder(sf::Vector2f(borderSize.x,borderSize.y));
    gameBorder.setPosition(borderEndx, borderEndy);
    gameBorder.setFillColor(sf::Color::Black);
    gameBorder.setOutlineThickness(5);
    gameBorder.setOutlineColor(sf::Color::White);
    //time for animation trigger
    sf::Clock clock;
    std::cout.precision(18);
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
        if (sprite.getPosition().x + sprite.getLocalBounds().width >= window.getSize().x ) {
            sprite.move(-2.f,0.f);
        }
        if (sprite.getPosition().y + sprite.getLocalBounds().height >= window.getSize().y ) {
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

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
     
        //draw sprites  
        window.clear(); 
        window.draw(gameBorder); 
        window.draw(itemsprite); 
        window.draw(sprite);
        window.display();
    }
    return 0;
}

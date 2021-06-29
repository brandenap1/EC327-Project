// Copyright 2021 Branden Applewhite bja955@bu.edu



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

    sf::RenderWindow window(sf::VideoMode(810, 1080), "bja955@bu.edu");
    sf::Vector2f borderSize;
    float borderEndx = 40.f;
    float borderEndy = 40.f;
    borderSize.x = window.getSize().x - 80;
    borderSize.y = window.getSize().y - 80;
    sf::Texture spritesheet;
    sf::RectangleShape gameBorder(sf::Vector2f(borderSize.x,borderSize.y));
    gameBorder.setPosition(borderEndx, borderEndy);
    gameBorder.setFillColor(sf::Color::Black);
    gameBorder.setOutlineThickness(5);
    gameBorder.setOutlineColor(sf::Color::White);
    spritesheet.loadFromFile("charspritescropped.png");
    sf::IntRect SourceSprite(0,0, 210, 200);
    sf::Sprite sprite(spritesheet,SourceSprite);
    sf::Clock clock;
    // Animation charanimation(spritesheet, sf::Vector2u(6,0), 0.3f);
    std::cout.precision(18);
    char direction = 'f';
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
        //draw sprites  
        window.clear(); 
        window.draw(gameBorder);  
        window.draw(sprite);
        window.display();
    }
    return 0;
}

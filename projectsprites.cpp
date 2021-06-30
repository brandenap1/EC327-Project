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

    // dimensions for gamescreen border
    sf::Vector2f borderSize;
    float borderEndx = 80.f;
    float borderEndy = 80.f;
    borderSize.x = window.getSize().x - 160;
    borderSize.y = window.getSize().y - 160;
    sf::RectangleShape gameBorder(sf::Vector2f(borderSize.x,borderSize.y));
    gameBorder.setPosition(borderEndx, borderEndy);
    gameBorder.setFillColor(sf::Color::Black);
    gameBorder.setOutlineThickness(5);
    gameBorder.setOutlineColor(sf::Color::White);

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
    //clock item
    sf::IntRect oclock(30,185,90,90);
    sf::Sprite oclockSprite(itemsheet,oclock);
    oclockSprite.setPosition(50,100);
    //heart item
    sf::IntRect heart(145,185,90,90);
    sf::Sprite heartSprite(itemsheet,heart);
    heartSprite.setPosition(170,100);
    //boulder item
    sf::IntRect boulder(620,185,110,110);
    sf::Sprite boulderSprite(itemsheet,boulder);
    boulderSprite.setPosition(290,100);
    //stump item
    sf::IntRect stump(760,185,110,110);
    sf::Sprite stumpSprite(itemsheet,stump);
    stumpSprite.setPosition(410,100);
    // red scroll item (least points - slowest)
    sf::IntRect rscroll(920,175,70,105);
    sf::Sprite rscrollSprite(itemsheet,rscroll);
    rscrollSprite.setPosition(530,100);
    //green scroll item (more points - faster)
    sf::IntRect gscroll(1005,175,70,105);
    sf::Sprite gscrollSprite(itemsheet,gscroll);
    gscrollSprite.setPosition(740,100);
    //yellow scroll item (most points - fastest)
    sf::IntRect yscroll(1090,175,70,105);
    sf::Sprite yscrollSprite(itemsheet,yscroll);
    yscrollSprite.setPosition(50,220);
    
    //time for animation trigger
    sf::Clock clock;
    std::cout.precision(18);
  
    // point counter
    // border (may no longer be necessary)
    // sf::RectangleShape pointCounter(sf::Vector2f(100, 50));
    // pointCounter.setPosition(660, 50);
    // pointCounter.setFillColor(sf::Color::Black);
    // pointCounter.setOutlineThickness(5);
    // pointCounter.setOutlineColor(sf::Color::White);
    // points
    sf::Font font;
    font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf");
    sf::Text points;
    points.setFont(font);
    points.setCharacterSize(60);
    points.setFillColor(sf::Color::Red);
    points.setPosition(650, 5);

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
        // window.draw(pointCounter);
        window.draw(gameBorder); 
        window.draw(oclockSprite);
        window.draw(heartSprite);
        window.draw(boulderSprite);
        window.draw(stumpSprite);
        window.draw(rscrollSprite);
        window.draw(gscrollSprite);
        window.draw(yscrollSprite);
        window.draw(sprite);
        window.draw(points);
        window.display();
    }
    return 0;
}

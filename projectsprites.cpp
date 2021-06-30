
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
using std::fmod;

bool CheckCollision(sf::Sprite player, sf::Sprite item) {
    float proximity;
    float basex;
    float basey;
    basex = (player.getPosition().x) - (item.getPosition().x);
    basey = (player.getPosition().y) - (item.getPosition().y);
    proximity = abs( sqrt( pow(basex,2) + pow(basey,2)));
    proximity -= player.getLocalBounds().height / 2;
    proximity -= item.getLocalBounds().height / 2;
    //collision
    if(proximity <= 0)
        return true;
    //no collision
    return false;
}

int main() {
  
    // window
    sf::RenderWindow window(sf::VideoMode(810, 1080), "bja955@bu.edu | cwgough@bu.edu | jsevilla@bu.edu");

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

    //spritesheet for main menu
    std::vector<sf::Sprite> mainmenuSprites;
    sf::Texture menusheet;
    menusheet.loadFromFile("mainmenusprites.png");
    //time game mode
    sf::IntRect time(0,88, 225, 44);
    sf::Sprite timeMode(menusheet,time);
    timeMode.setPosition(310,500);
    mainmenuSprites.push_back(timeMode);
    //infinite game mode
    sf::IntRect inf(0,132, 225, 44);
    sf::Sprite infMode(menusheet,inf);
    infMode.setPosition(310,700);
    mainmenuSprites.push_back(infMode);
    
    //spritesheet for game items
    sf::Texture itemsheet;
    itemsheet.loadFromFile("itemsspritesheetcropped.png");

    std::vector<sf::Sprite> onscreenSprites;
    //Items to be moved
    int x = 0, y = 0;
    int count = 0;
    // sf::Clock count;
    //clock item
    sf::IntRect oclock(30,185,90,90);
    sf::Sprite oclockSprite(itemsheet,oclock);
    oclockSprite.setPosition(50,100);
    onscreenSprites.push_back(oclockSprite);
    //heart item
    sf::IntRect heart(145,185,90,90);
    sf::Sprite heartSprite(itemsheet,heart);
    heartSprite.setPosition(170,100);
    onscreenSprites.push_back(heartSprite);
    //boulder item
    sf::IntRect boulder(620,185,110,110);
    sf::Sprite boulderSprite(itemsheet,boulder);
    boulderSprite.setPosition(290,100);
    onscreenSprites.push_back(boulderSprite);
    //stump item
    sf::IntRect stump(760,185,110,110);
    sf::Sprite stumpSprite(itemsheet,stump);
    stumpSprite.setPosition(410,100);
    onscreenSprites.push_back(stumpSprite);    
    // red scroll item (least points - slowest)
    sf::IntRect rscroll(920,175,70,105);
    sf::Sprite rscrollSprite(itemsheet,rscroll);
    rscrollSprite.setPosition(530,100);
    onscreenSprites.push_back(rscrollSprite);
    //green scroll item (more points - faster)
    sf::IntRect gscroll(1090,175,70,105);
    sf::Sprite gscrollSprite(itemsheet,gscroll);
    gscrollSprite.setPosition(650,100);
    onscreenSprites.push_back(gscrollSprite);
    //yellow scroll item (most points - fastest)
    sf::IntRect yscroll(1005,175,70,105);
    sf::Sprite yscrollSprite(itemsheet,yscroll);
    // yscrollSprite.setPosition(50,220);
    onscreenSprites.push_back(yscrollSprite);
    //time for animation trigger
    sf::Clock clock;
  
    // point counter
    sf::Font font;
    font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf");
    sf::Text points;
    points.setFont(font);
    points.setCharacterSize(60);
    points.setFillColor(sf::Color::Red);
    points.setPosition(650, 5);
    bool mainMenu = true;

    window.setFramerateLimit(200);
    while (window.isOpen())
    {
        // Start at main menu
        if (mainMenu) {
            window.clear();
            for (auto itr = mainmenuSprites.begin(); itr != mainmenuSprites.end(); itr++) {
                window.draw(*itr);
            }
            window.display();
            sf::Sprite inf = mainmenuSprites.at(1);
            sf::Sprite time = mainmenuSprites.at(0);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                //mouse coords
                sf::Vector2f mouse_pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                //sprite bounds
                sf::FloatRect timeBounds = time.getGlobalBounds();
                sf::FloatRect infBounds = inf.getGlobalBounds();
                //check click
                if (timeBounds.contains(mouse_pos)) {
                    mainMenu = false;
                    window.clear();
                    //play time game mode
                }
                else if (infBounds.contains(mouse_pos)) {
                    mainMenu = false;
                    window.clear();
                    //play inf game mode
                }
            }
        }
        else {
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
            for (auto it = onscreenSprites.begin(); it != onscreenSprites.end();) {
                sf::Sprite curr = *it;
                if (CheckCollision(sprite, curr)) {
                    it = onscreenSprites.erase(it);
                }
                else
                    it++; 
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
                    SourceSprite.left = 0;
                }
                else {
                    SourceSprite.left += 210;
                }
                sprite.setTextureRect(SourceSprite);
                clock.restart();
            }

            // item movement
            if (count % 200 == 0) {
                x = 337;
                y = 0;
                yscrollSprite.setPosition(x, y);
            }
            yscrollSprite.setPosition(yscrollSprite.getPosition().x, yscrollSprite.getPosition().y + 3);
            // y += 3;
            count++;

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
            for (auto it = onscreenSprites.begin(); it != onscreenSprites.end(); it++) {
                window.draw(*it);
            }
            // window.draw(oclockSprite);
            // window.draw(heartSprite);
            // window.draw(boulderSprite);
            // window.draw(stumpSprite);
            // window.draw(rscrollSprite);
            // window.draw(gscrollSprite);
            // window.draw(yscrollSprite);
            window.draw(sprite);
            window.draw(points);
            window.display();
        }
    }
    return 0;
}
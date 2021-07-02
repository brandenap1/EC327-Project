// Copyright 2021 Branden Applewhite bja955@bu.edu | Chris Gough cwgough@bu.edu | Jose Sevilla jsevilla@bu.edu



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
#include <random>

using std::string;
using std::to_string;

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

    // prng setup
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> which_item(0, 20);
  
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
    gameBorder.setFillColor(sf::Color::Transparent);
    gameBorder.setOutlineThickness(8);
    gameBorder.setOutlineColor(sf::Color::Black);

    //spritesheet for char animations
    sf::Texture spritesheet;
    spritesheet.loadFromFile("charspritescropped.png");
    sf::IntRect SourceSprite(0,0, 210, 200);
    sf::Sprite sprite(spritesheet,SourceSprite);
    sprite.setScale(0.8,0.8);

    // spritesheet for main menu background
    sf::Texture backgroundsheet;
    backgroundsheet.loadFromFile("gamebackground.png");
    sf::IntRect background(0,20,202,270);
    sf::Sprite backgroundSprite(backgroundsheet, background);
    backgroundSprite.scale(4,4);


    //spritesheet for main menu
    std::vector<sf::Sprite> mainmenuSprites;
    sf::Texture menusheet;
    menusheet.loadFromFile("mainmenusprites.png");
    // title
    sf::Texture titlesheet;
    titlesheet.loadFromFile("Titlescroll.jpg");
    sf::IntRect titleSource(188,235,820,760);
    sf::Sprite title(titlesheet, titleSource);
    title.scale(0.3,0.3);
    title.setPosition(303,150);
    mainmenuSprites.push_back(title);
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

    //spritesheet for menu options during game
    sf::Texture optionsheet;
    optionsheet.loadFromFile("menuoptionscropped.png"); 
    //pause button
    sf::IntRect pause(20,0,300,300);
    sf::Sprite pauseSprite(optionsheet,pause);
    pauseSprite.scale(0.20,0.20);
    pauseSprite.setPosition(20,0);

    //Pause Menu
    std::vector<sf::Sprite> pausemenuSprites;
    // //home button
    sf::IntRect home(650,310,300,300);
    sf::Sprite homeSprite(optionsheet,home);
    homeSprite.scale(0.25,0.25);
    homeSprite.setPosition(380,300);
    pausemenuSprites.push_back(homeSprite);
    //cancel button (play)
    sf::IntRect play(930,310,300,300);
    sf::Sprite playSprite(optionsheet,play);
    playSprite.scale(0.25,0.25);
    playSprite.setPosition(470,105);
    pausemenuSprites.push_back(playSprite);
    
    //spritesheet for game items
    sf::Texture itemsheet;
    itemsheet.loadFromFile("itemsspritesheetcropped.png"); 

    // vector for top of gameplay sprites
    std::vector<sf::Sprite> compSprites;

    //Items to be moved
    std::vector<sf::Sprite> itemStorage;
    std::vector<sf::Sprite> onscreenSprites;
    int x = 0, y = 0;
    int count = 0;
    //clock item (x2)
    sf::IntRect oclock(30,185,90,90);
    sf::Sprite oclockSprite(itemsheet,oclock);
    for (int i = 0; i < 2; i++)
        itemStorage.push_back(oclockSprite);
    //heart item (x1)
    sf::IntRect heart(145,185,90,90);
    sf::Sprite heartSprite(itemsheet,heart);
    itemStorage.push_back(heartSprite);
    //lives (x3)
    sf::Sprite life(itemsheet,heart);
    life.setScale(0.8,0.8);
    //boulder item (x4)
    sf::IntRect boulder(620,185,110,110);
    sf::Sprite boulderSprite(itemsheet,boulder);
    for (int i = 0; i < 4; i++)
        itemStorage.push_back(boulderSprite);
    //stump item (x8)
    sf::IntRect stump(760,185,110,110);
    sf::Sprite stumpSprite(itemsheet,stump);
    for (int i = 0; i < 8; i++)
        itemStorage.push_back(stumpSprite);    
    // red scroll item (x3)
    sf::IntRect rscroll(920,175,70,105);
    sf::Sprite rscrollSprite(itemsheet,rscroll);
    for (int i = 0; i < 3; i++)
        itemStorage.push_back(rscrollSprite);
    //green scroll item (x2)
    sf::IntRect gscroll(1090,175,70,105);
    sf::Sprite gscrollSprite(itemsheet,gscroll);
    for (int i = 0; i < 2; i++)
        itemStorage.push_back(gscrollSprite);
    //yellow scroll item (x1)
    sf::IntRect yscroll(1005,175,70,105);
    sf::Sprite yscrollSprite(itemsheet,yscroll);
    itemStorage.push_back(yscrollSprite);

    //time for animation trigger
    sf::Clock clock;
  
    // controlling speed
    float itemspeed;
    float charspeed;
    float spawnspeed;
  
    // point counter
    int scroll_hits;
    sf::Font font;
    font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf");
    sf::Text points;
    points.setFont(font);
    points.setCharacterSize(60);
  
    // text in pause menu
    sf::Text pauseText;
    pauseText.setFont(font);
    pauseText.setCharacterSize(60);
    pauseText.setFillColor(sf::Color::Red);
    pauseText.setPosition(324, 200);
    
    // game over text
    sf::Text gameoverText;
    gameoverText.setFont(font);
    gameoverText.setCharacterSize(60);
    gameoverText.setFillColor(sf::Color::Red);
    gameoverText.setPosition(244, 200);
    gameoverText.setString("Game Over");

    //stopwatch for timed mode
    int sec = 60;
    int secCount = 0;
    sf::Text stopwatch;
    stopwatch.setFont(font);
    stopwatch.setCharacterSize(60);
    stopwatch.setFillColor(sf::Color::White);
    stopwatch.setPosition(340, 5);

    //bool values for game state
    bool mainMenu = true;
    bool pauseMenu = false;
    bool gameScreen = false;
    bool Timed;
    bool gameOver = false;

    window.setFramerateLimit(200);

    while (window.isOpen())
    {
        // Change to pause menu
        if (pauseMenu && !mainMenu && !gameScreen) {
            window.clear();
            backgroundSprite.setColor(sf::Color(255,255,255,128));
            gameBorder.setFillColor(sf::Color(255,255,255,128));
            sprite.setColor(sf::Color(255,255,255,128));
            for (auto ity = onscreenSprites.begin(); ity != onscreenSprites.end(); ity++) {
                (*ity).setColor(sf::Color(255,255,255,128));
            }
            for (auto itw = compSprites.begin(); itw != compSprites.end(); itw++) {
                (*itw).setColor(sf::Color(255,255,255,128));
            }
            pauseText.setString("Pause");
            window.draw(backgroundSprite);
            window.draw(sprite);
            for (auto it = onscreenSprites.begin(); it != onscreenSprites.end(); it++) {
                (*it).setPosition((*it).getPosition().x, (*it).getPosition().y);
                window.draw(*it);
            }
            window.draw(gameBorder);
            if (!Timed) {
                int p = 260;
                for (auto itv = compSprites.begin(); itv != compSprites.end(); itv++) {
                    (*itv).setPosition(p, 0);
                    p += 80;
                    window.draw(*itv);
                }
            }
            window.draw(sprite);
            window.draw(pauseSprite);
            window.draw(points);
            if (Timed)
                window.draw(stopwatch);
            window.draw(pauseText);
            for (auto itrs = pausemenuSprites.begin(); itrs != pausemenuSprites.end(); itrs++) {
                window.draw(*itrs);
            }
            window.display();
            sf::Sprite home = pausemenuSprites.at(0);
            sf::Sprite play = pausemenuSprites.at(1);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                //mouse coords
                sf::Vector2f mouse_pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                //sprite bounds
                sf::FloatRect playBounds = play.getGlobalBounds();
                sf::FloatRect homeBounds = home.getGlobalBounds();
                //check click
                if (homeBounds.contains(mouse_pos)) {
                    window.clear();
                    mainMenu = true;
                    gameScreen = false;
                    pauseMenu = false;
                    //go to main  menu
                }
                else if (playBounds.contains(mouse_pos)) {
                    window.clear();
                    mainMenu = false;
                    gameScreen = true;
                    pauseMenu = false;
                    //play
                }
            }
            
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
        }
        // Start at main menu
        else if (mainMenu && !pauseMenu && !gameScreen) {
            scroll_hits = 0;
            std::uniform_int_distribution<> spawn_loc(-110, 810);
            itemspeed = 2.f;
            charspeed = 4.f;
            spawnspeed = 200.f;
            sprite.setPosition(310,1000);

            // return to original color
            backgroundSprite.setColor(sf::Color::White);
            gameBorder.setFillColor(sf::Color::Transparent);
            sprite.setColor(sf::Color::White);            
            for (auto ity = onscreenSprites.begin(); ity != onscreenSprites.end(); ity++) {
                (*ity).setColor(sf::Color::White);
            }
            for (auto itw = compSprites.begin(); itw != compSprites.end(); itw++) {
                (*itw).setColor(sf::Color::White);
            }

            window.clear();
            window.draw(backgroundSprite);
            compSprites.clear();

            // item movement
            if (count % 200 == 0) {
                x = spawn_loc(generator);
                y = 0;
                int which = which_item(generator);
                itemStorage.at(which).setPosition(x, y);
                onscreenSprites.push_back(itemStorage.at(which));
            }
            count++;
            for (auto its = onscreenSprites.begin(); its != onscreenSprites.end(); its++) {
                (*its).setPosition((*its).getPosition().x, (*its).getPosition().y + 3);
                window.draw(*its);
            }

            for (auto itr = mainmenuSprites.begin(); itr != mainmenuSprites.end(); itr++) {
                window.draw(*itr);
            }

            window.display();
            sf::Sprite inf = mainmenuSprites.at(1);
            sf::Sprite timed = mainmenuSprites.at(0);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                //mouse coords
                sf::Vector2f mouse_pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                //sprite bounds
                sf::FloatRect timeBounds = timed.getGlobalBounds();
                sf::FloatRect infBounds = inf.getGlobalBounds();
                //check click
                if (timeBounds.contains(mouse_pos)) {
                    window.clear();
                    onscreenSprites.clear();
                    mainMenu = false;
                    gameScreen = true;
                    pauseMenu = false;
                    Timed = true;
                    sec = 60;
                    secCount = 0;
                    //play time game mode
                    Timed = true;
                }
                else if (infBounds.contains(mouse_pos)) {
                    window.clear();
                    onscreenSprites.clear();
                    mainMenu = false;
                    gameScreen = true;
                    pauseMenu = false;
                    Timed = false;  //play inf game mode
                    for (int i = 0; i < 3; i++)
                        compSprites.push_back(life);
                }
            }

            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
        }
        // Play Game
        else if (!pauseMenu && !mainMenu && gameScreen) {
            if (!gameOver){
                backgroundSprite.setColor(sf::Color::White);
                gameBorder.setFillColor(sf::Color::Transparent);
                sprite.setColor(sf::Color::White);            
                for (auto ity = onscreenSprites.begin(); ity != onscreenSprites.end(); ity++) {
                    (*ity).setColor(sf::Color::White);
                }
                for (auto itw = compSprites.begin(); itw != compSprites.end(); itw++) {
                    (*itw).setColor(sf::Color::White);
                }
                //Character moves
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                    sprite.move(charspeed,0.f);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                    sprite.move(-charspeed,0.f);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                    sprite.move(0.f,-charspeed);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                    sprite.move(0.f,charspeed);
                }

                // Item collisions
                for (auto it = onscreenSprites.begin(); it != onscreenSprites.end();) {
                    sf::Sprite curr = *it;
                    if (CheckCollision(sprite, curr)) {
                        if (curr.getTextureRect() == itemStorage.at(15).getTextureRect()) {
                            scroll_hits += 1;
                            // changing speed
                            if ((scroll_hits % 10 == 0) and (scroll_hits > 0)) {
                                itemspeed *= 2;
                                charspeed *= 2;
                                spawnspeed /= 2;
                            }
                        } else if (curr.getTextureRect() == itemStorage.at(18).getTextureRect()) {
                            for (int i = 0; i < 2; i++) {
                                scroll_hits += 1;
                                if ((scroll_hits % 10 == 0) and (scroll_hits > 0)) {
                                    itemspeed *= 2;
                                    charspeed *= 2;
                                    spawnspeed /= 2;
                                }
                            }
                        } else if (curr.getTextureRect() == itemStorage.at(20).getTextureRect()) {
                            for (int i = 0; i < 3; i++) {
                                scroll_hits += 1;
                                if ((scroll_hits % 10 == 0) and (scroll_hits > 0)) {
                                    itemspeed *= 2;
                                    charspeed *= 2;
                                    spawnspeed /= 2;
                                }
                            }
                        } else if (curr.getTextureRect() == itemStorage.at(7).getTextureRect()) {
                            sprite.setColor(sf::Color::Red);
                            if (!Timed) {
                                compSprites.pop_back();
                            } else {
                                scroll_hits -= 1;
                            }
                        } else if (curr.getTextureRect() == itemStorage.at(3).getTextureRect()) {
                            sprite.setColor(sf::Color::Red);
                            if (!Timed) {
                                compSprites.pop_back();
                            }
                            scroll_hits -= 2;
                        } else if (curr.getTextureRect() == itemStorage.at(2).getTextureRect()) {
                            if (!Timed) {
                                if (compSprites.size() < 4)
                                    compSprites.push_back(life);
                            } else {
                                scroll_hits += 5;
                            }
                        } else {
                            itemspeed /= 2;
                            charspeed /= 2;
                            spawnspeed *= 2;
                        }
                        onscreenSprites.erase(it);
                    }
                    else
                        it++;
                }

                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    //mouse coords
                    sf::Vector2f mouse_pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    //sprite bounds
                    sf::FloatRect pauseBounds = pauseSprite.getGlobalBounds();
                    //check click
                    if (pauseBounds.contains(mouse_pos)) {
                        mainMenu = false;
                        gameScreen = false;
                        pauseMenu = true;
                    }
                }

                //Border Collisions
                if (sprite.getPosition().x <=  borderEndx) {
                    sprite.move(charspeed,0.f);
                }
                if (sprite.getPosition().y <= borderEndy ) {
                    sprite.move(0.f,charspeed);
                }
                if (sprite.getPosition().x + sprite.getLocalBounds().width >= window.getSize().x ) {
                    sprite.move(-charspeed,0.f);
                }
                if (sprite.getPosition().y + sprite.getLocalBounds().height >= window.getSize().y ) {
                    sprite.move(0.f,-charspeed);
                }

                // case time 
                if (clock.getElapsedTime().asSeconds() > 0.1f) {
                    sprite.setColor(sf::Color::White);
                    if(SourceSprite.left == 1050) {
                        SourceSprite.left = 0;
                    }
                    else {
                        SourceSprite.left += 210;
                    }
                    sprite.setTextureRect(SourceSprite);
                    clock.restart();
                }
                if (Timed) {
                    stopwatch.setString(to_string(sec));
                    secCount++;
                    if (secCount > 200) {
                        --sec;
                        secCount = 0;
                    }
                    if (sec == 0){
                        stopwatch.setString(to_string(sec));
                        sec = 60;
                        secCount = 0;
                        gameOver = true;
                    }

                }

                if (!Timed) {
                    if (compSprites.size() == 0)  //No Lives
                        gameOver = true;
                }

                // item movement
                std::uniform_int_distribution<> spawn_loc(80, 620);
                if (std::fmod(count, spawnspeed) == 0.f) {
                    x = spawn_loc(generator);
                    y = 0;
                    int which = which_item(generator);
                    itemStorage.at(which).setPosition(x, y);
                    onscreenSprites.push_back(itemStorage.at(which));
                }
                count++;

                // adding points
                string numpoints = to_string(scroll_hits);
                if (numpoints.size() < 2)
                    numpoints = "0" + numpoints;
                points.setString(numpoints);
                points.setPosition(650, 5);
                points.setFillColor(sf::Color::Red);

            }
            else {
                backgroundSprite.setColor(sf::Color(255,255,255,128));
                gameBorder.setFillColor(sf::Color(255,255,255,128));
                sprite.setColor(sf::Color(255,255,255,128));
                points.setPosition(375, 100);
                for (auto ity = onscreenSprites.begin(); ity != onscreenSprites.end(); ity++) {
                    (*ity).setColor(sf::Color(255,255,255,128));
                }
                for (auto itw = compSprites.begin(); itw != compSprites.end(); itw++) {
                    (*itw).setColor(sf::Color(255,255,255,128));
                }
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    //mouse coords
                    sf::Vector2f mouse_pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    sf::FloatRect homeBounds = homeSprite.getGlobalBounds();
                    //check click
                    if (homeBounds.contains(mouse_pos)) {
                        window.clear();
                        mainMenu = true;
                        gameScreen = false;
                        pauseMenu = false;
                        gameOver = false;
                        //go to main  menu
                    }
                }
            }

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
            window.draw(backgroundSprite);
            window.draw(sprite);
            for (auto it = onscreenSprites.begin(); it != onscreenSprites.end(); it++) {
                (*it).setPosition((*it).getPosition().x, (*it).getPosition().y + itemspeed);
                window.draw(*it);
            }
            window.draw(gameBorder);
            if (!Timed) {
                int p = 260;
                for (auto itv = compSprites.begin(); itv != compSprites.end(); itv++) {
                    (*itv).setPosition(p, 0);
                    p += 80;
                    window.draw(*itv);
                }
            }
            window.draw(pauseSprite);
            window.draw(sprite);
            window.draw(points);
            if (Timed)
                window.draw(stopwatch);
            if (gameOver) {
                window.draw(points);
                window.draw(gameoverText);
                window.draw(homeSprite);
            }
            window.display();
        }
    }
    return 0;
}




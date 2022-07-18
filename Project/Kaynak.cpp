#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include <iostream>
#include <random>
bool isColiding(sf::RectangleShape s1, sf::RectangleShape s2) {
    return (s1.getGlobalBounds().intersects(s2.getGlobalBounds()));
}
int main() {
    bool big = false;
    const float WW = 800;
    const float WH = 600;
    sf::RenderWindow window(sf::VideoMode(WW, WH), "A game i guess");
    // run the program as long as the window is open
    float i = 0;
    const int enemyCount = 1;
    bool pressed = false;
    int rndsize = rand() % 30 + 6;
    int rndspeed = rand() % 6 + 3;
    int enemyi = 0;
    int score = 0;
    sf::Font font;
    if (!font.loadFromFile("font.ttf")) { }
    sf::Text text;
    sf::Text fpstext;
    try
    { text.setFont(font); } catch (const std::exception&) { }
    text.setCharacterSize(24);
    text.setString("0");
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    text.setPosition(10, 10);
    try {fpstext.setFont(font);}
    catch (const std::exception&) {}
    fpstext.setCharacterSize(12);
    fpstext.setString("FPS: -");
    fpstext.setFillColor(sf::Color::White);
    fpstext.setStyle(sf::Text::Bold);
    fpstext.setPosition(WW-200, 10);
    sf::Clock clock;
    window.setFramerateLimit(60);
    while (window.isOpen())
    {
        i+= 0.035f;
        enemyi++;
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            float cTime = clock.restart().asSeconds();
            float fps = 1.0f / cTime;
            fpstext.setString("FPS: " + std::to_string(fps));
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::Resized)
            {
                // update the view to the new size of the window
                sf::FloatRect visibleArea(-(event.size.width - WW)/2, -(event.size.height - WH)/2, event.size.width, event.size.height);
                sf::View view1(visibleArea);
                view1.zoom((WH / event.size.height));
                window.setView(view1);
            }
        }
        /*sf::View view;
        view.setSize(WW, WH);
        view.setCenter(window.getView().getCenter());
        window.setView(view);*/
        /// ground
        sf::RectangleShape ground(sf::Vector2f(0,0));
        ground.setSize(sf::Vector2f(WW,WH/3));
        ground.setFillColor(sf::Color::White);
        ground.setPosition(0, WH/1.5f);
        /// player
        sf::RectangleShape player(sf::Vector2f(0, 0));
        player.setSize(sf::Vector2f(20, 60));
        player.setPosition(0, WH/2+41);
        player.setFillColor(sf::Color::Blue);
        /// view
        /// enemy
        sf::RectangleShape enemy(sf::Vector2f(0, 0));
        enemy.setFillColor(sf::Color::Red);
        enemy.setOutlineColor(sf::Color(255,50,80));
        enemy.setOutlineThickness(5.0f);
        enemy.setSize(sf::Vector2f(rndsize, rndsize));
        enemy.setPosition(WW - (enemyi * rndspeed), ground.getGlobalBounds().top - enemy.getSize().x);
        /// text
        text.setString("Score: "+ std::to_string(score));
        /// events
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F11))
        {
            big = !big;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            if (!pressed)
            {
                pressed = true;
                i = 0;
            }
        }
        if (pressed)
        {
            player.setPosition(0, WH / 2 + (21- sinf(i) * 40));
            if (player.getPosition().y >= WH / 2 + 40)
            {
                pressed = false;
            }
        }
            if (isColiding(player, enemy))
            {
                sf::Texture texture;
                texture.create(window.getSize().x, window.getSize().y);
                texture.update(window);
                if (texture.copyToImage().saveToFile("lastwin.png"))
                {
                    std::cout << "screenshot saved to " << "lastwin.png" << std::endl;
                }

                window.close();
            }
            if (enemy.getPosition().x <= enemy.getSize().x - 20)
            {
                score++;
                rndsize = rand() % 30 + 6;
                rndspeed = rand() % 3 + 3;
                enemyi = rand() % 10 + 3;
            }
        /// print
        //std::cout << i << std::endl;
        /// display
        window.clear(sf::Color::Black);
        window.draw(text);
        window.draw(fpstext);
        window.draw(ground);
        window.draw(player);
        window.draw(enemy);
        window.display();
    }

    return 0;
}
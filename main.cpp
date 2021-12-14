#include <SFML/Graphics.hpp>
#include "gamer.hpp"
#include "game.hpp"
#include "menu.hpp"
#include <iostream>

sf::RenderWindow mainWindow(sf::VideoMode(1280,720,32), "Cpp Pong", sf::Style::Close);
void didAnyoneWin(Gamer&, Gamer&, Menu&);
float frameTime;
int main()
{
    sf::Clock clock;
    Menu *menu = new Menu();
    Game *game = new Game();
    Gamer *gamer[2] = {new Gamer(0), new Gamer(1)};

    while(mainWindow.isOpen())
    {
        sf::Event event;
        while( mainWindow.pollEvent(event))
        {
            if (event.type==sf::Event::Closed)
                mainWindow.close();
            if (event.type==sf::Event::KeyPressed && event.key.code==sf::Keyboard::Escape)
                if(menu->ifGame || menu->ifPause) {
                    menu->ifGame=!menu->ifGame;
                    menu->ifPause=!menu->ifPause;
                if (menu->ifGame)
                    mainWindow.setMouseCursorVisible(false);
                else
                    mainWindow.setMouseCursorVisible(true);
                }

            if(!menu->ifGame)
                menu->handleButtons(mainWindow, event, *gamer[0], *gamer[1], *game);
            //cheats
            /*if (event.type==sf::Event::KeyPressed && event.key.code==sf::Keyboard::Home)
                gamer[1]->dodaj_punkt();
            if (event.type==sf::Event::KeyPressed && event.key.code==sf::Keyboard::Insert)
                gamer[0]->dodaj_punkt();*/
        }
        if(menu->ifGame) {
            mainWindow.clear(sf::Color::Black);
            game->handleBall(*gamer[0],*gamer[1]);
            game->draw(mainWindow);
            gamer[0]->controls();
            gamer[1]->controls();
            gamer[0]->draw(mainWindow);
            gamer[1]->draw(mainWindow);
            didAnyoneWin(*gamer[0],*gamer[1], *menu);
        } else {
            mainWindow.clear(sf::Color(2,56,87));
            menu->draw(mainWindow);
        }
        mainWindow.display();
        frameTime = clock.restart().asSeconds();
    }
    delete menu;
    delete game;
    delete gamer[0];
    delete gamer[1];
    return 0;
}

void didAnyoneWin(Gamer& gamer0, Gamer& gamer1, Menu& menu){
    if(gamer0.points>=11 && gamer0.points-gamer1.points>=2)
        menu.win(gamer0, gamer1);
    if(gamer1.points>=11 && gamer1.points-gamer0.points>=2)
        menu.win(gamer1, gamer0);
}

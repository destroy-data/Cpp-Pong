#include "menu.hpp"
Menu::Menu() : ifGame(0), ifPause(0)
{
    t_button.loadFromFile("button.png");
    for (int i=0; i<3; ++i)
        button[i].setTexture(t_button);

    font.loadFromFile("font.ttf");
    button[0].setPosition(80, 80);
    button[1].setPosition(80, 250);
    button[2].setPosition(80, 420);

    text[0].setString(L"Continue");
    text[1].setString(L"New Game");
    text[2].setString(L"Exit");
    for (int i=0; i<3; ++i) {
        text[i].setFont(font);
        text[i].setPosition(button[i].getPosition().x+420/6,button[i].getPosition().y+85/8);
        text[i].setCharacterSize(50);
        text[i].setColor(sf::Color(0,0,0));
    }
    end.setFont(font);
    end.setCharacterSize(50);
}

void Menu::draw(sf::RenderWindow &window){
    if(!ifGame || ifPause)
    for (int i=0; i<3; ++i){
        window.draw(button[i]);
        window.draw(text[i]);
    }
    if(ifWinnerScreen) {
        window.setMouseCursorVisible(true);
        window.draw(end);
    }
}

void Menu::handleButtons(sf::RenderWindow &window, sf::Event &event, Gamer &gamer0, Gamer &gamer1, Game &game) {
    for (int i=0; i<3; ++i){
        text[i].setColor(sf::Color(0,0,0));
        if (sf::Mouse::getPosition(window).x>button[i].getPosition().x && sf::Mouse::getPosition(window).x<button[i].getPosition().x+t_button.getSize().x
         && sf::Mouse::getPosition(window).y>button[i].getPosition().y && sf::Mouse::getPosition(window).y<button[i].getPosition().y+t_button.getSize().y)
         {
            text[i].setColor(sf::Color(105,105,105));
            if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                if(i==0)
                    if(ifPause) {
                        ifGame=1;
                        ifPause=0;
                        ifWinnerScreen=0;
                        window.setMouseCursorVisible(false);
                    }
                if(i==1){
                    ifGame=1;
                    ifPause=0;
                    ifWinnerScreen=0;
                    gamer0.reset();
                    gamer1.reset();
                    game.nextServe(gamer0, gamer1);
                    window.setMouseCursorVisible(false);
                }

                if(i==2)
                   window.close();
            }
         }
    }
}

void Menu::win(Gamer &winningGamer, Gamer &losingGamer){
    ifGame=0;
    ifPause=0;
    ifWinnerScreen=1;
    sf::String winnerString (L"The winner is gamer ");
    winnerString += intToString(winningGamer.getGamerNumber()+1);
    end.setString(winnerString);
    end.setPosition(1,1);
    winningGamer.reset();
    losingGamer.reset();
}

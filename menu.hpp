#ifndef menu_hpp
#define menu_hpp
#include <SFML/Graphics.hpp>
#include "gamer.hpp"
#include "game.hpp"

class Menu
{
    private:
    sf::Texture t_button;
    sf::Sprite button[3];
    sf::Font font;
    sf::Text text[3];
    sf::Text end;

    public:
    bool ifGame;
    bool ifPause;
    bool ifWinnerScreen;
    Menu();
    void draw(sf::RenderWindow &);
    void handleButtons(sf::RenderWindow &, sf::Event &, Gamer&, Gamer&, Game&);
    void win(Gamer&, Gamer&); // (winner, loser)
};
std::string intToString (int);
#endif

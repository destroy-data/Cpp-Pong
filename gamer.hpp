#ifndef gamer_hpp
#define gamer_hpp
#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>

class Menu;

extern float frameTime;
class Gamer
{
    private:
    sf::RectangleShape pallet;
    bool GamerNumber;
    sf::Font font;
    sf::Text t_points;
    int points;
    int speed;

    public:
    Gamer(int);
    void draw(sf::RenderWindow &);
    void controls();
    void addPoint();
    sf::Vector2f getPosition();
    sf::Vector2f getSize();
    friend void didAnyoneWin(Gamer&, Gamer&, Menu&);
    void reset();
    bool getGamerNumber();
    int getPoints();
};

std::string intToString (int);
#endif

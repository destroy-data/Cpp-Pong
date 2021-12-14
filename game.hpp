#ifndef game_hpp
#define game_hpp
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include "gamer.hpp"

extern float frameTime;
class Game
{
    private:
    sf::RectangleShape frame[2]; //1–pion, 2–poziom
    sf::RectangleShape square;
    enum {vertical=0, horizontal=1};
    sf::CircleShape ball;
    sf::Clock serveTime;
    sf::Sound reflection;
    sf::SoundBuffer b_reflection;
    struct BallMovement
    {
        //bool czy;
        float direction;
        int speed;
        float palletReflectionFactor;
    } ballMovement;

    public:
    Game();
    void normalizeBallMovement();
    void handleBall(Gamer&, Gamer&);
    void draw(sf::RenderWindow &);
    void nextServe(Gamer&, Gamer&);
};
#endif

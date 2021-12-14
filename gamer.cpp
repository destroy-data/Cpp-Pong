#include "gamer.hpp"
Gamer::Gamer(int number): GamerNumber(number), points(0){
    font.loadFromFile("font.ttf");
    t_points.setFont(font);
    t_points.setCharacterSize(100);
    t_points.setString(intToString(points));
    speed = 666;

    pallet.setSize(sf::Vector2f(10,75));
    pallet.setFillColor(sf::Color::Red);
    if(GamerNumber==0) {
        pallet.setPosition(35, 360-pallet.getSize().y/2);
        t_points.setPosition(600-t_points.getGlobalBounds().width,50);
    }
    if(GamerNumber==1) {
        pallet.setPosition(1235, 360-pallet.getSize().y/2);
        t_points.setPosition(680,50);
    }

}

void Gamer::draw(sf::RenderWindow &window) {
    window.draw(pallet);
    window.draw(t_points);
}

void Gamer::controls() {
    if(GamerNumber==0) {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            pallet.move(0, -frameTime*speed);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            pallet.move(0, frameTime*speed);

    }
    if(GamerNumber==1) {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            pallet.move(0, -frameTime*speed);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            pallet.move(0, frameTime*speed);

    }
    if(pallet.getPosition().y <25)
        pallet.setPosition(pallet.getPosition().x, 25);
    if(pallet.getPosition().y >695-pallet.getSize().y)
        pallet.setPosition(pallet.getPosition().x, 695-pallet.getSize().y);
}

void Gamer::addPoint(){
    ++points;
    t_points.setString(intToString(points));
    if(GamerNumber==0)
        t_points.setPosition(600-t_points.getGlobalBounds().width,50);
    if(GamerNumber==1)
        t_points.setPosition(680,50);
}

sf::Vector2f Gamer::getPosition(){
    return pallet.getPosition();
}

sf::Vector2f Gamer::getSize(){
    return pallet.getSize();
}

void Gamer::reset(){
    points=0;
    t_points.setString(intToString(points));
    if(GamerNumber==0) {
        pallet.setPosition(35, 360-pallet.getSize().y/2);
        t_points.setPosition(600-t_points.getGlobalBounds().width,50);
    }
    if(GamerNumber==1) {
        pallet.setPosition(1235, 360-pallet.getSize().y/2);
        t_points.setPosition(680,50);
    }
}

bool Gamer::getGamerNumber(){
    return GamerNumber;
}

int Gamer::getPoints () {
    return points;
}

std::string intToString (int a)
{
    std::ostringstream temp;
    temp<<a;
    return temp.str();
}

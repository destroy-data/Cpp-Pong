#include "game.hpp"
Game::Game(){
    b_reflection.loadFromFile("pyk.wav");
    reflection.setBuffer(b_reflection);
    frame[vertical].setSize(sf::Vector2f(1250, 10));
    frame[horizontal].setSize(sf::Vector2f(10, 690));
    square.setSize(sf::Vector2f(10, 10));
    ball.setRadius(10);
    ball.setFillColor(sf::Color::Yellow);
    ball.setOrigin(10,10);
    ball.setPosition(640,360);
    ballMovement.direction = 90;
    ballMovement.speed = 1024;
    ballMovement.palletReflectionFactor=0.25;
}

void Game::normalizeBallMovement()
{
    while (!(ballMovement.direction>=0 && ballMovement.direction <360))
    {
        if(ballMovement.direction<0)
            ballMovement.direction+=360;
        else if(ballMovement.direction>=360)
            ballMovement.direction-=360;
    }
}

void Game::handleBall(Gamer& gamer0, Gamer& gamer1) {
    if(serveTime.getElapsedTime().asSeconds()>1.5)
    {
        ball.move((sin((ballMovement.direction* M_PI)/180.0f)*ballMovement.speed)*frameTime,
        -(cos((ballMovement.direction* M_PI)/180.0f)*ballMovement.speed)*frameTime);
        // Collisions
        //vertical
        if (ball.getPosition().y<=35 && (ballMovement.direction<90 || ballMovement.direction>270)) {
            ballMovement.direction=180-ballMovement.direction;
            reflection.play();
            normalizeBallMovement();
        }
        else if (ball.getPosition().y>=685 && (ballMovement.direction>90 && ballMovement.direction<270)) {
            ballMovement.direction=180-ballMovement.direction;
            reflection.play();
            normalizeBallMovement();
        }
        // horizontal
        if ((ball.getPosition().x<=35 && ballMovement.direction>180 && ballMovement.direction<360) || ball.getPosition().x<=20)
        {
            gamer1.addPoint();
            nextServe(gamer0, gamer1);
            normalizeBallMovement();
        }
        if ((ball.getPosition().x>=1245 && ballMovement.direction>0 && ballMovement.direction<180) || ball.getPosition().x>=1250)
        {
            gamer0.addPoint();
            nextServe(gamer0, gamer1);
            normalizeBallMovement();
        }

        //Reflections from pallets
        if(fabs(ball.getPosition().x -20 - gamer0.getPosition().x)<=3 && ball.getPosition().y +10>= gamer0.getPosition().y  &&
            ball.getPosition().y -10 <= gamer0.getPosition().y + gamer0.getSize().y)
            if(ballMovement.direction>180 && ballMovement.direction<360)
            {
                    ballMovement.direction=360-ballMovement.direction*(1+(ball.getPosition().y- gamer0.getPosition().y - gamer0.getSize().y/2)/gamer0.getSize().y*ballMovement.palletReflectionFactor);
                    reflection.play();
            }
        if(fabs(ball.getPosition().x +10 - gamer1.getPosition().x)<=3 && ball.getPosition().y +10 >= gamer1.getPosition().y  &&
            ball.getPosition().y -10 <= gamer1.getPosition().y + gamer1.getSize().y)
            if(ballMovement.direction>0 && ballMovement.direction<180)
            {
                    ballMovement.direction=360-ballMovement.direction*(1+(ball.getPosition().y- gamer1.getPosition().y - gamer1.getSize().y/2)/gamer1.getSize().y*ballMovement.palletReflectionFactor);
                    reflection.play();
            }
        //Reflections from sides of pallets
        if(fabs(ball.getPosition().y +10 - gamer0.getPosition().y)<=3 && ball.getPosition().x -10 <= gamer0.getPosition().x
            && ballMovement.direction>180 && ballMovement.direction<270)
                ballMovement.direction=180-ballMovement.direction;
        else if(fabs(ball.getPosition().y -10 - (gamer0.getPosition().y + gamer0.getSize().y))<=3 && ball.getPosition().x -10 <= gamer0.getPosition().x
            && ballMovement.direction>270 && ballMovement.direction<360)
                ballMovement.direction=180-ballMovement.direction;

        if(fabs(ball.getPosition().y +10 - gamer1.getPosition().y)<=3 && ball.getPosition().x +10 >= gamer1.getPosition().x
            && ballMovement.direction>90 && ballMovement.direction<180)
                ballMovement.direction=180-ballMovement.direction;
        else if(fabs(ball.getPosition().y -10 - (gamer1.getPosition().y + gamer1.getSize().y))<=3 && ball.getPosition().x +10 >= gamer1.getPosition().x
            && ballMovement.direction>0 && ballMovement.direction<90)
                ballMovement.direction=180-ballMovement.direction;
    }
}

void Game::draw(sf::RenderWindow &window) {
    frame[vertical].setPosition(15,15);
    window.draw(frame[vertical]);
    frame[vertical].setPosition(15, 695);
    window.draw(frame[vertical]);

    frame[horizontal].setPosition(15,15);
    window.draw(frame[horizontal]);
    frame[horizontal].setPosition(1255, 15);
    window.draw(frame[horizontal]);

    for (int i=15; i<695; i+=20) {
        square.setPosition(635, i);
        window.draw(square);
    }
    window.draw(ball);
}

void Game::nextServe(Gamer& gamer0, Gamer& gamer1){
    ball.setPosition(640,360);
    if (gamer0.getPoints()<=10 && gamer1.getPoints()<=10)
    {
        if ((gamer0.getPoints()+gamer1.getPoints())%4 <2)
            ballMovement.direction=90;
        else
            ballMovement.direction=270;
    } else if ((gamer0.getPoints()+gamer1.getPoints())%2 ==0)
        ballMovement.direction=90;
    else
        ballMovement.direction=270;
    serveTime.restart();
}

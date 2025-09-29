#include "ALinePlot.h"
#include <cmath>

ALinePlot:: ALinePlot(std::vector<double> x, std::vector<double> y, sf::Color dotColor){
    // stores x
    _x = x;
    //stors y
    _y = y;
    //prepares the sfml x cordinates
    this->matchX();
    //prepares the sfml y cordinates
    this->matchY();   
    //prepares the drawable objects
    this->prepareDraw(dotColor);
}

ALinePlot:: ~ALinePlot(){
    // does destructor things
    for(unsigned int i = 0; i< _plotPoints.size(); i++){
        delete _plotPoints.at(i);
    }
    for(unsigned int i = 0; i< _plotLines.size(); i++){
        delete _plotLines.at(i);
    }
}


void ALinePlot::matchX(){
    // creates x location based on points
    for(unsigned int i = 0; i< _x.size(); i++){
        _newX.push_back(_x.at(i)*(600/7.0)+24+40);
    }   
    return;
}
        
void ALinePlot::matchY(){
    // creates y location based on points
    for(unsigned int i = 0; i< _y.size(); i++){
        _newY.push_back( 300 - _y.at(i)*280);
    }
    return;
}

void  ALinePlot::prepareDraw(sf::Color dotColor){
    // creates points based on x and y
    sf::CircleShape* circleHolder;
    for(unsigned int i = 0; i< _newY.size(); i++){
        circleHolder = new sf::CircleShape();
        circleHolder->setRadius(6);
        circleHolder->setOrigin(6,6);
        circleHolder->setPosition(_newX.at(i), _newY.at(i));
        circleHolder->setFillColor(dotColor);
        _plotPoints.push_back(circleHolder);
    }
    
    // draws lines between points
    sf::ConvexShape* lineHolder;
     for(unsigned int i = 1; i< _newY.size(); i++){
        lineHolder = new sf::ConvexShape;
        lineHolder->setPointCount(4);
        lineHolder->setPoint(0, sf::Vector2f(_newX.at(i-1), _newY.at(i-1)-2));
        lineHolder->setPoint(3, sf::Vector2f(_newX.at(i-1), _newY.at(i-1)+2));
        lineHolder->setPoint(1, sf::Vector2f(_newX.at(i), _newY.at(i)-2));
        lineHolder->setPoint(2, sf::Vector2f(_newX.at(i), _newY.at(i)+2));
        lineHolder->setFillColor(sf::Color(0,0,0,120));
        _plotLines.push_back(lineHolder);
    }
     // adds ticks to x axis
        for(unsigned int i = 0; i< _newY.size(); i++){
            lineHolder = new sf::ConvexShape;
            lineHolder->setPointCount(4);
            lineHolder->setPoint(0, sf::Vector2f(_newX.at(i)-3, 308));
            lineHolder->setPoint(1, sf::Vector2f(_newX.at(i)+3, 308));
            lineHolder->setPoint(3, sf::Vector2f(_newX.at(i)-3, 300));
            lineHolder->setPoint(2, sf::Vector2f(_newX.at(i)+3, 300));
            lineHolder->setFillColor(sf::Color::Black);
            _plotLines.push_back(lineHolder);
        }

    return;
}

void ALinePlot::draw(sf::RenderTarget& window){
    // draws to window
    for(unsigned int i = 0; i< _plotLines.size(); i++){
        window.draw(*(_plotLines.at(i)));
    }
    for(unsigned int i = 0; i< _plotPoints.size(); i++){
        window.draw(*(_plotPoints.at(i)));
    }

    return;
}

std::vector<double> ALinePlot::getNewX() const{
    return _newX;
}
std::vector<double> ALinePlot::getNewY() const{
    return _newY;
}
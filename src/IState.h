#pragma once
#include"SFML/Graphics.hpp"	

class IState {
public:
    virtual void handleEvents(sf::RenderWindow& window) = 0;
    virtual void update() = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    virtual ~IState() = default;
};


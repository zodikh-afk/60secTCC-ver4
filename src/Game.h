#pragma once
#include <SFML/Graphics.hpp>
#include "IState.h"
#include "Player.h"
#include "Stew.h"
#include <iostream>
#include "MenuState.h"  
#include "RandomGenerator.h"
#include "WeaponDamageCalculator.h"


class Game {
public:
    Game();
    ~Game();
    RandomGenerator rng;
    WeaponDamageCalculator damageCalc;
    Player player;


    void run();
    void changeState(IState* newState);

    sf::RenderWindow window;  

private:
    sf::Font font;
    IState* currentState = nullptr;

    void processEvents();
    void update();
    void render();
};
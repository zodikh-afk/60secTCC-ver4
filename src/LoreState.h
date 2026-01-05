#pragma once
#include "IState.h"
#include <SFML/Graphics.hpp>

class Game;  

class LoreState : public IState {
public:
    LoreState(Game& game, sf::Font& font);

    void handleEvents(sf::RenderWindow& window) override;
    void update() override;
    void render(sf::RenderWindow& window) override;

private:
    Game& game;
    sf::Font& font;

    sf::Text title;
    sf::Text loreText;
    sf::Text backBtn;

    void layout();
};


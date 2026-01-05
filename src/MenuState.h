#pragma once

#include "IState.h"
#include <SFML/Graphics.hpp>
#include "Difficulty.h"

class Game;

class MenuState : public IState {
private:
    Game& game;
    sf::Font& font;

    sf::Text title;

    sf::Text btnStart;
    sf::Text btnLore;
    sf::Text btnExit;

    // --- Difficulty buttons ---
    sf::Text btnEasy;
    sf::Text btnNormal;
    sf::Text btnHard;

    Difficulty selectedDifficulty = Difficulty::Normal;

    void layout();
    bool isMouseOver(const sf::Text& t, sf::RenderWindow& window) const;

public:
    MenuState(Game& g, sf::Font& f);

    void handleEvents(sf::RenderWindow& window) override;
    void update() override;
    void render(sf::RenderWindow& window) override;
};

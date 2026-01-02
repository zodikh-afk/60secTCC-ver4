#pragma once
#include "IState.h"
#include <SFML/Graphics.hpp>

class Game;
class GameState;
class LoreState;

class MenuState : public IState {
public:
    MenuState(Game& game, sf::Font& font);

    void handleEvents(sf::RenderWindow& window) override;
    void update() override;
    void render(sf::RenderWindow& window) override;

private:
    Game& game;
    sf::Font& font;

    sf::Text title;
    sf::Text btnStart;
    sf::Text btnLore;
    sf::Text btnExit;

    bool isMouseOver(const sf::Text& t, sf::RenderWindow& window) const;
    void layout();
};

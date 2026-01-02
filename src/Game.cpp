#include "Game.h"

Game::Game() : window(sf::VideoMode::getDesktopMode(),"100 секунд",sf::Style::Fullscreen), rng(), damageCalc(rng), player(damageCalc)
{
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Не удалось загрузить шрифт!\n";
    }


    // Первое состояние — главное меню
    changeState(new MenuState (*this, font));
}

Game::~Game() {
    if (currentState)
        delete currentState;
}

void Game::changeState(IState* newState) {
    if (currentState)
        delete currentState;

    currentState = newState;
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents() {
    currentState->handleEvents(window);
}

void Game::update() {
    currentState->update();
}

void Game::render() {
    window.clear(sf::Color::Black);
    currentState->render(window);
    window.display();
}
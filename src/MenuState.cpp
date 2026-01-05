#include "MenuState.h"
#include "Game.h"
#include "GameState.h"
#include "LoreState.h"
#include "DifficultyManager.h"

// --- ctor ---
MenuState::MenuState(Game& g, sf::Font& f)
    : game(g), font(f)
{
    // --- Title ---
    title.setFont(font);
    title.setString(L"60 секунд до приходу ТЦК");
    title.setCharacterSize(60);
    title.setFillColor(sf::Color::White);

    // --- Main buttons ---
    btnStart.setFont(font);
    btnStart.setString(L"Почати гру");
    btnStart.setCharacterSize(48);
    btnStart.setFillColor(sf::Color::White);

    btnLore.setFont(font);
    btnLore.setString(L"Історія світу");
    btnLore.setCharacterSize(48);
    btnLore.setFillColor(sf::Color::White);

    btnExit.setFont(font);
    btnExit.setString(L"Вийти");
    btnExit.setCharacterSize(48);
    btnExit.setFillColor(sf::Color::White);

    // --- Difficulty buttons ---
    btnEasy.setFont(font);
    btnEasy.setString(L"Легко");
    btnEasy.setCharacterSize(36);

    btnNormal.setFont(font);
    btnNormal.setString(L"Нормально");
    btnNormal.setCharacterSize(36);

    btnHard.setFont(font);
    btnHard.setString(L"Складно");
    btnHard.setCharacterSize(36);

    // default difficulty
    DifficultyManager::Instance().SetDifficulty(Difficulty::Normal);

    layout();
}

// --- layout ---
void MenuState::layout()
{
    const float W = static_cast<float>(game.window.getSize().x);
    const float centerX = W / 2.f;

    // temporary reset
    title.setPosition(0.f, 0.f);
    btnStart.setPosition(0.f, 0.f);
    btnLore.setPosition(0.f, 0.f);
    btnExit.setPosition(0.f, 0.f);
    btnEasy.setPosition(0.f, 0.f);
    btnNormal.setPosition(0.f, 0.f);
    btnHard.setPosition(0.f, 0.f);

    // center alignment
    title.setPosition(centerX - title.getGlobalBounds().width / 2.f, 80.f);
    btnStart.setPosition(centerX - btnStart.getGlobalBounds().width / 2.f, 260.f);

    // difficulty row
    btnEasy.setPosition(centerX - 220.f, 340.f);
    btnNormal.setPosition(centerX - btnNormal.getGlobalBounds().width / 2.f, 340.f);
    btnHard.setPosition(centerX + 140.f, 340.f);

    btnLore.setPosition(centerX - btnLore.getGlobalBounds().width / 2.f, 430.f);
    btnExit.setPosition(centerX - btnExit.getGlobalBounds().width / 2.f, 520.f);
}

// --- helper ---
bool MenuState::isMouseOver(const sf::Text& t, sf::RenderWindow& window) const
{
    sf::Vector2i m = sf::Mouse::getPosition(window);
    return t.getGlobalBounds().contains(
        static_cast<float>(m.x),
        static_cast<float>(m.y)
    );
}

// --- events ---
void MenuState::handleEvents(sf::RenderWindow& window)
{
    sf::Event e;
    while (window.pollEvent(e)) {
        if (e.type == sf::Event::Closed)
            window.close();

        if (e.type == sf::Event::Resized)
            layout();

        if (e.type == sf::Event::MouseButtonPressed &&
            e.mouseButton.button == sf::Mouse::Left)
        {
            if (isMouseOver(btnEasy, window)) {
                selectedDifficulty = Difficulty::Easy;
                DifficultyManager::Instance().SetDifficulty(Difficulty::Easy);
            }
            else if (isMouseOver(btnNormal, window)) {
                selectedDifficulty = Difficulty::Normal;
                DifficultyManager::Instance().SetDifficulty(Difficulty::Normal);
            }
            else if (isMouseOver(btnHard, window)) {
                selectedDifficulty = Difficulty::Hard;
                DifficultyManager::Instance().SetDifficulty(Difficulty::Hard);
            }
            else if (isMouseOver(btnStart, window)) {
                game.changeState(new GameState(game, game.player, font));
            }
            else if (isMouseOver(btnLore, window)) {
                game.changeState(new LoreState(game, font));
            }
            else if (isMouseOver(btnExit, window)) {
                window.close();
            }
        }
    }
}

// --- update ---
void MenuState::update()
{
    // reset colors
    btnStart.setFillColor(sf::Color::White);
    btnLore.setFillColor(sf::Color::White);
    btnExit.setFillColor(sf::Color::White);

    btnEasy.setFillColor(sf::Color::White);
    btnNormal.setFillColor(sf::Color::White);
    btnHard.setFillColor(sf::Color::White);

    // selected difficulty
    if (selectedDifficulty == Difficulty::Easy)
        btnEasy.setFillColor(sf::Color::Green);
    else if (selectedDifficulty == Difficulty::Normal)
        btnNormal.setFillColor(sf::Color::Green);
    else if (selectedDifficulty == Difficulty::Hard)
        btnHard.setFillColor(sf::Color::Green);

    // hover
    if (isMouseOver(btnStart, game.window)) btnStart.setFillColor(sf::Color::Yellow);
    if (isMouseOver(btnLore, game.window))  btnLore.setFillColor(sf::Color::Yellow);
    if (isMouseOver(btnExit, game.window))  btnExit.setFillColor(sf::Color::Yellow);

    if (isMouseOver(btnEasy, game.window))   btnEasy.setFillColor(sf::Color::Yellow);
    if (isMouseOver(btnNormal, game.window)) btnNormal.setFillColor(sf::Color::Yellow);
    if (isMouseOver(btnHard, game.window))   btnHard.setFillColor(sf::Color::Yellow);
}

// --- render ---
void MenuState::render(sf::RenderWindow& window)
{
    window.draw(title);
    window.draw(btnStart);
    window.draw(btnEasy);
    window.draw(btnNormal);
    window.draw(btnHard);
    window.draw(btnLore);
    window.draw(btnExit);
}

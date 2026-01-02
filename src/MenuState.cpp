#include "MenuState.h"
#include "Game.h"
#include "GameState.h"
#include "LoreState.h"


MenuState::MenuState(Game& g, sf::Font& f) : game(g), font(f)
{
    // Заголовок
    title.setFont(font);
    title.setString(L"60 секунд до приходу ТЦК");
    title.setCharacterSize(60);
    title.setFillColor(sf::Color::White);

    // Кнопки
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

    layout();
}

void MenuState::layout() {
    const float W = static_cast<float>(game.window.getSize().x);
    const float centerX = W / 2.f;

    // Ñíà÷àëà âðåìåííî ñòàâèì íà (0,0), ÷òîáû êîððåêòíî ïîëó÷èòü bounds
    title.setPosition(0.f, 0.f);
    btnStart.setPosition(0.f, 0.f);
    btnLore.setPosition(0.f, 0.f);
    btnExit.setPosition(0.f, 0.f);

    // Öåíòðîâêà ïî øèðèíå
    title.setPosition(centerX - title.getGlobalBounds().width / 2.f, 80.f);
    btnStart.setPosition(centerX - btnStart.getGlobalBounds().width / 2.f, 300.f);
    btnLore.setPosition(centerX - btnLore.getGlobalBounds().width / 2.f, 400.f);
    btnExit.setPosition(centerX - btnExit.getGlobalBounds().width / 2.f, 500.f);
}

bool MenuState::isMouseOver(const sf::Text& t, sf::RenderWindow& window) const {
    sf::Vector2i m = sf::Mouse::getPosition(window);
    return t.getGlobalBounds().contains(static_cast<float>(m.x), static_cast<float>(m.y));
}

void MenuState::handleEvents(sf::RenderWindow& window) {
    sf::Event e;
    while (window.pollEvent(e)) {
        if (e.type == sf::Event::Closed) {
            window.close();
        }

        if (e.type == sf::Event::Resized) {
            // При изменении размера — перелэйаутим, чтобы оставалось по центру
            layout();
        }

        if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left) {
            if (isMouseOver(btnStart, window)) {
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

void MenuState::update() {
    // Подсветка при наведении
    btnStart.setFillColor(sf::Color::White);
    btnLore.setFillColor(sf::Color::White);
    btnExit.setFillColor(sf::Color::White);

    if (isMouseOver(btnStart, game.window)) btnStart.setFillColor(sf::Color::Yellow);
    if (isMouseOver(btnLore, game.window)) btnLore.setFillColor(sf::Color::Yellow);
    if (isMouseOver(btnExit, game.window)) btnExit.setFillColor(sf::Color::Yellow);
}

void MenuState::render(sf::RenderWindow& window) {
    window.draw(title);
    window.draw(btnStart);
    window.draw(btnLore);
    window.draw(btnExit);
}

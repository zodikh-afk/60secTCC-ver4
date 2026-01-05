#include "LoreState.h"
#include "Game.h"
#include "MenuState.h"

LoreState::LoreState(Game& g, sf::Font& f) : game(g), font(f)
{
    float W = g.window.getSize().x;
    float centerX = W / 2.f;

    // Заголовок
    title.setFont(font);
    title.setCharacterSize(60);
    title.setFillColor(sf::Color::White);
    title.setString(L"Історія Світу");

    loreText.setFont(font);
    loreText.setCharacterSize(32);
    loreText.setFillColor(sf::Color::White);
    loreText.setString(
        L"Cвіт занурився у хаос.\n"
        L"ТЦК дозволили вламуватись у домівлі людей.\n"
		L"У тебе є рівно 60 секунд до їх приходу\n"
        L"Скоріше шукай речі і ховайся в підвал\n"
        L"Кожне рішення може стати останнім.\n"
        L"Ти повинен вижити будь–якою ціною..."
    );

    loreText.setPosition(80.f, 200.f);

    // Кнопка Назад
    backBtn.setFont(font);
    backBtn.setCharacterSize(40);
    backBtn.setFillColor(sf::Color::White);
    backBtn.setString(L"Назад");

    layout();
}

void LoreState::layout() 
{
    float W = game.window.getSize().x;
    float centerX = W / 2.f;

    title.setPosition(centerX - title.getGlobalBounds().width / 2.f, 60.f);

    backBtn.setPosition(80.f, game.window.getSize().y - 120.f);
}

void LoreState::handleEvents(sf::RenderWindow& window) {
    sf::Event e;

    while (window.pollEvent(e)) {

        if (e.type == sf::Event::Closed)
            window.close();

        if (e.type == sf::Event::KeyPressed) {
            // ESC → назад
            if (e.key.code == sf::Keyboard::Escape) {
                game.changeState(new MenuState(game, font));
            }
        }

        if (e.type == sf::Event::MouseButtonPressed &&
            e.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2i mp = sf::Mouse::getPosition(window);

            if (backBtn.getGlobalBounds().contains(
                (float)mp.x, (float)mp.y))
            {
                game.changeState(new MenuState(game, font));
            }
        }

        if (e.type == sf::Event::Resized) {
            layout();
        }
    }
}

void LoreState::update() {
    // Подсветка кнопки при наведении
    sf::Vector2i mp = sf::Mouse::getPosition(game.window);

    if (backBtn.getGlobalBounds().contains((float)mp.x, (float)mp.y))
        backBtn.setFillColor(sf::Color::Yellow);
    else
        backBtn.setFillColor(sf::Color::White);
}

void LoreState::render(sf::RenderWindow& window) {
    window.draw(title);
    window.draw(loreText);
    window.draw(backBtn);
}

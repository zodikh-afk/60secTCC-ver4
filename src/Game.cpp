#include "Game.h"
#include <iostream>

// --- ctor ---
Game::Game()
    : window(sf::VideoMode::getDesktopMode(),
             "100 секунд",
             sf::Style::Fullscreen),
      rng(),
      damageCalc(rng),
      player(damageCalc),
      itemFactory(rng)   // 👈 фабрика отримує RNG (DI)
{
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Не удалось загрузить шрифт!\n";
    }

    // Перше стан — меню
    changeState(new MenuState(*this, font));
}

// --- dtor ---
Game::~Game()
{
    if (currentState)
        delete currentState;
}

// --- changeState ---
void Game::changeState(IState* newState)
{
    if (currentState)
        delete currentState;

    currentState = newState;
}

// --- main loop ---
void Game::run()
{
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

// --- events ---
void Game::processEvents()
{
    currentState->handleEvents(window);
}

// --- update ---
void Game::update()
{
    currentState->update();

    // ⚠️ ТИМЧАСОВО ДЛЯ ТЕСТУ
    // Пізніше це буде кнопка або меню
    static bool testOnce = false;
    if (!testOnce) {
        simulateScavenge();
        testOnce = true;
    }
}

// --- render ---
void Game::render()
{
    window.clear(sf::Color::Black);
    currentState->render(window);
    window.display();
}

void Game::simulateScavenge()
{
    std::cout << "Scavenging started...\n";

    auto item = itemFactory.createRandomItem();

    // Якщо це зброя — екіпіруємо
    if (auto weaponItem = dynamic_cast<WeaponItem*>(item.get())) {
        player.SetWeapon(weaponItem->getWeapon());
        std::cout << "Equipped weapon from scavenging.\n";
    }

    if (player.PickUpItem(std::move(item))) {
        std::wcout << player.GetInventoryString();
    }
    else {
        std::cout << "Inventory is full!\n";
    }
}

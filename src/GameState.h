#pragma once
#include "IState.h"
#include "Game.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <memory>
#include <cmath>
#include "IPlayer.h"
#include "HouseSystem.h" // пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ

class Game;

enum class GamePhase {
    COUNTDOWN,
    GAME_RUNNING,
    NEXT_LEVEL,
    BASEMENT 
};

enum class HouseView {
    SELECT_ROOM,
    INSIDE_ROOM,
    INSIDE_FURNITURE
};

class GameState : public IState {
public:
    GameState(Game& g, IPlayer& p, sf::Font& f);


    // Ці пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ camelCase, пїЅпїЅ пїЅпїЅпїЅпїЅ пїЅ IState
    void handleEvents(sf::RenderWindow& window) override;
    void update() override;
    void render(sf::RenderWindow& window) override;

private:
    Game& game;
    IPlayer& player;
    sf::Font& font;
    void ConsumeDailyResources(IPlayer& player);

    // --- пїЅпїЅпїЅпїЅпїЅ snake_case ---
    GamePhase current_phase;
    sf::Clock dt_clock;
    float timer_accumulator;
    int start_countdown_val;
    float main_game_timer;

    sf::Text center_text;
    sf::Text timer_text;
    sf::Text inventory_text;
    sf::Text back_button;

    // пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ
    HouseView current_view;
    std::vector<Room> house;
    int selected_room_index = -1;   
    int selected_furniture_index = -1;

    // --- пїЅпїЅпїЅпїЅпїЅпїЅ PascalCase ---
    void InitHouse();
    bool IsMouseOver(const sf::Text& t, sf::RenderWindow& window) const;
    // ===== ФАЗА 2: ПІДВАЛ =====
    int current_day = 1;

    sf::Texture basement_bg_tex;
    sf::Sprite  basement_bg_sprite;

    sf::Text day_text;

    // Кнопка щоденника
    sf::RectangleShape diary_button;
    sf::Text diary_button_text;

    // Вікно щоденника
    bool diary_open = false;
    sf::RectangleShape diary_panel;
    sf::Text diary_panel_text;
    std::vector<std::wstring> diary_lines;
    
        // ===== РЕСУРСИ ВИЖИВАННЯ =====
    int food_units = 0;   // умовні порції їжі
    int water_units = 0;  // умовні порції води

    int FOOD_PER_DAY = 1;   // скільки їжі витрачається за день
    int WATER_PER_DAY = 1;  // скільки води витрачається за день

    bool is_dead = false;

    // Текст ресурсів в щоденнику
    sf::Text resources_text;

    // Кнопка "Наступний день" (в щоденнику знизу справа)
    sf::RectangleShape next_day_button;
    sf::Text next_day_button_text;


    void UpdateBasementUIPositions(sf::RenderWindow& window);
    void RebuildDiaryText();
    bool IsMouseOverRect(const sf::RectangleShape& r, sf::RenderWindow& window) const;
    void InitSurvivalFromInventory();
    void NextDay();
};


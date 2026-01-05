#include "GameState.h"
#include "Stew.h"
#include "Water.h" // Підключаємо Воду (якщо є такий клас)
#include <iostream>
#include <cmath>
#include <algorithm> // Для std::shuffle
#include <random>    // Для генератора випадкових чисел
#include <sstream>
#include "DifficultyManager.h"

void GameState::ConsumeDailyResources(IPlayer& player)
{
    float multiplier =
        DifficultyManager::Instance().GetDailyConsumptionMultiplier();

    int foodLoss  = static_cast<int>(10 * multiplier);
    int waterLoss = static_cast<int>(8  * multiplier);

    // ↓ безпечне приведення
    if (auto* p = dynamic_cast<Player*>(&player)) {
        p->ConsumeFood(foodLoss);
        p->ConsumeWater(waterLoss);
    }
}


GameState::GameState(Game& g, IPlayer& p, sf::Font& f)
    : game(g), player(p), font(f)
{
    // Ініціалізація змінних
    current_phase = GamePhase::COUNTDOWN;
    start_countdown_val = 3;
    timer_accumulator = 0.0f;
    main_game_timer = 60.0f;
    dt_clock.restart();

    // Налаштування тексту по центру (Відлік)
    center_text.setFont(font);
    center_text.setCharacterSize(100);
    center_text.setFillColor(sf::Color::Yellow);
    center_text.setString(std::to_wstring(start_countdown_val));

    sf::FloatRect textRect = center_text.getLocalBounds();
    center_text.setOrigin(textRect.left + textRect.width / 2.0f,
        textRect.top + textRect.height / 2.0f);
    center_text.setPosition(game.window.getSize().x / 2.0f, game.window.getSize().y / 2.0f);

    // Таймер
    timer_text.setFont(font);
    timer_text.setCharacterSize(40);
    timer_text.setFillColor(sf::Color::Red);
    timer_text.setPosition(game.window.getSize().x - 150.f, 10.f);

    // Інвентар
    inventory_text.setFont(font);
    inventory_text.setCharacterSize(20);
    inventory_text.setFillColor(sf::Color::White);
    inventory_text.setPosition(50, 50);

    // Ініціалізація дому
    current_view = HouseView::SELECT_ROOM;
    InitHouse();

    // Кнопка Назад
    back_button.setFont(font);
    back_button.setString(L"<< Назад");
    back_button.setCharacterSize(30);
    back_button.setFillColor(sf::Color::Yellow);
    back_button.setPosition(50, game.window.getSize().y - 100.f);
    // ====== ФАЗА 2: ПІДВАЛ ======
    current_day = 1;

    // Текст дня (справа зверху)
    day_text.setFont(font);
    day_text.setCharacterSize(36);
    day_text.setFillColor(sf::Color::White);
    day_text.setPosition(game.window.getSize().x - 220.f, 10.f);
    day_text.setString(L"Day: 1");

    // Фон підвалу (статична картинка)
    // Постав свій файл, наприклад: assets/basement.png
    if (basement_bg_tex.loadFromFile("assets/basement.png")) {
        basement_bg_sprite.setTexture(basement_bg_tex);

        // Масштаб під розмір вікна
        auto ws = game.window.getSize();
        auto ts = basement_bg_tex.getSize();
        if (ts.x > 0 && ts.y > 0) {
            basement_bg_sprite.setScale(
                (float)ws.x / (float)ts.x,
                (float)ws.y / (float)ts.y
            );
        }
    }
    // якщо файл не знайдено — просто буде порожній (можеш намалювати rect у render)

    // Кнопка щоденника (знизу справа)
    diary_button.setSize(sf::Vector2f(260.f, 70.f));
    diary_button.setFillColor(sf::Color(30, 30, 30, 220));
    diary_button.setOutlineThickness(3.f);
    diary_button.setOutlineColor(sf::Color::White);

    diary_button_text.setFont(font);
    diary_button_text.setCharacterSize(28);
    diary_button_text.setFillColor(sf::Color::White);
    diary_button_text.setString(L"Щоденник");

    // Панель щоденника
    diary_panel.setSize(sf::Vector2f(600.f, 500.f));
    diary_panel.setFillColor(sf::Color(0, 0, 0, 200));
    diary_panel.setOutlineThickness(3.f);
    diary_panel.setOutlineColor(sf::Color::White);
    diary_panel.setPosition(60.f, 120.f);

    diary_panel_text.setFont(font);
    diary_panel_text.setCharacterSize(22);
    diary_panel_text.setFillColor(sf::Color::White);
    diary_panel_text.setPosition(diary_panel.getPosition().x + 20.f, diary_panel.getPosition().y + 140.f);


        // Текст ресурсів (у щоденнику)
    resources_text.setFont(font);
    resources_text.setCharacterSize(22);
    resources_text.setFillColor(sf::Color::White);

    // Кнопка "Наступний день"
    next_day_button.setSize(sf::Vector2f(220.f, 60.f));
    next_day_button.setFillColor(sf::Color(30, 30, 30, 220));
    next_day_button.setOutlineThickness(3.f);
    next_day_button.setOutlineColor(sf::Color::White);

    next_day_button_text.setFont(font);
    next_day_button_text.setCharacterSize(24);
    next_day_button_text.setFillColor(sf::Color::White);
    next_day_button_text.setString(L"Наступний день");

    // Стартові записи щоденника (приклад)
    diary_lines.clear();
    diary_lines.push_back(L"День 1: Я у підвалі. Треба вижити...");


}

void GameState::InitHouse() {
    // --- 1. КУХНЯ ---
    Room kitchen;
    kitchen.name = L"Кухня";

    Furniture fridge;
    fridge.name = L"Холодильник";
    fridge.slots.push_back(SearchSlot(L"Верхня полиця", std::make_unique<Stew>()));
    fridge.slots.push_back(SearchSlot(L"Нижня полиця", nullptr));
    fridge.slots.push_back(SearchSlot(L"Морозилка", std::make_unique<Stew>())); // Додали морозилку
    kitchen.furniture.push_back(std::move(fridge));

    Furniture table;
    table.name = L"Обідній стіл";
    table.slots.push_back(SearchSlot(L"На столі", std::make_unique<Water>())); // Тут вода
    table.slots.push_back(SearchSlot(L"Під столом", nullptr));
    kitchen.furniture.push_back(std::move(table));

    Furniture oven;
    oven.name = L"Плита";
    oven.slots.push_back(SearchSlot(L"Духовка", std::make_unique<Stew>()));
    kitchen.furniture.push_back(std::move(oven));

    // --- 2. СПАЛЬНЯ ---
    Room bedroom;
    bedroom.name = L"Спальня";

    Furniture wardrobe;
    wardrobe.name = L"Шафа для одягу";
    wardrobe.slots.push_back(SearchSlot(L"Кишеня пальто", nullptr));
    wardrobe.slots.push_back(SearchSlot(L"Верхня полиця", std::make_unique<Water>()));
    wardrobe.slots.push_back(SearchSlot(L"Нижня шухляда", nullptr));
    bedroom.furniture.push_back(std::move(wardrobe));

    Furniture bed;
    bed.name = L"Ліжко";
    bed.slots.push_back(SearchSlot(L"Під подушкою", std::make_unique<Stew>()));
    bed.slots.push_back(SearchSlot(L"Під ліжком", nullptr));
    bedroom.furniture.push_back(std::move(bed));

    // --- 3. ВАННА (НОВА) ---
    Room bathroom;
    bathroom.name = L"Ванна кімната";

    Furniture cabinet;
    cabinet.name = L"Дзеркальна шафка";
    cabinet.slots.push_back(SearchSlot(L"За дзеркалом", std::make_unique<Water>()));
    cabinet.slots.push_back(SearchSlot(L"Нижня полиця", nullptr));
    bathroom.furniture.push_back(std::move(cabinet));

    Furniture bath;
    bath.name = L"Ванна";
    bath.slots.push_back(SearchSlot(L"На бортику", nullptr));
    bathroom.furniture.push_back(std::move(bath));

    // --- 4. ВІТАЛЬНЯ (НОВА) ---
    Room livingroom;
    livingroom.name = L"Вітальня";

    Furniture sofa;
    sofa.name = L"Диван";
    sofa.slots.push_back(SearchSlot(L"Між подушками", std::make_unique<Stew>()));
    livingroom.furniture.push_back(std::move(sofa));

    // Додаємо кімнати в дім
    house.push_back(std::move(kitchen));
    house.push_back(std::move(bedroom));
    house.push_back(std::move(bathroom));
    house.push_back(std::move(livingroom));

    // --- РАНДОМІЗАЦІЯ (ПЕРЕМІШУВАННЯ) ---
    std::random_device rd;
    std::mt19937 g(rd());

    // 1. Перемішуємо порядок кімнат
    std::shuffle(house.begin(), house.end(), g);

    // 2. Перемішуємо меблі всередині кожної кімнати та слоти в меблях
    for (auto& room : house) {
        std::shuffle(room.furniture.begin(), room.furniture.end(), g);

        for (auto& furn : room.furniture) {
            std::shuffle(furn.slots.begin(), furn.slots.end(), g);
        }
    }
}

bool GameState::IsMouseOver(const sf::Text& t, sf::RenderWindow& window) const {
    sf::Vector2i m = sf::Mouse::getPosition(window);
    sf::Vector2f world_pos = window.mapPixelToCoords(m);
    return t.getGlobalBounds().contains(world_pos);
}

void GameState::handleEvents(sf::RenderWindow& window) {
    sf::Event e;
    while (window.pollEvent(e)) {
        if (e.type == sf::Event::Closed) window.close();
        if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape) window.close();

        if (e.type == sf::Event::Resized) {
            center_text.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
            timer_text.setPosition(window.getSize().x - 150.f, 10.f);
        }

        if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left) {
            if (current_phase == GamePhase::GAME_RUNNING) {
                // Кнопка Назад
                if (current_view != HouseView::SELECT_ROOM) {
                    if (IsMouseOver(back_button, window)) {
                        if (current_view == HouseView::INSIDE_FURNITURE) current_view = HouseView::INSIDE_ROOM;
                        else if (current_view == HouseView::INSIDE_ROOM) current_view = HouseView::SELECT_ROOM;
                        return;
                    }
                }

                // Логіка вибору (Room -> Furniture -> Slot)
                if (current_view == HouseView::SELECT_ROOM) {
                    for (size_t i = 0; i < house.size(); ++i) {
                        sf::Text room_text;
                        room_text.setFont(font);
                        room_text.setString(house[i].name);
                        room_text.setCharacterSize(40);
                        // Позиція вже не хардкодна по суті, бо house перемішаний
                        room_text.setPosition(100.f, 150.f + static_cast<float>(i) * 60.f);

                        if (IsMouseOver(room_text, window)) {
                            selected_room_index = static_cast<int>(i);
                            current_view = HouseView::INSIDE_ROOM;
                            break;
                        }
                    }
                }
                else if (current_view == HouseView::INSIDE_ROOM) {
                    Room& room = house[selected_room_index];
                    for (size_t i = 0; i < room.furniture.size(); ++i) {
                        sf::Text furn_text;
                        furn_text.setFont(font);
                        furn_text.setString(room.furniture[i].name);
                        furn_text.setCharacterSize(40);
                        furn_text.setPosition(100.f, 150.f + static_cast<float>(i) * 60.f);

                        if (IsMouseOver(furn_text, window)) {
                            selected_furniture_index = static_cast<int>(i);
                            current_view = HouseView::INSIDE_FURNITURE;
                            break;
                        }
                    }
                }
                else if (current_view == HouseView::INSIDE_FURNITURE) {
                    Furniture& furn = house[selected_room_index].furniture[selected_furniture_index];

                    for (size_t i = 0; i < furn.slots.size(); ++i) {
                        if (furn.slots[i].is_searched && furn.slots[i].item_inside == nullptr) continue;

                        sf::Text slot_text;
                        slot_text.setFont(font);
                        slot_text.setCharacterSize(35);
                        slot_text.setPosition(100.f, 150.f + static_cast<float>(i) * 60.f);

                        if (!furn.slots[i].is_searched) {
                            slot_text.setString(furn.slots[i].hidden_name);
                            slot_text.setFillColor(sf::Color::White);
                        }
                        else {
                            std::wstring full_text =L"Забрати: " +std::wstring(furn.slots[i].item_inside->getName().begin(),furn.slots[i].item_inside->getName().end());

                            slot_text.setString(full_text);
                            slot_text.setFillColor(sf::Color::Green);
                        }

                        if (IsMouseOver(slot_text, window)) {
                            if (!furn.slots[i].is_searched) {
                                furn.slots[i].is_searched = true;
                            }
                            else if (furn.slots[i].item_inside) {
                                game.player.PickUpItem(std::move(furn.slots[i].item_inside));
                            }
                            break;
                        }
                    }
                }
            }
                else if (current_phase == GamePhase::BASEMENT) {
                // натиснули на кнопку щоденника
                if (IsMouseOverRect(diary_button, window)) {
                    diary_open = !diary_open;
                    return;
                }
                // якщо щоденник відкритий — даємо натискати кнопку наступного дня
                if (diary_open && IsMouseOverRect(next_day_button, window)) {
                    NextDay();
                    return;
                }

            }
        }
    }
}

void GameState::update() {
    float dt = dt_clock.restart().asSeconds();

    if (current_phase == GamePhase::COUNTDOWN) {
        timer_accumulator += dt;
        if (timer_accumulator >= 1.0f) {
            start_countdown_val--;
            timer_accumulator = 0.0f;
            if (start_countdown_val > 0) {
                center_text.setString(std::to_wstring(start_countdown_val));
            }
            else {
                current_phase = GamePhase::GAME_RUNNING;
                center_text.setString(L"");
            }
            sf::FloatRect textRect = center_text.getLocalBounds();
            center_text.setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height / 2.f);
            center_text.setPosition(game.window.getSize().x / 2.f, game.window.getSize().y / 2.f);
        }
    }
    else if (current_phase == GamePhase::GAME_RUNNING) {
        main_game_timer -= dt;
        int seconds_left = static_cast<int>(std::ceil(main_game_timer));
        timer_text.setString(std::to_wstring(seconds_left));

        if (main_game_timer <= 0.0f) {
            main_game_timer = 0.0f;

            // Переходимо у фазу підвалу
            current_phase = GamePhase::BASEMENT;

            // Скидаємо / стартуємо день і щоденник
            current_day = 1;
            InitSurvivalFromInventory();
            resources_text.setString(L"Їжа: " + std::to_wstring(food_units) + L"\nВода: " + std::to_wstring(water_units));

            day_text.setString(L"Day: " + std::to_wstring(current_day));

            diary_open = false;
            diary_lines.clear();
            diary_lines.push_back(L"День 1: Я у підвалі. Треба вижити...");
            RebuildDiaryText();

            // Позиції UI під поточне вікно
            UpdateBasementUIPositions(game.window);
        }

    }
}

void GameState::render(sf::RenderWindow& window) {
    if (current_phase == GamePhase::COUNTDOWN) {
        window.draw(center_text);
    }
    else if (current_phase == GamePhase::GAME_RUNNING) {

        std::wstring info = player.GetInventoryString();
        inventory_text.setString(info);
        window.draw(inventory_text);
        window.draw(timer_text);

        // --- ЗАГОЛОВОК ПО ЦЕНТРУ ---
        sf::Text title;
        title.setFont(font);
        title.setCharacterSize(50);
        title.setFillColor(sf::Color::Cyan);

        // Встановлюємо текст залежно від вигляду
        if (current_view == HouseView::SELECT_ROOM) {
            title.setString(L"Оберіть кімнату:");
        }
        else if (current_view == HouseView::INSIDE_ROOM) {
            title.setString(house[selected_room_index].name);
        }
        else if (current_view == HouseView::INSIDE_FURNITURE) {
            title.setString(house[selected_room_index].furniture[selected_furniture_index].name);
        }

        // ЦЕНТРУВАННЯ ТЕКСТУ
        sf::FloatRect titleRect = title.getLocalBounds();
        title.setOrigin(titleRect.left + titleRect.width / 2.0f, titleRect.top);
        title.setPosition(window.getSize().x / 2.0f, 20.f); // По центру зверху

        window.draw(title);

        // Малювання списків
        if (current_view == HouseView::SELECT_ROOM) {
            for (size_t i = 0; i < house.size(); ++i) {
                sf::Text item;
                item.setFont(font); 
                item.setString(house[i].name);
                item.setCharacterSize(40);
                item.setFillColor(sf::Color::White);
                item.setPosition(100.f, 150.f + static_cast<float>(i) * 60.f);
                if (IsMouseOver(item, window)) item.setFillColor(sf::Color::Yellow);
                window.draw(item);
            }
        }
        else if (current_view == HouseView::INSIDE_ROOM) {
            window.draw(back_button);
            Room& room = house[selected_room_index];
            for (size_t i = 0; i < room.furniture.size(); ++i) {
                sf::Text item;
                item.setFont(font);
                item.setString(room.furniture[i].name);
                item.setCharacterSize(40);
                item.setFillColor(sf::Color::White);
                item.setPosition(100.f, 150.f + static_cast<float>(i) * 60.f);
                if (IsMouseOver(item, window)) item.setFillColor(sf::Color::Yellow);
                window.draw(item);
            }
        }
        else if (current_view == HouseView::INSIDE_FURNITURE) {
            window.draw(back_button);
            Furniture& furn = house[selected_room_index].furniture[selected_furniture_index];
            for (size_t i = 0; i < furn.slots.size(); ++i) {
                if (furn.slots[i].is_searched && furn.slots[i].item_inside == nullptr) continue;

                sf::Text item;
                item.setFont(font);
                item.setCharacterSize(35);
                item.setPosition(100.f, 150.f + static_cast<float>(i) * 60.f);

                if (!furn.slots[i].is_searched) {
                    item.setString(furn.slots[i].hidden_name);
                    item.setFillColor(sf::Color::White);
                }
                else {
                    std::wstring full_text =L"Забрати: " +std::wstring(furn.slots[i].item_inside->getName().begin(),furn.slots[i].item_inside->getName().end());

                    item.setString(full_text);
                    item.setFillColor(sf::Color::Green);
                }
                if (IsMouseOver(item, window)) item.setFillColor(sf::Color::Yellow);
                window.draw(item);
            }
        }
    }
    else if (current_phase == GamePhase::NEXT_LEVEL) {
        window.draw(center_text);
    }
    else if (current_phase == GamePhase::BASEMENT) {

    // 1) Фон
    if (basement_bg_tex.getSize().x > 0) {
        window.draw(basement_bg_sprite);
    } else {
        // fallback якщо картинки нема
        sf::RectangleShape bg(sf::Vector2f((float)window.getSize().x, (float)window.getSize().y));
        bg.setFillColor(sf::Color(20, 20, 20));
        window.draw(bg);
    }

    // 2) UI позиції (щоб точно не “поїхало”)
    UpdateBasementUIPositions(window);

    // 3) День справа зверху
    window.draw(day_text);

    // 4) Кнопка щоденника справа знизу
    // hover ефект
    if (IsMouseOverRect(diary_button, window)) {
        diary_button.setFillColor(sf::Color(50, 50, 50, 230));
    } else {
        diary_button.setFillColor(sf::Color(30, 30, 30, 220));
    }

    window.draw(diary_button);
    window.draw(diary_button_text);
    resources_text.setString(L"Їжа: " + std::to_wstring(food_units) + L"\nВода: " + std::to_wstring(water_units));

    // 5) Панель щоденника (якщо відкрита)
    if (diary_open) {
        window.draw(diary_panel);

        // ресурси
        window.draw(resources_text);

        // текст щоденника (зсуваємо вниз, щоб не перекривало ресурси)
        window.draw(diary_panel_text);

        // hover ефект для next day
        if (IsMouseOverRect(next_day_button, window)) {
            next_day_button.setFillColor(sf::Color(50, 50, 50, 230));
        } else {
            next_day_button.setFillColor(sf::Color(30, 30, 30, 220));
        }

        window.draw(next_day_button);
        window.draw(next_day_button_text);
    }

}



    
}
bool GameState::IsMouseOverRect(const sf::RectangleShape& r, sf::RenderWindow& window) const {
    sf::Vector2i m = sf::Mouse::getPosition(window);
    sf::Vector2f w = window.mapPixelToCoords(m);
    return r.getGlobalBounds().contains(w);
}

void GameState::UpdateBasementUIPositions(sf::RenderWindow& window) {
    auto ws = window.getSize();

    // day_text справа зверху
    day_text.setPosition(ws.x - 220.f, 10.f);

    // кнопка щоденника знизу справа
    diary_button.setPosition(ws.x - diary_button.getSize().x - 30.f, ws.y - diary_button.getSize().y - 30.f);

    // центруємо текст на кнопці
    sf::FloatRect tr = diary_button_text.getLocalBounds();
    diary_button_text.setOrigin(tr.left + tr.width / 2.f, tr.top + tr.height / 2.f);
    diary_button_text.setPosition(
        diary_button.getPosition().x + diary_button.getSize().x / 2.f,
        diary_button.getPosition().y + diary_button.getSize().y / 2.f
    );
        // Всередині панелі щоденника: ресурси (під заголовком)
    resources_text.setPosition(diary_panel.getPosition().x + 20.f,
                            diary_panel.getPosition().y + 80.f);

    // Кнопка "Наступний день" — внизу справа в межах панелі
    next_day_button.setPosition(
        diary_panel.getPosition().x + diary_panel.getSize().x - next_day_button.getSize().x - 20.f,
        diary_panel.getPosition().y + diary_panel.getSize().y - next_day_button.getSize().y - 20.f
    );

    // Центруємо текст на кнопці
    sf::FloatRect ntr = next_day_button_text.getLocalBounds();
    next_day_button_text.setOrigin(ntr.left + ntr.width / 2.f, ntr.top + ntr.height / 2.f);
    next_day_button_text.setPosition(
        next_day_button.getPosition().x + next_day_button.getSize().x / 2.f,
        next_day_button.getPosition().y + next_day_button.getSize().y / 2.f
    );

}

void GameState::RebuildDiaryText() {
    
    std::wstringstream ss;

    ss << L"Щоденник\n\n";
    // показуємо останні ~12 рядків (щоб не вилізло за панель)
    int start = 0;
    if ((int)diary_lines.size() > 12) start = (int)diary_lines.size() - 12;

    for (int i = start; i < (int)diary_lines.size(); ++i) {
        ss << L"• " << diary_lines[i] << L"\n";
    }
    diary_panel_text.setString(ss.str());
}
void GameState::InitSurvivalFromInventory() {
    // якщо в Item є назва українською (як у тебе), рахуємо по імені
    // "Тушонка" = їжа, "Вода" = вода
    food_units = 0;
    water_units = 0;

    // Тут припускаю, що ти можеш отримати інвентар (inventory приватний у Player)
    // Тому найпростіше зараз: парсимо текст інвентарю.
    // (Краще потім зробити Player::CountItemByName())
    std::wstring inv = player.GetInventoryString();

    auto countInText = [&](const std::wstring& key) -> int {
        // шукаємо рядок виду "- Вода - x3 ..."
        size_t pos = inv.find(key);
        if (pos == std::wstring::npos) return 0;

        // шукаємо "x" після назви
        size_t xPos = inv.find(L"x", pos);
        if (xPos == std::wstring::npos) return 0;

        // читаємо число після x
        int val = 0;
        size_t i = xPos + 1;
        while (i < inv.size() && iswdigit(inv[i])) {
            val = val * 10 + (inv[i] - L'0');
            i++;
        }
        return val;
    };

    food_units = countInText(L"Тушонка");
    water_units = countInText(L"Вода");
}
void GameState::NextDay() {
    if (is_dead) return;

    current_day++;
    day_text.setString(L"Day: " + std::to_wstring(current_day));

    // Витрати за день
    food_units -= FOOD_PER_DAY;
    water_units -= WATER_PER_DAY;

    // Записи у щоденник
    diary_lines.push_back(L"День " + std::to_wstring(current_day) + L": Минув ще один день у підвалі...");

    if (food_units < 0) food_units = 0;
    if (water_units < 0) water_units = 0;

    if (food_units == 0) diary_lines.push_back(L"⚠ Немає їжі. Голод посилюється.");
    if (water_units == 0) diary_lines.push_back(L"⚠ Немає води. Спрага посилюється.");

    // Примітивна умова поразки (можеш змінити)
    if (food_units == 0 && water_units == 0) {
        is_dead = true;
        diary_lines.push_back(L"☠ Ти не витримав. Гру завершено.");
    }

    RebuildDiaryText();
}


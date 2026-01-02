#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>   
#include "Game.h"
#include "Stew.h"   
#include "Food.h"   
#include "Item.h"        


using namespace std;

int main() {
    setlocale(LC_ALL, "ukr");

    Game game;
    game.run();
    
    // RegistryFactory<Item> foodFactory;
    //foodFactory.Register<Food>("stew");

   //auto stew = foodFactory.Create("stew");
  
    
    return 0;
}




#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>  //string stream...what this does is that is allows to create long string with mixed input types...ints floats doubles etc. into a string
#include <vector>
// class that acts like a game engine
class Game {
 private:
  // private varuables
  // Window
  sf::RenderWindow* window;  // we want to delete the window later and hence we
                             // are alloacting the memory dynamiccally
  sf::Event ev;
  sf::VideoMode videoMode;
  // Mouse positions...for the window
  sf::Vector2i mousePosWindow;
  sf::Vector2f mousePosView;  // this is one you are gonna ude oftrn
  // game objects
  // to use textures we will use something called sf::Sprite but as we wont be
  // using it at the moment we will be using something else...Rectangle Shape

  std::vector<sf::RectangleShape> enemies;
  sf::RectangleShape enemy;

  // private functions
  void initialiseVariables();
  void initWindow();
  void initFonts();
  void initText();
  // resources
  sf::Font font;
  // text thing
  sf::Text uitext;
  // game logic
  unsigned points;
  float enemySpawnTimer;
  float enemySpawnMax;
  int health;  // dies if health goes below zero
  int maxEnemies;
  bool endGame;
  bool mouseHeld;

 public:
  Game();   // constructor
  ~Game();  // destruc tor
  // functions
  void update();
  void render();
  void updateText();
  // accessors
  const bool getEndGame() const;
  const bool running() const;
  void pollEvents();
  void initEnemies();
  void updateMousePositions();
  void spawnEnemy();
  void updateEnemies();
  void renderEnemies(sf::RenderTarget& target);
  void renderText(sf::RenderTarget& target);
};
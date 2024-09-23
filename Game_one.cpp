#include "Game_one.h"

#include <ctime>  //to initalise random numbers for the enemies
#include <iostream>
#include <vector>
using namespace std;
void Game::initialiseVariables() {
  this->window = nullptr;
  unsigned points;  // points will be above or equal to zero
  float enemySpawnTimer;
  float enemySpawnMax;
  int maxEnemies;
  this->points = 0;
  this->endGame = false;
  this->mouseHeld = false;  // to check if the mouse the held down...if it is
                            // the enemies wont be removed

  // if u want your enemy to spawn directly....u can have the enemy spaewn max
  // above the spawn timer and teh enemy spawn timer will be enemySpawnTimer=
  // this->enemySpawnTimerMax;
  // removes the enemies at the edge of the screen
  this->enemySpawnMax = 10.f;
  this->enemySpawnTimer = this->enemySpawnMax;
  this->maxEnemies = 5;
  this->health = 1;
  // move the enemies
}

void Game::initWindow() {
  this->videoMode.height = 600;
  this->videoMode.width = 800;
  // this->videoMode.getDesktopMode........this is a way to get the desktop's
  // current resolution
  this->window = new sf::RenderWindow(this->videoMode, "My first game",
                                      sf::Style::Titlebar | sf::Style::Close);
  this->window->setFramerateLimit(60);
}

Game::Game() {
  // constructor
  this->initialiseVariables();
  this->initWindow();
  this->initFonts();
  this->initText();
  this->initEnemies();
}

Game::~Game() {
  // destrctor
  delete this->window;
}

void Game::render() {
  this->window->clear(sf::Color(230, 230, 220));
  // draw game objects
  this->renderEnemies(*this->window);
  this->renderText(*this->window);
  this->window->display();
}

void Game::update() {
  this->pollEvents();
  // update mouse position relative to the screen
  if (this->endGame == false) {
    this->updateMousePositions();
    this->updateText();
    this->updateEnemies();
  }
  if (this->health <= 0) {
    this->endGame = true;  // endgame condition
  }
}
void Game::updateEnemies() {
  // updating the timer for enemy spawning when the total enemies is smaller
  // than the max
  // moves the enemies downwards
  if (this->enemies.size() < this->maxEnemies) {
    if (this->enemySpawnTimer >= this->enemySpawnMax) {
      // spawn the enemy and reset the timer
      this->spawnEnemy();
      this->enemySpawnTimer = 0.f;
    } else {
      this->enemySpawnTimer += 1.f;
    }
  }
  // this loop just gonna check  for the enemies going out of the screen
  for (int i = 0; i < this->enemies.size(); i++) {
    this->enemies[i].move(0.f, 1.f);  // it takes an x and y scale thing
    // once the enemy is remomved....check if it clicked upon...increases the
    // speed for the samae
    bool deleted = false;

    // if there enemy has passed the bottom of the screen we gonna delte that
    // too
    if (this->enemies[i].getPosition().y > this->window->getSize().y) {
      this->enemies.erase(
          this->enemies.begin() +
          i);  // used the erase functionality insetead of the deleted one
      this->health -= 1;
      cout << "health: " << this->health << "\n";
    }
  }
  // this is for the attacking.....the enemy yk
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    if (this->mouseHeld == false) {
      this->mouseHeld = true;
      bool deleted = false;
      for (int i = 0; i < this->enemies.size() && deleted == false; i++) {
        if (this->enemies[i].getGlobalBounds().contains(this->mousePosView)) {
          deleted = true;
          // gain points
          this->enemies.erase(this->enemies.begin() + i);
          this->points = this->points + 1.f;
        }
      }
      // if we dont do anything other than
      // sf::Mouse::isButtonPressed(sf::Mouse::Left.....thhe user can hold down
      // the mouse button
    }
  } else {
    this->mouseHeld = false;
  }
}

void Game::pollEvents() {
  while (this->window->pollEvent(this->ev)) {
    switch (this->ev.type) {
      case sf::Event::Closed:
        this->window->close();
        break;
      case sf::Event::KeyPressed:
        if (this->ev.key.code == sf::Keyboard::Escape) {
          this->window->close();
        }
        break;
      default:
        break;
    }
  }
}

const bool Game::running() const { return this->window->isOpen(); }

void Game::initEnemies() {
  this->enemy.setPosition(10.f, 10.f);
  this->enemy.setSize(sf::Vector2f(100.f, 100.f));
  this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
  this->enemy.setFillColor(sf::Color::Black);
  //   this->enemy.setOutlineColor(sf::Color::Red);
  this->enemy.setOutlineThickness(1.f);
}

void Game::updateMousePositions() {
  this->mousePosWindow = sf::Mouse::getPosition(
      *this->window);  // we are derefferncing the pointetr
  this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}
void Game::spawnEnemy() {
  // spawns enemies and sets their colors and positions
  // sets a random position, color and adds enemies to the vector
  this->enemy.setPosition(
      static_cast<float>(
          rand() % static_cast<int>(
                       this->window->getSize().x -
                       this->enemy.getSize().x)),  // randomiising it between 0
                                                   // and the window sizing
      0.0);
  this->enemy.setFillColor(sf::Color::Blue);
  this->enemies.push_back(this->enemy);
}

void Game::renderEnemies(sf::RenderTarget& target) {
  for (auto& e : this->enemies) {
    target.draw(e);
  }
}
bool const Game::getEndGame() const { return this->endGame; }
void Game::initFonts() {
  if (this->font.loadFromFile("dogica.ttf")) {
    cout << "Failed to load font! " << endl;
  }
}
void Game::initText() {
  this->uitext.setFont(this->font);
  this->uitext.setCharacterSize(12);
  this->uitext.setFillColor(sf::Color::Black);
  this->uitext.setString("NONE");
}

void Game::renderText(sf::RenderTarget& target) { target.draw(this->uitext); }
void Game::updateText() {
  std::stringstream ss;
  ss << "Points: " << this->points << "\n\n"
     << "Health: " << this->health;  // stream mixed of interger and strins
  this->uitext.setString(ss.str());
}
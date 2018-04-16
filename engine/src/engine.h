#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <ecm.h>
#include <maths.h>

#include <string>



class Engine {
public:
  Engine() = delete;
  static void Start(unsigned int width, unsigned int height,
                    const std::string& gameName, Scene* scn);
  static void ChangeScene(Scene*, std::string name);
  static sf::RenderWindow& GetWindow();
  static sf::Vector2u getWindowSize();
  static Scene* GetActiveScene();
  static void setVsync(bool b);
  static void pause(bool paused);

private:
  static Scene* _activeScene;
  static std::string _sceneName;
  static std::string _gameName;
  static void Update();
  static void Render(sf::RenderWindow& window);
};

namespace timing {
// Return time since Epoc
long long now();
// Return time since last() was last called.
long long last();
} // namespace timing
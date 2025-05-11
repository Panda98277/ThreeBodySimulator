#include <SFML/Graphics.hpp>

#include "ThreeBodySimulator.h"

int main() {
  auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}),
                                 "ThreeBodySimulator Project");
  window.setFramerateLimit(60);

  std::vector<Body> bodies;

  randombodies(bodies);

  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
    }

    // 更新物理模拟
    process(bodies);

    // 渲染新帧
    window.clear(sf::Color(30, 30, 30));  // 深灰色背景更好显示天体

    for (auto body : bodies) {
      window.draw(body.circle);
    }
    window.display();
  }
}

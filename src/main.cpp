#include "ThreeBodySimulator.h"
#include "pch.h"

/**
 * @brief 程序主入口，创建窗口并运行三体模拟循环
 *
 * 初始化窗口和天体系统，运行模拟主循环
 */
int main() {
  auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}),
                                 "ThreeBodySimulator Project");
  window.setFramerateLimit(60);

  std::vector<Body> bodies;

Loop:
  bodies = {};           // 重置天体集合
  randombodies(bodies);  // 生成随机初始条件的天体

  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
      Sleep(10);
      goto Loop;
    }

    // 更新物理模拟（计算引力相互作用并更新位置/速度）
    process(bodies);  // 参数 bodies 按引用传递，直接修改对象状态

    // 渲染新帧（双缓冲机制）
    window.clear(sf::Color(30, 30, 30));  // 使用深灰色背景提高天体可见度

    for (auto body : bodies) {
      window.draw(body.circle);
    }

    window.display();
  }
}

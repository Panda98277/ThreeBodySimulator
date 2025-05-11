#include "ThreeBodySimulator.h"

/// @brief 天体构造函数
/// @param m 质量（单位：千克）
/// @param p 初始位置（像素坐标）
/// @param v 初始速度（像素/秒）
/// @param a 初始加速度（像素/秒²）
/// @param c 显示颜色
Body::Body(double m,
           sf::Vector2f p,
           sf::Vector2f v,
           sf::Vector2f a,
           sf::Color c)
    : m(m), p(p), v(v), a(a), c(c) {
  circle = sf::CircleShape(m / 3e8);
  circle.setFillColor(c);

  update();
}

/// @brief 更新天体显示位置
/// @return 始终返回0表示成功
int Body::update() {
  circle.setPosition(p);
  return 0;
}

/// @brief 计算天体间引力相互作用
/// @param bodies 天体对象集合
/// @return 更新后的天体集合（含新计算的加速度）
std::vector<Body> calculateForces(std::vector<Body>& bodies) {
  // 重置加速度
  for (auto& body : bodies) {
    body.a.x = 0.0;
    body.a.y = 0.0;
  }

  // 计算每个天体之间的引力
  for (size_t i = 0; i < bodies.size(); ++i) {
    for (size_t j = i + 1; j < bodies.size(); ++j) {
      double dx = bodies[j].p.x - bodies[i].p.x;
      double dy = bodies[j].p.y - bodies[i].p.y;
      double r = std::sqrt(dx * dx + dy * dy);

      if (r == 0)
        continue;  // 避免除以零

      double F = G * bodies[i].m * bodies[j].m / (r * r);
      double Fx = F * dx / r;
      double Fy = F * dy / r;

      // 应用牛顿第三定律
      bodies[i].a.x += Fx * 5e2 / bodies[i].m;
      bodies[i].a.y += Fy * 5e2 / bodies[i].m;
    }
  }
  return bodies;
}

/// @brief 更新所有天体的运动状态
/// @param bodies 天体对象集合
/// @return 始终返回0表示成功
int updateBodies(std::vector<Body>& bodies) {
  for (auto& body : bodies) {
    // 更新速度
    body.v.x += body.a.x * time_step;
    body.v.y += body.a.y * time_step;

    // 更新位置
    body.p.x += body.v.x * time_step;
    body.p.y += body.v.y * time_step;

    body.update();
  }
  return 0;
}

/// @brief 主处理流程（单帧更新）
/// @param bodies 天体对象集合
/// @return 始终返回0表示成功
int process(std::vector<Body>& bodies) {
  // 位置更新
  calculateForces(bodies);
  updateBodies(bodies);

  // 输出位置信息
  for (size_t i = 0; i < bodies.size(); ++i) {
    std::cout << "Body " << i + 1 << ": (" << bodies[i].p.x << ", "
              << bodies[i].p.y << ")\n";
  }
  std::cout << "-------------------\n";

  return 0;
}

/// @brief 生成随机初始条件的天体
/// @param bodies 用于存储生成天体的容器
/// @return 始终返回0表示成功
int randombodies(std::vector<Body>& bodies) {
  // 初始化随机数生成器
  std::random_device rd;
  std::mt19937 gen(rd());

  // 天体参数范围设置
  std::uniform_real_distribution<double> mass_dist(1e10, 3e10);  // 优化质量范围
  std::uniform_real_distribution<double> pos_x_dist(600,
                                                    1320);      // 更集中的X位置
  std::uniform_real_distribution<double> pos_y_dist(400, 680);  // 更集中的Y位置
  std::uniform_real_distribution<double> vel_dist(-1, 1);   // 更合理的初速度
  std::uniform_int_distribution<int> color_dist(100, 255);  // 更好的颜色亮度

  // 生成三个随机天体
  for (int i = 0; i < 3; ++i) {
    // 随机生成初始参数
    double mass = mass_dist(gen);
    sf::Vector2f position(pos_x_dist(gen), pos_y_dist(gen));
    sf::Vector2f velocity(vel_dist(gen), vel_dist(gen));
    // sf::Vector2f velocity(1, 1);

    sf::Vector2f acceleration(0, 0);
    sf::Color color(color_dist(gen), color_dist(gen), color_dist(gen));

    bodies.emplace_back(mass, position, velocity, acceleration, color);
  }

  return 0;
}

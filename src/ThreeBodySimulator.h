#pragma once

#include "pch.h"

const double G = 6.67430e-11;  // 引力常数 (m^3 kg^-1 s^-2)
const double time_step = 0.1;  // 时间步长 (秒)

/**
 * @brief 表示三体系统中的天体对象
 *
 * 包含天体的物理属性和图形属性，提供更新位置的方法
 */

class Body {
 public:
  double m;                // 质量（千克）
  sf::Vector2f p;          // 位置（米）
  sf::Vector2f v;          // 速度（米/秒）
  sf::Vector2f a;          // 加速度（米/秒²）
  sf::Color c;             // 图形颜色
  sf::CircleShape circle;  // SFML图形对象

  Body(double m, sf::Vector2f p, sf::Vector2f v, sf::Vector2f a, sf::Color c);
  int update();
};

/// @brief 计算并更新所有天体的加速度和位置
/// @param bodies 天体对象的引用向量
/// @return 成功返回0，错误返回非零值
int process(std::vector<Body>& bodies);

/// @brief 生成随机初始条件的天体集合
/// @param bodies 用于存储生成天体的空向量
/// @return 成功返回0，错误返回非零值
int randombodies(std::vector<Body>& bodies);

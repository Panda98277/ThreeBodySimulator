#pragma once

#include <SFML/Graphics.hpp>

#include <cmath>
#include <iostream>
#include <random>
#include <vector>

const double G = 6.67430e-11;  // 引力常数 (m^3 kg^-1 s^-2)
const double time_step = 0.1;  // 时间步长 (秒)

class Body {
 public:
  double m;  // 质量
  sf::Vector2f p;
  sf::Vector2f v;
  sf::Vector2f a;
  sf::Color c;
  sf::CircleShape circle;

  Body(double m, sf::Vector2f p, sf::Vector2f v, sf::Vector2f a, sf::Color c);
  int update();
};

int process(std::vector<Body>& bodies);
int randombodies(std::vector<Body>& bodies);

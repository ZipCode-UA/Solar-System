#include "UI.h"

#include <string>
#include <vector>

#include <raylib.h>

#include "CelestialBody.h"

void DrawUI(Font& font, std::vector<CelestialBody>& SolarSystem, int days, int timeScale)
{
  // Time information
  drawTime(font, days, timeScale);

  // Planetary facts
  static int index = GetRandomValue(0, SolarSystem.size() - 1);
  if (days != 0 && days % 100 == 0) // Print a new fact every 100 days
    index = GetRandomValue(0, SolarSystem.size() - 1);
  drawFacts(font, SolarSystem, index);
}

void drawTime(Font& font, int days, int timeScale)
{
  std::vector<std::string> UI;

  std::string daysElapsed = "Days: ";
  daysElapsed += std::to_string(days);
  UI.push_back(daysElapsed);

  std::string yearsElapsed = "Years: ";
  yearsElapsed += std::to_string(days / 365);
  UI.push_back(yearsElapsed);

  std::string speed = "Time: ";
  speed += std::to_string(timeScale);
  speed += "x";
  UI.push_back(speed);

  // UI modifiers
  int UIfontSize = 38;
  int UIspacingSize = 2;
  float UIgap = 40;

  // UI location vectors
  Vector2 UIstart = { 10, 40 };
  Vector2 UIcurrent = UIstart;

  // Draw UI members
  for (const auto iter : UI)
  {
    DrawTextEx(font, iter.c_str(), UIcurrent, UIfontSize, UIspacingSize, WHITE);
    UIcurrent.y += UIgap;
  }
}

void drawFacts(Font& font, std::vector<CelestialBody>& SolarSystem, int index)
{
  std::vector<std::string> UI;

  std::string body = SolarSystem[index].getName();
  body += " Facts:";
  UI.push_back(body);

  std::string mass = "Mass: ";
  mass += std::to_string(static_cast<double>(SolarSystem[index].getMass()));
  mass += "kg";
  UI.push_back(mass);

  std::string radius = "Radius ";
  radius += std::to_string(static_cast<double>(SolarSystem[index].getRadius()));
  radius += "km";
  UI.push_back(radius);

  std::string volume = "Volume: ";
  volume += std::to_string(static_cast<double>(SolarSystem[index].getVolume()));
  volume += "km^3";
  UI.push_back(volume);

  std::string gravity = "Gravity: ";
  gravity += std::to_string(static_cast<int>(SolarSystem[index].getGravity()));
  gravity += "m/s^2";
  UI.push_back(gravity);

  std::string orbit = "Orbit Length: ";
  orbit += std::to_string(static_cast<int>(SolarSystem[index].getOrbit()));
  orbit += " days";
  UI.push_back(orbit);

  std::string day = "Day Length: ";
  day += std::to_string(static_cast<int>(SolarSystem[index].getAxisRotation()));
  day += " hours";
  UI.push_back(day);

  std::string satellites = "Number of Moons: ";
  satellites += std::to_string(static_cast<int>(SolarSystem[index].getSatellites()));
  UI.push_back(satellites);

  // UI modifiers
  int UIfontSize = 30;
  int UIspacingSize = 2;
  float UIgap = 40;

  // UI location vectors
  Vector2 UIstart = { 10, static_cast<float>(GetScreenHeight() - 400) };
  Vector2 UIcurrent = UIstart;

  // Draw heading
  DrawTextEx(font, body.c_str(), UIstart, 60, UIspacingSize, WHITE);
  UIcurrent.y += UIgap * 2;

  // Draw UI members
  for (const auto iter : UI)
  {
    DrawTextEx(font, iter.c_str(), UIcurrent, UIfontSize, UIspacingSize, WHITE);
    UIcurrent.y += UIgap;
  }
}

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
  std::string daysElapsed = "Days: ";
  daysElapsed += std::to_string(days);

  std::string yearsElapsed = "Years: ";
  yearsElapsed += std::to_string(days / 365);

  std::string speed = "Time: ";
  speed += std::to_string(timeScale);
  speed += "x";

  DrawTextEx(font, daysElapsed.c_str(), { 10, 10 }, 38, 2, WHITE);
  DrawTextEx(font, yearsElapsed.c_str(), { 10, 50 }, 38, 2, WHITE);
  DrawTextEx(font, speed.c_str(), { 10, 90 }, 38, 2, WHITE);
}

void drawFacts(Font& font, std::vector<CelestialBody>& SolarSystem, int index)
{
  std::string body = SolarSystem[index].getName();
  body += " Facts:";

  std::string mass = "Mass: ";
  mass += std::to_string(static_cast<double>(SolarSystem[index].getMass()));
  mass += "kg";

  std::string radius = "Radius ";
  radius += std::to_string(static_cast<double>(SolarSystem[index].getRadius()));
  radius += "km";

  std::string volume = "Volume: ";
  volume += std::to_string(static_cast<double>(SolarSystem[index].getVolume()));
  volume += "km^3";

  std::string gravity = "Gravity: ";
  gravity += std::to_string(static_cast<int>(SolarSystem[index].getGravity()));
  gravity += "m/s^2";

  std::string orbit = "Orbit Length: ";
  orbit += std::to_string(static_cast<int>(SolarSystem[index].getOrbit()));
  orbit += " days";

  std::string day = "Day Length: ";
  day += std::to_string(static_cast<int>(SolarSystem[index].getAxisRotation()));
  day += " hours";

  std::string satellites = "Number of Moons: ";
  satellites += std::to_string(static_cast<int>(SolarSystem[index].getSatellites()));

  Vector2 UIstart = { 10, static_cast<float>(GetScreenHeight() - 325) };
  Vector2 UIprevious = UIstart;
  Vector2 UIcurrent;
  int UIfontSize = 30;
  int UIspacingSize = 2;
  float UIgap = UIfontSize + 10;
  DrawTextEx(font, body.c_str(), UIstart, 60, UIspacingSize, WHITE);
  UIcurrent = UIprevious;
  UIcurrent.y = UIprevious.y + (UIgap * 2);
  DrawTextEx(font, mass.c_str(), UIcurrent, UIfontSize, UIspacingSize, WHITE);
  UIprevious = UIcurrent;
  UIcurrent.y = UIprevious.y + UIgap;
  DrawTextEx(font, radius.c_str(), UIcurrent, UIfontSize, UIspacingSize, WHITE);
  UIprevious = UIcurrent;
  UIcurrent.y = UIprevious.y + UIgap;
  DrawTextEx(font, volume.c_str(), UIcurrent, UIfontSize, UIspacingSize, WHITE);
  UIprevious = UIcurrent;
  UIcurrent.y = UIprevious.y + UIgap;
  DrawTextEx(font, gravity.c_str(), UIcurrent, UIfontSize, UIspacingSize, WHITE);
  UIprevious = UIcurrent;
  UIcurrent.y = UIprevious.y + UIgap;
  DrawTextEx(font, orbit.c_str(), UIcurrent, UIfontSize, UIspacingSize, WHITE);
  UIprevious = UIcurrent;
  UIcurrent.y = UIprevious.y + UIgap;
  DrawTextEx(font, day.c_str(), UIcurrent, UIfontSize, UIspacingSize, WHITE);
  UIprevious = UIcurrent;
  UIcurrent.y = UIprevious.y + UIgap;
  DrawTextEx(font, satellites.c_str(), UIcurrent, UIfontSize, UIspacingSize, WHITE);
}

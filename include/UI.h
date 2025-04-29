#ifndef UI_H
#define UI_H

#include <string>
#include <vector>

#include <raylib.h>

#include "CelestialBody.h"

void DrawUI(Font& font, std::vector<CelestialBody>& SolarSystem, int days, int timeScale, bool displayInput);

void drawTime(Font& font, int days, int timeScale);
void drawFacts(Font& font, std::vector<CelestialBody>& SolarSystem, int index);
void drawInput(Font& font);

std::string fixedString(const std::string& input);
std::string scientificString(const std::string& input);

#endif // UI_HPP

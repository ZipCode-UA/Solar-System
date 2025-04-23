#ifndef UI_H
#define UI_H

#include <vector>

#include <raylib.h>

#include "CelestialBody.h"

void DrawUI(Font& font, std::vector<CelestialBody>& SolarSystem, int days, int timeScale);

void drawTime(Font& font, int days, int timeScale);
void drawFacts(Font& font, std::vector<CelestialBody>& SolarSystem, int index);

#endif // UI_HPP

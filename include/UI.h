#ifndef UI_H
#define UI_H

#include <vector>

#include <raylib.h>

#include "CelestialBody.h"

void DrawUI(Font& font, std::vector<CelestialBody>& SolarSystem, int days, int timeScale, bool displayInput);

void drawTime(Font& font, int days, int timeScale);
void drawFacts(Font& font, std::vector<CelestialBody>& SolarSystem, int index);
void drawInput(Font& font);

#endif // UI_HPP

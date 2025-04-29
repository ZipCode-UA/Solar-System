#ifndef INPUT_H
#define INPUT_H

#include <vector>

#include <raylib.h>

#include "CelestialBody.h"

void handleInput();
void handleMouseClick(Camera& camera, const std::vector<Model>& models, const std::vector<CelestialBody>& SolarSystem);

#endif // INPUT_H

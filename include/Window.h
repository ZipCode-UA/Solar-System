#ifndef WINDOW_H
#define WINDOW_H

#include "raylib.h"

class Window
{
public:
  Window();
  ~Window();

private:
  void InitCamera();
  void DrawSphereBasic(Color color);      // Draw sphere without any matrix transformation

public:
  bool Open();
  void Update();

private:
  Camera camera = { 0 };
};

#endif // WINDOW_H

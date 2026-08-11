#include "raylib.h"
#include <stddef.h>

int main(void) {
  InitWindow(0, 0, "fingering");

  int monitor = GetCurrentMonitor();
  SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    EndMode3D();
    EndDrawing();
  }
  CloseWindow();
  return 0;
}

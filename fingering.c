#include "raylib.h"
#include <stddef.h>

int main(void) {
  InitWindow(0, 0, "fingering");

  int monitor = GetCurrentMonitor();
  SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
  SetTargetFPS(60);

  Camera3D camera = {.position = (Vector3){0.0f, 6.0f, 9.0f},
                     .target = (Vector3){0.0f, 1.0f, 0.0f},
                     .up = (Vector3){0.0f, 1.0f, 0.0f},
                     .fovy = 45.0f,
                     .projection = CAMERA_PERSPECTIVE};

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(WHITE);

    BeginMode3D(camera);
    EndMode3D();

    EndDrawing();
  }
  CloseWindow();

  return 0;
}

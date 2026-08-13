#include "./extruded_text.h"
#include "raylib.h"
#include <stddef.h>

int main(void) {
  InitWindow(0, 0, "fingering");
  int monitor = GetCurrentMonitor();
  SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
  SetTargetFPS(60);
  Camera3D camera = {.position = (Vector3){10.0, 10.0, 14.0},
                     .target = (Vector3){0.0, 0.0, 0.0},
                     .up = (Vector3){0.0, 0.1, 0.0},
                     .fovy = 45.0,
                     .projection = CAMERA_PERSPECTIVE};

  Font font = LoadFontEx("./resources/Font/PressStart2P.ttf", 100, NULL, 0);
  ExtrudedText tx = InitExtrudedText(font, "fingering", 14.4);

  Vector3 pos = {0.0, 0.0, 0.0};

  int typeCount = 0;
  bool hasError = false;
  while (!WindowShouldClose()) {
    int key = GetCharPressed();
    while (key > 0) {
      if (!hasError && typeCount < tx.textLength) {
        if (key == tx.text[typeCount]) {
          typeCount++;
        } else {
          hasError = true;
        }
      }
      key = GetCharPressed();
    }
    if (IsKeyPressed(KEY_BACKSPACE)) {
      if (hasError) {
        hasError = false;
      } else if (typeCount > 0) {
        typeCount--;
      }
    }
    UpdatedExtrudedTextColor(&tx, hasError, typeCount);
    BeginDrawing();
    ClearBackground(RAYWHITE);
    BeginMode3D(camera);
    DrawExtrudedText3D(camera, tx, pos);
    EndMode3D();
    EndDrawing();
  }
  UnloadFont(font);
  UnloadExtrudedText(tx);
  CloseWindow();
  return 0;
}

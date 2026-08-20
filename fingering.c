#include "./extruded_text.h"
#include "./wordlist.h"
#include "raylib.h"
#include <stddef.h>
#include <string.h>

int main(void) {
  SetTraceLogLevel(LOG_WARNING);
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

  WordList wl = LoadWordList("./resources/WordList/english200.txt");
  char sentence[500] = {0};
  for (int i = 0; i < 10; i++) {
    strcat(sentence, GetRandomWords(&wl));
    strcat(sentence, " ");
  }
  ExtrudedText tx = InitExtrudedText(font, sentence, 44.4);

  Vector3 pos = {0.0, 0.0, 0.0};

  int typeCount = 0;
  bool hasError = false;

  double startTime = 0.0;
  bool started = false;
  float wpm = 0.0f;

  while (!WindowShouldClose()) {
    if (!started) {
      startTime = GetTime();
      started = !started;
    }
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
    if (started && typeCount > 0 && typeCount < tx.textLength) {
      double elapsedMin = (GetTime() - startTime) / 60.0;
      wpm = (typeCount / 5.0) / elapsedMin;
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
    // DrawGrid(120, 1.0);
    EndMode3D();
    DrawText(TextFormat("WPM: %.1f", wpm), 20, 0, 50, BLACK);
    EndDrawing();
  }
  UnloadFont(font);
  UnloadExtrudedText(tx);
  CloseWindow();
  return 0;
}

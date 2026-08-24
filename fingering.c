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
  int totalKeyStrokes = 0;
  int totalErrors = 0;

  double startTime = 0.0;
  double endTime = 0.0;
  bool started = false;
  bool finished = false;
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
          totalErrors += 1;
        }
      }
      key = GetCharPressed();
      totalKeyStrokes += 1;
    }

    if (!finished && typeCount == tx.textLength) {
      finished = true;
      endTime = GetTime();
      double elapsedMin = (endTime - startTime) / 60.0;
      wpm = (typeCount / 5.0) / elapsedMin;
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
    if (finished && IsKeyPressed(KEY_R)) {
      UnloadExtrudedText(tx);
      memset(sentence, 0, sizeof(sentence));
      for (int i = 0; i < 10; i++) {
        strcat(sentence, GetRandomWords(&wl));
        strcat(sentence, " ");
      }
      tx = InitExtrudedText(font, sentence, 44.4);

      typeCount = 0;
      hasError = false;
      totalKeyStrokes = 0;
      totalErrors = 0;
      startTime = 0.0;
      endTime = 0.0;
      started = false;
      finished = false;
      wpm = 0.0f;
    }
    UpdatedExtrudedTextColor(&tx, hasError, typeCount);
    BeginDrawing();
    ClearBackground(RAYWHITE);
    if (!finished) {
      BeginMode3D(camera);
      DrawExtrudedText3D(camera, tx, pos);
      // DrawGrid(120, 1.0);
      EndMode3D();
      DrawText(TextFormat("WPM: %.1f", wpm), 20, 0, 50, BLACK);
    } else {
      float accuracy =
          100.0 * (totalKeyStrokes - totalErrors) / totalKeyStrokes;
      DrawText(TextFormat("WPM: %.1f", wpm), 100, 100, 50, BLACK);
      DrawText(TextFormat("ACCURACY: %.1f", accuracy), 100, 140, 50, BLACK);
      DrawText(TextFormat("Press R to restart"), 100, 180, 50, BLACK);
    }
    EndDrawing();
  }
  UnloadFont(font);
  UnloadExtrudedText(tx);
  CloseWindow();
  return 0;
}

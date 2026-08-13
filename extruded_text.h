#ifndef EXTRUDED_TEXT_H
#define EXTRUDED_TEXT_H
#define MAX_TEXT_LENGTH 120

#include "raylib.h"

typedef struct ExtrudedText {
  RenderTexture2D buffer;
  Rectangle sourceRec;
  Vector2 billboardSize;
  int thicknessLayers;
  float stepZ;

  Font font;
  const char *text;
  int textLength;
  int fontSize;
  float fontSpacing;
  float extraSeperation;
  int texW;
  int texH;

  float totalWidth;
  float currentScrollX;
  float targetScrollX;
  float letterPositions[MAX_TEXT_LENGTH];

} ExtrudedText;

ExtrudedText InitExtrudedText(Font font, const char *text, float baseWidth);
void DrawExtrudedText3D(Camera3D camera, ExtrudedText exText, Vector3 position);
void UpdatedExtrudedTextColor(ExtrudedText *exT, bool hasError, int typeCount);
void UnloadExtrudedText(ExtrudedText exText);

#endif

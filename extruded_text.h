#ifndef EXTRUDED_TEXT_H
#define EXTRUDED_TEXT_H

#include "raylib.h"

typedef struct ExtrudedText {
  RenderTexture2D buffer;
  Rectangle sourceRec;
  Vector2 billboardSize;
  int thicknessLayers;
  float stepZ;
} ExtrudedText;

ExtrudedText InitExtrudedText(Font font, const char *text, float baseWidth);
void DrawExtrudedText3D(Camera3D camera, ExtrudedText exText, Vector3 position);
void UnloadExtrudedText(ExtrudedText exText);

#endif

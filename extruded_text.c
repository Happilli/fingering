#include "./extruded_text.h"

ExtrudedText InitExtrudedText(Font font, const char *text, float baseWidth) {
  ExtrudedText exText = {0};

  exText.texW = 2040;
  exText.texH = 200;

  exText.buffer = LoadRenderTexture(exText.texW, exText.texH);

  exText.sourceRec =
      (Rectangle){0.0f, 0.0f, (float)exText.texW, -(float)exText.texH};
  float aspect = (float)exText.texH / (float)exText.texW;

  exText.billboardSize = (Vector2){baseWidth, baseWidth * aspect};
  exText.thicknessLayers = 40;
  exText.stepZ = 0.015f;
  exText.targetScrollX = 0.0f;
  exText.currentScrollX = 0.0f;

  exText.font = font;
  exText.text = text;
  exText.textLength = TextLength(text);
  exText.fontSize = 120;
  exText.fontSpacing = 2.0;
  exText.extraSeperation = 12.3f;

  float currentx = 0.0;

  for (int i = 0; i < exText.textLength; i++) {
    exText.letterPositions[i] = currentx;
    char ch[2] = {text[i], '\0'};
    Vector2 size = MeasureTextEx(font, ch, exText.fontSize, exText.fontSpacing);

    currentx += size.x + exText.extraSeperation;
  }
  exText.totalWidth = currentx;
  UpdatedExtrudedTextColor(&exText, false, 0);
  return exText;
}

void UpdatedExtrudedTextColor(ExtrudedText *exT, bool hasError, int typeCount) {
  if (typeCount < exT->textLength) {
    exT->targetScrollX = exT->letterPositions[typeCount];
  } else {
    exT->targetScrollX = exT->totalWidth;
  }
  exT->currentScrollX += (exT->targetScrollX - exT->currentScrollX) * 0.14f;

  BeginTextureMode(exT->buffer);
  ClearBackground(BLANK);
  int centerAnchorX = exT->texW / 2;
  for (int i = 0; i < exT->textLength; i++) {
    char ch[2] = {exT->text[i], '\0'};
    Color color = WHITE;
    if (i < typeCount) {
      color = GREEN;
    } else if (hasError && i == typeCount) {
      color = RED;
    }

    float offsetDrawx =
        (float)centerAnchorX + exT->letterPositions[i] - exT->currentScrollX;
    Vector2 pos = {offsetDrawx, 69.9};
    DrawTextEx(exT->font, ch, pos, exT->fontSize, exT->fontSpacing, color);
  }
  EndTextureMode();
}

void DrawExtrudedText3D(Camera3D camera, ExtrudedText exText,
                        Vector3 position) {
  for (int i = exText.thicknessLayers; i >= 0; i--) {
    Vector3 layerPos = {position.x, position.y,
                        position.z - ((float)i * exText.stepZ)};
    Color layerColor = (i == 0) ? WHITE : BLACK;

    DrawBillboardRec(camera, exText.buffer.texture, exText.sourceRec, layerPos,
                     exText.billboardSize, layerColor);
  }
}

void UnloadExtrudedText(ExtrudedText exText) {
  UnloadRenderTexture(exText.buffer);
}

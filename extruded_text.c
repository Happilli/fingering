#include "./extruded_text.h"

ExtrudedText InitExtrudedText(Font font, const char *text, float baseWidth) {
  ExtrudedText exText = {0};

  Vector2 textSize = MeasureTextEx(font, text, 40.0f, 4.0f);
  int texW = (int)textSize.x + 40;
  int texH = (int)textSize.y + 40;

  exText.buffer = LoadRenderTexture(texW, texH);

  BeginTextureMode(exText.buffer);
  ClearBackground(BLANK);
  Vector2 textPos = {(texW - textSize.x) / 2.0f, (texH - textSize.y) / 2.0f};
  DrawTextEx(font, text, textPos, 40.0f, 4.0f, BLUE);
  EndTextureMode();

  exText.sourceRec = (Rectangle){0.0f, 0.0f, (float)texW, -(float)texH};
  float aspect = (float)texW / (float)texH;

  exText.billboardSize = (Vector2){baseWidth, baseWidth / aspect};
  exText.thicknessLayers = 40;
  exText.stepZ = 0.015f;

  exText.font = font;
  exText.text = text;
  exText.textLength = TextLength(text);
  exText.fontSize = 40;
  exText.fontSpacing = 2.0;
  exText.texW = texW;
  exText.texH = texH;

  return exText;
}

void UpdatedExtrudedTextColor(ExtrudedText *exT, bool hasError, int typeCount) {
  BeginTextureMode(exT->buffer);
  ClearBackground(BLANK);
  float startX =
      (exT->texW -
       MeasureTextEx(exT->font, exT->text, exT->fontSize, exT->fontSpacing).x) /
      2.0;
  float startY = (exT->texH - exT->fontSize) / 2.0;
  float currentx = 0.0;

  for (int i = 0; i < exT->textLength; i++) {
    char ch[2] = {exT->text[i], '\0'};
    Color color = WHITE;
    if (i < typeCount) {
      color = GREEN;
    } else if (hasError && i == typeCount) {
      color = RED;
    }

    Vector2 pos = {startX + currentx, startY};
    DrawTextEx(exT->font, ch, pos, exT->fontSize, exT->fontSpacing, color);
    Vector2 size =
        MeasureTextEx(exT->font, ch, exT->fontSize, exT->fontSpacing);

    currentx += size.x + exT->fontSpacing;
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

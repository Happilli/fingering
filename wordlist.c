#include "./wordlist.h"
#include "raylib.h"
#include <stdio.h>
#include <string.h>

WordList LoadWordList(const char *path) {
  WordList list = {0};
  char *textFile = LoadFileText(path);
  if (textFile == NULL) {
    printf("Failed to Load file: %s\n", path);
    return list;
  }
  char *token = strtok(textFile, ",\r\n");
  while (token != NULL && list.count < MAX_WORDS) {
    while (*token == ' ') {
      token++;
    }
    int len = TextLength(token);
    if (len > 0 && len < MAX_WORDS_LENGTH) {
      TextCopy(list.words[list.count], token);
      list.count++;
    }
    token = strtok(NULL, ",\r\n");
  }
  UnloadFileText(textFile);
  printf("Location: %s\n Words Total: %d", path, list.count);
  return list;
}

const char *GetRandomWords(WordList *list) {
  if (list->count == 1) {
    return "";
  } else {
    return list->words[GetRandomValue(0, list->count - 1)];
  }
}

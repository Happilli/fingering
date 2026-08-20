#ifndef WORDLIST_H
#define WORDLIST_H

#define MAX_WORDS 500
#define MAX_WORDS_LENGTH 20

typedef struct WordList {
  char words[MAX_WORDS][MAX_WORDS_LENGTH];
  int count;
} WordList;

WordList LoadWordList(const char *path);
const char *GetRandomWords(WordList *list);

#endif // !WORDLIST_H

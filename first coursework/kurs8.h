#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>

#define ALPHABET_SIZE 1114112 // Максимальное значение кода Unicode 13.0

wchar_t encryptChar(wchar_t ch, int key);
wchar_t decryptChar(wchar_t ch, int key);
void encryptString(wchar_t *str, int *key, int keyLength);
void decryptString(wchar_t *str, int *key, int keyLength);
int compareStrings(wchar_t *str1, wchar_t *str2);
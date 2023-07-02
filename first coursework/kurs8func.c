#include "kurs8.h"

// Функция для шифрования символа с использованием ключа
wchar_t encryptChar(wchar_t ch, int key)
{
    if (ch == L' ')
    {
        return ch;
    }
    else if ((ch >= 0x0410 && ch <= 0x044F) || (ch >= 0x0041 && ch <= 0x005A) || (ch >= 0x0061 && ch <= 0x007A))
    {
        return ch + key;
    }
    else
    {
        return (ch + key) % ALPHABET_SIZE;
    }
}

// Функция для дешифрования символа с использованием ключа
wchar_t decryptChar(wchar_t ch, int key)
{
    if (ch == L' ')
    {
        return ch;
    }
    else if ((ch >= 0x0410 && ch <= 0x044F) || (ch >= 0x0041 && ch <= 0x005A) || (ch >= 0x0061 && ch <= 0x007A))
    {
        return ch - key;
    }
    else
    {
        return (ch - key + ALPHABET_SIZE) % ALPHABET_SIZE;
    }
}

// Функция для шифрования строки с использованием ключа
void encryptString(wchar_t *str, int *key, int keyLength)
{
    int strLength = wcslen(str);
    int keyIndex = 0;
    for (int i = 0; i < strLength; i++)
    {
        if (str[i] != L' ')
        {
            str[i] = encryptChar(str[i], key[keyIndex % keyLength]);
            keyIndex++;
        }
    }
}

// Функция для дешифрования строки с использованием ключа
void decryptString(wchar_t *str, int *key, int keyLength)
{
    int strLength = wcslen(str);
    int keyIndex = 0;
    for (int i = 0; i < strLength; i++)
    {
        if (str[i] != L' ')
        {
            str[i] = decryptChar(str[i], key[keyIndex % keyLength]);
            keyIndex++;
        }
    }
}

// Функция для сравнения оригинального текста и дешифрованного текста
int compareStrings(wchar_t *str1, wchar_t *str2)
{
    // Сравниваем длины строк
    size_t len1 = wcslen(str1);
    size_t len2 = wcslen(str2);
    if (len1 != len2)
    {
        return 0;
    }

    // Сравниваем символы строк
    for (size_t i = 0; i < len1; i++)
    {
        if (str1[i] != str2[i])
        {
            return 0;
        }
    }

    return 1;
}
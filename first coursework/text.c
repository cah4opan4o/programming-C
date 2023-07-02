#include "kurs8.h"

int main(int argc, char **argv)
{
    setlocale(LC_ALL, "");
    int key[] = {2, 7, 1, 8};
/*
    // Ввод и вывод текста для файлов
    wchar_t text[1000];
    if (argc < 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    else
    {
        mbstowcs(text, argv[1], 1000);
    }
    int len = wcslen(text);
    text[len] = L' ';      // добавляем пробел в конец массива
    text[len + 1] = L'\0'; // добавляем нулевой символ в конец массива
*/
    wchar_t RuLine[1024]; // Буфер для считывания строки
    FILE *file1 = fopen("originalru.txt","r, ccs=UTF-8");
    FILE *file2 = fopen("encryptru.txt","w, ccs=UTF-8");
    while (fgetws(RuLine, 1024, file1) != NULL)
    {
        encryptString(RuLine, key, 4);
        fwprintf(file2, L"\n%ls",RuLine);
    }
    fclose(file1);
    fclose(file2);
    
 /*   FILE *file1 = fopen("originalru.txt", "a, ccs=UTF-8");
    if (!file1)
    {
        wprintf(L"Error opening file1\n");
        return 1;
    }

    fwprintf(file1, L"\n%ls", text);
    fclose(file1);

    encryptString(text, key, 4);
    wprintf(L"Encoded text: %ls\n", text);

    FILE *file2 = fopen("encryptru.txt", "a, ccs=UTF-8");
    if (!file2)
    {
        wprintf(L"Error opening file2\n");
        return 1;
    }

    fwprintf(file2, L"\n%ls", text);
    fclose(file2);

    decryptString(text, key, 4);
    wprintf(L"Decoded text: %ls\n", text);
*/
    return 0;
}

/*
// Статическая библиотека:
// Получаем объектные файлы .o:
gcc main.c func.c -c

// Создаем статическую библиотеку MY_PRINT, расширение .a из объектного файла с функциями
ar r libMY_PRINT.a func.o

// Линкуем (компонуем) библиотеку с объектным файлом main.o:
gcc main.o -L. -lMY_PRINT -o static_example
// -L - путь до библиотеки, -l - название

// Запускаем:
./static_example

// Динамическая библиотека:
// Объектный файл с главной функцией:
gcc -c main.c
// Объектный файл для создания дин. либы:
gcc -c -fPIC func.c

// Собираем дин. библиотеку:
gcc -shared -o libMY_PRINT.so func.o

// Линковка:
gcc -o dyn_example main.o -L. -lMY_PRINT -Wl,-rpath,.

// Запуск
./dyn_example
*/
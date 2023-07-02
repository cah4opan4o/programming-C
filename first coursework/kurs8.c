#include "kurs8.h"

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    setlocale(LC_ALL, "");

    int key[] = {2, 7, 1, 8};

    wchar_t *filename1;
    // Определяем размер буфера для хранения имени файла в формате wchar_t
    int len1 = mbstowcs(NULL, argv[1], 0) + 1;
    filename1 = (wchar_t *)malloc(len1 * sizeof(wchar_t));

    // Преобразуем строку argv[1] в формат wchar_t
    mbstowcs(filename1, argv[1], len1);

    wchar_t *filename2;
    // Определяем размер буфера для хранения имени файла в формате wchar_t
    int len2 = mbstowcs(NULL, argv[2], 0) + 1;
    filename2 = (wchar_t *)malloc(len2 * sizeof(wchar_t));

    // Преобразуем строку argv[1] в формат wchar_t
    mbstowcs(filename2, argv[2], len2);

    // Открываем файл для чтения
    FILE *RuFile = fopen(argv[1], "r, ccs=UTF-8");
    if (RuFile == NULL)
    {
        wprintf(L"Error: cannot open OriginalRU.txt\n");
        return 1;
    }

    // Создаем динамический массив для хранения строк из файла OriginalRU.txt
    wchar_t **RuStrings = NULL;
    int RuStringsCount = 0;

    wchar_t RuLine[1024]; // Буфер для считывания строки
    while (fgetws(RuLine, 1024, RuFile) != NULL)
    {
        RuLine[wcslen(RuLine) - 1] = L'\n';
        // Увеличиваем размер массива RuStrings на 1
        RuStringsCount++;
        RuStrings = (wchar_t **)realloc(RuStrings, RuStringsCount * sizeof(wchar_t *));

        // Создаем копию строки RuLine и добавляем ее в массив RuStrings
        RuStrings[RuStringsCount - 1] = wcsdup(RuLine);
    }

    // Освобождаем память, используемую для чтения строк
    fclose(RuFile);

    FILE *ENFile = fopen(argv[2], "r, ccs=UTF-8");
    if (ENFile == NULL)
    {
        wprintf(L"Error: cannot open OriginalRU.txt\n");
        return 1;
    }

    // Создаем динамический массив для хранения строк из файла EncryptRU.txt
    wchar_t **ENStrings = NULL;
    wchar_t **DEStrings = NULL;
    int ENStringsCount = 0;

    wchar_t ENLine[1024]; // Буфер для считывания строки
    while (fgetws(ENLine, 1024, ENFile) != NULL)
    {
        ENLine[wcslen(ENLine) - 1] = L'\n'; // добавляем элемент конца строки
        // Увеличиваем размер массива RuStrings на 1
        ENStringsCount++;
        DEStrings = (wchar_t **)realloc(DEStrings, ENStringsCount * sizeof(wchar_t *));
        ENStrings = (wchar_t **)realloc(ENStrings, ENStringsCount * sizeof(wchar_t *));

        //  Создаем копию строки ENLine и добавляем ее в массив ENStrings
        ENStrings[ENStringsCount - 1] = wcsdup(ENLine);

        // Создаем копию строки ENLine, но уже после дешифровки и добавляем ее в массив DEStrings
        wchar_t *DELine = wcsdup(ENLine);
        decryptString(DELine, key, 4);
        DELine[wcslen(DELine) - 1] = L'\n'; // добавляем элемент конца строки
        DEStrings[ENStringsCount - 1] = DELine;
    }

    // Освобождаем память, используемую для чтения строк
    fclose(ENFile);

    // Выводим содержимое массива RuStrings
    wprintf(L"\n=====ORIGINAL TEXT=====\n");
    for (int i = 0; i < RuStringsCount; i++)
    {
        wprintf(L"%ls", RuStrings[i]);
    }

    wprintf(L"\n=====ENCRYPT TEXT=====\n");
    // Выводим содержимое массива ENStrings
    for (int i = 0; i < ENStringsCount; i++)
    {
        // decryptString(ENStrings[i], key, 4);
        wprintf(L"%ls", ENStrings[i]);
    }

    wprintf(L"\n");

    wprintf(L"\n=====DECRYPT TEXT=====\n");
    // Выводим содержимое массива ENStrings
    for (int i = 0; i < ENStringsCount; i++)
    {
        // decryptString(ENStrings[i], key, 4);
        wprintf(L"%ls", DEStrings[i]);
    }

    wprintf(L"\n");

    int count = 0;
    for (int i = 0; i < RuStringsCount; i++)
    {
        if (compareStrings(RuStrings[i], DEStrings[i]))
        {
            count++;
        }
    }

    if (count == RuStringsCount)
    {
        wprintf(L"SUCCES!\n");
    }
    else
    {
        wprintf(L"FAIL!\n");
    }

    // Освобождаем память, используемую для хранения строк
    for (int i = 0; i < RuStringsCount; i++)
    {
        free(RuStrings[i]);
    }
    free(RuStrings);

    // Освобождаем память, используемую для хранения строк
    for (int i = 0; i < ENStringsCount; i++)
    {
        free(ENStrings[i]);
        free(DEStrings[i]);
    }
    free(ENStrings);
    free(DEStrings);

    free(filename1);
    free(filename2);
}
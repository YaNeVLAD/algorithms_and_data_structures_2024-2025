//Задание: Задан текстовый файл. Переносов слов нет. Создать файл, в котором каждое слово будет записано в обратном порядке
//Автор: Ковалев Владислав ПС-21
//Среда выполнения: Visual Studio 2022

#include <Windows.h>
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

void reverseWord(char* word);

int main(int argc, char* argv[])
{
    char ch = 0;
    int i = 0;
    char word[255]{};

    std::ifstream inFile;
    std::ofstream outFile;

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    if (argc <= 2)
    {
        cout << "Передано недостаточное количество параметров." << endl;
        cout << "После названия программы через пробел должен быть указан путь входного файла" << endl;
        cout << "После него через пробел должен быть указан путь выходного файла" << endl;
        return EXIT_FAILURE;
    }

    inFile.open(argv[1]);
    if (inFile.is_open() == false)
    {
        cout << "Входной файл не существует или находится в другом месте." << endl;
        return EXIT_FAILURE;
    }

    outFile.open(argv[2]);
    if (outFile.is_open() == false)
    {
        cout << "Возникли проблемы с созданием выходного файла" << endl;
        return EXIT_FAILURE;
    }

    while (inFile.get(ch))
    {
        if (ch == ' ' || ch == '\n')
        {
            if (i > 0)
            {
                word[i] = '\0';
                reverseWord(word);
                outFile << word;
                i = 0;
            }
            outFile << ch;
        }
        else
        {
            if (i < 255)
            {
                word[i++] = ch;
            }
        }
    }

    if (i > 0) {
        word[i] = '\0';
        reverseWord(word);
        outFile << word;
    }

    inFile.close();
    outFile.close();

    system(("start " + std::string(argv[2])).c_str());

    cout << "Программа успешно завершила работу" << endl;
    return EXIT_SUCCESS;
}

void reverseWord(char* word)
{
    int len = strlen(word);
    for (int i = 0; i < len / 2; ++i) {
        char temp = word[i];
        word[i] = word[len - i - 1];
        word[len - i - 1] = temp;
    }
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

#include <iostream>
#include <string>
#include <locale>
#include <sstream>
#include <vector>
#include <codecvt>

#include "List.h"
#include "LinkedList.h"
#include "HashSet.h"
#include "Dict.h"

using namespace std;


void parseLine(const string& line, string& lastName, string& firstName, int& task1, int& task2, int& task3) {
    stringstream ss(line);
    ss >> lastName >> firstName >> task1 >> task2 >> task3;
}

int main() {
    setlocale(LC_ALL, "Russian");
    cout << "Задание 1" << endl;
    // Создание списка L
    List<int> L;
    L.add(1);
    L.add(2);
    L.add(3);
    L.add(4);
    L.add(5);
    cout << "Список L: ";
    L.print();

    // Создание подсписка L1
    List<int> L1;
    L1.add(2);
    L1.add(3);
    cout << "Список L1 (подсписок): ";
    L1.print();

    // Создание подсписка L2
    List<int> L2;
    L2.add(8);
    L2.add(9);
    cout << "Список L2 (замена): ";
    L2.print();

    // Замена первого вхождения L1 в L на L2
    L.replaceSublist(L1, L2);

    // Вывод изменённого списка L
    cout << "Изменённый список L: ";
    L.print();
    cout << endl;

    cout << "Задание 2" << endl;
    LinkedList<int> list;

    // Добавление элементов в список
    list.add(3);
    list.add(1);
    list.add(4);
    list.add(2);

    // Печать элементов списка
    cout << "Исходный список: ";
    list.print();

    // Сортировка списка по возрастанию
    list.sort();
    cout << "Отсортированный список: ";
    list.print();

    // Удаление первого элемента списка
    // Используем публичный метод getHead() для получения первого узла
    auto firstNode = list.getHead();
    if (firstNode) {
        list.remove(firstNode);
    }
    cout << "После удаления первого элемента: ";
    list.print();

    // Добавление новых элементов в список
    list.add(5);
    list.add(0);
    cout << "После добавления новых элементов: ";
    list.print();

    // Очистка списка
    list.clear();
    cout << "После очистки списка: ";
    list.print();  // Ожидается пустой список
    cout << endl;

    cout << "Задание 3" << endl;
    HashSet<wstring> allGames;
    allGames.add(L"D&D");
    allGames.add(L"Pathfinder");
    allGames.add(L"Starfinder");
    allGames.add(L"Cyberpunk2022");
    allGames.add(L"Entropy");

    vector<HashSet<wstring>> studentsGames(3);

    // Игры студентов
    studentsGames[0].add(L"D&D");
    studentsGames[0].add(L"Pathfinder");

    studentsGames[1].add(L"D&D");
    studentsGames[1].add(L"Starfinder");

    studentsGames[2].add(L"D&D");
    studentsGames[2].add(L"Cyberpunk2022");

    // Общие игры
    HashSet<wstring> commonGames = HashSet<wstring>::getCommonGames(studentsGames);
    wcout << L"Игры, в которые играют все студенты:" << endl;
    commonGames.print();

    // Частично играемые игры
    HashSet<wstring> someGames = HashSet<wstring>::getSomeGames(studentsGames);
    wcout << L"Игры, в которые играют некоторые студенты:" << endl;
    someGames.print();

    // Игры, в которые никто не играет
    HashSet<wstring> noGames = HashSet<wstring>::getNoGames(studentsGames, allGames);
    wcout << L"Игры, в которые никто не играет:" << endl;
    noGames.print();
    cout << endl;


    cout << "Задание 4" << endl;

    // Открытие файла
    wifstream inputFile("C:\\Users\\mypcs\\C++ Projects\\Test\\Projectlab6\\text.txt");
    inputFile.imbue(locale("ru_RU.UTF-8")); // Установка русской кодировки

    if (!inputFile) {
        wcerr << L"Не удалось открыть файл text.txt" << endl;
        return 1;
    }

    wstring line;
    while (getline(inputFile, line)) {
        wcout << L"Прочитанная строка: " << line << endl;
    }

    // Сброс указателя на начало файла для последующего чтения слов
    inputFile.clear();
    inputFile.seekg(0, ios::beg);

    HashSet<wchar_t> allLetters;    // Все буквы (глухие согласные тоже)
    HashSet<wchar_t> usedLetters;   // Использованные буквы (только те, что встретились в словах)

    wstring word;
    while (inputFile >> word) {
        for (wchar_t letter : word) {
            if (iswalpha(letter)) {
                allLetters.add(towlower(letter));   // Все буквы
                usedLetters.add(towlower(letter));  // Использованные буквы
            }
        }
    }

    inputFile.close();

    // Вывод глухих согласных, которые не встречаются хотя бы в одном слове
    usedLetters.printMissingDeafConsonants(allLetters);
    setlocale(LC_ALL, "Russian_Russia.1251");  // Для кодировки Windows-1251

    cout << endl;

    cout << "Задание 5" << endl;
    

    // Вводим количество участников
    int N;
    wcout << L"Введите количество участников: ";
    cin >> N;
    cin.ignore();  // Чтобы игнорировать символ новой строки после ввода числа

    // Создаем объект для хранения участников
    Dict<wstring> participants;

    // Вводим данные участников
    wcout << L"Введите данные участников (Фамилия Имя Баллы):\n";
    for (int i = 0; i < N; ++i) {
        wstring line;
        getline(wcin, line);  // Считываем строку, содержащую фамилию, имя и баллы

        // Разбиваем строку на отдельные элементы
        wstringstream ss(line);
        wstring lastName, firstName;
        int task1, task2, task3;

        ss >> lastName >> firstName >> task1 >> task2 >> task3;  // Разбиваем на компоненты

        // Формируем ключ (фамилия + имя)
        wstring key = lastName + L" " + firstName;

        // Добавляем участника в словарь
        participants.add(key, Dict<wstring>::Scores(task1, task2, task3));
    }

    // Находим участников с максимальными баллами
    vector<wstring> maxScoreParticipants = participants.getMaxScoreParticipants();

    // Выводим участников с максимальными баллами
    wcout << L"Участники с максимальными баллами:\n";
    for (const wstring& participant : maxScoreParticipants) {
        wcout << participant << endl;
    }

    return 0;
}

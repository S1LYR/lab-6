#ifndef HASHSET_H
#define HASHSET_H

#include <set>
#include <vector>
#include <string>
#include <locale>
#include <iostream>
#include <fstream>

using namespace std;

template <typename T>
class HashSet {
private:
    set<T> elements;

public:
    // Добавление элемента
    void add(const T& element) {
        elements.insert(element);
    }

    // Удаление элемента
    void remove(const T& element) {
        elements.erase(element);
    }

    // Проверка наличия элемента
    bool contains(const T& element) const {
        return elements.find(element) != elements.end();
    }

    // Объединение множеств
    void unionSets(const HashSet<T>& other) {
        elements.insert(other.elements.begin(), other.elements.end());
    }

    // Разность множеств
    void exceptSets(const HashSet<T>& other) {
        for (const T& elem : other.elements) {
            elements.erase(elem);
        }
    }

    // Пересечение множеств
    void intersectSets(const HashSet<T>& other) {
        set<T> result;
        for (const T& elem : elements) {
            if (other.contains(elem)) {
                result.insert(elem);
            }
        }
        elements = result;
    }

    // Получение всех элементов множества
    const set<T>& getElements() const {
        return elements;
    }

    // Вывод элементов множества
    void print() const {
        for (const T& element : elements) {
            wcout << element << L" ";
        }
        wcout << endl;
    }

    void printMissingDeafConsonants(const HashSet<wchar_t>& allLetters) const {
        static const wstring deafConsonants = L"кптфхсшцч"; // Список глухих согласных.
        HashSet<wchar_t> missingLetters;

        // Проходим по каждому символу в строке глухих согласных
        for (wchar_t letter : deafConsonants) {
            // Приводим букву к нижнему регистру
            wchar_t lowerLetter = towlower(letter);

            // Проверяем, содержится ли данная глухая согласная в allLetters
            if (!allLetters.contains(lowerLetter)) {
                missingLetters.add(lowerLetter); // Добавляем отсутствующую букву
            }
        }

        // Выводим отсутствующие глухие согласные
        if (missingLetters.getElements().empty()) {
            wcout << L"Все глухие согласные присутствуют в тексте." << endl;
        }
        else {
            wcout << L"Глухие согласные, отсутствующие хотя бы в одном слове: ";
            for (const wchar_t& letter : missingLetters.getElements()) {
                wcout << letter << L" ";
            }
            wcout << endl;
        }
    }




    // --- Методы для работы с играми ---
    static HashSet<T> getCommonGames(const vector<HashSet<T>>& studentsGames) {
        if (studentsGames.empty()) return HashSet<T>();

        HashSet<T> result = studentsGames[0];
        for (const auto& games : studentsGames) {
            result.intersectSets(games);
        }
        return result;
    }

    static HashSet<T> getSomeGames(const vector<HashSet<T>>& studentsGames) {
        HashSet<T> result;
        for (const auto& games : studentsGames) {
            result.unionSets(games);
        }
        return result;
    }

    static HashSet<T> getNoGames(const vector<HashSet<T>>& studentsGames, const HashSet<T>& allGames) {
        HashSet<T> playedGames = getSomeGames(studentsGames);
        HashSet<T> result = allGames;
        result.exceptSets(playedGames);
        return result;
    }
};

#endif // HASHSET_H

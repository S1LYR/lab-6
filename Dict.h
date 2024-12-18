#include <string>
#include <vector>
#include <locale>
#include <codecvt>
#include <algorithm>
#include <iostream>

using namespace std;  // Добавлено, чтобы использовать стандартные типы без префикса std::

template <typename KeyType>
class Dict {
public:
    // Структура для хранения баллов
    struct Scores {
        int task1, task2, task3;

        Scores(int t1, int t2, int t3) : task1(t1), task2(t2), task3(t3) {}

        int totalScore() const {
            return task1 + task2 + task3;
        }
    };

private:
    // Словарь, который хранит ключи и их баллы
    vector<pair<KeyType, Scores>> data;

public:
    // Функция добавления данных в словарь
    void add(const KeyType& key, const Scores& score) {
        data.push_back(make_pair(key, score));
    }

    // Функция для поиска участников с максимальными баллами
    vector<KeyType> getMaxScoreParticipants() {
        int maxScore = -1;
        vector<KeyType> maxScoreParticipants;

        // Находим максимальный балл
        for (const auto& entry : data) {
            int score = entry.second.totalScore();
            if (score > maxScore) {
                maxScore = score;
            }
        }

        // Собираем участников с максимальным баллом
        for (const auto& entry : data) {
            int score = entry.second.totalScore();
            if (score == maxScore) {
                maxScoreParticipants.push_back(entry.first);
            }
        }

        // Перекодируем строки из wstring в utf8 перед выводом
        vector<KeyType> result;
        for (const auto& participant : maxScoreParticipants) {
            result.push_back(participant);  // Здесь возвращаем уже правильный формат
        }

        return result;
    }

private:
    // Функция для преобразования из wstring в string (UTF-8)
    string utf8Encode(const wstring& input) const {
        wstring_convert<codecvt_utf8<wchar_t>> converter;
        return converter.to_bytes(input);  // Преобразуем в строку UTF-8
    }
};

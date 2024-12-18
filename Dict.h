#include <string>
#include <vector>
#include <locale>
#include <codecvt>
#include <algorithm>
#include <iostream>

using namespace std;  // ���������, ����� ������������ ����������� ���� ��� �������� std::

template <typename KeyType>
class Dict {
public:
    // ��������� ��� �������� ������
    struct Scores {
        int task1, task2, task3;

        Scores(int t1, int t2, int t3) : task1(t1), task2(t2), task3(t3) {}

        int totalScore() const {
            return task1 + task2 + task3;
        }
    };

private:
    // �������, ������� ������ ����� � �� �����
    vector<pair<KeyType, Scores>> data;

public:
    // ������� ���������� ������ � �������
    void add(const KeyType& key, const Scores& score) {
        data.push_back(make_pair(key, score));
    }

    // ������� ��� ������ ���������� � ������������� �������
    vector<KeyType> getMaxScoreParticipants() {
        int maxScore = -1;
        vector<KeyType> maxScoreParticipants;

        // ������� ������������ ����
        for (const auto& entry : data) {
            int score = entry.second.totalScore();
            if (score > maxScore) {
                maxScore = score;
            }
        }

        // �������� ���������� � ������������ ������
        for (const auto& entry : data) {
            int score = entry.second.totalScore();
            if (score == maxScore) {
                maxScoreParticipants.push_back(entry.first);
            }
        }

        // ������������ ������ �� wstring � utf8 ����� �������
        vector<KeyType> result;
        for (const auto& participant : maxScoreParticipants) {
            result.push_back(participant);  // ����� ���������� ��� ���������� ������
        }

        return result;
    }

private:
    // ������� ��� �������������� �� wstring � string (UTF-8)
    string utf8Encode(const wstring& input) const {
        wstring_convert<codecvt_utf8<wchar_t>> converter;
        return converter.to_bytes(input);  // ����������� � ������ UTF-8
    }
};

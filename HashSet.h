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
    // ���������� ��������
    void add(const T& element) {
        elements.insert(element);
    }

    // �������� ��������
    void remove(const T& element) {
        elements.erase(element);
    }

    // �������� ������� ��������
    bool contains(const T& element) const {
        return elements.find(element) != elements.end();
    }

    // ����������� ��������
    void unionSets(const HashSet<T>& other) {
        elements.insert(other.elements.begin(), other.elements.end());
    }

    // �������� ��������
    void exceptSets(const HashSet<T>& other) {
        for (const T& elem : other.elements) {
            elements.erase(elem);
        }
    }

    // ����������� ��������
    void intersectSets(const HashSet<T>& other) {
        set<T> result;
        for (const T& elem : elements) {
            if (other.contains(elem)) {
                result.insert(elem);
            }
        }
        elements = result;
    }

    // ��������� ���� ��������� ���������
    const set<T>& getElements() const {
        return elements;
    }

    // ����� ��������� ���������
    void print() const {
        for (const T& element : elements) {
            wcout << element << L" ";
        }
        wcout << endl;
    }

    void printMissingDeafConsonants(const HashSet<wchar_t>& allLetters) const {
        static const wstring deafConsonants = L"���������"; // ������ ������ ���������.
        HashSet<wchar_t> missingLetters;

        // �������� �� ������� ������� � ������ ������ ���������
        for (wchar_t letter : deafConsonants) {
            // �������� ����� � ������� ��������
            wchar_t lowerLetter = towlower(letter);

            // ���������, ���������� �� ������ ������ ��������� � allLetters
            if (!allLetters.contains(lowerLetter)) {
                missingLetters.add(lowerLetter); // ��������� ������������� �����
            }
        }

        // ������� ������������� ������ ���������
        if (missingLetters.getElements().empty()) {
            wcout << L"��� ������ ��������� ������������ � ������." << endl;
        }
        else {
            wcout << L"������ ���������, ������������� ���� �� � ����� �����: ";
            for (const wchar_t& letter : missingLetters.getElements()) {
                wcout << letter << L" ";
            }
            wcout << endl;
        }
    }




    // --- ������ ��� ������ � ������ ---
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

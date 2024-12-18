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
    cout << "������� 1" << endl;
    // �������� ������ L
    List<int> L;
    L.add(1);
    L.add(2);
    L.add(3);
    L.add(4);
    L.add(5);
    cout << "������ L: ";
    L.print();

    // �������� ��������� L1
    List<int> L1;
    L1.add(2);
    L1.add(3);
    cout << "������ L1 (���������): ";
    L1.print();

    // �������� ��������� L2
    List<int> L2;
    L2.add(8);
    L2.add(9);
    cout << "������ L2 (������): ";
    L2.print();

    // ������ ������� ��������� L1 � L �� L2
    L.replaceSublist(L1, L2);

    // ����� ���������� ������ L
    cout << "��������� ������ L: ";
    L.print();
    cout << endl;

    cout << "������� 2" << endl;
    LinkedList<int> list;

    // ���������� ��������� � ������
    list.add(3);
    list.add(1);
    list.add(4);
    list.add(2);

    // ������ ��������� ������
    cout << "�������� ������: ";
    list.print();

    // ���������� ������ �� �����������
    list.sort();
    cout << "��������������� ������: ";
    list.print();

    // �������� ������� �������� ������
    // ���������� ��������� ����� getHead() ��� ��������� ������� ����
    auto firstNode = list.getHead();
    if (firstNode) {
        list.remove(firstNode);
    }
    cout << "����� �������� ������� ��������: ";
    list.print();

    // ���������� ����� ��������� � ������
    list.add(5);
    list.add(0);
    cout << "����� ���������� ����� ���������: ";
    list.print();

    // ������� ������
    list.clear();
    cout << "����� ������� ������: ";
    list.print();  // ��������� ������ ������
    cout << endl;

    cout << "������� 3" << endl;
    HashSet<wstring> allGames;
    allGames.add(L"D&D");
    allGames.add(L"Pathfinder");
    allGames.add(L"Starfinder");
    allGames.add(L"Cyberpunk2022");
    allGames.add(L"Entropy");

    vector<HashSet<wstring>> studentsGames(3);

    // ���� ���������
    studentsGames[0].add(L"D&D");
    studentsGames[0].add(L"Pathfinder");

    studentsGames[1].add(L"D&D");
    studentsGames[1].add(L"Starfinder");

    studentsGames[2].add(L"D&D");
    studentsGames[2].add(L"Cyberpunk2022");

    // ����� ����
    HashSet<wstring> commonGames = HashSet<wstring>::getCommonGames(studentsGames);
    wcout << L"����, � ������� ������ ��� ��������:" << endl;
    commonGames.print();

    // �������� �������� ����
    HashSet<wstring> someGames = HashSet<wstring>::getSomeGames(studentsGames);
    wcout << L"����, � ������� ������ ��������� ��������:" << endl;
    someGames.print();

    // ����, � ������� ����� �� ������
    HashSet<wstring> noGames = HashSet<wstring>::getNoGames(studentsGames, allGames);
    wcout << L"����, � ������� ����� �� ������:" << endl;
    noGames.print();
    cout << endl;


    cout << "������� 4" << endl;

    // �������� �����
    wifstream inputFile("C:\\Users\\mypcs\\C++ Projects\\Test\\Projectlab6\\text.txt");
    inputFile.imbue(locale("ru_RU.UTF-8")); // ��������� ������� ���������

    if (!inputFile) {
        wcerr << L"�� ������� ������� ���� text.txt" << endl;
        return 1;
    }

    wstring line;
    while (getline(inputFile, line)) {
        wcout << L"����������� ������: " << line << endl;
    }

    // ����� ��������� �� ������ ����� ��� ������������ ������ ����
    inputFile.clear();
    inputFile.seekg(0, ios::beg);

    HashSet<wchar_t> allLetters;    // ��� ����� (������ ��������� ����)
    HashSet<wchar_t> usedLetters;   // �������������� ����� (������ ��, ��� ����������� � ������)

    wstring word;
    while (inputFile >> word) {
        for (wchar_t letter : word) {
            if (iswalpha(letter)) {
                allLetters.add(towlower(letter));   // ��� �����
                usedLetters.add(towlower(letter));  // �������������� �����
            }
        }
    }

    inputFile.close();

    // ����� ������ ���������, ������� �� ����������� ���� �� � ����� �����
    usedLetters.printMissingDeafConsonants(allLetters);
    setlocale(LC_ALL, "Russian_Russia.1251");  // ��� ��������� Windows-1251

    cout << endl;

    cout << "������� 5" << endl;
    

    // ������ ���������� ����������
    int N;
    wcout << L"������� ���������� ����������: ";
    cin >> N;
    cin.ignore();  // ����� ������������ ������ ����� ������ ����� ����� �����

    // ������� ������ ��� �������� ����������
    Dict<wstring> participants;

    // ������ ������ ����������
    wcout << L"������� ������ ���������� (������� ��� �����):\n";
    for (int i = 0; i < N; ++i) {
        wstring line;
        getline(wcin, line);  // ��������� ������, ���������� �������, ��� � �����

        // ��������� ������ �� ��������� ��������
        wstringstream ss(line);
        wstring lastName, firstName;
        int task1, task2, task3;

        ss >> lastName >> firstName >> task1 >> task2 >> task3;  // ��������� �� ����������

        // ��������� ���� (������� + ���)
        wstring key = lastName + L" " + firstName;

        // ��������� ��������� � �������
        participants.add(key, Dict<wstring>::Scores(task1, task2, task3));
    }

    // ������� ���������� � ������������� �������
    vector<wstring> maxScoreParticipants = participants.getMaxScoreParticipants();

    // ������� ���������� � ������������� �������
    wcout << L"��������� � ������������� �������:\n";
    for (const wstring& participant : maxScoreParticipants) {
        wcout << participant << endl;
    }

    return 0;
}

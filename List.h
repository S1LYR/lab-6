#ifndef LIST_H
#define LIST_H

#include <iostream>
using namespace std;

// ������ ������ ��� ����������������� ������
template <typename T>
class List {
private:
    struct Node {
        T data;
        Node* next;

        Node(T value) : data(value), next(nullptr) {}
    };

    Node* head;

public:
    // �����������
    List() : head(nullptr) {}

    // ����������
    ~List() {
        clear();
    }

    // ����� ��� ���������� �������� � ����� ������
    void add(T value);

    // ����� ��� �������� ������� ��������
    void removeFirst();

    // ����� ��� ������ ������� ��������� ������ L1 � ������ L
    Node* findSublist(List<T>& sublist);

    // ����� ��� ������ ������� ��������� L1 �� L2
    void replaceSublist(List<T>& sublist1, List<T>& sublist2);

    // ����� ��� ������� ������
    void clear();

    // ����� ��� ������ ��������� ������
    void print();
};

// ����� ��� ���������� �������� � ����� ������
template <typename T>
void List<T>::add(T value) {
    Node* newNode = new Node(value);
    if (head == nullptr) {
        head = newNode;
    }
    else {
        Node* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// ����� ��� �������� ������� ��������
template <typename T>
void List<T>::removeFirst() {
    if (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

// ����� ��� ������� ������
template <typename T>
void List<T>::clear() {
    while (head != nullptr) {
        removeFirst();
    }
}

// ����� ��� ������ ��������� ������
template <typename T>
void List<T>::print() {
    Node* temp = head;
    while (temp) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

// ����� ��� ������ ������� ��������� ���������
template <typename T>
typename List<T>::Node* List<T>::findSublist(List<T>& sublist) {
    Node* temp = head;
    Node* sublistHead = sublist.head;

    while (temp) {
        Node* node1 = temp;
        Node* node2 = sublistHead;

        // ����, ������������� �� ������������������ ��������� ������ L1
        while (node2 && node1 && node1->data == node2->data) {
            node1 = node1->next;
            node2 = node2->next;
        }

        // ���� ��� �������� �������, ���������� ��������� �� ������ ����������
        if (!node2) {
            return temp;
        }

        temp = temp->next;
    }

    return nullptr; // ���� �� �����
}

// ����� ��� ������ ������� ��������� ������ L1 �� ������ L2
template <typename T>
void List<T>::replaceSublist(List<T>& sublist1, List<T>& sublist2) {
    Node* pos = findSublist(sublist1);
    if (pos) {
        Node* sublistTemp = sublist2.head;

        // �������� ��������
        while (sublistTemp) {
            pos->data = sublistTemp->data;
            pos = pos->next;
            sublistTemp = sublistTemp->next;
        }
    }
}

#endif

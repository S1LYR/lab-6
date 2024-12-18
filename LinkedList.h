#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
using namespace std;

// ����� ����������� ������
template <typename T>
class LinkedList {
private:
    // ��������� ���� ����������� ������
    struct Node {
        T data;
        Node* next;
        Node* prev;

        Node(T value) : data(value), next(nullptr), prev(nullptr) {}
    };

    Node* head;  // ��������� �� ������ ����
    Node* tail;  // ��������� �� ��������� ����

public:
    // �����������
    LinkedList() : head(nullptr), tail(nullptr) {}

    // ����������
    ~LinkedList() {
        clear();
    }

    // ���������� �������� � ����� ������
    void add(T value) {
        Node* newNode = new Node(value);
        if (tail == nullptr) {
            head = tail = newNode;  // ������ ����, ����� ������� � � ������, � �����
        }
        else {
            tail->next = newNode;   // ����������� ����� ���� � ������
            newNode->prev = tail;   // ������������� ������ �� ���������� ����
            tail = newNode;         // ����� ���� ���������� �������
        }
    }

    // �������� ��������
    void remove(Node* node) {
        if (node->prev) {
            node->prev->next = node->next;  // ����������� ��������� ���� � �����������
        }
        else {
            head = node->next;  // ���� ���� ��� �������, ��������� ������
        }

        if (node->next) {
            node->next->prev = node->prev;  // ����������� ���������� ���� � ����������
        }
        else {
            tail = node->prev;  // ���� ���� ��� �������, ��������� �����
        }

        delete node;  // ������� ����
    }

    // ������� ������
    void clear() {
        Node* temp = head;
        while (temp) {
            Node* next = temp->next;
            delete temp;
            temp = next;
        }
        head = tail = nullptr;  // ������ ����
    }

    // ������ ��������� ������
    void print() {
        Node* temp = head;
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    // ���������� ������ �� �����������
    void sort() {
        if (head == nullptr) return;  // ���� ������ ����, ������ �� ������

        bool swapped;
        do {
            swapped = false;
            Node* current = head;
            while (current && current->next) {
                if (current->data > current->next->data) {
                    // ���������� ������
                    T temp = current->data;
                    current->data = current->next->data;
                    current->next->data = temp;
                    swapped = true;
                }
                current = current->next;
            }
        } while (swapped);  // ���������, ���� ���� ���������
    }

    // �������� ���������� ����
    Node* getPrevious(Node* node) {
        return node ? node->prev : nullptr;
    }

    // �������� ��������� ����
    Node* getNext(Node* node) {
        return node ? node->next : nullptr;
    }

    // �������� ������ ������
    Node* getHead() {
        return head;
    }

    // �������� ����� ������
    Node* getTail() {
        return tail;
    }
};

#endif  // LINKEDLIST_H

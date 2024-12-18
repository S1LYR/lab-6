#ifndef LIST_H
#define LIST_H

#include <iostream>
using namespace std;

// Шаблон класса для однонаправленного списка
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
    // Конструктор
    List() : head(nullptr) {}

    // Деструктор
    ~List() {
        clear();
    }

    // Метод для добавления элемента в конец списка
    void add(T value);

    // Метод для удаления первого элемента
    void removeFirst();

    // Метод для поиска первого вхождения списка L1 в списке L
    Node* findSublist(List<T>& sublist);

    // Метод для замены первого вхождения L1 на L2
    void replaceSublist(List<T>& sublist1, List<T>& sublist2);

    // Метод для очистки списка
    void clear();

    // Метод для вывода элементов списка
    void print();
};

// Метод для добавления элемента в конец списка
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

// Метод для удаления первого элемента
template <typename T>
void List<T>::removeFirst() {
    if (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

// Метод для очистки списка
template <typename T>
void List<T>::clear() {
    while (head != nullptr) {
        removeFirst();
    }
}

// Метод для вывода элементов списка
template <typename T>
void List<T>::print() {
    Node* temp = head;
    while (temp) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

// Метод для поиска первого вхождения подсписка
template <typename T>
typename List<T>::Node* List<T>::findSublist(List<T>& sublist) {
    Node* temp = head;
    Node* sublistHead = sublist.head;

    while (temp) {
        Node* node1 = temp;
        Node* node2 = sublistHead;

        // Ищем, соответствует ли последовательность элементов списка L1
        while (node2 && node1 && node1->data == node2->data) {
            node1 = node1->next;
            node2 = node2->next;
        }

        // Если все элементы совпали, возвращаем указатель на первое совпадение
        if (!node2) {
            return temp;
        }

        temp = temp->next;
    }

    return nullptr; // Если не нашли
}

// Метод для замены первого вхождения списка L1 на список L2
template <typename T>
void List<T>::replaceSublist(List<T>& sublist1, List<T>& sublist2) {
    Node* pos = findSublist(sublist1);
    if (pos) {
        Node* sublistTemp = sublist2.head;

        // Заменяем элементы
        while (sublistTemp) {
            pos->data = sublistTemp->data;
            pos = pos->next;
            sublistTemp = sublistTemp->next;
        }
    }
}

#endif

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
using namespace std;

// Класс двусвязного списка
template <typename T>
class LinkedList {
private:
    // Структура узла двусвязного списка
    struct Node {
        T data;
        Node* next;
        Node* prev;

        Node(T value) : data(value), next(nullptr), prev(nullptr) {}
    };

    Node* head;  // Указатель на первый узел
    Node* tail;  // Указатель на последний узел

public:
    // Конструктор
    LinkedList() : head(nullptr), tail(nullptr) {}

    // Деструктор
    ~LinkedList() {
        clear();
    }

    // Добавление элемента в конец списка
    void add(T value) {
        Node* newNode = new Node(value);
        if (tail == nullptr) {
            head = tail = newNode;  // Список пуст, новый элемент — и голова, и хвост
        }
        else {
            tail->next = newNode;   // Привязываем новый узел к хвосту
            newNode->prev = tail;   // Устанавливаем ссылку на предыдущий узел
            tail = newNode;         // Новый узел становится хвостом
        }
    }

    // Удаление элемента
    void remove(Node* node) {
        if (node->prev) {
            node->prev->next = node->next;  // Привязываем следующий узел к предыдущему
        }
        else {
            head = node->next;  // Если узел был головой, обновляем голову
        }

        if (node->next) {
            node->next->prev = node->prev;  // Привязываем предыдущий узел к следующему
        }
        else {
            tail = node->prev;  // Если узел был хвостом, обновляем хвост
        }

        delete node;  // Удаляем узел
    }

    // Очистка списка
    void clear() {
        Node* temp = head;
        while (temp) {
            Node* next = temp->next;
            delete temp;
            temp = next;
        }
        head = tail = nullptr;  // Список пуст
    }

    // Печать элементов списка
    void print() {
        Node* temp = head;
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    // Сортировка списка по возрастанию
    void sort() {
        if (head == nullptr) return;  // Если список пуст, ничего не делаем

        bool swapped;
        do {
            swapped = false;
            Node* current = head;
            while (current && current->next) {
                if (current->data > current->next->data) {
                    // Обмениваем данные
                    T temp = current->data;
                    current->data = current->next->data;
                    current->next->data = temp;
                    swapped = true;
                }
                current = current->next;
            }
        } while (swapped);  // Повторяем, пока есть изменения
    }

    // Получить предыдущий узел
    Node* getPrevious(Node* node) {
        return node ? node->prev : nullptr;
    }

    // Получить следующий узел
    Node* getNext(Node* node) {
        return node ? node->next : nullptr;
    }

    // Получить голову списка
    Node* getHead() {
        return head;
    }

    // Получить хвост списка
    Node* getTail() {
        return tail;
    }
};

#endif  // LINKEDLIST_H

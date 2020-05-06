//
// Created by snirg on 03/05/2020.
//

#ifndef WET1_LINKEDLIST_H
#define WET1_LINKEDLIST_H

template<typename T>
struct Node {
    int key;
    T info;
    Node *next;
    Node *previous;
};

template<typename T>
class LinkedList {
private:
    Node<T> *head;
    Node<T> *last;
public:
    explicit LinkedList() : head(nullptr), last(nullptr) {}

    explicit LinkedList(int k, T i) : head(new Node<T>()) {
        this->head->key = k;
        this->head->info = i;
        this->head->next = nullptr;
        this->head->previous = nullptr;
        this->last = this->head;
    }

    Node<T> *createNode(int key, T info) {
        auto newNode = new Node<T>();
        newNode->key = key;
        newNode->info = info;
        newNode->next = nullptr;
        newNode->previous = this->last;
        return newNode;
    }

    void insertLast(int key, T info) {
        Node<T> *newNode = createNode(key, info);

        if (this->last) { this->last->next = newNode; }
        else { this->head = newNode; }
        this->last = newNode;
    }

    void insertFirst(int key, T info) {
        Node<T> *newNode = createNode(key, info);

        if (this->head) { this->head->previous = newNode; }
        else { this->last = newNode; }
        this->head = newNode;
    }

    Node<T> *getNodeByIndex(int index) {
        if (index < 0) { return nullptr; }
        Node<T> *iterator = this->head;
        for (int i = 0; i < index; ++i) {
            if (!iterator) { return nullptr; }
            iterator = iterator->next;
        }
        return iterator;
    }

    Node<T> *getNodeByKey(int key) {
        if (!this->head) { return nullptr; }
        Node<T> *iterator = this->head;
        while (iterator) {
            if (iterator->key == key) { return iterator; }
            iterator = iterator->next;
        }
        return iterator;
    }

    void deleteHead() {
        Node<T> *node = this->head;
        if (this->head == this->last) { this->last = nullptr; }
        this->head = this->head->next;
        if (this->head) { this->head->previous = nullptr; }
        delete node;
    }

    void deleteLast() {
        Node<T> *node = this->last;
        if (this->head == this->last) { this->head = nullptr; }
        this->last = this->last->previous;
        if(this->last){this->last->next = nullptr;}
        delete node;
    }

    void deleteNodeByPointer(Node<T> *node) {
        if (!node) { return; }
        if (node->previous && node->next) {
            node->previous->next = node->next;
            node->next->previous = node->previous;
            delete node;
            return;
        }
        if (!node->previous) {
            this->head = node->next;
            this->head->previous = nullptr;
        }
        if (!node->next) {
            this->last = node->previous;
            this->last->next = nullptr;
        }
        delete node;

    }

    void deleteNodeByKey(int key) {
        deleteNodeByPointer(getNodeByKey(key));
    }
};


#endif //WET1_LINKEDLIST_H

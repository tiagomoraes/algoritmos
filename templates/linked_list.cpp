#include <bits/stdc++.h>

using namespace std;

template<typename T>
struct linked_list {
    struct node {
        T value;
        node *prev;
        node *next;

        node(T value) : value(value), prev(nullptr), next(nullptr) {}
    };

    node *head;
    node *tail;
    int size;

    linked_list() : head(nullptr), tail(nullptr), size(0) {}

    virtual ~linked_list() {
        node *cur = this->head;
        while (cur) {
            node *n = cur;
            cur = cur->next;
            delete n;
        }
    }

    void add_back(T i) {
        node *n = new node(i);

        if (this->tail) {
            this->tail->next = n;
            n->prev = this->tail;
        } else
            this->head = n;
        this->tail = n;

        ++this->size;
    }

    void add_front(T i) {
        node *n = new node(i);

        if (this->head) {
            this->head->prev = n;
            n->next = this->head;
        } else
            this->tail = n;
        this->head = n;

        ++this->size;
    }

    bool add_middle(T val, int index) {
        node *n = new node(val);

        int i = 0;
        for (node *cur = this->head; cur; cur = cur->next) {
            if (i == index) {
                n->prev = cur->prev;
                n->next = cur;
                if (cur->prev)
                    cur->prev->next = n;
                else
                    this->head = n;
                cur->prev = n;

                ++this->size;
                return true;
            }
            ++i;
        }
        return false;
    }

    bool remove(T val) {
        for (node *cur = this->head; cur; cur = cur->next)
            if (cur->value == val) {
                if (cur->prev)
                    cur->prev->next = cur->next;
                else
                    this->head = cur->next;
                if (cur->next)
                    cur->next->prev = cur->prev;
                else
                    this->tail = cur->prev;
                delete cur;

                --this->size;
                return true;
            }
        return false;
    }

    T *get(int index) {
        int i = 0;
        for (node *cur = this->head; cur; cur = cur->next) {
            if (i == index)
                return &cur->value;
            ++i;
        }
        return nullptr;
    }

    void print() {
        node *cur = this->head;
        while (cur) {
            cout << cur->value << endl;
            cur = cur->next;
        }
    }
};

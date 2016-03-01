#ifndef SLIST_H
#define SLIST_H
#include <stdio.h>
template<typename T>
struct Slist {
    struct Element {
        T data;
        Element *next;
        Element() {
            next = NULL;
        }
    };
	Element *head;
	Element *tail;
    Slist() {
        head = new Element;
        tail = head;
    }
    ~Slist() {
    }

    Element *Delete(Element *delElement, Element *preElement) {
        preElement->next = delElement->next;
        if(delElement == tail) {
            tail = preElement;
        }
        delete delElement;

        if(tail == NULL) {
            tail = head;
        }

        return preElement->next;
    }
    void PushBack(T data) {
        tail->next = new Element;
        tail->next->data = data;
        tail = tail->next;
    }

};
#endif // SLIST_H

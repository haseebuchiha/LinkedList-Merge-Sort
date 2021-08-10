#include<iostream>

using namespace std;

class Node {
public:
    int data;
    Node *next = NULL;
};

class LinkList {
public:
    LinkList();

    ~LinkList();


    void appendNode(int value) { //N
        if (head == NULL) {
            head = new Node;
            head->data = value;
            head->next = NULL;
        } else {
            Node *temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = new Node;
            temp = temp->next;
            temp->data = value;
            temp->next = NULL;
        }
        size++;
    }

    bool findNode(int value) { //N
        if (head == NULL) {
            return NULL;
        }
        Node *temp = head;
        while (temp != NULL) {
            if (temp->data == value) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    bool updateNode(int value, int newValue) { //N
        if (head == NULL) {
            return false;
        }
        Node *temp = head;
        while (temp != NULL) {
            if (temp->data == value) {
                temp->data = newValue;
                return true;
            }
            temp = temp->next;
        }
        return false;

    }

    bool deleteNode(int value) {
        if (head->data == value && head->next != NULL) {
            Node *current = head;
            head = head->next;
            delete current;
            size--;
            return true;
        } else if (head->data == value) {
            head = NULL;
            size--;
            return true;
        }
        Node *temp = head; // 1->NULL
        Node *prev = head;
        while (temp != NULL) {
            if (temp->data == value) {
                Node *current = temp;
                temp = temp->next;
                prev->next = temp;
                delete current;
                size--;
                return true;
            }
            prev = temp;
            temp = temp->next;
        }
        return false;
    }

    void printList() {
        if (head != NULL) {
            Node *temp = head;
            while (temp != NULL) {
                cout << temp->data << " -> ";
                temp = temp->next;
            }
        }
        cout << "NULL" << endl;
    }

    size_t length() {
        return size;
    }

    int &operator[](int index) {
        if (index > size) {
            cout << "Index out of bound" << endl;
            return head->data;
        }
        Node *temp = head;
        int counter = 0;
        while (temp != NULL) {
            if (counter == index) {
                return temp->data;
            }
            temp = temp->next;
            ++counter;
        }
    }

private:
    Node *head = NULL;
    size_t size = 0;
};

LinkList sortNodes(LinkList list);


LinkList::LinkList() {
}

LinkList::~LinkList() {
}


//Haan bhai merge sort

void merge(LinkList &list, LinkList &left, LinkList &right) {
    int i = 0, j = 0, k = 0;
    while (i < left.length() && j < right.length()) {
        if (left[i] <= right[j]) {
            list[k] = left[i];
            ++i;
        } else if (right[j] < left[i]) {
            list[k] = right[j];
            ++j;
        }
        ++k;
    }
    while (i < left.length()) {
        list[k] = left[i];
        ++i;
        ++k;
    }
    while (j < right.length()) {
        list[k] = right[j];
        ++j;
        ++k;
    }
}

void split(LinkList &list, LinkList &left, LinkList &right) {
    int size = list.length();
    int mid = floor(size / 2);

    for (int i = 0; i < mid; i++) {
        left.appendNode(list[i]);
    }
    for (int i = mid; i < list.length(); i++) {
        right.appendNode(list[i]);
    }
}

void mergeSort(LinkList &list) {
    if (list.length() == 1) return;

    LinkList left;
    LinkList right;

    split(list, left, right);

    mergeSort(left);
    mergeSort(right);

    merge(list, left, right);
}


int main() {
    LinkList list;
    list.appendNode(16);
    list.appendNode(13);
    list.appendNode(18);
    list.appendNode(14);
    list.appendNode(12);
    list.printList();
    mergeSort(list);
    list.printList();

    return 0;
}
#include <iostream>
#include <vector>
//#include "leaker.h"
using namespace std;

template <typename T>
class LinkedList {
    public:
        struct Node {
            T data;
            Node* next;
            Node* prev;
            Node();
            Node(T data, Node* next, Node* prev);
        };
        LinkedList();
        LinkedList(const LinkedList<T>& list);
        ~LinkedList();
        void AddHead(const T& data);
        void AddTail(const T& data);
        void AddNodesHead(const T* data, unsigned int count);
        void AddNodesTail(const T* data, unsigned int count);
        unsigned int NodeCount() const;
        void PrintForward() const;
        void PrintReverse() const;
        Node* Head();
        const Node* Head() const;
        Node* Tail();
        const Node* Tail() const;
        Node* GetNode(unsigned int index);
        const Node* GetNode(unsigned int index) const;
        T& operator[](unsigned int index);
        const T& operator[](unsigned int index) const;
        Node* Find(const T& data);
        const Node* Find(const T& data) const;
        void FindAll(vector<Node*>& outData, const T& value) const;
        LinkedList<T>& operator=(const LinkedList<T>& rhs);
        void InsertAfter(Node* node, const T& data);
        void InsertBefore(Node* node, const T& data);
        void InsertAt(const T& data, unsigned int index);
        bool operator==(const LinkedList<T>& rhs) const;
        bool RemoveHead();
        bool RemoveTail();
        unsigned int Remove(const T& data);
        bool RemoveAt(unsigned int index);
        void Clear();
        void PrintForwardRecursive(const Node* node) const;
        void PrintReverseRecursive(const Node* node) const;
    private:
        unsigned int nodes;
        Node* head;
        Node* tail;
};

template <typename T>
LinkedList<T>::Node::Node() {
    next = nullptr;
    prev = nullptr;
}

template <typename T>
LinkedList<T>::Node::Node(T data, Node* next, Node* prev) {
    this->data = data;
    this->next = next;
    this->prev = prev;
}

template <typename T>
LinkedList<T>::LinkedList() {
    nodes = 0;
    head = nullptr;
    tail = nullptr;
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& list) {
    this->nodes = list.nodes;
    this->head = new Node(list.head->data, nullptr, nullptr);
    Node* currentNodeOriginal = list.head->next;
    Node* prevNode = this->head;
    unsigned int _count = 1;
    while (currentNodeOriginal->next != nullptr) {
        Node* newNode = new Node(currentNodeOriginal->data, nullptr, prevNode);
        newNode->prev->next = newNode;
        currentNodeOriginal = currentNodeOriginal->next;
        prevNode = newNode;
        ++_count;
    }
    Node* newNode1 = new Node(currentNodeOriginal->data, nullptr, prevNode);
    newNode1->prev->next = newNode1;
    this->tail = newNode1;
}

template <typename T>
LinkedList<T>::~LinkedList() {
    if (nodes == 0) {
        return;
    }
    Node* currentNode = head;
    Node* temp;

    while (currentNode->next != nullptr) {
        temp = currentNode->next;
        delete currentNode;
        currentNode = temp;
    }
    delete currentNode;
}

template <typename T>
void LinkedList<T>::AddHead(const T& data) {
    Node* newNode = new Node(data, head, nullptr);
    head = newNode;
    if (nodes == 0) {
        head = newNode;
        tail = newNode;
    }
    else {
        newNode->next->prev = newNode;
    }
    nodes++;
}

template <typename T>
void LinkedList<T>::AddTail(const T& data) {
    Node* newNode = new Node(data, nullptr, tail);
    tail = newNode;
    if (nodes == 0) {
        head = newNode;
        tail = newNode;
    }
    else {
        newNode->prev->next = newNode;
    }
    nodes++;
}

template <typename T>
void LinkedList<T>::AddNodesHead(const T* data, unsigned int count) {
    for (int i = (count - 1); i > -1; --i) {
        T dataToAdd = data[i];
        AddHead(dataToAdd);
    }
}

template <typename T>
void LinkedList<T>::AddNodesTail(const T* data, unsigned int count) {
    for (unsigned int i = 0; i < count; ++i) {
        T dataToAdd = data[i];
        AddTail(dataToAdd);
    }
}

template <typename T>
unsigned int LinkedList<T>::NodeCount() const {
    return nodes;
}

template <typename T>
void LinkedList<T>::PrintForward() const {
    Node* nextAddress = head;
    while (nextAddress->next != nullptr) {
        cout << nextAddress->data << endl;
        nextAddress = nextAddress->next;
    }
    cout << nextAddress->data << endl;
}

template <typename T>
void LinkedList<T>::PrintReverse() const {
    Node* nextAddress = tail;
    for (unsigned int i = 0; i < nodes; ++i) {
        cout << nextAddress->data << endl;
        nextAddress = nextAddress->prev;
    }
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Head() {
    return head;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Head() const {
    return head;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Tail() {
    return tail;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Tail() const {
    return tail;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) {
    if ((index >= nodes) || (index < 0)) {
        throw out_of_range("Index out of range!");
    }
    Node* nextAddress = head;
    for (unsigned int i = 0; i < index; i++) {
        nextAddress = nextAddress->next;
    }
    return nextAddress;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) const {
    if ((index >= nodes) || (index < 0)) {
        throw out_of_range("Index out of range!");
    }
    Node* nextAddress = head;
    for (unsigned int i = 0; i < index; i++) {
        nextAddress = nextAddress->next;
    }
    return nextAddress;
}

template <typename T>
T& LinkedList<T>::operator[](unsigned int index) {
    Node* nodePtr = GetNode(index);
    return nodePtr->data;
}

template <typename T>
const T& LinkedList<T>::operator[](unsigned int index) const {
    Node* nodePtr = GetNode(index);
    return nodePtr->data;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data) {
    Node* nextAddress = head;
    for (unsigned int i = 0; i < nodes; ++i) {
        if (data == nextAddress->data) {
            return nextAddress;
        }
        nextAddress = nextAddress->next;
    }
    return nullptr;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data) const {
    Node* nextAddress = head;
    for (int i = 0; i < nodes; ++i) {
        if (data == nextAddress->data) {
            return nextAddress;
        }
        nextAddress = nextAddress->next;
    }
    return nullptr;
}

template <typename T>
void LinkedList<T>::FindAll(vector<Node*>& outData, const T& value) const {
    Node* nextAddress = head;
    for (unsigned int i = 0; i < nodes; ++i) {
        if (value == nextAddress->data) {
            outData.push_back(nextAddress);
        }
        nextAddress = nextAddress->next;
    }
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rhs) {
    //delete previous nodes
    Node* temp;
    while (head->next != nullptr) {
        temp = head->next;
        delete head;
        head = temp;
    }
    delete head;

    //copying everything over
    this->nodes = rhs.nodes;
    this->head = new Node(rhs.head->data, nullptr, nullptr);
    Node* currentNodeOriginal = rhs.head->next;
    Node* prevNode = this->head;
    unsigned int _count = 1;
    while (currentNodeOriginal->next != nullptr) {
        Node* newNode = new Node(currentNodeOriginal->data, nullptr, prevNode);
        newNode->prev->next = newNode;
        currentNodeOriginal = currentNodeOriginal->next;
        prevNode = newNode;
        ++_count;
    }
    Node* newNode1 = new Node(currentNodeOriginal->data, nullptr, prevNode);
    newNode1->prev->next = newNode1;
    this->tail = newNode1;
    return *this;
}

template <typename T>
void LinkedList<T>::InsertAfter(Node* node, const T& data) {
    Node* nxtNode = node->next;
    Node* newNode = new Node(data, nxtNode, node);
    node->next = newNode;
    if (node != tail) {
        nxtNode->prev = newNode;
    }
    else {
        tail = newNode;
    }
    ++nodes;
}

template <typename T>
void LinkedList<T>::InsertBefore(Node* node, const T& data) {
    Node* prevNode = node->prev;
    Node* newNode = new Node(data, node, prevNode);
    if (node != head) {
        prevNode->next = newNode;
    }
    else {
        head = newNode;
    }
    node->prev = newNode;
    ++nodes;
}

template <typename T>
void LinkedList<T>::InsertAt(const T& data, unsigned int index) {
    if (index > nodes) {
        throw out_of_range("Index out of range!");
    }
    else if (index == 0) {
        AddHead(data);
    }
    else if (index == nodes) {
        AddTail(data);
    }
    else {
        Node* node = GetNode(index);
        InsertBefore(node, data);
    }
}

template <typename T>
bool LinkedList<T>::operator==(const LinkedList<T>& rhs) const {
    if (nodes == rhs.nodes) {
        Node* nextNodelhs = head;
        Node* nextNoderhs = rhs.head;
        while (nextNodelhs->next != nullptr) {
            if (nextNodelhs->data != nextNoderhs->data) {
                return false;
            }
            nextNodelhs = nextNodelhs->next;
            nextNoderhs = nextNoderhs->next;
        }
        if (nextNodelhs->data != nextNoderhs->data) {
            return false;
        }
    }
    return true;
}

template <typename T>
bool LinkedList<T>::RemoveHead() {
    if (nodes == 0) {
        return false;
    }
    else if (nodes == 1) {
        delete head;
        --nodes;
        return true;
    }
    else {
        Node* newHead = head->next;
        newHead->prev = nullptr;
        delete head;
        head = newHead;
        --nodes;
        return true;
    }
}

template <typename T>
bool LinkedList<T>::RemoveTail() {
    if (nodes == 0) {
        return false;
    }
    else if (nodes == 1) {
        delete tail;
        --nodes;
        return true;
    }
    else {
        Node* newTail = tail->prev;
        newTail->next = nullptr;
        delete tail;
        tail = newTail;
        --nodes;
        return true;
    }
}

template <typename T>
unsigned int LinkedList<T>::Remove(const T& data) {
    unsigned int count = 0;
    Node* currentNode = head;
    Node* prevNode = nullptr;
    Node* nxtNode = nullptr;
    while (currentNode->next != nullptr) {
        if (currentNode->data == data) {
            ++count;
            prevNode = currentNode->prev;
            nxtNode = currentNode->next;
            delete currentNode;
            --nodes;
            prevNode->next = nxtNode;
            nxtNode->prev = prevNode;
            currentNode = nxtNode;
        } else {
        currentNode = currentNode->next;
        }
    }
    if (currentNode->data == data) {
            ++count;
            prevNode = currentNode->prev;
            nxtNode = currentNode->next;
            delete currentNode;
            --nodes;
            prevNode->next = nxtNode;
            nxtNode->prev = prevNode;
        }
    return count;
}

template <typename T>
bool LinkedList<T>::RemoveAt(unsigned int index) {
    if ((index < 0) || (index >= nodes)) {
        return false;
    }
    else {
        Node* node = GetNode(index);
        Node* nextNode = node->next;
        Node* prevNode = node->prev;
        delete node;
        --nodes;
        prevNode->next = nextNode;
        nextNode->prev = prevNode;
        return true;
    }

}

template <typename T>
void LinkedList<T>::Clear() {
    if (nodes == 0) {
        return;
    }
    Node* currentNode = head;
    Node* temp;
    while (currentNode->next != nullptr) {
        temp = currentNode->next;
        delete currentNode;
        currentNode = temp;
    }
    delete currentNode;
    nodes = 0;
    head = nullptr;
    tail = nullptr;
}

template <typename T>
void LinkedList<T>::PrintForwardRecursive(const Node* node) const {
    if (node == nullptr) {
        return;
    }
    else {
        cout << node->data << endl;
        PrintForwardRecursive(node->next);
    }
}

template <typename T>
void LinkedList<T>::PrintReverseRecursive(const Node* node) const {
    if (node == nullptr) {
        return;
    }
    else {
        cout << node->data << endl;
        PrintReverseRecursive(node->prev);
    }
}
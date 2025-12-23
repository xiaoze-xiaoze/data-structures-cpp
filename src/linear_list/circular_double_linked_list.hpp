#include "../error/error.hpp"

template<typename T>
class CircularDoubleLinkList {
public:
    struct Node {
        T data;
        Node* prev;
        Node* next;
    };
    int length;

protected:
    Node* head;
    Node* tail;

public:
    CircularDoubleLinkList() : length(0) {
        head = new Node{ T(), nullptr, nullptr };
        head->next = head;
        head->prev = head;
        tail = head;
    }

    ~CircularDoubleLinkList() {
        clear();
        delete head;
    }

    int getLength() const { return length; }

    bool isEmpty() const { return length == 0; }

    std::expected<void, DataStructureError> insert(int index, const T& value) {
        if (index < 0 || index > length) return std::unexpected(DataStructureError::IndexOutOfRange);
        Node* prevNode = head;
        for (int i = 0;i < index;i++) prevNode = prevNode->next;
        Node* newNode = new Node{ value, prevNode, prevNode->next };
        prevNode->next->prev = newNode;
        prevNode->next = newNode;
        if (index == length) {
            tail = newNode;
            tail->next = head;
            head->prev = tail;
        }
        length++;
        return {};
    }

    std::expected<void, DataStructureError> pushFront(const T& value) {
        return insert(0, value);
    }

    std::expected<void, DataStructureError> pushBack(const T& value) {
        return insert(length, value);
    }

    std::expected<T, DataStructureError> erase(int index) {
        if (index < 0 || index >= length) return std::unexpected(DataStructureError::IndexOutOfRange);
        Node* deleteNode = head->next;
        for (int i = 0;i < index;i++) deleteNode = deleteNode->next;
        T value = deleteNode->data;
        deleteNode->prev->next = deleteNode->next;
        deleteNode->next->prev = deleteNode->prev;
        if (index == length - 1) {
            tail = deleteNode->prev;
            tail->next = head;
            head->prev = tail;
        }
        delete deleteNode;
        length--;
        return value;
    }

    std::expected<T, DataStructureError> popFront() {
        return erase(0);
    }

    std::expected<T, DataStructureError> popBack() {
        return erase(length - 1);
    }

    std::expected<void, DataStructureError> remove(const T& value) {
        Node* deleteNode = head->next;
        for (int i = 0;i < length;i++) {
            if (deleteNode->data == value) {
                deleteNode->prev->next = deleteNode->next;
                deleteNode->next->prev = deleteNode->prev;
                if (i == length - 1) {
                    tail = deleteNode->prev;
                    tail->next = head;
                    head->prev = tail;
                }
                delete deleteNode;
                length--;
                return {};
            }
            deleteNode = deleteNode->next;
        }
        return std::unexpected(DataStructureError::ElementNotFound);
    }

    std::expected<T, DataStructureError> get(int index) {
        if (index < 0 || index >= length) return std::unexpected(DataStructureError::IndexOutOfRange);
        Node* node = head->next;
        for (int i = 0;i < index;i++) node = node->next;
        return node->data;
    }

    std::expected<int, DataStructureError> find(const T& value) {
        Node* node = head->next;
        for (int i = 0;i < length;i++) {
            if (node->data == value) return i;
            node = node->next;
        }
        return std::unexpected(DataStructureError::ElementNotFound);
    }

    std::expected<T, DataStructureError> update(int index, const T& newValue) {
        if (index < 0 || index >= length) return std::unexpected(DataStructureError::IndexOutOfRange);
        Node* node = head->next;
        for (int i = 0;i < index;i++) node = node->next;
        T oldValue = node->data;
        node->data = newValue;
        return oldValue;
    }

    void clear() {
        Node* node = head->next;
        for (int i = 0;i < length;i++) {
            Node* nextNode = node->next;
            delete node;
            node = nextNode;
        }
        head->next = head;
        tail = head;
        length = 0;
    }
};
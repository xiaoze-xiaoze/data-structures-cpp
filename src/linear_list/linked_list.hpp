#include "../error/error.hpp"

template<typename T>
class LinkList {
public:
    struct Node {
        T data;
        Node* next;
    };
    int length;

protected:
    Node* head;

public:
    LinkList(): length(0) { head = new Node{ T(), nullptr }; }

    ~LinkList() {
        clear();
        delete head;
    }

    int getLength() const { return length; }

    bool isEmpty() const { return length == 0; }

    std::expected<void, DataStructureError> insert(int index, const T& value) {
        if (index < 0 || index > length) return std::unexpected(DataStructureError::IndexOutOfRange);
        Node* prevNode = head;
        for (int i = 0;i < index;i++) prevNode = prevNode->next;
        Node* newNode = new Node{ value, prevNode->next };
        prevNode->next = newNode;
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
        Node* prevNode = head;
        for (int i = 0;i < index;i++) prevNode = prevNode->next;
        Node* deleteNode = prevNode->next;
        prevNode->next = deleteNode->next;
        T value = deleteNode->data;
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
        Node* prevNode = head;
        for (int i = 0;i < length;i++) {
            if (prevNode->next->data == value) {
                Node* deleteNode = prevNode->next;
                prevNode->next = deleteNode->next;
                delete deleteNode;
                length--;
                return {};
            }
            prevNode = prevNode->next;
        }
        return std::unexpected(DataStructureError::ElementNotFound);
    }

    std::expected<T, DataStructureError> get(int index) {
        if (index < 0 || index >= length) return std::unexpected(DataStructureError::IndexOutOfRange);
        Node* p = head->next;
        for (int i = 0;i < index;i++) p = p->next;
        return p->data;
    }

    std::expected<int, DataStructureError> find(const T& value) {
        Node* p = head->next;
        for (int i = 0;i < length;i++) {
            if (p->data == value) return i;
            p = p->next;
        }
        return std::unexpected(DataStructureError::ElementNotFound);
    }

    std::expected<T, DataStructureError> update(int index, const T& newValue) {
        if (index < 0 || index >= length) return std::unexpected(DataStructureError::IndexOutOfRange);
        Node* p = head->next;
        for (int i = 0;i < index;i++) p = p->next;
        T oldValue = p->data;
        p->data = newValue;
        return oldValue;
    }

    void clear() {
        Node* node = head->next;
        for (int i = 0;i < length;i++) {
            Node* deleteNode = node;
            node = node->next;
            delete deleteNode;
        }
        head->next = nullptr;
        length = 0;
    }
};
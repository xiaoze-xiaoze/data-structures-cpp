#include <vector>
#include "../error/error.hpp"

template<typename T>
class CircularDequeue {
public:
    std::vector<T> data;
    int front;
    int rear;
    int capacity;
    int length;

    CircularDequeue() = default;
    explicit CircularDequeue(int capacity) : capacity(capacity + 1), front(0), rear(0), length(0) { data.resize(capacity); }

    ~CircularDequeue() = default;

    bool isEmpty() const { return length == 0; }

    bool isFull() const { return length == capacity - 1; }

    int getCapacity() const { return capacity - 1; }

    int getLength() const { return length; }

    std::expected<void, DataStructureError> pushFront(const T& value) {
        if (isFull()) return std::unexpected(DataStructureError::ContainerIsFull);
        front = (front - 1 + capacity) % capacity;
        data[front] = value;
        length++;
        return {};
    }

    std::expected<void, DataStructureError> pushRear(const T& value) {
        if (isFull()) return std::unexpected(DataStructureError::ContainerIsFull);
        data[rear] = value;
        rear = (rear + 1) % capacity;
        length++;
        return {};
    }

    std::expected<T, DataStructureError> popFront() {
        if (isEmpty()) return std::unexpected(DataStructureError::ContainerIsEmpty);
        T value = data[front];
        front = (front + 1) % capacity;
        length--;
        return value;
    }

    std::expected<T, DataStructureError> popRear() {
        if (isEmpty()) return std::unexpected(DataStructureError::ContainerIsEmpty);
        rear = (rear - 1 + capacity) % capacity;
        T value = data[rear];
        length--;
        return value;
    }

    std::expected<T, DataStructureError> getFront() const {
        if (isEmpty()) return std::unexpected(DataStructureError::ContainerIsEmpty);
        return data[front];
    }

    std::expected<T, DataStructureError> getRear() const {
        if (isEmpty()) return std::unexpected(DataStructureError::ContainerIsEmpty);
        return data[(rear - 1 + capacity) % capacity];
    }

    void clear() {
        front = rear = length = 0;
    }
};
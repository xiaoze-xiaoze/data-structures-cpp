#include <vector>
#include "../error/error.hpp"

template<typename T>
class CircularDeque {
public:
    std::vector<T> data;
    int front;
    int rear;
    int capacity;

    CircularDeque() = default;
    explicit CircularDeque(int capacity) : capacity(capacity + 1), front(0), rear(0) { data.resize(capacity); }

    ~CircularDeque() = default;

    bool isEmpty() const { return front == rear; }

    bool isFull() const { return front == (rear + 1) % capacity; }

    int getCapacity() const { return capacity - 1; }

    int getLength() const { return (rear - front + capacity) % capacity; }

    std::expected<void, DataStructureError> push(const T& value) {
        if (isFull()) return std::unexpected(DataStructureError::ContainerIsFull);
        data[rear] = value;
        rear = (rear + 1) % capacity;
        return {};
    }

    std::expected<T, DataStructureError> pop() {
        if (isEmpty()) return std::unexpected(DataStructureError::ContainerIsEmpty);
        T value = data[front];
        front = (front + 1) % capacity;
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
        front = rear = 0;
    }
};
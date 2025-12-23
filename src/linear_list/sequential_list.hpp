#include "../error/error.hpp"

template<typename T>
class SequentialList {
public:
    T* data;
    int capacity;
    int length;

    explicit SequentialList(int capacity) : capacity(capacity), length(0), data(new T[capacity]) {}

    ~SequentialList() { delete[] data; }

    int getCapacity() { return capacity; }
    
    int getLength() { return length; }
    
    bool isEmpty() { return length == 0; }

    bool isFull() { return length == capacity; }

    std::expected<void, DataStructureError> insert(int index, const T& value) {
        if (index < 0 || index > length) return std::unexpected(DataStructureError::IndexOutOfRange);
        if (isFull()) return std::unexpected(DataStructureError::ContainerIsFull);
        for (int i = length; i > index; i--) data[i] = data[i - 1];
        data[index] = value;
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
        if (isEmpty()) return std::unexpected(DataStructureError::ContainerIsEmpty);
        T value = data[index];
        for (int i = index;i < length - 1;i++) data[i] = data[i + 1];
        length--;
        return value;
    }

    std::expected<T, DataStructureError> popFront() {
        return erase(0);
    }

    std::expected<T, DataStructureError> popBack() {
        return erase(length - 1);
    }

    std::expected<T, DataStructureError> remove(const T& value) {
        for (int i = 0;i < length;i++) {
            if (data[i] == value) {
                for (int j = i;j < length - 1;j++) data[j] = data[j + 1];
                length--;
                return value;
            }
        }
        return std::unexpected(DataStructureError::ElementNotFound);
    }

    std::expected<T, DataStructureError> get(int index) {
        if (index < 0 || index >= length) return std::unexpected(DataStructureError::IndexOutOfRange);
        if (isEmpty()) return std::unexpected(DataStructureError::ContainerIsEmpty);
        return data[index];
    }

    std::expected<int, DataStructureError> find(const T& value) {
        if (isEmpty()) return std::unexpected(DataStructureError::ContainerIsEmpty);
        for (int i = 0;i < length;i++) {
            if (data[i] == value) return i;
        }
        return std::unexpected(DataStructureError::ElementNotFound);
    }

    std::expected<T, DataStructureError> update(int index, const T& newValue) {
        if (index < 0 || index >= length) return std::unexpected(DataStructureError::IndexOutOfRange);
        if (isEmpty()) return std::unexpected(DataStructureError::ContainerIsEmpty);
        T value = data[index];
        data[index] = newValue;
        return value;
    }

    int reverse(int addCapacity) {
        T* newData = new T[capacity + addCapacity];
        for (int i = 0;i < length;i++) newData[i] = data[i];
        delete[] data;
        data = newData;
        capacity += addCapacity;
        return capacity;
    }

    void clear() {
        length = 0;
    }
};
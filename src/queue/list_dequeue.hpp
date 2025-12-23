#include <list>
#include "../error/error.hpp"

template<typename T>
class ListDequeue {
public:
    std::list<T> data;

    ListDequeue() = default;

    ~ListDequeue() = default;

    bool isEmpty() const { return data.empty(); }

    int getLength() const { return data.size(); }

    void pushFront(const T& value) {
        data.push_front(value);
    }

    void pushRear(const T& value) {
        data.push_back(value);
    }

    std::expected<T, DataStructureError> popFront() {
        if (isEmpty()) return std::unexpected(DataStructureError::ContainerIsEmpty);
        T value = data.front();
        data.pop_front();
        return value;
    }

    std::expected<T, DataStructureError> popRear() {
        if (isEmpty()) return std::unexpected(DataStructureError::ContainerIsEmpty);
        T value = data.back();
        data.pop_back();
        return value;
    }

    std::expected<T, DataStructureError> getFront() const {
        if (isEmpty()) return std::unexpected(DataStructureError::ContainerIsEmpty);
        return data.front();
    }

    std::expected<T, DataStructureError> getRear() const {
        if (isEmpty()) return std::unexpected(DataStructureError::ContainerIsEmpty);
        return data.back();
    }

    void clear() {
        data.clear();
    }
};
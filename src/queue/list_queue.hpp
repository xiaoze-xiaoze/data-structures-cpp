#include <list>
#include "../error/error.hpp"

template<typename T>
class LinkQueue {
public:
    std::list<T> data;

    LinkQueue() = default;

    ~LinkQueue() = default;

    bool isEmpty() const { return data.empty(); }

    int getLength() const { return data.size(); }

    void push(const T& value) {
        data.push_back(value);
    }

    std::expected<T, DataStructureError> pop() {
        if (isEmpty()) return std::unexpected(DataStructureError::ContainerIsEmpty);
        T value = data.front();
        data.pop_front();
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
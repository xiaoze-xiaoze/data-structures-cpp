#include "binary_tree.cpp"

template<typename T>
class BinarySearchTree : public BinaryTree<T> {
public:
    using Node = typename BinaryTree<T>::Node;

protected:
    using BinaryTree<T>::root;

public:
    BinarySearchTree() : BinaryTree<T>() {}

    std::expected<void, DataStructureError> insert(const T& value) {
        if (root == nullptr) {
            root = new Node{value, nullptr, nullptr, nullptr};
            return {};
        }
        Node* current = root;
        while (current != nullptr) {
            if (value < current->data) {
                if (current->left == nullptr) {
                    current->left = new Node{value, current, nullptr, nullptr};
                    break;
                }
                current = current->left;
            }
            else if (value > current->data) {
                if (current->right == nullptr) {
                    current->right = new Node{value, current, nullptr, nullptr};
                    break;
                }
                current = current->right;
            }
            else return std::unexpected(DataStructureError::DuplicateValue);
        }
        return {};
    }

    std::expected<Node*, DataStructureError> find(const T& value) {
        Node* current = root;
        while (current != nullptr) {
            if (value == current->data) return current;
            current = (value < current->data) ? current->left : current->right;
        }
        return std::unexpected(DataStructureError::ElementNotFound);
    }

    std::expected<T, DataStructureError> getMin() {
        if (root == nullptr) return std::unexpected(DataStructureError::ContainerIsEmpty);
        Node* current = root;
        while (current->left != nullptr) current = current->left;
        return current->data;
    }

    std::expected<T, DataStructureError> getMax() {
        if (root == nullptr) return std::unexpected(DataStructureError::ContainerIsEmpty);
        Node* current = root;
        while (current->right != nullptr) current = current->right;
        return current->data;
    }

    std::expected<Node*, DataStructureError> remove(const T& value) {
        if (root == nullptr) return std::unexpected(DataStructureError::ContainerIsEmpty);
        TRY(target, find(value));
        Node* rebalanceStart = nullptr;
        if (target->left == nullptr && target->right == nullptr) {
            rebalanceStart = target->parent;
            if (target == root) root = nullptr;
            else if (target == target->parent->left) target->parent->left = nullptr;
            else target->parent->right = nullptr;
            delete target;
        }
        else if (target->left == nullptr || target->right == nullptr) {
            Node* child = target->left ? target->left : target->right;
            rebalanceStart = target->parent;
            if (target == root) {
                root = child;
                root->parent = nullptr;
            }
            else if (target->parent->left == target) {
                target->parent->left = child;
                child->parent = target->parent;
            }
            else {
                target->parent->right = child;
                child->parent = target->parent;
            }
            delete target;
        }
        else {
            Node* successor = target->right;
            while (successor->left != nullptr) successor = successor->left;
            target->data = successor->data;
            rebalanceStart = successor->parent;
            if (successor->parent->left == successor) successor->parent->left = successor->right;
            else successor->parent->right = successor->right;
            if (successor->right) successor->right->parent = successor->parent;
            delete successor;
        }
        return rebalanceStart;
    }
};
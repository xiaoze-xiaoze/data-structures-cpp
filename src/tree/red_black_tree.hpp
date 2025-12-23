#include "../error/error.hpp"

template<typename T>
class RedBlackTree {
public:
    enum Color {RED, BLACK};
    struct Node {
        T data;
        Node* parent;
        Node* left;
        Node* right;
        Color color;
    };

protected:
    Node* root;

    void rotateLeft(Node* node) {
        Node* newRoot = node->right;
        Node* orphan = newRoot->left;
        newRoot->left = node;
        node->right = orphan;
        newRoot->parent = node->parent;
        node->parent = newRoot;
        if (orphan) orphan->parent = node;
        if (newRoot->parent == nullptr) root = newRoot;
        else if (newRoot->parent->left == node) newRoot->parent->left = newRoot;
        else newRoot->parent->right = newRoot;
    }

    void rotateRight(Node* node) {
        Node* newRoot = node->left;
        Node* orphan = newRoot->right;
        newRoot->right = node;
        node->left = orphan;
        newRoot->parent = node->parent;
        node->parent = newRoot;
        if (orphan) orphan->parent = node;
        if (newRoot->parent == nullptr) root = newRoot;
        else if (newRoot->parent->left == node) newRoot->parent->left = newRoot;
        else newRoot->parent->right = newRoot;
    }

    void insertFixUp(Node* node) {
        while (node->parent != nullptr && node->parent->color == RED) {
            Node* parent = node->parent;
            Node* grandparent = parent->parent;
            if (parent == grandparent->left) {
                Node* uncle = grandparent->right;
                if (uncle != nullptr && uncle->color == RED) {
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    grandparent->color = RED;
                    node = grandparent;
                } 
                else {
                    if (node == parent->right) {
                        rotateLeft(parent);
                        node = parent;
                        parent = node->parent;
                    }
                    parent->color = BLACK;
                    grandparent->color = RED;
                    rotateRight(grandparent);
                }
            }
            else {
                Node* uncle = grandparent->left;
                if (uncle != nullptr && uncle->color == RED) {
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    grandparent->color = RED;
                    node = grandparent;
                } 
                else {
                    if (node == parent->left) {
                        rotateRight(parent);
                        node = parent;
                        parent = node->parent;
                    }
                    parent->color = BLACK;
                    grandparent->color = RED;
                    rotateLeft(grandparent);
                }
            }
        }
        root->color = BLACK;
    }

    void removeFixUp(Node* node, Node* parent) {
        while (node != root && (node == nullptr || node->color == BLACK)) {
            if (node == parent->left) {
                Node* sibling = parent->right;
                if (sibling != nullptr && sibling->color == RED) {
                    sibling->color = BLACK;
                    parent->color = RED;
                    rotateLeft(parent);
                    sibling = parent->right;
                }
                bool leftChildBlack = (sibling->left == nullptr || sibling->left->color == BLACK);
                bool rightChildBlack = (sibling->right == nullptr || sibling->right->color == BLACK);
                if (leftChildBlack && rightChildBlack) {
                    sibling->color = RED;
                    node = parent;
                    parent = node->parent;
                }
                else {
                    if (rightChildBlack) {
                        if (sibling->left != nullptr) sibling->left->color = BLACK;
                        sibling->color = RED;
                        rotateRight(sibling);
                        sibling = parent->right;
                    }
                    sibling->color = parent->color;
                    parent->color = BLACK;
                    if (sibling->right != nullptr) sibling->right->color = BLACK;
                    rotateLeft(parent);
                    node = root;
                }
            }
            else {
                Node* sibling = parent->left;
                if (sibling != nullptr && sibling->color == RED) {
                    sibling->color = BLACK;
                    parent->color = RED;
                    rotateRight(parent);
                    sibling = parent->left;
                }
                bool leftChildBlack = (sibling->left == nullptr || sibling->left->color == BLACK);
                bool rightChildBlack = (sibling->right == nullptr || sibling->right->color == BLACK);
                if (leftChildBlack && rightChildBlack) {
                    sibling->color = RED;
                    node = parent;
                    parent = node->parent;
                }
                else {
                    if (leftChildBlack) {
                        if (sibling->right != nullptr) sibling->right->color = BLACK;
                        sibling->color = RED;
                        rotateLeft(sibling);
                        sibling = parent->left;
                    }
                    sibling->color = parent->color;
                    parent->color = BLACK;
                    if (sibling->left != nullptr) sibling->left->color = BLACK;
                    rotateRight(parent);
                    node = root;
                }
            }
        }
        if (node != nullptr) node->color = BLACK;
    }

    void erase(Node* node) {
        if (node != nullptr) {
            erase(node->left);
            erase(node->right);
            delete node;
        }
    }

public:
    RedBlackTree() : root(nullptr) {}

    ~RedBlackTree() { clear(); }

    bool isEmpty() const { return root == nullptr; }

    std::expected<Node*, DataStructureError> find(const T& value) const {
        Node* current = root;
        while (current != nullptr) {
            if (value == current->data) return current;
            current = (value < current->data) ? current->left : current->right;
        }
        return std::unexpected(DataStructureError::ElementNotFound);
    }

    std::expected<T, DataStructureError> getMin() const {
        if (root == nullptr) return std::unexpected(DataStructureError::ContainerIsEmpty);
        Node* current = root;
        while (current->left != nullptr) current = current->left;
        return current->data;
    }

    std::expected<T, DataStructureError> getMax() const {
        if (root == nullptr) return std::unexpected(DataStructureError::ContainerIsEmpty);
        Node* current = root;
        while (current->right != nullptr) current = current->right;
        return current->data;
    }

    std::expected <void, DataStructureError> insert(const T& value) {
        Node* newNode = nullptr;
        if (root == nullptr) {
            root = new Node{value, nullptr, nullptr, nullptr, BLACK};
            return {};
        }
        Node* current = root;
        while (current != nullptr) {
            if (value < current->data) {
                if (current->left == nullptr) {
                    newNode = new Node{value, current, nullptr, nullptr, RED};
                    current->left = newNode;
                    break;
                }
                current = current->left;
            }
            else if (value > current->data) {
                if (current->right == nullptr) {
                    newNode = new Node{value, current, nullptr, nullptr, RED};
                    current->right = newNode;
                    break;
                }
                current = current->right;
            }
            else {
                return std::unexpected(DataStructureError::DuplicateValue);
            }
        }
        insertFixUp(newNode);
        return {};
    }
    
    std::expected<void, DataStructureError> remove(const T& value) {
        if (root == nullptr) return std::unexpected(DataStructureError::ContainerIsEmpty);
        TRY(target, find(value));
        Node* toDelete = target;
        if (target->left != nullptr && target->right != nullptr) {
            toDelete = target->right;
            while (toDelete->left != nullptr) toDelete = toDelete->left;
            target->data = toDelete->data;
        }
        Node* replacement = (toDelete->left != nullptr) ? toDelete->left : toDelete->right;
        Node* replacementParent = toDelete->parent;
        Color deletedColor = toDelete->color;
        if (replacement != nullptr) replacement->parent = toDelete->parent;
        if (toDelete->parent == nullptr) root = replacement;
        else if (toDelete == toDelete->parent->left) toDelete->parent->left = replacement;
        else toDelete->parent->right = replacement;
        delete toDelete;
        if (deletedColor == BLACK && (replacement != nullptr || replacementParent != nullptr)) removeFixUp(replacement, replacementParent);
        return {};
    }

    void clear() {
        erase(root);
        root = nullptr;
    }
};
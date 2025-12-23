#include <algorithm>
#include <stack>
#include <queue>
#include <functional>
#include "../error/error.hpp"

template<typename T>
class BinaryTree {
public:
    struct Node {
        T data;
        Node* parent;
        Node* left;
        Node* right;
    };

protected:
    Node* root;

public:
    BinaryTree() : root(nullptr) {}

    virtual ~BinaryTree() { clear(); }

    std::expected<void, DataStructureError> createRoot(const T& value) {
        if (root != nullptr) return std::unexpected(DataStructureError::ContainerIsFull);
        root = new Node{value, nullptr, nullptr, nullptr};
        return {};
    }

    bool isEmpty() const { return root == nullptr; }

    int getHeight(Node* node) const {
        if (node == nullptr) return 0;
        return std::max(getHeight(node->left), getHeight(node->right)) + 1;
    }

    std::expected<int, DataStructureError> getDepth(Node* node) const {
        if (node == nullptr) return std::unexpected(DataStructureError::ContainerIsEmpty);
        if (node->parent == nullptr) return 0;
        return getDepth(node->parent).value() + 1;
    }

    int countNodes(Node* node) const {
        if (node == nullptr) return 0;
        return countNodes(node->left) + countNodes(node->right) + 1;
    }

    int countLeaves(Node* node) const {
        if (node == nullptr) return 0;
        if (node->left == nullptr && node->right == nullptr) return 1;
        return countLeaves(node->left) + countLeaves(node->right);
    }

    //std::function<void(Node*)> visitor = [](auto* node) { std::cout << node->data << " "; };
    std::expected<void, DataStructureError> preorderRecursive(Node* node, std::function<void(Node*)> visitor) const {
        if (node == nullptr) return std::unexpected(DataStructureError::ContainerIsEmpty);
        visitor(node);
        if (node->left) preorderRecursive(node->left, visitor);
        if (node->right) preorderRecursive(node->right, visitor);
        return {};
    }

    std::expected<void, DataStructureError> inorderRecursive(Node* node, std::function<void(Node*)> visitor) const {
        if (node == nullptr) return std::unexpected(DataStructureError::ContainerIsEmpty);
        if (node->left) inorderRecursive(node->left, visitor);
        visitor(node);
        if (node->right) inorderRecursive(node->right, visitor);
        return {};
    }

    std::expected<void, DataStructureError> postorderRecursive(Node* node, std::function<void(Node*)> visitor) const {
        if (node == nullptr) return std::unexpected(DataStructureError::ContainerIsEmpty);
        if (node->left) postorderRecursive(node->left, visitor);
        if (node->right) postorderRecursive(node->right, visitor);
        visitor(node);
        return {};
    }

    std::expected<void, DataStructureError> preorderIterative(Node* node, std::function<void(Node*)> visitor) const {
        if (node == nullptr) return std::unexpected(DataStructureError::ContainerIsEmpty);
        std::stack<Node*> stack;
        stack.push(node);
        while (!stack.empty()) {
            Node* current = stack.top();
            stack.pop();
            visitor(current);
            if (current->right) stack.push(current->right);
            if (current->left) stack.push(current->left);
        }
        return {};
    }

    std::expected<void, DataStructureError> inorderIterative(Node* node, std::function<void(Node*)> visitor) const {
        if (node == nullptr) return std::unexpected(DataStructureError::ContainerIsEmpty);
        std::stack<Node*> stack;
        Node* current = node;
        while (current != nullptr || !stack.empty()) {
            while (current != nullptr) {
                stack.push(current);
                current = current->left;
            }
            current = stack.top();
            stack.pop();
            visitor(current);
            current = current->right;
        }
        return {};
    }

    std::expected<void, DataStructureError> postorderIterative(Node* node, std::function<void(Node*)> visitor) const {
        if (node == nullptr) return std::unexpected(DataStructureError::ContainerIsEmpty);
        std::stack<Node*> stack;
        Node* current = node;
        Node* lastVisited = nullptr;
        while (current != nullptr || !stack.empty()) {
            if (current != nullptr) {
                stack.push(current);
                current = current->left;
            } 
            else {
                Node* peekNode = stack.top();
                if (peekNode->right != nullptr && lastVisited != peekNode->right) {
                    current = peekNode->right;
                } 
                else {
                    visitor(peekNode);
                    lastVisited = stack.top();
                    stack.pop();
                }
            }
        }
        return {};
    }

    std::expected<void, DataStructureError> levelorder(std::function<void(Node*)> visitor) const {
        if (root == nullptr ) return std::unexpected(DataStructureError::ContainerIsEmpty);
        std::queue<Node*> queue;
        queue.push(root);
        while (!queue.empty()) {
            Node* current = queue.front();
            queue.pop();
            visitor(current);
            if (current->left) queue.push(current->left);
            if (current->right) queue.push(current->right);
        }
        return {};
    }

    std::expected<void, DataStructureError> insertLeft(Node* parent, const T& value) {
        if (parent == nullptr) return std::unexpected(DataStructureError::InvalidArgument);
        if (parent->left != nullptr) return std::unexpected(DataStructureError::ContainerIsFull);
        parent->left = new Node{value, parent, nullptr, nullptr};
        return {};
    }

    std::expected<void, DataStructureError> insertRight(Node* parent, const T& value) {
        if (parent == nullptr) return std::unexpected(DataStructureError::InvalidArgument);
        if (parent->right != nullptr) return std::unexpected(DataStructureError::ContainerIsFull);
        parent->right = new Node{value, parent, nullptr, nullptr};
        return {};
    }

    std::expected<void, DataStructureError> betweenLeft(Node* parent, const T& value) {
        if (parent == nullptr) return std::unexpected(DataStructureError::InvalidArgument);
        if (parent->left == nullptr) return std::unexpected(DataStructureError::ContainerIsEmpty);
        Node* newNode = new Node{value, parent, parent->left, nullptr};
        parent->left->parent = newNode;
        parent->left = newNode;
        return {};
    }

    std::expected<void, DataStructureError> betweenRight(Node* parent, const T& value) {
        if (parent == nullptr) return std::unexpected(DataStructureError::InvalidArgument);
        if (parent->right == nullptr) return std::unexpected(DataStructureError::ContainerIsEmpty);
        Node* newNode = new Node{value, parent, parent->right, nullptr};
        parent->right->parent = newNode;
        parent->right = newNode;
        return {};
    }

    std::expected<T, DataStructureError> get(Node* node) const {
        if (node == nullptr) return std::unexpected(DataStructureError::ContainerIsEmpty);
        return node->data;
    }

    std::expected<T, DataStructureError> getLeft(Node* node) const {
        if (node == nullptr) return std::unexpected(DataStructureError::ContainerIsEmpty);
        if (node->left == nullptr) return std::unexpected(DataStructureError::ContainerIsEmpty);
        return node->left->data;
    }

    std::expected<Node*, DataStructureError> getLeftNode(Node* node) const {
        if (node == nullptr) return std::unexpected(DataStructureError::ContainerIsEmpty);
        if (node->left == nullptr) return std::unexpected(DataStructureError::ContainerIsEmpty);
        return node->left;
    }

    std::expected<T, DataStructureError> getRight(Node* node) const {
        if (node == nullptr) return std::unexpected(DataStructureError::ContainerIsEmpty);
        if (node->right == nullptr) return std::unexpected(DataStructureError::ContainerIsEmpty);
        return node->right->data;
    }

    std::expected<Node*, DataStructureError> getRightNode(Node* node) const {
        if (node == nullptr) return std::unexpected(DataStructureError::ContainerIsEmpty);
        if (node->right == nullptr) return std::unexpected(DataStructureError::ContainerIsEmpty);
        return node->right;
    }

    std::expected<T, DataStructureError> getParent(Node* node) const {
        if (node == nullptr) return std::unexpected(DataStructureError::ContainerIsEmpty);
        if (node->parent == nullptr) return std::unexpected(DataStructureError::ContainerIsEmpty);
        return node->parent->data;
    }

    std::expected<Node*, DataStructureError> getParentNode(Node* node) const {
        if (node == nullptr) return std::unexpected(DataStructureError::ContainerIsEmpty);
        if (node->parent == nullptr) return std::unexpected(DataStructureError::ContainerIsEmpty);
        return node->parent;
    }

    std::expected<T, DataStructureError> getRoot() const {
        return get(root);
    }

    std::expected<Node*, DataStructureError> getRootNode() const {
        if (root == nullptr) return std::unexpected(DataStructureError::ContainerIsEmpty);
        return root;
    }

    std::expected<Node*, DataStructureError> find(const T& value) const {
        if (root == nullptr) return std::unexpected(DataStructureError::ContainerIsEmpty);
        if (root->data == value) return root;
        auto leftNode = find(root->left, value);
        return leftNode.has_value() ? leftNode : find(root->right, value);
    }

    void erase(Node* node) {
        if (node != nullptr) {
            erase(node->left);
            erase(node->right);
            delete node;
        }
    }

    std::expected<void, DataStructureError> eraseLeft(Node* parent) {
        erase(parent->left);
        parent->left = nullptr;
        return {};
    }
    
    std::expected<void, DataStructureError> eraseRight(Node* parent) {
        erase(parent->right);
        parent->right = nullptr;
        return {};
    }

    std::expected<T, DataStructureError> update(Node* node, const T& newValue) {
        if (node == nullptr) return std::unexpected(DataStructureError::ContainerIsEmpty);
        T value = node->data;
        node->data = newValue;
        return value;
    }

    bool isEqual(Node* node1, Node* node2) const {
        if (node1 == nullptr && node2 == nullptr) return true;
        if (node1 == nullptr || node2 == nullptr) return false;
        if (node1->data != node2->data) return false;
        return isEqual(node1->left, node2->left) && isEqual(node1->right, node2->right);
    }

    std::expected<bool, DataStructureError> isCompleteTree() const {
        if (root == nullptr) return std::unexpected(DataStructureError::ContainerIsEmpty);
        std::queue<Node*> queue;
        queue.push(root);
        bool foundNull = false;
        while(!queue.empty()) {
            Node* current = queue.front();
            queue.pop();
            if (current == nullptr) foundNull = true;
            else {
                if (foundNull) return false;
                queue.push(current->left);
                queue.push(current->right);
            }
        }
        return true;
    }

    std::expected<bool, DataStructureError> isFullTree(Node* node = nullptr) const {
        if (node == nullptr) {
            if (root == nullptr ) return std::unexpected(DataStructureError::ContainerIsEmpty);
            node = root;
        }
        if (node->left == nullptr && node->right == nullptr) return true;
        if (node->left == nullptr || node->right == nullptr) return false;
        return isFullTree(node->left).value() && isFullTree(node->right).value();
    }

    std::expected<bool, DataStructureError> isBalanced(Node* node = nullptr) const {
        if (node == nullptr) {
            if (root == nullptr) return std::unexpected(DataStructureError::ContainerIsEmpty);
            node = root;
        }
        if (node->left == nullptr && node->right == nullptr) return true;
        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);
        if (std::abs(leftHeight - rightHeight) > 1) return false;
        return isBalanced(node->left).value() && isBalanced(node->right).value();
    }

    void clear() {
        erase(root);
        root = nullptr;
    }
};
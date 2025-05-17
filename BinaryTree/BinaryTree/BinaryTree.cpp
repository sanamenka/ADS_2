#include <cstdlib>
#include <ctime>

class BinaryTree {
public:
	struct Node {
		int key;
		Node* left{ nullptr };
		Node* right{ nullptr };
		Node(int key = 0, Node* left = nullptr, Node* right = nullptr) : key(key), left(left), right(right) {}
		~Node() = default;
	};
private:
	Node* root{ nullptr };

	Node* copyTree(const Node* otherRoot) {
		if (otherRoot == nullptr)
			return nullptr;
		Node* newNode = new Node(otherRoot->key);
		newNode->left = copyTree(otherRoot->left);
		newNode->right = copyTree(otherRoot->right);
		return newNode;
	}
	
	void deleteTree(Node* node) {
		if (node) {
			deleteTree(node->left);
			deleteTree(node->right);
			delete node;
		}
	}

	Node* addNodeRandom(Node* node, int key) {
		if (node == nullptr)
			return new Node(key);
		if (std::rand() % 2 == 0)
			node->left = addNodeRandom(node->left, key);
		else
			node->right = addNodeRandom(node->right, key);
		return node;
	}

public:
	BinaryTree() = default;

	BinaryTree(const BinaryTree& other) {
		copyTree(other.root);
	}

	~BinaryTree() {
		deleteTree(root);
	}

	Node* getRoot() const {
		return root;
	}

	bool isEmpty() const {
		if (root == nullptr)
			return true;
		return false;
	}
	
	int countNodes(const Node* node) {
		if (node == nullptr)
			return 0;
		return 1 + countNodes(node->left) + countNodes(node->right);
	}

	void insertRandom(int key) {
		root = addNodeRandom(root, key);
	}
};

class SearchTree : BinaryTree {

};

int main() {
	BinaryTree mTree;
	mTree.insertRandom(10);

	return 0;
}
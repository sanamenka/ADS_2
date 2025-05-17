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
protected:

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

	Node* nlrSearch(Node* node, int key) const {
		if (!node || node->key == key)
			return node;
		Node* searchResult = nlrSearch(node->left, key);
		if (!searchResult)
			searchResult = nlrSearch(node->right, key);
		return searchResult;
	}

	Node* deleteNode(Node* node, int key) {
		if (!node || node->key == key)
			return node;
		Node* searchResult = nlrSearch(node->left, key);
		if (!searchResult)
			searchResult = nlrSearch(node->right, key);

		if (searchResult->key == key) {
			Node* rnode = rSearch(searchResult);
			if (!rnode)
				
			if (searchResult == node->left) {
				rnode->left = node->left->left;
				rnode->right = node->left->right;
				delete node->left;
				node->left = rnode;
			}
			if (searchResult == node->right) {
				rnode->left = node->right->left;
				rnode->right = node->right->right;
				delete node->right;
				node->right = rnode;
			}
		}
		return searchResult;
	}

	Node* rSearch(Node* node) const {
		if (!node)
			return node;
		Node* searchResult = rSearch(node->right);
		if (!searchResult)
			searchResult = rSearch(node->left);
		if (!searchResult) {
			return node;
		}
		if (searchResult == node->right)
			node->right = nullptr;
		if (searchResult == node->left)
			node->left = nullptr;
		return searchResult;
	}

public:
	BinaryTree() = default;

	BinaryTree(const BinaryTree& other) {
		root = copyTree(other.root);
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

	virtual void insert(int key) {
		root = addNodeRandom(root, key);
	}

	virtual bool deleteNode(int key) {
		return deleteNode(root, key);
	}

	virtual Node* searchNode(int key) const {
		return nlrSearch(root, key);
	}


};

class SearchTree : public BinaryTree {

};

int main() {
	BinaryTree mTree;
	mTree.insert(10);
	return 0;
}
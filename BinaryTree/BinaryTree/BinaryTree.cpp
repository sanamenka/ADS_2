#include <cstdlib>
#include <ctime>
#include <iostream>


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

	Node* leafSearch(Node* node) const {
		if (!node)
			return node;
		if (!node->left && !node->right)
			return node;
		Node* searchResult = leafSearch(node->right);
		if (searchResult)
			return searchResult;
		return leafSearch(node->left);
	}

	Node* parentSearch(Node* node, Node* fnode) const {
		if (fnode == root)
			return nullptr;
		if (!node)
			return node;
		if (fnode == node->left || fnode == node->right)
			return node;
		Node* searchResult = parentSearch(node->right, fnode);
		if (searchResult)
			return searchResult;
		return parentSearch(node->left, fnode);
	}

	Node* deleteNode(Node* node, int key) {
		if (!node) {
			return nullptr;
		}
		
		if (node->key == key) {
			if (!node->left && !node->right) {
				delete node;
				return nullptr;
			}

			if (!node->left) {
				Node* temp = node->right;
				Node* parent = parentSearch(root, node);
				delete node;
				if (!parent) {
					root = temp;
					return temp;
				}
				parent->right = temp;
				return temp;
			}

			if (!node->right) {
				Node* temp = node->left;
				Node* parent = parentSearch(root, node);
				delete node;
				if (!parent) {
					root = temp;
					return temp;
				}
				parent->left = temp;
				return temp;
			}
			
			Node* temp = leafSearch(node);
			Node* parentTemp = parentSearch(root, temp);
			if (parentTemp->left == temp)
				parentTemp->left = nullptr;
			else
				parentTemp->right = nullptr;
			if (node != root) {
				Node* parent = parentSearch(root, node);
				if (parent->left == node) {
					parent->left = temp;
				}
				else
					parent->right = temp;
				temp->left = node->left;
				temp->right = node->right;
				delete node;
				return temp;
			}
			temp->left = node->left;
			temp->right = node->right;
			root = temp;
			delete node;
			return temp;
			
		}
		Node* searchResult = deleteNode(node->right, key);
		if (searchResult)
			return searchResult;
		searchResult = deleteNode(node->left, key);
	}

	void printTree(Node* node, int depth = 0) const {
		if (!node)
			return;
		printTree(node->right, depth + 1);
		std::cout << std::string(depth * 4, ' ') << node->key << std::endl;
		printTree(node->left, depth + 1);
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
		if (isEmpty()) {
			return false;
		}
		if (deleteNode(root, key) == nullptr)
			return false;
		return true;
	}

	virtual Node* searchNode(int key) const {
		return nlrSearch(root, key);
	}

	void print() const {
		printTree(root);
	}

};

class SearchTree : public BinaryTree {

};

int main() {
	BinaryTree mTree;
	mTree.insert(10);
	mTree.insert(20);
	mTree.insert(14);
	mTree.insert(44);
	mTree.insert(54);
	mTree.insert(55);
	mTree.insert(56);
	mTree.insert(57);
	mTree.print();
	std::cout << "--------------------------------------------------------------------------" << std::endl;
	std::cout << mTree.deleteNode(30) << std::endl;
	std::cout << mTree.deleteNode(10) << std::endl;
	std::cout << "--------------------------------------------------------------------------" << std::endl;
	mTree.print();
	return 0;
}
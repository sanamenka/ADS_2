
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

public:
	BinaryTree() = default;

	BinaryTree(const BinaryTree& other) {
		copyTree(other.root);
	}

	~BinaryTree() {
		deleteTree(root);
	}

};

class SearchTree : BinaryTree {

};
#include <iostream>

struct Node 
{
	int value;
	int height;

	Node* right;
	Node* left;
};

int maxHeight(Node* first, Node* second);

class AVLTree 
{
public:

	Node* root = NULL;

	int height(Node* node) {
		if (node == nullptr) {
			return 0;
		}
		else {
			return node->height;
		}
	}

	int getBalance(Node* node) {
		if (node == nullptr) {
			return 0;
		}
		else {
			return height(node->left) - height(node->right);
		}
	}

	Node* rightRotate(Node* node) {
		
		Node* leftNode = node->left;
		Node* temp = leftNode->right;

		leftNode->right = node;
		node->left = temp;

		node->height = maxHeight(node->left, node->right) + 1;
		leftNode->height = maxHeight(leftNode->left, leftNode->right) + 1;

		return leftNode;
	}

	Node* leftRotate(Node* node) {

		Node* rightNode = node->right;
		Node* temp = rightNode->left;

		rightNode->left = node;
		node->right = temp;

		node->height = maxHeight(node->left, node->right) + 1;
		rightNode->height = maxHeight(rightNode->left, rightNode->right) + 1;

		return rightNode;
	}

	Node* insert(Node* root, int value) {

		if (root == nullptr) {
			Node* newNode = new Node;
			newNode->value = value;
			newNode->height = 0;
			newNode->left = nullptr;
			newNode->right = nullptr;
			return newNode;
		}
		if (root->value < value) {
			root->left = insert(root->left, value);
		}
		else if (root->value > value) {
			root->right = insert(root->right, value);
		}
		else {
			return root;
		}

		root->height = maxHeight(root->left, root->right) + 1;

		int balance = getBalance(root);

		//L-L
		if (balance > 1 && getBalance(root->left) >= 0) {
			return rightRotate(root);
		}
		//R-R
		if (balance < -1 && getBalance(root->right) <= 0) {
			return leftRotate(root);
		}
		//L-R
		if (balance > 1 && getBalance(root->left) < 0) {
			root->left = leftRotate(root->left);
			return rightRotate(root);
		}
		//R-L
		if (balance < -1 && getBalance(root->right) > 0) {
			root->right = rightRotate(root->right);
			return rightRotate(root);
		}
		return root;
	}

	void inOrderTraversal(Node* root) {
		if (root != nullptr) {
			inOrderTraversal(root->left);
			std::cout << root->value << ", ";
			inOrderTraversal(root->right);
		}
	}
};

int maxHeight(Node* first, Node* second) 
{
	int firstHeight = (first != nullptr) ? first->height : 0;
	int secondHeight = (second != nullptr) ? second->height : 0;
	return (firstHeight > secondHeight) ? firstHeight : secondHeight;
}

int main()
{
	AVLTree tree;
	int values[] = { 40, 50, 60, 20, 30, 36, 25, 10, 5 };

	for (int value : values) {
		tree.root = tree.insert(tree.root, value);
	}
	tree.inOrderTraversal(tree.root);

	std::cout << std::endl;

	tree.root = tree.insert(tree.root, 27);
	tree.inOrderTraversal(tree.root);

	return 0;
}

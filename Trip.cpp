#include <iostream>

typedef int KeyType;
using namespace std;

struct Node {
	KeyType key;

	int priority, size;

	Node *left, *right;

	Node(const KeyType& _key) : key(_key), priority(rand()), size(1), left(nullptr), right(nullptr) {}

	void setLeft(Node* newLeft) { left = newLeft; calcSize(); }
	void setRight(Node* newRight) { right = newRight; calcSize(); }

	void calcSize() {
		size = 1;
		if (left != nullptr) size += left->size;
		if (right != nullptr) size += right->size;
	}
};

pair<Node*, Node*> split(Node* root, KeyType key)
{
	if (root->key < key) {
		Node* lbdToKey = root;
		while (true) {
			// ���� �߰� => root ���� ��� ���Ұ� key ���� �۴�.
			if (lbdToKey->right == nullptr) return make_pair(lbdToKey, nullptr);
			
			// ����ؼ� �۴� => ���������� �����Ѵ�.
			if (lbdToKey->right->key < key) lbdToKey = lbdToKey->right;
			// right���� Ŀ���� => ���⼭ �ڸ���.
			else
			{
				Node* rightRetVal = lbdToKey->right;
				lbdToKey->setRight(nullptr);
				return make_pair(lbdToKey, rightRetVal);
			}
		}
	}
	else
	{ 
		Node* ubdToKey = root;
		while (true) {
			// ���� �߰� => root ���� ��� ���Ұ� key ���� ũ��.
			if (ubdToKey->left == nullptr) return make_pair(nullptr, ubdToKey);

			// ����ؼ� �۴� => ���������� �����Ѵ�.
			if (ubdToKey->left->key > key) ubdToKey = ubdToKey->left;
			// right���� �۾����� => ���⼭ �ڸ���.
			else
			{
				Node* leftRetVal = ubdToKey->left;
				ubdToKey->setLeft(nullptr);
				return make_pair(leftRetVal, ubdToKey);
			}
		}
	}
}

Node* insert(Node* root, Node* node) {
	if (root == nullptr) return node;

	// node�� priority �� �� ���� => node�� root ���� �ö󰣴�.
	if (node->priority > root->priority) {
		if (node->key > root->key)	node->setLeft(root);
		else node->setRight(root);
		
		return node;
	}
	// node�� priority�� �� ���� ==> root �Ʒ��� node�� �ִ´�.
	else if (node->priority < root->priority)
	{
		
	}
	else
	{
		return root;
	}
}
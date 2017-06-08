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
			// 끝을 발견 => root 내의 모든 원소가 key 보다 작다.
			if (lbdToKey->right == nullptr) return make_pair(lbdToKey, nullptr);
			
			// 계속해서 작다 => 오른쪽으로 갱신한다.
			if (lbdToKey->right->key < key) lbdToKey = lbdToKey->right;
			// right에서 커진다 => 여기서 자른다.
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
			// 끝을 발견 => root 내의 모든 원소가 key 보다 크다.
			if (ubdToKey->left == nullptr) return make_pair(nullptr, ubdToKey);

			// 계속해서 작다 => 오른쪽으로 갱신한다.
			if (ubdToKey->left->key > key) ubdToKey = ubdToKey->left;
			// right에서 작아진다 => 여기서 자른다.
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

	// node의 priority 가 더 높다 => node가 root 위에 올라간다.
	if (node->priority > root->priority) {
		if (node->key > root->key)	node->setLeft(root);
		else node->setRight(root);
		
		return node;
	}
	// node의 priority가 더 낮다 ==> root 아래에 node를 넣는다.
	else if (node->priority < root->priority)
	{
		
	}
	else
	{
		return root;
	}
}
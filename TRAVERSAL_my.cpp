#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;
#define MIN(x, y)	((x) > (y) ? (y) : (x))
#define MAX(x, y)	((x) > (y) ? (x) : (y))
#define nextl '\n'

int numNode;
vector<int> preorder, inorder;

class MyTree
{
private:
	MyTree();
public:
	int num;
	MyTree* head, *left, *right;
	MyTree(int num) : num(num), head(nullptr), left(nullptr), right(nullptr) {}
	~MyTree() {};
	void connectLeft(MyTree& left);
	void connectRight(MyTree& right);
	void preorder();
	void inorder();
	void postorder();
};

int main()
{
	ios_base::sync_with_stdio(false);

	int numCase;
	cin >> numCase;


	while (numCase--)
	{
		cin >> numNode;
		preorder.resize(numNode, 0);
		inorder.resize(numNode, 0);
		for (int i = 0; i < numNode; i++)
		{
			cin >> preorder[i];
		}
		for (int i = 0; i < numNode; i++)
		{
			cin >> inorder[i];
		}

		
	}


#if 0
	MyTree a(27), b(16), c(54), d(9), e(36), f(72), g(12);

	a.connectLeft(b);
	a.connectRight(c);
	b.connectLeft(d);
	d.connectRight(g);
	c.connectLeft(e);
	c.connectRight(f);

	a.preorder();
	cout << nextl << nextl;
	a.inorder();
	cout << nextl << nextl;
	a.postorder();
	cout << nextl << nextl;
#endif
	return 0;
}


void MyTree::connectLeft(MyTree& left)
{
	assert(this->left == nullptr && left.head == nullptr);
	this->left = &left;
	left.head = this;
}

void MyTree::connectRight(MyTree& right)
{
	assert(this->right == nullptr && right.head == nullptr);
	this->right = &right;
	right.head = this;
}

void MyTree::preorder()
{
	cout << num << ' ';
	if (left != nullptr)
		left->preorder();
	if (right != nullptr)
		right->preorder();
}

void MyTree::inorder()
{
	if (left != nullptr)
		left->inorder();
	cout << num << ' ';
	if (right != nullptr)
		right->inorder();
}

void MyTree::postorder()
{
	if (left != nullptr)
		left->postorder();
	if (right != nullptr)
		right->postorder();
	cout << num << ' ';
}

#include<iostream>
#include<string>
#include<fstream>
using namespace std;
typedef struct node
{
	int val;
	int pr;
	node *left;
	node *right;
}node;
typedef node* pointer;
void div(pointer tree, int x, pointer &levo, pointer &pravo)
{
	if (!tree)
		pravo = levo = NULL;
	else
		if (x < tree->val)
		{
			div(tree->left, x, levo, tree->left);
			pravo = tree;
		}
		else
		{
			div(tree->right, x, tree->right, pravo);
			levo = tree;
		}
}
void push(pointer &tree,pointer newel)
{
	if (!tree)
		tree = newel;
	else
		if (newel->pr > tree->pr)
		{
			div(tree, newel->val, newel->right, newel->left);
			tree = newel;
		}
		else
			push(tree->val > newel->val ? tree->left : tree->right, newel);
}
void add(int x, pointer &tree)
{
	pointer newel = makenode(x, NULL, NULL);
	push(tree, newel);
}
void merge(pointer &tree, pointer levo, pointer pravo)
{
	if (!levo || !pravo)
		tree = levo ? levo : pravo;
	else
		if (levo->pr > pravo->pr)
			merge(levo->right, levo->right, pravo),pravo=tree;
		else
			merge(pravo->left, levo, pravo->left),levo=tree;
}
int del(int x, pointer &tree)
{
	if (tree->val == x)
		merge(tree, tree->left, tree->right);
	else
		del(x, x < tree->val ? tree->left : tree->right);
}
node* makenode(int x, node* left, node* right)
{
	node *n = new node;
	n->val = x;
	n->left = left;
	n->right = right;
	n->pr = rand();
}
bool exist(int x, pointer tree)
{
	if (!tree)
		return false;
	if (tree->val == x)
		return true;
	if (x > tree->val)
		return exist(x, tree->right);
	else
		return exist(x, tree->left);
}
int next(int x, pointer tree)
{
	int result;
	if (!tree)
		return NULL;
	if (x <= tree->val)
		return next(x, tree->left);
	result = next(x, tree->left);
	if (result == false || tree->val > result)
		return tree->val;
}
long prev(pointer tree, long x) {
	if (!tree)
		return NULL;
	if (tree->val >= x) return prev(tree->left, x);
	long res = prev(tree->right, x);
	if (tree->val > res || res == NULL) res = tree->val;
	return res;
}
int main()
{
	ifstream fin("bst.in");
	ofstream fout("bst.out");
	int x;
	string z;
	pointer tree = NULL;
	while (getline(fin, z))
	{
		fin >> z >> x;
		if (z=="insert")
		{
			if (!tree)
				makenode(x, NULL, NULL);
			if (!exist(x, tree))
				add(x, tree);
		}
		if (z == "delete")
		{
			if (exist(x, tree))
				del(x, tree);
		}
		if (z == "exists")
		{
			cout << exist(x, tree);
		}
		if (z == "next")
		{
			int result= next(x, tree);
			if (!result)
				cout << "none"<<endl;
			else
				cout << "res" << endl;
		}
		if (z=="prev")
		{
			int result = prev(x, tree);
			if (!result)
				cout << "none"<<endl;
			else
				cout << result<<endl;
		}
	}
	cin.get();
	return 0;
}
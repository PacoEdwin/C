#include <iostream>
#include <vector>
#include <utility>
#include <memory>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

struct BTree
{
	BTree(int t);
	BTree(const BTree&);
	BTree() = default;
	int n;
	int t;
	BTree* root;
	vector<BTree*> c;
	vector<int> key;
	bool leaf;

	BTree* New();
};

BTree::BTree(int t)
{
	this->t = t;
	c.reserve(2 * t);
	key.reserve(2 * t - 1);
}

BTree::BTree(const BTree& r)
{
	t = r.t;
	this->root = r.root;
	c.reserve(2 * r.t);
	key.reserve(2 * r.t - 1);
}

BTree* BTree::New()
{
	return new BTree(*this);
}

pair<BTree*, int> BTreeSearch(BTree *x, int k)
{
	int i = 0;
	while (i < x->n && x->key[i] < k)
		i++;

	if (i < x->n && k == x->key[i])
		return { x, i };
	else
		if (x->leaf)
			return {};
		else
			return BTreeSearch(x->c[i], k);
}

BTree* BTreeCtreate(int t)
{
	if (t < 2)
		throw std::logic_error("B-tree allowed with t >= 2 only! You dumb fuck.");

	BTree* n = new BTree(t);
	n->root = n;
	n->leaf = true;
	n->n = 0;
	return n;
}
// x is splitting node
void splitChild(BTree* x, int i)
{
	// create new array where we will move t-1 nodes
	BTree* z = new BTree(*x);
	// ith child of x
	BTree* y = x->c[i];
	z->leaf = y->leaf;
	z->n = z->t - 1;
	// copy right t-1 to new array
	for (int j = 0; j < z->t - 1; j++)
		z->key.push_back(y->key[j + y->t]);
	// if not leaf copy all shit
	if (!y->leaf)
		for (int j = 0; j < z->t; j++)
			z->c.push_back(y->c[j + y->t]);
	// decrease size to least allowed (t-1) for those who doesn't read books
	y->n = y->t - 1;
	x->c.resize(x->c.size() + 1);
	for (int j = x->n; j >= i + 1; j--)
		x->c[j + 1] = x->c[j];
	x->c[i+1] = z;

	x->key.resize(x->key.size() + 1);
	for (int j = x->n - 1; j >= i; j--)
		x->key[j + 1] = x->key[j];
	x->key[i] = y->key[y->t - 1];
	x->n++;
	// decrease size
	y->key.resize(y->n);
	y->c.resize(y->n + 1);
}

// different name of node again?
// Well it is my implementation go fuck yourself
void insertNonFull(BTree* v, int k)
{
	int i = v->n - 1;
	if (v->leaf)
	{
		v->key.resize(v->n + 1);
		while (i >= 0 && k < v->key[i])
		{
			v->key[i + 1] = v->key[i];
			i--;
		}
		v->key[i + 1] = k;
		v->n++;
	}
	else
	{
		while (i >= 0 && k < v->key[i])
			i--;
		i++;
		if (v->c[i]->n == 2 * v->t - 1)
		{
			splitChild(v, i);
			if (k > v->key[i])
				i++;
		}
		insertNonFull(v->c[i], k);
	}
}

void insert(BTree* T, int k)
{
	auto r = T->root;
	if (r->n == r->t * 2 - 1)
	{
		auto s = new BTree(*r);
		T->root = s;
		s->root = s;
		r->root = s;
		s->leaf = false;
		s->n = 0;
		s->c.push_back(r);
		splitChild(s, 0);
		insertNonFull(s, k);
	}
	else
		insertNonFull(r, k);
}

// I assume search of elements can be improved up to O(log(t)*log_t(n)) by using binry search
// now it takes O(t*log_t(n))
// Insertion probably as well. The only problem is insertion inf hte middle of the vector of new elemnt.
// QList by qt doc can erase and insert by O(1), ergo by bin search we can decrease insert to O(log(t)*log_t(n)
// But I'm lazy so implement it yourself.

// Oh, yeah almost forgat.
// Fuck you.
// kidding.
// You could use templates to introduce btree for floats here.
// Lazy, sorry.

// P.s
// This code is just implemetation of btree. It is not trimmed and I could do lots of improvements on it. But i probably won't)
int main()
{
	cout << "Enter number of elements" << endl;
	int n, v;
	cin >> n;
	cout << "Enter t >= 2 stuff(forgot the notation)" << endl;
	cin >> v;
	
	try
	{
		BTree* t = BTreeCtreate(v);
		vector<int> r(n);
		// insert elements
		{
			auto start = chrono::steady_clock::now();
			for (int i = 0; i < n; i++)
			{
				int x = rand() - (RAND_MAX / 2);
				r[i] = x;
				// insert key into the tree
				insert(t->root, x);
			}
			auto end = chrono::steady_clock::now();
			auto diff = end - start;
			cout << "Insertion of " << n << " elements took "
				<< chrono::duration <double, milli>(diff).count() << " ms" << endl;
		}

		// check
		{
			auto start = chrono::steady_clock::now();

			for (int i = 0; i < n; i++)
			{
				int ind = rand() % r.size();
				auto ans = BTreeSearch(t->root->root, r[ind]);
				if (ans.first->key[ans.second] != r[ind])
				{
					cout << "Well, I've fucked up somewhere. My answer: " << ans.first->key[ans.second] << " Number should be outputed: " << r[ind] << endl;
					system("pause");
					return 0;
				}
			}

			auto end = chrono::steady_clock::now();
			auto diff = end - start;
			cout << "Check of " << n << " elements took "
				<< chrono::duration <double, milli>(diff).count() << " ms" << endl;
		}
		cout << "OK" << endl;
	}
	catch (std::exception &e)
	{
		cout << e.what() << endl;
	}

	system("pause");
	return 0;
}
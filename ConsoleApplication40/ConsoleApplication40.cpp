#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <locale.h>
using namespace std;



class Node
{
	int key;
	Node* l; Node* r;
public: 
	Node(int size = 0, Node* left = NULL, Node* right = NULL)
  {
	key = size; l = left; r = right;
  };
	friend class Ftree;
	
};

struct elem
{
	Node* p;
	elem* next;
};

class Ftree
{
	Node* root;
public:
	Ftree() { root = NULL;}
	Ftree(int n);
	Ftree(const Ftree&);
	~Ftree();
	void ADD(int k);
	Node* copy(Node* a);
	void des(Node* root);
	void Print(Node* a, int k);
	Node* Root();
	void operator= (const Ftree&);
	Node* find(int k);
	int min();
	int max();
	void Befdel(Node*);
	Node* Delete(Node* q);
	int RLR (int* a);
	void RLR (Node* q, int* a, int& kol);
	void levels();
	
};



Ftree::Ftree(int n)
{
	if (n == 0) root = NULL;
	else {
		Node* q = new Node(rand() % 100);
		root = q; n--;
		while (n > 0)
		{
			int k = rand() % 100;
	
			ADD(k);
			n--;
		}
	}
	
}

void Ftree::ADD(int k)
{
	Node *q1 = root;
	Node* pred = new Node;
	while (q1!=NULL)
	{
		pred = q1;
		if (k<q1->key) q1 = q1->l;
		else q1 = q1->r;
	}
	
	if ( k<pred->key ) pred->l = new Node(k);
	else pred->r = new Node(k);
}

Ftree::Ftree(const Ftree& a)
{
	if (a.root == NULL) root = NULL;
	else 
	{
		root = new Node(a.root->key);
		root->l = copy(a.root->l);
		root->r = copy(a.root->r);

	}

}

Node* Ftree::copy(Node* a)
{
	if (a == NULL) return NULL;
	else 
	{
		Node* q = new Node(a->key);
		q->l = copy(a->l);
		q->r = copy(a->r);
		return q;
	}
}

Ftree::~Ftree()
{
	des(root);
}

void Ftree::des(Node* subroot)
{
	if (root)
	{
	
		if (subroot->l) des(subroot->l);
		if (subroot->r) des(subroot->r);
		delete subroot;
	}
}


void Ftree::Print(Node* a, int k)
{
	if (a == NULL) return;
	Print(a->r, k + 2);
	for (int i = 0; i < k; i++) cout << ' ';
	cout.width(2);
	cout << a->key << endl;
	Print(a->l, k + 2);

}

Node* Ftree::Root()
{
	return (root);
}

void Ftree::operator= (const Ftree& b)
{
	des(root);
	if (b.root == NULL) root = NULL;
	else 
	{
		root = new Node(b.root->key);
		root->l = copy(b.root->l);
		root->r = copy(b.root->r);
	}
}

Node* Ftree::find(int k)
{
	Node* q1 = root;
	while (q1 && q1->key != k)
	{
		if (k < q1->key) q1 = q1->l;
		else q1 = q1->r;
	}
	return q1;

}

int Ftree::min()
{   
	if (root == NULL) return NULL;
	Node* q1 = root;
	while (q1->l)
		q1 = q1->l;
	return q1->key;
}

int Ftree::max()
{
	if (root == NULL) return NULL;
	Node* q1 = root;
	while (q1->r )
		q1 = q1->r;
	return q1->key;
}

void Ftree::Befdel(Node* q1)
{
	Node* tmp = root;
	if (q1 == NULL) return;
	if (root == q1) { root = (*this).Delete(q1); return;}
	while (tmp->l != q1 && tmp->r != q1)
	{
		if (q1->key < tmp->key) tmp = tmp->l;
		else tmp = tmp->r;
	}
	
	if (tmp->l == q1) tmp->l = (*this).Delete(q1);
	else tmp->r = (*this).Delete(q1);
}

Node* Ftree::Delete(Node* q1)
{
	
	Node* d, *s, *r1;
	if (q1->r == NULL)
	{
		d = q1; q1 = q1->l;
		delete d; return q1;
	}
	if (q1->l == NULL)
	{
		
		d = q1; q1 = q1->r;
		delete d; return q1;
	}
	
	s = q1->r;
	if (s->l == NULL)
	{
		q1->key = s->key; 
		q1->r = s->r;
	}

	else
	{
		r1 = s;
		while (s->l != NULL)
		{
			r1 = s;
			s = s->l;
		}
		q1->key = s->key; 
		r1->l = s->r;
	}

	return(q1);
}

int Ftree::RLR (int* a)
{
	int kol = 0;
	RLR(root, a, kol);
	return kol;
}


void Ftree::RLR(Node* q, int* a, int& k)
{
	if (q == NULL) return;
	a[k++] = q->key;
	RLR(q->l, a, k);
	RLR(q->r, a, k);
	
}

void Ftree::levels()
{
	elem* h = new elem;
	elem* t = new elem;
	h->p = root;
	h->next = NULL;
	t = h;
	elem* tmp = h;
	elem* l;
	elem* r;
	while (h!= NULL)
	{
		
		if (h->p->l != NULL) { 
			l = new elem; l->next = NULL; tmp->next = l;
			l->p = h->p->l;
			tmp = tmp->next; }
		if (h->p->r != NULL) { r = new elem; r->next = NULL;
		r->p = h->p->r; tmp->next = r;
		tmp = tmp->next; }
		cout << h->p->key << ' ';
		t = h;
		h = h->next;
		delete t; 
	}
}

class Baltree :public Ftree
{
public:
	Baltree(int k) : Ftree(k){};
	
};


int main()
{
	
	setlocale(LC_ALL, "Russian");
	
	Ftree q(6), b, c(q);
	b = q;
	b.Print(b.Root(), 0);
	cout << endl;
	q.Print(q.Root(), 0);
	cout << endl;
	c.Print(c.Root(), 0);
	cout << endl;
	q.ADD(53); q.ADD(68); q.ADD(60);
	q.Print(q.Root(), 0);
	Node* r=q.find(53);
	if (r) cout << "содержится"; else cout << "не содержится";
	cout << endl;
	cout << q.max()<<' '<<q.min();
	cout << endl<<endl;
	q.Befdel(q.find(41)); 
	q.Print(q.Root(), 0);
	cout << endl << endl;
	int* a = new int[8];
	int n=q.RLR(a);
	for (int i = 0; i < n; i++) cout << a[i]<<' ';
	cout << endl;
	q.levels();
	cout << endl;
	
	
	
}







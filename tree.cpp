#include <iostream>
#include <vector>

template<typename T>
inline void swp(T& a, T& b)
{
	T tmp = a;
	a = b;
	b = tmp;
}

template<>
inline void swp(int& a, int& b)
{
	a ^= b;
	b ^= a;
	a ^= b;
}


template<typename T>
class Tree
{
private:
	struct Node
	{
		Node(Node* l=0, Node* r=0, T v=0) : left(l),right(r),data(v) {}
		Node* left;
		Node* right;
		T data;
	};
	Node* m_root;
	
	void recursivePrint(const Node* node)
	{
		if(!node)
			return;

		if(node->left)
			recursivePrint(node->left);
		
		std::cout << node->data << ",";
		
		if(node->right)
			recursivePrint(node->right);	
	}

	Node* recursiveInsert(Node* node,T val)
	{
		// Null case.
		if(!node)
			return new Node(0,0,val);			

		if(val < node->data)
			node->left = recursiveInsert(node->left,val);
		else if(val > node->data)
			node->right = recursiveInsert(node->right,val);

		// Must be the same.			
		return node;					
	}


	Node* findMin(Node* i)
	{	
		if(!i)
			return 0;

		Node* child = findMin(i->left);
		if(!child)
			return i;
		else 
			return child;				
	}

	Node* recursiveRemove(Node* node, T val)
	{
		if(!node)
			return 0;
		
		if(val < node->data)
		{
			node->left = recursiveRemove(node->left,val);
			return node;
		}
		else if(val > node->data)
		{
			node->right = recursiveRemove(node->right,val);
			return node;
		}
		else 
		{
			// Has two children.
			if(node->right && node->left)
			{
				// traverse right hand side and find smallest item. (most left)
				Node* small = findMin(node->right); 

				// Change this node to resemble the smallest node.
				node->data = small->data;
				node->right = recursiveRemove(node->right,node->data);
				return node;
			}
			else if(node->left)	
			{
				Node* l = node->left;
				delete node;
				return l;
			}
			else if(node->right)
			{
				Node* r = node->right;
				delete node;
				return r;
			}
		}
		return 0;		
	}
	
	void recursiveDelete(Node* n)
	{
		if(!n)
			return;
		recursiveDelete(n->left);
		recursiveDelete(n->right);
		delete n;
	}

public:
	Tree() : m_root(0) {}
	~Tree() 
	{
		recursiveDelete(m_root);
	}

	void remove(T n)
	{
		m_root=recursiveRemove(m_root,n);
	}
	
	void print()
	{
		recursivePrint(m_root);
	}

	bool insert(T n)
	{
		m_root = recursiveInsert(m_root,n);
	}		
};

template<typename T>
class Tree2
{
	struct Node
	{
		Node(const T& d,Node* l=0,Node* r=0,Node* p=0) : data(d),left(l),right(r),parent(p) {}
		T data;
		Node* left;
		Node* right;
		Node* parent;
	};

	Node* m_root;

	Node* minNode(Node* i)
	{
		while(i && i->left)
			i = i->left;
		return i;
	}
	Node* maxNode(Node* i)
	{
		while(i && i->right)
			i = i->right;
		return i;
	}
	Node* nextNode(Node* i)
	{
		if(i->right)
		{
			i = i->right;
			while(i->left)
				i = i->left;
		}
		else
		{
			// go up until we hit either a null or something we haven't decended.
			Node* parent = i->parent;
			while(parent && parent->right == i)
			{
				i = parent;
				parent = parent->parent;
			}
			if(!parent)
				i = i->right;
			else if(parent->right != i)
				i = parent;
		}
		return i;	
	}
	
	Node* findNode(const T& v)
	{
		Node* i = m_root;
		while(i)
		{
			if(v < i->data)
				i= i->left;
			else if(v > i->data)
				i=i->right;
			else
				return i;
		}
		return 0;
	}
	void deleteNode(Node* n)
	{
		if(n->left)
			n->left->parent = n->parent;
		else if (n->right)
			n->right->parent = n->parent;

		if(Node* parent = n->parent)
		{
			if(parent->left == n)
				parent->left = n->left;
			else
				parent->right = n->right;			
		}
		delete n;
	}
	
public:

	Tree2()
		:m_root(0) 
	{}

	void insert(const T& v)
	{
		if(!m_root)
		{
			m_root = new Node(v);
			return;
		}

		Node* i = m_root;
		while(i)
		{
			if(v < i->data)				
			{
				if(!i->left)
					i->left = new Node(v,0,0,i);
				i = i->left;
			}
			else if(v > i->data)
			{	    
				if(!i->right)
					i->right = new Node(v,0,0,i);
				i = i->right;
			}
			else
				return;					
		}
	}

	void print()
	{
		// Find smallest and start from there.
		Node* i = minNode(m_root);
		Node* end = maxNode(m_root);
	
		for( ; i != end; i = nextNode(i))
			std::cout << i->data << ",";
	}
	
	void remove(const T& v)
	{		
		Node* toRemove = findNode(v);
		//std::cout << " removing " << v << std::endl;
	
		if(toRemove->left && toRemove->right)
		{
			//std::cout << " node has two children " << toRemove->left->data << " and " << toRemove->right->data << std::endl;
			Node* minRight = minNode(toRemove->right);
			toRemove->data = minRight->data;
			deleteNode(minRight);
		}
		else if(toRemove->left)
		{
			//std::cout << " node has 1 child " << toRemove->left->data <<  std::endl;
			deleteNode(toRemove);
		}
		else if(toRemove->right)
		{
			//std::cout << " node has 1 child " << toRemove->right->data << std::endl;
			deleteNode(toRemove);
		}
		else
		{
			//std::cout << " node has no children" << std::cout;
			deleteNode(toRemove);
		}
	}
};

int main(int argc, char** argv)
{	
	using namespace std;
	vector<int> numbers;
	Tree2<float> tree;

	int c;
	while(std::cin >> c)
	{
		tree.insert(c);
		numbers.push_back(c);
	}

	cout << " done" << endl;
	
	tree.print();
	for(vector<int>::const_reverse_iterator i = numbers.rbegin(); i!= numbers.rend(); ++i)
	{
		tree.remove(*i);
		std::cout << std::endl;
		tree.print();
	}	

	std::cout << std::endl;

	return 0;
}

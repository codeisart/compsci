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

template<typename IT>
inline void bubble(IT b, IT e)
{
	bool sorted;	
	do
	{
		sorted = true;
		for(IT i = b; i != e-1; ++i)
		{
			if(*i > *(i+1))
			{
				swp(*i,*(i+1));
				sorted = false;
			}
		}
	} while(!sorted);
}

template<typename IT>
inline void bubble2(IT b, IT e)
{
	bool sorted;
	int top = 1;	
	do
	{
		sorted = true;
		for(IT i = b; i != e-top; ++i)
		{
			if(*i > *(i+1))
			{
				swp(*i,*(i+1));
				sorted = false;
			}
		}
		top++;
	} while(!sorted);
}

// log2 where pow(2,n) >= n
int log2greaterThanN(int n)
{
	int p = 0;
	while((1 << p) < n)
		p++;

	return p;	
}

template<typename IT>
void merge_exchange(IT b, IT e)
{
	int n = std::distance(b,e);
	int t = log2greaterThanN(n);		// logN

	for(int p = 1 << (t-1); p > 0; p >>=1)
	{
		int q = 1<<(t-1);
		int r = 0;
		int d = p; 
            		
		for(;;)
		{
			for(int i = 0; ; ++i)
			{
				if( b[i] > b[i+d])
					swp(b[i], b[i+d]);
				
				// Condition must be before any change to i AND 
				// loop must execute at least once.
				if(i>=n-d || i&p != r)
					break;
			}
			
			// Condition must be before any change to q or q AND
			// loop must execute at least once.
			if(q==p)
				break;

			d = q-p;
			q >>= 1;
			r = p;
		} 
	}
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

int main(int argc, char** argv)
{	
	using namespace std;
	vector<int> numbers;
	Tree<float> tree;

	int c;
	while(std::cin >> c)
	{
		if(c > 0)
			tree.insert((float)1.f / c);
		numbers.push_back(c);
		//tree.print();
		//std::cout << c << std::endl;
	}

	cout << " read " << numbers.size() << endl;
	cout << " sorting...";

	//merge_exchange(numbers.begin(),numbers.end());
	//radix_sort(numbers.begin(), numbers.end());	

	cout << " done" << endl;
	
	tree.print();
	for(vector<int>::const_reverse_iterator i = numbers.rbegin(); i!= numbers.rend(); ++i)
	{
		if( *i > 0 )
			tree.remove((float)1.f / *i);
	
		std::cout << std::endl;
		tree.print();
	}	

	tree.remove(154);
	std::cout << std::endl;
	tree.print();

	//cout << *i << endl;

	return 0;
}

#include <iostream>
#include <vector>

using namespace std;

class Tri
{
	struct Node
	{
		Node(char c=0)  : data(c) {}
		typedef vector<Node*> ChildCon; 
		ChildCon children;
		char data;

		Node* findChild(char c) const
		{
			// Crappy linear search. Replace with binary search.		
			for(ChildCon::const_iterator i = children.begin(); i != children.end(); ++i)
				if((*i)->data == c)
					return *i;
			return 0;
		}
		Node* insertChild(char c)
		{
			children.push_back(new Node(c));
			return children.back();
		}
	};
	Node* m_root;

public:

	Tri() 
		: m_root(new Node()) {}
	
	void insert(const string& str)
	{
		cout << "inserting " << str << endl;
		Node* node = m_root;
		for(string::const_iterator i = str.begin(); i!= str.end(); ++i)
		{
			// Decend until we can't any more.
			Node* n = node->findChild(*i);
			if(n)
				node = n;
			else
				n = node->insertChild(*i);

			// Insefficent here, should really fail and stop searching as these are new nodes with no children.
			node = n;
		}
	}
	string nextWord(Node* t, const const string& prefix)
	{
		string w;
		if(!t)
			return;

		// traversing down to lowest node. first word.
		if( t-.)
		
		
		nextNode(child,prefix+t->data);

		
		// Visit all children in ORDER.
		Node::ChildCon::const_iterator i = t->children.begin(); i
	}
};

int main(int argc, char** argv)
{
	Tri t;

	string s;
	while(cin >> s)
	{
		//cout << s << endl;
		t.insert(s);
	}


	return 0;
}

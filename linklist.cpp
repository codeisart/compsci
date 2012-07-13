#include <iostream>

template<typename T>
class LinkList
{
private:
	struct Node
	{
		Node(T& v, Node* n=0, Node* p=0) : data(v),next(n),prev(p) {}
		T data;
		Node* next;
		Node* prev;
	};

	Node* m_head;
	Node* m_tail;

	Node* insertToRightOf(Node* n,Node* newNode)
	{
		if(!n)
			return newNode;		

		// Insert new node.
		newNode->next = n->next;
		newNode->prev = n;

		// PREV pointer for forward neighbour
		if(n->next)
			n->next->prev = n;		

		// finally NEXT pointer of current.
		n->next = newNode;

		// Return new pointer.
		return newNode;
	}

	Node* insertToLeftOf(Node* n, Node* newNode)
	{
		if(!n)
			return newNode;		

		// Insert new node.
		newNode->next = n;
		newNode->prev = n->prev;

		// NEXT pointer for backwards neighbour
		if(n->prev)
			n->prev->next = n;		

		// finally PREVOUS pointer of current.
		n->prev = newNode;

		// Return new pointer.
		return newNode;
	}

	Node* removeNode(Node* n)
	{
		if(!n)
			return 0;
	
		if(n->prev)
			n->prev->next = n->next;
		if(n->next)
			n->next->prev = n->prev;
		
		Node* next = n;
		n->next = 0;
		n->prev = 0;
		
		return next;
	}

	void deleteAll()
	{
		Node* i = m_head;
		while(i)
		{
			Node* next = i->next;			
			delete i;
			i = next;
		}
	}

public:
	LinkList(const LinkList& c)
	{
		Node* i = c.m_head;
		while(i)
		{
			push_back(i->data);
			i=i->next;
		}
	}

	LinkList() : m_head(0),m_tail(0) {}
	~LinkList()
	{
		deleteAll();
	}

	LinkList& operator=(const LinkList& c)
	{
		deleteAll();
		Node* i = c.m_head;
		while(i)
		{
			push_back(i->data);
			i=i->next;
		}
		return *this;
	}
	
	void push_back(T& v)
	{
		m_tail = insertToRightOf(m_tail,new Node(v));	
		if(!m_head)
			m_head = m_tail;
	}

	void push_front(T& v)
	{
		m_head = insertToLeftOf(m_head,new Node(v));	
		if(!m_tail)
			m_tail = m_head;
	}


	void merge(const LinkList& c)
	{
		using namespace std;
		cerr << "merging..." << endl;

		Node* insertPoint = m_head;
		for(Node* i = c.m_head; i; i = i->next)
		{
			Node* j = m_head;
			while(j)
			{
				if(j->data < i->data)
				{
					cerr << "inserting" << i->data << endl;

					// Insert new to left of J
					Node* node = new Node(i->data,j,j->prev);
					
					// If the current item is the first item in the list we must update the head.
					if(!j->prev)
						m_head = node;
					else
						j->prev->next = node; // Point previous node at the new one.

					// Point current node's previous at our new node.
					j->prev = node;

					// Now our new position is the newly inserted node.					
					j = node;					
				}
				else
					j = j->next;
			}
		}		
	}

	void sort()
	{
		Node* sorted = 0;
		Node* i = m_head;
		
		while(i)
		{
			Node* head = i;
			Node** trail = &sorted;
			i = i->next;

			for(;;)
			{
				if(!*trail || head->data < (*trail)->data)
				{
					head->next = *trail;
					*trail = head;
					break;
				}
				else
					trail = &(*trail)->next;	
			}
		}
		m_head = sorted;

		// Correct back pointers.
		i = m_head;
		Node* prev = 0;
		while(i)
		{
			i->prev = prev;
			prev = i;
			i = i->next;
		}
		m_tail = prev;
	}

	void print()
	{
		Node* i = m_head;
		while(i)
		{
			std::cout << i->data << ",";
			i = i->next;
		}
		std::cout << std::endl;
	}
};

int main(int argc, char** argv)
{
	LinkList<int> list;
	LinkList<int> list2;

	int c;
	while(std::cin >> c)
		list.push_back(c);

	list.print();

	list2 = list;
	list.sort();
	list2.sort();
	list.merge(list2);
	list.print();

	return 0;
}




#include <iostream>

template<typename T>
class LinkList
{
private:
	struct Node
	{
		Node(T& v, Node* n=0) : data(v),next(n) {}
		T data;
		Node* next;
	};

	Node* m_head;

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

	LinkList() : m_head(0) {}
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
		// Find back.
		Node* i = m_head;
		Node* trail = 0;
		while(i)
		{
			trail = i;
			i = i->next;
		}
		
		// Insert at the back.
		Node* node = new Node(v,0);
		if(trail)
			trail->next = node;
		else
			m_head = node;

	}

	void push_front(T& v)
	{
		m_head = new Node(v,m_head);	
	}

	Node* recursive_reverse(Node* n)
	{
		if(!n)
			return 0;
		if(!n->next)
			return n;

		Node* list = recursive_reverse(n->next);
		Node* i = list;
		while(i->next)
			i=i->next;			

		i->next = n;
		n->next = 0;

		return list;
	}

	void reverse()
	{
		m_head = recursive_reverse(m_head);
	}

	void merge(const LinkList& c)
	{
		Node* newHead = 0;
		Node* j = m_head;
		Node* trail = 0;

		// Run through each item in incoming list.
		for(const Node* i = c.m_head; i; i=i->next)
		{			
			// Insert from where we left off as we're sorted.
			while(j)
			{
				// Insert the incoming item in the list.
				if(i->data < j->data)
				{
					Node* newNode = new Node(i->data, j);
					if(trail)
						trail->next = newNode;
					else 
						newHead = newNode;

					j = newNode;
				}
				else
					j = j->next;	
								
				trail = j;
			}	
		}
		m_head = newHead;		
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
	using namespace std;

	LinkList<int> list1;
	LinkList<int> list2;

	int c;
	while(std::cin >> c)
		list1.push_back(c);

	cout << "what we just read list1" << endl;
	list1.print();
	
	cout << "after sorting" << endl;
	list1.sort();	
	list1.print();

	cout << "copy of called list2" << endl;
	list2 = list1;
	list2.print();

	cout << "merge of list1 and list2" << endl;
	LinkList<int> list3 = list1;
	list3.merge(list2);
	list3.print();

	cout << "reversed list1" << endl;
	list1.reverse();
	list1.print();

	return 0;
}




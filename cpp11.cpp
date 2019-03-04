#include <atomic>
#include <unordered_map>
#include <initializer_list>
#include <vector>
#include <algorithm>
#include <iostream>

class Widget
{
public:
	Widget() : ptr(new char[256])
	{} 

	Widget(std::initializer_list<int> l)
		: Widget()
	{
		int index = 0;
		for(auto i: l)
			array[++index] = i;
	
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	}

	Widget operator+(const Widget& rhs)
	{
		return *this;
	}
	
	Widget(int a, int b, int c) 
		: array {a,b,c}, ptr(nullptr) 
	{
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	}
	int getValue() const { return array[0]; }	

	Widget(Widget&& r)
		: ptr(std::move(r.ptr))
	{
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	}
	~Widget()
	{
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	}
	
private:
	Widget& operator=(Widget&) = delete;
	Widget(const Widget&) = default;
	
	char* ptr;
	int array[50];
};

template<typename T>
class LockFreeQueue
{
	struct Node
	{
		Node(const T& v) : value(v), next(nullptr) {} 
		T value;
		Node* next;
	};
	Node* first;
	std::atomic<Node*> divider;
	std::atomic<Node*> last;

public:
	LockFreeQueue()
	{
		first = divider = last = new Node( T() );
	}		
	~LockFreeQueue()
	{
		while(first)
		{	
			Node* tmp = first;
			first.compare_and_exchange(tmp,first()->next);
			delete tmp;
		}
	}
	void Produce(const T& t)
	{
		last()->next = new Node(t);
		last.compare_and_exchange(last(),last()->next);							// Publish.
		while(first != divider)
		{
			Node* tmp = first();
			first(first->next);
			delete tmp;
		}	
	}
	bool Consume(const T& t)
	{
		if(divider != last) 
		{											// if queue is nonempty
			auto result = divider()->next->value;	// C: copy it back
			divider(divider->next);					// D: publish that we took it
			return true;							// and report success
		}
		return false;						// else report empty	
	}
	
};

Widget Factory()
{
	Widget a { 1,2,3,4,5 };
	return a;
}


int main(int argc, char** argv)
{
	Widget a { 1,2,3,4,5 };
	Widget b(3,3,3);
	Widget c(a+b+Factory());


/*	std::vector<int> blah;
	for(int i = 0; i < 65536; ++i)
		blah.push_back(i);

	std::sort(blah.begin(),blah.end(),
		[&](const int &l, const int& r) { return l < r && l < a.getValue(); } );
*/
	return 0;
}

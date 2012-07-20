#include <atomic>
#include <unordered_map>

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
			first = first->next;
			delete tmp;
		}
	}
	void Produce(const T& t)
	{
		last->next = new Node(t);
		last = last->next;				// Publish.
		while(first != divider)
		{
			Node* tmp = first;
			first = first->next;
			delete tmp;
		}	
	}
	bool Consume(const T& t)
	{
		if(divider != last) 
		{											// if queue is nonempty
			auto result = divider->next->value;		// C: copy it back
			divider = divider->next;				// D: publish that we took it
			return true;							// and report success
		}
		return false;						// else report empty	
	}
	
};


int main(int argc, char** argv)
{
//	typedef unordered_map<

/*
	LockFreeQueue<int> q;

	q.Produce(1);
	q.Produce(1);
	q.Produce(1);
	q.Produce(1);
	q.Consume(1);
	
	q.Consume(1);
	q.Consume(1);
	q.Consume(1);
	q.Consume(1);
	q.Consume(1);
*/

	return 0;
}

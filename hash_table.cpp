#include <iostream>
#include <vector>
#include <iomanip>

template<typename KEY=const char*,typename VALUE=int>
class HashTable
{
private:
	typedef unsigned int Hash;
	typedef KEY Key;
	typedef VALUE Value;
	typedef std::pair<Hash,Value> Kvp;
	typedef std::vector<Kvp> HashContainer;

	Hash generateHash(int x)
	{
		// easy for now.
		Hash hash = 2166136261U;		// offset.
		const Hash fnvPrime = 16777619;	// fnv prime
		Hash c = (Hash) x;	
		
		hash ^= c;
		hash *= fnvPrime;
		return hash;
	}

	Hash generateHash(const char* v)	// string hash.
	{
		Hash hash = 2166136261U;		// offset.
		const Hash fnvPrime = 16777619;	// fnv prime
		while(Hash c = *v++)			// assume string for now.	
		{
			hash ^= c;
			hash *= fnvPrime;
		}
		return hash;
	}

	HashContainer m_hashSpace;
public:
	
	HashTable(int tableSize = 251)	// Biggest prime < 256
	{
		m_hashSpace.resize(tableSize);
	}
	Value* insert(Key k)
	{
		Hash hash = generateHash(k);
		int index = hash % m_hashSpace.size();
		Value v = 0;							// assuming this is ok.;

		Kvp kvp(hash,v);
		const int maxAttempts = m_hashSpace.size();
		
		for(int i = 0; i < maxAttempts && m_hashSpace[index].first!=0 && m_hashSpace[index].first != hash; i++)
			index = (index+1) % m_hashSpace.size();
		
		if(m_hashSpace[index].first == 0 || m_hashSpace[index].first == hash)
		{
			m_hashSpace[index] = kvp;
			return &m_hashSpace[index].second;		
		}	
		return 0;	
	}	
	Value* find(Key k) 
	{
		Hash hash = generateHash(k);
		int index = hash % m_hashSpace.size();
		
		const int maxAttempts = m_hashSpace.size();
		
		for(int i = 0; i < maxAttempts && m_hashSpace[index].first!=0 && m_hashSpace[index].first != hash; i++)
			index = (index+1) % m_hashSpace.size();
		
		if(m_hashSpace[index].first == hash)
			return &m_hashSpace[index].second;

		// fail.
		return 0;
	}
	
	Value& operator[](Key k)
	{
		if(Value* v= find(k))
			return *v;

		return *insert(k);		// This is bad if this fails.
	}

	void print()
	{	
		using namespace std;	
		//for( HashContainer::iterator i = m_hashSpace.begin(); i != m_hashSpace.end(); ++i) 
		for(int i = 0; i < m_hashSpace.size(); ++i)
		{		
			const Kvp& thing = m_hashSpace[i];
			if(thing.first)	
			{
				cout << setw(10) << "Index: " << i;
				cout << setw(10) << "Hash: " << thing.first;
				cout << setw(10) << "Value: " << thing.second;
				cout << endl;
			}
		}
	}
};

/*
int main(int argc, char** argv)
{	
	using namespace std;

	HashTable<int,int> table;

	int i;
	while(cin >> i)
		table[i]++;

	//table.add("walk",9);
	//table.add("with",2);
	//table.add("me",6);
	table.print();
	

	return 0;
}
*/

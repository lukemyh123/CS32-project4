#ifndef TRIE_INCLUDED
#define TRIE_INCLUDED

#include <string>
#include <vector>

template<typename ValueType>
class Trie
{
public:
	Trie();
	~Trie();
	void reset();
	void insert(const std::string& key, const ValueType& value);
	std::vector<ValueType> find(const std::string& key, bool exactMatchOnly) const;

	// C++11 syntax for preventing copying and assignment
	Trie(const Trie&) = delete;
	Trie& operator=(const Trie&) = delete;
private:
	struct tNode
	{
		char label;
		vector<ValueType> values;
		tNode* children[5];
	}
	tNode *root;
	//void insertHelper(const std::string& key, const ValueType& value)
};

template<typename ValueType>
Trie<ValueType>::Trie()
{
	root = nullptr;
}

template<typename ValueType>
void Trie<ValueType>::insert(const std::string& key, const ValueType& value)
{
	tNode = *temp;

}

template<typename ValueType>
std::vector<ValueType> Trie<ValueType> ::find(const std::string& key, bool exactMatchOnly) const
{

}
#endif // TRIE_INCLUDED
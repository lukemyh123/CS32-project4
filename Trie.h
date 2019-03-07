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
		//char label;
		vector<ValueType> values;
		tNode* children[5];
	};
	tNode *root;
	void insertHelper(const std::string& key, tNode* cur, const ValueType& value)
};

template<typename ValueType>
Trie<ValueType>::Trie()
{
	tNode *root_node = new tNode;
	root_node->children = nullptr;
	root_node->values = nullptr;
	root = nullptr;

}

template<typename ValueType>
void Trie<ValueType>::insert(const std::string& key, const ValueType& value)
{
	insertHelper(key, root, value);
}

template<typename ValueType>
void Trie<ValueType>::insertHelper(const std::string& key, tNode* cur, const ValueType& value)
{
	if (key.size() == 0)
		return;

	tNode *cur = root;
	if (key[0] == 'A')
		insertHelper(key, )
	if((key[0] == 'T')
		return;
	if((key[0] == 'C')
		return;
	if((key[0] == 'G')
		return;
}

template<typename ValueType>
std::vector<ValueType> Trie<ValueType> ::find(const std::string& key, bool exactMatchOnly) const
{

}
#endif // TRIE_INCLUDED
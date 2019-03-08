#ifndef TRIE_INCLUDED
#define TRIE_INCLUDED

#include <string>
#include <vector>

template<typename ValueType>
class Trie
{
public:
	Trie();
	~Trie() { delete root; };
	void reset();
	void insert(const std::string& key, const ValueType& value);
	std::vector<ValueType> find(const std::string& key, bool exactMatchOnly) const;

	//test function need to delete;
	void print() { printHelp(root); }

	// C++11 syntax for preventing copying and assignment
	Trie(const Trie&) = delete;
	Trie& operator=(const Trie&) = delete;
private:
	struct tNode
	{
		char label;
		std::vector<ValueType> values;
		std::vector<tNode*> children;
	};
	tNode *root;
	std::vector<tNode*> paths;  //push_back all possible paths

	void insertHelper(const std::string& key, tNode* cur, const ValueType& value);
	std::vector<ValueType> findHelperTrue(const std::string& key, tNode* cur) const;
	std::vector<ValueType> findHelperFalse(const std::string& key, tNode* cur) const;
	std::vector<ValueType> findAnotherHelperFalse(const std::string& key, tNode* cur) const;


	//void findAllPaths(const std::string& key, tNode* cur);
	//void findAllPathsHelper(tNode* cur);

	tNode* newNode(char c)
	{
		tNode* new_node = new tNode;
		new_node->label = c;

		return new_node;
	}

	//need to delete;
	void printHelp(tNode *cur)
	{
		if (cur->label == 'T')
			return;

		for (typename std::vector<tNode*>::iterator it = cur->children.begin();
			it != cur->children.end(); ++it)
		{
			for (typename std::vector<ValueType>::iterator nit = (*it)->values.begin();
				nit != (*it)->values.end();
				++nit)
				std::cout << (*nit) << std::endl;
			return printHelp(*it);
		}
	}
};

template<typename ValueType>
inline
Trie<ValueType>::Trie()
{
	tNode *root_node = new tNode;  //initialize the tNode
	root = root_node;
}

template<typename ValueType>
void Trie<ValueType>::reset()
{
	for (typename std::vector<tNode*>::iterator it = root->children.begin();
		it != root->children.end();)
	{
		delete *it;
		it = root.erase(it);
	}
}
template<typename ValueType>
void Trie<ValueType>::insert(const std::string& key, const ValueType& value)
{
	if (key.size() == 0)  //do nothing if the key is empty
		return;
	insertHelper(key, root, value);
}

template<typename ValueType>
void Trie<ValueType>::insertHelper(const std::string& key, tNode* cur, const ValueType& value)
{

	if (key.size() == 0)
	{
		cur->values.push_back(value);
		return;
	}
	if (cur->children.size() == 0)
	{
		tNode *newnode = newNode(key[0]);
		cur->children.push_back(newnode);
		return insertHelper(key.substr(1), newnode, value);
	}
	else
	{
		for (typename std::vector<tNode*>::iterator it = cur->children.begin();
			it != cur->children.end(); ++it)
		{
			if (key[0] == (*it)->label)
				return insertHelper(key.substr(1), *it, value);
		}
		tNode *newnode = newNode(key[0]);
		cur->children.push_back(newnode);
		return insertHelper(key.substr(1), newnode, value);
	}
}

/*template<typename ValueType>
void Trie<ValueType>::findAllPaths(const std::string& key, tNode* cur)
{
	for (typename std::vector<tNode*>::iterator it = cur->children.begin();
		it != cur->children.end(); ++it)
	{
		if (key[0] == (*it)->label)
		{
			return findAllPathsHelper(*it);
		}
	}
}

template<typename ValueType>
void Trie<ValueType>::findAllPathsHelper(tNode* cur)
{
	if (cur->children.size() == 0)
		return;

	for (typename std::vector<tNode*>::iterator it = cur->children.begin();
		it != cur->children.end(); ++it)
	{
		return findAllPathsHelper(*it);
	}
}*/


template<typename ValueType>
std::vector<ValueType> Trie<ValueType>::find(const std::string& key, bool exactMatchOnly) const
{
	if (exactMatchOnly == true)
		return findHelperTrue(key, root);
	else
		return findHelperFalse(key, root);
}

template<typename ValueType>
std::vector<ValueType> Trie<ValueType>::findHelperTrue(const std::string& key, tNode* cur) const
{
	std::vector<ValueType> find_values;
	
	if (key.size() == 0)
	{
		for (typename std::vector<ValueType>::iterator it = cur->values.begin();
			it != cur->values.end(); ++it)
		find_values.push_back(*it);
		return find_values;
	}

	for (typename std::vector<tNode*>::iterator it = cur->children.begin();
		it != cur->children.end(); ++it)
	{
		if (key[0] == (*it)->label)
			return findHelperTrue(key.substr(1), *it);
	}

	return find_values;
}

template<typename ValueType>
std::vector<ValueType> Trie<ValueType>::findHelperFalse(const std::string& key, tNode* cur) const
{
	for (typename std::vector<tNode*>::iterator it = cur->children.begin();
		it != cur->children.end(); ++it)
	{
		if (key[0] == (*it)->label)
			return findAnotherHelperFalse(key.substr(1), *it);
	}
}

template<typename ValueType>
std::vector<ValueType> Trie<ValueType>::findAnotherHelperFalse(const std::string& key, tNode* cur) const
{
	std::vector<ValueType> find_values;

	if (cur->children.size() == 0)
	{
		for (typename std::vector<ValueType>::iterator it = cur->values.begin();
			it != cur->values.end(); ++it)
			find_values.push_back(*it);
		return find_values;
	}

	for (typename std::vector<tNode*>::iterator it = cur->children.begin();
		it != cur->children.end(); ++it)
	{
		return findAnotherHelperFalse(key.substr(1), *it);
	}

	return find_values;

}

#endif // TRIE_INCLUDED
#ifndef TRIE_INCLUDED
#define TRIE_INCLUDED

#include <string>
#include <vector>

template<typename ValueType>
class Trie
{
public:
    Trie();
    ~Trie(){delete root;};
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
        std::vector<ValueType> values;
        tNode* children[4];  //A,T,C,G
    };
    tNode *root;
    
    void insertHelper(const std::string& key, tNode* cur, const ValueType& value);
    
    tNode* newNode(char c)
    {
        tNode* new_node = new tNode;
        new_node->label = c;
        for(int i=0; i<4; i++)
            new_node->children[i] = nullptr;  // for loop
        // new_node->values = nullptr;
        
        return new_node;
    }
};

template<typename ValueType>
inline
Trie<ValueType>::Trie()
{
    tNode *root_node = new tNode;
    for(int i=0; i<4; i++)
        root_node->children[i] = nullptr;  // for loop
 //   root_node->values = nullptr;
   // root_node->label = '';
    root = root_node;
}

template<typename ValueType>
void Trie<ValueType>::insert(const std::string& key, const ValueType& value)
{
    insertHelper(key, root, value);
}

template<typename ValueType>
void Trie<ValueType>::insertHelper(const std::string& key, tNode* cur, const ValueType& value)
{
    if(key.size() == 1)
        cur->values.push_back(value);
    
    if (key.size() == 0)
        return;
    
    //if()
    if(key[0] == 'A')
    {
        if(cur->children[0] != nullptr)
            insertHelper(key.substr(1), cur->children[0], value);
        else
        {
            cur->children[0] = newNode(key[0]);
            insertHelper(key.substr(1), cur->children[0], value);
        }
    }
    
     if(key[0] == 'T')
    {
        if(cur->children[1] != nullptr)
            insertHelper(key.substr(1), cur->children[1], value);
        else
        {
            cur->children[1] = newNode(key[0]);
            insertHelper(key.substr(1), cur->children[1], value);
        }
    }
    if(key[0] == 'C')
    {
        if(cur->children[2] != nullptr)
            insertHelper(key.substr(1), cur->children[2], value);
        else
        {
            cur->children[2] = newNode(key[0]);
            insertHelper(key.substr(1), cur->children[2], value);
        }
    }
    if(key[0] == 'G')
    {
        if(cur->children[3] != nullptr)
            insertHelper(key.substr(1), cur->children[3], value);
        else
        {
            cur->children[3] = newNode(key[0]);
            insertHelper(key.substr(1), cur->children[3], value);
        }
    }
    
     for (typename std::vector<ValueType>::iterator it = cur->values.begin() ; it != cur->values.end(); ++it)
        std::cout << ' ' << *it;
    //std::cout << cur->label << std::endl;

    //return insertHelper(key.substr(1), )
}
                 
 template<typename ValueType>
 std::vector<ValueType> Trie<ValueType> ::find(const std::string& key, bool exactMatchOnly) const
{
    return;
}
#endif // TRIE_INCLUDED

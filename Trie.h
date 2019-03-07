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
    
    //test function need to delete;
    void print(){printHelp(root);}
    // C++11 syntax for preventing copying and assignment
    Trie(const Trie&) = delete;
    Trie& operator=(const Trie&) = delete;
private:
    struct tNode
    {
        char label;
        std::vector<ValueType> values;
        tNode* children[5];  //A,T,C,G
    };
    tNode *root;

    void insertHelper(const std::string& key, tNode* cur, const ValueType& value);
    std::vector<ValueType> findHelper(const std::string& key, tNode* cur, bool exactMatchOnly) const;

    tNode* newNode()
    {
        tNode* new_node = new tNode;
        for(int i=0; i<5; i++)
            new_node->children[i] = nullptr;  // for loop
        return new_node;
    }
    
    //need to delete;
    void printHelp(tNode *cur)
    {
        /* for (typename std::vector<ValueType>::iterator it = cur->values.begin() ; it != cur->values.end(); ++it)
         std::cout << ' ' << *it;*/
       // std::cout << cur->children[3]->children[0]->children[1] << std::endl;
       /* for (typename std::vector<ValueType>::iterator it = cur->children[3]->children[0]->children[1]->values.begin() ;
             it != cur->children[3]->children[0]->children[1]->values.end();
             ++it)
            std::cout << ' ' << *it;*/

        for(int i=0; i<5; i++)
        {
            if(cur->children[i] == nullptr)
            {
                return;
            }
        }
        
        for(int i=0; i<5; i++)
        {
            if(cur->children[i] != nullptr)
            {
                std::cout << cur->children[i] << std::endl;
                printHelp(cur->children[i]);
            }
        }
    }
};

template<typename ValueType>
inline
Trie<ValueType>::Trie()
{
    tNode *root_node = new tNode;  //initialize the tNode
    for(int i=0; i<5; i++)
        root_node->children[i] = nullptr;  // for loop
    root = root_node;
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
   
    if(key.size() == 0)
    {
        cur->values.push_back(value);
        return;
    }
    
    if(key[0] == 'A')
    {
        if(cur->children[0] != nullptr)
            insertHelper(key.substr(1), cur->children[0], value);
        else
        {
            cur->children[0] = newNode();
            insertHelper(key.substr(1), cur->children[0], value);
        }
    }
    
     if(key[0] == 'T')
    {
        if(cur->children[1] != nullptr)
            insertHelper(key.substr(1), cur->children[1], value);
        else
        {
            cur->children[1] = newNode();
            insertHelper(key.substr(1), cur->children[1], value);
        }
    }
    if(key[0] == 'C')
    {
        if(cur->children[2] != nullptr)
            insertHelper(key.substr(1), cur->children[2], value);
        else
        {
            cur->children[2] = newNode();
            insertHelper(key.substr(1), cur->children[2], value);
        }
    }
    if(key[0] == 'G')
    {
        if(cur->children[3] != nullptr)
            insertHelper(key.substr(1), cur->children[3], value);
        else
        {
            cur->children[3] = newNode();
            insertHelper(key.substr(1), cur->children[3], value);
        }
    }
    if(key[0] == 'N')
    {
        if(cur->children[4] != nullptr)
            insertHelper(key.substr(1), cur->children[4], value);
        else
        {
            cur->children[4] = newNode();
            insertHelper(key.substr(1), cur->children[4], value);
        }
    }
    //std::cout << "ghhhh" << std::endl;
}
                 
template<typename ValueType>
std::vector<ValueType> Trie<ValueType>::find(const std::string& key, bool exactMatchOnly) const
{
    return findHelper(key, root, exactMatchOnly);
}

template<typename ValueType>
std::vector<ValueType> Trie<ValueType>::findHelper(const std::string& key, tNode* cur, bool exactMatchOnly) const
{
    std::vector<ValueType> find_values;

    if(exactMatchOnly == true)
    {
        if(key.size() == 0)
        {
            for (typename std::vector<ValueType>::iterator it = cur->values.begin();
                 it != cur->values.end(); ++it)
                find_values.push_back((*it));
            return find_values;
        }
        
        if(key[0] == 'A')
        {
            if(cur->children[0] != nullptr)
                return findHelper(key.substr(1), cur->children[0], exactMatchOnly);
        }
        
        if(key[0] == 'T')
        {
            if(cur->children[1] != nullptr)
                return findHelper(key.substr(1), cur->children[1], exactMatchOnly);
        }
        if(key[0] == 'C')
        {
            if(cur->children[2] != nullptr)
                return findHelper(key.substr(1), cur->children[2], exactMatchOnly);
        }
        if(key[0] == 'G')
        {
            if(cur->children[3] != nullptr)
                return findHelper(key.substr(1), cur->children[3], exactMatchOnly);
        }
        if(key[0] == 'N')
        {
            if(cur->children[4] != nullptr)
                return findHelper(key.substr(1), cur->children[4], exactMatchOnly);
        }
    }
    
    if(exactMatchOnly == false)
    {
        
        return;
    }
    
    return find_values;
}
#endif // TRIE_INCLUDED

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
        std::vector<tNode*> children;  //A,T,C,G
    };
    tNode *root;

    void insertHelper(const std::string& key, tNode* cur, const ValueType& value);
    std::vector<ValueType> findHelper(const std::string& key, tNode* cur, bool exactMatchOnly) const;

    tNode* newNode(char c)
    {
        tNode* new_node = new tNode;
        new_node->label = c;
        
        return new_node;
    }
    
    //need to delete;
    void printHelp(tNode *cur)
    {
        if(cur->label == 'T')
            return;
            
        for (typename std::vector<tNode*>::iterator it = cur->children.begin() ;
                it != cur->children.end(); ++it)
        {
                for (typename std::vector<ValueType>::iterator nit = (*it)->values.begin() ;
                          nit != (*it)->values.end();
                        ++nit)
                    std::cout << (*nit) <<std::endl;
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
    if(cur->children.size() == 0)
    {
        tNode *newnode = newNode(key[0]);
        cur->children.push_back(newnode);
        return insertHelper(key.substr(1), newnode, value);
    }
    else
    {
        for(typename std::vector<tNode*>::iterator it = cur->children.begin();
                  it != cur->children.end(); ++it)
        {
            if(key[0] == (*it)->label)
                return insertHelper(key.substr(1), *it, value);
        }
        tNode *newnode = newNode(key[0]);
        cur->children.push_back(newnode);
        return insertHelper(key.substr(1), newnode, value);
    }
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

   /* if(exactMatchOnly == true)
    {
        
    }*/
    
/*    if(exactMatchOnly == false)
    {
        
        return;
    }*/
    
    return find_values;
}
#endif // TRIE_INCLUDED

//
//  main.cpp
//  project4
//
//  Created by yunhui ma on 3/6/19.
//  Copyright © 2019 luke. All rights reserved.
//

#include <iostream>
#include <vector>

#include "Trie.h"
using namespace std;
int main() {
    
  Trie<int>    trie;        //    This    is    like    std::multimap<std::string,int>    trie;
   /* trie.insert("GATTACA",    42);        //    GATTACA    à {42}
    trie.insert("GATTACA",    17);       //    GATTACA    à {42,    17}
    trie.insert("GATTACA",    42);*/
    
    //trie.insert("CA",    10);        //    GATTACA    à {42}
    //trie.insert("GA",    42);        //    GATTACA    à {42}
    trie.insert("GKb",    17);       //    GATTACA    à {42,    17}
    trie.insert("GKb",    42);
    trie.insert("GKb",    5);
    trie.insert("KKT",    42);

    trie.print();
    /*vector<int> temp = trie.find("GAT", true);//    GATTACA    à {42,    17,    42}
    for (vector<int>::iterator it = temp.begin();
         it != temp.end(); ++it)
        cout << *it << endl;*/
    return 0;
}

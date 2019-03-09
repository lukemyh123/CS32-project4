//
//  main.cpp
//  project4
//
//  Created by yunhui ma on 3/6/19.
//  Copyright © 2019 luke. All rights reserved.
//
#include <fstream>     //    needed    to    open    files
#include <string>
#include <iostream>
#include <vector>

#include "Trie.h"
#include "provided.h"
using namespace std;
int main() {
    
   /* Trie<int>    trie;        //    This    is    like    std::multimap<std::string,int>    trie;
    trie.insert("GATTACA",    42);        //    GATTACA    à {42}
     trie.insert("GATTACA",    17);       //    GATTACA    à {42,    17}
     trie.insert("GATTACA",    42);
    trie.insert("GATTAjA",    989);
    trie.insert("GgTTACA",    9989);

    //trie.insert("CA",    10);        //    GATTACA    à {42}
    //trie.insert("GA",    42);        //    GATTACA    à {42}
    trie.insert("GKb", 17);       //    GATTACA    à {42,    17}
    trie.insert("GKb", 42);
    trie.insert("GKb", 5);
    trie.insert("GKjjjjjjjjjjjiiohiguigfufuyfuyfb", 56);
    trie.insert("GKjjjjjjjjjjjiiohiguigfuguyfuyfb", 999);

    trie.insert("jKa", 999);

    trie.insert("GKa", 100);
    trie.insert("GKa", 196);
    trie.insert("Gob", 888);

    trie.insert("KKT", 42);
    
    //trie.print();
    vector<int> temp = trie.find("GATTACA", false);//    GATTACA    à {42,    17,    42}
    for (vector<int>::iterator it = temp.begin();
         it != temp.end(); ++it)
        cout << (*it) << " ";
    cout<<endl;
    
    trie.reset();
    
    trie.insert("Gob", 888);

    vector<int> tempr = trie.find("GATTACA", false);//    GATTACA    à {42,    17,    42}
    for (vector<int>::iterator it = tempr.begin();
         it != tempr.end(); ++it)
        cout << (*it) << " ";*/
   /* string filename = "/Users/yunhuima/Documents/CS32/Gee-nomics/data/test.txt";

    ifstream strm(filename);
    if(!strm)
    {
        cout << "Cannot open " << filename << endl;
        return 0;
    }
    vector<Genome> vg;
    bool success = Genome::load(strm, vg);
    if(success)
    {
        cout << "Loaded " <<vg.size()<<" genomes successfully:" <<endl;
        for(int k = 0; k != vg.size(); k++)
            cout << vg[k].length() << " " << vg[k].name() << endl;
    }
    else
        cout << "Error loading genome data"<<endl;
    */
    
    Genome g("oryx",
             "GCTCGGNACACATCCGCCGCGGACGGGACGGGATTCGGGCTGTCGATTGTCTCACAGATCGTCGACGTACATGACTGGGA");
    
    string f1, f2, f3;
    bool result1 = g.extract(0, 5, f1);     //    result1    =    true,    f1    =    “GCTCG”;
    bool result2 = g.extract(74, 6, f2); //    result2 =    true,    f2 =    “CTGGGA”;
    bool result3 = g.extract(74, 7, f3); //    result3 =    false,    f3 is    unchanged
    
    cout << result3 <<endl;
    return 0;
}

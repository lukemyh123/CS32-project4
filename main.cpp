#include "provided.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <cstdlib>
using namespace std;

// Change the string literal in this declaration to be the path to the
// directory that contains the genome data files we provide, e.g.,
// "Z:/CS32/Geenomics/data" or "/Users/fred/cs32/Geenomics/data"

int main()
{
    Genome g1("Genome1", "CGGTGTACNACGACTGGGGATAGAATATCTTGACGTCGTACCGGTTGTAGTCGTTCGACCGAAGGGTTCCGCGCCAGTAC");
    Genome g2("Genome2", "TAACAGAGCGGTNATATTGTTACGAATCACGTGCGAGACTTAGAGCCAGAATATGAAGTAGTGATTCAGCAACCAAGCGG");
    Genome g3("Genome3", "TTTTGAGCCAGCGACGCGGCTTGCTTAACGAAGCGGAAGAGTAGGTTGGACACATTNGGCGGCACAGCGCTTTTGAGCCA");
    
    GenomeMatcher temp(4);
    temp.addGenome(g1);
    temp.addGenome(g2);
    temp.addGenome(g3);

    
    std::vector<DNAMatch> matches;
    bool result;
    result = temp.findGenomesWithThisDNA("GAAG", 5, false, matches);

    for(std::vector<DNAMatch>::iterator it = matches.begin(); it!=matches.end(); it++)
    {
        cout << (*it).genomeName << "  " << (*it).length << " " << (*it).position << endl;
    }
}

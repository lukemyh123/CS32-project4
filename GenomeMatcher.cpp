#include "provided.h"
#include "Trie.h"
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
using namespace std;

class GenomeMatcherImpl
{
public:
    GenomeMatcherImpl(int minSearchLength);
    //~GenomeMatcherImpl();
    void addGenome(const Genome& genome);
    int minimumSearchLength() const;
    bool findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const;
    bool findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const;
private:
    int m_minSearchLength;  //for findGenomesWithThisDNA()
    
    struct GenomeAndPos
    {
        string genome_name;
        int pos;
    };
    
    vector<Genome> m_genome;
    Trie<GenomeAndPos> trie;
    void whatPushBack(vector<DNAMatch>& matches, DNAMatch new_match) const;
    void push_backHelper(vector<DNAMatch>& matches, DNAMatch new_match, int minimumLength)  const;
    void check_sequence(bool exactMatchOnly, int& length, int& misMatches);
    //void whatPushBack(vector<DNAMatch> matches, DNAMatch new_match) const;
};

GenomeMatcherImpl::GenomeMatcherImpl(int minSearchLength)
{
    m_minSearchLength = minSearchLength;
}

void GenomeMatcherImpl::addGenome(const Genome& genome)
{
    string whole_sequence;
    genome.extract(0, genome.length(), whole_sequence);
    
    m_genome.push_back(genome);

    if (minimumSearchLength() >= genome.length())
    {
        string dna_sequency;
        if (genome.extract(0, minimumSearchLength(), dna_sequency))
        {
            GenomeAndPos temp;
            temp.genome_name = genome.name();
            temp.pos = 0;
            trie.insert(dna_sequency, temp);
        }
    }
    else
    {
        for (int i = 0; i <= (genome.length() - minimumSearchLength()); i++)
        {
            string dna_sequency;
            if (genome.extract(i, minimumSearchLength(), dna_sequency))
            {
                GenomeAndPos temp;
                temp.genome_name = genome.name();
                temp.pos = i;
                trie.insert(dna_sequency, temp);
            }
        }
    }
}

int GenomeMatcherImpl::minimumSearchLength() const
{
    return m_minSearchLength;
}

void GenomeMatcherImpl::whatPushBack(vector<DNAMatch>& matches, DNAMatch new_match) const
{
    if(matches.size()==0)
        matches.push_back(new_match);

    bool temp1 = false; //using for not adding same name same length genome
    bool temp2 = false; //true if it found same name, different length genome

    for (vector<DNAMatch>::iterator it = matches.begin(); it != matches.end(); ++it)
    {
        if((*it).length == new_match.length)
        {
            if((*it).genomeName == new_match.genomeName)
                temp1 = true;
        }
        if((*it).genomeName == new_match.genomeName)
        {
            if((*it).length < new_match.length)
            {
                (*it).position = new_match.position;
                (*it).length = new_match.length;
                temp2 = true;
            }
            else
                return;
        }
    }
    if(!temp1 && !temp2)
        matches.push_back(new_match);
}


bool GenomeMatcherImpl::findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const
{
    if(fragment.size() < minimumLength)
        return false;
    if (minimumLength < minimumSearchLength())
        return false;
    
    string prefi_sequence;
    bool extract_bool = true;
    bool not_match = false;
    int length = 0;
    int misMatches = 0;
    for (int i = 0; i < minimumSearchLength(); i++)
    {
        prefi_sequence += fragment[i];
    }
    
    if (fragment.size() == minimumSearchLength())
    {
        vector<GenomeAndPos> temp = trie.find(prefi_sequence, exactMatchOnly);
        for (vector<GenomeAndPos>::iterator it = temp.begin(); it != temp.end(); ++it)
        {
            DNAMatch new_match;
            new_match.genomeName = (*it).genome_name;
            new_match.position = (*it).pos;
            new_match.length = minimumLength;
            whatPushBack(matches, new_match);
        }
    }
    
    if (fragment.size() > minimumSearchLength())
    {
        vector<GenomeAndPos> temp = trie.find(prefi_sequence, exactMatchOnly);
        for (vector<GenomeAndPos>::iterator it = temp.begin(); it != temp.end(); ++it)
        {
            string match_sequence;
            for (int i=0; i<m_genome.size(); i++)
            {
                if(m_genome[i].name()==(*it).genome_name)
                   extract_bool = m_genome[i].extract((*it).pos, fragment.size(), match_sequence);
            }
            if(extract_bool == false) //if extract return false; then return false;
                return false;
            
            for (int i = 0; i < minimumLength; i++)  //check the minimumLength first
            {
                if (exactMatchOnly == true)
                {
                    if (match_sequence[i] == fragment[i])
                        length++;
                    else
                    {
                        length++;
                        misMatches++;
                    }
                }
                else if(exactMatchOnly == false)
                {
                    if (match_sequence[i] == fragment[i])
                        length++;
                    else if(match_sequence[i] != fragment[i])
                    {
                        length++;
                        misMatches++;
                    }
                }
            }
            
            if(exactMatchOnly == true)
            {
                if(misMatches < 1)
                {
                    for (int j = minimumLength; j < fragment.size(); j++)   //check the rest sequence
                    {
                        if (exactMatchOnly == true)
                        {
                            if (match_sequence[j] == fragment[j])
                                length++;
                            else
                                break;
                        }
                        else if(exactMatchOnly == false)
                        {
                            if (match_sequence[j] == fragment[j])
                                length++;
                            else if(match_sequence[j] != fragment[j])
                            {
                                break;
                            }
                        }
                    }
                }
            }
            if(exactMatchOnly == false)
            {
               if(misMatches < 2)
                {
                    for (int j = minimumLength; j < fragment.size(); j++)   //check the rest sequence
                    {
                        if (exactMatchOnly == true)
                        {
                            if (match_sequence[j] == fragment[j])
                                length++;
                            else
                                break;
                        }
                        else if(exactMatchOnly == false)
                        {
                            if (match_sequence[j] == fragment[j])
                                length++;
                            else if(match_sequence[j] != fragment[j])
                            {
                                break;
                            }
                        }
                    }
                }
            }

            
            DNAMatch new_match;
            new_match.genomeName = (*it).genome_name;
            new_match.position = (*it).pos;
            new_match.length = length;
            if(exactMatchOnly == true && misMatches < 1)
                whatPushBack(matches, new_match);
            
            if(exactMatchOnly == false && misMatches < 2)
                whatPushBack(matches, new_match);
            
            length = 0;  //reset them for the next for loop
            misMatches = 0;
            extract_bool = true;
            not_match = false;
        }
        
    }
    
    return true;
    
    //DNAMatch *new_match = new DNAMatch;
    //new_match->genomeName = name;
    //new_match->position = position;
    //new_match->length = length;
    //matches.push_back(new_match);
    
}

bool GenomeMatcherImpl::findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const
{
    return false;  // This compiles, but may not be correct
}

//******************** GenomeMatcher functions ********************************

// These functions simply delegate to GenomeMatcherImpl's functions.
// You probably don't want to change any of this code.

GenomeMatcher::GenomeMatcher(int minSearchLength)
{
    m_impl = new GenomeMatcherImpl(minSearchLength);
}

GenomeMatcher::~GenomeMatcher()
{
    delete m_impl;
}

void GenomeMatcher::addGenome(const Genome& genome)
{
    m_impl->addGenome(genome);
}

int GenomeMatcher::minimumSearchLength() const
{
    return m_impl->minimumSearchLength();
}

bool GenomeMatcher::findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const
{
    return m_impl->findGenomesWithThisDNA(fragment, minimumLength, exactMatchOnly, matches);
}

bool GenomeMatcher::findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const
{
    return m_impl->findRelatedGenomes(query, fragmentMatchLength, exactMatchOnly, matchPercentThreshold, results);
}

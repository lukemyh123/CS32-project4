#include "provided.h"
#include "Trie.h"
#include <string>
#include <vector>
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
    void findRelatedGenomesHelper(vector<GenomeMatch>& result, GenomeMatch new_GenomeMatch, double matchPercentThreshold) const;
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
                    for (int j = minimumLength; j < match_sequence.size(); j++)   //check the rest sequence
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
                                break;
                        }
                    }
                }
            }
            if(exactMatchOnly == false)
            {
               if(misMatches < 2)
                {
                    for (int j = minimumLength; j < match_sequence.size(); j++)   //check the rest sequence
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
                                if(misMatches == 0)
                                    length++;
                                else if(misMatches == 1)
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
    
    if(matches.size() != 0)
        return true;
    else
        return false;
}

void GenomeMatcherImpl::findRelatedGenomesHelper(vector<GenomeMatch>& matches, GenomeMatch new_GenomeMatch, double matchPercentThreshold) const
{
    if(matches.size() == 0)
    {
        if(new_GenomeMatch.percentMatch >= matchPercentThreshold/100)
            matches.push_back(new_GenomeMatch);
    }
    
    if(matches.size() != 0)
    {
        for (vector<GenomeMatch>::iterator it = matches.begin(); it != matches.end(); ++it)
        {
            if((*it).genomeName == new_GenomeMatch.genomeName)
            {
                if(new_GenomeMatch.percentMatch >= matchPercentThreshold/100)
                {
                    (*it).percentMatch += new_GenomeMatch.percentMatch;
                    return;
                }
            }
        }
        if(new_GenomeMatch.percentMatch >= matchPercentThreshold/100)
            matches.push_back(new_GenomeMatch);
    }
}

bool GenomeMatcherImpl::findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const
{
    if(fragmentMatchLength < minimumSearchLength())
        return false;
    
    vector<DNAMatch> matches;
    int counter = 0;
    bool extract_success;
    for(int i=0; i<query.length(); i++)
    {
        string sub_sequence;
       // string match_sequence;
        
        extract_success = query.extract(i*fragmentMatchLength, fragmentMatchLength, sub_sequence);
        if(extract_success == true)
        {
            if(findGenomesWithThisDNA(sub_sequence, fragmentMatchLength, exactMatchOnly, matches))
            {
                for(int j=0; j<matches.size(); j++)
                {
                    GenomeMatch new_GenomeMatch;
                    new_GenomeMatch.genomeName = matches[i].genomeName;
                    counter += matches[i].length;
                    new_GenomeMatch.percentMatch = counter/fragmentMatchLength;
                    findRelatedGenomesHelper(results,new_GenomeMatch, matchPercentThreshold);
                    counter = 0; //reset the counter;
                }
            }
        }
    }
    
   if(results.size() != 0)
        return true;
    else
        return false;
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

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
	void addGenome(const Genome& genome);
	int minimumSearchLength() const;
	bool findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const;
	bool findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const;
	
	void test();
private:
	int m_minSearchLength;  //for findGenomesWithThisDNA()

	struct nameAndPos
	{
		string genome_name;
		int pos;
	};

	Trie<nameAndPos*> trie;

};

void GenomeMatcherImpl::test()
{
	vector<nameAndPos*> temp = trie.find("GAAG", true);
	for (vector<nameAndPos*>::iterator it = temp.begin(); it != temp.end(); ++it)
		cout << (*it)->genome_name << endl;
}

GenomeMatcherImpl::GenomeMatcherImpl(int minSearchLength)
{
	m_minSearchLength = minSearchLength;
}

void GenomeMatcherImpl::addGenome(const Genome& genome)
{
	if (minimumSearchLength() >= genome.length())
	{
		string dna_sequency;
		if (genome.extract(0, minimumSearchLength(), dna_sequency))
		{
			nameAndPos* temp = new nameAndPos;
			temp->genome_name = genome.name();
			temp->pos = 0;
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
				nameAndPos* temp = new nameAndPos;
				temp->genome_name = genome.name();
				temp->pos = i;
				trie.insert(dna_sequency, temp);
			}
		}
	}
}

int GenomeMatcherImpl::minimumSearchLength() const
{
	return m_minSearchLength;
}

bool GenomeMatcherImpl::findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const
{
	if(fragment.size() < minimumLength)
		return false;
	if (minimumLength < minimumSearchLength())
		return false;

	string prefi_sequence;
	for (int i = 0; i < minimumSearchLength(); i++)
	{
		prefi_sequence += fragment[i];
	}

	/*vector<int> temp = trie.find(prefi_sequence, true);
	for (vector<int>::iterator it = temp.begin(); it != temp.end(); ++it)
		cout << (*it) << endl;*/

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

void GenomeMatcher::test()
{
	m_impl->test();
}

bool GenomeMatcher::findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const
{
	return m_impl->findGenomesWithThisDNA(fragment, minimumLength, exactMatchOnly, matches);
}

bool GenomeMatcher::findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const
{
	return m_impl->findRelatedGenomes(query, fragmentMatchLength, exactMatchOnly, matchPercentThreshold, results);
}
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
private:
	int m_minSearchLength;  //for findGenomesWithThisDNA()

	struct nameAndPos
	{
		string genome_name;
		int pos;
	};

	Trie<nameAndPos*> trie;

	Trie<Genome> trie_new;

};

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

			/*string sub_sequency;
			genome.extract(0, genome.length(), sub_sequency);
			Genome g1(genome.name(), sub_sequency);
			trie_new.insert(dna_sequency, g1);*/
			
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

	if (minimumLength == minimumSearchLength())
	{
		vector<nameAndPos*> temp = trie.find(prefi_sequence, exactMatchOnly);
		for (vector<nameAndPos*>::iterator it = temp.begin(); it != temp.end(); ++it)
		{
			//cout << (*it)->genome_name << endl;
			DNAMatch *new_match = new DNAMatch;
			new_match->genomeName = (*it)->genome_name;
			new_match->position = (*it)->pos;
			new_match->length = minimumLength;
			matches.push_back(*new_match);
		}
	}

	if (minimumLength > minimumSearchLength())
	{
		vector<nameAndPos*> temp = trie.find(prefi_sequence, exactMatchOnly);
		for (vector<nameAndPos*>::iterator it = temp.begin(); it != temp.end(); ++it)
		{
			//cout << (*it)->genome_name << endl;
			string rest_sequence;
			int i = (*it)->pos;
		}
	}
	
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
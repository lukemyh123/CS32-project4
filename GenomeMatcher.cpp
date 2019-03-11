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
		Genome *m_genome;
		int pos;
	};

	Trie<GenomeAndPos> trie;
};

GenomeMatcherImpl::GenomeMatcherImpl(int minSearchLength)
{
	m_minSearchLength = minSearchLength;
}

void GenomeMatcherImpl::addGenome(const Genome& genome)
{
	string whole_sequence;
	genome.extract(0, genome.length(), whole_sequence);

	if (minimumSearchLength() >= genome.length())
	{
		string dna_sequency;
		if (genome.extract(0, minimumSearchLength(), dna_sequency))
		{
			GenomeAndPos temp;
			Genome *newTemp = new Genome(genome);
			temp.m_genome = newTemp;
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
				Genome *newTemp = new Genome(genome);
				temp.m_genome = newTemp;
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

bool GenomeMatcherImpl::findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const
{
	if(fragment.size() < minimumLength)
		return false;
	if (minimumLength < minimumSearchLength())
		return false;

	string prefi_sequence;
	bool alreadyHaveGenomeWithSameLength = false;
	int length = 0;
	int misMatch = 0;
	for (int i = 0; i < minimumSearchLength(); i++)
	{
		prefi_sequence += fragment[i];
	}

	if (minimumLength == minimumSearchLength())
	{
		vector<GenomeAndPos> temp = trie.find(prefi_sequence, exactMatchOnly);
		for (vector<GenomeAndPos>::iterator it = temp.begin(); it != temp.end(); ++it)
		{
			DNAMatch new_match;
			new_match.genomeName = (*it).m_genome->name();
			new_match.position = (*it).pos;
			new_match.length = minimumLength;
			matches.push_back(new_match);
		}
	}

	if (minimumLength > minimumSearchLength())
	{
		vector<GenomeAndPos> temp = trie.find(prefi_sequence, exactMatchOnly);
		for (vector<GenomeAndPos>::iterator it = temp.begin(); it != temp.end(); ++it)
		{
			//cout << (*it).m_genome->name() << " " <<(*it).pos << endl;
			string rest_sequence;
			if ((*it).m_genome->extract((*it).pos, fragment.size(), rest_sequence))
			{
				for (int i = 0; i < fragment.size(); i++)
				{
					if (exactMatchOnly == true)
					{
						if (rest_sequence[i] == fragment[i])
							length++;
						else
							break;
					}
					if (exactMatchOnly == false)
					{
						if (rest_sequence[i] == fragment[i])
							length++;
						else if (rest_sequence[i] != fragment[i])
						{
							length++;
							misMatch++;
						}
						if (misMatch == 2)
							break;
					}
				}
				if (misMatch != 2)
				{
					DNAMatch new_match;
					new_match.genomeName = (*it).m_genome->name();
					new_match.position = (*it).pos;
					new_match.length = length;
					for (vector<DNAMatch>::iterator nit = matches.begin(); nit != matches.end(); ++nit)
					{
						if ((*nit).genomeName != (*it).m_genome->name())
							alreadyHaveGenomeWithSameLength = true;
					}
					if(alreadyHaveGenomeWithSameLength == false)
						matches.push_back(new_match);

					alreadyHaveGenomeWithSameLength = false;
				}
				length = 0;
				misMatch = 0;
			}
			
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
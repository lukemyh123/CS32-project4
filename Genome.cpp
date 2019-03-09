#include "provided.h"
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <istream>
using namespace std;

class GenomeImpl
{
public:
    GenomeImpl(const string& nm, const string& sequence);
    static bool load(istream& genomeSource, vector<Genome>& genomes);
    int length() const;
    string name() const;
    bool extract(int position, int length, string& fragment) const;
private:
    string m_name;
    string m_sequence;
    int m_length;
};

GenomeImpl::GenomeImpl(const string& nm, const string& sequence)
{
    m_name = nm;
    m_sequence = sequence;
}

bool GenomeImpl::load(istream& genomeSource, vector<Genome>& genomes)
{
    string s;
    string name;
    string dna;
    bool isfirst = true;
    while(getline(genomeSource, s))
    {
        if(s.at(0) == '>')
        {
            if ( !isfirst) {
                Genome *new_genome = new Genome(name, dna);
                genomes.push_back(*new_genome);
            }
            else isfirst = false;
                
            name = s.substr(1);  //name
            dna = "";
        }
        else
        {
            dna += s;  //dna sequency
        }
    }
    Genome *new_genome = new Genome(name, dna);
    genomes.push_back(*new_genome);
    
    //genomes->push_back(s);
    return true;  // This compiles, but may not be correct
}

int GenomeImpl::length() const
{
    return 0;  // This compiles, but may not be correct
}

string GenomeImpl::name() const
{
    return m_sequence;  // This compiles, but may not be correct
}

bool GenomeImpl::extract(int position, int length, string& fragment) const
{
    return false;  // This compiles, but may not be correct
}

//******************** Genome functions ************************************

// These functions simply delegate to GenomeImpl's functions.
// You probably don't want to change any of this code.

Genome::Genome(const string& nm, const string& sequence)
{
    m_impl = new GenomeImpl(nm, sequence);
}

Genome::~Genome()
{
    delete m_impl;
}

Genome::Genome(const Genome& other)
{
    m_impl = new GenomeImpl(*other.m_impl);
}

Genome& Genome::operator=(const Genome& rhs)
{
    GenomeImpl* newImpl = new GenomeImpl(*rhs.m_impl);
    delete m_impl;
    m_impl = newImpl;
    return *this;
}

bool Genome::load(istream& genomeSource, vector<Genome>& genomes)
{
    return GenomeImpl::load(genomeSource, genomes);
}

int Genome::length() const
{
    return m_impl->length();
}

string Genome::name() const
{
    return m_impl->name();
}

bool Genome::extract(int position, int length, string& fragment) const
{
    return m_impl->extract(position, length, fragment);
}

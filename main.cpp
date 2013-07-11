/*
 * main.cpp
 *
 *  Created on: Dec 3, 2012
 *      Author: eli_lab
 */

#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>

const std::string PROGNAME = "fastqSol2Phred";
const std::string USAGE = "Usage: fastqSol2Phred input.fq output.fqs\nTest quality conversion with fastqSol2Phred unittest";
const std::string VERSION = "1.0.0";
const std::string atSymbol = "@";
const std::string plusSymbol = "+";
const int SOLOFFSET = 64;
const int PHREDOFFSET = 33;
const int OFFSETDIFF = PHREDOFFSET - SOLOFFSET;

bool readLine (std::ifstream& f, std::string& s)
{
	s = "";
	char c = ' ';

	while (!f.eof())
	{
		f.get( c );

		if (c == '\n' or f.eof()) { break; }
		else { s += c; }
	}

	return s.length() != 0 ? true : false;
}

std::string convertedScore( std::string const& s)
{
	std::string retString = "";
	
	for (unsigned int ui = 0; ui < s.size(); ++ui)
	{
		retString += static_cast<char>( s[ui] + OFFSETDIFF );
	}

	return retString;
}

void unittest()
{
	// pass
	// sol string BCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^
	// phred string #$%&\'()*+,-./0123456789:;<=>?
	std::string solString = "BCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^";
	std::string phredString = "#$%&\'()*+,-./0123456789:;<=>?";
	if (convertedScore(solString) == phredString)
	{
		std::cout << "Unittest passed!" << std::endl;
		std::exit(0);
	}
	else
	{
		std::cout << "Unittest failed!!!" << std::endl;
		std::exit(1);
	}
}

int main (int argc, char *argv[])
{
	unsigned long int readCount = 0;
	
	std::cout << PROGNAME << " v" << VERSION << std::endl;
	
	if (argc == 1 || argc > 3)
	{
		std::cout << USAGE << std::endl;
		std::exit(0);
	}

	std::string infilename = argv[1];
	
	if (infilename == "unittest")
	{
		unittest();
	}

	std::ifstream INFILE( infilename.c_str(), std::ios::in);

	if (!INFILE.good())
	{
		std::cout << "Error opening input file " << infilename << std::endl;
		std::exit(1);
	}

	std::string outfilename = argv[2];
	std::fstream OUTFILE( outfilename.c_str(), std::ios::out);

	if (!OUTFILE.good())
	{
		std::cout << "Error opening output file " << outfilename << std::endl;
		std::exit(1);
	}

	short int fqLine = 0;
	std::string buffer = "";

	while (!INFILE.eof())
	{
		if (readLine(INFILE, buffer))
		{
			++fqLine;
			if (fqLine == 1 && buffer[0] == atSymbol[0])
			{
				OUTFILE << buffer << "\n";
			}
			else if (fqLine == 2)
			{
				OUTFILE << buffer << "\n";
			}
			else if (fqLine == 3 && buffer[0] == plusSymbol[0])
			{
				OUTFILE << "+\n";
			}
			else if (fqLine == 4)
			{
				fqLine = 0;
				OUTFILE << convertedScore(buffer) << "\n";
				++readCount;
			}
			else
			{
				std::cout << "Input file format error!!!" << std::endl;
				std::exit(1);
			}
		}
	}
	
	INFILE.close();
	OUTFILE.close();
	
	std::cout << readCount << " reads processed" << std::endl;
	
	std::exit(0);
}

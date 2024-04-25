// NEW BOGGLE DRIVER
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <set>
#include <random>
#include <fstream>

#include "boggle.h"

using namespace std;

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		cout << "Usage: boggle-driver <size>" << endl;
		exit(1);
	}

	int size = atoi(argv[1]);

	// Define the test board
	vector<vector<char>> board = {
		{'C', 'A', 'T', 'D', 'O', 'G'},
		{'C', 'A', 'T', 'C', 'O', 'A'},
		{'C', 'A', 'T', 'S', 'E', 'A'},
		{'C', 'A', 'B', 'S', 'O', 'W'},
		{'C', 'A', 'T', 'C', 'O', 'W'},
		{'C', 'A', 'T', 'D', 'O', 'G'}};

	// Print the board
	printBoard(board);

	// Define a default dictionary file
	const string defaultDictionary = "dict.txt";

	// Use the default dictionary if no file is specified
	string dictionaryFile = (argc > 2) ? argv[2] : defaultDictionary;

	// Ensure the dictionary file exists
	ifstream dictfs(dictionaryFile.c_str());
	if (dictfs.fail())
	{
		cout << "Error: Unable to open dictionary file: " << dictionaryFile << endl;
		exit(1);
	}

	// Parse the dictionary and prefixes
	pair<set<string>, set<string>> parsed = parseDict(dictionaryFile);
	set<string> dictionary = parsed.first;
	set<string> prefix = parsed.second;

	// Find words in the test board
	set<string> found = boggle(dictionary, prefix, board);

	// Output the found words
	stringstream os;
	for (auto it = found.begin(); it != found.end(); ++it)
	{
		os << *it << ", ";
	}
	cout << "Found " << found.size() << " words:" << endl;
	cout << os.str().substr(0, os.str().size() - 2) << endl;
}

// OG BOGGLE DRIVER
/* #include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <set>
#include <random>

#include "boggle.h"

using namespace std;

int main(int argc, char* argv[])
{
	if(argc < 4)
	{
		cout << "Usage: boggle-driver <size> <seed> <dictionary file>" << endl;
		exit(1);
	}
	int size = atoi(argv[1]);
	int seed = atoi(argv[2]);
	vector<vector<char> > board = genBoard(size, seed);
	printBoard(board);
	pair<set<string>, set<string> > parsed = parseDict(string(argv[3]));
	set<string> dictionary = parsed.first;
	set<string> prefix = parsed.second;
	set<string> found = boggle(dictionary, prefix, board);
	set<string>::iterator it;
	stringstream os;
	for(it=found.begin();it != found.end(); ++it)
	{
		os << *it << ", ";
	}
	cout << "Found " << found.size() << " words:" << endl;
	cout << os.str().substr(0,os.str().size()-2) << endl;
}
*/
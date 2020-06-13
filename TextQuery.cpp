#include "TextQuery.h"
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <regex>
using namespace std;

TextQuery::TextQuery(ifstream &is): file(new vector<string>)
{
    string text;
    while (getline(is, text)) {       // for each line in the file
		file->push_back(text);        // remember this line of text
		int n = file->size() - 1;     // the current line number
		istringstream line(text);     // separate the line into words
		string word;               
		while (line >> word) {        // for each word in that line
            auto &lines = wm[word]; // lines is a shared_ptr 
            if (!lines) // that pointer is null the first time we see word
                lines.reset(new set<line_no>); // allocate a new set
            lines->insert(n);      // insert this line number
		}
	}
}

QueryResult
TextQuery::query(const string &sought) const
{
	// we'll return a pointer to this set if we don't find sought
	static shared_ptr<set<line_no>> nodata(new set<line_no>); 
    // use find and not a subscript to avoid adding words to wm!
    auto loc = wm.find(sought);
	if (loc == wm.end()) 
		return QueryResult(sought, nodata, file);  // not found
	else 
		return QueryResult(sought, loc->second, file);
}

// debugging routine
void TextQuery::display_map()
{
    auto iter = wm.cbegin(), iter_end = wm.cend();
    // for each word in the map
    for ( ; iter != iter_end; ++iter) {
        cout << "word: " << iter->first << " {";
        // fetch location vector as a const reference to avoid copying it
        auto text_locs = iter->second;
        auto loc_iter = text_locs->cbegin(),
                        loc_iter_end = text_locs->cend();
        // print all line numbers for this word
        while (loc_iter != loc_iter_end)
        {
            cout << *loc_iter;
            if (++loc_iter != loc_iter_end)
                 cout << ", ";

         }
         cout << "}\n";  // end list of output this word
    }
    cout << endl;  // finished printing entire map
}

std::ostream &print(std::ostream &os, const QueryResult &qr)
{
  os << "\"" << qr.sought << "\"" << " occurs " << 
    qr.lines->size() << " times:" <<std::endl;

  for (auto num : *qr.lines)
  {
    os << "\t(line " << num + 1 << ") " 
      << *(qr.file->begin() + num) << std::endl;
  }

  return os;
}

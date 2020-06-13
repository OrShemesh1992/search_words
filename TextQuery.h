// This file contains code from "C++ Primer, Fifth Edition",
// by Stanley B.Lippman, Josee Lajoie, and Barbara E. Moo

#ifndef TEXTQUERY_H
#define TEXTQUERY_H

#include <memory>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <fstream>
#include "QueryResult.h"

class QueryResult; // declaration needed for return type in the query function
class TextQuery {
public:
	using line_no = std::vector<std::string>::size_type;
	TextQuery(std::ifstream&);
    QueryResult query(const std::string&) const; 
    void display_map(); // debugging aid
private:
	// pointer to a vector of lines of the input file
    std::shared_ptr<std::vector<std::string>> file; 
    // maps each word to a pointer to the set of lines in which that word appears
    std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;  
};
std::ostream &print(std::ostream &os, const QueryResult &qr);
#endif

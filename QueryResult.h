#ifndef QUERYRESULT_H
#define QUERYRESULT_H

#include <string>
#include <vector>
#include <set>
#include <iostream>

class QueryResult {
friend std::ostream& print(std::ostream&, const QueryResult&);
  public:
	using line_no = std::vector<std::string>::size_type;
	QueryResult(std::string s, 
	            std::shared_ptr<std::set<line_no>> p, 
	            std::shared_ptr<std::vector<std::string>> f):
		sought(s), lines(p), file(f) { }
		
	std::set<line_no>::iterator begin() {return lines->begin();}
	std::set<line_no>::iterator end() {return lines->end();}
	std::shared_ptr<std::vector<std::string>> get_file() { return file; }		
private:
	std::string sought;  // word this query represents
	std::shared_ptr<std::set<line_no>> lines; // lines it's on
	std::shared_ptr<std::vector<std::string>> file;  //input file
};
#endif

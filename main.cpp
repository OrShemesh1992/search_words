#include <iostream>
#include <stdexcept>
#include "Query.h"
#include "TextQuery.h"
#include "QueryResult.h"
using namespace std;

int main(int argc, char **argv)
{
  ifstream infile(argv[1]);
  if (!infile) { cerr << "No input file!" << endl; exit(1); }
  TextQuery tq(infile);
//  tq.display_map();
  while (true)
  {
    cout << "Enter one or two words to look for, or q to quit:" << endl;
    string line;
    getline(cin, line);
    if (line.empty() || line == "q") break;
	shared_ptr<QueryBase> q;
	try {
      q = QueryBase::factory(line);
	}
	catch( const invalid_argument& e ) {
      cout << e.what() << endl;
	  continue;
	}
    print(cout, q->eval(tq)) << endl;
  }
  exit(0);
}

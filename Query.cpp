#include "Query.h"
#include "TextQuery.h"
#include <memory>
#include <set>
#include <algorithm>
#include <iostream>
#include <cstddef>
#include <iterator>
#include <stdexcept>
#include <regex>
using namespace std;
////////////////////////////////////////////////////////////////////////////////
std::shared_ptr<QueryBase> QueryBase::factory(const string& l)
{
if(/* Regular Expression of l matches WordQuery*/)
	return std::shared_ptr<QueryBase>(new WordQuery(/* */));
/* Other Queries . . . */
}
////////////////////////////////////////////////////////////////////////////////
QueryResult AndQuery::eval (const TextQuery& text) const
{
   QueryResult left_result = text.query(lhs);
   QueryResult right_result = text.query(rhs);
   auto ret_lines = std::make_shared<std::set<line_no>>();
   std::set_intersection(left_result.begin(), left_result.end(),
      right_result.begin(), right_result.end(), 
      std::inserter(*ret_lines, ret_lines->begin()));
   return QueryResult(rep(), ret_lines, left_result.get_file());
}

QueryResult OrQuery::eval(const TextQuery &text) const
{
   QueryResult left_result = text.query(lhs);
   QueryResult right_result = text.query(rhs);
   auto ret_lines = 
      std::make_shared<std::set<line_no>>(left_result.begin(), left_result.end());
   ret_lines->insert(right_result.begin(), right_result.end());
   return QueryResult(rep(), ret_lines, left_result.get_file());
}
/////////////////////////////////////////////////////////
QueryResult BesideQuery::eval (const TextQuery& text) const
{

}
/////////////////////////////////////////////////////////

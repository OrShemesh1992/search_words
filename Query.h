#ifndef QUERY_H
#define QUERY_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <memory>
#include <regex>
#include "TextQuery.h"
#include "QueryResult.h"

class QueryBase {
public:
   using line_no = QueryResult::line_no;
   virtual ~QueryBase() = default;
   virtual QueryResult eval(const TextQuery&) const = 0;
   virtual std::string rep() const = 0; 
   static std::shared_ptr<QueryBase> factory(const std::string& s);
};

class WordQuery : public QueryBase {
public:
   WordQuery(const std::string &s): query_word(s) { }
   QueryResult eval(const TextQuery &t) const
      { return t.query(query_word); }
   std::string rep() const { return query_word; }
private:
   std::string query_word;
};

class BinaryQuery : public QueryBase {
protected:
   BinaryQuery(const std::string &l, const std::string &r): 
          lhs(l), rhs(r) { }
   std::string lhs, rhs;
};

class AndQuery : public BinaryQuery {
public:
   AndQuery(const std::string &left_string, const std::string &right_string) :
      BinaryQuery(left_string, right_string) { }
   QueryResult eval(const TextQuery&) const;
   std::string rep() const 
      { return lhs + " AND " + rhs; }
};

class OrQuery: public BinaryQuery {
public:
   OrQuery(const std::string &left_string, const std::string &right_string):
      BinaryQuery(left_string, right_string) { }
   QueryResult eval(const TextQuery&) const;
   std::string rep() const 
      { return lhs + " OR " + rhs; }
};

class BesideQuery : public AndQuery {
public:
   BesideQuery(const std::string &left_string, const std::string &right_string):
      AndQuery(left_string, right_string) { }
   QueryResult eval(const TextQuery&) const;
   std::string rep() const 
      { return lhs + " BESIDE " + rhs; }
};
#endif

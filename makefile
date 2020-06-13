a.out: main.cpp TextQuery.cpp Query.cpp TextQuery.h Query.h QueryResult.h
	g++ -g -std=c++11 main.cpp TextQuery.cpp Query.cpp


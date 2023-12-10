#include <iostream>
#include "sql_query_builder.h"

//"SELECT name, phone FROM students WHERE id=42 AND name=John;"

std::string parse_select_query(std::string& query) {
	std::vector <std::string> fields;
    return "parsed\n";
}

//void static_assert(const Query& q, std::string& query) {
//	std::cout << "Query built:\n";
//	auto itr = q.rows.begin();
//	for (; itr != q.rows.begin(); ++itr) {
//		//if ()
//	}
//}

void check(const int b)
{
    const int a = 3;

    static_assert(a != 0, "not zero");
};


int main() {
    SqlSelectQueryBuilder query_builder;
    query_builder.AddColumn("name").AddColumn("phone");
    query_builder.AddFrom("students");
    query_builder.AddWhere("id", "42").AddWhere("name", "John");
    query_builder.BuildQuery();

   /* static_assert(query_builder.BuildQuery(),
        "SELECT name, phone FROM students WHERE id=42 AND name=John;");*/
    check(17);
	return 0;
}
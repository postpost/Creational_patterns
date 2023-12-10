#pragma once
#include <iostream>
#include <map>
#include <vector>



struct Query {
	std::string table_name_ ="";
	size_t id = 0;
	std::map<std::string, std::string> rows;
};

class SqlSelectQueryBuilder
{
public:
	const explicit SqlSelectQueryBuilder() noexcept {
		query.rows.insert(std::make_pair("id", " "));
	};
	const bool BuildQuery() noexcept {
		std::cout << "Query built:\n";
		if (!query.rows.empty()) {
			std::cout << "Table " << query.table_name_ << " was built\n";
			for (const auto& row : query.rows) {
				std::cout << row.first << ": " << row.second << std::endl;
			}
			return true;
		}
		else
			std::cout << "Table " << query.table_name_ << " is empty\n";
		return false;
	};

	SqlSelectQueryBuilder& AddColumn(const std::string& col_name) noexcept {
		query.rows.insert(std::make_pair(col_name, " "));
		return *this;
	};

	SqlSelectQueryBuilder& AddFrom(const std::string& table_name) noexcept {
		query.table_name_ = table_name;
		return *this;
	}

	//query_builder.AddWhere("id", "42")
	// .AddWhere("name", "John");
	SqlSelectQueryBuilder& AddWhere(const std::string& key, const std::string& val) {
		for (const auto& el : query.rows) {
			if (el.first == key) {
				query.rows[key] = val;
			}
			else 
				query.rows.insert(std::make_pair(key, val));
		}
		return *this;
	};

private:
	Query query;

};


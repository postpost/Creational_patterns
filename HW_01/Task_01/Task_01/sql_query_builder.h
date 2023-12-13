#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <assert.h>

struct Query {
	//explicit Query() = default;
    //Query(const Query&) = default;
	//Query& operator=(const Query&) = default;
	std::string table_name_;
	size_t id = 0;
	std::map<std::string, std::string> rows;
	std::vector<std::string>& columns_;
};

class SqlSelectQueryBuilder
{
public:
	//SqlSelectQueryBuilder(const SqlSelectQueryBuilder&) = default;
	//SqlSelectQueryBuilder& operator=(const SqlSelectQueryBuilder&) = default;
	explicit SqlSelectQueryBuilder()  noexcept {
		query.rows.insert(std::make_pair("id", " "));
	}
	bool BuildQuery() noexcept {
		//static_assert(checked, " ");
		std::cout << "Query built:\n";
		if (!query.rows.empty()) {
			check_assert = true;
			std::cout << "Table " << query.table_name_ << " was built\n";
			for (const auto& row : query.rows) {
				std::cout << row.first << ": " << row.second << std::endl;
			}
		}
		else {
			throw std::runtime_error("Table is empty!\n");
		}
		return check_assert;
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

	SqlSelectQueryBuilder& AddWhere(const std::map<std::string, std::string>& kv) noexcept {
		for (auto itr = kv.begin(); itr != kv.end(); ++itr) {
			query.rows.insert(std::make_pair(itr->first, itr->second));
		}
		return *this;
	}

	SqlSelectQueryBuilder& AddColumns(const std::vector<std::string>& columns) noexcept {
		for (const auto& col : columns) {
			query.columns_.push_back(col);
		}
		return *this;
	};
private:
	bool check_assert = false;
	Query query;
};


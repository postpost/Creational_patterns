#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <assert.h>

struct Query {
	std::string table_name_;
	size_t id = 0;
	std::map<std::string, std::string> rows;
	std::vector<std::string> columns_;
};

class SqlSelectQueryBuilder
{
public:
	explicit SqlSelectQueryBuilder()  noexcept {
		query.rows.insert(std::make_pair("id", ""));
	}
	std::string BuildQuery() {
		//static_assert(checked, " ");
		std::cout << "Query built:\n";
		if (!query.rows.empty()) {
			for (const auto& col : query.columns_) {
				result_string += col + ", ";
			}
			result_string +=" FROM " + query.table_name_ + " WHERE ";
			for (const auto& row : query.rows) {
				if (!row.second.empty()) {
					result_string += " " + row.first + "=" + row.second + " AND";
				}
			}
		}
		else {
			throw std::runtime_error("Table is empty!\n");
		}
		trim(result_string);
		return result_string;
	};

	void trim(std::string& data) {
			std::reverse(data.begin(), data.end());
			data.erase(std::find(data.begin(), data.end(), ','));
			std::reverse(data.begin(), data.end());
			auto it = data.end() - 4;
			data.erase(it, data.end());
	}

	SqlSelectQueryBuilder& AddColumn(const std::string& col_name) noexcept {
		query.columns_.push_back(col_name);
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
	std::string result_string = "SELECT ";
	Query query;
};

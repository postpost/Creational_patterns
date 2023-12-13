#pragma once
#include <iostream>
#include <fstream>

class LogCommand {
public:
	virtual ~LogCommand() = default;
	virtual void print(const std::string& message) = 0;

};

class LogInConsole : public LogCommand {
public:
	//LogInConsole() :LogCommand() {}
	void print(const std::string& message) {
		std::cout << "Your message is: " << message << std::endl;
	}
};

class LogInFile : public LogCommand {
public:
	LogInFile(const std::string& file_path) : file_path_(file_path) {}
	~LogInFile() {
	}
	void print(const std::string& message) override {
		std::ofstream fout(file_path_, std::ios::app);
		fout << message;
		std::cout << "File was written\n";
		fout.close();
	}
private:
	std::string file_path_;
};

void print(LogCommand& where, const std::string& msg) {
	where.print(msg);
}

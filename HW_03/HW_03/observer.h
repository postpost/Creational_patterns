#pragma once
#include <iostream>

class Observer {
public:
	Observer() = default;
	virtual ~Observer() = default;
	virtual void onWarning(const std::string& message) {};
	virtual void onError(const std::string& message) {};
	virtual void onFatalError(const std::string& message) {};
};

class ObserverOnWarning :public Observer {
public:
	ObserverOnWarning() = default;
	~ObserverOnWarning() = default;
	void onWarning(const std::string& message) override;

};

class ObserverOnError :public Observer {
public:
	ObserverOnError(const std::string& path);
	~ObserverOnError() = default;
	void onError(const std::string& message) override;
private:
	std::string file_path_;
};

class ObserverOnFatalError :public Observer {
public:
	ObserverOnFatalError(const std::string& path);
	~ObserverOnFatalError() = default;
	void onFatalError(const std::string& message) override;
private:
	std::string file_path_;
};


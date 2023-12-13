#pragma once
#include "observer.h"
#include <iostream>
#include <vector>
#include <memory>

class Observed {
public:
	Observed() = default;
	void AddObserver(std::weak_ptr<Observer> observer);
	void warning(const std::string& message) const;
	void error(const std::string& message) const;
	void fatalError(const std::string& message) const;

private:
	std::vector <std::weak_ptr<Observer>> observers_;
};



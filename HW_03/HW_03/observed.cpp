#include "observer.h"
#include "observed.h"
#include <iostream>
#include <vector>
#include <memory>

void Observed::AddObserver(std::weak_ptr<Observer> observer) {
		observers_.push_back(observer);
	}

void Observed::warning(const std::string& message) const {
	for (const auto& observer : observers_) {
		if (auto strong_ptr = observer.lock())
			strong_ptr->onWarning(message);
	}

};

void Observed::error(const std::string& message) const {
	for (const auto& observer : observers_) {
		if (auto strong_ptr = observer.lock())
			strong_ptr->onError(message);
	}
};
void Observed::fatalError(const std::string& message) const {
	for (const auto& observer : observers_) {
		if (auto strong_ptr = observer.lock())
			strong_ptr->onFatalError(message);
	}
};

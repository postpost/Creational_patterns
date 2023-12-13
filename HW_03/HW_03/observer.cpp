#include "observer.h"
#include <iostream>
#include <fstream>

void ObserverOnWarning::onWarning(const std::string& message)  
{
	std::cout << "Attention! Warning!!!\n" << message << std::endl;
};

ObserverOnError::ObserverOnError(const std::string& path) : file_path_(path) {};

void ObserverOnError::onError(const std::string& message)  
{
	std::ofstream fout(file_path_, std::ios::app);
	std::cout << "Attention! Error: \n" << message << std::endl;
	fout << message;
	fout.close();
};

ObserverOnFatalError::ObserverOnFatalError(const std::string& path) :file_path_(path) {};
void ObserverOnFatalError::onFatalError(const std::string& message)
{
	std::ofstream fout(file_path_, std::ios::app);
	std::cout << "Attention! Fatal error: \n" << message << std::endl;
	fout << message;
	fout.close();
};

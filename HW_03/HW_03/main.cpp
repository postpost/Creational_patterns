#include <iostream>
#include <memory>
#include "logger.h"
#include "observed.h"
#include "observer.h"

int main() {
	//Task_01
	LogCommand* log1 = new LogInConsole();
	print(*log1, "Write in console\n");
	delete log1;
	log1 = nullptr;
	log1 = new LogInFile("file.txt");
	print(*log1, "Write in file\n");
	delete log1;

	//Task_02
	Observed* observed = new Observed();
	//Warning
	auto obs_warning = std::make_shared<ObserverOnWarning>();
	observed->AddObserver(obs_warning);
	observed->warning("Se acerca la tormenta del siglo!");

	//Error
	auto obs_error = std::make_shared<ObserverOnError>("file_errors.txt");
	observed->AddObserver(obs_error);
	observed->error("Elegiste el poder!");
	
	//Fatal error
	auto obs_fatal_error = std::make_shared<ObserverOnFatalError>("file_fatal_errors");
	observed->AddObserver(obs_fatal_error);
	observed->fatalError("El poder te destruira!");

	return 0;
}
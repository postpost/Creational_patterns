#include <iostream>
#include <fstream>


class LogMessage {
public:
	virtual ~LogMessage() = default;
	enum Type { WARNING, ERROR, FATAL_ERROR, UKNOWN, };
	virtual Type type() const = 0;
	virtual const std::string& message() const = 0;
};

//messages!
class WarningMsg : public LogMessage {
public:
	WarningMsg(const std::string& msg): message_(msg) {};
	Type type() const override {
		return Type::WARNING;
	}
	const std::string& message() const override {
		return this->message_;
	}
private:
	std::string message_;

};

//messages!
class ErrorMsg : public LogMessage {
public:
	ErrorMsg(const std::string& path, const std::string& msg) : message_(msg), file_path_(path) {};
	Type type() const override {
		return Type::ERROR;
	}
	const std::string& message() const override {
		std::ofstream fout(file_path_, std::ios::app);
		fout << message_;
		fout.close();
		return this->message_;
	}
private:
	std::string message_;
	std::string file_path_;
};


class FatalErrorMsg : public LogMessage {
public:
	FatalErrorMsg(const std::string& msg) : message_(msg) {};
	Type type() const override {
		return Type::FATAL_ERROR;
	}
	const std::string& message() const override {
		return this->message_;
	}
private:
	std::string message_;
};

//messages!
class UknownMsg : public LogMessage {
public:
	UknownMsg(const std::string& msg) : message_(msg){};
	Type type() const override {
		return Type::UKNOWN;
	}
	const std::string& message() const override {
		return nullptr;
	}
private:
	std::string message_;
};

class LogHandler {
public:
	//используем юник, как в прокси, тк только один обработчик может владеть *ключами* в одно время
	explicit LogHandler(std::unique_ptr<LogHandler> next) : next_(std::move(next)) {};
	virtual ~LogHandler() = default;
	//передаем сообщение обработчику
	void receiveMessage(const LogMessage& msg) {
		if (handleMessage(msg)) //если сообщение обработано, то закрываем лавочку
			return;
		
		if (!next_)
			throw std::runtime_error ("Сообщение неподходящего типа\n");
		next_->receiveMessage(msg); //передай другому, только не мне
	}

private:
	virtual bool handleMessage(const LogMessage& message) = 0; //В наследниках реализуем логику по обработке сообщений
	std::unique_ptr<LogHandler> next_; //указатель на обработчицу(ка) (она(_) одна(_) единственная(_))
};

//обработчицы(_)
class WarningHandler :public LogHandler {
public:
	LogHandler::LogHandler; //мы используем конструктор LogHandler
private:
	//проверяем, подходит ли это сообщение по типу
	bool handleMessage(const LogMessage& message) override {
		if (message.type() != message.WARNING)
			return false; //передай другой(му)
		std::cout << message.message() << std::endl;
		return true;
	}
};

class ErrorHandler :public LogHandler {
public:
	using LogHandler::LogHandler;
private:
	bool handleMessage(const LogMessage& message) override {
		if (message.type() != message.ERROR)
			return false;
		message.message();
		return true;
	}
};

class FatalErrorHandler : public LogHandler {
public:
	using LogHandler::LogHandler;
private:
	bool handleMessage(const LogMessage& message) override {
		if (message.type() != message.FATAL_ERROR)
			return false;
		std::cout << "Fatal error! ";
		throw std::runtime_error(message.message());
		return 1;
	}
};

int main() {
	setlocale(LC_ALL, "ru");
	auto warning = std::make_unique<WarningHandler>(nullptr);
	auto error = std::make_unique<WarningHandler>(std::move(warning)); 
	auto fatal = std::make_unique<FatalErrorHandler>(std::move(warning));
	std::string path = "file_errors_01";
	try {
		fatal->receiveMessage(ErrorMsg(path, "Something wrong with the governments\n"));
		fatal->receiveMessage(WarningMsg("Warning!!!Zonda is coming\n"));
		fatal->receiveMessage(FatalErrorMsg("Fatal error. Program must be terminated\n"));
		fatal->receiveMessage(UknownMsg("Sorry. Delivery is postponed\n"));
	}

	catch (std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}
	return 0;
}
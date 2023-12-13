#include <iostream>
#include <fstream>

class Printable
{
public:
    virtual ~Printable() = default;

    virtual std::string printAsHTML() const = 0; //DRY
    virtual std::string printAsText() const = 0; //DRY
    virtual std::string printAsJSON() const = 0; //DRY
    //я бы отдельно создала класс Data с виртуальными saveTo() + print();
    // и от него наследовать все форматы:
    // DataHTML:public Data; DataText:public Data; DataJSON:public Data
    //в каждом из классов реализовать свои методы: saveTo() + print();
};

//1. Single Responsibility: 
// Для каждого класса должно быть определено единственное назначение, у нас их три
 
class Data : public Printable
{
public:
    enum class Format
    {
        kText,
        kHTML,
        kJSON
    };
    //если мы добавим здесь еще одну сущность, то придется исправлять остальные куски кода
    //примерно везде далее

    Data(std::string data, Format format)
        : data_(std::move(data)), format_(format) {}

    std::string printAsHTML() const override
    {
        if (format_ != Format::kHTML) {
            throw std::runtime_error("Invalid format!");
        }
        return "<html>" + data_ + "<html/>";
    }
    std::string printAsText() const override
    {
        if (format_ != Format::kText) {
            throw std::runtime_error("Invalid format!");
        }
        return data_;
    }
    std::string printAsJSON() const override
    {
        if (format_ != Format::kJSON) {
            throw std::runtime_error("Invalid format!");
        }
        return "{ \"data\": \"" + data_ + "\"}";
    }

private:
    std::string data_;
    Format format_;
};

//2. Interface segregation
//разделять интерфейсы на более мелкие тематические, 
// чтобы реализующие их классы не были вынуждены определять методы, 
// которые непосредственно в них не используются

void saveTo(std::ofstream& file, const Printable& printable, Data::Format format)
{
    //если мы добавим еще одну сущность в enum, здесь можно забыть дописать кусок кода 
    //---> воспользоваться методом подстановки Барбары Лисков + открытости/закрытости,
    // расширяя класс для каждого из форматов

    switch (format)
    {
    case Data::Format::kText:
        file << printable.printAsText();
        break;
    case Data::Format::kJSON:
        file << printable.printAsJSON();
        break;
    case Data::Format::kHTML:
        file << printable.printAsHTML();
        break;
    }
}

void saveToAsHTML(std::ofstream& file, const Printable& printable) {
    saveTo(file, printable, Data::Format::kHTML);
}

void saveToAsJSON(std::ofstream& file, const Printable& printable) {
    saveTo(file, printable, Data::Format::kJSON);
}

void saveToAsText(std::ofstream& file, const Printable& printable) {
    saveTo(file, printable, Data::Format::kText);
}

int main() {
	return 0;
}
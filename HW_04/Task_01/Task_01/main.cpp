#include <iostream>
#include <fstream>

class Printable
{
public:
    virtual ~Printable() = default;

    virtual std::string printAsHTML() const = 0; //DRY
    virtual std::string printAsText() const = 0; //DRY
    virtual std::string printAsJSON() const = 0; //DRY
    //� �� �������� ������� ����� Data � ������������ saveTo() + print();
    // � �� ���� ����������� ��� �������:
    // DataHTML:public Data; DataText:public Data; DataJSON:public Data
    //� ������ �� ������� ����������� ���� ������: saveTo() + print();
};

//1. Single Responsibility: 
// ��� ������� ������ ������ ���� ���������� ������������ ����������, � ��� �� ���
 
class Data : public Printable
{
public:
    enum class Format
    {
        kText,
        kHTML,
        kJSON
    };
    //���� �� ������� ����� ��� ���� ��������, �� �������� ���������� ��������� ����� ����
    //�������� ����� �����

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
//��������� ���������� �� ����� ������ ������������, 
// ����� ����������� �� ������ �� ���� ��������� ���������� ������, 
// ������� ��������������� � ��� �� ������������

void saveTo(std::ofstream& file, const Printable& printable, Data::Format format)
{
    //���� �� ������� ��� ���� �������� � enum, ����� ����� ������ �������� ����� ���� 
    //---> ��������������� ������� ����������� ������� ������ + ����������/����������,
    // �������� ����� ��� ������� �� ��������

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
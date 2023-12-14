#include <iostream>
#include <fstream>

class Printable
{
public:
    Printable(const std::string& data) : data_(data) {}
    virtual ~Printable() = default;
    virtual std::string print() const = 0;
protected:
    std::string data_;
 };


class Data{
public:
    ~Data() {
          delete format_;
    }
    enum Format {kText, kHTML, kJSON};
    virtual void saveTo(std::ofstream& file, Printable* printable_) const = 0;
    virtual Format getFormat() const = 0;
    Format* format_{ nullptr };
 };

class HTMLData :public Data {
public:
    HTMLData() {
        format_= new Format(Data::Format::kHTML);
    }
    void saveTo(std::ofstream& file, Printable* printable_) const override {
        file << printable_->print();
    }
    Format getFormat() const override {
        return *format_;
    }
};


class TextData :public Data {
public:
//using Data::Data;
    TextData() {
        format_ = new Format(Data::Format::kText);
    }
    void saveTo(std::ofstream& file, Printable* printable_) const override {
        file << printable_->print();
    }
    Format getFormat() const override {
        return *format_;
    }
};

class JSONData :public Data {
public:
    JSONData() {
        format_ = new Format(Data::Format::kJSON);
    };
    void saveTo(std::ofstream& file, Printable* printable_) const override {
        file << printable_->print();
    }
    Format getFormat() const override {
        return *format_;
    }
};


class PrintAsHTML :public Printable {
public:
    PrintAsHTML(const std::string& data, Data* format) : Printable(data), format_(format) {}
    std::string print() const override {
        std::cout << format_->getFormat() << std::endl; //Exception thrown: read access violation.
                                                        //this->format_ was nullptr.
        if (format_->getFormat() != format_->Format::kHTML)
            throw std::runtime_error("Invalid format!");
        return "<html>" + data_ + "<html/>";
    }
private:
    Data* format_;
};

class PrintAsText :public Printable {
public:
    PrintAsText(const std::string& data) : Printable(data) {}
    std::string print() const override {
        if (format_->getFormat() != format_->Format::kText) {
            throw std::runtime_error("Invalid format!");
        }
        return data_;
    }
private:
    Data* format_;
};

class PrintAsJSON :public Printable {
public:
    PrintAsJSON(const std::string& data) : Printable(data) {}
    std::string print() const override {
        if (format_->getFormat() != format_->Format::kJSON) {
            throw std::runtime_error("Invalid format!");
        }
        return "{ \"data\": \"" + data_ + "\"}";
    }
private:
    Data* format_;
};

void saveTo(std::ofstream& file, Data* data, Printable* printable_) {
    data->saveTo(file, printable_);
}

int main() {

    Data* data = new HTMLData();
    std::ofstream fout("file_format_test");
    Printable* print_html = new PrintAsHTML("print html data", data);
    saveTo(fout, data, print_html);
    fout.close();
    delete data;
    return 0;
}
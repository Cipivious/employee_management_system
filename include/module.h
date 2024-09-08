#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

// Forward declaration of Person class
class Person {
public:
    std::string name;
    std::string job;
    Person(std::string n, std::string j) : name(n), job(j) {}
};

class AbstractModule {
public:
    std::string info;
    std::string tag;
    virtual std::vector<std::string> menu_function() = 0;
    virtual void realize(std::vector<std::string>& args, std::vector<Person>& persons) = 0;
    static std::string read_from_command_line(const std::string& prompt);
    bool worker(std::vector<Person>& persons, const std::string& choice);
};

class AddPersonModule : public AbstractModule {
    public:
    AddPersonModule();
    std::vector<std::string> menu_function() override;
    void realize(std::vector<std::string>& args, std::vector<Person>& persons) override;
};
class CopyPersonModule : public AbstractModule {
    public:
    CopyPersonModule();
    std::vector<std::string> menu_function() override;
    void realize(std::vector<std::string>& args, std::vector<Person>& persons) override;
};
class DeletePersonModule : public AbstractModule {
    public:
    DeletePersonModule();
    std::vector<std::string> menu_function() override;
    void realize(std::vector<std::string>& args, std::vector<Person>& persons) override;
};
class SearchPersonModule : public AbstractModule {
    public:
    SearchPersonModule();
    std::vector<std::string> menu_function() override;
    void realize(std::vector<std::string>& args, std::vector<Person>& persons) override;
};
class EditPersonModule : public AbstractModule {
    public:
    EditPersonModule();
    std::vector<std::string> menu_function() override;
    void realize(std::vector<std::string>& args, std::vector<Person>& persons) override;
};
class DisplayPersonModule : public AbstractModule {
    public:
    DisplayPersonModule();
    std::vector<std::string> menu_function() override;
    void realize(std::vector<std::string>& args, std::vector<Person>& persons) override;
};
class ExitPersonModule : public AbstractModule {
    public:
    ExitPersonModule();
    std::vector<std::string> menu_function() override;
    void realize(std::vector<std::string>& args, std::vector<Person>& persons) override;
};
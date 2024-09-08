#pragma once
#include "module.h"

class Manager  
{
    public:
    std::vector<Person> persons;
    std::vector<AbstractModule*> modules;
    Manager(std::vector<AbstractModule*> modules);
    ~Manager();
    void read_from_file();
    void write_into_file();
    void show_menu();
    void work(std::string choice);
    void start();
};
#include "module.h"
#include <iostream>

std::string AbstractModule::read_from_command_line(const std::string& prompt) {
    std::cout << "Please enter " << prompt << ": ";
    std::string result;
    std::getline(std::cin, result);
    std::cout << "OK, your entered \"" << result << "\" has been recorded." << std::endl;
    return result;
}

bool AbstractModule::worker(std::vector<Person>& persons, const std::string& choice) {
    if (choice != tag) {
        return false;
    }
    std::vector<std::string> args = menu_function();
    realize(args, persons);
    return true;
}

AddPersonModule::AddPersonModule() {
    info = "Add a new person (enter: add)";
    tag = "add";
}

std::vector<std::string> AddPersonModule::menu_function() {
    std::string name = AbstractModule::read_from_command_line("name");
    std::string job = AbstractModule::read_from_command_line("job");
    return {name, job};
}

void AddPersonModule::realize(std::vector<std::string>& args, std::vector<Person>& persons) {
    if (persons.size() < 10000) {
        persons.emplace_back(args[0], args[1]);
    }
}


CopyPersonModule::CopyPersonModule() {
    info = "Copy a new person (enter: copy)";
    tag = "copy";
}

std::vector<std::string> CopyPersonModule::menu_function() {
    std::string name = AbstractModule::read_from_command_line("name");
    return {name};
}

void CopyPersonModule::realize(std::vector<std::string>& args, std::vector<Person>& persons) {
    std::string name = args[0];
    for (int i = 0; i < persons.size(); ++i) {
        if (persons[i].name == name) {
            persons.emplace_back(persons[i].name, persons[i].job);
            break;
        }
    }
}


DeletePersonModule::DeletePersonModule() {
    info = "Delete a person (enter: delete)";
    tag = "delete";
}

std::vector<std::string> DeletePersonModule::menu_function() {
    std::string name = AbstractModule::read_from_command_line("name of the person to delete");
    return {name};
}

void DeletePersonModule::realize(std::vector<std::string>& args, std::vector<Person>& persons) {
    std::string name = args[0];
    for (int i = 0; i < persons.size(); ++i) {
        if (persons[i].name == name) {
            persons.erase(persons.begin() + i);
            break;
        }
    }
}


SearchPersonModule::SearchPersonModule() {
    info = "Search a person (enter: search)";
    tag = "search";
}

std::vector<std::string> SearchPersonModule::menu_function() {
    std::string name = AbstractModule::read_from_command_line("name of the person to search");
    return {name};
}

void SearchPersonModule::realize(std::vector<std::string>& args, std::vector<Person>& persons) {
    std::string name = args[0];
    for (int i = 0; i < persons.size(); ++i) {
        if (persons[i].name == name) {
            std::cout << "Found: " << persons[i].name << ", Job: " << persons[i].job << std::endl;
            break;
        }
    }
}

EditPersonModule::EditPersonModule() {
    info = "Edit a person (enter: edit)";
    tag = "edit";
}

std::vector<std::string> EditPersonModule::menu_function() {
    std::string old_name = AbstractModule::read_from_command_line("current name of the person to edit");
    std::string new_name = AbstractModule::read_from_command_line("new name of the person");
    std::string job = AbstractModule::read_from_command_line("new job of the person");
    return {old_name, new_name, job};
}

void EditPersonModule::realize(std::vector<std::string>& args, std::vector<Person>& persons) {
    std::string old_name = args[0];
    for (int i = 0; i < persons.size(); ++i) {
        if (persons[i].name == old_name) {
            persons[i].name = args[1];
            persons[i].job = args[2];
            std::cout << "Updated successfully!" << std::endl;
            break;
        }
    }
}


DisplayPersonModule::DisplayPersonModule() {
    info = "Display all persons (enter: display)";
    tag = "display";
}

std::vector<std::string> DisplayPersonModule::menu_function() {
    return {};
}

void DisplayPersonModule::realize(std::vector<std::string>& args, std::vector<Person>& persons) {
    for (int i = 0; i < persons.size(); ++i) {
        std::cout << "Person " << i + 1 << ": Name: " << persons[i].name << ", Job: " << persons[i].job << std::endl;
    }
}

ExitPersonModule::ExitPersonModule() {
    info = "Exit this system (enter: exit)";
    tag = "exit";
}

std::vector<std::string> ExitPersonModule::menu_function() {
    return {};
}

void ExitPersonModule::realize(std::vector<std::string>& args, std::vector<Person>& persons) {
    std::exit(0);
}


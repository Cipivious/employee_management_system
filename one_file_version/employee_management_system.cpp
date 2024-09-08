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

    static std::string read_from_command_line(const std::string& prompt) {
        std::cout << "Please enter " << prompt << ": ";
        std::string result;
        std::getline(std::cin, result);
        std::cout << "OK, your entered \"" << result << "\" has been recorded." << std::endl;
        return result;
    }

    bool worker(std::vector<Person>& persons, const std::string& choice) {
        if (choice != tag) {
            return false;
        }
        std::vector<std::string> args = menu_function();
        realize(args, persons);
        return true;
    }
};

class AddPersonModule : public AbstractModule {
public:
    AddPersonModule() {
        info = "Add a new person (enter: add)";
        tag = "add";
    }

    std::vector<std::string> menu_function() {
        std::string name = read_from_command_line("name");
        std::string job = read_from_command_line("job");
        return {name, job};
    }

    void realize(std::vector<std::string>& args, std::vector<Person>& persons) override {
        if (persons.size() < 10000) {
            persons.emplace_back(args[0], args[1]);
        }
    }
};

class CopyPersonModule : public AbstractModule {
public:
    CopyPersonModule() {
        info = "Copy a new person (enter: copy)";
        tag = "copy";
    }

    std::vector<std::string> menu_function() {
        std::string name = read_from_command_line("name");
        return {name};
    }

    void realize(std::vector<std::string>& args, std::vector<Person>& persons) override {
        std::string name = args[0];
        for (int i = 0; i < persons.size(); ++i) {
            if (persons[i].name == name) {
                persons.emplace_back(persons[i].name, persons[i].job);
                break;
            }
        }
    }
};

class DeletePersonModule : public AbstractModule {
public:
    DeletePersonModule() {
        info = "Delete a person (enter: delete)";
        tag = "delete";
    }

    std::vector<std::string> menu_function(){
        std::string name = read_from_command_line("name of the person to delete");
        return {name};
    }

    void realize(std::vector<std::string>& args, std::vector<Person>& persons) override {
        std::string name = args[0];
        for (int i = 0; i < persons.size(); ++i) {
            if (persons[i].name == name) {
                persons.erase(persons.begin() + i);
                break;
            }
        }
    }
};

class SearchPersonModule : public AbstractModule {
public:
    SearchPersonModule() {
        info = "Search a person (enter: search)";
        tag = "search";
    }

    std::vector<std::string> menu_function(){
        std::string name = read_from_command_line("name of the person to search");
        return {name};
    }

    void realize(std::vector<std::string>& args, std::vector<Person>& persons) override {
        std::string name = args[0];
        for (int i = 0; i < persons.size(); ++i) {
            if (persons[i].name == name) {
                std::cout << "Found: " << persons[i].name << ", Job: " << persons[i].job << std::endl;
                break;
            }
        }
    }
};

class EditPersonModule : public AbstractModule {
public:
    EditPersonModule() {
        info = "Edit a person (enter: edit)";
        tag = "edit";
    }

    std::vector<std::string> menu_function(){
        std::string old_name = read_from_command_line("name of the person to edit");
        std::string new_name = read_from_command_line("name of the person to edit");
        std::string job = read_from_command_line("name of the person to edit");
        return {old_name, new_name, job};
    }

    void realize(std::vector<std::string>& args, std::vector<Person>& persons) override {
        std::string name = args[0];
        for (int i = 0; i < persons.size(); ++i) {
            if (persons[i].name == name) {
                persons[i].name = args[1];
                persons[i].job = args[2];
                std::cout << "Updated successfully!" << std::endl;
                break;
            }
        }
    }
};

class DisplayPersonModule : public AbstractModule {
public:
    DisplayPersonModule() {
        info = "Display all persons (enter: display)";
        tag = "display";
    }

    std::vector<std::string> menu_function(){
        return {};
    }

    void realize(std::vector<std::string>& args, std::vector<Person>& persons) override {
        for (int i = 0; i < persons.size(); ++i) {
            std::cout << "Person " << i + 1 << ": Name " << persons[i].name << ", Job " << persons[i].job << std::endl;
        }
    }
};

class ExitPersonModule : public AbstractModule {
public:
    ExitPersonModule() {
        info = "Exit this system (enter: exit)";
        tag = "exit";
    }

    std::vector<std::string> menu_function(){
        return {};
    }

    void realize(std::vector<std::string>& args, std::vector<Person>& persons) override {
        // std::exit(0);
    }
};


class Manager  
{
    public:
    std::vector<Person> persons;
    std::vector<AbstractModule*> modules;
    Manager(std::vector<AbstractModule*> modules){
        this->modules = modules;
        read_from_file();
    }
    ~Manager() {
        std::cout << "Welcome to ~Manager()" << std::endl;
        write_into_file();
    }
    void read_from_file(){
        std::ifstream ifs("info.txt", std::ios::in);
        if (!ifs.is_open()) {
            std::cerr << "Failed to open file." << std::endl;
            return;
        }
        std::string name, job, line;
        while (std::getline(ifs, line)) {
            std::istringstream iss(line);  // 创建字符串流以分割姓名和职位
            if (!(iss >> name >> job)) {   // 提取姓名和职位
                std::cerr << "Failed to parse line: " << line << std::endl;
                continue;
            }
            persons.emplace_back(name, job);  // 创建新的 Person 对象
        }
        ifs.close();
    }
    void write_into_file(){
        std::ofstream ofs;
        ofs.open("info.txt", std::ios::out);

        for(int i = 0; i < persons.size(); i++) {
            ofs << persons[i].name << " " << persons[i].job << std::endl;
        }
    }
    
    void show_menu(){
        std::cout << "\n\n----------------------------------------" << std::endl;
        std::cout << "Welcome to the person Management System" << std::endl;  
        for(int i = 0; i < modules.size(); i++){
            std::cout << modules[i]->info << std::endl;
        }      
    }

    void work(std::string choice){
        for(int i = 0; i < modules.size(); i++){
            if(modules[i]->worker(persons, choice)){
                break;
            }
        } 
    }
    void start(){
        while(true){
            show_menu();    
            std::string choice = AbstractModule::read_from_command_line("your choice");
            if(choice == "exit"){
                break;
            }
            work(choice);
            system("pause");
            system("cls");
        }
    }
};

int main() {
    std::vector<AbstractModule*> modules = {
        new AddPersonModule,
        new DeletePersonModule,
        new DisplayPersonModule,
        new EditPersonModule,
        new SearchPersonModule,
        new CopyPersonModule,
        new ExitPersonModule
    };
    Manager manager(modules);
    manager.start();
    return 0;
}

#include "manager.h"

Manager::Manager(std::vector<AbstractModule*> modules){
    this->modules = modules;
    read_from_file();
}
Manager::~Manager() {
    std::cout << "Welcome to ~Manager()" << std::endl;
    write_into_file();
}
void Manager::read_from_file(){
    std::ifstream ifs("info.txt", std::ios::in);
    if (!ifs.is_open()) {
        std::cerr << "I will create a info.txt to storage information later." << std::endl;
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
void Manager::write_into_file(){
    std::ofstream ofs;
    ofs.open("info.txt", std::ios::out);

    for(int i = 0; i < persons.size(); i++) {
        ofs << persons[i].name << " " << persons[i].job << std::endl;
    }
}
    
void Manager::show_menu(){
    std::cout << "\n\n----------------------------------------" << std::endl;
    std::cout << "Welcome to the person Management System" << std::endl;  
    for(int i = 0; i < modules.size(); i++){
        std::cout << modules[i]->info << std::endl;
    }      
}

void Manager::work(std::string choice){
    for(int i = 0; i < modules.size(); i++){
        if(modules[i]->worker(persons, choice)){
            break;
        }
    } 
}
void Manager::start(){
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

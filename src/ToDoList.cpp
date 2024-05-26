#include <iostream>
#include <limits>
#include <vector>
#include <memory>

class Task{
    static int _count;
    int _id;
    std::string _title;
    std::string _desc;
    std::string _due_date;
public:
    Task(const std::string& title, const std::string& desc, const std::string& due_date){
        _count++;
        _id = _count;
        _title = title;
        _desc = desc;
        _due_date = due_date;
    }

    void setId(const int& id){
        _id = id;
    }

    void setTitle(const std::string& title){
        _title = title;
    }

    void setDesc(const std::string& desc){
        _desc = desc;
    }

    void setDueDate(const std::string& due_date){
        _due_date = due_date;
    }

    int getId() const{
        return _id;
    }

    std::string getTitle() const{
        return _title;
    }

    std::string getDesc() const{
        return _desc;
    }

    std::string getDueDate() const{
        return _due_date;
    }

    int decCount(){
        _count--;
    }
};

int Task :: _count = 0;

void addTask(std::vector <std::unique_ptr<Task>>& v){
    std::string title, desc, due_date;
    std::cout << "\nEnter title: ";
    getline(std::cin, title);
    std::cout << "Enter description: ";
    getline(std::cin, desc);
    std::cout << "Enter due date: ";
    getline(std::cin, due_date);
    v.push_back(std::make_unique<Task>(title, desc, due_date));
    std::cout << "Task entered successfully!" << std::endl;
}

void deleteTask(std::vector <std::unique_ptr<Task>>& v){
    int id;
    std::cout << "\nEnter ID: ";
    std::cin >> id;
    std::cin.ignore();
    if(std::cin.fail()){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    bool idFound = false;
    for(auto it = v.begin(); it != v.end(); ){
        if((*it) -> getId() == id){
            (*it) -> decCount();
            v.erase(it);
            it = v.end();
            idFound = true;
            break;
        }
        else
            it++;
        
    }
    if(!idFound){
        std::cout << "Task do not exists." << std::endl;
        return;
    }
    for(const auto& ptr : v){
        if(ptr -> getId() >= id){
            int new_id = ptr -> getId() - 1;
            ptr -> setId(new_id);
        }
    }
}

void editTask(std::vector <std::unique_ptr<Task>>& v){
    int id;
    std::cout << "\nEnter ID: ";
    std::cin >> id;
    std::cin.ignore();
    if(std::cin.fail()){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    bool idFound = false;
    for(auto it = v.begin(); it != v.end(); ){
        if((*it) -> getId() == id){
            std::string newTitle, newDesc, newDueDate;
            std::cout << "New Title: ";
            getline(std::cin, newTitle);
            (*it) -> setTitle(newTitle);
            std::cout << "New Description: ";
            getline(std::cin, newDesc);
            (*it) -> setDesc(newDesc);
            std::cout << "New Due Date: ";
            getline(std::cin, newDueDate);
            (*it) -> setDueDate(newDueDate);
            it = v.end();
            idFound = true;
            break;
        }
        else
            it++;
        
    }
    if(!idFound){
        std::cout << "Task do not exists." << std::endl;
        return;
    }
}

void displayTask(std::vector <std::unique_ptr<Task>>& v){
    for(const auto& ptr : v){
        std::cout << "\nID: " << ptr -> getId() << std::endl;
        std::cout << "Title: " << ptr -> getTitle() << std::endl;
        std::cout << "Description: " << ptr -> getDesc() << std::endl;
        std::cout << "Due Date: " << ptr -> getDueDate() << std::endl;
    }
}

int main(){
    std::cout << "\n\tTo Do List" << std::endl;
    
    int choice;
    bool runProgram = true;
    std::vector <std::unique_ptr<Task>> v;

    while(runProgram){
        std::cout << "\n1. Add Task" << std::endl;
        std::cout << "2. Delete Task" << std::endl;
        std::cout << "3. Edit Task" << std::endl;
        std::cout << "4. Display Tasks" << std::endl;
        std::cout << "5. Exit" << std::endl;

        std::cout << "\nChoice: ";
        std::cin >> choice;
        std::cin.ignore();

        switch(choice){
            case 1:
                addTask(v);
                break;
            
            case 2:
                deleteTask(v);
                break;

            // case 3:
            //     editTask(v);
            //     break;
            
            case 4:
                displayTask(v);
                break;
            
            case 5:
                runProgram = false;
                std::cout << "\nExiting the program..." << std::endl;
            default:
                if(std::cin.fail()){
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                std::cout << "Invalid input! Enter valid response." << std::endl;
                break;
        }
        
    }

}
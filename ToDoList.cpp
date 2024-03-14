#include <iostream>
#include <string>
#include <vector>

class Task {
public:
    virtual void ViewOnDisplayTask() = 0;
    virtual void MarkCompletedTask() = 0;
};

class ConcretTask : public Task {
private:
    std::string description;
    bool Iscompleted;

public:
    ConcretTask(std::string desc, bool completed) : description(desc), Iscompleted(completed) {}

    void MarkCompletedTask() override {
        Iscompleted = true;
    }

    void ViewOnDisplayTask() {
        std::cout << (Iscompleted ? "[X] " : "[] ") << description << "\n";
    }
};

class TaskList {
private:
    std::vector<Task*> tasks;

public:
    void addTaskToList(Task* task) {
        tasks.push_back(task);
    }

    void ViewOnDisplayTask() {
        for (size_t i = 0; i < tasks.size(); i++) {
            std::cout << i + 1 << ". ";
            tasks[i]->ViewOnDisplayTask();
        }
    }

    void MarkCompletedTask(int index) {
        if (index > 0 && index <= tasks.size()) {
            tasks[index - 1]->MarkCompletedTask();
        }
    }

    void AddExistingTaskToList(int index) {
        if (index > 0 && index <= tasks.size()) {
            Task* existingTask = tasks[index - 1];
            addTaskToList(existingTask);
        }
    }

    void DeleteTask(int index) {
        if (index > 0 && index <= tasks.size()) {
            tasks.erase(tasks.begin() + index - 1);
        }
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(0); std::cin.tie(0), std::cerr.tie(0);
    setlocale(LC_ALL, "Russian");

    TaskList taskList;

    while (true) {
        std::cout << "Выберите действие:" << std::endl;
        std::cout << "1. Создать новую задачу" << std::endl;
        std::cout << "2. Просмотреть список задач" << std::endl;
        std::cout << "3. Пометить задачу как выполненную" << std::endl;
        std::cout << "4. Удалить задачу" << std::endl;
        std::cout << "5. Добавить задачу в список" << std::endl;
        std::cout << "6. Выйти из программы" << std::endl;

        int Command;
        std::string taskName;
        bool comp;

        std::cin >> Command;

        try {
            if (Command == 1) {
                std::cout << "Введите название задачи и статус выполнения (0 - не выполнено, 1 - выполнено): ";
                std::cin >> taskName >> comp;
                if (comp > 1) {
                    break;
                }
                ConcretTask* newTask = new ConcretTask(taskName, comp);
                taskList.addTaskToList(newTask);
            }
            else if (Command == 2) {
                taskList.ViewOnDisplayTask();
            }
            else if (Command == 3) {
                int index;
                std::cout << "Введите номер задачи для пометки как выполненной: ";
                std::cin >> index;
                taskList.MarkCompletedTask(index);
            }
            else if (Command == 4) {
                int index;
                std::cout << "Введите номер удаляемой задачи : ";
                std::cin >> index;
                taskList.DeleteTask(index);
                std::cout << "Задача под номером " << index << " удалена " << std::endl;
            }
            else if (Command == 5) {
                int index;
                std::cout << "Введите номер задачи для добавления в список: ";
                std::cin >> index;
                taskList.AddExistingTaskToList(index);
            }
            else if (Command == 6) {
                break; // Выход из цикла и завершение программы
            }
            else {
                throw std::invalid_argument("Некорректная команда");
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Ошибка: " << e.what() << ". Пожалуйста, повторите ввод." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        std::cout << "-------------------------------------------" << "\n";
    }

    return 0;
}


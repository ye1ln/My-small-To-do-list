/*Класс – это способ описания сущности, определяющий состояние и поведение, зависящее от этого состояния, а также правила для взаимодействия с данной сущностью (контракт).

С точки зрения программирования класс можно рассматривать как набор данных (полей, атрибутов, членов класса) и функций для работы с ними (методов).

С точки зрения структуры программы, класс является сложным типом данных.*/


/*Объект (экземпляр) – это отдельный представитель класса, имеющий конкретное состояние и поведение, полностью определяемое классом.
*/

/*Интерфейс – это набор методов класса, доступных для использования другими классами.*/

/*я
Инкапсуляция – это свойство системы, позволяющее объединить данные и методы, работающие с ними, в классе и скрыть детали
реализации от пользователя.
*/

/*
Абстрагирование – это способ выделить набор значимых характеристик объекта, исключая из рассмотрения незначимые. Соответственно, абстракция – это набор всех таких характеристик.
*/

/*Полиморфизм – это свойство системы использовать объекты с одинаковым интерфейсом без информации о типе и внутренней структуре объекта*/

/*Наследование – это свойство системы, позволяющее описать новый класс на основе уже существующего с частично или полностью заимствующейся функциональностью. Класс, от которого производится наследование, называется базовым или родительским. Новый класс – потомком, наследником или производным классом.
*/

//ПРЯМО СЕЙЧАС ТУТ ДЕЛАЕТСЯ
/*Список задач (To-Do List): Создайте приложение для управления списком задач.
Пользователь может добавлять новые задачи, отмечать задачи как выполненные, удалять задачи и просматривать список задач.*/


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


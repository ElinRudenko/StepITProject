#include <iostream>
#include <cstring>
#include <string>

#define MAX_SIZE 100
#define INPUT_SIZE 50
#define MIN_INPUT_SIZE 10

enum Status
{
    NotCompleted,
    InProgress,
    Completed
}; // перечисление статуса задачи

struct ToDoItem
{
    Status status;              // статус
    char month[MIN_INPUT_SIZE]; // месяц
    char data[MIN_INPUT_SIZE]; //дата задачи (обьеденение даты и месяца)
    char day[MIN_INPUT_SIZE];  // дата
    char week[MIN_INPUT_SIZE]; //неделя
    char time[MIN_INPUT_SIZE]; // время
    char title[INPUT_SIZE];     //название
    char priority[INPUT_SIZE];  // приоритет
    char description[MAX_SIZE]; //описание

};

void set_status(ToDoItem& item)
{ // УСТАНОВКА СТАТУСА ЗАДАЧИ
    std::cout << "Enter the status of the item:" << std::endl;
    std::cout << "1. Not Completed" << std::endl;
    std::cout << "2. In Progress" << std::endl;
    std::cout << "3. Completed" << std::endl;

    int choice;
    std::cout << "Choose an option: ";
    std::cin >> choice;
    std::cin.ignore();

    switch (choice)
    {
    case 1:
        item.status = NotCompleted; // сатус не выполненно
        break;
    case 2:
        item.status = InProgress; // статус в процессе
        break;
    case 3:
        item.status = Completed; // статус выполненно
        break;
    default:
        item.status = NotCompleted; // ставится не выполненно как бы по умолчанию
        break;
    }
}


//__ПРОВЕРКИ__
bool Numeric(const char* str)
{ //ПРОВЕРКА НА ЧИЛО
    for (int i = 0; str[i] != '\0'; i++) //проходится по символам строки
    {
        // если не является цифрой
        if (str[i] < '0' || str[i] > '9') { return false; }// возвращает ложь
    }
    return true; // если символы цифры
}

bool Valid_day(const char* day)
{ // ПРОВЕРКА ДНЯ
    int dayValue = atoi(day); //преобразует строку в целое число
    return (dayValue >= 1 && dayValue <= 31); // истина если введено от 1 до 31
}

bool Valid_week(const char* week)
{ // ПРОВЕРКА ДНЯ НЕДЕЛИ
    int weekNumber = atoi(week); // преобразует строку в целое число
    return (weekNumber >= 1 && weekNumber <= 4); // истина если введено 1-4
}

bool Valid_time(const char* time)
{ // ПРОВЕРКА ВРЕМЕНИ
    int timeValue = atoi(time); // преобразует строку в целое число
    return (timeValue >= 0 && timeValue <= 23); // о - 24
}

bool validateInput(const char* input)
{ // является ли строка числом
    if (!Numeric(input)) // если введенная строка не является числом
    {
        std::cout << "Invalid input. Please enter a number" << std::endl; // вывод предупреждения
        return false;
    }
    return true; // является числом
}

bool Valid_priority(const char* priority)
{ // ПРОВЕРКА ПРИОРИТЕТА
    return (strcmp(priority, "High") == 0 || strcmp(priority, "Medium") == 0 || strcmp(priority, "Low") == 0);
    // сравнение введенных данных с 3 предложенными вариантами
}

bool isValidMonth(char* month)
{
    std::string monthArr[12] = { "01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12" };

    for (int i = 0; i < 12; ++i)
    {
        if (month == monthArr[i]) { return true; }
    }

    return false;
}

void isValidAmPm(char* time)
{
    int timeInput = atoi(time);

    if (timeInput >= 12) { std::cout << "p.m" << std::endl; }
    else { std::cout << "a.m" << std::endl; }
}

bool issValidAmPm(const char* time) 
{
    int timeInput = atoi(time);

    if (timeInput <= 12) { return true; }

    return false;
}


void printMenu()
{ // ВЫВОД МЕНЮ
    std::cout << "Todo List:" << std::endl;
    std::cout << "1. Add item" << std::endl;
    std::cout << "2. Delete item" << std::endl;
    std::cout << "3. Edit item" << std::endl;
    std::cout << "4. Display to-do list " << std::endl;
    std::cout << "5. Search" << std::endl;
    std::cout << "6. Sort list" << std::endl;
    std::cout << "7. Exit" << std::endl;
}


// ДОБАВЛЕНИЕ СПИСКА
void add_todo_item(ToDoItem* todo_list, int* count)
{
    if (*count == MAX_SIZE) //проверка лимита
    {
        std::cout << "Todo list is full. Unable to add new item"
            << std::endl; // список заполнен
        return;
    }

    ToDoItem new_item; // новая задача

    // 1
    std::cout << "Enter the title of the item: ";
    std::cin.getline(new_item.title, INPUT_SIZE); //название

    // 2
    //ввод приоритета и проверка, вызов функции выше
    char input[INPUT_SIZE];
    do
    {
        std::cout << "Enter the priority (High / Medium / Low): ";
        std::cin.getline(input, INPUT_SIZE); // приоритет

        if (Valid_priority(input))
        { // проверка правильности введенного приоритета
            strcpy_s(new_item.priority, input); // копируется приоритет в новую задачу
        }
        else
        {
            std::cout << "Invalid priority. Please enter 'High', 'Medium', or 'Low'" << std::endl;
        }                               // не правильный ввод
    } while (!Valid_priority(input)); // повтор

    // 3
    std::cout << "Enter the DATE by which the item must be completed (DD/MM): ";
    std::cin.getline(new_item.data, MIN_INPUT_SIZE); // дата/месяц

    // разделение на день и на неделю
    int i = 0;
    while (new_item.data[i] != '/' && i < MIN_INPUT_SIZE)
    {
        new_item.day[i] = new_item.data[i]; // копирует дату из строки
        i++;
    }
    new_item.day[i] = '\0'; // символ конца строки

    i++; // Пропуск '/'
    int j = 0;
    while (new_item.data[i] != '\0' && i < MIN_INPUT_SIZE)
    {
        new_item.month[j] = new_item.data[i]; // копирует месяц из строки
        i++;
        j++;
    }
    new_item.month[j] = '\0'; // символ конца строки

    if (!validateInput(new_item.day) || !validateInput(new_item.month) || !Valid_day(new_item.day) || !Valid_day(new_item.month))
    { // проверка дня и месяцы
        return;
    }

    // 4
    std::cout << "Enter the WEEK by which the item must be completed (number): ";
    std::cin.getline(new_item.week, MIN_INPUT_SIZE); // неделя

    while (!Valid_week(new_item.week))
    {
        std::cout << "Invalid week. Please enter a valid week (1-4): ";
        std::cin.getline(new_item.week, MIN_INPUT_SIZE);
    }

    // 5
    std::cout << "Enter the TIME by which the item must be completed (HH): ";
    std::cin.getline(new_item.time, MIN_INPUT_SIZE);

    if (!validateInput(new_item.time) || !Valid_time(new_item.time))
    { // Проверка времени
        return;
    }

    set_status(new_item); // установка статуса задачи

    // 6
    std::cout << "Enter the description of the item: ";
    std::cin.getline(new_item.description, MAX_SIZE); // описание

    todo_list[*count] = new_item; // добавление новой задачи в список
    (*count)++; // увеличение счетчика количества задач

    std::cout << std::endl;
    std::cout << "Item successfully added to the list" << std::endl; // все ок
}


//ВЫВОД
void print_todo_list(const ToDoItem* todo_list, int count)
{ //  ВЫВОД ВСЕГО СПИСКА
    if (count == 0)
    {
        std::cout << "Todo list is empty" << std::endl;
        return;
    }

    std::cout << "Todo List" << std::endl;
    std::cout << "--------------------------" << std::endl;

    for (int i = 0; i < count; i++)
    {
        const ToDoItem& item = todo_list[i];

        std::cout << "Item #" << i + 1 << std::endl;
        std::cout << "Title: " << item.title << std::endl;
        std::cout << "Priority: " << item.priority << std::endl;

        std::cout << "Status: ";
        if (item.status == NotCompleted)
            std::cout << "Not Completed";
        else if (item.status == InProgress)
            std::cout << "In Progress";
        else if (item.status == Completed)
            std::cout << "Completed";

        std::cout << std::endl;
        std::cout << "Terms: " << todo_list[i].data << " till " << todo_list[i].time << " o'clock" << std::endl;
        std::cout << "Description: " << todo_list[i].description << std::endl;
        std::cout << "--------------------------" << std::endl;

    }
}

void printTask(ToDoItem* tasksArr, int taskIdx)
{// ВЫВОД ЗАДАНИЯ

    std::cout << "Title: " << tasksArr[taskIdx].title << std::endl
        << "Priority: " << tasksArr[taskIdx].priority << std::endl;

    std::cout << "Status: ";
    if (tasksArr[taskIdx].status == NotCompleted)
        std::cout << "Not Completed";
    else if (tasksArr[taskIdx].status == InProgress)
        std::cout << "In Progress";
    else if (tasksArr[taskIdx].status == Completed)
        std::cout << "Completed";
    std::cout << std::endl;

    std::cout << "Description: " << tasksArr[taskIdx].description << std::endl
        << "Due date: " << tasksArr[taskIdx].day << "/" << tasksArr[taskIdx].month << std::endl
        << "Due time: " << tasksArr[taskIdx].time << " ";
    isValidAmPm(tasksArr[taskIdx].time);
    std::cout << "--------------------------------" << std::endl;
}

void printDayTask(ToDoItem* tasksArr, int tasksArrSize, char* dayInput, char* monthInput)
{// ВЫВОД СПИСКА НА ВВЕДЕННЫЙ ДЕНЬ

    std::cout << std::endl;
    std::cout << "Tasks for the " << dayInput << std::endl;
    std::cout << "--------------------------------" << std::endl;

    for (int i = 0; i < tasksArrSize; ++i)
    {
        if (!strcmp(tasksArr[i].day, dayInput) && !strcmp(tasksArr[i].month, monthInput))
        {
            printTask(tasksArr, i);
        }
    }
}

void printWeekTasks(ToDoItem* tasksArr, int tasksArrSize, char* weekInput, char* monthInput)
{ // ВЫВОД СПИСКА НА ВВЕДЕННЫЙ НЕДЕЛЮ

    std::cout << std::endl;
    std::cout << "Tasks for the week " << weekInput << " of month " << monthInput << std::endl;
    std::cout << "-------------------------------" << std::endl;

    for (int i = 0; i < tasksArrSize; ++i)
    {
        if (!strcmp(weekInput, tasksArr[i].week) && !strcmp(monthInput, tasksArr[i].month))
        {
            printTask(tasksArr, i);
        }
    }
}

void printMonthTasks(ToDoItem* tasksArr, int tasksArrSize, char* monthInput)
{ // ВЫВОД СПИСКА НА ВВЕДЕННЫЙ мЕСЯЦ

    std::cout << std::endl;
    std::cout << "Tasks for the " << monthInput << std::endl;
    std::cout << "--------------------------------" << std::endl;

    for (int i = 0; i < tasksArrSize; ++i)
    {
        if (!strcmp(tasksArr[i].month, monthInput))
        {
            printTask(tasksArr, i);
        }
    }
}

//ПОИСК
void searchStatus(ToDoItem* tasksArr, int tasksArrSize, int statusInput)
{
    for (int i = 0; i < tasksArrSize; ++i)
    {
        if (statusInput == tasksArr[i].status)
        {
            printTask(tasksArr, i);
        }
    }
}

void searchTitle(ToDoItem* tasks, int tasksArrSize, char* titleInput)
{
    for (int i = 0; i < tasksArrSize; ++i)
    {
        if (!strcmp(titleInput, tasks[i].title))
        {
            printTask(tasks, i);
        }
    }
}

void searchPriority(ToDoItem* tasks, int tasksArrSize, char* priorityInput)
{
    for (int i = 0; i < tasksArrSize; ++i)
    {
        if (!strcmp(tasks[i].priority, priorityInput))
        {
            printTask(tasks, i);
        }
    }
}

void searchDescript(ToDoItem* tasks, int tasksArrSize, char* descriptInput)
{
    for (int i = 0; i < tasksArrSize; ++i)
    {
        if (!strcmp(descriptInput, tasks[i].description))
        {
            printTask(tasks, i);
        }
    }
}

void searchDateTime(ToDoItem* tasks, int tasksArrSize, char* dayInput, char* monthInput, char* time)
{
    for (int i = 0; i < tasksArrSize; ++i)
    {
        if (!strcmp(dayInput, tasks[i].day) && !strcmp(monthInput, tasks[i].month) && !strcmp(time, tasks[i].time))
        {
            printTask(tasks, i);
        }
    }
}

void swap(ToDoItem* task1, ToDoItem* task2)
{
    ToDoItem temp = *task1;
    *task1 = *task2;
    *task2 = temp;
}


//СОРТИРКИ
void sortHigh(ToDoItem* tasks, int tasksArrSize)
{
    for (int i = 0; i < tasksArrSize; ++i)
    {
        for (int j = 0; j < tasksArrSize - 1; ++j)
        {
            if (tasks[j].priority[0] + tasks[j].priority[1] > tasks[j + 1].priority[0] + tasks[j + 1].priority[1])
            {
                swap(&tasks[j], &tasks[j + 1]);
            }
        }
    }
}

void sortLow(ToDoItem* tasks, int tasksArrSize)
{

    for (int i = 0; i < tasksArrSize; ++i)
    {
        for (int j = 0; j < tasksArrSize - 1; ++j)
        {
            if (tasks[j].priority[0] + tasks[j].priority[1] < tasks[j + 1].priority[0] + tasks[j + 1].priority[1])
            {
                swap(&tasks[j], &tasks[j + 1]);
            }
        }
    }
}

void sortPriority(ToDoItem* tasks, char* priorityInput, int tasksArrSize)
{
    int input = priorityInput[0];

    switch (input)
    {
    case 72: sortHigh(tasks, tasksArrSize); break;
    case 76: sortLow(tasks, tasksArrSize); break;
    default: std::cout << "Wrong input!" << std::endl; break;
    }
}

void sortTime(ToDoItem* tasks, char* dayInput, char* monthInput, int tasksArrSize)
{
    for (int i = 0; i < tasksArrSize; ++i)
    {
        if (!strcmp(monthInput, tasks[i].month) && !strcmp(dayInput, tasks[i].day))
        {
            for (int j = 0; j < tasksArrSize - 1; ++j)
            {
                if (tasks[j].time < tasks[j + 1].time)
                {
                    swap(&tasks[j], &tasks[j + 1]);
                }
            }
        }
    }
}

void sortDays(ToDoItem* tasks, char* monthInput, int tasksArrSize)
{
    for (int i = 0; i < tasksArrSize; ++i)
    {
        if (!strcmp(monthInput, tasks[i].month))
        {
            for (int j = 0; j < tasksArrSize - 1; ++j)
            {
                int day1 = std::atoi(tasks[j].day), day2 = std::atoi(tasks[j + 1].day);

                if (day1 > day2)
                {
                    swap(&tasks[j], &tasks[j + 1]);
                }
            }
        }
    }
}

void sortMonths(ToDoItem* tasks, int tasksArrSize)
{
    for (int i = 0; i < tasksArrSize; ++i)
    {
        for (int j = 0; j < tasksArrSize - 1; ++j)
        {
            int month1 = std::atoi(tasks[j].month), month2 = std::atoi(tasks[j + 1].month);

            if (month1 > month2)
            {
                swap(&tasks[j], &tasks[j + 1]);
            }
        }
    }
}

void sortTimeDate(ToDoItem* tasks, int input, int tasksArrSize)
{

    char monthInput[3];
    char dayInput[3];

    switch (input)
    {
    case 1: sortMonths(tasks, tasksArrSize); break;
    case 2:
        std::cout << "Enter the month: "; std::cin >> monthInput;
        sortDays(tasks, monthInput, tasksArrSize);
        break;
    case 3:
        std::cout << "Enter date: "; std::cin >> monthInput; std::cin >> dayInput;
        sortTime(tasks, dayInput, monthInput, tasksArrSize);
        break;
    default:
        std::cout << "Wrong input!" << std::endl;
        break;
    }
}


void delete_todo_item(ToDoItem* todo_list, int count, int index, int* item_count)
{
    --index; //уменьшение индекса, потому что с 0 а пользователь с 1

    if (index < 0 || index >= count)
    { // проверка введенного индекса (номера списка)
        std::cout << "Invalid item index" << std::endl; // ошибка
        return;
    }

    for (int i = index; i < count - 1; i++)
    {
        todo_list[i] = todo_list[i + 1];
    } //сдвиг элемента массива ВЛЕВО, для удаления задачи

    (*item_count)--; // уменьшение счетчика количества задач

    std::cout << "Item successfully deleted from the list" << std::endl; // все ок
}


//EDIT
void display_todo_item(const ToDoItem& item, int index)
{
    std::cout << "Editing item #" << index + 1 << std::endl;
    std::cout << "--------------------------" << std::endl;
    std::cout << "Current item details:" << std::endl;
    std::cout << "Title: " << item.title << std::endl;
    std::cout << "Priority: " << item.priority << std::endl;
    std::cout << "Status: ";

    if (item.status == NotCompleted)
        std::cout << "Not Completed";
    else if (item.status == InProgress)
        std::cout << "In Progress";
    else if (item.status == Completed)
        std::cout << "Completed";

    std::cout << std::endl;
    std::cout << "Terms: " << item.data << " till " << item.time << " o'clock" << std::endl;
    std::cout << "Description: " << item.description << std::endl;
    std::cout << "--------------------------" << std::endl;
}

void edit_todo_item_switch()
{
    //МЕНЮ
    std::cout << std::endl;
    std::cout << "1. Edit title" << std::endl;
    std::cout << "2. Edit priority" << std::endl;
    std::cout << "3. Edit date" << std::endl;
    std::cout << "4. Edit week" << std::endl;
    std::cout << "5. Edit time" << std::endl;
    std::cout << "6. Edit description" << std::endl;
    std::cout << "7. Change status" << std::endl;
    std::cout << "8. Exit" << std::endl;
}

void edit_todo_item_switch(ToDoItem& item)
{

    int choice = 0; // выбор пользователя
    while (choice != 8) // пока не выйдет с редакта
    {
        std::cout << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(); //игнор новой строки предыдущего ввода

        switch (choice)
        {
        case 1:
            std::cout << "Enter the new title: ";
            std::cin.getline(item.title, INPUT_SIZE); // новое название
            std::cout << "Title successfully updated" << std::endl; // все ок
            break;
        case 2:
            char input[INPUT_SIZE];

            do
            {
                std::cout << "Enter the new priority (High / Medium / Low): ";
                std::cin.getline(input, INPUT_SIZE); // нновый приоритет 

                if (Valid_priority(input))
                { // проверка
                    strcpy_s(item.priority, input); // копирование нового приоритета в задачу
                    std::cout << "Priority successfully updated" << std::endl; // все ок
                }
                else
                {
                    std::cout << "Invalid priority. Please enter 'High', 'Medium', or 'Low'" << std::endl; // ошибка ввода
                }
            } while (!Valid_priority(input));
            break;
        case 3:

        {
            std::cout << "Enter the new date (DD/MM): ";
            std::cin.getline(item.day, MIN_INPUT_SIZE); // новая дата

            //разделение на дату и на месяц, проверка
            int i = 0;
            while (item.data[i] != '/' && i < MIN_INPUT_SIZE)
            {
                item.day[i] = item.data[i];
                i++;
            }
            item.day[i] = '\0';  // символ конца строки

            i++;  // Пропуск '/'
            int j = 0;
            while (item.data[i] != '\0' && i < MIN_INPUT_SIZE)
            {
                item.month[j] = item.data[i];
                i++;
                j++;
            }
            item.month[j] = '\0';  // символ конца строки

            if (!validateInput(item.day) || !validateInput(item.month) || !Valid_day(item.day) || !Valid_day(item.month))
            {// проверка
                return;
            }

            std::cout << "Date successfully updated" << std::endl; //все ок
        }
        break;
        case 4:
            std::cout << "Enter the new week (number): ";
            std::cin.getline(item.week, MIN_INPUT_SIZE); // новая неделя

            while (!Valid_week(item.week))
            {
                std::cout << "Invalid week. Please enter a valid week (1-4): "; // ошибка, повторный ввод
                std::cin.getline(item.week, MIN_INPUT_SIZE);
            }

            std::cout << "Week successfully updated" << std::endl; //все ок
            break;
        case 5:
            std::cout << "Enter the new time (HH): ";
            std::cin.getline(item.time, MIN_INPUT_SIZE); // новое время

            if (!validateInput(item.time) || !Valid_time(item.time))
            {//проверка
                return;
            }

            std::cout << "Time successfully updated" << std::endl; //все ок
            break;
        case 6:
            std::cout << "Enter the new description: ";
            std::cin.getline(item.description, MAX_SIZE); // описание
            std::cout << "Description successfully updated" << std::endl; //вусе ок
            break;
        case 7:
        {
            // влзможные статусы
            std::cout << "Enter the status of the item:" << std::endl;
            std::cout << "1. Not Completed" << std::endl;
            std::cout << "2. In Progress" << std::endl;
            std::cout << "3. Completed" << std::endl;

            int choice;
            std::cout << "Choose an option: ";
            std::cin >> choice;//выбор 
            std::cin.ignore();

            switch (choice)
            {
            case 1:
                item.status = NotCompleted;
                std::cout << "Status set to 'Not Completed'" << std::endl;
                break;
            case 2:
                item.status = InProgress;
                std::cout << "Status set to 'In Progress'" << std::endl;
                break;
            case 3:
                item.status = Completed;
                std::cout << "Status set to 'Completed'" << std::endl;
                break;
            default:
                std::cout << "Invalid status choice" << std::endl;
                break;
            }
            break;
        case 8:
            std::cout << "Exiting edit menu" << std::endl;
            break;
        default:
            std::cout << "Invalid choice!" << std::endl;
        }
        break;
        }
    }
}

void edit_todo_item(ToDoItem* todo_list, int count, int index)
{
    --index; // уменьшение индекса, потому что с 0 а пользователь с 1

    if (index < 0 || index >= count)
    {
        std::cout << "Invalid item index!" << std::endl;
        return;
    }

    ToDoItem& item = todo_list[index];

    display_todo_item(item, index);
    edit_todo_item_switch();
    edit_todo_item_switch(item);
}


void print_todo_list_SAFE(const ToDoItem* todo_list, int count)
{
    FILE* file;
    if (fopen_s(&file, "ToDoList.txt", "w") == 0) 
    {
        if (count == 0) 
        {
            fputs("Todo list is empty\n", file);
        }
        else 
        {
            fputs("Todo List\n", file);
            fputs("--------------------------\n", file);

            for (int i = 0; i < count; i++) 
            {
                const ToDoItem& item = todo_list[i];

                fprintf_s(file, "Item #%d\n", i + 1);
                fprintf_s(file, "Title: %s\n", item.title);
                fprintf_s(file, "Priority: %s\n", item.priority);

                fputs("Status: ", file);
                switch (item.status) 
                {
                case NotCompleted:
                    fputs("Not Completed", file);
                    break;
                case InProgress:
                    fputs("In Progress", file);
                    break;
                case Completed:
                    fputs("Completed", file);
                    break;
                }
                fputs("\n", file);

                fprintf_s(file, "Description: %s\n", item.description);
                fprintf_s(file, "Due date: %s", item.day);
                fprintf_s(file, "/%s\n", item.month);
                fprintf_s(file, "Week: %s\n", item.week);
                fprintf_s(file, "Time: %s", item.time);
               
                if (issValidAmPm(item.time)) 
                {

                    fputs("a.m\n", file);
                }
                else {

                    fputs("p.m\n", file);
                }
                

                fputs("\n--------------------------\n", file);
            }
        }

        fclose(file);
        std::cout << "Data saved to file: ToDoList.txt" << std::endl;
    }
    else 
    {
        std::cerr << "Failed to open file: ToDoList.txt" << std::endl;
    }
}

int main()
{
    ToDoItem todo_list[MAX_SIZE];
    int item_count = 0;
    int choice, choice_print = 0, choice_search = 0, choice_sort = 0;

    char dayInput[3];
    char monthInput[3];
    char weekInput[3];

    printMenu(); // вывод меню

    while (true) {
        std::cout << std::endl;
        std::cout << "Select a menu item: ";
        std::cin >> choice;
        std::cin.ignore();

        switch (choice)
        {
        case 1:
            //ДОБАВЛЕНИЕ
            std::cout << std::endl;
            add_todo_item(todo_list, &item_count);
            break;
        case 2:
            //УДАВЕНИЕ
            std::cout << std::endl;
            if (item_count > 0) {
                int index;
                std::cout << "Enter the index (list number) of the item to delete: ";
                std::cin >> index;
                std::cin.ignore();
                delete_todo_item(todo_list, item_count, index, &item_count);
            }
            else {
                std::cout << "Todo list is empty!" << std::endl;
            }
            break;
        case 3:
            //ИЗМЕНЕНИЕ
            std::cout << std::endl;
            if (item_count > 0) {
                int index;
                std::cout << "Enter the index (list number) of the item to edit: ";
                std::cin >> index;
                std::cin.ignore();
                edit_todo_item(todo_list, item_count, index);
            }
            else {
                std::cout << "Todo list is empty!" << std::endl;
            }
            break;
        case 4:
        {
            //ВЫВОД
            std::cout << std::endl;
            std::cout << "1. Showing all lists" << std::endl;
            std::cout << "2. List for the day" << std::endl;
            std::cout << "3. List for the week" << std::endl;
            std::cout << "4. List for the month" << std::endl;
            std::cout << "5. Exit" << std::endl;
            while (choice_print != 5)
            {
                std::cout << std::endl;
                std::cout << "Enter your choice: ";
                std::cin >> choice_print;
                std::cin.ignore();
                std::cout << std::endl;
                switch (choice_print)
                {
                case 1:
                    print_todo_list(todo_list, item_count);
                    break;
                case 2:
                    std::cout << "Enter the DAY in which you want to view the list: ";
                    std::cin >> dayInput;
                    std::cout << "Enter the MONTH in which you want to view the list: ";
                    std::cin >> monthInput;
                    printDayTask(todo_list, item_count, dayInput, monthInput);
                    break;
                case 3:
                    std::cout << "Enter the MONTH in which you want to view the list: ";
                    std::cin >> monthInput;
                    std::cout << "Enter the WEEK in which you want to view the list: ";
                    std::cin >> weekInput;

                    printWeekTasks(todo_list, item_count, weekInput, monthInput);
                    break;
                case 4:
                    std::cout << "Enter the MONTH in which you want to view the list: ";
                    std::cin >> monthInput;
                    printMonthTasks(todo_list, item_count, monthInput);
                    break;

                }
            }
        }
        break;
        case 5:
            std::cout << std::endl;
            std::cout << "Search by:  " << std::endl;
            std::cout << "1. Title" << std::endl;
            std::cout << "2. Priority" << std::endl;
            std::cout << "3. Status" << std::endl;
            std::cout << "4. Date and time" << std::endl;
            std::cout << "5. Description" << std::endl;
            std::cout << "6. Exit" << std::endl;



            while (choice_search != 6)
            {
                std::cout << std::endl;
                std::cout << "Enter your choice: ";
                std::cin >> choice_search;
                switch (choice_search)
                {

                case 1:
                    char titleInput[INPUT_SIZE];
                    std::cout << std::endl;
                    std::cout << "Enter Title: ";
                    std::cin >> titleInput;
                    std::cout << std::endl;
                    std::cout << "Tasks according to your input: " << std::endl;
                    std::cout << "-------------------------------" << std::endl;
                    searchTitle(todo_list, item_count, titleInput);
                    break;

                case 2:
                    char priInput[INPUT_SIZE];
                    std::cout << "Enter priority: ";
                    std::cin >> priInput;
                    std::cout << std::endl;
                    std::cout << "Tasks according to your input: " << std::endl;
                    std::cout << "-------------------------------" << std::endl;
                    searchPriority(todo_list, item_count, priInput);
                    break;

                case 3:
                    int statusInput;
                    std::cout << std::endl;
                    std::cout << "Enter the searched status: " << std::endl;
                    std::cout << "1. Not Complete" << std::endl;
                    std::cout << "2. In Progress" << std::endl;
                    std::cout << "3. Complete" << std::endl;
                    std::cout << std::endl;
                    std::cout << "Enter your choice: ";
                    std::cin >> statusInput;
                    std::cout << std::endl;
                    std::cout << "Tasks according to your input: " << std::endl;
                    std::cout << "-------------------------------" << std::endl;
                    --statusInput;
                    searchStatus(todo_list, item_count, statusInput);
                    break;

                case 4:
                    char timeInput[INPUT_SIZE];

                    std::cout << "Enter day: ";
                    std::cin >> dayInput;
                    std::cout << "Enter month: ";
                    std::cin >> monthInput;
                    std::cout << "Enter time: ";
                    std::cin >> timeInput;
                    std::cout << std::endl;
                    std::cout << "Tasks according to your input: " << std::endl;
                    std::cout << "-------------------------------" << std::endl;
                    searchDateTime(todo_list, item_count, dayInput, monthInput, timeInput);
                    break;

                case 5:
                    char descriptionInput[INPUT_SIZE];

                    std::cout << "Enter description: ";
                    std::cin >> descriptionInput;
                    std::cout << std::endl;
                    std::cout << "Tasks according to your input: " << std::endl;
                    std::cout << "-------------------------------" << std::endl;

                    searchDescript(todo_list, item_count, descriptionInput);
                    break;

                case 6:
                    break;
                }
            }

        case 6:
            std::cout << std::endl;
            std::cout << "Sort by: " << std::endl;
            std::cout << "1. Sort by priority" << std::endl;
            std::cout << "2. Sort by time and date" << std::endl;
            std::cout << "3. Exit" << std::endl;

            while (choice_sort != 3)
            {
                std::cout << std::endl;
                std::cout << "Enter you choice: ";
                std::cin >> choice_sort;

                switch (choice_sort)
                {
                case 1:
                    char priorityInput[INPUT_SIZE];
                    std::cout << "Enter the priority: ";
                    std::cin >> priorityInput;
                    std::cout << std::endl;
                    std::cout << "Tasks according to your input: " << std::endl;
                    sortPriority(todo_list, priorityInput, item_count);
                    print_todo_list(todo_list, item_count);
                    break;

                case 2:
                    int dateTimeChoice;
                    std::cout << std::endl;
                    std::cout << "Enter your choice: " << std::endl;
                    std::cout << "1. Sort by Months" << std::endl;
                    std::cout << "2. Sort by days" << std::endl;
                    std::cout << "3. Sort by time" << std::endl;
                    std::cout << "Enter you choice: ";
                    std::cin >> dateTimeChoice;
                    std::cout << std::endl;
                    sortTimeDate(todo_list, dateTimeChoice, item_count);
                    print_todo_list(todo_list, item_count);
                    break;

                case 3:
                    break;
                }
            }
            break;

        case 7:
            //ВЫХОД
            std::cout << std::endl;
            print_todo_list_SAFE(todo_list, item_count);
            std::cout << "Bye-Bye! Your plans have been saved to a file!" << std::endl;
            return 0;
        default:
            std::cout << std::endl;
            std::cout << "Invalid choice!" << std::endl;
            break;
        }
    }

    return 0;
}
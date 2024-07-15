#include <iostream>
#include <string>
using namespace std;

struct node {
    string task;
    int task_num;
    bool complete;
    node* next, * prev;
};

class ToDoList {
private:
    node* head, * tail;
    int num_tasks;
public:
    ToDoList() {
        head = NULL;
        tail = NULL;
        num_tasks = 0;
    }

    void add_task(string task) {
        node* temp = new node;
        temp->task = task;
        temp->task_num = num_tasks + 1;
        temp->complete = false;
        temp->next = NULL;
        if (head == NULL) {
            temp->prev = NULL;
            head = temp;
            tail = temp;
        }
        else {
            temp->prev = tail;
            tail->next = temp;
            tail = temp;
        }
        num_tasks++;
    }

    void delete_task() {
        if (head == NULL) {
            cout << "The list is empty." << endl;
        }
        else {
            node* temp = head;
            head = head->next;
            if (head == NULL) {
                tail = NULL;
            }
            else {
                head->prev = NULL;
            }
            delete temp;
            num_tasks--;
        }
    }

    void print() {
        if (head == NULL) {
            cout << "The list is empty." << endl;
        }
        else {
            node* temp = head;
            while (temp != NULL) {
                cout << temp->task_num << ". ";
                cout << temp->task << " ";
                if (temp->complete) {
                    cout << "(completed)";
                }
                cout << endl;
                temp = temp->next;
            }
        }
    }

    void complete_task(int task_num) {
        node* temp = head;
        while (temp != NULL) {
            if (temp->task_num == task_num) {
                temp->complete = true;
                break;
            }
            temp = temp->next;
        }
    }

    void bring_completed_task_to_front() {
        node* temp = head;
        while (temp != NULL) {
            if (temp->complete) {
                if (temp == head) {
                    break;
                }
                temp->prev->next = temp->next;
                if (temp == tail) {
                    tail = temp->prev;
                }
                else {
                    temp->next->prev = temp->prev;
                }
                temp->prev = NULL;
                temp->next = head;
                head->prev = temp;
                head = temp;
            }
            temp = temp->next;
        }
    }

    int number_of_not_complete_tasks() {
        int count = 0;
        node* temp = head;
        while (temp != NULL) {
            if (!temp->complete) {
                count++;
            }
            temp = temp->next;
        }
        return count;
    }
};

int main() {
    ToDoList list;
    int choice, task_num;
    string task;
    do {
        cout << "1. Add task" << endl;
        cout << "2. Delete task" << endl;
        cout << "3. Print list" << endl;
        cout << "4. Complete task" << endl;
        cout << "5. Bring completed tasks to front" << endl;
        cout << "6. Number of not completed tasks" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            cout << "Enter task: ";
            cin.ignore();
            getline(cin, task);
            list.add_task(task);
            break;
        case 2:
            list.delete_task();
            break;
        case 3:
            list.print();
            break;
        case 4:
            cout << "Enter task number: ";
            cin >> task_num;
            list.complete_task(task_num);
            break;
        case 5:
            list.bring_completed_task_to_front();
            break;
        case 6:
            cout << "Number of not completed tasks: " << list.number_of_not_complete_tasks() << endl;
            break;
        case 7:
            break;
        default:
            cout << "Invalid choice." << endl;
        }
        cout << endl;
    } while (choice != 7);
    return 0;
}

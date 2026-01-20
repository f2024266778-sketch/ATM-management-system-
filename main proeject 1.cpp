#include <iostream>
using namespace std;
struct Transaction {
    string type;
    int amount;
    Transaction* next;

    Transaction(string t, int a) {
        type = t;
        amount = a;
        next = NULL;
    }
};
class Stack {
public:
    Transaction* top = NULL;

    void push(string type, int amount) {
        Transaction* temp = new Transaction(type, amount);
        temp->next = top;
        top = temp;
    }

    void showLastThree() {
        Transaction* temp = top;
        int count = 0;

        cout << "\n--- Last 3 Transactions ---\n";

        while (temp != NULL && count < 3) {
            cout << temp->type << " : " << temp->amount << endl;
            temp = temp->next;
            count++;
        }

        if (count == 0)
            cout << "No transactions found.\n";
    }
};

class Queue {
public:
    Transaction* front = NULL;
    Transaction* rear = NULL;

    void enqueue(string type, int amount) {
        Transaction* temp = new Transaction(type, amount);
        if (rear == NULL)
            front = rear = temp;
        else {
            rear->next = temp;
            rear = temp;
        }
    }
};

class LinkedList {
public:
    Transaction* head = NULL;

    void add(string type, int amount) {
        Transaction* temp = new Transaction(type, amount);
        temp->next = head;
        head = temp;
    }
};

struct Account {
    int accNo;
    int pin;
    int balance;
    Account* left;
    Account* right;

    Account(int a, int p, int b) {
        accNo = a;
        pin = p;
        balance = b;
        left = right = NULL;
    }
};

class AccountTree {
public:
    Account* root = NULL;

    Account* insert(Account* root, int accNo, int pin, int balance) {
        if (root == NULL)
            return new Account(accNo, pin, balance);

        if (accNo < root->accNo)
            root->left = insert(root->left, accNo, pin, balance);
        else
            root->right = insert(root->right, accNo, pin, balance);

        return root;
    }

    void addAccount(int accNo, int pin, int balance) {
        root = insert(root, accNo, pin, balance);
    }

    Account* search(Account* root, int accNo) {
        if (root == NULL || root->accNo == accNo)
            return root;

        if (accNo < root->accNo)
            return search(root->left, accNo);
        else
            return search(root->right, accNo);
    }

    void display(Account* root) {
        if (root != NULL) {
            display(root->left);
            cout << "Account No: " << root->accNo
                 << " | Balance: " << root->balance << endl;
            display(root->right);
        }
    }
};

int main() {
    AccountTree bank;
    Stack stack;
    Queue queue;
    LinkedList history;

    bank.addAccount(1001, 1111, 5000);
    bank.addAccount(1002, 2222, 8000);
    bank.addAccount(1003, 3333, 12000);

    int accNo, pin;

    cout << "========== ATM LOGIN ==========\n";
    cout << "Enter Account Number: ";
    cin >> accNo;
    cout << "Enter PIN: ";
    cin >> pin;

    Account* user = bank.search(bank.root, accNo);

    if (user == NULL || user->pin != pin) {
        cout << "\nInvalid Account Number or PIN!\n";
        return 0;
    }

    cout << "\nLogin Successful!\n";

    int choice, amount;

    while (true) {
        cout << "\n========== ATM MENU ==========\n";
        cout << "1. Check Balance\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Transaction History (Last 3)\n";
        cout << "5. Account Records (Admin - Tree)\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 6) {
            cout << "\nThank you for using ATM!\n";
            break;
        }

        switch (choice) {
        case 1:
            cout << "Current Balance: " << user->balance << endl;
            break;

        case 2:
            cout << "Enter deposit amount: ";
            cin >> amount;
            user->balance += amount;
            history.add("Deposit", amount);
            stack.push("Deposit", amount);
            queue.enqueue("Deposit", amount);
            cout << "Deposit successful.\n";
            break;

        case 3:
            cout << "Enter withdraw amount: ";
            cin >> amount;
            if (amount > user->balance) {
                cout << "Insufficient Balance!\n";
            } else {
                user->balance -= amount;
                history.add("Withdraw", amount);
                stack.push("Withdraw", amount);
                queue.enqueue("Withdraw", amount);
                cout << "Withdraw successful.\n";
            }
            break;

        case 4:
            stack.showLastThree();
            break;

        case 5:
            cout << "\n--- All Account Records (BST) ---\n";
            bank.display(bank.root);
            break;

        default:
            cout << "Invalid option!\n";
        }
    }

    return 0;
}


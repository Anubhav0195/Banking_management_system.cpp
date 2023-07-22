#include <iostream>
#include <fstream>
#include <string>
#include<sstream>

using namespace std;

// Function to create a new account
void createAccount() {
    string accountNumber, name;
    double balance;

    cout << "Enter account number: ";
    cin >> accountNumber;
    cout << "Enter account holder name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter initial balance: ";
    cin >> balance;

    ofstream outFile("accounts.txt", ios::app);
    outFile << accountNumber << " " << name << " " << balance << endl;
    outFile.close();

    cout << "Account created successfully!" << endl;
}

// Function to perform a deposit
void deposit() {
    string accountNumber;
    double amount;

    cout << "Enter account number: ";
    cin >> accountNumber;
    cout << "Enter amount to deposit: ";
    cin >> amount;

    ifstream inFile("accounts.txt");
    ofstream tempFile("temp.txt");

    string line;
    bool found = false;

    while (getline(inFile, line)) {
        string currentAccountNumber, name;
        double balance;
        istringstream iss(line);

        if (iss >> currentAccountNumber >> name >> balance) {
            if (currentAccountNumber == accountNumber) {
                balance += amount;
                found = true;
            }
            tempFile << currentAccountNumber << " " << name << " " << balance << endl;
        }
    }

    inFile.close();
    tempFile.close();

    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    if (found) {
        cout << "Deposit successful!" << endl;
    } else {
        cout << "Account not found!" << endl;
    }
}

// Function to perform a withdrawal
void withdraw() {
    string accountNumber;
    double amount;

    cout << "Enter account number: ";
    cin >> accountNumber;
    cout << "Enter amount to withdraw: ";
    cin >> amount;

    ifstream inFile("accounts.txt");
    ofstream tempFile("temp.txt");

    string line;
    bool found = false;

    while (getline(inFile, line)) {
        string currentAccountNumber, name;
        double balance;
        istringstream iss(line);

        if (iss >> currentAccountNumber >> name >> balance) {
            if (currentAccountNumber == accountNumber) {
                if (balance >= amount) {
                    balance -= amount;
                    found = true;
                } else {
                    cout << "Insufficient balance!" << endl;
                }
            }
            tempFile << currentAccountNumber << " " << name << " " << balance << endl;
        }
    }

    inFile.close();
    tempFile.close();

    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    if (found) {
        cout << "Withdrawal successful!" << endl;
    } else {
        cout << "Account not found!" << endl;
    }
}

// Function to check the account balance
void checkBalance() {
    string accountNumber;

    cout << "Enter account number: ";
    cin >> accountNumber;

    ifstream inFile("accounts.txt");

    string line;
    bool found = false;

    while (getline(inFile, line)) {
        string currentAccountNumber, name;
        double balance;
        istringstream iss(line);

        if (iss >> currentAccountNumber >> name >> balance) {
            if (currentAccountNumber == accountNumber) {
                cout << "Account Number: " << currentAccountNumber << endl;
                cout << "Name: " << name << endl;
                cout << "Balance: " << balance << endl;
                found = true;
                break;
            }
        }
    }

    inFile.close();

    if (!found) {
        cout << "Account not found!" << endl;
    }
}

// Function to display all account details
void displayAllAccounts() {
    ifstream inFile("accounts.txt");

    string line;

    while (getline(inFile, line)) {
        string accountNumber, name;
        double balance;
        istringstream iss(line);

        if (iss >> accountNumber >> name >> balance) {
            cout << "Account Number: " << accountNumber << endl;
            cout << "Name: " << name << endl;
            cout << "Balance: " << balance << endl;
            cout << endl;
        }
    }

    inFile.close();
}

int main() {
    int choice;

    while (true) {
        cout << "=== Banking Management System ===" << endl;
        cout << "1. Create Account" << endl;
        cout << "2. Deposit Funds" << endl;
        cout << "3. Withdraw Funds" << endl;
        cout << "4. Check Account Balance" << endl;
        cout << "5. Display All Accounts" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                deposit();
                break;
            case 3:
                withdraw();
                break;
            case 4:
                checkBalance();
                break;
            case 5:
                displayAllAccounts();
                break;
            case 0:
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice!" << endl;
        }

        cout << endl;
    }

    return 0;
}
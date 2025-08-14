#include <iostream>
#include <string>
#include <unordered_map>
#include <iomanip>

class Account {
private:
    std::string accountHolderName;
    int accountNumber;
    double balance;

public:
    Account(const std::string& name, int number, double initialBalance)
        : accountHolderName(name), accountNumber(number), balance(initialBalance) {}

    int getAccountNumber() const {
        return accountNumber;
    }

    std::string getAccountHolderName() const {
        return accountHolderName;
    }

    double getBalance() const {
        return balance;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            std::cout << "Deposited: $" << amount << "\n";
        } else {
            std::cout << "Invalid deposit amount.\n";
        }
    }

    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            std::cout << "Withdrawn: $" << amount << "\n";
        } else {
            std::cout << "Invalid withdrawal amount or insufficient balance.\n";
        }
    }
};

class ATM {
private:
    std::unordered_map<int, Account*> accounts;

public:
~ATM() {
    for (std::unordered_map<int, Account*>::iterator it = accounts.begin(); it != accounts.end(); ++it) {
        delete it->second;
    }
}

    void addAccount(const Account& account) {
        accounts[account.getAccountNumber()] = new Account(account);
    }

    void displayMenu() {
        std::cout << "\n--- ATM Menu ---\n";
        std::cout << "1. Check Balance\n";
        std::cout << "2. Deposit\n";
        std::cout << "3. Withdraw\n";
        std::cout << "4. Exit\n";
    }

    void handleTransaction(int accountNumber) {
        if (accounts.find(accountNumber) == accounts.end()) {
            std::cout << "Account not found.\n";
            return;
        }
    
        Account& account = *accounts[accountNumber]; // dereference pointer
        int choice;
        do {
            displayMenu();
            std::cout << "Enter your choice: ";
            std::cin >> choice;
    
            switch (choice) {
                case 1:
                    std::cout << "Account Holder: " << account.getAccountHolderName() << "\n";
                    std::cout << "Current Balance: $" << std::fixed << std::setprecision(2) 
                              << account.getBalance() << "\n";
                    break;
                case 2: {
                    double depositAmount;
                    std::cout << "Enter amount to deposit: ";
                    std::cin >> depositAmount;
                    account.deposit(depositAmount);
                    break;
                }
                case 3: {
                    double withdrawAmount;
                    std::cout << "Enter amount to withdraw: ";
                    std::cin >> withdrawAmount;
                    account.withdraw(withdrawAmount);
                    break;
                }
                case 4:
                    std::cout << "Thank you for using the ATM.\n";
                    break;
                default:
                    std::cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 4);
    }
};      

int main() {
    ATM atm;

    // Adding some accounts
    atm.addAccount(Account("John Doe", 101, 500.00));
    atm.addAccount(Account("Jane Smith", 102, 1000.00));

    int accountNumber;
    std::cout << "Enter your account number: ";
    std::cin >> accountNumber;

    atm.handleTransaction(accountNumber);

    return 0;
}
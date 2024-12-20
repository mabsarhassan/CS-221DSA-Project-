#include <bits/stdc++.h>
#include <ctime> // For timestamps
using namespace std;

class Entity {
public:
    string name;
    int netAmount;
};

class Transaction {
public:
    string debtor;
    string creditor;
    int amount;
    time_t timestamp; // Timestamp for the transaction
    Transaction* next;

    Transaction(string debtor, string creditor, int amount) :
        debtor(debtor), creditor(creditor), amount(amount), next(nullptr) {
        timestamp = time(0); // Record current time when the transaction is created
    }

};

class TransactionManager {
private:
    stack<vector<Transaction>> undoStack; // Stack for undo history
    stack<vector<Transaction>> redoStack; // Stack for redo history
    vector<Transaction> transactions;     // Current transactions

public:
    void addTransaction(const string& debtor, const string& creditor, int amount) {
        // Save current state to undo stack
        undoStack.push(transactions);

        // Clear redo stack since future redo history is invalidated
        while (!redoStack.empty()) 
        {
            redoStack.pop();
        }

        // Add the new transaction
        transactions.emplace_back(debtor, creditor, amount);
        //cout << "Transaction added: " << debtor << " owes " << amount << " to " << creditor << endl;
    }

    void undo() {
        if (undoStack.empty()) {
            cout << "No actions to undo.\n";
            return;
        }

        // Save current state to redo stack
        redoStack.push(transactions);

        // Restore previous state
        transactions = undoStack.top();
        undoStack.pop();

        cout << "Undo successful. Current transactions:\n";
        displayTransactions();
    }

    void redo() {
        if (redoStack.empty()) {
            cout << "No actions to redo.\n";
            return;
        }

        // Save current state to undo stack
        undoStack.push(transactions);

        // Restore last undone state
        transactions = redoStack.top();
        redoStack.pop();

        cout << "Redo successful. Current transactions:\n";
        displayTransactions();
    }

    void clearTransactions() {
        // Save current state to undo stack
        undoStack.push(transactions);

        // Clear redo stack
        while (!redoStack.empty()){
                redoStack.pop();
        }

        transactions.clear();
        cout << "All transactions have been cleared.\n";
    }

    void displayTransactions() {
        if (transactions.empty()) {
            cout << "No transactions found.\n";
            return;
        }

        for (const auto& t : transactions) {
            cout << t.debtor << " owes " << t.creditor << " amount: " << t.amount << endl;
        }
    }
};


int main(){

    return 0;
}

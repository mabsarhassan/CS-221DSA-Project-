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

void saveData(const vector<vector<int>>& graph, const vector<string>& entityNames) {
    ofstream file(DATA_FILE);
    if (!file) {
        cerr << "Error: Unable to open file for saving data.\n";
        return;
    }

    // Save entities
    file << entityNames.size() << "\n";
    for (const string& name : entityNames) {
        file << name << "\n";
    }

    // Save graph
    int size = graph.size();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            file << graph[i][j] << " ";
        }
        file << "\n";
    }

    file.close();
}

void loadData(vector<vector<int>>& graph, vector<string>& entityNames) {
    ifstream file(DATA_FILE);
    if (!file) {
        cerr << "\nNo previous data found. Starting fresh...\n";
        return;
    }

    int numEntities;
    file >> numEntities;
    entityNames.resize(numEntities);

    // Load entity names
    for (int i = 0; i < numEntities; i++) {
        file >> entityNames[i];
    }

    // Load graph
    graph.resize(numEntities, vector<int>(numEntities, 0));
    for (int i = 0; i < numEntities; i++) {
        for (int j = 0; j < numEntities; j++) {
            file >> graph[i][j];
        }
    }

    file.close();
}
void mergeSort(vector<Entity>& entities, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(entities, left, mid);
        mergeSort(entities, mid + 1, right);

        merge(entities, left, mid, right);
    }
}

int main(){

    return 0;
}

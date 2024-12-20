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

int main(){

    return 0;
}
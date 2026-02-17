#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>

// Simple DeltaCash Technologies Cryptocurrency System
// This is a basic simulation for educational purposes.
// It includes user accounts, transactions, and a simple blockchain-like structure.

class DeltaCash {
private:
    std::map<std::string, double> balances;  // User balances
    std::vector<std::string> transactionLog; // Log of transactions

    // Generate a simple transaction ID
    std::string generateTransactionID() {
        std::string id = "TXN-";
        for (int i = 0; i < 8; ++i) {
            id += 'A' + rand() % 26;
        }
        return id;
    }

public:
    DeltaCash() {
        srand(time(0));  // Seed for random ID generation
    }

    // Create a new user account with initial balance
    bool createAccount(const std::string& user, double initialBalance = 0.0) {
        if (balances.find(user) != balances.end()) {
            std::cout << "Account already exists for " << user << std::endl;
            return false;
        }
        balances[user] = initialBalance;
        transactionLog.push_back("Account created for " + user + " with balance " + std::to_string(initialBalance));
        return true;
    }

    // Transfer funds from one user to another
    bool transfer(const std::string& from, const std::string& to, double amount) {
        if (balances.find(from) == balances.end() || balances.find(to) == balances.end()) {
            std::cout << "Invalid sender or receiver." << std::endl;
            return false;
        }
        if (balances[from] < amount) {
            std::cout << "Insufficient balance." << std::endl;
            return false;
        }
        balances[from] -= amount;
        balances[to] += amount;
        std::string txnID = generateTransactionID();
        transactionLog.push_back(txnID + ": " + from + " -> " + to + " : " + std::to_string(amount) + " DeltaCash");
        return true;
    }

    // Check balance of a user
    double getBalance(const std::string& user) {
        if (balances.find(user) == balances.end()) {
            return -1.0;  // Indicate user not found
        }
        return balances[user];
    }

    // Print transaction log
    void printTransactionLog() {
        std::cout << "Transaction Log:" << std::endl;
        for (const auto& log : transactionLog) {
            std::cout << log << std::endl;
        }
    }

    // Mine new DeltaCash (simulate mining by adding to a user's balance)
    void mine(const std::string& miner, double reward = 10.0) {
        if (balances.find(miner) == balances.end()) {
            std::cout << "Miner account does not exist." << std::endl;
            return;
        }
        balances[miner] += reward;
        transactionLog.push_back("Mined: " + std::to_string(reward) + " DeltaCash to " + miner);
    }
};

int main() {
    DeltaCash deltaCash;

    // Example usage
    deltaCash.createAccount("Alice", 100.0);
    deltaCash.createAccount("Bob", 50.0);

    std::cout << "Alice's balance: " << deltaCash.getBalance("Alice") << std::endl;
    std::cout << "Bob's balance: " << deltaCash.getBalance("Bob") << std::endl;

    deltaCash.transfer("Alice", "Bob", 20.0);
    std::cout << "After transfer:" << std::endl;
    std::cout << "Alice's balance: " << deltaCash.getBalance("Alice") << std::endl;
    std::cout << "Bob's balance: " << deltaCash.getBalance("Bob") << std::endl;

    deltaCash.mine("Alice", 5.0);
    std::cout << "After mining:" << std::endl;
    std::cout << "Alice's balance: " << deltaCash.getBalance("Alice") << std::endl;

    deltaCash.printTransactionLog();

    return 0;
}

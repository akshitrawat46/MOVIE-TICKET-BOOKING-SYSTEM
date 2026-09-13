#include <iostream>
#include <string>
using namespace std;

// Abstraction + inheritance + runtime polymorphism.
class Payment {
public:
    virtual ~Payment() = default;
    virtual bool pay(double amount) = 0;
    virtual string getMethodName() const = 0;
};

class UpiPayment : public Payment {
public:
    bool pay(double amount) override {
        cout << "Processing UPI payment of Rs." << amount << "...\n";
        return true;
    }
    string getMethodName() const override { return "UPI"; }
};

class CardPayment : public Payment {
public:
    bool pay(double amount) override {
        cout << "Processing Card payment of Rs." << amount << "...\n";
        return true;
    }
    string getMethodName() const override { return "CARD"; }
};

class CashPayment : public Payment {
public:
    bool pay(double amount) override {
        cout << "Cash payment received: Rs." << amount << "\n";
        return true;
    }
    string getMethodName() const override { return "CASH"; }
};

#include <iostream>
#include <string>
using namespace std;

class CashPayment : public Payment {
public:
    bool pay(double amount) override {
        cout << "Cash payment received: Rs." << amount << "\n";
        return true;
    }
    string getMethodName() const override { return "CASH"; }
};

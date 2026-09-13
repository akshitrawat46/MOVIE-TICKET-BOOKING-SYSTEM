#include <iostream>
#include <string>
using namespace std;

class UpiPayment : public Payment {
public:
    bool pay(double amount) override {
        cout << "Processing UPI payment of Rs." << amount << "...\n";
        return true;
    }
    string getMethodName() const override { return "UPI"; }
};

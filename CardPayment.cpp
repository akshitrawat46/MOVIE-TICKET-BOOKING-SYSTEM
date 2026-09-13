#include <iostream>
#include <string>
using namespace std;

class CardPayment : public Payment {
public:
    bool pay(double amount) override {
        cout << "Processing Card payment of Rs." << amount << "...\n";
        return true;
    }
    string getMethodName() const override { return "CARD"; }
};

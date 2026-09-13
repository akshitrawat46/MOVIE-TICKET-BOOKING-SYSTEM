#include <string>
using namespace std;

class Customer {
    string name;
    string phone;
public:
    Customer(const string& name, const string& phone) : name(name), phone(phone) {}
    const string& getName() const { return name; }
    const string& getPhone() const { return phone; }
};

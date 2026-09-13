#include <string>
using namespace std;

// Abstraction: common payment contract.
class Payment {
public:
    virtual ~Payment() = default;
    virtual bool pay(double amount) = 0;
    virtual string getMethodName() const = 0;
};

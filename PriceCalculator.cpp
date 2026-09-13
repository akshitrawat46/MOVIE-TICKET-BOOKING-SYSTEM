#include <vector>
using namespace std;

class PriceCalculator {
public:
    double calculateTotal(const vector<ShowSeat*>& seats) const {
        double total = 0;
        for (ShowSeat* showSeat : seats) total += showSeat->getSeat()->getPrice();
        return total;
    }
};

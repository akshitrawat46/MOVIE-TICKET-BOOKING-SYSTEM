#include <string>
using namespace std;

class Seat {
    int number;
    SeatType type;
public:
    Seat(int number, SeatType type) : number(number), type(type) {}
    int getNumber() const { return number; }
    SeatType getType() const { return type; }
    int getPrice() const {
        if (type == SeatType::SILVER) return 150;
        if (type == SeatType::GOLD) return 250;
        return 400;
    }
};

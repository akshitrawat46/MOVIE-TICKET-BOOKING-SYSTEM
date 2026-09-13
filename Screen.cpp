#include <vector>
using namespace std;

class Screen {
    int screenNumber;
    vector<Seat> seats;
public:
    Screen(int screenNumber, int seatCount) : screenNumber(screenNumber) {
        for (int number = 1; number <= seatCount; ++number) {
            SeatType type = number <= seatCount / 2 ? SeatType::SILVER
                             : (number <= (seatCount * 4) / 5 ? SeatType::GOLD : SeatType::PLATINUM);
            seats.emplace_back(number, type);
        }
    }
    int getScreenNumber() const { return screenNumber; }
    const vector<Seat>& getSeats() const { return seats; }
};

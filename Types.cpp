#include <string>
using namespace std;

enum class SeatType { SILVER, GOLD, PLATINUM };
enum class SeatStatus { AVAILABLE, BOOKED };
enum class BookingStatus { PENDING, CONFIRMED, CANCELLED };

string seatTypeName(SeatType type) {
    if (type == SeatType::SILVER) return "SILVER";
    if (type == SeatType::GOLD) return "GOLD";
    return "PLATINUM";
}

string bookingStatusName(BookingStatus status) {
    if (status == BookingStatus::PENDING) return "PENDING";
    if (status == BookingStatus::CONFIRMED) return "CONFIRMED";
    return "CANCELLED";
}

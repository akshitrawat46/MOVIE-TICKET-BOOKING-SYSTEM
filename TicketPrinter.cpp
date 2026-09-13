#include <iostream>
#include <iomanip>
using namespace std;

class TicketPrinter {
public:
    void print(const Booking& booking) const {
        cout << "\n================ TICKET ================\n";
        cout << "Booking ID : " << booking.getBookingId() << '\n';
        cout << "Customer   : " << booking.getCustomer()->getName() << '\n';
        cout << "Movie      : " << booking.getShow()->getMovie()->getTitle() << '\n';
        cout << "Screen     : " << booking.getShow()->getScreen()->getScreenNumber() << '\n';
        cout << "Time       : " << booking.getShow()->getStartTime() << '\n';
        cout << "Seats      : ";
        for (ShowSeat* seat : booking.getBookedSeats()) cout << seat->getSeat()->getNumber() << ' ';
        cout << "\nAmount     : Rs." << fixed << setprecision(2) << booking.getBookingAmount() << '\n';
        cout << "Status     : " << bookingStatusName(booking.getStatus()) << '\n';
        cout << "=========================================\n";
    }
};

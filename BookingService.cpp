#include <vector>
#include <iostream>
using namespace std;

class BookingService {
    PriceCalculator priceCalculator;
    TicketPrinter ticketPrinter;
    vector<Booking*> bookings;
public:
    Booking* createBooking(Customer& customer, Show& show, const vector<int>& seatNumbers, Payment& payment) {
        vector<ShowSeat*> selectedSeats;
        for (int seatNumber : seatNumbers) {
            ShowSeat* showSeat = show.findSeat(seatNumber);
            if (showSeat == nullptr) {
                cout << "Invalid seat number: " << seatNumber << ". Booking rejected.\n";
                return nullptr;
            }
            if (!showSeat->isAvailable()) {
                cout << "Seat " << seatNumber << " is already BOOKED. Booking rejected.\n";
                return nullptr;
            }
            selectedSeats.push_back(showSeat);
        }
        double total = priceCalculator.calculateTotal(selectedSeats);
        Booking* booking = new Booking(&show, &customer, selectedSeats, total);
        booking->setPayment(&payment);
        for (ShowSeat* showSeat : selectedSeats) showSeat->bookSeat();
        bool isPaid = payment.pay(total);
        if (!isPaid) {
            for (ShowSeat* showSeat : selectedSeats) showSeat->cancelSeat();
            cout << "Payment failed. Booking NOT confirmed and seats released.\n";
            delete booking;
            return nullptr;
        }
        booking->confirm();
        bookings.push_back(booking);
        cout << "Payment successful. Booking confirmed.\n";
        ticketPrinter.print(*booking);
        return booking;
    }
    Booking* findBooking(int bookingId) const {
        for (Booking* booking : bookings) if (booking->getBookingId() == bookingId) return booking;
        return nullptr;
    }
    bool cancelBooking(int bookingId) {
        Booking* booking = findBooking(bookingId);
        if (booking == nullptr) { cout << "Booking not found.\n"; return false; }
        if (booking->getStatus() != BookingStatus::CONFIRMED) {
            cout << "Only confirmed bookings can be cancelled.\n"; return false;
        }
        booking->cancel();
        cout << "Booking cancelled. Seats are AVAILABLE again.\n";
        return true;
    }
    void showTicket(int bookingId) const {
        Booking* booking = findBooking(bookingId);
        if (booking == nullptr) { cout << "Booking not found.\n"; return; }
        ticketPrinter.print(*booking);
    }
};

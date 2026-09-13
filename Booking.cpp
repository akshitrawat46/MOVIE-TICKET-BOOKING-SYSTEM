#include <vector>
using namespace std;

class Booking {
    static int nextBookingId;
    int bookingId;
    Show* show;
    Customer* customer;
    vector<ShowSeat*> bookedSeats;
    double bookingAmount;
    BookingStatus status;
    Payment* payment;
public:
    Booking(Show* show, Customer* customer, const vector<ShowSeat*>& seats, double amount)
        : bookingId(nextBookingId++), show(show), customer(customer), bookedSeats(seats),
          bookingAmount(amount), status(BookingStatus::PENDING), payment(nullptr) {}
    int getBookingId() const { return bookingId; }
    Show* getShow() const { return show; }
    Customer* getCustomer() const { return customer; }
    const vector<ShowSeat*>& getBookedSeats() const { return bookedSeats; }
    double getBookingAmount() const { return bookingAmount; }
    BookingStatus getStatus() const { return status; }
    Payment* getPayment() const { return payment; }
    void setPayment(Payment* payment) { this->payment = payment; }
    void confirm() { status = BookingStatus::CONFIRMED; }
    void cancel() {
        for (ShowSeat* showSeat : bookedSeats) showSeat->cancelSeat();
        status = BookingStatus::CANCELLED;
    }
};

int Booking::nextBookingId = 1001;

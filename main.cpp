#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Course rule: one class per file and no header files.
#include "Types.cpp"
#include "Movie.cpp"
#include "Seat.cpp"
#include "ShowSeat.cpp"
#include "Screen.cpp"
#include "Cinema.cpp"
#include "Show.cpp"
#include "Customer.cpp"
#include "Payment.cpp"
#include "UpiPayment.cpp"
#include "CardPayment.cpp"
#include "CashPayment.cpp"
#include "PriceCalculator.cpp"
#include "Booking.cpp"
#include "TicketPrinter.cpp"
#include "BookingService.cpp"

int main() {
    Cinema cinema("PVR City Mall");
    cinema.addScreen(1, 10);
    cinema.addScreen(2, 10);
    Movie movie1("Interstellar", "English", 169);
    Movie movie2("3 Idiots", "Hindi", 170);
    vector<Show> shows;
    shows.emplace_back(1, &movie1, const_cast<Screen*>(&cinema.getScreens()[0]), "10:00 AM");
    shows.emplace_back(2, &movie1, const_cast<Screen*>(&cinema.getScreens()[0]), "02:00 PM");
    shows.emplace_back(3, &movie2, const_cast<Screen*>(&cinema.getScreens()[1]), "06:00 PM");
    Customer customer("Akshit", "9876543210");
    BookingService bookingService;

    while (true) {
        cout << "\n===== MOVIE TICKET BOOKING =====\n"
             << "1. List movies\n2. List shows\n3. Show seats\n"
             << "4. Book ticket\n5. Cancel booking\n6. Print ticket\n0. Exit\n"
             << "Enter choice: ";
        int choice;
        if (!(cin >> choice)) { cout << "Invalid input. Program stopped safely.\n"; return 0; }
        if (choice == 0) break;
        if (choice == 1) {
            cout << "\nMovies currently playing:\n";
            cout << "1. " << movie1.getTitle() << " (" << movie1.getLanguage() << ", " << movie1.getDurationMinutes() << " min)\n";
            cout << "2. " << movie2.getTitle() << " (" << movie2.getLanguage() << ", " << movie2.getDurationMinutes() << " min)\n";
        } else if (choice == 2) {
            cout << "\nShows:\n";
            for (const Show& show : shows)
                cout << show.getShowId() << ". " << show.getMovie()->getTitle() << " | Screen " << show.getScreen()->getScreenNumber() << " | " << show.getStartTime() << '\n';
        } else if (choice == 3) {
            int showId; cout << "Enter show ID: "; cin >> showId;
            if (showId < 1 || showId > (int)shows.size()) cout << "Invalid show ID.\n";
            else shows[showId - 1].displaySeats();
        } else if (choice == 4) {
            int showId, seatNumber, paymentChoice;
            cout << "Enter show ID: "; cin >> showId;
            if (showId < 1 || showId > (int)shows.size()) { cout << "Invalid show ID.\n"; continue; }
            Show& show = shows[showId - 1]; show.displaySeats();
            cout << "Enter seat number to book: "; cin >> seatNumber;
            cout << "Payment: 1.UPI  2.Card  3.Cash: "; cin >> paymentChoice;
            if (paymentChoice == 1) { UpiPayment payment; bookingService.createBooking(customer, show, {seatNumber}, payment); }
            else if (paymentChoice == 2) { CardPayment payment; bookingService.createBooking(customer, show, {seatNumber}, payment); }
            else if (paymentChoice == 3) { CashPayment payment; bookingService.createBooking(customer, show, {seatNumber}, payment); }
            else cout << "Invalid payment choice. Nothing changed.\n";
        } else if (choice == 5) {
            int bookingId; cout << "Enter booking ID: "; cin >> bookingId; bookingService.cancelBooking(bookingId);
        } else if (choice == 6) {
            int bookingId; cout << "Enter booking ID: "; cin >> bookingId; bookingService.showTicket(bookingId);
        } else cout << "Invalid menu choice. Please try again.\n";
    }
    cout << "Thank you for using the Movie Ticket Booking System.\n";
    return 0;
}

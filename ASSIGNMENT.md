# TCS-504 System Design — Assignment 1
## Movie Ticket Booking System

**Course:** B.Tech. CSE Semester 5  
**Subject:** System Design — TCS-504  
**Submission date:** 07-September-2026

## A. Requirement Analysis

### Functional Requirements
| ID | Requirement |
|---|---|
| FR1 | The system shall display all movies currently playing with title, language and duration. |
| FR2 | The system shall display shows for a chosen movie, including screen and start time. |
| FR3 | The system shall display every seat of a chosen show with AVAILABLE or BOOKED status. |
| FR4 | The system shall book one or more available seats and reject an already-booked seat without changing it. |
| FR5 | The system shall calculate price by seat type: SILVER ₹150, GOLD ₹250, PLATINUM ₹400. |
| FR6 | The system shall accept UPI, Card or Cash; failed payment must not confirm the booking and must release seats. |
| FR7 | The system shall print booking ID, movie, screen, time, seat numbers and total amount. |
| FR8 | The system shall cancel a confirmed booking and make its seats AVAILABLE again. |

### Non-Functional Requirements
1. **Modularity:** one class per file and no header files, as required.
2. **Extensibility:** payment is abstract, so new payment implementations can be added without changing booking orchestration.
3. **Validation:** invalid menu, show and seat input gives a clear message and does not crash.
4. **Maintainability:** movie/seat/show entities, pricing, payment, printing and booking orchestration have separate responsibilities.

## B. Noun–Verb Analysis

| Noun | Class? | Reason |
|---|---|---|
| Movie | Yes | Has independent data and identity. |
| Seat | Yes | Represents a physical seat, type and price. |
| Seat layout | No | It is a view of ShowSeat objects; `Show::displaySeats()` is enough. |
| Screen | Yes | Represents an auditorium and owns seats. |
| Cinema | Yes | Represents theatre and owns screens. |
| Show | Yes | Represents one movie screening on a screen at a time. |
| ShowSeat | Yes | Stores one seat's status for one show. |
| Customer | Yes | Has customer identity data. |
| Booking | Yes | Stores booking ID, seats, amount and status. |
| Payment | Yes | Defines a payment contract. |
| UPI/Card/Cash | Yes | Different payment implementations. |
| Price | No | Behavior belongs to `PriceCalculator`. |
| Ticket | No | Only formatting/printing is required, handled by `TicketPrinter`. |
| Booking service | Yes | Coordinates the end-to-end flow. |

Important verbs map to methods: list → menu display; display → `displaySeats()`; book → `bookSeat()` / `createBooking()`; pay → `Payment::pay()`; calculate → `calculateTotal()`; print → `TicketPrinter::print()`; cancel → `cancelBooking()` / `cancelSeat()`.

## C. Classes and Responsibilities

| Class | Knows | Does | Must NOT do |
|---|---|---|---|
| Movie | title, language, duration | Provides movie data | Manage seats/payments |
| Seat | number, type | Provides identity and price | Track show booking status |
| Screen | number, physical seats | Owns/creates seats | Handle payment |
| Cinema | name, screens | Owns/creates screens | Calculate prices |
| Show | movie, screen, time, ShowSeats | Finds/displays seats | Process payment |
| ShowSeat | Seat, status | Book/cancel one seat | Calculate booking total |
| Customer | name, phone | Provides identity | Directly manage payment |
| Booking | ID, show, customer, seats, amount, status | Confirm/cancel booking | Print ticket or calculate price |
| Payment | pay contract | Defines payment abstraction | Manage movie/seat data |
| UpiPayment/CardPayment/CashPayment | payment method | Perform payment | Manage bookings |
| PriceCalculator | selected seats | Calculates total | Book/print |
| TicketPrinter | booking information | Formats/prints ticket | Change booking state |
| BookingService | calculators, printer, bookings | Orchestrates workflow | Own movie/seat data |
| main | application objects/input | Console menu and input | Contain domain algorithms |

## D. Relationships and Lifetime Justification

| Pair | Relationship | Lifetime test |
|---|---|---|
| Cinema–Screen | Composition | Screens are created/owned by Cinema; destroying Cinema destroys its screens. |
| Screen–Seat | Composition | Seats are created/owned by Screen; destroying Screen destroys those seats. |
| Show–Movie | Aggregation | Movie exists independently and can have multiple shows; destroying Show does not destroy Movie. |
| Show–Screen | Association | Show refers to an existing Screen; destroying Show does not destroy Screen. |
| Show–ShowSeat | Composition | Show creates its ShowSeat status objects; destroying Show destroys them. |
| Booking–Customer | Association | Customer exists independently; destroying Booking does not destroy Customer. |
| Booking–ShowSeat | Aggregation | Booking references ShowSeat objects owned by Show; destroying Booking does not destroy them. |
| Booking–Payment | Association | Booking receives a Payment reference; neither owns the other. |
| Payment–UpiPayment | Inheritance | UPI is a specialized Payment implementation, not a lifetime whole-part relation. Same for Card/Cash. |
| BookingService–Booking | Association | Service coordinates and references bookings; a booking has independent identity/lifetime. |

## E. Class Diagram
See `docs/class-diagram.puml`. It includes three compartments, visibility markers, multiplicities, composition/aggregation/association and the abstract Payment hierarchy.

## F. Sequence Diagram
See `docs/sequence-diagram.puml` for the required use case: customer books one seat and pays by UPI. It includes the required lifelines, activation bars, synchronous calls, return messages and `<<create>>` messages.

## G. Modular Working Code + Demo

Build:
```bash
g++ -std=c++17 main.cpp -o movie_booking
./movie_booking
```

Expected flow:
```text
===== MOVIE TICKET BOOKING =====
1. List movies
2. List shows
3. Show seats
4. Book ticket
5. Cancel booking
6. Print ticket
0. Exit

Enter choice: 4
Enter show ID: 1
Enter seat number to book: 1
Payment: 1.UPI  2.Card  3.Cash: 1
Processing UPI payment of Rs.150...
Payment successful. Booking confirmed.

================ TICKET ================
Booking ID : 1001
Customer   : Akshit
Movie      : Interstellar
Screen     : 1
Time       : 10:00 AM
Seats      : 1
Amount     : Rs.150.00
Status     : CONFIRMED
=========================================
```

Edge cases handled: already-booked seat is rejected; invalid seat/show/menu choice is rejected safely; failed payment releases seats; cancellation releases seats.

### OOP concepts
- **Encapsulation:** private seat status and booking data with controlled methods.
- **Abstraction:** abstract `Payment` with pure virtual `pay()`.
- **Inheritance:** UPI/Card/Cash derive from Payment.
- **Runtime polymorphism:** payment is used through a `Payment&`.
- **Compile-time polymorphism:** overloaded `Movie` constructors.
- **Static member:** `Booking::nextBookingId` generates unique IDs.
- **this:** used in `Booking::setPayment()`.
- **Composition:** Cinema→Screen, Screen→Seat, Show→ShowSeat.
- **Aggregation:** Show→Movie, Booking→ShowSeat.

## H. SOLID Mapping

| Principle | Application |
|---|---|
| S — Single Responsibility | PriceCalculator calculates, TicketPrinter prints, payment classes pay, BookingService orchestrates. |
| O — Open/Closed | New payment types can implement Payment without changing booking flow. |
| L — Liskov Substitution | UPI/Card/Cash can all substitute for Payment. |
| I — Interface Segregation | Payment exposes only operations common to every payment type. |
| D — Dependency Inversion | BookingService receives `Payment&` rather than constructing a concrete payment internally. |

**Deliberately not done:** a separate Ticket entity was not created because the assignment only requires ticket formatting/printing; `TicketPrinter` provides that single responsibility without unnecessary persistent state.

## Clean Code Checklist
- Intention-revealing names.
- No number-series variable names.
- Focused methods and responsibilities.
- Pricing encapsulated in Seat/PriceCalculator.
- No repeated payment logic.
- Validation before changing seat state.
- Printing does not book/cancel seats.

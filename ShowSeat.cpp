class ShowSeat {
    Seat* seat;
    SeatStatus seatStatus;
public:
    explicit ShowSeat(Seat* seat) : seat(seat), seatStatus(SeatStatus::AVAILABLE) {}
    Seat* getSeat() const { return seat; }
    SeatStatus getStatus() const { return seatStatus; }
    bool isAvailable() const { return seatStatus == SeatStatus::AVAILABLE; }
    bool bookSeat() {
        if (!isAvailable()) return false;
        seatStatus = SeatStatus::BOOKED;
        return true;
    }
    void cancelSeat() { seatStatus = SeatStatus::AVAILABLE; }
};

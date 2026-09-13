#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Show {
    int showId;
    Movie* movie;
    Screen* screen;
    string startTime;
    vector<ShowSeat> showSeats;
public:
    Show(int showId, Movie* movie, Screen* screen, const string& startTime)
        : showId(showId), movie(movie), screen(screen), startTime(startTime) {
        for (const Seat& seat : screen->getSeats())
            showSeats.emplace_back(const_cast<Seat*>(&seat));
    }
    int getShowId() const { return showId; }
    Movie* getMovie() const { return movie; }
    Screen* getScreen() const { return screen; }
    const string& getStartTime() const { return startTime; }
    vector<ShowSeat>& getShowSeats() { return showSeats; }
    ShowSeat* findSeat(int number) {
        for (ShowSeat& showSeat : showSeats)
            if (showSeat.getSeat()->getNumber() == number) return &showSeat;
        return nullptr;
    }
    void displaySeats() const {
        cout << "\nScreen " << screen->getScreenNumber() << " | " << movie->getTitle()
             << " | " << startTime << "\n";
        for (const ShowSeat& showSeat : showSeats) {
            cout << "[" << showSeat.getSeat()->getNumber() << ": "
                 << seatTypeName(showSeat.getSeat()->getType()) << " - "
                 << (showSeat.isAvailable() ? "AVAILABLE" : "BOOKED") << "] ";
            if (showSeat.getSeat()->getNumber() % 5 == 0) cout << '\n';
        }
        cout << '\n';
    }
};

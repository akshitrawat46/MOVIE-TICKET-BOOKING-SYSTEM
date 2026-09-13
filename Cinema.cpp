#include <vector>
#include <string>
using namespace std;

class Cinema {
    string name;
    vector<Screen> screens;
public:
    explicit Cinema(const string& name) : name(name) {}
    void addScreen(int screenNumber, int seatCount) { screens.emplace_back(screenNumber, seatCount); }
    const string& getName() const { return name; }
    const vector<Screen>& getScreens() const { return screens; }
};

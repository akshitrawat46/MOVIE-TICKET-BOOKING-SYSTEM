#include <string>
using namespace std;

class Movie {
    string title;
    string language;
    int durationMinutes;
public:
    Movie(const string& title) : Movie(title, "Hindi", 120) {}
    Movie(const string& title, const string& language, int durationMinutes)
        : title(title), language(language), durationMinutes(durationMinutes) {}
    const string& getTitle() const { return title; }
    const string& getLanguage() const { return language; }
    int getDurationMinutes() const { return durationMinutes; }
};

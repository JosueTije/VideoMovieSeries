#include "Episode.h"

Episode::Episode(string title, int season) : title(title), season(season) {}

void Episode::addRating(int rating) {
    if (rating >= 1 && rating <= 5) {
        ratings.push_back(rating);
    }
}

double Episode::getAverageRating() const {
    if (ratings.empty()) return 0;
    return accumulate(ratings.begin(), ratings.end(), 0.0) / ratings.size();
}

void Episode::display(ostream os) {
    os << "Title: " << title << ", Season: " << season << ", Avg Rating: " << getAverageRating();
}

ostream operator<<(ostream os, Episode episode) {
    episode.display(os);
    return os;
}

#include "Video.h"

Video::Video(int id, string name, int length, string genre)
    : id(id), name(name), length(length), genre(genre) {}

void Video::addRating(int rating) {
    if (rating >= 1 && rating <= 5) {
        ratings.push_back(rating);
    }
}

double Video::getAverageRating() {
    if (ratings.empty()) return 0;
    return accumulate(ratings.begin(), ratings.end(), 0.0) / ratings.size();
}

void Video::display(ostream os) {
    os << "ID: " << id << ", Name: " << name << ", Length: " << length 
       << " min, Genre: " << genre << ", Avg Rating: " << getAverageRating();
}

ostream& operator<<(ostream os, Video video) {
    video.display(os);
    return os;
}

string Video::getGenre() {
    return genre;
}
#include "Movies.h"

Movies::Movies(int id, const string& name, int length, const string& genre)
    : Video(id, name, length, genre) {}

void Movies::display(ostream& os) const {
    os << "Movie: ";
    Video::display(os);
}
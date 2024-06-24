#include "Series.h"

Series::Series(int id, string name, int length, string genre)
    : Video(id, name, length, genre) {}

void Series::addEpisode(Episode episode) {
    episodes.push_back(episode);
}

void Series::display(ostream os) {
    os << "Series: ";
    Video::display(os);
    os << ", Episodes: ";
    for (const auto& episode : episodes) {
        os << "\n  ";
        episode.display(os);
    }
    os << "\n";
}



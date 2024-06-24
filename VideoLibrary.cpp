#include "VideoLibrary.h"
#include <fstream>
#include <sstream>

VideoLibrary::~VideoLibrary() {
    for (auto video : videos) {
        delete video;
    }
}

void VideoLibrary::readData(const string& filename) {
    ifstream infile(filename);
    if (!infile.is_open()) {
        cerr << "Error opening file" << endl;
        return;
    }

    string line;
    Series* currentSeries = nullptr;

    while (getline(infile, line)) {
        stringstream ss(line);
        string type;
        getline(ss, type, ',');

        if (type == "MOVIE") {
            int id, length;
            string name, genre, ratingStr;
            getline(ss, ratingStr, ',');
            id = stoi(ratingStr);
            getline(ss, name, ',');
            getline(ss, ratingStr, ',');
            length = stoi(ratingStr);
            getline(ss, genre, ',');

            Movies* movies = new Movies(id, name, length, genre);

            while (getline(ss, ratingStr, ',')) {
                movies->addRating(stoi(ratingStr));
            }

            videos.push_back(movies);
        } else if (type == "SERIES") {
            int id, length;
            string name, genre, ratingStr;
            getline(ss, ratingStr, ',');
            id = stoi(ratingStr);
            getline(ss, name, ',');
            getline(ss, ratingStr, ',');
            length = stoi(ratingStr);
            getline(ss, genre, ',');

            currentSeries = new Series(id, name, length, genre);
            videos.push_back(currentSeries);
        } else if (type == "EPISODE" && currentSeries != nullptr) {
            string title, ratingStr;
            int season;
            getline(ss, title, ',');
            getline(ss, ratingStr, ',');
            season = stoi(ratingStr);

            Episode episode(title, season);

            while (getline(ss, ratingStr, ',')) {
                episode.addRating(stoi(ratingStr));
            }

            currentSeries->addEpisode(episode);
        }
    }

    infile.close();
}

void VideoLibrary::displayAll() const {
    for (const auto& video : videos) {
        cout << *video << endl;
    }
}

void VideoLibrary::displayByGenre(const string& genre) const {
    for (const auto& video : videos) {
        if (video->getGenre() == genre) {
            cout << *video << endl;
        }
    }
}

void VideoLibrary::displayMoviesByRating(double rating) const {
    for (const auto& video : videos) {
        if (auto movie = dynamic_cast<Movies*>(video)) {
            if (movie->getAverageRating() >= rating) {
                cout << *movie << endl;
            }
        }
    }
}

#ifndef VIDEOLIBRARY_H
#define VIDEOLIBRARY_H

#include <iostream>
#include <vector>
#include "Video.h"
#include "Movies.h"
#include "Series.h"
#include "Episode.h"

using namespace std;

class VideoLibrary {
    vector<Video*> videos;

public:
    ~VideoLibrary();
    void readData(const string& filename);
    void displayAll() const;
    void displayByGenre(const string& genre) const;
    void displayMoviesByRating(double rating) const;
};

#endif

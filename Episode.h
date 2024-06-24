#ifndef EPISODE_H
#define EPISODE_H

#include <iostream>
#include <vector>
#include <numeric>
#include <string>

using namespace std;

class Episode {
    string title;
    int season;
    vector<int> ratings;

public:
    Episode(string title, int season);
    void addRating(int rating);
    double getAverageRating();
    void display(ostream os);
};

#endif


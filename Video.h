#ifndef VIDEO_H
#define VIDEO_H

#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <fstream>
#include <sstream>

using namespace std;

class Video {
protected:
    int id;
    string name;
    int length;
    string genre;
    vector<int> ratings;

public:
    Video(int id, string name, int length, string genre);
    Video() = default;

    void addRating(int rating);
    virtual double getAverageRating();
    virtual void display(ostream os);
    string getGenre();

    friend ostream operator<<(ostream os, Video video);
};

#endif

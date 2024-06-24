#ifndef SERIES_H
#define SERIES_H

#include "Video.h"
#include "Episode.h"
#include <vector>

class Series : public Video {
    vector<Episode> episodes;

public:
    Series(int id, string name, int length, string genre);
    void addEpisode(Episode episode);
    void display(ostream os) override;
};

#endif
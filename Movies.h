#ifndef MOVIE_H
#define MOVIE_H

#include "Video.h"

class Movies : public Video {
public:
    Movies(int id, const string& name, int length, const string& genre);
    void display(ostream& os) const override;
};

#endif

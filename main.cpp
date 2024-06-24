#include <iostream>
#include "VideoLibrary.h"

using namespace std;

int main() {
    VideoLibrary library;

    library.readData("video.txt");

    cout << "All Videos:" << endl;
    library.displayAll();

    cout << "\nMovies with rating 4.0 and above:" << endl;
    library.displayMoviesByRating(4.0);

    cout << "\nVideos in the Action genre:" << endl;
    library.displayByGenre("Action");

    return 0;
}

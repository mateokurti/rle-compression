#include <iostream>
#include <vector>
using namespace std;

const int M = 5;
const int N = 8;
const int MAX_RLE = M * N;

struct Color {
    int red;    // R
    int green;  // G
    int blue;   // B

    Color(int r=255, int g=255, int b=255) {
        red = r;
        green = g;
        blue = b;
    }    
};

void display_image(vector<vector<Color> > img) {
    Color pixel;
    for (int i=0; i<img.size(); i++) {
        for (int j=0; j<img[i].size(); j++) {
            pixel = img[i][j];
            cout << pixel.red << " " << pixel.green << " " << pixel.blue << "\t";
        }
        cout << "\n";
    }
}

void reset_image(vector<vector<Color> >& img) {
    for (int i=0; i<img.size(); i++) {
        for (int j=0; j<img[i].size(); j++) {
            img[i][j] = Color(255, 255, 255);
        }
    }
}

int main() {
    vector<vector<Color> > img;

    for (int i=0; i<M; i++) {
        vector<Color> row;
        for (int j=0; j<N; j++) {
            row.push_back(Color(1,1,1));
        }
        img.push_back(row);
    }

    display_image(img);
}
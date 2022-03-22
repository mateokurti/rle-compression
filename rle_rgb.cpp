#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
using namespace std;

const int M = 5;
const int N = 8;
const int MAX_RLE = M * N;

class Color {
    public:
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
    cout << "\n\nDisplayed Image:\n\n";
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

void generate_image(vector<vector<Color> >& img) {
    // THIS IS AN UGLY WAY TO DO IT, but it works...
    // TODO: Find a more creative way to generate images
    // Either need to upgrade to C++11 or find a better way to initialize vectors
    vector<Color> colors;
    colors.push_back(Color(0,0,0));
    colors.push_back(Color(1,2,3));
    // colors.push_back(Color(4,5,6));
    // colors.push_back(Color(7,8,9));
    // colors.push_back(Color(1,3,7));
    // NOTE: Chose numbers 0-9 instead of 0-255 to make the display easies (same number of digits)

    srand(time(0));
    for (int i=0; i<M; i++) {
        vector<Color> row;
        for (int j=0; j<N; j++) {
            row.push_back(colors[rand() % 10 % 2]);
        }
        img.push_back(row);
    }
}

bool compare_colors(Color c1, Color c2) {
    // TODO: Make Operator Overloading working instead of using this method
    return c1.red == c2.red && c1.green == c2.green && c1.blue == c2.blue;
}

int rle_rgb_encode(vector<vector<Color> > img, int rle[4][MAX_RLE]) {
    int rle_size = 0;
    int count = 0;
    Color previous_pixel = img[0][0];

    for (int i=0; i<img.size(); i++) {
        for (int j=0; j<img[i].size(); j++) {
            if (compare_colors(img[i][j], previous_pixel)) {
                count++;
            } else {
                rle[0][rle_size] = previous_pixel.red;
                rle[1][rle_size] = previous_pixel.green;
                rle[2][rle_size] = previous_pixel.blue;
                rle[3][rle_size] = count;
                rle_size++;
                count = 1;
            }
            previous_pixel = img[i][j];
        }
    }

    if (count > 0) {
        rle[0][rle_size] = previous_pixel.red;
        rle[1][rle_size] = previous_pixel.green;
        rle[2][rle_size] = previous_pixel.blue;
        rle[3][rle_size] = count;
        rle_size++;
    }

    return rle_size;
}

void rle_rgb_decode(int rle[4][MAX_RLE], int rle_size, vector<vector<Color> >& img) {
    int m = 0, n = 0;
    for (int i=0; i<rle_size; i++) {
        for (int j=0; j<rle[3][i]; j++) {
            img[m][n].red = rle[0][i];
            img[m][n].green = rle[1][i];
            img[m][n].blue = rle[2][i];
            if (n < N-1) {
                n++;
            } else {
                n = 0;
                m += 1;
            }
        }
    }
}

int main() {
    vector<vector<Color> > img;
    generate_image(img);
    display_image(img);

    int rle_size;
    int rle[4][MAX_RLE];

    // Encode RGB image to RLE
    rle_size = rle_rgb_encode(img, rle);

    reset_image(img);
    display_image(img);

    // Decode RLE to RGB image
    rle_rgb_decode(rle, rle_size, img);
    display_image(img);
}
#include <iostream>
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
    // TODO: Find a more creative way to generate images
    for (int i=0; i<M; i++) {
        vector<Color> row;
        for (int j=0; j<N; j++) {
            row.push_back(Color(1,1,1));
        }
        img.push_back(row);
    }
}

bool compare_colors(Color c1, Color c2) {
    // TODO: Make Operator Overloading working instead of using this method
    return c1.red = c2.red && c1.green == c2.green && c1.blue == c2.blue;
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
                rle[0][rle_size] = img[i][j].red;
                rle[1][rle_size] = img[i][j].green;
                rle[2][rle_size] = img[i][j].blue;
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

int main() {
    vector<vector<Color> > img;
    generate_image(img);
    display_image(img);

    int rle_size;
    int rle[4][MAX_RLE];

    // Encode RGB image to RLE
    rle_size = rle_rgb_encode(img, rle);
    
}
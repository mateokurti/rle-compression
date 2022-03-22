#include <iostream>
#include <vector>
using namespace std;

const int M = 5;
const int N = 8;
const int MAX_RLE = M * N;

void display_image(int img[][N], int M, int N) {
    cout << "\n\nDisplayed Image:\n\n";
    int pixel;
    for (int i=0; i<M; i++) {
        for (int j=0; j<N; j++) {
            pixel = img[i][j];
            if (pixel == 255) {
                cout << "  "; // Representation of white
            } else {
                cout << "* "; // Representation of any other color
            }
        }
        cout << "\n";
    }
    cout << "\n";
}


void reset_image(int img[][N], int M, int N) {
    for (int i=0; i<M; i++) {
        for (int j=0; j<N; j++) {
            img[i][j] = 255;
        }
    }
}


int rle_grayscale_encode(int img[][N], int M, int N, int rle[2][MAX_RLE]) {
    int rle_size = 0;
    int count = 0;
    int previous_pixel = img[0][0];

    for (int i=0; i<M; i++) {
        for (int j=0; j<N; j++) {
            if (img[i][j] == previous_pixel) {
                count++;
            } else {
                rle[0][rle_size] = previous_pixel;
                rle[1][rle_size] = count;
                rle_size++;
                count = 1;
            }
            previous_pixel = img[i][j];
        }
    }

    if (count > 0) {
        rle[0][rle_size] = previous_pixel;
        rle[1][rle_size] = count;
        rle_size++;
    }

    return rle_size;
}

void rle_grayscale_decode(int rle[2][MAX_RLE], int rle_size, int img[][N]) {
    int m = 0, n = 0;
    for (int i=0; i<rle_size; i++) {
        for (int j=0; j<rle[1][i]; j++) {
            img[m][n] = rle[0][i];
            if (n < N-1) {
                n += 1;
            } else {
                n = 0;
                m += 1;
            }
        }
    }
}


int main() {
    int img[M][N] = {
        {0, 255, 255, 0, 255, 0, 0, 0},
        {0, 255, 255, 0, 255, 255, 0, 255},
        {0, 0, 0, 0, 255, 255, 0, 255},
        {0, 255, 255, 0, 255, 255, 0, 255},
        {0, 255, 255, 0, 255, 0, 0, 0}
    };

    display_image(img, M, N);

    int rle_size;
    int rle[2][MAX_RLE];

    // Encode GrayScale image to RLE
    rle_size = rle_grayscale_encode(img, M, N, rle);
    
    reset_image(img, M, N);

    // Decode RLE to GrayScale
    rle_grayscale_decode(rle, rle_size, img);
    display_image(img, M, N);   
}
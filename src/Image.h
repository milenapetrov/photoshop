#include <iostream>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

struct Pixel {
    unsigned char R;
    unsigned char G;
    unsigned char B;
    Pixel();
    Pixel(unsigned char
          red, unsigned char
          green, unsigned char
          blue){
        R = red;
        G = green;
        B = blue;
    }
};

struct Header{
    char idLength;
    char colorMapType;
    char dataTypeCode;
    short colorMapOrigin;
    short colorMapLength;
    char colorMapDepth;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char bitsPerPixel;
    char imageDescriptor;
    unsigned int size;
    vector<Pixel> pixels;
};

class Image {
public:
    Header imgHead;
//    Pixel pix;
    Image();
    Image(Header data);
    //Image(const string& fileName);
    ~Image();
    Header ReadTga(const string& fileName);
    void writeTga(const string &fileName, Header& img);
    bool Compare(vector<Pixel> pix, vector<Pixel> pix2);
    void Multiply(Header& img, Header& img2);
    void Scale(Header* img);
    void Subtract(Header* img, Header* img2);
    void Screen(Header* img, Header* img2);
    void Overlay(Header* img, Header* img2);
    void Add200(Header* img);
    void LoadR(Header* img);
    void LoadG(Header* img);
    void LoadB(Header* img);
    void Combine(Header* img, Header* img2, Header* img3);
    void Rotate180(Header* img, Header* img2);
};


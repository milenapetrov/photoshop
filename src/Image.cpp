#include <iostream>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "Image.h"
using namespace std;

Pixel::Pixel(){}

Image::Image() {}

Image::Image(Header data){
    imgHead = data;
}

Image::~Image(){}

Header Image::ReadTga(const string& fileName) {
    ifstream file(fileName, ios_base::binary);
    if(!file){
        cout << "not open" << endl;
    }
    Header head;
    short t;
    //read header
    file.read(&head.idLength, sizeof(head.idLength)); //ID length
    //cout << (int)head.idLength << endl;
    file.read(&head.colorMapType, sizeof(head.colorMapType)); //colormap type

    file.read(&head.dataTypeCode, sizeof(head.dataTypeCode)); //data type

    file.read((char*)&head.colorMapOrigin, sizeof(head.colorMapOrigin)); //colormap orig

    file.read((char*)&head.colorMapLength, sizeof(head.colorMapLength)); //colormap length

    file.read((char*)&head.colorMapDepth, sizeof(head.colorMapDepth));//depth

    file.read((char*)&head.xOrigin, sizeof(head.xOrigin)); //x origin

    file.read((char*)&head.yOrigin, sizeof(head.yOrigin)); //y

    file.read((char*)&head.width, sizeof(head.width)); //width
    //cout << (int)head.width << endl;
    file.read((char*)&head.height, sizeof(head.height)); //height
    //cout << (int)head.height << endl;
    file.read((char*)&head.bitsPerPixel, sizeof(head.bitsPerPixel));//pix depth

    file.read((char*)&head.imageDescriptor, sizeof(head.imageDescriptor)); //image desc.

//    imgHead.width = head.width;
//    imgHead.height = head.height;

    //read pixels
    //int imageSize = head.height * head.width * (head.bitsPerPixel/8);   ??
    Pixel pix;
    //vector<Pixel> pixels;
    head.size = head.width*head.height;
    Pixel* color = new Pixel;
    for (int i = 0; i < head.size; ++i) {
            file.read((char*)&color->B, 1);

            file.read((char*)&color->G, 1);

            file.read((char*)&color->R, 1);

            pix = Pixel(color->B, color->G, color->R);
            head.pixels.push_back(pix);

    }
    delete color;
    file.close();
    return head;
}

void Image::writeTga(const string& fileName, Header& img){
    ofstream out(fileName, ios_base::binary);
    out.write(&img.idLength,sizeof(img.idLength));
    out.write(&img.colorMapType, sizeof(img.colorMapType));
    out.write(&img.dataTypeCode, sizeof(img.dataTypeCode));
    out.write((char*)&img.colorMapOrigin, sizeof(img.colorMapOrigin));
    out.write((char*)&img.colorMapLength, sizeof(img.colorMapLength));
    out.write((char*)&img.colorMapDepth, sizeof(img.colorMapDepth));
    out.write((char*)&img.xOrigin, sizeof(img.xOrigin));
    out.write((char*)&img.yOrigin, sizeof(img.yOrigin));
    out.write((char*)&img.width, sizeof(img.width));
    out.write((char*)&img.height, sizeof(img.height));
    out.write((char*)&img.bitsPerPixel, sizeof(img.bitsPerPixel));
    out.write((char*)&img.imageDescriptor, sizeof(img.imageDescriptor));

    for (int i = 0; i < img.size; ++i) {
        //out.write((char*)&img.imgHead.pixels[i], sizeof(img.imgHead.pixels[i]));
       // out.write((char*)&img.pixels[i], sizeof(img.pixels[i]));
        out.write((char*)&img.pixels[i].R, sizeof(img.pixels[i].R));
        out.write((char*)&img.pixels[i].G, sizeof(img.pixels[i].G));
        out.write((char*)&img.pixels[i].B, sizeof(img.pixels[i].B));
    }
    out.close();
}

bool Image::Compare(vector<Pixel> pix, vector<Pixel> pix2) {
    for (int i = 0; i < pix.size(); i++) {
        if(pix[i].B != pix2[i].B || pix[i].G != pix2[i].G || pix[i].R != pix[i].R){
            return false;
        }
    }
    return true;
}

void Image::Multiply(Header& img, Header& img2){
    //Header newImg;
    double prod;
    for (int i = 0; i < img.size; ++i) {
        prod = (((double)(img.pixels[i].B))*((double)(img2.pixels[i].B))/255) +0.5f;
        img.pixels[i].B = (unsigned char)prod;
        prod = (((double)(img.pixels[i].G))*((double)(img2.pixels[i].G))/255) +0.5f;
        img.pixels[i].G = (unsigned char)prod;
        prod = (((double)(img.pixels[i].R))*((double)(img2.pixels[i].R))/255) +0.5f;
        img.pixels[i].R = (unsigned char)prod;
    }
}

void Image::Subtract(Header *img, Header *img2) {
    for (int i = 0; i < img->size; ++i) {
        double b = (double)img2->pixels[i].B - (double)img->pixels[i].B;
        double g = (double)img2->pixels[i].G - (double)img->pixels[i].G;
        double r = (double)img2->pixels[i].R - (double)img->pixels[i].R;
        if(b < 0)
            b = 0;
        if(g < 0)
            g = 0;
        if(r < 0)
            r = 0;
        img->pixels[i].B = b;
        img->pixels[i].G = g;
        img->pixels[i].R = r;
    }
}

//screen 255 - (255-A)*(255-B)
void Image::Screen(Header* img, Header* img2){
    for (int i = 0; i < img->size; ++i) {
        img->pixels[i].B = 255 - ((float)(255-img->pixels[i].B)*(float)(255-img2->pixels[i].B))/255 +0.5f;
        img->pixels[i].G = 255 - ((float)(255-img->pixels[i].G)*(float)(255-img2->pixels[i].G))/255 + 0.5f;
        img->pixels[i].R = 255 - ((float)(255-img->pixels[i].R)*(float)(255-img2->pixels[i].R))/255 +0.5f;
    }
}

void Image::Overlay(Header *img, Header *img2) {
    for (int i = 0; i < img->size; ++i) {
        if((double)(img2->pixels[i].R) <= (255.0/2.0)){
            img->pixels[i].R = 2 * (img->pixels[i].R)*(img2->pixels[i].R)/255.0 + 0.5f;
        }else{
            img->pixels[i].R = 255- img->pixels[i].R;
            img2->pixels[i].R = 255- img2->pixels[i].R;
            img->pixels[i].R= 2 * img->pixels[i].R *img2->pixels[i].R /255.0 + 0.5f;
            img->pixels[i].R = 255 - img->pixels[i].R;
        }
        if((double)(img2->pixels[i].G) > (255.0/2.0)){
            img->pixels[i].G = 255- img->pixels[i].G;
            img2->pixels[i].G = 255- img2->pixels[i].G;
            img->pixels[i].G = 2*img->pixels[i].G *img2->pixels[i].G /255.0 + 0.5f;
            img->pixels[i].G = 255 - img->pixels[i].G;
        }else{
            img->pixels[i].G = 2 * (img->pixels[i].G)*(img2->pixels[i].G)/255.0 + 0.5f;
        }
        if((float)(img2->pixels[i].B/255.0) > 0.5){
            img->pixels[i].B = 255- img->pixels[i].B;
            img2->pixels[i].B = 255- img2->pixels[i].B;
            img->pixels[i].B= 2*img->pixels[i].B*img2->pixels[i].B /255.0 + 0.5f;
            img->pixels[i].B = 255 - img->pixels[i].B;
        }else{
            img->pixels[i].B = 2 * (img->pixels[i].B)*(img2->pixels[i].B)/255.0 + 0.5f;
        }
    }
}

void Image::Add200(Header* img){
    for (int i = 0; i < img->size; ++i) {
        if(img->pixels[i].G + 200 > 255){
            img->pixels[i].G = 255;
        }else{
            img->pixels[i].G += 200;
        }
    }
}

void Image::Scale(Header *img) {
    for (int i = 0; i < img->size; ++i) {
        if(img->pixels[i].B > 63){
            img->pixels[i].B = 255;
        }else{
            img->pixels[i].B *= 4;
        }
        img->pixels[i].R = 0;

    }
}

void Image::LoadR(Header* img){
    for (int i = 0; i < img->size; ++i) {
        img->pixels[i].R = img->pixels[i].B;
        img->pixels[i].G = img->pixels[i].B;
    }
}
void Image::LoadG(Header* img){
    for (int i = 0; i < img->size; ++i) {
        img->pixels[i].R = img->pixels[i].G;
        img->pixels[i].B = img->pixels[i].G;
    }
}
void Image::LoadB(Header* img){
    for (int i = 0; i < img->size; ++i) {
        img->pixels[i].B = img->pixels[i].R;
        img->pixels[i].G = img->pixels[i].R;
    }
}

void Image::Combine(Header *r, Header *g, Header *b) {
    for (int i = 0; i < r->size; ++i) {
        r->pixels[i].G = g->pixels[i].G;
        r->pixels[i].R = b->pixels[i].R;
    }
}

void Image::Rotate180(Header* img, Header* img2){
    int k = 0;
    img2->pixels[k] = img->pixels[img->size-1];
    for(int i = img->size-1 ; i > 0 ; i--) {
        img2->pixels[i] = img->pixels[k];
        k++;
    }


}

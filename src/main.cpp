#include <iostream>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
//#include <stdlib.h>
#include "Image.h"
using namespace std;

int main() {
    Image img;

    cout << "Test1...";
    Header layer1 = img.ReadTga("input/layer1.tga");
    Header pattern1 = img.ReadTga("input/pattern1.tga");

    img.Multiply(layer1, pattern1);

    img.writeTga("output/part1.tga", layer1);
    Header part1 = img.ReadTga("examples/EXAMPLE_part1.tga");
    if(img.Compare(layer1.pixels, part1.pixels)){cout << "passed :)" << endl;}
    else{
        cout << "norp" << endl;
    }

    Image img2;
    cout << "Test2...";
    Header layer2 = img2.ReadTga("input/layer2.tga");
    Header car = img2.ReadTga("input/car.tga");

    img2.Subtract(&layer2, &car);

    img2.writeTga("output/part2.tga", layer2);
    Header part2 = img2.ReadTga("output/part2.tga");
    if(img2.Compare(layer2.pixels, part2.pixels)){
        cout << "passed :)" << endl;
    }else{
        cout << "bye.." << endl;
    }

    Image img3;
    cout<< "Test3...";
    layer1 = img3.ReadTga("input/layer1.tga");
    Header pattern2 = img3.ReadTga("input/pattern2.tga");
    Header text = img3.ReadTga("input/text.tga");

    img3.Multiply(layer1, pattern2);
    img3.Screen(&layer1, &text);

    img3.writeTga("output/part3.tga", layer1);
    Header part3 = img3.ReadTga("examples/EXAMPLE_part3.tga");
    if(img.Compare(layer1.pixels, part3.pixels)){
        cout << "passed :)" << endl;
    }else{
        cout << "bye.." << endl;
    }

    Image img4;
    cout << "Test4...";
    layer2 = img4.ReadTga("input/layer2.tga");
    Header circles = img4.ReadTga("input/circles.tga");
    img.Multiply(layer2, circles);
    img4.Subtract(&pattern2, &layer2);
    img4.writeTga("output/part4.tga", pattern2);
    Header part4 = img4.ReadTga("examples/EXAMPLE_part4.tga");
    if(img4.Compare(pattern2.pixels, part4.pixels)){
        cout << "passed :)" << endl;
    }else{
        cout << "bye.." << endl;
    }

    Image img5;
    cout<< "Test5...";
    layer1 = img5.ReadTga("input/layer1.tga");
    img5.Overlay(&layer1, &pattern1);
    img5.writeTga("output/part5.tga", layer1);
    Header part5 = img5.ReadTga("examples/Example_part5.tga");
    if(img5.Compare(layer1.pixels, part5.pixels)){
        cout << "passed :)" << endl;
    }else{
        cout << "bye.." << endl;
    }

    Image img6;
    cout<< "Test6...";
    img6.Add200(&car);
    img6.writeTga("output/part6.tga", car);
    Header part6 = img6.ReadTga("examples/EXAMPLE_part6.tga");
    if(img6.Compare(car.pixels, part6.pixels)){
        cout << "passed :)" << endl;
    }else{
        cout << "bye.." << endl;
    }

    Image img7;
    cout << "Test7...";
    car = img7.ReadTga("input/car.tga");
    img7.Scale(&car);
    img7.writeTga("output/part7.tga", car);
    Header part7 = img7.ReadTga("examples/EXAMPLE_part7.tga");
    if(img7.Compare(car.pixels, part7.pixels)){
        cout << "passed :)" << endl;
    }else{
        cout << "bye.." << endl;
    }

    cout << "Test8...";
    car = img.ReadTga("input/car.tga");
    img.LoadR(&car);
    img.writeTga("output/part8_r.tga", car);
    if(img.Compare(car.pixels, img.ReadTga("examples/EXAMPLE_part8_r.tga").pixels)){
        car = img.ReadTga("input/car.tga");
        img.LoadG(&car);
        img.writeTga("output/part8_g.tga", car);
        if(img.Compare(car.pixels, img.ReadTga("examples/EXAMPLE_part8_g.tga").pixels)){
            car = img.ReadTga("input/car.tga");
            img.LoadB(&car);
            img.writeTga("output/part8_b.tga", car);
            if(img.Compare(car.pixels, img.ReadTga("examples/EXAMPLE_part8_b.tga").pixels)){
                cout << "passed :)" << endl;
            }
        }
    }else{
        cout << "bye.." << endl;
    }

    cout << "Test9...";
    Header layerR = img.ReadTga("input/layer_red.tga");
    Header layerG = img.ReadTga("input/layer_green.tga");
    Header layerB = img.ReadTga("input/layer_blue.tga");
    img.Combine(&layerR, &layerG, &layerB);
    img.writeTga("output/part9.tga", layerR);
    if(img.Compare(layerR.pixels, img.ReadTga("examples/EXAMPLE_part9.tga").pixels)){
        cout << "passed :)" << endl;
    }else{
        cout << "bye.." << endl;
    }

    cout<<"Test10...";
    Header text2 = img.ReadTga("input/text2.tga");
    Header comp = text2;
    img.Rotate180(&text2, &comp);
    img.writeTga("output/part10.tga", comp);
    Header part10 = img.ReadTga("examples/EXAMPLE_part10.tga");
    if(img.Compare(comp.pixels, part10.pixels)){
        cout << "passed :)" << endl;
    }else{
        cout << "bye.." << endl;
    }

    return 0;
}

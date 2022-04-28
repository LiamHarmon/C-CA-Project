//
// Created by floodd on 23/03/2022.
//
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <valarray>
#include "Image.h"

bool Image::load(string filename)
{
    ifstream ifs(filename, std::ios::binary);
    string magicNumber;
    ifs >> magicNumber;
    ifs >> this->w;
    ifs >> this->h;
    int p;
    ifs >> p;
    ifs.ignore(256, '\n');
    if(p==255)
    {
        delete[] pixels;
        pixels = new Rgb[w*h];
        unsigned char pix[3];
        for(int i = 0; i < w*h; i++)
        {
            ifs.read(reinterpret_cast<char *>(pix), 3);
            this->pixels[i].r = pix[0];
            this->pixels[i].g = pix[1];
            this->pixels[i].b = pix[2];
            if(i < 100) {
//            cout << (int)pixels[i].r << (int)pixels[i].g << (int)pixels[i].b << endl;
            }
        }
        return true;
    }
    return false;

}
bool Image::loadRaw(string filename)
{
    ifstream ifs(filename);
    if(ifs.good()){
        ifs >> w;
        ifs >> h;
        for(int i = 0; i < w*h; i++){
            float r, g, b;
            ifs >> r >> g >> b;
            pixels[i].r =  pow(r, 1/2.2) * 255;
            pixels[i].g =  pow(g, 1/2.2) * 255;
            pixels[i].b =  pow(b, 1/2.2) * 255;
            cout << r << pixels[i].r << endl;
        }
        ifs.close();
        return true;
    }
    return false;
}
bool Image::savePPM(string filename)
{
    // Reference https://www.scratchapixel.com/lessons/digital-imaging/simple-image-manipulations
    if (w == 0 ||h == 0) {
        fprintf(stderr, "Can't save an empty image\n");
        return false;
    }
    std::ofstream ofs;
    try {
        ofs.open(filename, std::ios::binary); // binary mode for Windows users
        if (ofs.fail()) throw("Can't open output file");
        ofs << "P6\n" << w << " " << h << "\n255\n";
        unsigned char pix[3];
        // loop over each pixel in the image, clamp and convert to byte format
        for (int i = 0; i < w * h; i++) {
            pix[0] = static_cast<unsigned char>(this->pixels[i].r);
            pix[1] = static_cast<unsigned char>(this->pixels[i].g);
            pix[2] = static_cast<unsigned char>(this->pixels[i].b);
            ofs.write(reinterpret_cast<char *>(pix), 3);
        }
        ofs.close();

    }
    catch (const char *err) {
        fprintf(stderr, "%s\n", err);
        ofs.close();
    }
    return true;
}


void Image::filterRed()
{
    // Reference https://www.youtube.com/watch?v=zjxmZ4AODgI&t=193s (2:50)
    for(int i = 0; i < w*h; i++)
    {
        this->pixels[i].g = 0;
        this->pixels[i].b = 0;
    }
}
void Image::filterGreen()
{
    // Reference https://www.youtube.com/watch?v=zjxmZ4AODgI&t=193s (2:50)

    for(int i = 0; i < w*h; i++)
    {
        this->pixels[i].r = 0;
        this->pixels[i].b = 0;
    }
}
void Image::filterBlue()
{
    // Reference https://www.youtube.com/watch?v=zjxmZ4AODgI&t=193s (2:50)

    for(int i = 0; i < w*h; i++)
    {
        this->pixels[i].r = 0;
        this->pixels[i].g = 0;
    }
}
void Image::greyScale()
{
    // Reference = https://stackoverflow.com/questions/28923676/convert-ppm-image-to-greyscale-c

    int size = this->w * this->h;
    for (int i = 0; i < size; i++)
    {
        unsigned char greyscaleValue = ((this->pixels[i].r) + (this->pixels[i].g) + (this->pixels[i].b))/3;
        this->pixels[i].r = greyscaleValue;
        this->pixels[i].g = greyscaleValue;
        this->pixels[i].b = greyscaleValue;
    }
}
void Image::flipHorizontal()
{
    for(int i = 0; i < w/2; i++)
    {
        for(int x = 0; x < h; x++)
        {
            unsigned int p1 = i + x * w;
            unsigned int p2 = (w - 1 - i) + x * w;

            swap(pixels[p1], pixels[p2]);
        }
    }
}
void Image::flipVertically()
{
    for(int i = 0; i < w; i++)
    {
        for(int x = 0; x < h/2; x++)
        {
           unsigned int p1 = i + x * w;
           unsigned int p2 = i + (h - 1 - x) * w;

           swap(pixels[p1], pixels[p2]);
        }
    }
}
void Image::AdditionalFunction1()
{
    // Reference https://www.codeproject.com/Tips/878863/Simple-Method-to-Invert-a-Color

    int size = this->w * this->h;
    for (int i = 0; i < size; i++)
    {
        unsigned char invert = (( 255 - this->pixels[i].r), ( 255 - this->pixels[i].g), ( 255 - this->pixels[i].b));
        this->pixels[i].r = invert;
        this->pixels[i].g = invert;
        this->pixels[i].b = invert;
    }
}
void Image::AdditionalFunction2()
{
    int size = this->w * this->h;
    for(int i = 0; i < size; i++)
    {
        this->pixels[i].r *= 0.25;
        this->pixels[i].g *= 0.25;
        this->pixels[i].b *= 0.25;
    }

}
void Image::AdditionalFunction3()
{
    // Reference https://www.youtube.com/watch?v=zjxmZ4AODgI&t=369s

    int size = this->w * this->h;
    for (int i = 0; i < size; i++)
    {
        unsigned char pink = (this->pixels[i].r > this->pixels[i].g+90 && this->pixels[i].r > this->pixels[i].b-20)?255:0;
        this->pixels[i].r = pink;
        this->pixels[i].g = pink;
        this->pixels[i].b = pink;

    }
}

/* Functions used by the GUI - DO NOT MODIFY */
int Image::getWidth()
{
    return w;
}

int Image::getHeight()
{
    return h;
}

Rgb* Image::getImage()
{
    return pixels;
}
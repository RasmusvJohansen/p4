#include <iostream>
#include <fstream>
#include <vector>
#ifndef IMAGE_H
#define IMAGE_H
//#include "Image.cpp"
//using namespace std;


struct Color {
    float r, g, b;
    Color();
    Color(float r, float g, float b);
    ~Color(); 
};

class Image
{
public:
    Image(int width, int height);
    ~Image();

    Color GetColor(int x, int y) const;
    void SetColor(const Color& color, int x, int y);

    void Export(const char* path) const; // this will generate the file

private:
    int m_width;
    int m_height;
    std::vector<Color> m_colors; 
};
#endif


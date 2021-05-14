#include <fstream>
#include <vector>
#ifndef IMAGE_H
#define IMAGE_H


struct Color {
    volatile float r, g, b;
    Color();
    Color(volatile float r, volatile float g, volatile float b);
    ~Color(); 
};

class Image
{
public:
    Image(volatile int width, volatile int height);
    ~Image();

    Color GetColor(volatile int x, volatile int y) const;
    void SetColor(const Color& color, int x, int y);

    void Export(const char* path) const; // this will generate the file

private:
    volatile int m_width;
    volatile int m_height;
    std::vector<Color> m_colors; 
};
#endif



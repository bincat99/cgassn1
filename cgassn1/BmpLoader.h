#ifndef BMPLOADER_H
#define BMPLOADER_H

#ifdef __APPLE__

/*
typedef struct tagBITMAPFILEHEADER {
    unsigned short bfType;
    unsigned long bfSize;
    unsigned short bfReserved1;
    unsigned short bfReserved2;
    unsigned long bfOffBits;
} BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER {
    unsigned long biSize;
    long biWidth;
    long biHeight;
    unsigned short biPlanes;
    unsigned short biBitCount;
    unsigned long biCompression;
    unsigned long biSizeImage;
    long biXPelsPerMeter;
    long biYPelsPerMeter;
    unsigned long biClrUsed;
    unsigned long biClrImportant;
} BITMAPINFOHEADER;
 */

#pragma pack(2)
typedef struct                      // BMP file header structure
{
    unsigned short bfType ;         // Magic number for file
    unsigned int bfSize ;           // Size of file
    unsigned short bfReserved1 ;    // Reserved, usually set to 0
    unsigned short bfReserved2 ;    // Reserved, usually set to 0
    unsigned int bfOffBits ;        // Offset to bitmap data
}BITMAPFILEHEADER;

#pragma pack()
typedef struct
{
    unsigned int   biSize ;        // Size of info header
    int            biWidth ;       //  Width of image
    int            biHeight ;      // Height of image
    unsigned short biPlanes ;      // Number of color planes
    unsigned short biBitCount ;    // Number of bits per pixel
    unsigned int biCompression ;   // Type of compression to use, 0 if there is no compression
    unsigned int biSizeImage ;     // Size of image data
    int biXPelsPerMeter ;          // X pixels per meter
    int biYPelsPerMeter ;          // Y pixels per meter
    unsigned int biClrUsed ;       // Number of color used
    unsigned int biClrImportant ;  // Number of important color
}BITMAPINFOHEADER;
#else
#include <windows.h>
#endif

class BmpLoader
{
public :
	unsigned char* textureData;
	long iWidth, iHeight;
	BmpLoader(const char*);
	~BmpLoader();

private :
    
	BITMAPFILEHEADER bfh;
	BITMAPINFOHEADER bih;
};
#endif

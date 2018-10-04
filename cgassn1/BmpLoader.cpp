#include "BmpLoader.h"
#include <stdio.h>
#include <iostream>


BmpLoader::BmpLoader(const char* filename) {
	FILE *file = 0;
	

#ifdef __APPLE__
    file = fopen (filename, "rb");
    if (file == NULL)
        std::cout << "File not found" << std::endl;
    
#else
    errno_t err;
	err = fopen_s(&file, filename, "rb");
	if (err != 0) {
		std::cout << "File not found" << std::endl;
	}
#endif
	fread(&bfh, sizeof(BITMAPFILEHEADER), 1, file);
	if (bfh.bfType != 0x4D42)
		std::cout << "Not a valid bitmap" << std::endl;
	fread(&bih, sizeof(BITMAPINFOHEADER), 1, file);
    
    std::cout << bih.biWidth << std::endl;
    std::cout << bih.biHeight << std::endl;
    std::cout << sizeof (BITMAPFILEHEADER) << std::endl;
    std::cout << sizeof (BITMAPINFOHEADER) << std::endl;
	if (bih.biSizeImage == 0)
    {
		bih.biSizeImage = bih.biHeight*bih.biWidth * 3;
    }
	textureData = new unsigned char[bih.biSizeImage];
	fseek(file, bfh.bfOffBits, SEEK_SET);
	fread(textureData, 1, bih.biSizeImage, file);
	unsigned char temp;
	for (int i = 0; i < bih.biSizeImage; i += 3) {
		temp = textureData[i];
		textureData[i] = textureData[i + 2];
		textureData[i + 2] = temp;
	}

	iWidth = bih.biWidth;
	std::cout << bih.biWidth << std::endl;
	iHeight = bih.biHeight;
	
	fclose(file);
}

BmpLoader::~BmpLoader() {
	delete [] textureData;
}

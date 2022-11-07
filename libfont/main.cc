#include <iostream>
#include "ft2build.h"
#include FT_FREETYPE_H  

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

int printChar(FT_Library *ftLib , wchar_t wChar){
    FT_Face face;
    if (FT_New_Face(*ftLib, "songti.ttc", 0, &face)){
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        return -1;
    }
    
    FT_Set_Pixel_Sizes(face , 0 , 32);

    if (FT_Load_Char(face, wChar, FT_LOAD_RENDER)){
        std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
        return -1;
    }

    std::cout << "width = " << face->glyph->bitmap.width << std::endl;
    std::cout << "height = " << face->glyph->bitmap.rows << std::endl;
    std::cout << "pitch  = " << face->glyph->bitmap.pitch << std::endl;

    std::cout << "left = " << face->glyph->bitmap_left << std::endl;
    std::cout << "top  = " << face->glyph->bitmap_top << std::endl;

    std::cout << "advance  = " << face->glyph->advance.x / 64 << 
        " , " << face->glyph->advance.y << std::endl;

    FT_Bitmap fontBit = face->glyph->bitmap;

    for(int i = 0 ;  i < fontBit.rows ; i++ ){
        for(int j = 0 ; j < fontBit.width ; j++){
            std::cout << ((fontBit.buffer[i * fontBit.pitch + j] == 0)?" ":"+");
        }
        std::cout<< std::endl;
    }

    FT_Done_Face(face);

    return 0;
}

int main(){
    FT_Library ftLib;
    if (FT_Init_FreeType(&ftLib)){
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        return -1;
    }
    
    std::wstring str = L"陶馨兰";

    //auto p = wStr.c_str();
    for(int i = 0 ; i < str.size();i++){
        printChar(&ftLib , str[i]);
        // std::cout << p[i] << std::endl;
    }//end for i
    
    FT_Done_FreeType(ftLib);

    int width = 100;
    int height = 100;
    uint32_t *data = (uint32_t *)malloc(width * height * sizeof(uint32_t));

    for(int i = 0 ; i < height ; i++){
        for(int j = 0 ; j < width ;j++){
            // a r g b
            data[i * width + j] = 0xFF000000;
        }
    }

    stbi_write_png("test.png" , 100, 100, 4 , data , 0);

    return 0;
}
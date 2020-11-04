#include "PNGStream.h"
#include <fstream>
#include <iostream>
#include <istream>
#include <streambuf>
#include <stdio.h>

PNGStream::PNGStream(const std::string& input_path)
    :_input_path(input_path)
{
    
}
void PNGStream::Init()
{
  FILE* fp = fopen(_input_path.c_str(), "rb");
  if(!fp)
  {
    std::cout<<"error! PNGStream cannot open "<<_input_path<<std::endl;
  }
  char header[8];
  fread(header, 1, 8,fp);
  if(png_sig_cmp(( const unsigned  char*)header, 0, 8))
  {
    std::cout<< "Error!! File "<<_input_path<<" is not recognized as PNG file"<<std::endl;
  }
  png_structp png_ptr;
  png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if(!png_ptr)
  {
      std::cout<<"Error!! png_create_read_struct failed"<<std::endl;;
  }
  png_infop info_ptr = png_create_info_struct(png_ptr);
  if(!info_ptr)
  {
      std::cout<<"Error!! png_create_info_struct failed"<<std::endl;
  }
  //if(setjmp(


}

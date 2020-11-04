#ifndef __PNG_STREAM_H__
#define __PNG_STREAM_H__
#include <istream>
#include <png.h>
#include<string>
#include<iostream>
#include<fstream>
class PNGStream
{
    public:
        PNGStream(const std::string& file_path);
        ~PNGStream();

        void Init();
    private:
        std::fstream _input;
        std::string _input_path;
};
#endif

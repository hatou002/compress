#ifndef COMPRESSOR_H
#define COMPRESSOR_H

extern "C" {
    void compress_file(const char *input_file, const char *output_file);
    void decompress_file(const char *input_file, const char *output_file);
}

#endif // COMPRESSOR_H
#include <stdio.h>
#include <tiffio.h>
int main (int argc, char** argv)
{
 TIFF* tiff;
 tiff = TIFFOpen ("file_example_TIFF_1MB.tiff", "r");
 TIFFClose (tiff);
 return 0;
} 
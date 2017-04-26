#include "Image.h"

Image::Image()
{

}

Image::Image(Matrix<unsigned char> matrix) :
  Matrix<unsigned char>(matrix)
{

}

Image::Image( unsigned int width, unsigned int height, unsigned int qtyLayers) :
  Matrix<unsigned char>(width, height, qtyLayers)
{
  
}


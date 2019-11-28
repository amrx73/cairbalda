#include <cairo/cairo.h>
#include <iostream>
#include <array>

struct point
{
  double x, y;
};

struct layer
{
    point a, b;
    std::string color;
    int width;
    int datasize;
};

//prints a single layer
//returns canvas (surface)
int hexToInt(char hex) 
{
  int val = ((int)hex-48);
  if(val>30)
    val -= 39;
  //std::cout<<"debug hex "<<val<<std::endl;
  return val;
}

int getR(std::string color)
{
  int val=(16*hexToInt(color.at(0))+hexToInt(color.at(1)));
  //std::cout<<"debug checkpointr0 "<<val<<std::endl;
  if(!(val>=1&&val<=255))
    val=0;
  //std::cout<<"debug checkpointr1 "<<val<<std::endl;
  return val;
}

int getG(std::string color)
{
  int val=(16*hexToInt(color.at(2))+hexToInt(color.at(3)));
  //std::cout<<"debug checkpointg0 "<<val<<std::endl;
  if(!(val>=1&&val<=255))
    val=0;
  //std::cout<<"debug checkpointg1 "<<val<<std::endl;
  return val;
}

int getB(std::string color)
{
  int val=16*hexToInt(color.at(4))+hexToInt(color.at(5));
  //std::cout<<"debug checkpointb0 "<<val<<std::endl;
  if(!(val>=1&&val<=255))
    val=0;
  //std::cout<<"debug checkpointb1 "<<val<<std::endl;
  return val;
}


cairo_surface_t * addLayer(cairo_surface_t *canvas, layer layer)
{
    cairo_t *cr;
    cr=cairo_create(canvas);
    std::cout<<getR(layer.color)<<" "<<getG(layer.color)<<" "<<getB(layer.color)<<std::endl;
    cairo_set_source_rgb(cr,(double)getR(layer.color)/255,(double)getG(layer.color)/255,(double)getB(layer.color)/255);
    cairo_set_line_width(cr,layer.width);
    std::cout<<"line of width: "<<layer.width<<std::endl;
    cairo_move_to(cr,layer.a.x,layer.a.y);
    std::cout<<"start at point: "<<layer.a.x<<","<<layer.a.y<<std::endl;
    cairo_line_to(cr,layer.b.x,layer.b.y);
    std::cout<<"move to point: "<<layer.b.x<<","<<layer.b.y<<std::endl;
    cairo_stroke(cr);
    std::cout<<"debug checkpoint4"<<std::endl;
    return canvas;
}

layer readLayer()
{
  layer readIn;
  bool reading_points;
  int pos=0;
  std::string input;

  std::cout<<"X: ";
  std::cin>>readIn.a.x;
  std::cout<<"Y: ";
  std::cin>>readIn.a.y;
  std::cout<<"X: ";
  std::cin>>readIn.b.x;
  std::cout<<"Y: ";
  std::cin>>readIn.b.y;
  std::cout<<"Color? (000000 to ffffff)";
  std::cin>>readIn.color;
  std::cout<<"debug - color is "<<readIn.color<<std::endl;
  std::cout<<"Width?";
  std::cin>>readIn.width;
  return readIn;
}

int main()
{
  cairo_surface_t * canvas=cairo_image_surface_create(CAIRO_FORMAT_ARGB32,1280,690);
  layer *blankLayer = new layer;
  layer balda;
  int pos=0;
  char * filename;
  
  balda=readLayer();
  std::cout<<"debug color "<<balda.color<<std::endl;

  //-------------------add function to print data to file here

  canvas=addLayer(canvas, balda);

  /*
  std::cout<<std::endl<<"Filename? :";
  std::cin>>filename;
  filename+='.png';
  */

  cairo_surface_write_to_png(canvas,"printline.png");
  std::cout<<std::endl;
  cairo_surface_destroy(canvas);

  return 0;
}

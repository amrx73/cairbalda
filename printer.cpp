#include <cairo/cairo.h>
#include <iostream>
#include <array>

template <class T>
  class Vector
  {
  private:
    int size,capacity;
    T *obj;
  public:
    Vector()
    {
      size = capacity = 0;
      obj = NULL;
    }
    ~Vector()
    {
      delete [] obj;
    }
    Vector(int a)
    {
      size = a;
      obj = new T[size];
      //for(int i = 0 ; i<size; i++)
      //{
      //  obj[i] = NULL;
      //}
    }
    void reserve(int);
    T& operator[](int);
    void insert(int,T);
  
  };
template<class T>
void Vector<T>::reserve(int Num)
{
  if(capacity >Num)
    return;
  T *temp = new T[Num];
  for(int i = 0; i<size; i++)
  {
    temp[i] = obj[i];
  }
  if(obj != NULL) delete [] obj;
  obj = temp;
  capacity = Num;
}
template<class T>
T& Vector<T>::operator[](int index)
{
  return obj[index];
}
template<class T>
void Vector<T>::insert(int i, T e)
{
  obj[i] = e;
}

struct point
{
  double x, y;
  void operator=(point temp);
};

void point::operator=(point right)
{
  x=right.x;
  y=right.y;
  return;
}
struct layer
{
  Vector<point>coord;
  std::string color;
  int width;
  int datasize;
  void operator=(layer right);
};

void layer::operator=(layer right)
{
  std::cout<<"debug check assignment 0"<<std::endl;
  color=right.color;
  std::cout<<"debug check assignment color "<<color<<std::endl;
  datasize=right.datasize;
  std::cout<<"debug check assignment datasize "<<datasize<<std::endl;
  coord.reserve(datasize);
  std::cout<<"debug check assignment 2"<<std::endl;
  for(int i=0;i<datasize;i++)
  {
    coord.insert(i,right.coord[i]);
  }
  std::cout<<"debug check assignment 4"<<std::endl;
  width=right.width;
  std::cout<<"debug check assignment 5"<<std::endl;
  return;
}

//prints a single layer
//returns canvas (surface)
int hexToInt(char hex) 
{
  //std::cout<<"debug checkpoint hex1"<<std::endl;
  int val = ((int)hex-48);
  if(val>30)
    val -= 39;
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
    std::cout<<"debug checkpoint1"<<std::endl;
    std::cout<<"debug color "<<layer.color<<std::endl;
    cairo_set_source_rgb(cr,(double)getR(layer.color)/255,(double)getG(layer.color)/255,(double)getB(layer.color)/255);
    std::cout<<"debug checkpoint2"<<std::endl;
    cairo_set_line_width(cr,layer.width);
    std::cout<<"debug checkpoint3"<<std::endl;
    cairo_move_to(cr,layer.coord[0].x,layer.coord[0].y);
    std::cout<<"debug checkpoint4"<<std::endl;
    for(int i=1;i<layer.datasize;i++)
    {
      cairo_line_to(cr,layer.coord[i].x,layer.coord[i].y);
    }
    std::cout<<"debug checkpoint5"<<std::endl;
    cairo_stroke(cr);
    std::cout<<"debug checkpoint6"<<std::endl;
    cairo_destroy(cr);
    std::cout<<"debug checkpoint7"<<std::endl;
    return canvas;
}

layer readLayer()
{
  layer readIn;
  bool reading_points;
  int pos=0;
  std::string input;

  while(reading_points)
  {
    pos++;
    readIn.coord.reserve(pos);
    std::cout<<"X: ";
    std::cin>>readIn.coord[pos].x;
    std::cout<<"Y: ";
    std::cin>>readIn.coord[pos].y;
    std::cout<<"Add element? Y/N: ";
    std::cin>>input;
    if(input!="Y"&&input!="y")
      reading_points=false;
  }
  readIn.datasize=pos;
  std::cout<<"Color? (000000 to ffffff) ";
  std::cin>>readIn.color;
  //std::cout<<"debug - color is "<<readIn.color<<std::endl;
  std::cout<<"Width? ";
  std::cin>>readIn.width;
  std::cout<<"debug check - all read in"<<std::endl;
  return readIn;
}

int main()
{
  cairo_surface_t * canvas=cairo_image_surface_create(CAIRO_FORMAT_ARGB32,1280,690);
  layer *blankLayer = new layer;
  Vector<layer>balda(1);
  Vector<point>coord(1);
  int pos=0;
  bool reading_layer=true;
  std::string input;
  char * filename;
   
  while(reading_layer)
  {
    pos++;
    balda.reserve(pos);
    balda.insert(pos,readLayer());
    std::cout<<"debug color "<<balda[pos].color<<std::endl;
    std::cout<<"Add element? Y/N: ";
    std::cin>>input;
    if(input!="Y"&&input!="y")
      reading_layer=false;
  }

  //-------------------add function to print data to file here

  for(int i=1;i<=pos;i++)
  {
    std::cout<<"debug color "<<balda[i].color<<std::endl;
    canvas=addLayer(canvas, balda[i]);
  }
  /*
  std::cout<<std::endl<<"Filename? :";
  std::cin>>filename;
  filename+='.png';
  */

  std::cout<<"debug checkpointe"<<std::endl;
  cairo_surface_write_to_png(canvas,"printer.png");
  std::cout<<"debug checkpointe2"<<std::endl;
  cairo_surface_destroy(canvas);
  std::cout<<"debug checkpointe3"<<std::endl;


  return 0;
}

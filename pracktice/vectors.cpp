#include<iostream>
using namespace std;

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
      for(int i = 0 ; i<size; i++)
      {
        obj[i] = NULL;
      }
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
int main()
{
  int pos=0;
  bool reading=true;
  int input;
  char input2;
  Vector<int> a(1);
  while(reading)
  {
    pos++;
    a.reserve(pos);
    cout<<"What number would you like to add? ";
    cin>>input;
    a.insert(pos,input);
    cout<<"Add element? Y/N: ";
    cin>>input2;
    if(input2!='Y'&&input2!='y')
        reading=false;
  }
  for(int i=1;i<=pos;i++)
  {
    cout<<i<<"/"<<pos<<": "<<a[i]<<endl;
  }
  return 0;
}
#include <iostream>
#include <array>


int hexToInt(char hex) 
{
  int val = ((int)hex-48);
  if(val>30)
    val=val-39;
  return val;
}

int main()
{
  while(true)
  {
    std::string x;
    std::cin>>x;
    std::cout<<hexToInt(x.at(0))<<std::endl;
  }
  return 0;
}
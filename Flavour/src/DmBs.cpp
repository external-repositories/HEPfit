
#include "DmBs.h"
#include <iostream>

using namespace std;


 double  DmBs::getThValue() 
 
 { 
     
     std::cout << "Delta MB_s = " << 2.*AmpBs(NLO).abs() << std::endl;

     return(2.*AmpBs(NLO).abs()); 

 
 }
 
 
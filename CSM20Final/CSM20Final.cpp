//
//  CSM20Final.cpp
//  CSM20Final
//
//  Copyright (c) 2015 CSM20Final. All rights reserved.
//

#pragma warning(disable : 4290)

#include <iostream>
#include "AirlineInterface.h"

int main() {
    
    AirlineInterface interface;
    bool OK = true;
    
    while (OK)
        OK = interface.displayMenu();
    
    return 0;
}

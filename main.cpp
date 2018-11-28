//
//  main.cpp
//  CIS22C_Lab6
//
//  Created by Matan Broner on 11/26/18.
//  Copyright © 2018 Matan Broner. All rights reserved.
//

#include <iostream>
#include "HashTableManager.h"

using namespace std;
int main(int argc, const char * argv[]) {
    HashTableManager<Person> manager;
    manager.menu();
    
    return 0;
}

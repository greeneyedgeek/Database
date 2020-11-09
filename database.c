/*
Project:  SQLearn
File:	  database.c
Created:  2020-11-06
Modified: 2020-11-07
Author:   Gabriel Fontaine-Escobar
This code is in the public domain.
https://github.com/greeneyedgeek/SQLearn
  
References
SQLite Database System: Design and Implementation
https://www.sqlite.org/arch.html
https://cstack.github.io/db_tutorial
*/

//Libraries
#include "command_processor.h"

int main()
{
    welcome();
    
    while(1)
    {
		//Run the program
        run();
    }
}






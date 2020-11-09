/*
Project:  SQLearn
File:	  command_processor.c
Created:  2020-11-07
Modified: 2020-11-07
Author:   Gabriel Fontaine-Escobar
This code is in the public domain.
https://github.com/greeneyedgeek/SQLearn

Partly based on
https://cstack.github.io/db_tutorial

References
SQLite Database System: Design and Implementation
https://www.sqlite.org/arch.html
*/

#define  _POSIX_C_SOURCE 200809L

//Libraries
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "command_processor.h"
#include "virtual_machine.h" 

//Table description
char* id = "ID";
char* username = "USERNAME";
char* email = "EMAIL";

//used for storing user commands
typedef struct
{
    char* command;
    long unsigned int length;
} Input;
Input* input;

//A list of command types
typedef enum 
{
SELECT,
INSERT
} Command_type;

//This is what goes into a row
#define COLUMN_USERNAME_SIZE 32
#define COLUMN_EMAIL_SIZE 255
typedef struct {
  uint32_t id;
  char username[COLUMN_USERNAME_SIZE];
  char email[COLUMN_EMAIL_SIZE];
} Row;

// Used for temporary storage data
typedef struct {
  Command_type type;
  Row new_row;
} Statement;
Statement* statement;

//Reads commands from the user
void command_read(Input* input)
{
	printf("cmd >");
    size_t length = getline(&(input->command), &(input->length), stdin);
    input->length = length-1;
    input->command[input->length] = 0;
    printf("command read\n");
}

//Processes a metacommand
void metacommand_process(Input* input)
{

    if(strcmp(input->command, ".exit")==0)
	{
		printf("Goodbye!\n");
        free(input->command);
        free(input);
        free(statement);
		exit(EXIT_SUCCESS);
	}
	else
	{
		printf("Unkown command \"%s\" \n", input->command); 
	}
}

//Executes a SQL statement
void statement_prepare(Input* input, Statement* statement)
{
    
    //switch case
    printf("EXECUTING STATEMENT\n");
    printf("\"%s\" ID[%d]\n", input->command, statement->type);
    sscanf
    (
        input->command, 
        "%*s %d %s %s", 
        &(statement->new_row.id),
        statement->new_row.username, 
        statement->new_row.email
    );

printf("%-4s | %-10s | %-20s\n", id, username, email);     
printf("%-4d | %-10s | %-20s\n", 
        statement->new_row.id, statement->new_row.username, statement->new_row.email);
}

//Processes a SQL statement
void statement_process(Input* input, Statement* statement)
{
    char str_compared[6];
    strncpy(str_compared, input->command, sizeof(str_compared));    
    //Assign the correct statement based on received user command
    if((strcmp(str_compared, "select")==0) | (strcmp(str_compared, "SELECT")==0))
	{
		statement->type = SELECT; 
        printf("SELECT\n");
        //statement_prepare(input, statement);
	}
    else if((strcmp(str_compared, "insert")==0) | (strcmp(str_compared, "INSERT")==0))
	{
		statement->type = INSERT;  
        printf("INSERT\n");
        statement_prepare(input, statement);
	}
	else
	{
		printf("Unkown statement \"%s\" \n", input->command); 
	}
    
}

//Returns 1 (true) if the command starts with a dot
int is_metacommand(const char *command){
    return (command[0] == '.');
}

//Processes an input from the user
void command_process(Input* input)
{
    if(is_metacommand(input->command))
    {
        printf("processing metacommand...\n");
        metacommand_process(input);
        
    }
    else
    {
        statement = malloc(sizeof(Statement));
        printf("processing statement...\n");
        statement_process(input, statement);
    }
}

//Reads and processes a user input
void run() 
{
    input = malloc(sizeof(Input));
    command_read(input);  
	command_process(input);
}

//Welcome message with information for the user
void welcome()
{
    printf("\nSQLearn version 0.1 2020-11-07\nEnter \".exit\" to quit\n\n");
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Employee
{
    char name[100];
    double salary;
    int age;

} employee;

int main()
{
    employee *emp = (employee *) malloc(sizeof(employee));
    char name[] = {'S', 'A', 'R', 'A', 'T', 'H', '\0'};
    strcpy(emp->name, name);
    emp->salary = 11.23;
    emp->age = 23;
    
    printf("%s, %lf, %d\n", emp->name, emp->salary, emp->age);


    //Creating char buff
    char buff[112];
    memcpy(buff, emp->name, 100);
    memcpy((buff + 100), &(emp->salary), 8);
    memcpy((buff + 108), &(emp->age), 4);
    
    //fitting array back to struct
    employee *new_emp = (employee *) malloc(sizeof(employee));
    memcpy(new_emp->name, buff, 100);
    memcpy(&(new_emp->salary), (buff + 100), 8);
    memcpy(&(new_emp->age), (buff + 108), 4);
    printf("%s, %lf, %d\n", new_emp->name, new_emp->salary, new_emp->age);

    free(emp);
    free(new_emp);
}
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
    memcpy((buff + sizeof(double)), &(emp->age), 4);

    int del_sts = remove("struct_data.dat");
    if(del_sts != 0)
    {
        printf("Cannot delete file\n");
    }

    //writing to file
    FILE *fp = fopen("struct_data.dat", "wb");
    if(fp == NULL)
    {
        printf("Cannot open file\n");
        exit(EXIT_FAILURE);
    }

    fwrite(buff, 1, sizeof(buff), fp);
    fclose(fp);

    //reading file and mapping back to struct
    fp = fopen("struct_data.dat", "rb");
    if(fp == NULL)
    {
        printf("Cannot open file\n");
        exit(EXIT_FAILURE);
    }

    char new_buff[112];
    fread(new_buff, sizeof(new_buff), 1, fp);
    fclose(fp);
    
    //fitting array back to struct
    employee *new_emp = (employee *) malloc(sizeof(employee));
    memcpy(new_emp->name, new_buff, 100);
    memcpy(&(new_emp->salary), (new_buff + 100), 8);
    memcpy(&(new_emp->age), (new_buff + sizeof(double)), 4);
    printf("%s, %lf, %d\n", new_emp->name, new_emp->salary, new_emp->age);

    free(emp);
    free(new_emp);
}
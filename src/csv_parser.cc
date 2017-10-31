#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define BFR_SIZE 4096

typedef struct Employee {
    char *name;
    double salary;
    int age;

} employee;

void marshall_employee(employee *employees, int no_employees, char *record, int record_length);

char* get_value(char *bfr, int initial_index, int size);

int main(int argc, char **argv)
{        

    if(2 != argc) 
    {
        printf("Usage : csv_parser.exe filename\n");
        return -1;
    }

    FILE *fp = fopen(argv[1], "rt");

    if(0 == fp)
    {
        printf("Unable to open the file exiting\n");
        return -2;
    }    

    employee *employees;
    char buffer[BFR_SIZE];
    
    int i=0;
    
    int no_employees = 1;

    while(!feof(fp))
    {                        
        fgets(buffer, BFR_SIZE, fp);
        printf("Buffer read : %s\n", buffer);   
        
        while(buffer[i] !='\0' && buffer[i] !='\n') i++;                        

        printf("Buffer index : %d\n", i);

        employees = (employee *) realloc(employees, sizeof(Employee) * no_employees);        
        
        marshall_employee(employees, no_employees, buffer, i);            
        no_employees++;
        i = 0;                                
    }

    fclose(fp);
}

void marshall_employee(employee *employees, int no_employees, char *record, int record_length)
{
    printf("rec_length : %d\n", record_length);
    employee *emp = (employees + (no_employees - 1));        
    int elem_count = 0;
    int offset = 0;
    for(int i = 0; i < record_length; i++)
    {
        printf("Offset : %d, i: %d\n", offset, i);
        if(*(record + i) == ',')
        {
            char *val = get_value(record, offset, i);
            printf("Val, : %s\n", val);            
            if(elem_count == 0) 
            {
                emp->name = (char *) malloc(sizeof(char) * i);
                // printf("%ld", sizeof(emp->name));
                memcpy(emp->name, val, i);
            }
            else if(elem_count == 1) emp->salary = atof(val);
            offset = i + 1;
            elem_count++;
            printf("Emp->name, : %s\n", emp->name);
            printf("Emp->salary, : %f\n", emp->salary);
            
        } 
        else if(elem_count == 2)
        {
            char *val = get_value(record, offset, record_length);
            printf("Val : %s\n", val);
            emp->age = atoi(val);            
            printf("Emp->age, : %d\n", emp->age);
            
            break;
        }

    }
    printf("Name: %s, salary: %f, age: %d\n", emp->name, emp->salary, emp->age);
}

char* get_value(char *bfr, int initial_index, int size)
{   if(initial_index >= size)
    {
        printf("Initial index is greater than size of bfr\n");
        return NULL;
    } 
    int size_val = size - initial_index;
    printf("Value initial_index : %d, size : %d, size_val : %d \n", initial_index, size, size_val);    
    void *mem = NULL;
    mem = malloc(sizeof(char) * (size_val + 1));     
    char *val = NULL;
    if(mem == NULL)
    {
        fprintf(stderr, "Out of memory\n");
        exit(EXIT_FAILURE);
    }
    val = (char*)mem;
    printf("temp val: %s\n", val);
    for(int i = initial_index; i < size + 1; i++) 
    {
        int val_index = i - initial_index;
        *(val + val_index) = *(bfr + i);
    }
    *(val + size_val) = '\0';
    return val;
}
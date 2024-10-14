#include <stdio.h>
#include <unistd.h>
int main()
{
    write(1, "STDOUT\n", 7);
    write(2, "STDERR\n", 7);    
}
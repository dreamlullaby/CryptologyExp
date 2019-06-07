#include<sys/syscall.h>
#include<unistd.h>
#include<linux/psta.h>

int main()
{
 struct pinfo info;
 syscall(320,&info);
 return 0;
}

#include<stdio.h>
#include<string.h>
#define PI 3.14
int main(){
int x,y=PI;//replace macro
char s[20]="hello";
x=sizeof(s);
/*sizeof 
gives 20 */
int z=x/y;//div
printf("x=%d\n",x);
printf("y=%d\n",y);
printf("z=%d\n",z);
return 0;
}

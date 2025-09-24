#include <stdio.h>
#include <string.h>
int main()
{
    char contents[20];
    printf("请输入:\n");
    scanf("%s",contents);
    if(strcmp(contents,"Dian") == 0){
        printf("2002\n");
        return 0;
    }else if(strcmp(contents,"Quit") == 0){
        return 0;
    }else{printf("Error\n"); return 0;}
    return 0;
    
}
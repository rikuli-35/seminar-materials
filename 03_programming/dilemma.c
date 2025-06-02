#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    printf("私は囚人A、あなたは囚人Bです。\n");

    int n;
    int m=rand()%2;

    printf("自白なら0、黙秘なら1を入力してください。:");
    scanf("%d",&n);

    if(n==0 && m==0)
    printf("私の懲役は5年、あなたの懲役も5年です。");
    else if (n==0 && m==1)
    printf("私の懲役は10年、あなたの懲役は0年です。");
    else if (n==1 && m==0)
    printf("私の懲役は0年、あなたの懲役は10年です。");
    else if (n==1 && m==1)
    printf("私の懲役は2年、あなたの懲役は2年です。");
    
    return 0;
}
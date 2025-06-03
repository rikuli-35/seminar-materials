#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    printf("私は囚人A、あなたは囚人Bです。\n");
    printf("利得表に基づいて計10ラウンド行い、合計懲役年数が多い方が負けです\n");

    int n;
    int a=0;
    int b=0;
    int m=rand()%2;

for(int i=1; i<11; i++) {
    while(1){
        printf("%dラウンド目\n",i);
        printf("自白なら0、黙秘なら1を入力してください。:");
        if(scanf("%d",&n) != 1) {
        printf("数字を入力して下さい。\n");
        while(getchar() != '\n');
        continue; 
        } 
        if(n == 0 || n == 1) break;
        printf("数字の入力は0か1です。\n");
        }

    if(n==0 && m==0){
    printf("私の懲役は5年、あなたの懲役も5年です。\n");
    a = a+5; b= b+5; m=0;
    } else if (n==0 && m==1) {
    printf("私の懲役は10年、あなたの懲役は0年です。\n");
    a = a+10; m=0;
    } else if (n==1 && m==0) {
    printf("私の懲役は0年、あなたの懲役は10年です。\n");
    b = b+10; m=1;
    } else if (n==1 && m==1) {
    printf("私の懲役は2年、あなたの懲役は2年です。\n");
    a= a+2; b= b+2; m=1;
    }
}     
    printf("私の合計懲役年数は%d年、あなたの合計懲役年数は%d年です。\n",a,b);
    if(a<b) printf("私の勝ちです。\n");
    if(a>b) printf("あなたの勝ちです。\n");
    if(a==b) printf("引き分けです。\n");

    return 0;
}

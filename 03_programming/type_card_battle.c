#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const char* type_names_1[15] =
{
"normal","fire","water","electric","grass","ice","fighting","poison","ground","flying","psychic","bug","rock","ghost","dragon"
};

const char* type_names_2[17] =
{
"normal","fire","water","electric","grass","ice","fighting","poison","ground","flying","psychic","bug","rock","ghost","dragon","dark","steel"
};

const char* type_names_3[18] =
{
"normal","fire","water","electric","grass","ice","fighting","poison","ground","flying","psychic","bug","rock","ghost","dragon","dark","steel","fairy"
};

const double type_char_1[15][15] =
{
    {1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.5,0.0,1.0},
    {1.0,0.5,0.5,1.0,2.0,2.0,1.0,1.0,1.0,1.0,1.0,2.0,0.5,1.0,0.5},
    {1.0,2.0,0.5,1.0,0.5,1.0,1.0,1.0,2.0,1.0,1.0,1.0,2.0,1.0,0.5},
    {1.0,1.0,2.0,0.5,0.5,1.0,1.0,1.0,0.0,2.0,1.0,1.0,1.0,1.0,0.5},
    {1.0,0.5,2.0,1.0,0.5,1.0,1.0,0.5,2.0,0.5,1.0,0.5,2.0,1.0,0.5},
    {1.0,1.0,0.5,1.0,2.0,0.5,1.0,1.0,2.0,2.0,1.0,1.0,1.0,1.0,2.0},
    {2.0,1.0,1.0,1.0,1.0,2.0,1.0,0.5,1.0,0.5,0.5,0.5,2.0,0.0,1.0},
    {1.0,1.0,1.0,1.0,2.0,1.0,1.0,0.5,0.5,1.0,1.0,2.0,0.5,0.5,1.0},
    {1.0,2.0,1.0,2.0,0.5,1.0,1.0,2.0,1.0,0.0,1.0,0.5,2.0,1.0,1.0},
    {1.0,1.0,1.0,0.5,2.0,1.0,2.0,1.0,1.0,1.0,1.0,2.0,0.5,1.0,1.0},
    {1.0,1.0,1.0,1.0,1.0,1.0,2.0,2.0,1.0,1.0,0.5,1.0,1.0,1.0,1.0},
    {1.0,0.5,1.0,1.0,2.0,1.0,0.5,2.0,1.0,0.5,2.0,1.0,1.0,0.5,1.0},
    {1.0,2.0,1.0,1.0,1.0,2.0,0.5,1.0,0.5,2.0,1.0,2.0,1.0,1.0,1.0},
    {0.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.0,1.0,1.0,2.0,1.0},
    {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0}
};

const double type_char_2[17][17] =
{
    {1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.5,0.0,1.0,1.0,0.5},
    {1.0,0.5,0.5,1.0,2.0,2.0,1.0,1.0,1.0,1.0,1.0,2.0,0.5,1.0,0.5,1.0,2.0},
    {1.0,2.0,0.5,1.0,0.5,1.0,1.0,1.0,2.0,1.0,1.0,1.0,2.0,1.0,0.5,1.0,1.0},
    {1.0,1.0,2.0,0.5,0.5,1.0,1.0,1.0,0.0,2.0,1.0,1.0,1.0,1.0,0.5,1.0,1.0},
    {1.0,0.5,2.0,1.0,0.5,1.0,1.0,0.5,2.0,0.5,1.0,0.5,2.0,1.0,0.5,1.0,0.5},
    {1.0,0.5,0.5,1.0,2.0,0.5,1.0,1.0,2.0,2.0,1.0,1.0,1.0,1.0,2.0,1.0,0.5},
    {2.0,1.0,1.0,1.0,1.0,2.0,1.0,0.5,1.0,0.5,0.5,0.5,2.0,0.0,1.0,2.0,2.0},
    {1.0,1.0,1.0,1.0,2.0,1.0,1.0,0.5,0.5,1.0,1.0,1.0,0.5,0.5,1.0,1.0,0.0},
    {1.0,2.0,1.0,2.0,0.5,1.0,1.0,2.0,1.0,0.0,1.0,0.5,2.0,1.0,1.0,1.0,2.0},
    {1.0,1.0,1.0,0.5,2.0,1.0,2.0,1.0,1.0,1.0,1.0,2.0,0.5,1.0,1.0,1.0,0.5},
    {1.0,1.0,1.0,1.0,1.0,1.0,2.0,2.0,1.0,1.0,0.5,1.0,1.0,1.0,1.0,0.0,0.5},
    {1.0,0.5,1.0,1.0,2.0,1.0,0.5,1.0,1.0,0.5,2.0,1.0,1.0,0.5,1.0,2.0,0.5},
    {1.0,2.0,1.0,1.0,1.0,2.0,0.5,1.0,0.5,2.0,1.0,2.0,1.0,1.0,1.0,1.0,0.5},
    {0.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,2.0,1.0,1.0,2.0,1.0,0.5,0.5},
    {1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,2.0,1.0,0.5},
    {1.0,1.0,1.0,1.0,1.0,1.0,0.5,1.0,1.0,1.0,2.0,1.0,1.0,2.0,1.0,0.5,0.5},
    {1.0,0.5,0.5,0.5,1.0,2.0,1.0,1.0,1.0,1.0,1.0,1.0,2.0,1.0,1.0,1.0,0.5}
};

const double type_char_3[18][18] =
{
    {1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.5,0.0,1.0,1.0,0.5,1.0},
    {1.0,0.5,0.5,1.0,2.0,2.0,1.0,1.0,1.0,1.0,1.0,2.0,0.5,1.0,0.5,1.0,2.0,1.0},
    {1.0,2.0,0.5,1.0,0.5,1.0,1.0,1.0,2.0,1.0,1.0,1.0,2.0,1.0,0.5,1.0,1.0,1.0},
    {1.0,1.0,2.0,0.5,0.5,1.0,1.0,1.0,0.0,2.0,1.0,1.0,1.0,1.0,0.5,1.0,1.0,1.0},
    {1.0,0.5,2.0,1.0,0.5,1.0,1.0,0.5,2.0,0.5,1.0,0.5,2.0,1.0,0.5,1.0,0.5,1.0},
    {1.0,0.5,0.5,1.0,2.0,0.5,1.0,1.0,2.0,2.0,1.0,1.0,1.0,1.0,2.0,1.0,0.5,1.0},
    {2.0,1.0,1.0,1.0,1.0,2.0,1.0,0.5,1.0,0.5,0.5,0.5,2.0,0.0,1.0,2.0,2.0,0.5},
    {1.0,1.0,1.0,1.0,2.0,1.0,1.0,0.5,0.5,1.0,1.0,1.0,0.5,0.5,1.0,1.0,0.0,2.0},
    {1.0,2.0,1.0,2.0,0.5,1.0,1.0,2.0,1.0,0.0,1.0,0.5,2.0,1.0,1.0,1.0,2.0,1.0},
    {1.0,1.0,1.0,0.5,2.0,1.0,2.0,1.0,1.0,1.0,1.0,2.0,0.5,1.0,1.0,1.0,0.5,1.0},
    {1.0,1.0,1.0,1.0,1.0,1.0,2.0,2.0,1.0,1.0,0.5,1.0,1.0,1.0,1.0,0.0,0.5,1.0},
    {1.0,0.5,1.0,1.0,2.0,1.0,0.5,1.0,1.0,0.5,2.0,1.0,1.0,0.5,1.0,2.0,0.5,0.5},
    {1.0,2.0,1.0,1.0,1.0,2.0,0.5,1.0,0.5,2.0,1.0,2.0,1.0,1.0,1.0,1.0,0.5,1.0},
    {0.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,2.0,1.0,1.0,2.0,1.0,0.5,1.0,1.0},
    {1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,2.0,1.0,0.5,0.0},
    {1.0,1.0,1.0,1.0,1.0,1.0,0.5,1.0,1.0,1.0,2.0,1.0,1.0,2.0,1.0,0.5,1.0,1.0},
    {1.0,0.5,0.5,0.5,1.0,2.0,1.0,1.0,1.0,1.0,1.0,1.0,2.0,1.0,1.0,1.0,0.5,2.0},
    {1.0,0.5,1.0,1.0,1.0,1.0,2.0,0.5,1.0,1.0,1.0,1.0,1.0,1.0,2.0,2.0,0.5,1.0}
};

const int type_count_1 = 15;
const int type_count_2 = 17;
const int type_count_3 = 18;

int player_flag[18] = {0};
int cpu_flag[18] = {0};

int select_version(){
    int n;
    while(1){
        printf("\nどのバージョンで遊ぶ？\n");
        printf("1：初代ポケモン\n");
        printf("2：第2世代〜第5世代ポケモン\n");
        printf("3：第6世代〜第9世代ポケモン\n");
        printf("\n1~3を入力して選んでね！：");
        if(scanf("%d",&n) != 1) {
            printf("[エラー]：1〜3の数字のみ入力してください！\n");
            while(getchar() != '\n');
            continue;
        }
        if(n == 1 || n == 2 || n == 3) return n;
        printf("[エラー]：1〜3の数字を入力してください！\n");
    } 
}


int player_choice(const char** type_names, int type_count, int* flag){

    while(1) {
        printf("\n[いまあなたが持っている手札]:\n");
            for(int i = 0; i < type_count; i++){
                if(flag[i] != 1) {
                    printf("<");
                    printf("%s",type_names[i]);
                    printf(">");
                    printf(",");
                } 
            }
    
            printf("\n\nあなたのタイプ：");
            char type_input[100];
            scanf("%s",type_input);
    
            int player_index = -1;
            for(int j = 0; j < type_count; j++){
                if(strcmp(type_input, type_names[j]) == 0){
                    player_index = j;
                    break;
                }
            }
            if(player_index == -1){
                printf("[エラー]：タイプ名が正しくありません！\n");
                continue;
            }
            if(flag[player_index] == 1){
                printf("[エラー]：そのタイプをあなたは既に使用しています！\n");
                continue;
            }
            flag[player_index] = 1;
            return player_index;
        }
    }


int cpu_choice(const char** type_names, int type_count, int* flag){

    while(1) {
        int cpu_index = rand() % type_count;
        if(flag[cpu_index] == 0) {
            flag[cpu_index] = 1;
            printf("相手が使ったタイプ：%s\n", type_names[cpu_index]);
            return cpu_index;
        }
    }
}


double point_calculation(int attack, int defense, const double* chart, int type_count){
    return chart[attack * type_count + defense];
}


void round_result(int round, double player_score, double cpu_score) {

    printf("\n---------------現在のスコア---------------\n");
    printf("あなた：%.lf   |   相手：%.lf\n", player_score, cpu_score);
    printf("------------------------------------------\n");

    if(player_score > cpu_score) 
    printf("--- あなたが%.lf点リードしています！ ---\n", player_score - cpu_score);
    else if(player_score < cpu_score) 
    printf("--- 相手が%.lf点リードしています、、、 ---\n", cpu_score - player_score);
    else 
    printf("--- いまは引き分けです ---\n");

}


void play_game(int version) {
    
    const double* chart;
    const char** type_names;
    int type_count;
    double point;
    double player_score = 0.0;
    double cpu_score = 0.0;

    switch(version) {
        case 1:
        type_names = type_names_1;
        chart = &type_char_1[0][0];
        type_count = type_count_1;
        printf("\n<<<初代ポケモンのカードバトル!>>>\n");
        break;

        case 2:
        type_names = type_names_2;
        chart = &type_char_2[0][0];
        type_count = type_count_2;
        printf("\n<<<第2世代〜第5世代のポケモンカードバトル!>>>\n");
        break;

        case 3:
        type_names = type_names_3;
        chart = &type_char_3[0][0];
        type_count = type_count_3;
        printf("\n<<<第6世代〜第9世代のポケモンカードバトル!>>>\n");
        break;

        default:
        printf("\nエラー：バージョン不明\n");
    }

    srand(time(NULL));
    int coin_toss = rand() % 2;
    if(coin_toss == 1) printf("\n---あなたは先攻（攻撃側）です！---\n");
    else printf("\n---あなたは後攻（防御側）です！---\n");

    for(int round = 0; round < type_count; round++) {

        printf("\n===第 %d ラウンド===\n",round + 1);

        int player_index = player_choice(type_names, type_count, player_flag);
        int cpu_index = cpu_choice(type_names, type_count, cpu_flag);
        int turn_decide = (round + coin_toss) % 2;

        if(turn_decide == 1) {
            printf("\n---あなたの攻撃！---\n");
            point = point_calculation(player_index, cpu_index, chart, type_count);
            player_score += point;
            printf("あなたは%.lf点獲得！\n",point);
            round_result(round, player_score, cpu_score);
            printf("\n\n<<<次のターンは防御側です！>>>\n\n");
        } else {
            printf("\n---相手の攻撃！---\n");
            point =  point_calculation(cpu_index, player_index, chart, type_count);
            cpu_score += point;
            printf("相手は%.lf点獲得！\n",point);
            round_result(round, player_score, cpu_score);
            printf("\n\n<<<次のターンは攻撃側です！>>>\n\n");
        }
    }

    if(player_score > cpu_score)
    printf("\n---あなたの勝ち！！！---\n");
    else if(player_score < cpu_score)
    printf("\n---あなたの負け、、、---\n");
    else 
    printf("\n---引き分け---\n");

}


int main() {

    while(1) {
    int version = select_version();

    memset(player_flag, 0, sizeof(player_flag));
    memset(cpu_flag, 0, sizeof(cpu_flag));

    printf("\n-------------------------------------------------------------------\n");
    printf("[ゲームの説明1]：各ラウンドで手札の中からタイプを1つ選択してください。\n");
    printf("[ゲームの説明2]：一度使用したタイプは使えません！よく考えて使いましょう！\n");
    printf("[ゲームの説明3]：各世代のタイプ相性表をもとに、CPUと対戦します\n");
    printf("[ゲームの説明4]：最終ラウンドで合計得点が多い方が勝ちです！\n");
    printf("---------------------------------------------------------------------\n");
    
    play_game(version);

    printf("もう一度遊びますか？()：");
    char again[10];
    scanf("%s",again);
    if(again[0] != 'y' && again[0] != 'Y') {
        printf("ゲームを終了します\n");
        break;
    }   
    }
    return 0;

}

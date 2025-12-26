#include "game.h"
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <iostream>
#include <fstream>

using namespace std;

// タイプ名一覧
vector<string> type_list = 
{
    "normal","fire","water","electric","grass","ice","fighting","poison","ground","flying","psychic","bug","rock","ghost","dragon","dark","steel","fairy","new"
};

// タイプ数変数
int type_count = 19;

// 得点表の変数
vector<vector<double>> PointGraph;

// ファイル読み込みを行う関数
vector<vector<double>> ReadCSV(const string& filename) {

    vector<vector<double>> table(TYPE_COUNT, vector<double>(TYPE_COUNT, 0.0));
    ifstream ifs(filename, ios::in);
    if(!ifs) {
        cerr << "エラー：ファイルが開けませんでした" << endl;
        return {};
    }
    
    string a, d;
    double m;

    while(ifs >> a >> d >> m)  {

        int a_i = find(type_list.begin(), type_list.end(), a) - type_list.begin();
        int d_i = find(type_list.begin(), type_list.end(), d) - type_list.begin();
        table[a_i][d_i] = m;

    }
    
    return table;
    
}

// バージョン読み込みを行う関数
void LoadVersion(GameVersion version, GameData& game) {

    switch(version) {

        case GameVersion::V1: {

            type_count = 15;
            PointGraph = ReadCSV("type_analysis_1.csv");
            break;

        }

        case GameVersion::V2_TO_5: {

            type_count = 17;
            PointGraph = ReadCSV("type_analysis_2_to_5.csv");
            break;

        }

        case GameVersion::V6_TO_9: {

            type_count = 18;
            PointGraph = ReadCSV("type_analysis_6_to_9.csv");
            break;

        }

        case GameVersion::NEW: {

            type_count = 19;
            PointGraph = ReadCSV("type_analysis_new.csv");
            break;

        }

    }

}

// ゲームの初期状態
void InitGame(GameData& game) {

    game.round = 1;
    game.round_ready = false;

    static std::mt19937 gen{ std::random_device{}() };
    std::uniform_int_distribution<int> dist(0, 1);

    game.attacker = static_cast<PlayerID>(dist(gen));
    game.turn_end = game.attacker;

    for(auto& p : game.players) {

        p.hand.clear();
        p.deck.clear();
        p.used.clear();
        p.select.clear();
        p.score = 0.0;

    }

    for(int i=0; i<TYPE_COUNT; i++) {

        game.players[0].deck.push_back(i);
        game.players[1].deck.push_back(i);

    }
    
    std::shuffle(game.players[0].deck.begin(), game.players[0].deck.end(), gen);
    std::shuffle(game.players[1].deck.begin(), game.players[1].deck.end(), gen);

    // 初期手札とデッキの作成
    for(int i=0; i<4; i++) {

        for(int j=0; j<2; j++) {

            auto& deck = game.players[j].deck;
            game.players[j].hand.push_back(deck.back());
            deck.pop_back();

        }

    }

}

// ドローを行う関数
void HandDraw(GameData& game, PlayerID id) {

    Player& p = game.players[static_cast<int>(id)];
    if(p.hand.size() >= 5 || p.deck.empty()) return ;
  
    p.hand.push_back(p.deck.back());
    p.deck.pop_back();

}

// ハンデスを行う関数（
void HandDeath(GameData& game, PlayerID id) {

    Player& p = game.players[static_cast<int>(id)];
    if(p.hand.empty()) return ;
    
    
    static std::mt19937 gen{ std::random_device{}() };
    std::uniform_int_distribution<int> dist(0, p.hand.size() - 1);
    p.hand.erase(p.hand.begin() + dist(gen));

}

// プレイヤーが手札を選択する関数
void PlayerSelect(GameData& game, int index, int count) {

    Player& p = game.players[static_cast<int>(PlayerID::PLAYER)];

    if((int)p.select.size() >= count) return ;
    if(index < 0 || index >= (int)p.hand.size()) return ;

    int card = p.hand[index];

    if(find(p.select.begin(), p.select.end(), card) != p.select.end()) return ;

    p.select.push_back(card);

}

// CPUが手札を選択する関数
void CpuSelect(GameData& game, int count) {

    Player& cpu = game.players[static_cast<int>(PlayerID::CPU)];
    cpu.select.clear();

    if(cpu.hand.empty()) return;

    // CPUはランダムな枚数を選んでしまうため、上限を設定する
    int max_count = std::min<int>(count, (int)cpu.hand.size());

    //CPUの使用枚数を決定
    static std::mt19937 gen{ std::random_device{}() };
    std::uniform_int_distribution<int> use_dist(1, max_count);
    int use = use_dist(gen);

    vector<int> temp = cpu.hand;
    std::shuffle(temp.begin(), temp.end(), gen);

    for(int i=0; i<use; i++) cpu.select.push_back(temp[i]);
    
}

// 得点計算を行う関数
double RoundPoint(const vector<int> &attack, int defense) {

    double score = 0.0;
    for(int i=0; i<attack.size(); i++) {

        // 得点表を参照して加算
        score += PointGraph[attack[i]][defense];

    }

    return score;

}

// ラウンド終了後の手札処理を行う関数
void RoundManagement(GameData& game) {

    if(game.players[static_cast<int>(PlayerID::PLAYER)].select.empty() || game.players[static_cast<int>(PlayerID::CPU)].select.empty()) return ;

    // 得点加算
    if(game.turn_end == PlayerID::PLAYER)  game.players[static_cast<int>(PlayerID::PLAYER)].score += RoundPoint(game.players[static_cast<int>(PlayerID::PLAYER)].select, game.players[static_cast<int>(PlayerID::CPU)].select[0]);
    else game.players[static_cast<int>(PlayerID::CPU)].score += RoundPoint(game.players[static_cast<int>(PlayerID::CPU)].select, game.players[static_cast<int>(PlayerID::PLAYER)].select[0]);
    
    // プレイヤーの手札と墓地の更新
    for(int c : game.players[static_cast<int>(PlayerID::PLAYER)].select) {

        auto a = find(game.players[static_cast<int>(PlayerID::PLAYER)].hand.begin(), game.players[static_cast<int>(PlayerID::PLAYER)].hand.end(), c);
                
        if(a != game.players[static_cast<int>(PlayerID::PLAYER)].hand.end()) {

            game.players[static_cast<int>(PlayerID::PLAYER)].used.push_back(*a);
            game.players[static_cast<int>(PlayerID::PLAYER)].hand.erase(a);

        }

    }

    // CPUの手札と墓地の更新
    for(int c : game.players[static_cast<int>(PlayerID::CPU)].select) {

        auto a = find(game.players[static_cast<int>(PlayerID::CPU)].hand.begin(), game.players[static_cast<int>(PlayerID::CPU)].hand.end(), c);

        if(a != game.players[static_cast<int>(PlayerID::CPU)].hand.end()) {

            game.players[static_cast<int>(PlayerID::CPU)].used.push_back(*a);
            game.players[static_cast<int>(PlayerID::CPU)].hand.erase(a);

        }

    }

}

// ラウンド開始
void RoundStart(GameData& game) {

    game.players[static_cast<int>(PlayerID::PLAYER)].select.clear();
    game.players[static_cast<int>(PlayerID::CPU)].select.clear();
    game.round_ready = false;

}

// ラウンド終了
void RoundEnd(GameData& game) {

    game.round++;
    game.attacker = game.turn_end;

}

// 終了時処理
bool IsRoundFinished(const GameData& game) {

    return game.players[static_cast<int>(PlayerID::PLAYER)].select.size() > 0 && game.players[static_cast<int>(PlayerID::CPU)].select.size() > 0;

}


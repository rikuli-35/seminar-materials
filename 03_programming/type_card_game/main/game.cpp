#include "game.h"
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <iostream>
#include <fstream>

using namespace std;

// タイプ名一覧
std::vector<std::string> type_list = 
{
    "normal","fire","water","electric","grass","ice","fighting","poison","ground","flying","psychic","bug","rock","ghost","dragon","dark","steel","fairy","unknown"
};

// 得点表の変数
std::vector<std::vector<double>> PointGraph;

// ファイル読み込みを行う関数
std::vector<std::vector<double>> ReadCSV(const std::string& filename) {

    std::vector<std::vector<double>> table(TYPE_COUNT, std::vector<double>(TYPE_COUNT, 0.0));
    
    ifstream ifs(filename, ios::in);
    if(!ifs) {

        cerr << "エラー：ファイルが開けませんでした" << endl;
        return {};

    }
    
    std::string a, d;
    double m;

    while(ifs >> a >> d >> m)  {

        int a_i = std::find(type_list.begin(), type_list.end(), a) - type_list.begin();
        int d_i = std::find(type_list.begin(), type_list.end(), d) - type_list.begin();
        if(a_i < TYPE_COUNT && d_i < TYPE_COUNT) table[a_i][d_i] = m;

    }
    
    return table;
    
}

// バージョン読み込みを行う関数
void LoadVersion(GameVersion version, GameData& game) {

    switch(version) {

        case GameVersion::V1: {

            game.type_count = 15;
            PointGraph = ReadCSV("type_analysis_1.csv");
            break;

        }

        case GameVersion::V2_TO_5: {

            game.type_count = 17;
            PointGraph = ReadCSV("type_analysis_2_to_5.csv");
            break;

        }

        case GameVersion::V6_TO_9: {

            game.type_count = 18;
            PointGraph = ReadCSV("type_analysis_6_to_9.csv");
            break;

        }

        case GameVersion::NEW: {

            game.type_count = 19;
            PointGraph = ReadCSV("type_analysis_new.csv");
            break;

        }

    }

}

// ゲームの初期状態
void InitGame(GameData& game) {

    static std::mt19937 gen{std::random_device{}()};

    game.round = 1;
    game.state = GameState::COIN_TOSS;

    for(auto& p : game.players) {

        p.hand.clear();
        p.deck.clear();
        p.used.clear();
        p.select.clear();
        p.score = 0.0;

    }

    for(int i=0; i<TYPE_COUNT; i++) {

        game.players[0].deck.push_back(static_cast<Type>(i));
        game.players[1].deck.push_back(static_cast<Type>(i));

    }
    
    std::shuffle(game.players[0].deck.begin(), game.players[0].deck.end(), gen);
    std::shuffle(game.players[1].deck.begin(), game.players[1].deck.end(), gen);

    // 初期手札とデッキの作成
    for(int i=0; i<4; i++) {

        for(int j=0; j<2; j++) {

            auto& deck = game.players[j].deck;
            Type card = deck.back();
            game.players[j].hand.push_back(card);
            deck.pop_back();

        }

    }

}

// コイントスを行う関数
void CoinToss(GameData& game) {

    static std::mt19937 gen{std::random_device{}()};
    std::uniform_int_distribution<int> dist(0, 1);
    game.current_turn = static_cast<PlayerID>(dist(gen));

}

// 墓地から手札を回収する関数(ラウンド効果)
void HandRecover(Player& p) {

    if(p.used.empty()) return;

    static std::mt19937 gen{std::random_device{}()};
    std::uniform_int_distribution<int> dist(0, p.used.size() - 1);

    int idx = dist(gen);
    p.hand.push_back(p.used[idx]);
    p.used.erase(p.used.begin() + idx);

}

// ラウンドを開始する関数
void RoundStart(GameData& game) {

    for(auto& p: game.players) {

        if(p.hand.empty()) {

            p.score -= 2;
            HandRecover(p);

        }

    }

    for(auto& p : game.players) p.select.clear();
    
}

// ドローを行う関数
void HandDraw(GameData& game, PlayerID id) {

    Player& p = game.players[static_cast<int>(id)];
    if(p.hand.size() >= 5 || p.deck.empty()) return ;
  
    p.hand.push_back(p.deck.back());
    p.deck.pop_back();

}

// ハンデスを行う関数
void HandDeath(GameData& game, PlayerID id) {

    Player& p = game.players[static_cast<int>(id)];
    if(p.hand.empty()) return ;
    
    
    static std::mt19937 gen{ std::random_device{}() };
    std::uniform_int_distribution<int> dist(0, p.hand.size() - 1);
    p.hand.erase(p.hand.begin() + dist(gen));

}

// プレイヤーがドローかハンデスを選択する関数
void PlayerCommand(GameData& game) {

    if(game.state != GameState::DRAW_OR_HANDDEATH) return;
    if(game.player_prepared) return;

    switch(game.command) {

        case GameCommand::DRAW: {

            HandDraw(game, PlayerID::PLAYER);
            game.player_prepared = true;
            game.command = GameCommand::NONE;
            break;

        }

        case GameCommand::HANDDEATH: {

            HandDeath(game, PlayerID::CPU);
            game.player_prepared = true;
            game.command = GameCommand::NONE;
            break;

        }

        default: break;

    }

}

// CPUがドローかハンデスを選択する関数
void CpuCommand(GameData& game) {

    if(game.cpu_prepared) return;

    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 1);

    int cpu_choice = dist(rng);
    if(cpu_choice == 0) HandDraw(game, PlayerID::CPU);
    else HandDeath(game, PlayerID::PLAYER);

    game.cpu_prepared = true;

}

// プレイヤーが手札を選択する関数
void PlayerSelect(GameData& game, int index, int count) {

    Player& p = game.players[static_cast<int>(PlayerID::PLAYER)];

    if(index < 0 || index >= (int)p.hand.size()) return ;

    Type t = p.hand[index];
    auto num = find(p.select.begin(), p.select.end(), t);
    
    // 選択済みなら解除
    if(num != p.select.end()) {

        p.select.erase(num);
        return;

    }

    // 未選択なら追加
    if((int)p.select.size() < count) p.select.push_back(t);

}

// CPUが手札を選択する関数
void CpuSelect(GameData& game, int count) {

    Player& cpu = game.players[static_cast<int>(PlayerID::CPU)];

    if(cpu.hand.empty()) return;

    // CPUはランダムな枚数を選んでしまうため、上限を設定する
    int max_count = std::min<int>(count, (int)cpu.hand.size());

    //CPUの使用枚数を決定
    static std::mt19937 gen{ std::random_device{}() };
    std::uniform_int_distribution<int> use_dist(1, max_count);
    int use = use_dist(gen);

    vector<Type> temp = cpu.hand;
    std::shuffle(temp.begin(), temp.end(), gen);

    for(int i=0; i<use; i++) cpu.select.push_back(temp[i]);
    
}

// 得点計算を行う関数
double RoundPoint(const vector<Type>& attack, Type defense) {

    double score = 0.0;
    int d = static_cast<int>(defense);

    for(Type a : attack) {

        // 得点表を参照して加算
        int ai = static_cast<int>(a);
        score += PointGraph[ai][d];

    }

    return score;

}

// ラウンド終了後の手札処理を行う関数
void HandManagement(GameData& game) {

    if(game.players[static_cast<int>(PlayerID::PLAYER)].select.empty() || game.players[static_cast<int>(PlayerID::CPU)].select.empty()) return ;

    // 得点加算
    if(game.current_turn == PlayerID::PLAYER)  game.players[static_cast<int>(PlayerID::PLAYER)].score += RoundPoint(game.players[static_cast<int>(PlayerID::PLAYER)].select, game.players[static_cast<int>(PlayerID::CPU)].select[0]);
    else game.players[static_cast<int>(PlayerID::CPU)].score += RoundPoint(game.players[static_cast<int>(PlayerID::CPU)].select, game.players[static_cast<int>(PlayerID::PLAYER)].select[0]);
    
    // プレイヤーの手札と墓地の更新
    for(Type c : game.players[static_cast<int>(PlayerID::PLAYER)].select) {

        auto a = find(game.players[static_cast<int>(PlayerID::PLAYER)].hand.begin(), game.players[static_cast<int>(PlayerID::PLAYER)].hand.end(), c);
                
        if(a != game.players[static_cast<int>(PlayerID::PLAYER)].hand.end()) {

            game.players[static_cast<int>(PlayerID::PLAYER)].used.push_back(*a);
            game.players[static_cast<int>(PlayerID::PLAYER)].hand.erase(a);

        }

    }

    // CPUの手札と墓地の更新
    for(Type c : game.players[static_cast<int>(PlayerID::CPU)].select) {

        auto a = find(game.players[static_cast<int>(PlayerID::CPU)].hand.begin(), game.players[static_cast<int>(PlayerID::CPU)].hand.end(), c);

        if(a != game.players[static_cast<int>(PlayerID::CPU)].hand.end()) {

            game.players[static_cast<int>(PlayerID::CPU)].used.push_back(*a);
            game.players[static_cast<int>(PlayerID::CPU)].hand.erase(a);

        }

    }

}

// 次のラウンドの用意
void NextRound(GameData& game) {

    game.players[(int)PlayerID::PLAYER].select.clear();
    game.players[(int)PlayerID::CPU].select.clear();
    game.player_prepared = false;
    game.cpu_prepared = false;

    game.current_turn = (game.current_turn == PlayerID::PLAYER) ? PlayerID::CPU : PlayerID::PLAYER;
    game.round++;
    game.state = (game.round > MAX_ROUNDS) ? GameState::GAME_END : GameState::ROUND_START;
    game.command = GameCommand::NONE;

}

// ゲーム状態を更新する関数
void UpdateGame(GameData& game) {

    // UIからの要求処理
    PlayerCommand(game);
    
    // ゲーム状態の更新
    switch(game.state) {

        case GameState::COIN_TOSS: {

            CoinToss(game);
            game.state = GameState::ROUND_START;
            break;

        }

        case GameState::ROUND_START: {

            RoundStart(game);
            game.player_prepared = false;
            game.cpu_prepared = false;
            game.state = GameState::DRAW_OR_HANDDEATH;
            break;

        }

        case GameState::DRAW_OR_HANDDEATH: {

            CpuCommand(game);
            if(game.player_prepared && game.cpu_prepared) game.state = GameState::SELECT_PHASE;
            break;

        }

        case GameState::SELECT_PHASE: {

            // CPUの選択
            int cpu_use = (game.current_turn == PlayerID::CPU) ? 2 : 1;
            int player_use = (game.current_turn == PlayerID::PLAYER) ? 2 : 1;

            // CPUの手札選択は一度のみ
            if(game.players[(int)PlayerID::CPU].select.empty()) CpuSelect(game, cpu_use);

            // プレイヤーの選択待ち
            if(game.command == GameCommand::USE) {

                if(game.players[(int)PlayerID::PLAYER].select.size() != player_use) {

                    game.command = GameCommand::NONE;
                    break;

                }

                game.command = GameCommand::NONE;
                game.state = GameState::ROUND_RESULT;
                
            }

            break;

        }

        case GameState::ROUND_RESULT: {

            HandManagement(game);
            if(game.command == GameCommand::NEXT_ROUND) NextRound(game);
            break;

        }

        /*
        case GameState::ROUND_EFFECT: {

            break;

        }
        */
        
        case GameState::GAME_END: {

            break;

        }
        
        default: break;

    }

}



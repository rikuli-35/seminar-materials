#pragma once
#include <vector>
#include <string>

// タイプ数・ラウンド数
constexpr int TYPE_COUNT = 19;
constexpr int MAX_ROUNDS = 10;

// タイプタグ
enum class Type {

    NORMAL = 0,
    FIRE = 1,
    WATER = 2,
    ELECTRIC = 3,
    GRASS = 4,
    ICE = 5,
    FIGHTING = 6,
    POISON = 7,
    GROUND = 8,
    FLYING = 9,
    PSYCHIC = 10,
    BUG = 11,
    ROCK = 12,
    GHOST = 13,
    DRAGON = 14,
    DARK = 15,
    STEEL = 16,
    FAIRY = 17,
    UNKNOWN = 18

};

// プレイヤータグ
enum class PlayerID { 
    
    PLAYER = 0, 
    CPU = 1

};

// バージョンタグ
enum class GameVersion {

    V1,
    V2_TO_5,
    V6_TO_9,
    NEW

};

// プレイヤー情報
struct Player {

    // 手札・山札・捨札・選択中の手札
    std::vector<Type> hand;
    std::vector<Type> deck;
    std::vector<Type> used;
    std::vector<Type> select;

    // プレイヤーのスコア
    double score = 0.0;

};

// ゲーム画面タグ
enum class GameState {

    COIN_TOSS,
    ROUND_START,
    DRAW_OR_HANDDEATH,
    SELECT_PHASE,
    ROUND_EFFECT,
    ROUND_RESULT,
    GAME_END

};

// ゲーム内アクションタグ
enum class GameCommand {

    NONE,
    DRAW,
    HANDDEATH,
    USE,
    NEXT_ROUND

};

// ゲーム情報
struct GameData {

    // 2人のプレイヤー
    Player players[2];

    // ラウンド数
    int round = 1;

    // タイプ数
    int type_count;

    // ターン管理
    PlayerID current_turn;

    // ゲーム状態
    GameVersion version;
    GameState state;
    GameCommand command = GameCommand::NONE;

    // ドローorハンデス選択
    bool player_prepared = false;
    bool cpu_prepared = false;

};

// 関数の宣言（準備・初期化）
std::vector<std::vector<double>> ReadCSV(const std::string& filename);
void LoadVersion(GameVersion version, GameData& game);
void InitGame(GameData& game);

// 関数の宣言（ラウンド処理）
void RoundStart(GameData& game);
void CoinToss(GameData& game);
void HandManagement(GameData& game);
void NextRound(GameData& game);
void UpdateGame(GameData& game);

// 関数の宣言(ラウンド効果)
void HandRecover(Player& p);

// 関数の宣言（プレイヤー操作）　
void HandDraw(GameData& game, PlayerID id);
void HandDeath(GameData& game, PlayerID id);
void PlayerCommand(GameData& game);
void PlayerSelect(GameData& game, int index, int count);

// 関数の宣言（CPU操作）
void CpuCommand(GameData& game);
void CpuSelect(GameData& game, int count);

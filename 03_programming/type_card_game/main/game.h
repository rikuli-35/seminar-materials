#pragma once
#include <vector>

constexpr int TYPE_COUNT = 19;
constexpr int MAX_ROUNDS = 10;

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

// ゲームの状態管理
enum class GameState {

    COIN_TOSS,
    ROUND_START,
    TURN,
    ROUND_RESULT,
    GAME_END

};

// プレイヤーデータ
struct Player {

    // 手札・山札・捨札・選択中の手札
    std::vector<int> hand;
    std::vector<int> deck;
    std::vector<int> used;
    std::vector<int> select;

    // プレイヤーのスコア
    double score = 0.0;

};

// ゲーム全体データ
struct GameData {

    // 2人のプレイヤー
    Player players[2];

    // ラウンド数
    int round = 1;

    // どちらのターンか？
    PlayerID attacker;
    PlayerID turn_end;

    // 次のラウンドの用意
    bool round_ready = false;

    // ゲーム状態
    GameState state = GameState::COIN_TOSS;

};

// 関数の宣言（準備・初期化）
void LoadVersion(GameVersion version, GameData& game);
void InitGame(GameData& game);

// 関数の宣言（ラウンド処理）
void RoundStart(GameData& game);
void RoundEnd(GameData& game);
bool IsRoundFinished(const GameData& game);

// 関数の宣言（プレイヤー操作）
void HandDraw(GameData& game, PlayerID id);
void HandDeath(GameData& game, PlayerID id);
void PlayerSelect(GameData& game, int index, int count);

// 関数の宣言（CPU操作）
void CpuSelect(GameData& game, int count);

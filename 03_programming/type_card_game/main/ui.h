#pragma once
#include "raylib.h"
#include <vector>
#include "game.h"

// タイプ名
enum TypeName {

    NORMAL,
    FIRE,
    WATER,
    ELECTRIC,
    GRASS,
    ICE,
    FIGHTING,
    POISON,
    GROUND,
    FLYING,
    PSYCHIC,
    BUG,
    ROCK,
    GHOST,
    DRAGON,
    DARK,
    STEEL,
    FAIRY,
    UNKNOWN,

};

// 手札の公開
enum class HandView {

    OPEN,
    CLOSE

};

// 画像挿入の構造体
struct UI{

    Texture2D tex;
    Rectangle bounds;

};

// 透明ボタンの形
enum class HitBoxShape {

    RECTANGLE,
    CIRCLE

};

// 透明ボタンの当たり判定
struct HitBox { 
    
    HitBoxShape shape;
    
    //四角形
    Rectangle rect;

    //円
    Vector2 center;
    float radius;

};

// バージョン選択の行き先
enum class VersionSelect {

    START_GAME,
    OPEN_CHART

};

// バージョン先変数
extern VersionSelect purpose;

// 画面状態の管理
enum class UIState {

    TITLE,
    VERSION_SELECT,
    GAME_EXPLANATION,
    TYPE_CHART_EXPLANATION,
    TYPE_CHART_1,
    TYPE_CHART_2_TO_5,
    TYPE_CHART_6_TO_9,
    TYPE_CHART_NEW,
    IN_GAME,
    RESULT,
    END,

};

// UIの発生イベント
enum class UIEvent {

    // 初期状態
    none,

    // タイトル画面
    game_start,
    open_explanation,
    open_type_chart,
    open_version_select,
    back,

    // バージョン別画面
    open_type_chart_1,
    open_type_chart_2_to_5,
    open_type_chart_6_to_9,
    open_type_chart_new,

    // ゲーム画面
    draw,
    handdeath,
    use,
    round_result,
    next_round,
    back_title
    
};

// 関数の宣言
void InitResources();
void UnloadResources();
void DrawUI(UIState ui, GameData& game);
UIEvent UpdateUI(UIState state, GameData& game);

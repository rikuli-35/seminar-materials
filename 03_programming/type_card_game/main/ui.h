#pragma once
#include "raylib.h"
#include <vector>
#include "game.h"


enum class HandView {

    OPEN,
    CLOSE,

};

// 手札座標の構造体
struct Hand{

    Rectangle player_area;
    Rectangle cpu_area;
    int space;

};

// 画像挿入の構造体
struct UIButton{

    Texture2D tex;
    Rectangle bounds;

};

// 透明ボタンの当たり判定
struct HitBox { Rectangle bounds; };

// 手札描画用配列・変数
static UIButton typeButtons[TYPE_COUNT];
static UIButton cardback;

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
    back,

    // バージョン選択
    select_v1,
    select_v2_to_v5,
    select_v6_to_v9,
    select_new,

    // ゲーム画面
    draw,
    handdeath,
    use,
    next_round,
    
};

// 関数の宣言
void InitResources();
void UnloadResources();
UIEvent UpdateUI(UIState state);
void DrawUI(UIState ui, GameData& game);

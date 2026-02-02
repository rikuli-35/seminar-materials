#include "ui.h"
#include "game.h"
#include "raylib.h"

using namespace std;

// マウス座標
static Vector2 mousePoint;

// ウィンドウサイズ
constexpr float W = 1280.0f;
constexpr float H = 720.0f;

// カードサイズ
constexpr float CARD_W = W * 0.08f;
constexpr float CARD_H = H * 0.21f;

// 透明ボタン
HitBox start_Button;
HitBox game_explanation_Button;
HitBox type_explanation_Button; 
HitBox version_1_Button;
HitBox version_2_to_5_Button;
HitBox version_6_to_9_Button;
HitBox version_new_Button;
HitBox back_Button;
HitBox draw_Button;
HitBox handdeath_Button;
HitBox use_Button;
HitBox next_Button;
HitBox back_title_Button;

// 背景画像
UI title_chart;
UI back_ground_chart;
UI version_select_chart;
UI player_turn_field_chart;
UI cpu_turn_field_chart;
UI result_win_chart;
UI result_lose_chart;
UI result_draw_chart;

// 背景画像の上に表示する画像
UI back_chart;
UI draw_chart;
UI handdeath_chart;
UI use_chart;
UI card_back_chart;
UI next_chart;

// タイプカード
struct TypeCard { Texture2D tex; };
static TypeCard typecard[TYPE_COUNT];

// バージョン管理
VersionSelect purpose = VersionSelect::START_GAME;

// 四角形の透明ボタンを作成する関数
HitBox CreateRectangleHitBox(float x, float y, float w, float h) {

    HitBox box;
    box.shape = HitBoxShape::RECTANGLE;
    box.rect = {x, y , w, h};
    return box;

}

// 円の透明ボタンを作成する関数
HitBox CreateCircleHitBox(float x, float y, float r) {

    HitBox box;
    box.shape = HitBoxShape::CIRCLE;
    box.center = {x, y};
    box.radius = r;
    return box;

}

// UIを作成する関数
UI CreateUI(const char* filename, float center_x, float center_y, float max_width, float max_height) {
    
    UI btn;
    
    // 画像のロード
    btn.tex = LoadTexture(filename);

    // 表示倍率の決定
    float scale_w = max_width / btn.tex.width;
    float scale_h = max_height / btn.tex.height;
    float scale = fminf(scale_w, scale_h);

    // 大きさの決定
    float w = btn.tex.width * scale;
    float h = btn.tex.height * scale;
    btn.bounds = {center_x - w * 0.5f, center_y - h * 0.5f, w, h};
    
    return btn;

}

// 作成したUIを描画する関数
void DisplayUI(UI btn) { 

    DrawTexturePro(btn.tex, (Rectangle){0, 0, (float)btn.tex.width, (float)btn.tex.height}, btn.bounds, (Vector2){0, 0}, 0.0f, WHITE); 

}

/*
// ボタンを描画する関数
void DrawButton(const UIButton& btn) {

    DrawTexturePro(btn.tex, (Rectangle){0, 0, (float)btn.tex.width, (float)btn.tex.height}, btn.bounds, (Vector2){0, 0}, 0.0f, CheckCollisionPointRec(mousePoint, btn.bounds) ? LIGHTGRAY : WHITE);

}
*/

// ボタン生成
void InitResources() {

    // UIの作成
    title_chart = CreateUI("UI/ai_title.png", W * 0.5f, H * 0.5f, W, H);
    back_ground_chart = CreateUI("UI/ai_background.png", W * 0.5f, H * 0.5f, W, H);
    version_select_chart = CreateUI("UI/ai_version_select.png", W * 0.5f, H * 0.5f, W, H);
    player_turn_field_chart = CreateUI("UI/ai_field_player_turn.png", W * 0.5f, H * 0.5f, W, H);
    cpu_turn_field_chart = CreateUI("UI/ai_field_cpu_turn.png", W * 0.5f, H * 0.5f, W, H);
    result_win_chart = CreateUI("UI/ai_result_win.png", W * 0.5f, H * 0.5f, W, H);
    result_lose_chart = CreateUI("UI/ai_result_lose.png", W * 0.5f, H * 0.5f, W, H);
    result_draw_chart = CreateUI("UI/ai_result_draw.png", W * 0.5f, H * 0.5f, W, H);
    
    back_chart = CreateUI("UI/ai_back.png", W * 0.2f, H * 0.9f, W * 0.1f, H * 0.8f);
    draw_chart = CreateUI("UI/ai_draw.png", W * 0.85f, H * 0.4f, W * 0.4f, H * 0.1f);
    handdeath_chart = CreateUI("UI/ai_handdeath.png", W * 0.85f, H * 0.6f, W * 0.4f, H * 0.1f);
    use_chart = CreateUI("UI/ai_use.png",W * 0.85f, H * 0.8f, W * 0.4f, H * 0.1f);
    card_back_chart = CreateUI("UI/ai_cardback.png", W * 0.2f, H * 0.05f, W, H);
    next_chart = CreateUI("UI/ai_next.png", W * 0.5f, H * 0.9f, W * 0.15f, H * 0.6f);
    
    // タイトル画面のボタン作成
    start_Button = CreateCircleHitBox(W * 0.37f, H * 0.52f, W * 0.09f);
    game_explanation_Button = CreateRectangleHitBox(W * 0.27f, H * 0.77f, W * 0.2f, H * 0.18f);
    type_explanation_Button = CreateCircleHitBox(W * 0.63f, H * 0.78f, W * 0.09f);
    
    // バージョン選択画面のボタン作成
    version_1_Button = CreateRectangleHitBox(W * 0.4f, H * 0.07f, W * 0.2f, H * 0.13f);
    version_2_to_5_Button = CreateRectangleHitBox(W * 0.4f, H * 0.3f, W * 0.2f, H * 0.13f);
    version_6_to_9_Button = CreateRectangleHitBox(W * 0.4f, H * 0.53f, W * 0.2f, H * 0.13f);
    version_new_Button = CreateRectangleHitBox(W * 0.4f, H * 0.76f, W * 0.2f, H * 0.13f);
    back_Button = CreateRectangleHitBox(W * 0.23f, H * 0.90f, W * 0.11f, H * 0.077f);

    // ゲーム画面のボタン作成
    draw_Button = CreateRectangleHitBox(W * 0.79f, H * 0.35f, W * 0.12f, H * 0.1f);
    handdeath_Button = CreateRectangleHitBox(W * 0.79f, H * 0.55f, W * 0.12f, H * 0.1f);
    use_Button = CreateRectangleHitBox(W * 0.79f, H * 0.75f, W * 0.12f, H * 0.1f);
    next_Button = CreateRectangleHitBox(W * 0.425f, H * 0.845f, W * 0.15f, H * 0.12f);
    back_title_Button = CreateRectangleHitBox(W * 0.425f, H * 0.78f, W * 0.15f, H * 0.115f);
    
    // タイプカード一覧
    static_assert(TYPE_COUNT == 19, "mismatch");
    const char* typefiles[TYPE_COUNT] = {

        "UI/type/normal_card.png", "UI/type/fire_card.png", "UI/type/water_card.png", "UI/type/electric_card.png", "UI/type/grass_card.png",
        "UI/type/ice_card.png", "UI/type/fighting_card.png", "UI/type/poison_card.png", "UI/type/ground_card.png", "UI/type/flying_card.png",
        "UI/type/psychic_card.png", "UI/type/bug_card.png", "UI/type/rock_card.png", "UI/type/ghost_card.png", "UI/type/dragon_card.png",
        "UI/type/dark_card.png", "UI/type/steel_card.png", "UI/type/fairy_card.png","UI/type/unknown.png"

    };

    // タイプカードの作成
    for(int i=0; i<TYPE_COUNT; i++) {

        typecard[i].tex = LoadTexture(typefiles[i]);
        if(typecard[i].tex.id == 0) TraceLog(LOG_ERROR, "Failed %d", i); 

    }

}

// カードの表示位置を計算する関数
void DrawHandCards(const vector<Type>& cards, float x, float y, float space, HandView view) {

    for(int i=0; i<cards.size(); i++) {

        Type type = cards[i];
        int num = static_cast<int>(type);
        if(num < 0 || num >= TYPE_COUNT) continue;

        Rectangle DrawArea {x + i * space, y, CARD_W, CARD_H};
        Texture2D& tex = (view == HandView::OPEN) ? typecard[num].tex : card_back_chart.tex;
        Rectangle src {0, 0, (float)tex.width, (float)tex.height};

        DrawTexturePro(tex, src, DrawArea, {0, 0}, 0.0f, WHITE);

        // デバッグ用
        DrawRectangleLinesEx(DrawArea, 2, GREEN);

    }

}

// フィールドを描画する関数
void DrawField(GameData& game) {

    // 現在のターンを検索
    bool PlayerTurn = (game.current_turn == PlayerID::PLAYER);

    // フィールド画像の読み込み
    if(PlayerTurn) DisplayUI(player_turn_field_chart);
    else DisplayUI(cpu_turn_field_chart);
    
    // ターン数の表示
    DrawText(TextFormat("%d", game.round), W * 0.735f, H * 0.48f, 32, BLACK);

}

// プレイヤーカードを描画する関数
void DrawPlayerHand(GameData& game) {

    Player& player = game.players[static_cast<int>(PlayerID::PLAYER)];
    float x = W * 0.25f;
    float y = H * 0.75f;
    float space = W * 0.09;

    DrawHandCards(player.hand, x, y, space, HandView::OPEN);

}

// CPUカードを描画する関数
void DrawCpuHand(GameData& game) {
    
    Player& cpu = game.players[static_cast<int>(PlayerID::CPU)];
    float x = W * 0.28f;
    float y = W * 0.01f;
    float space = W * 0.09;

    DrawHandCards(cpu.hand, x, y, space, HandView::CLOSE);
    
}

// マウスの接触判定を行う関数
bool IsButtonClicked(const HitBox& btn) {

    bool hit = false;
    switch(btn.shape) {

        case HitBoxShape::RECTANGLE: {

            hit = CheckCollisionPointRec(mousePoint, btn.rect);
            break;

        }

        case HitBoxShape::CIRCLE: {

            hit = CheckCollisionPointCircle(mousePoint, btn.center, btn.radius);
            break;

        }
    }

    return (hit && IsMouseButtonReleased(MOUSE_BUTTON_LEFT));
    
}

// ラウンド結果を描画する関数
void DrawRoundResult(GameData& game) {

    DrawText(TextFormat("ROUND %d", game.round), W * 0.38f, H* 0.1f, 80, GOLD);

    // 使用した手札を表示
    DrawText("YOU USED", W * 0.1f, H * 0.5f, 20, BLACK);
    DrawHandCards(game.player_last_used, W * 0.25f, H * 0.4f, W * 0.09, HandView::OPEN); 
    DrawText("VS", W * 0.48f, H * 0.45f, 50, RED);
    DrawText("CPU USED", W * 0.8f, H * 0.5f, 20, BLACK);
    DrawHandCards(game.cpu_last_used, W * 0.6f, H * 0.4f, W * 0.09, HandView::OPEN);

    // 現在のスコアを表示
    DrawText(TextFormat("YOU: %.1f (+%.1f)", game.players[(int)PlayerID::PLAYER].score, (game.current_turn == PlayerID::PLAYER ? game.round_point : 0.0f)), W * 0.25f, H * 0.7f, 30, BLUE);
    DrawText(TextFormat("CPU: %.1f (+%.1f)", game.players[(int)PlayerID::CPU].score, (game.current_turn == PlayerID::CPU ? game.round_point : 0.0f)), W * 0.6f, H * 0.7f, 30, BLUE);
    
}

// デバック用関数(透明ボタンの確認)
void DrawHitBoxDebug(const HitBox& btn) {

    if(btn.shape == HitBoxShape::RECTANGLE) DrawRectangleLinesEx(btn.rect, 2, RED);
    else DrawCircleLines((int)btn.center.x, (int)btn.center.y, btn.radius, GREEN);
    
}

// ゲーム内描画を行う関数
void DrawGame(GameData& game) {

    switch(game.state) {

        case GameState::SELECT_PHASE: {

            DrawCpuHand(game);
            DrawPlayerHand(game);
            
            break;

        }

        case GameState::ROUND_RESULT: {

            DrawRoundResult(game);
            // 選ばれたカードを表示＋スコアの表示
            break;

        }

        /*
        case GameState::ROUND_EFFECT: {

            break;

        }
        */

        default: break;

    }

}

// デバッグ用(画面遷移バグ発見)
void DrawDebugStatus(UIState ui, GameData& game) {
    
    DrawRectangle(10, 10, 300, 150, Fade(BLACK, 0.6f));

    DrawText(TextFormat("UI State: %d", (int)ui), 20, 20, 20, RAYWHITE);
    DrawText(TextFormat("Game State: %d", (int)game.state), 20, 45, 20, RAYWHITE);
    DrawText(TextFormat("Command: %d", (int)game.command), 20, 70, 20, RAYWHITE);
    DrawText(TextFormat("Player Prepared: %s", game.player_prepared ? "YES" : "NO"), 20, 95, 20, RAYWHITE);
    DrawText(TextFormat("Round: %d", game.round), 20, 120, 20, RAYWHITE);

}

// UIの更新処理
UIEvent UpdateUI(UIState state, GameData& game) {
    
    // マウスの位置取得
    mousePoint = GetMousePosition();
        
    // 各画面での接触判定
    switch(state) {

        // タイトル画面
        case UIState::TITLE: {

            if(IsButtonClicked(start_Button)) {

                purpose = VersionSelect::START_GAME;
                return UIEvent::open_version_select;

            }

            if(IsButtonClicked(game_explanation_Button)) return UIEvent::open_explanation;

            if(IsButtonClicked(type_explanation_Button)) {
                
                purpose = VersionSelect::OPEN_CHART;
                return UIEvent::open_type_chart;

            }

            break;

        }
        
        
        // バージョン選択画面
        case UIState::VERSION_SELECT: {

            if(IsButtonClicked(version_1_Button)) {
                
                if(purpose == VersionSelect::START_GAME) return UIEvent::game_start;
                if(purpose == VersionSelect::OPEN_CHART) return UIEvent::open_type_chart_1;

            }
               
            if(IsButtonClicked(version_2_to_5_Button)) {
                
                if(purpose == VersionSelect::START_GAME) return UIEvent::game_start;
                if(purpose == VersionSelect::OPEN_CHART) return UIEvent::open_type_chart_2_to_5;

            }

            if(IsButtonClicked(version_6_to_9_Button)) {
                
                if(purpose == VersionSelect::START_GAME) return UIEvent::game_start;
                if(purpose == VersionSelect::OPEN_CHART) return UIEvent::open_type_chart_6_to_9;

            }

            if(IsButtonClicked(version_new_Button)) {
                
                if(purpose == VersionSelect::START_GAME) return UIEvent::game_start;
                if(purpose == VersionSelect::OPEN_CHART) return UIEvent::open_type_chart_new;

            }

            if(IsButtonClicked(back_Button)) return UIEvent::back;

            break;

        }
 
        // ゲーム説明画面
        case UIState::GAME_EXPLANATION: {

            if(IsButtonClicked(back_Button)) return UIEvent::back;
            break;

        }

        /*
        // 得点表バージョン選択画面
        case UIState::TYPE_CHART_EXPLANATION: {

            if(IsButtonClicked(version_1_Button)) return UIEvent::select_v1;
            if(IsButtonClicked(version_2_to_5_Button)) return UIEvent::select_v2_to_v5;
            if(IsButtonClicked(version_6_to_9_Button)) return UIEvent::select_v6_to_v9;
            if(IsButtonClicked(version_new_Button)) return UIEvent::select_new;
            if(IsButtonClicked(back_Button)) return UIEvent::back;
            break;

        }
    
        // バージョン別得点表確認画面
        case UIState::TYPE_CHART_1:
        case UIState::TYPE_CHART_2_TO_5:
        case UIState::TYPE_CHART_6_TO_9:
        case UIState::TYPE_CHART_NEW: {
        
            if(IsButtonClicked(back_Button)) return UIEvent::back;
            break;

        }
        */
        
        // ゲーム画面
        case UIState::IN_GAME: {

            switch(game.state) {
                
                case GameState::DRAW_OR_HANDDEATH: {

                    if(IsButtonClicked(draw_Button)) return UIEvent::draw;
                    if(IsButtonClicked(handdeath_Button)) return UIEvent::handdeath;
                    break;

                }

                case GameState::SELECT_PHASE: {

                    if(IsButtonClicked(use_Button)) return UIEvent::use;

                    Player& player = game.players[(int)PlayerID::PLAYER];
                    int use_count = (game.current_turn == PlayerID::PLAYER) ? 2 : 1;

                    float x = W * 0.25;
                    float y = H * 0.75f;
                    float space = W * 0.09f;

                    for(int i=0; i<(int)player.hand.size(); i++) {

                        Rectangle card_area = {x + i * space, y, CARD_W, CARD_H};
                        if(CheckCollisionPointRec(mousePoint, card_area) && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) PlayerSelect(game, i, use_count);

                    }

                    break;
                
                }

                default: break;

            }

            break;

        }
        
        // リザルト画面
        case UIState::RESULT: {

            if(IsButtonClicked(next_Button)) return UIEvent::next_round;
            break;

        }

        
        case UIState::END: {

            if(IsButtonClicked(back_title_Button)) return UIEvent::back_title;
            break;

        }
        

    }

    return UIEvent::none;

}


// UIの描画を行う関数
void DrawUI(UIState ui, GameData& game) {

    switch(ui) {

        // タイトル画面
        case UIState::TITLE: {

            DisplayUI(title_chart);
            DrawHitBoxDebug(start_Button);
            DrawHitBoxDebug(game_explanation_Button);
            DrawHitBoxDebug(type_explanation_Button);
            break;

        }

        // バージョン選択画面
        case UIState::VERSION_SELECT: 
        case UIState::TYPE_CHART_EXPLANATION: {

            DisplayUI(version_select_chart);
            DrawHitBoxDebug(version_1_Button);
            DrawHitBoxDebug(version_2_to_5_Button);
            DrawHitBoxDebug(version_6_to_9_Button);
            DrawHitBoxDebug(version_new_Button);
            DrawHitBoxDebug(back_Button);
            break;

        }

        // ゲーム説明画面
        case UIState::GAME_EXPLANATION: {
            
            DisplayUI(back_ground_chart);
            DrawHitBoxDebug(back_Button);
            break;

        }
        
        /*
        // タイプ相性バージョン１
        case UIState::TYPE_CHART_1: {

            DrawChart(type_chart_1);
            DrawHitBoxDebug(back_Button);
            break;

        }

        // タイプ相性バージョン2~5
        case UIState::TYPE_CHART_2_TO_5: {

            DrawChart(type_chart_2_to_5);
            DrawHitBoxDebug(back_Button);
            break;

        }

        // タイプ相性バージョン6~9
        case UIState::TYPE_CHART_6_TO_9: {

            DrawChart(type_chart_6_to_9);
            DrawHitBoxDebug(back_Button);
            break;

        }

        // タイプ相性バージョンnew
        case UIState::TYPE_CHART_NEW: {

            DrawChart(type_chart_new);
            DrawHitBoxDebug(back_Button);
            break;

        }

        */

        // ゲーム画面
        case UIState::IN_GAME:  { 

            DrawField(game);
            DrawGame(game);

            if(game.state == GameState::DRAW_OR_HANDDEATH) {

                DisplayUI(draw_chart);
                DisplayUI(handdeath_chart);
                DrawHitBoxDebug(draw_Button);
                DrawHitBoxDebug(handdeath_Button);

            }

            if(game.state == GameState::SELECT_PHASE) {

                DisplayUI(use_chart);
                DrawHitBoxDebug(use_Button);

            }

            // デバック用
            DrawText(TextFormat("STATE: %d", (int)game.state),20, 20, 20, DARKGRAY);

            DrawText(TextFormat("ROUND: %d", game.round),20, 45, 20, DARKGRAY);

            DrawText(TextFormat("TURN: %s", game.current_turn == PlayerID::PLAYER ? "PLAYER" : "CPU"),20, 70, 20, DARKGRAY);

            DrawText(TextFormat("SELECTED: %d", game.players[(int)PlayerID::PLAYER].select.size()), 20, 100, 20, RED);
            
            break;

        }

        // ラウンドリザルト画面
        case UIState::RESULT: {

            DrawRoundResult(game);
            DisplayUI(next_chart);
            DrawHitBoxDebug(next_Button);
            break;

        }

        // 最終結果画面
        case UIState::END: { 

            if(game.players[(int)(PlayerID::PLAYER)].score > game.players[(int)(PlayerID::CPU)].score) DisplayUI(result_win_chart);
            else if(game.players[(int)(PlayerID::PLAYER)].score < game.players[(int)(PlayerID::CPU)].score) DisplayUI(result_lose_chart);
            else DisplayUI(result_draw_chart);

            DrawHitBoxDebug(back_title_Button);
            break;

        }

    }

    DrawDebugStatus(ui, game);

}

// 終了時の処理を行う関数
void UnloadResources() {

    UnloadTexture(title_chart.tex);
    UnloadTexture(back_ground_chart.tex);
    UnloadTexture(version_select_chart.tex);
    UnloadTexture(player_turn_field_chart.tex);
    UnloadTexture(cpu_turn_field_chart.tex);
    UnloadTexture(draw_chart.tex);
    UnloadTexture(handdeath_chart.tex);
    UnloadTexture(use_chart.tex);
    UnloadTexture(card_back_chart.tex);
    UnloadTexture(next_chart.tex);
    /*
    UnloadTexture(result_win_chart);
    UnloadTexture(result_lose_chart);
    UnloadTexture(result_draw_chart);
    */
    
    for(int i=0; i<TYPE_COUNT; i++) UnloadTexture(typecard[i].tex);
   

}


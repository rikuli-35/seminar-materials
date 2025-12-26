#include "ui.h"
#include "game.h"
#include "raylib.h"

// マウス座標の用意
static Vector2 mousePoint;

// システムボタン一覧
HitBox start_Button;
HitBox game_explanation_Button;
HitBox type_explanation_Button; 

// チャート一覧
UIButton title_chart;
UIButton back_ground;

/*
// 手札
Hand hand;
*/

// システムボタン・チャートを作成する関数
UIButton CreateSystemButton(const char* filename, float x, float y, float scale) {
    
    UIButton btn;
    btn.tex = LoadTexture(filename);
    btn.bounds.x = x;
    btn.bounds.y = y;
    btn.bounds.width = btn.tex.width * scale;
    btn.bounds.height = btn.tex.height * scale;
    
    return btn;

}

// 透明ボタンを作成する関数
HitBox CreateHitBox(float x, float y, float w, float h) {

    HitBox box;
    box.bounds = {x, y , w, h};
    return box;

}

/*
// タイプボタンを作成する関数
UIButton CreateCardButton(const char* filename) {

    UIButton card;
    card.tex = LoadTexture(filename);
    card.bounds = (Rectangle){0, 0, (float)card.tex.width * 0.5f, (float)card.tex.height * 0.5f};

    return card;

}
*/

// ボタンを描画する関数
void DrawButton(const UIButton& btn) {

    DrawTexturePro(btn.tex, (Rectangle){0, 0, (float)btn.tex.width, (float)btn.tex.height}, btn.bounds, (Vector2){0, 0}, 0.0f, CheckCollisionPointRec(mousePoint, btn.bounds) ? LIGHTGRAY : WHITE);

}

// チャートを描画する関数
void DrawChart(UIButton btn) {

    DrawTexturePro(btn.tex, (Rectangle){0, 0, (float)btn.tex.width, (float)btn.tex.height}, btn.bounds, (Vector2){0, 0}, 0.0f, WHITE);

}

/*

// 手札を描画する関数
void DrawHand(const std::vector<int>& cards, const Hand& layout, Rectangle area, HandView view) {

    for(int i=0; i<cards.size(); i++) {

        UIButton card = (view == HandView::OPEN) ? typeButtons[cards[i]] : cardback;
        card.bounds.x = area.x + i * layout.space;
        card.bounds.y = area.y;
        DrawButton(card);
 
    }

}


*/

// ボタン生成（各座標はのちに設定する）
void InitResources() {

    // システムボタンの作成
    start_Button = CreateHitBox(325, 250, 200, 200);
    game_explanation_Button = CreateHitBox(300, 510, 250, 140);
    type_explanation_Button = CreateHitBox(610, 400, 250, 250);

    // チャートの作成
    title_chart = CreateSystemButton("UI/ai_title.png", 250, 5, 0.8f);
    back_ground = CreateSystemButton("UI/ai_background.png", 0, 0, 0.8f);

    /*
    // タイプカード一覧
    const char* typefiles[TYPE_COUNT] = {

        "UI/type/normal_button.png", "UI/type/fire_button.png", "UI/type/water_button.png", "UI/type/electric_button.png", "UI/type/grass_button.png",
        "UI/type/ice_button.png", "UI/type/fighting_button.png", "UI/type/poison_button.png", "UI/type/ground_button.png", "UI/type/flying_button.png",
        "UI/type/psychic_button.png", "UI/type/bug_button.png", "UI/type/rock_button.png", "UI/type/ghost_button.png", "UI/type/dragon_button.png",
        "UI/type/dark_button.png", "UI/type/steel_button.png", "UI/type/fairy_button.png"

    };

    // タイプカードの作成
    for(int i=0; i<TYPE_COUNT; i++) {

        typeButtons[i] = CreateCardButton(typefiles[i]);

    }
    cardback = CreateCardButton("UI/type/cpu_card.png");

    // 手札の作成
    hand.player_area = {100, 500, 800, 150};
    hand.cpu_area = {100, 100, 800, 150};
    hand.space = 120;

    */
}

// マウスの接触判定を行う関数
bool IsButtonClicked(const HitBox& btn) {

    return (CheckCollisionPointRec(mousePoint, btn.bounds) && IsMouseButtonReleased(MOUSE_BUTTON_LEFT));
    
}

// UIの更新処理
UIEvent UpdateUI(UIState state) {
    
    // マウスの位置取得
    mousePoint = GetMousePosition();
        
    // 各画面での接触判定
    switch(state) {

        // タイトル画面
        case UIState::TITLE: {

            if(IsButtonClicked(start_Button)) return UIEvent::game_start;
            if(IsButtonClicked(game_explanation_Button)) return UIEvent::open_explanation;
            if(IsButtonClicked(type_explanation_Button)) return UIEvent::open_type_chart;
            break;

        }
        
        /*
        // バージョン選択画面
        case UIState::VERSION_SELECT: {

            if(IsButtonClicked(version_1_Button)) return UIEvent::select_v1;
            if(IsButtonClicked(version_2_to_5_Button)) return UIEvent::select_v2_to_v5;
            if(IsButtonClicked(version_6_to_9_Button)) return UIEvent::select_v6_to_v9;
            if(IsButtonClicked(version_new_Button)) return UIEvent::select_new;
            if(IsButtonClicked(back_Button)) return UIEvent::back;
            break;

        }
 
        // ゲーム説明画面
        case UIState::GAME_EXPLANATION: {

            if(IsButtonClicked(back_to_title_Button)) return UIEvent::back;
            break;

        }

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

        // ゲーム画面
        case UIState::IN_GAME: {

            if(IsButtonClicked(draw_Button)) return UIEvent::draw;
            if(IsButtonClicked(handdeath_Button)) return UIEvent::handdeath;
            if(IsButtonClicked(use_Button)) return UIEvent::use;
            break;

        }

        // リザルト画面
        case UIState::RESULT: {

            if(IsButtonClicked(next_round_Button)) return UIEvent::next_round;
            break;

        }

        case UIState::END: {

            // if(IsButtonClicked(back_to_title_Button)) return UIEvent::game_start;
            break;
        }

        */

    }

    return UIEvent::none;

}

// UIの描画を行う関数
void DrawUI(UIState ui, GameData& game) {

    switch(ui) {

        // タイトル画面
        case UIState::TITLE: {

            DrawChart(title_chart);
            DrawRectangleLinesEx(start_Button.bounds, 2, RED);
            DrawRectangleLinesEx(game_explanation_Button.bounds, 2, BLUE);
            DrawRectangleLinesEx(type_explanation_Button.bounds, 2, GREEN);
            break;

        }

        /*
        // バージョン選択画面
        case UIState::VERSION_SELECT: {

            DrawButton(back_Button);
            break;

        }

        // ゲーム説明画面
        case UIState::GAME_EXPLANATION: {

            DrawButton(version_1_Button);
            DrawButton(version_2_to_5_Button);
            DrawButton(version_6_to_9_Button);
            DrawButton(version_new_Button);
            DrawChart(explanation_chart);
            DrawButton(back_Button);
            break;

        }
        
        // タイプ相性確認画面
        case UIState::TYPE_CHART_EXPLANATION: {

            DrawButton(version_1_Button);
            DrawButton(version_2_to_5_Button);
            DrawButton(version_6_to_9_Button);
            DrawButton(version_new_Button);
            DrawButton(back_Button);
            break;

        }

        // タイプ相性バージョン１
        case UIState::TYPE_CHART_1: {

            DrawChart(type_chart_1);
            DrawButton(back_Button);
            break;

        }

        // タイプ相性バージョン2~5
        case UIState::TYPE_CHART_2_TO_5: {

            DrawChart(type_chart_2_to_5);
            DrawButton(back_Button);
            break;

        }

        // タイプ相性バージョン6~9
        case UIState::TYPE_CHART_6_TO_9: {

            DrawChart(type_chart_6_to_9);
            DrawButton(back_Button);
            break;

        }

        // タイプ相性バージョンnew
        case UIState::TYPE_CHART_NEW: {

            DrawChart(type_chart_new);
            DrawButton(back_Button);
            break;

        }

        // ゲーム画面
        case UIState::IN_GAME:  { 

            DrawChart(game_field);
            DrawHand(game.players[static_cast<int>(PlayerID::PLAYER)].hand, hand, hand.player_area, HandView::OPEN);
            DrawHand(game.players[static_cast<int>(PlayerID::CPU)].hand, hand, hand.cpu_area, HandView::CLOSE);
            DrawButton(use_Button);
            if(game.attacker == PlayerID::PLAYER) DrawChart(you_are_attack_chart);
            else DrawChart(you_are_defense_chart);
            break;

        }

        // ラウンドリザルト画面
        case UIState::RESULT: {

            DrawButton(next_round_Button);
            break;

        }

        // 最終結果画面
        case UIState::END: { 

            if(game.players[static_cast<int>(PlayerID::PLAYER)].score > game.players[static_cast<int>(PlayerID::CPU)].score) DrawChart(you_win_chart);
            else if(game.players[static_cast<int>(PlayerID::PLAYER)].score < game.players[static_cast<int>(PlayerID::CPU)].score) DrawChart(you_lose_chart);
            else DrawChart(draw_chart);
            break;

        }

        */

    }

}

// 終了時の処理を行う関数
void UnloadResources() {

    UnloadTexture(title_chart.tex);

    // for(int i=0; i<TYPE_COUNT; i++) UnloadTexture(typeButtons[i].tex);
   

}




#include "raylib.h"
#include "game.h"
#include "ui.h"

// ゲーム全体の状態管理
void GameStateManagement(GameData& game) {

    switch(game.state) {

        case GameState::COIN_TOSS: {

            game.state = GameState::ROUND_START;
            break;

        }

        case GameState::ROUND_START: {

            if(game.round_ready) game.state = GameState::TURN;
            break;

        }

        case GameState::TURN: {

            if(IsRoundFinished(game)) game.state = GameState::ROUND_RESULT;
            break;

        }

        case GameState::ROUND_RESULT: {

            break;

        }

        case GameState::GAME_END: {

            break;

        }

    }

}

// UIの全体の状態管理
void UIStateManagement(UIEvent event, GameData& game, UIState& ui) {

    switch(event) {

        case UIEvent::game_start: {

            game.state = GameState::COIN_TOSS;
            ui = UIState::VERSION_SELECT;
            break;

        }

        case UIEvent::select_v1: {

            LoadVersion(GameVersion::V1, game);
            InitGame(game);
            ui = UIState::IN_GAME;
            break;

        }

        case UIEvent::select_v2_to_v5: {

            LoadVersion(GameVersion::V2_TO_5, game);
            InitGame(game);
            ui = UIState::IN_GAME;
            break;
            
        }

        case UIEvent::select_v6_to_v9: {

            LoadVersion(GameVersion::V6_TO_9, game);
            InitGame(game);
            ui = UIState::IN_GAME;
            break;
            
        }

        case UIEvent::select_new: {

            LoadVersion(GameVersion::NEW, game);
            InitGame(game);
            ui = UIState::IN_GAME;
            break;
            
        }

        case UIEvent::draw: {

            if(ui == UIState::IN_GAME) HandDraw(game, PlayerID::PLAYER);
            break;

        }

        case UIEvent::handdeath: {

            if(ui == UIState::IN_GAME) HandDeath(game, PlayerID::CPU);
            break;

        }

        case UIEvent::next_round: {

            RoundEnd(game);
            if(game.round > MAX_ROUNDS) {

                game.state = GameState::GAME_END; 
                ui = UIState::RESULT;
            }   
            else game.state = GameState::ROUND_START;
            break;

        }

        default:
        break;

    }

}


int main() {
    
    // ゲーム画面の起動
    InitWindow(1200, 675, "Type card Battle !");
    SetTargetFPS(60);
    
    GameData game;
    UIState uistate = UIState::TITLE;

    // ゲームの初期化
    InitResources();
    InitGame(game);

    // 画面を閉じるまで継続して行う処理
    while(!WindowShouldClose()) {

        // 入力発生イベントの処理
        UIEvent event = UpdateUI(uistate);

        // ゲームへの反映処理
        UIStateManagement(event, game, uistate);

        // ゲーム状態の更新処理
        GameStateManagement(game);
        
        // 描画処理
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawUI(uistate, game);
        EndDrawing();

    }

    // ゲーム終了
    UnloadResources();
    CloseWindow();

}

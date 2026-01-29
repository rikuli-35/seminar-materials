#include "raylib.h"
#include "game.h"
#include "ui.h"

// UIの全体の状態管理
void UIStateManagement(UIEvent event, GameData& game, UIState& ui) {

    switch(event) {

        case UIEvent::game_start: {

            LoadVersion(game.version, game);
            InitGame(game);
            ui = UIState::IN_GAME;
            break;

        }

        case UIEvent::open_explanation: {

            ui = UIState::GAME_EXPLANATION;
            break;

        }

        case UIEvent::open_version_select:
        case UIEvent::open_type_chart: {

            ui = UIState::VERSION_SELECT;
            break;

        }

        case UIEvent::open_type_chart_1: {

            ui = UIState::TYPE_CHART_1;
            break;

        }

        case UIEvent::open_type_chart_2_to_5: {

            ui = UIState::TYPE_CHART_2_TO_5;
            break;
            
        }

        case UIEvent::open_type_chart_6_to_9: {

            ui = UIState::TYPE_CHART_6_TO_9;
            break;
            
        }

        case UIEvent::open_type_chart_new: {

            ui = UIState::TYPE_CHART_NEW;
            break;
            
        }

        case UIEvent::back: {

            switch(ui) {

                case UIState::VERSION_SELECT: {

                    ui = UIState::TITLE;
                    break;

                }

                case UIState::GAME_EXPLANATION: {

                    ui = UIState::TITLE;
                    break;

                }

                case UIState::TYPE_CHART_1:
                case UIState::TYPE_CHART_2_TO_5:
                case UIState::TYPE_CHART_6_TO_9:
                case UIState::TYPE_CHART_NEW: {

                    ui = UIState::VERSION_SELECT;
                    break;

                }

                default: {

                    ui = UIState::TITLE;
                    break;

                }

                break;

            }
            
        }

        case UIEvent::draw: {

            if(ui == UIState::IN_GAME && game.state == GameState::DRAW_OR_HANDDEATH) game.command = GameCommand::DRAW;
            break;

        }

        case UIEvent::handdeath: {

            if(ui == UIState::IN_GAME && game.state == GameState::DRAW_OR_HANDDEATH) game.command = GameCommand::HANDDEATH;
            break;

        }

        case UIEvent::use: {

            if(ui == UIState::IN_GAME) game.command = GameCommand::USE;
            break;

        }

        case UIEvent::round_result: {

            TraceLog(LOG_INFO, ">>> UI STATE CHANGED TO RESULT");
            ui = UIState::RESULT;
            break;

        }

        case UIEvent::next_round: {

            ui = UIState::IN_GAME;
            game.command = GameCommand::NEXT_ROUND;
            break;

        }

        default:
        break;

    }

}


int main() {
    
    // ゲーム画面の起動
    InitWindow(1280, 720, "Type card Battle !");
    SetTargetFPS(60);
    
    GameData game;
    game.version = GameVersion::V1;
    UIState uistate = UIState::TITLE;

    // ゲームの初期化
    InitResources();
    InitGame(game);

    // 画面を閉じるまで継続して行う処理
    while(!WindowShouldClose()) {

        // 入力発生イベントの処理
        UIEvent event = UpdateUI(uistate, game);

        // ゲームへの反映処理
        UIStateManagement(event, game, uistate);

        // ゲーム状態の更新処理
        UpdateGame(game);
        
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

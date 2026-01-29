# 対NPCのタイプ相性カードゲームバトル

C・C++言語でNPC対戦型のカードゲームを自作しました。

下記の資料からゲームの概要をご覧いただけます。

- デモ版の解説資料：[type_card_battle_materials.pdf](./demo/type_card_battle_materials.pdf)

- メイン版の解説資料（現在制作中）：

# 実装コード

C言語のコード：[type_card_battle.c](./demo/type_card_battle.c/)

C++のコード(現在制作中/随時更新)：[type_card_battle2.cpp](./main/type_card_battle2.cpp/)
- game.h　（ゲームロジックに関するヘッダファイル）：[game.h](./main/game.h/)
- game.cpp （ゲームロジックに関する実装ファイル）：[game.cpp](./main/game.cpp/)
- ui.h （UIに関するヘッダファイル）：[ui.h](./main/ui.h/)
- ui.cpp （UIに関する実装ファイル）：[ui.cpp](./main/ui.cpp/)

# 制作状況について(2026/1/29)

- 「ゲーム開始→手札を選択→「使う」ボタンを押す」ところまではプレイ可能
- 「使う」ボタンを押した後に、お互いの手札を参照した結果画面を表示する予定
- しかしながら、画面遷移がうまくいかず、結果画面が表示されないバグが発生しており、現在対処中です。
- UIは、Geminiで画像生成→透明ボタンの配置→クリック判定→画面遷移、という形で実装しています。
  



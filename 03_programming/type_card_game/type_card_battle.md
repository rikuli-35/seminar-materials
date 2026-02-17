# 対NPCのタイプ相性カードゲームバトル

C・C++言語でNPC対戦型のカードゲームを制作しました。

下記の資料からゲームの概要をご覧いただけます（メイン版推奨）。

- デモ版の解説資料：[type_card_battle_materials.pdf](./demo/type_card_battle_materials.pdf)

- メイン版の解説資料（現在コード制作中のため、設計思想のみ記載）：[type_card_battle(simple_version).pdf](./main/type_card_battle2_1.pdf/)

# 実装コード

C言語のコード（デモ版）：[type_card_battle.c](./demo/type_card_battle.c/)

C++のコード(現在制作中/随時更新)
- type_card_battle2.cpp （メイン関数）：[type_card_battle2.cpp](./main/type_card_battle2.cpp/)
- game.h　（ゲームロジックに関するヘッダファイル）：[game.h](./main/game.h/)
- game.cpp （ゲームロジックに関する実装ファイル）：[game.cpp](./main/game.cpp/)
- ui.h （UIに関するヘッダファイル）：[ui.h](./main/ui.h/)
- ui.cpp （UIに関する実装ファイル）：[ui.cpp](./main/ui.cpp/)

# UI
デモ版での反省点を踏まえて、メイン版ではUIの実装も行いました。

なお、デザイン等の知識は持ち合わせていないため、画像は生成系AIを用いて制作しました。

UIフォルダ：[UI](./main/UI)

# 現在の制作状況について(2026/2/2)

- ゲームを一通りプレイすることが可能になりました。
  
→ただし、バージョンをV1に固定しているため、どのバージョンを選択してもV1の画面が表示されます。

→また、デバッグ用の表示が残っているままなので、見栄えが少し悪いです。

- 点数計算や手札管理がうまくいかないバグが発生中

→このバグの解消を中心に制作にあたっています。

# 今後の追加要素

- 全てのバージョンでプレイ可能にする
  
- 運要素（ラウンド効果）を任意のタイミングで発動させる



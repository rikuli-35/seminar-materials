# 対戦型RPGのゲームバランス分析プロジェクト
ネットワーク分析の観点から、ゲームバランスの構成、改善について考察するプロジェクトです。

-解説資料はこちら：https://trusting-eagle-b15.notion.site/21b2a19a047380f58c16eb764cfff4d5

# ライブラリ・実行環境

-RStdio：https://posit.co/download/rstudio-desktop/

-実行環境：macOS 13+　Windows 10/11

# データセット

-初代のタイプ相性表：https://wiki.ポケモン.com/wiki/相性 

-上記の表から自作したcsvファイル：[type_1.csv](type_1.csv/) 

-初代のネットワーク：[type_network_1.png](type_network_1.png/)

-第2世代〜第5世代のタイプ相性表：https://www.nintendo.co.jp/ds/ipkj/basis/pdf/pokemonHGSS_typeTable.pdf 

-上記の表から自作したcsvファイル：[type_2_to_5.csv](type_2_to_5.csv/)

-第2世代〜第5世代のネットワーク：[type_network_2_to_5.png](type_network_2_to_5.png/)

-第6世代以降のタイプ相性表：https://www.pokemon.co.jp/ex/xy/battle/01.html 

-上記の表から自作したcsvファイル：[type_6_to_9.csv](type_6_to_9.csv/)

-第6世代以降のネットワーク：[type_network_6_to_9.png](type_network_6_to_9.png/)

# コード解説（チュートリアル）
-[type_network.R](type_network.R/)

# 結果
-初代の次数中心性：[type_degree_graph_1.png](type_degree_graph_1.png/)

-初代の媒介中心性・固有ベクトル中心性：[type_bet_vec_graph_1.png](type_bet_vec_graph_1.png/)

-第2世代〜第5世代の次数中心性：[type_degree_graph_2_to_5.png](type_degree_graph_2_to_5.png/)

-第2世代〜第5世代の媒介中心性・固有ベクトル中心性：[type_bet_vec_graph_2_to_5.png](type_bet_vec_graph_2_to_5.png/)

-第6世代〜の次数中心性：[type_degree_graph_6_to_9.png](type_degree_graph_6_to_9.png/)

-第6世代〜の媒介中心性・固有ベクトル中心性：[type_bet_vec_graph_6_to_9.png](type_bet_vec_graph_6_to_9.png/)






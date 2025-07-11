# 新しいポケモンのタイプ提案プロジェクト
ここでは、ポケモンの新しいタイプを考案するために、ネットワーク分析の観点から、各タイプの重要性を推測しています。

詳しい説明はこちら：https://trusting-eagle-b15.notion.site/21b2a19a047380f58c16eb764cfff4d5

# 構築したネットワーク
ポケモンのタイプ相性は「初代」、「第2世代〜第5世代」、「第6世代以降」で変化しています。<br>
そのため、3種類のネットワークを構築し、それぞれを比較することで、各タイプの重要性を推測しています。

-初代のタイプ相性表：https://wiki.ポケモン.com/wiki/相性 

-上記の表から自作したcsvファイル：[type_1.csv](type_1.csv/) 

-初代のネットワーク：[type_network_1.png](type_network_1.png/)

-第2世代〜第5世代のタイプ相性表：https://www.nintendo.co.jp/ds/ipkj/basis/pdf/pokemonHGSS_typeTable.pdf 

-上記の表から自作したcsvファイル：[type_2_to_5.csv](type_2_to_5.csv/)

-第2世代〜第5世代のネットワーク：[type_network_2_to_5.png](type_network_2_to_5.png/)

-第6世代以降のタイプ相性表：https://www.pokemon.co.jp/ex/xy/battle/01.html 

-上記の表から自作したcsvファイル：[type_6_to_9.csv](type_6_to_9.csv/)

-第6世代以降のネットワーク：[type_network_6_to_9.png](type_network_6_to_9.png/)

# コード
-[type_network.R](type_network.R/)

# グラフ
-初代の次数中心性：[type_degree_graph_1.png](type_degree_graph_1.png/)

-初代の媒介中心性・固有ベクトル中心性：[type_bet_vec_graph_1.png](type_bet_vec_graph_1.png/)

-第2世代〜第5世代の次数中心性：[type_degree_graph_2_to_5.png](type_degree_graph_2_to_5.png/)

-第2世代〜第5世代の媒介中心性・固有ベクトル中心性：[type_bet_vec_graph_2_to_5.png](type_bet_vec_graph_2_to_5.png/)

-第6世代〜の次数中心性：[type_degree_graph_6_to_9.png](type_degree_graph_6_to_9.png/)

-第6世代〜の媒介中心性・固有ベクトル中心性：[type_bet_vec_graph_6_to_9.png](type_bet_vec_graph_6_to_9.png/)






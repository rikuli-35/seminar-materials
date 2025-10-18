# 対戦型RPGのゲームバランス分析プロジェクト
ネットワーク分析の観点から、ゲームバランスの構成、改善について考察するプロジェクトです。<br>
まずは、解説資料を見ていただき、プロジェクトの概要を理解していただければ幸いです。

-解説資料はこちら：

-RStdio：https://posit.co/download/rstudio-desktop/

-実行環境：macOS 13+　Windows 10/11

# データセット

-初代のタイプ相性表：https://wiki.ポケモン.com/wiki/相性 

-上記の表から自作したcsvファイル：[type_analysis_1.csv](type_analysis_1.csv/) 

-初代のネットワーク：[type_analysis_network_1.pdf](type_analysis_network_1.pdf/)

-第2世代〜第5世代のタイプ相性表：https://www.nintendo.co.jp/ds/ipkj/basis/pdf/pokemonHGSS_typeTable.pdf 

-上記の表から自作したcsvファイル：[type_analysis_2_to_5.csv](type_analysis_2_to_5.csv/)

-第2世代〜第5世代のネットワーク：[type_analysis_network_2_to_5.pdf](type_analysis_network_2_to_5.pdf/)

-第6世代以降のタイプ相性表：https://www.pokemon.co.jp/ex/xy/battle/01.html 

-上記の表から自作したcsvファイル：[type_analysis_6_to_9.csv](type_analysis_6_to_9.csv/)

-第6世代以降のネットワーク：[type_analysis_network_6_to_9.pdf](type_analysis_network_6_to_9.pdf/)

# コード解説（チュートリアル）
※解説資料にも記載していますが、チュートリアルに沿ってコードを実行するためには、事前にcsvファイルをダウンロードする必要があります。

-チュートリアル：https://rikuli-35.github.io/seminar-materials/02_data_analysis/type_analytics_tutorial.html<img width="824" height="42" alt="image" src="https://github.com/user-attachments/assets/55d8753a-862d-451e-823a-8547526a14c9" />
-解説資料作成コード：[type_analysis_tutorial.html](type_analysis_tutorial.html/)

# 結果
-初代の次数中心性：[type_analysis_degree_graph_1.pdf](type_analysis_degree_graph_1.pdf/)

-初代の媒介中心性・固有ベクトル中心性：[type_analysis_bet_vec_graph_1.pdf](type_analysis_bet_vec_graph_1.pdf/)

-第2世代〜第5世代の次数中心性：[type_analysis_degree_graph_2_to_5.pdf](type_analysis_degree_graph_2_to_5.pdf/)

-第2世代〜第5世代の媒介中心性・固有ベクトル中心性：[type_analysis_bet_vec_graph_2_to_5.pdf](type_analysis_bet_vec_graph_2_to_5.pdf/)

-第6世代〜の次数中心性：[type_analysis_degree_graph_6_to_9.pdf](type_analysis_degree_graph_6_to_9.pdf/)

-第6世代〜の媒介中心性・固有ベクトル中心性：[type_analysis_bet_vec_graph_6_to_9.pdf](type_analysis_bet_vec_graph_6_to_9.pdf/)






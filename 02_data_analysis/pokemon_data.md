# ポケモンのデータ分析
Kaggleに掲載されている、「Pokemon with stats」のデータセットを使用してデータ分析(回帰分析・判別分析・主成分分析)を行なっています。<br>
使用したデータセット：https://www.kaggle.com/datasets/abcsds/pokemon<br>

-データセットについて<br>
このデータセットは、ポケットモンスターシリーズに登場するポケモン721匹（初代から第6世代まで）の名前、タイプ、種族値（HP、攻撃、防御、特殊、特防、素早さ）がまとめられているものです。<br>

-データセットで使われている変数<br>
X.：図鑑番号<br>
Name：ポケモンの名前<br>
Type 1：ポケモンのタイプ<br>
Type 2：ポケモンの複合タイプ<br>
Total：合計種族値<br>
HP：ポケモンのHP数値<br>
Attack：ポケモンの攻撃数値<br>
Defense：ポケモンの防御数値<br>
Sp. .Atk：ポケモンの特攻数値<br>
Sp. .Def：ポケモンの特防数値<br>
Speed：ポケモンの素早さ数値<br>
Generation：ポケモンの登場世代<br>
Legendary：伝説ポケモンならTrue、そうでないならFalse<br>

-変数に関する注意点<br>
Rでデータ分析を行う際には、カテゴリ変数をダミー変数に変換する必要があります。
つまり、ノーマルタイプ→1、ほのおタイプ→2といったように、文字列の変数を数値に置き換える必要があります。<br>
そのため、ここでは変数の規則をあらかじめ決めておきます。<br>

-変換が必要な変数<br>
Type 1、Type 2、Legendary、（Generation）

-Type1,2
"Normal"（ノーマルタイプ）→1 <br>
"Fire"（ほのおタイプ）→2 <br>
"Water"（みずタイプ）→3 <br>
"Electric"（でんきタイプ）→4 <br>
"Grass"（くさタイプ）→5 <br>
"Ice"（こおりタイプ）→6 <br>
"Fighting"（かくとうタイプ）→7 <br>
"Poison"（どくタイプ）→8 <br>
"Ground"（じめんタイプ）→9 <br>
"Flying"（ひこうタイプ）→10 <br>
"Psychic"（エスパータイプ）→11 <br>
"Bug"（むしタイプ）→12 <br>
"Rock"（いわタイプ）→13 <br>
"Ghost"（ゴーストタイプ）→14 <br>
"Dragon"（ドラゴンタイプ）→15 <br>
"Dark"（あくタイプ）→16 <br>
"Steel"（はがねタイプ）→17 <br>
"Fairy"（フェアリータイプ）→18 <br>
""(２つ目のタイプがない場合) →19 (コード内では、変数を書き換えて"None"表記にしています) <br>

-Legendary <br>
True・Falseはas.factorで２値変数に変換していますが、表記はTrue・Falseです。

-Generation <br>
1~6の数値で表現できるため、ダミー化する必要はありませんが、「各世代の平均」などを求める際にはダミー変数にする場合があります。

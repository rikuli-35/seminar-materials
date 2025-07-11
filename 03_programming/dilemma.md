# 囚人のジレンマゲーム（C言語）
C言語で囚人のジレンマゲームを自作しました。<br>
-コードはこちら：[dilemma.c](dilemma.c/)　<br>

単純な囚人のジレンマゲームを改良したラウンド制のゲームを自作しました。<br>
-コードはこちら：[dilemma2.c](dilemma2.c/) <br>

コンピュータに戦略を持たせた囚人のジレンマゲームを自作しました。<br>
-コードはこちら：[dilemma3.c](dilemma3.c/) 

# 囚人のジレンマとは？
囚人のジレンマはゲーム理論（複数のプレイヤーの行動や意思決定を分析する理論）の1つです。<br>
似たようなものとして、鹿狩りゲーム、チキンゲーム、男女ゲームなどがあります。<br>

・問題の背景<br>
まず、AとBの2人が共犯で、ある軽犯罪を犯して捕まったとします。そして、この2人はもっと重い罪を犯したのではないかと疑われています。<br>
2人の囚人はそれぞれ異なる取り調べ室で「自白」か「黙秘」を選択し、囚人はお互いにどちらを選択したのかは知ることができないとします。<br>
そして以下の利得表によって、2人の囚人の懲役年数が決定します。<br>

| 囚人A\囚人B| 自白 | 黙秘 |
| ------- | ------- | ------- |
| 自白 | (5,5) | (0,10) |
| 黙秘| (10,0) | (2,2) |

(a,b)=(囚人Aの懲役,囚人Bの懲役)

# なぜ「ジレンマ」なのか？
先ほどの表から、AとBのそれぞれの最適反応（相手がある戦略をとる上で、自分の利益を最大化する戦略をとること）を考えると、AとBは共に「自白」を選んだ方が自分のメリットが大きいです。しかしながら、全体的なメリットを考えるとAとBは協力して黙秘を選ぶ必要があります。<br>
つまり、AとBは「自分の利益」を優先するなら「自白」、「全体の利益」を優先するなら「黙秘」を選択する必要があります。よって、「自白」は裏切り行動、「黙秘」は協力行動と解釈され、戦略の選択にジレンマが存在すると知られています。

# プログラム内の処理について
コード内では、コンピュータ側を囚人A、プログラム実行者は囚人B、自白を0、黙秘を1として扱っています。
（dilemma.cとdilemma2.cはコンピュータ側が選択する戦略はランダムになっています。）<br>
・dilemma.cは囚人のジレンマを模倣した単純なプログラムです。<br>
・dilemma2.cは10ラウンドのゲーム式で、懲役年数の合計が高い方が負けというプログラムです。<br>
・dilemma3.cはコンピュータ側が戦略(最初の戦略はランダム、以降はプログラム実行者の戦略を後追いする)をもっているパターンのプログラムです。<br>

# 次に挑戦するプロジェクト
コンピュータに持たせる戦略は今回作成したもの以外には「ずっと自白を選択」、「ずっと黙秘を選択」、「最後のラウンドは必ず自白」、「一度でも裏切られたら以降ずっと自白を選択」などが挙げられます。様々な戦略のプログラムを作成し、複数回実行することでコンピュータ側がどのような戦略を取りやすいのかなどの分析ができるのではないかと考えています。また、様々な戦略を持つコンピュータにどのような戦略を取れば勝率が高いのかなどにも興味があります。<br>
他言語でのプロジェクトが終わり次第、こちらにも取り組もうと思っています。


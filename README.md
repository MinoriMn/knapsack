# ナップサック問題
- 使用言語: C++
- 品物データ(物品名,重量,価値): items.csv
- 出力ファイル: result.csv

(世代, 最大評価点と物品, 平均評価点と物品)

# 実行ブランチ
## 条件
- 物品データ:20種、ランダム生成
- 個体数:親4個体 + (生成)子個体24個体 = 計28個体 
- 親:エリート1個体 + ルーレット3個体 = 計4個体
- 交叉:一点交叉、遺伝子の中点で分割
- 突然変異:各遺伝子に5%。制限なし
- 世代:1000世代で終了
## 実行回数
10回
## 実行結果

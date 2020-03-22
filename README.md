# ナップサック問題
- 使用言語: C++
- 品物データ(物品名,重量,価値): items.csv
- 出力ファイル:
  - `ga_result_raw_record.csv` 各世代の個体群データとその評価値まとめ
  - `ga_result_uni_record.csv` 各世代の評価情報を元に算出したデータをまとめたもの
  - `ga_result_graph.pdf` `ga_result_uni_record.csv`をグラフ表示したもの
- 構成
  - `main` メイン処理、GAの具体的な設定などもここで行う
  - `learning` GA処理を担う。(learningという名前にすべきでは無かった…)
  - `matplotlib` グラフ描画処理。(pythonのmatplotを使う)
  - `n_item` 入力物品データを扱う。
  - `utility` その他関数。
  
# 実行方法
## 通常起動
1. `make`コマンドでコンパイル
2. `./knapsack`で実行
## 複数回実行
1. `make`コマンドでコンパイル
2. `bash auto_run.sh <実行回数(整数)> <全ての結果を保存するフォルダ名>`

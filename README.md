*This project has been created as part of the 42 curriculum by ksadayas.*

# 説明-Description

push_swap は 42 のアルゴリズム課題です。

この課題では、2つのスタック（a と b）と限られた操作のみを使用して、整数列を昇順に並び替えるプログラムを作成します。

単純にソートするだけではなく、できるだけ少ない操作回数で並び替えることが求められます。

---

# 導入-Instructions

初期状態では、

- stack a に全ての整数が格納されている
- stack b は空
- 最初の引数が stack a の先頭

となります。

最終的に、

- stack a が昇順
- stack b が空

になれば成功です。

---

# 使用可能な操作

| 操作 | 説明 |
|--------|--------|
| sa | stack a の先頭2要素を交換 |
| sb | stack b の先頭2要素を交換 |
| ss | sa と sb を同時実行 |
| pa | stack b の先頭を stack a の先頭に移動 |
| pb | stack a の先頭を stack b の先頭に移動 |
| ra | stack a の先頭を最後尾に送る |
| rb | stack b の先頭を最後尾に送る |
| rr | ra と rb を同時実行 |
| rra | stack a を逆回転 |
| rrb | stack b を逆回転 |
| rrr | rra と rrb を同時実行 |

---

# データ構造

このプロジェクトでは双方向連結リストを使用してスタックを管理しています。

```c
typedef struct s_node
{
	int				value;
	int				index;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;
```

各ノードは、

- value : 元の整数値
- index : radix sort 用の圧縮済み順位

を保持しています。

スタック構造体は以下です。

```c
typedef struct s_stack
{
	t_node	*head;
	t_node	*tail;
	int		size;
}	t_stack;
```

---

# アルゴリズム

この実装では **Binary Radix Sort（2進基数ソート）** を使用しています。

---

## なぜ Radix Sort を選んだのか

push_swap では、

- 比較ソートを実装する必要がない
- 実装が比較的簡単
- 100個や500個の入力でも安定した結果が出る

という利点があります。

---

## インデックス化

radix sort は負の整数を扱うのは難しいので、

そのため入力値をソート順位へ変換します。

例

```text
入力:
42 -3 100 7

昇順:
-3 7 42 100
```

順位を付けると

```text
42 -> 2
-3 -> 0
100 -> 3
7 -> 1
```

となります。

変換後

```text
2 0 3 1
```

を radix sort で処理します。

これだったら簡単ですね

---

## Radix Sort の流れ

各ビットを下位ビットから順番に見ます。

例えば

```text
2 0 3 1
```

なら

```text
10
00
11
01
```

として扱います。

各ビットについて

```text
ビットが0 → pb
ビットが1 → ra
```

を行います。

全要素を確認した後

```text
pa
```

を stack b が空になるまで繰り返します。

これを最大ビット数まで繰り返します。

---
長い説明(がちで長い)
---

## Radix Sort の具体例

ここでは 5 個の数字を使って、`ra` がどのような動作をしているのかを説明します。

初期状態

```text
A: 4 1 3 0 2
B:
```

各値を 2 進数で表すと

```text
4 = 100
1 = 001
3 = 011
0 = 000
2 = 010
```

---

### bit0（最下位ビット）を見る

```text
4 → 0
1 → 1
3 → 1
0 → 0
2 → 0
```

ルール

```text
bit = 0 → pb
bit = 1 → ra
```

---

### 4

```text
pb
```

```text
A: 1 3 0 2
B: 4
```

---

### 1

```text
ra
```

```text
A: 3 0 2 1
B: 4
```

ここで重要なのは、

```text
1
```

が消えたわけではなく、

```text
先頭 → 末尾
```

へ移動しただけということです。

---

### 3

```text
ra
```

```text
A: 0 2 1 3
B: 4
```

ここでも

```text
1 → 3
```

の順番は維持されています。

---

### 0

```text
pb
```

```text
A: 2 1 3
B: 0 4
```

---

### 2

```text
pb
```

```text
A: 1 3
B: 2 0 4
```

---

ここで bit0 が

```text
1
```

だった要素だけを見ると

```text
1 3
```

になっています。

元の順番も

```text
1 → 3
```

だったので、順序は変わっていません。

---

### A に残った要素

```text
A: 1 3
```

これは

```text
bit0 = 1
```

だったグループです。

---

### B に送られた要素

```text
B: 2 0 4
```

これは

```text
bit0 = 0
```

だったグループです。

---

### pa で戻す

```text
pa
pa
pa
```

を行うと

```text
A: 4 0 2 1 3
B:
```

となります。

---

## なぜ ra を使うのか

`ra` は

```text
先頭を末尾へ移動する
```

だけなので、

例えば

```text
1 3
```

に対して実行しても

```text
3 1
```

になるだけで、

同じグループ内の相対的な順序は維持されます。

この性質を

```text
Stable Sort（安定ソート）
```

と呼びます。

Radix Sort はこの安定性を利用して、

- bit0
- bit1
- bit2
- ...

を順番に処理することで最終的に完全な昇順を実現しています。

---

## ra のイメージ

```text
A: 5 2 8 1 7

ra

A: 2 8 1 7 5
```

つまり

```text
先頭ノードを取り外して末尾へ接続する
```

操作です。

要素をランダムな位置へ移動しているわけではありません。

そのため、同じビット値を持つ要素同士の順序を壊さずに処理できます。

つづき

```text
A: 4 0 2 1 3
B:
```

```text
4 = 100
0 = 000
2 = 010
1 = 001
3 = 011
```

２桁目確認してpb,ra,pa

```text
A: 2 3
B: 1 0 4
```

戻す

```text
A: 4 0 1 2 3
B: 
```

3桁目確認してpb,ra,pa

```text
4 = 100
0 = 000
1 = 001
2 = 010
3 = 011
```

```text
A: 4
B: 3 2 1 0
```

戻す

```text
A: 0 1 2 3 4
B: 
```

実際に並び替えに成功しました

---
長い説明終わり
---
---

# コンパイル方法

コンパイル

```bash
make
```

再コンパイル

```bash
make re
```

オブジェクト削除

```bash
make clean
```

実行ファイルも削除

```bash
make fclean
```

---

# 実行方法

例

```bash
./push_swap 2 1 3
```

出力

```text
sa
```

例

```bash
./push_swap 3 2 1
```

出力

```text
sa
rra
```

---

# エラー処理

以下の場合は

```text
Error
```

を標準エラー出力へ表示します。

- 数値以外が含まれる
- int範囲外
- 重複した値
- 空文字列

例

```bash
./push_swap 1 2 a
```

```text
Error
```

例

```bash
./push_swap 1 2 2
```

```text
Error
```

例

```bash
./push_swap 2147483648
```

```text
Error
```

---

# テスト方法

## checkerによる確認

```bash
ARG="4 67 3 87 23"

./push_swap $ARG | ./checker_linux $ARG
```

期待結果

```text
OK
```

---

## 操作回数の確認

```bash
ARG="4 67 3 87 23"

./push_swap $ARG | wc -l
```

出力例

```text
6
```

---

# ランダム100個テスト

引数生成

```bash
ARG="$(shuf -i 1-10000 -n 100 | tr '\n' ' ')"
```

回数確認

```bash
./push_swap $ARG | wc -l
```

checker確認

```bash
./push_swap $ARG | ./checker_linux $ARG
```

両方確認

```bash
./push_swap $ARG | tee ops.txt | ./checker_linux $ARG

wc -l ops.txt
```

---

# ランダム500個テスト

```bash
ARG="$(shuf -i 1-100000 -n 500 | tr '\n' ' ')"
```

回数

```bash
./push_swap $ARG | wc -l
```

checker

```bash
./push_swap $ARG | ./checker_linux $ARG
```

---

# 自動テスト

## 100回連続テスト

```bash
for i in {1..100}
do
	ARG="$(shuf -i 1-10000 -n 100 | tr '\n' ' ')"
	./push_swap $ARG | ./checker_linux $ARG
done
```

全て

```text
OK
```

になれば成功です。

---

## 平均操作回数

```bash
for i in {1..100}
do
	ARG="$(shuf -i 1-10000 -n 100 | tr '\n' ' ')"
	./push_swap $ARG | wc -l
done | awk '{sum += $1} END {print sum / NR}'
```

---

# ベンチマーク

課題で要求されている目安

| 個数 | 目標 |
|--------|--------|
| 100個 | 700回未満 |
| 500個 | 5500回未満 |

現在の radix sort 実装では一般的に

| 個数 | 回数 |
|--------|--------|
| 100個 | 約1000〜1100 |
| 500個 | 約6500〜7000 |

程度になります。

---

# デバッグ用コマンド

生成された引数確認

```bash
echo "$ARG"
```

操作保存

```bash
./push_swap $ARG > ops.txt
```

回数確認

```bash
wc -l ops.txt
```

checker実行

```bash
./checker_linux $ARG < ops.txt
```

---

# ディレクトリ構成

```text
.
├── Makefile
├── push_swap.h
├── main.c
├── parse_args.c
├── ft_split.c
├── create_new_node.c
├── swap.c
├── push.c
├── rotate.c
├── reverse_rotate.c
├── radix_sort.c
├── index.c
├── utils.c
└── free.c
```

---

# AI利用について

本プロジェクトでは AI を以下の用途で利用しました。

- 課題内容の理解整理
- radix sortの設計検討
- テストコマンド作成
- エッジケース確認

---

# 参考資料

- push_swap Subject
- Radix Sort
- Linked List
- Stack Data Structure
- Big-O Complexity


## コードの解説

## コードファイルと関数の説明

このプロジェクトでは、処理ごとにファイルを分割し、各関数を短く保つことで可読性と保守性を高めています。

---

## `push_swap.h`

プロジェクト全体で使用するヘッダーファイルです。

主な内容は以下です。

* 構造体の定義
* 必要な標準ライブラリの include
* 各関数のプロトタイプ宣言

### `t_node`

スタックの1つの要素を表す構造体です。

```c
typedef struct s_node
{
	int				value;
	int				index;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;
```

* `value` : 入力された元の整数値
* `index` : radix sort 用に変換した順位
* `next` : 次のノード
* `prev` : 前のノード

### `t_stack`

スタック全体を管理する構造体です。

```c
typedef struct s_stack
{
	t_node	*head;
	t_node	*tail;
	int		size;
}	t_stack;
```

* `head` : スタックの先頭
* `tail` : スタックの末尾
* `size` : スタック内の要素数

---

## `main.c`

プログラムの開始地点です。

### `main`

プログラム全体の流れを管理します。

主な処理は以下です。

1. 引数がない場合は何もせず終了
2. stack a と stack b を初期化
3. 引数を解析して stack a に格納
4. 重複チェック
5. インデックスを設定
6. ソート処理を実行
7. 確保したメモリを解放

---

## `parse_args.c`

コマンドライン引数を解析するファイルです。

### `parse_args`

`argv` から受け取った文字列を整数として読み取り、stack a に追加します。

対応している入力形式は以下です。

```bash
./push_swap 3 2 1
```

また、スペースを含む文字列にも対応します。

```bash
./push_swap "3 2 1"
```

この関数では、各文字列を `ft_split` で分割し、数値チェックを行った後、stack a に追加します。

### `is_all_digit`

文字列が整数として正しい形式かを確認します。

有効な例

```text
123
-42
+7
```

無効な例

```text
abc
12a
+
-
```

### `check_duplicates`

stack a の中に重複した値がないかを確認します。

同じ値が2つ以上ある場合は `Error` を表示して終了します。

---

## `ft_split.c`

文字列を指定した区切り文字で分割するためのファイルです。

### `ft_split`

文字列を分割して、文字列配列として返します。

例

```c
ft_split("3 2 1", ' ');
```

結果

```text
["3", "2", "1"]
```

### `ft_count_words`

分割後に必要になる単語数を数えます。

### `ft_copy_word`

文字列の一部分を新しく確保してコピーします。

### `ft_free_all`

途中で malloc に失敗した場合、すでに確保したメモリを解放します。

---

## `create_new_node.c`

スタックのノード作成と追加を行うファイルです。

### `create_new_node`

新しいノードを作成します。

初期値として、

* `value` に入力値
* `index` に `-1`
* `next` に `NULL`
* `prev` に `NULL`

を設定します。

### `add_back`

stack の末尾に新しいノードを追加します。

入力された数字を stack a に順番通り入れるために使用します。

---

## `index.c`

radix sort 用の index を設定するファイルです。

### `set_index`

各ノードの `value` を比較し、小さい順に `index` を設定します。

例

```text
value:  42 -3 100 7
index:   2  0   3 1
```

元の値を直接 radix sort するのではなく、順位に変換してからソートします。

これにより、負の数や大きな数も安全に扱えます。

---

## `sort.c` または `sort_small.c`

少ない個数のソートを行うファイルです。

### `is_sorted`

stack a がすでに昇順になっているかを確認します。

昇順ならソート処理を行わず終了します。

### `sort_two`

要素が2個の場合のソートを行います。

必要であれば `sa` を実行します。

### `sort_three`

要素が3個の場合のソートを行います。

`sa`、`ra`、`rra` を組み合わせて、少ない操作で並び替えます。

### `sort_stack`

要素数に応じてソート方法を選択します。

* 2個なら `sort_two`
* 3個なら `sort_three`
* それ以上なら `radix_sort`

を呼び出します。

---

## `radix_sort.c`

メインのソートアルゴリズムを実装するファイルです。

### `radix_sort`

Binary Radix Sort を使って stack a を昇順に並び替えます。

処理の流れは以下です。

1. 最大 index に必要なビット数を求める
2. 下位ビットから順番に確認する
3. bit が `0` なら `pb`
4. bit が `1` なら `ra`
5. stack b に移した要素を `pa` で戻す
6. 全ビット分繰り返す

### `get_max_bits`

最大 index を2進数で表すために必要なビット数を求めます。

例

```text
最大index = 4
2進数 = 100
必要bit数 = 3
```

---

## `swap.c`

swap 系の操作を実装するファイルです。

### `swap`

指定された stack の先頭2要素を交換します。

この関数は内部処理用で、命令名は出力しません。

### `sa`

stack a の先頭2要素を交換し、`sa` を出力します。

### `sb`

stack b の先頭2要素を交換し、`sb` を出力します。

### `ss`

stack a と stack b の両方で swap を行い、`ss` を出力します。

---

## `push.c`

push 系の操作を実装するファイルです。

### `push`

src の先頭要素を dest の先頭へ移動します。

この関数は内部処理用で、命令名は出力しません。

### `pa`

stack b の先頭要素を stack a に移動し、`pa` を出力します。

### `pb`

stack a の先頭要素を stack b に移動し、`pb` を出力します。

---

## `rotate.c`

rotate 系の操作を実装するファイルです。

### `rotate`

stack の先頭要素を末尾に移動します。

例

```text
A: 5 2 8 1 7

ra

A: 2 8 1 7 5
```

この関数は内部処理用で、命令名は出力しません。

### `ra`

stack a を回転させ、`ra` を出力します。

### `rb`

stack b を回転させ、`rb` を出力します。

### `rr`

stack a と stack b の両方を回転させ、`rr` を出力します。

---

## `reverse_rotate.c`

reverse rotate 系の操作を実装するファイルです。

### `reverse_rotate`

stack の末尾要素を先頭に移動します。

例

```text
A: 5 2 8 1 7

rra

A: 7 5 2 8 1
```

この関数は内部処理用で、命令名は出力しません。

### `rra`

stack a を逆回転させ、`rra` を出力します。

### `rrb`

stack b を逆回転させ、`rrb` を出力します。

### `rrr`

stack a と stack b の両方を逆回転させ、`rrr` を出力します。

---

## `utils.c`

補助関数をまとめたファイルです。

### `ft_strlen`

文字列の長さを数えます。

### `ft_atol`

文字列を `long` 型の数値に変換します。

`int` の範囲外かどうかを確認するために使用します。

### `error_exit`

標準エラー出力に

```text
Error
```

を表示してプログラムを終了します。

---

## `free.c`

メモリ解放を行うファイルです。

### `free_stack`

stack 内の全ノードを解放します。

### `free_matrix`

`ft_split` で作成された文字列配列を解放します。

---

## `Makefile`

コンパイルを管理するファイルです。

主なルールは以下です。

### `make`

`push_swap` を作成します。

### `make clean`

オブジェクトファイルを削除します。

### `make fclean`

オブジェクトファイルと実行ファイルを削除します。

### `make re`

一度すべて削除してから再コンパイルします。

---

## 全体の処理の流れ

```text
1. main.c
   ↓
2. parse_args.c で引数を解析
   ↓
3. create_new_node.c で stack a に値を追加
   ↓
4. check_duplicates で重複確認
   ↓
5. index.c で値を index に変換
   ↓
6. sort_stack でソート方法を選択
   ↓
7. radix_sort.c でソート
   ↓
8. 操作関数が命令を出力
   ↓
9. free.c でメモリ解放
```

---

## まとめ

この実装では、入力値をそのまま比較して並び替えるのではなく、一度 index に変換してから radix sort を行っています。

そのため、

* 負の数
* 大きな数
* ランダムな順番の数

にも対応できます。

また、操作関数を `swap`、`push`、`rotate`、`reverse_rotate` に分けることで、push_swap のルールに沿った処理を分かりやすく管理しています。

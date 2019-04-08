# ソケット プログラミング

## 必要環境
* クライアント
** cloud shell でもローカルマシンでもよい
* サーバー
** Linux でも Windows でも可。どうせbashしか動かさないのでlinuxのが楽かも。
** NSGで必要なポートを空けておく

## 使い方
1. クライアントに client_main.c をコピーし、コンパイルする。
2. サーバーに server_main.c をコピーし、コンパイルする。
3. サーバー側で、下記コマンドを実行

  `a.out <port番号>`
4. クライアント側で、下記コマンドを実行

  `a.out <server ip> <Port番号>`
5. なんか適当に文字列を打ち込む




### 参考
https://qiita.com/tajima_taso/items/13b5662aca1f68fc6e8e#%E3%82%AF%E3%83%A9%E3%82%A4%E3%82%A2%E3%83%B3%E3%83%88%E3%82%BD%E3%83%95%E3%83%88%E3%81%AE%E3%82%BD%E3%83%BC%E3%82%B9%E3%82%B3%E3%83%BC%E3%83%89

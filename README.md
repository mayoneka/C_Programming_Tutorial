# README



## Azure クラウドシェルで Github を利用する方法



### Azure クラウドシェル で、ssh 鍵を生成する



1. 下記コマンドを実行

   ```bash
   ssh-keygen -t rsa -b 4096 -C "<githubに登録したメールアドレス>
   ```

1. 鍵の生成場所を問われるが、デフォルトで特に問題なし

   Default : ~/.ssh

2. 下記コマンドの出力結果をコピー

   ```
   cat ~/.ssh/id_rsa.pub
   ```

### Github に、ssh の公開鍵を登録する

![1551959214674](https://github.com/mayoneka/CSS_Academy_C/images/1.jpg)





### Azure クラウドシェル上に Clone する

1. clone の前に、git コマンドの config を追加する

```
  git config --global user.email "you@example.com"
  git config --global user.name "Your Name"
```

1. Clone 実行

```
git clone 
```






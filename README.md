<h3>公開鍵の作成</h3>

リモートリポジトリと色々するためにはgithubアカウントをローカルマシンの秘密鍵と紐づける必要があります
まずはローカルマシンで秘密鍵と公開鍵のペアを作成しましょう
ssh鍵は ~/.ssh/ に作成するのがお行儀が良いです。
/home/lab/user/に作っておけばssh先の複数のホストで同じ鍵で接続できます。
ssh鍵の作成前に既存の鍵の存在を確認しましょう
```
$ ls -al ~/.ssh
```
出力に何も表示されなければ鍵がない状態なので、作成します。
```
$ cd ~/.ssh
$ ssh-keygen -t ed25519 -C "your_email@example.com"
```
メールアドレスのところは自分のメールアドレスを書きましょう
```
Enter file in which to save the key (/Users/you/.ssh/id_rsa):
```
SSH鍵の保存先を聞かれるので特に気にしなければそのままEnterを押下します
```
Enter passphrase (empty for no passphrase):
```
2回パスフレーズの入力を求められるので任意のパスフレーズを設定します

これで秘密鍵と公開鍵のペアが作成されました
```
$ ls ~/.ssh
config          id_rsa      id_rsa.pub  known_hosts
```

___

<h3>githubアカウントとリンク</h3>

githubアカウントを作成しましょう。
https://github.com
リモートリポジトリのクローンやプッシュ、ソースコードの公開などができるようになります。

公開鍵をgithubに登録する必要があるので
アカウント → Setting → SSH and GPG keys → New SSH keyと移動します
```
$ pbcopy < ~/.ssh/id_rsa.pub
```
ターミナルから公開鍵をクリップボードにコピーして、サイトのKeyの下の入力エリアに貼り付けます
任意のタイトルを入力してAdd SSH keyを押下して登録完了です

ターミナルにて以下のコマンドを打ち、接続できることを確認します
```
$ ssh -T git@github.com
Hi user! You've successfully authenticated, but GitHub does not provide shell access.
```

___

<h3>リポジトリ操作</h3>

誰かがgit hubに公開しているプロジェクトをローカルに持ってくる場合は`git clone`を使用します
`git clone`の後ろはリポジトリを開いて緑色の Code ボタンを押下し、SSHのタブを開くことでコピーできます
まずは`git clone`をしてみましょう
```
$ git clone git@github.com:2clchino/pforgit.git
```

次に、テキトーなプロジェクトを作成して自身の git hub にpushするまでの流れをやります
gitの根幹ともいえる `git add` > `git commit` までをやってみましょう
```
$ mkdir git_sample
$ cd git_sample
$ touch sample.c
$ git init
$ git status
$ git add .
$ git commit -m "first commit"
```
`git init` はローカルのプロジェクトフォルダをgit 追従させるコマンドで、リポジトリを作成した最初の1回のみ行います
`git status` は現在の状態を確認するコマンドです。先ほど作成した sample.c が Untracked filesとして赤文字になっていることを確認しましょう

`git add` は変更をステージングするコマンドで、`git add sample.c` のようにファイル名を指定して特定のファイルだけステージングさせたり、ワイルドカードで指定したりもできます
しかし、`.gitignore` を書くことで特定のファイルを git追従 から外すことができるため、`.gitignore`を書いておいて `git add .`で一括追加するのが楽です
`git add .` では `git status` コマンドで赤文字で表示されているファイルがすべて追加されます
	先ほどcloneしたリポジトリの中に `.gitignore` が入っているので見てみましょう
		実行ファイル(*.out)や容量が大きくなりがちなデータ類などが ignore されています
再度`git status`コマンドを打って`sample.c`が緑文字になり new file としてgit追従されたことを確認しましょう

`git commit` は作業内容を保存するコマンドです。そのcommitで自分がどんな機能を追加したかが一目でわかるように -mオプションでコメントをつけましょう
間違ったときは↓
```
$ git commit --amend -m "サンプルソースを追加"
```
`git commit` したファイルやその変更は、そのリポジトリを見ることのできるすべての人間が見ることができます
リポジトリの公開予定がある場合は誤って機密情報をcommitしないよう、細心の注意を払いましょう

ここまでで、ローカルでの準備は完了です。github上にpushするにはまず、リポジトリを作成する必要があります
アカウント > Profile > Repositories > New と進み、任意の Repository name を入れて作成しましょう
作成するとgithubがサンプルコマンドを教えてくれるので、これを実行します
基本的には以下の2コマンドです
```
$ git remote add origin git@github.com:2clchino/pforgit.git
$ git push origin master
```

___

<h3>過去に戻る</h3>

バージョン管理の神髄ですが、gitでは過去のcommitに戻ることができます

まずは`git log` コマンドで過去のコミットメッセージとコミットID、コミットしたユーザと日付を見て、戻りたいcommitを探しましょう
```
$ git log
commit a036755f818375c9f2853b8492e823a947612fd6 (HEAD -> master, origin/master)
Author: mano <mano.24.rites@gmail.com>
Date:   Wed Mar 23 22:22:03 2022 +0900

    first commit
```
基本的に今後、ここで表示される激長のコミットIDでcommitを指定しますが最初の4文字以降は省略できます

`git diff` コマンドで差分を確認することもできます
```
$ git diff cfb55 2c6b12        // コミット間の差分はコミットIDで指定
$ git diff origin/master..HEAD // 
```

commitの差分に関してはgithubのサイト上で確認することもできます

`git checkout` コマンドで一時的に過去のcommitに戻ることができます
`git checkout ブランチ名`とすることで過去の状態から現在に戻ってこれます
過去のcommitで別の作業を行いたいときには後述のブランチ操作を行います
```
$ git checkout a0367
$ git checkout master
```

___

<h3>ブランチ操作</h3>

過去のコミットの内容から作業を行う際には`git branch` コマンドで新規でブランチを切って、`git checkout` コマンドでブランチに切り替えます
他のユーザと同じリポジトリで作業する際に活躍するほか、
Subversionの説明にも書かれていますが、すぐに切り替え可能な状態で作業内容を残しておきたい場合やなどにもブランチは使用できます
```
$ git branch ブランチ名
$ git checkout ブランチ名
```

ブランチの一覧は以下のコマンドで確認することができます
```
$ git branch                       // ローカルブランチ一覧
$ git branch -a                    // リモートブランチも含めた一覧
```

`git checkout` コマンドは-bオプションを使用することでリモートブランチをローカルに持ってきて切り替えることができます
```
$ git checkout -b [ローカルブランチ名] [リモートブランチ名]
```

ブランチの切り替えは基本的に作業中のファイルをcommitしてから行うようになっており、怒られます
```
$ git checkout check_api
error: Your local changes to the following files would be overwritten by checkout:
        projects/web_app/api/main.py
Please commit your changes or stash them before you switch branches.
Aborting
```

ローカルで大した作業をしておらず、変更を破棄してでもブランチを切り替えたい場合には `git checkout .` で変更を破棄します。
`git stash` コマンドでstashに作業内容を保存してからブランチを切り替えることで、変更を一時的に保存してブランチを切り替えることもできます
保存した変更を再度反映させるには`git stash apply`を使用します。
```
$ git stash -u
Saved working directory and index state WIP on master: cfb5555 python apiを整理
 // ブランチ切り替え
$ git stash list

stash@{0}: WIP on master: cfb5555 first commit
$ git stash apply stash@{0}
```

ブランチの枝分かれはマージ先のブランチに切り替えて`git merge` コマンドを使用することで、結合することができます。
```
$ git checkout master
$ git merge develop
```
この際マージ先ブランチでも作業をしていて同じファイルの同じ行を編集していた場合にはConflictが起こります。
どちらかの変更を優先するかを選択するか、どちらの変更も取り込みたい場合には`git diff` で差分を確認してコンフリクトしているファイルを手動で修正します(たまにgitがよしなにやってくれることもあります)

___

<h3>リモートの変更取り込み</h3>

リモートの変更は`git fetch` コマンドで確認することができ、`git pull` コマンドでローカルに変更を反映することができます。
```
$ git fetch
$ git pull origin master
```
公開されているリポジトリからクローンして作業するなかで、アップデートなどがあった際に使うことになると思います
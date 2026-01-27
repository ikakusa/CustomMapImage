# このツールについて
このツールはマップに任意の画像を設定できるツールです

<img width="1920" height="1080" alt="image" src="https://github.com/user-attachments/assets/6f76f898-14b2-4801-b6d9-6be0cc843615" />
 
 
# 使い方
まず[リリースページ](https://github.com/ikakusa/CustomMapImage/releases/latest)からCustomMap.dllをダウンロードします

<img width="911" height="394" alt="image" src="https://github.com/user-attachments/assets/a0698fbc-3ae4-4e97-9204-2553ed3ccad9" />
 
ダウンロードが完了したら [FateInjector](https://github.com/fligger/FateInjector) などのインジェクターを使用してマイクラ上にdllをインジェクトしてください
 
インジェクトが完了したらチャットを開き次のようなコマンドを使用します
 
```
.set_map <マップのサイズ(128)> <画像ファイルのパス>
```
<img width="772" height="74" alt="image" src="https://github.com/user-attachments/assets/014b37bc-157a-418d-bd02-a3e735cc0d2d" />
 
**※注意 画像のパスに"を含めるとNot Foundエラーが出ます**

 正しく画像が設定されると下の画像のようなメッセージが表示されます
 
<img width="389" height="170" alt="image" src="https://github.com/user-attachments/assets/fe804368-8d6c-4ffd-899e-8a048d11d2e6" />

画像の設定が完了したら 空の地図を使用して地図を作成し 手に持ちます

しばらく待つと下の画像のようなメッセージが表示されます 表示されたら成功です

<img width="370" height="123" alt="image" src="https://github.com/user-attachments/assets/a44780ef-5efd-481f-bd7e-ada7c2420488" />

手に持っている状態ではただの地図ですが 額縁などに飾ると正しく設定した画像に切り替わります

# 問題が起きた場合
<details>
<summary><h2>Q. ワールドに入りなおしたり時間経過で地図が元の地形の表示に戻ってしまった</h2></summary>

**A. 座標１０万など普段はロードしない距離で地図を作成して画像を設定することで対処できます**
</details>

<details>
<summary><h2>Q. 右下にメッセージが表示されない</h2></summary>

**A. メッセージが表示されない場合は 下に書いてあるフォルダのパスの中にある`logs.txt`にメッセージが書き込まれます**

```
%APPDATA%\Local\Packages\Microsoft.MinecraftUWP_8wekyb3d8bbwe\RoamingState
```
</details>

バグ報告などはIssueにお願いします

# 参考
[Shock95 bdsx-image-maps](https://github.com/Shock95/bdsx-image-maps)

## 禁止事項 ⚠️
以下の行為は **明確に禁止** します。

- ソースコードの全てまたは一部を **自分の成果物として使用・公開する行為**
- 許可のない **再配布・転載は禁止**

> ※「参考にする」と「コピーして使う」は別物です。
> 
> 第三者にこのツールを紹介する場合は必ずgithubのURLを使用する事
>
> このツールを使用してマップを作る場合はクレジット欄にこのツールのurlなどを掲載してください
---

## ライセンス
This project is **source-available but NOT open source**.

ソースコードの無許可での転載は禁止されています。  
詳細は [LICENSE](./LICENSE) を参照してください。

---

## 免責事項
本ツールを使用したことによって生じたいかなる損害についても、
作者は一切の責任を負いません。

---

# try-direct2d

![image](https://user-images.githubusercontent.com/5266152/35228246-99cd2ba6-ffd3-11e7-9083-332dddd7dff5.png)

direct2dを使ったゲームの習作です。  
カーソルについてくる四角いプレイヤーを壁にぶつからないようにゴールまで導きます。  
四角の中の黒い円が当たり判定で、ここが緑の円に触れると失敗で再スタートとなります。  
ピンクの円がゴールです。  
ステージの編集も可能です。

動画=> https://tanishi109.tumblr.com/post/170821763408/%E3%83%98%E3%83%93%E3%81%8C%E5%A3%81%E3%81%AB%E5%BD%93%E3%81%9F%E3%82%89%E3%81%AA%E3%81%84%E3%82%88%E3%81%86%E3%81%AB%E9%80%B2%E3%82%80%E3%82%B2%E3%83%BC%E3%83%A0


# 操作

## ゲーム画面

![image](https://user-images.githubusercontent.com/5266152/35228246-99cd2ba6-ffd3-11e7-9083-332dddd7dff5.png)

- マウスカーソル: プレイヤーの移動
- クリック(左): マウスカーソルによるプレイヤーの操作を開始(カーソルがwindow内に固定されます)
- エスケープキー: メニューの表示。マウスカーソルによるプレイヤーの操作を停止

## メニュー画面

![image](https://user-images.githubusercontent.com/5266152/36132956-ae173e3a-10bd-11e8-9c93-a1ca29069c0c.png)

- 上下キー: 項目を選択
- エンターキー: 確定

## キャンバス画面

![image](https://user-images.githubusercontent.com/5266152/35228249-9a23c7ea-ffd3-11e7-81d0-168d3d7786a5.png)

- クリック(左): 壁(緑の円)を置く
- 右クリック: 床(白いエリア)を置く
- スペースキーを押しながらドラッグ: キャンバスの中心を移動
- エスケープキー: メニューの表示。

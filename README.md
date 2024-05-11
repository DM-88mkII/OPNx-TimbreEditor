# OPNx-TimbreEditor
YAMAHA の FM音源チップ OPN系用の音色エディターです。

実行ファイルのダウンロードは[こちら](https://github.com/DM-88mkII/OPNx-TimbreEditor/blob/main/OPNx-TimbreEditor/x64/Release/OPNx-TimbreEditor.exe)  

<br>

# 特徴
* キーボード操作志向で、素早いエディットが可能
* 効果音モードに対応
* FNumberを活用したオクターブ拡張
  * o-1c ～ o9g+ まで、幅広い音域で発音可能
  * 高マルチプルな音色も、適正音域で発音可能
* 強制ダンプ機能
  * 音色のプレビューで、CL(カレントレベル)が無音の状態から発音
  * 音色のアタック部の作り込みに便利


<br>

# 操作方法
|キー|効果|
|:-:|:-:|
|↑,↓,←,→|パラメータ項目の移動|
|PageUp,PageDown|パラメータの値を1ずつ上下|
|Shift+(PageUp,PageDown)|パラメータの値を10ずつ上下|
|'-',0,1,2,3,4,5,6,7,8,9,Space,BackSpace,Enter|パラメータの値を入力|
|ESC|パラメータの値入力をキャンセル|
|Home,End|プレビューのオクターブを1ずつ上下|
|z,s,x,d,c,v,g,b,h,n,j,m,','|音色のプレビュー|
|Ctrl+(←,→)|レイヤータブの移動|

<br>

# 音色
## コントロール部
|パラメータ|効果|
|:-:|:-:|
|EN|発音の有効/無効|
|FDE|強制ダンプの有効/無効|
|ALG|アルゴリズム|
|FB|フィードバック|
|NUM|未実装|
|VOL|未実装|
|SE|効果音モードの有効/無効|
|KT|キートランスポーズ|
|FDT|FNumberデチューン|

## オペレータ部
|パラメータ|効果|
|:-:|:-:|
|EN|発音の有効/無効|
|FDE|強制ダンプの有効/無効|
|AR|アタックレート|
|DR|ディケイレート|
|SR|サスティンレート|
|RR|リリースレート|
|SL|サスティンレベル|
|TL|トータルレベル|
|KS|キースケール|
|MT|マルチプル|
|DT|デチューン|
|SSG|SSG-Envelope|
|FIX（※）|固定周波数モードの有効/無効|
|KT（※）|FIXが無効な場合、プレビュー音階との相対音階<br>FIXが有効な場合、o-1c からの絶対音階|
|FDT（※）|FNumberデチューン|

（※）効果音モードが有効な場合に機能します。

# OPNx-TimbreEditor
YAMAHA の FM音源チップ OPN系用の音色エディターです。

実行ファイルのダウンロードは[こちら](https://github.com/DM-88mkII/OPNx-TimbreEditor/blob/main/OPNx-TimbreEditor/x64/Release/OPNx-TimbreEditor.exe)  
実行ファイルが起動しない場合は、[最新の Microsoft Visual C++ 再頒布可能パッケージ バージョン](https://learn.microsoft.com/ja-jp/cpp/windows/latest-supported-vc-redist?view=msvc-170#latest-microsoft-visual-c-redistributable-version)をインストールしてみて下さい。  
また、セキュリティソフトによって除外されていないか、確認してみて下さい。

<br>

# 特徴
* キーボード操作志向で、素早いエディットが可能
* レイヤーに対応
  * 複数の音色を同時にプレビュー可能
* 効果音モードに対応
  * OPM(YM2151)のDT2に似せた音作りが可能
  * マルチプルを超える範囲と精度で、倍音を生成可能
* FNumberを活用したオクターブ拡張
  * o-1c ～ o9g+ まで、幅広い音域で発音可能
  * 高マルチプルな音色も、適正音域で発音可能
* 強制ダンプ機能
  * 音色のプレビューで、CL(カレントレベル)を無音の状態から発音
  * 音色のアタック部の作り込みに便利
* 拡張コピーに対応（以下の形式に対応）
  * MUCOM
  * PMD（OPN型）
  * PMD（OPM型）
  * FMP
  * FMP（A形式）
  * FMP7（F形式）
  * FMP7（FA形式）
  * FMP7（FC形式）
  * mml2vgm（F形式）
  * mml2vgm（N形式）
  * mml2vgm（M形式）
  * mucomDotNET
  * MAmidiMemo（mopn形式）
  * MAmidiMemo（mopm形式）
  * Z-MUSIC（v形式）
  * Z-MUSIC（@形式）
  * NAGDRV
  * NRTDRV（MODE5）
  * mmldrv
  * mmlgui
  * MUAP98
  * V3MML（OPN）
  * V3MML（OPNA）
  * V3MML（OPM）
  * N88BASIC
* ペーストは、上記全ての形式を自動判別してインポート

<br>

# 操作方法
|キー|効果|
|:-:|:-:|
|↑,↓,←,→|パラメータ項目の移動|
|PageUp,PageDown|パラメータの値を1ずつ上下|
|Shift + (PageUp,PageDown)|パラメータの値を4ずつ上下|
|'-',0,1,2,3,4,5,6,7,8,9,Space,BackSpace|パラメータの編集|
|Enter|パラメータの編集/決定|
|Ctrl + z|パラメータのアンドゥ/リドゥ|
|Ctrl + r|オペレータのローテート（※）|
|ESC|パラメータ編集/オペレータローテートのキャンセル|
|Ctrl + (Insert,Delete)|レイヤータブの追加/削除|
|Ctrl + (←,→)|レイヤータブの移動|
|z,s,x,d,c,v,g,b,h,n,j,m,','|現レイヤーの音色をプレビュー|
|Shift + (z,s,x,d,c,v,g,b,h,n,j,m,',')|全レイヤーの音色をプレビュー|
|Home,End|プレビューのオクターブを1ずつ上下|
|Insert,Delete|プレビューのボリュームを0.1ずつ上下|
|Ctrl + (c,v)|通常コピー（OPNx形式の音色データ）|
|Ctrl + Shift + (c,v)|拡張コピー（Setting形式の音色データ）|
|Ctrl + (o,s)|音色のロード/セーブ|

（※）一回目で移動元オペレータの選択、二回目で移動先オペレータの選択

<br>

# 音色
## コントロール部
|パラメータ|効果|
|:-:|:-:|
|EN|発音の有効/無効|
|FDE|強制ダンプの有効/無効|
|ALG|アルゴリズム|
|FB|フィードバック|
|NUM|外部ツール連携の為の音色番号|
|KML（※）|キーマップ下限|
|KMH（※）|キーマップ上限|
|SE|効果音モードの有効/無効|
|KT|キートランスポーズ|
|FDT|FNumberデチューン|

（※）プレビュー時、ノートナンバーがキーマップ範囲内であれば発音します。

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

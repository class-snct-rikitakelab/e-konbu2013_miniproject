SHITAKE PROJECT はＥＴロボコンにおける開発手法、要素技術、開発対象の理解を目的に実施された。
ＥＴロボコン２０１２において配布されたサンプルコースをできるだけ早く３週するプロダクトを開発対象とした。



成果物の概要
ＬＥＧＯＭＩＮＤＳＴＯＲＭで作られたロボットがサンプルコースを１周走り切れる。
自己位置推定機能により、走行区間を認識可能。
マーカーを通過する際コースアウトしないように、輝度値に平滑化をかけ、急峻な変化をカットしている。



デプロイ方法
/SHITAKE/templete/ においてmake all を実行
LEGOMINDSTORM にＵＳＢケーブルを接続し、./rxeflash.sh プログラムを転送する。

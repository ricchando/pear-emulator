pear-emulator
=============

自作CPU用エミュレータもどき

配布条件についてははLICENSEを参照すること

これは何?
--------
参考: https://gist.github.com/ricchando/92c2ec8581921642c097c529566d8f24


使い方
-----
クローンしてmakeで実行ファイルpearができる。
実行するとプログラムを実行後のレジスタとメモリの0x000-0x0cfをダンプする。
main関数で場所を指定したので、そこをいじり、そのつどmakeして結果を観察することを
とりあえずの使い方とする。

不具合・問題点など
----------------

現在main関数を直接いじる以外のプログラムロード手段がない。
- エミュレータとして致命的。最優先に解決するべき問題。

chs命令未実装
- エミュレータとしての品質確保が先

useropの10番以降未実装
- バグ潰しと並行して実装予定

そのほか多数の不具合が予想される

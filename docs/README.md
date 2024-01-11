# 式の計算(計算式評価)DLL

Windows x86, x64 用の 式の計算(計算式評価)DLL です。

四則演算・冪乗・括弧・組込関数(27種)を含む計算式の文字列を渡して、計算結果を double(倍精度浮動小数点)値で受け取れます。

自由に使える x64 (64ビット)用の DLL が無いようなので 
[Boost Spirit X3](https://www.boost.org/doc/libs/1_84_0/libs/spirit/doc/x3/html/index.html) 
を利用して作成しました。

C++, C, C#, VB.NET のサンプルを添付しています。

C# と VB.NET のサンプルでは、プラットホームに AnyCPU を指定してコンパイルし、
実行時に x86/x64 を判定して呼び出す DLL を切り分けるようにしています。

Arm にはまだ対応していません。

* [組込関数](builtin_functions.html)

## C#サンプルの出力

    2*2+2/2 = 5
    1/3 = 0.333333333333333
    1/3-0.3333333333333 = 3.33066907387547E-14
    1/0 = ∞
    (-1)/0 = -∞
    0/0 = NaN
    ERROR: 0/0+ : 構文解析エラー: +
    ERROR: 0/0+Hoge : 構文解析エラー: +Hoge
    2**3**4 = 2.41785163922926E+24
    2**(3**4) = 2.41785163922926E+24
    (2**3)**4 = 4096
    2^(1/2) = 1.4142135623731
    -2^(1/2) = -1.4142135623731
    -2^-(1/2) = -0.707106781186548
    (-2)^-(1/2) = NaN
    (2^(1/12))^7 = 1.49830707687668
    gamma(0.5)**2 = 3.14159265358979
    exp(-1/0) = 0
    round(exp(gammaln(0.5)*2),2) = 3.14

## 動作環境

Windows 10 以降 (x86, x64) 日本語版

## ライセンス

ソースコードは [Boost Software License, Version 1.0](https://www.boost.org/LICENSE_1_0.txt) に従って公開しています。

バイナリの配布は自由です。

## バイナリ リリース

C++, C, C#, VB.NET のサンプル コード、ビルド済みの DLL、インポート ライブラリを含むバイナリ リリースが
https://github.com/neige68/shiki-no-keisan-dll/releases にあります。
ソースからビルドしたい場合以外はこちらを使用してください。

## ソースコードの所在

ソースコードは https://github.com/neige68/shiki-no-keisan-dll/ にあります。

## 今後の予定

* Ver.1 にする

* 変数対応

* Arm 対応(実機が入手できたら)

## 連絡先

* [github issues](https://github.com/neige68/shiki-no-keisan-dll/issues)

* mail: shiki-no-keisan-dll@neige@ の2つめの@を .nu で置換してください

## 検索用ワード

    数式評価 数式変換 数式計算 数式の文字列を変換 ダイナミック リンク ライブラリ x64対応 64ビット対応 64ビットOS対応 商利用可能
    Evaluate Math Expression Basic CSharp Dynamic Link Library x64 Supported 64bit Operating System Supported
    Commercial use available
# 式の計算(計算式評価)DLL

Windows x86, x64 用の 式の計算(計算式評価)DLL です。

四則演算・冪乗・括弧・組込関数(27種)を含む計算式の文字列を渡して、計算結果を double(倍精度浮動小数点)値で受け取れます。

アルファベットで始まり、アルファベットと数字からなる変数も使用できます。
イコール(=)で代入し、セミコロン(;)またはコロン(,)で区切って複数の式が指定でき、最後の式の値が返されます。

漢字、ひらがな、カタカナもアルファベットに含まれます。

自由に使える x64 (64ビット)用の DLL が無いようなので 
[Boost Spirit X3](https://www.boost.org/doc/libs/1_84_0/libs/spirit/doc/x3/html/index.html) 
を利用して作成しました。

[C++](https://github.com/neige68/shiki-no-keisan-dll/blob/main/sample/vcpp/eval.cpp), 
[C](https://github.com/neige68/shiki-no-keisan-dll/blob/main/sample/vc/sample.c), 
[C#](https://github.com/neige68/shiki-no-keisan-dll/blob/main/sample/cs/sample.cs), 
[VB.NET](https://github.com/neige68/shiki-no-keisan-dll/blob/main/sample/vb/sample.vb) 
のサンプルを添付しています。

C# と VB.NET のサンプルでは、プラットホームに AnyCPU を指定してコンパイルし、
実行時に x86/x64 を判定して呼び出す DLL を切り分けるようにしています。

Arm にはまだ対応していません。

* [組込関数](builtin_functions.html)

floor, round などの関数では別途指定の許容誤差の吸収を行っています。

詳しくは 
[include/shiki_no_keisan.h](https://github.com/neige68/shiki-no-keisan-dll/blob/main/include/shiki_no_keisan.h)
をご覧ください。

予約変数 _RT が切捨時相対許容誤差、_AT が 切捨時絶対許容誤差で、初期値は両方とも 1e-15 になっています。

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
    往路=120;復路=80;2/(1/往路+1/復路) = 96

## 動作環境

Windows 10 以降 (x86, x64) 日本語版

## ライセンス

ソースコードは [Boost Software License, Version 1.0](https://www.boost.org/LICENSE_1_0.txt) に従って公開しています。

バイナリの配布は自由です。

## バイナリ リリース

C++, C, C#, VB.NET のサンプル コード、ビルド済みの DLL、インポート ライブラリを含むバイナリ リリースがあります。
ソースからビルドしたい場合以外はこちらを使用してください。

* [最新 Ver.1.00](https://github.com/neige68/shiki-no-keisan-dll/releases/download/v1.0/shiki-no-keisan-dll-1.00.zip)
* [リリース一覧](https://github.com/neige68/shiki-no-keisan-dll/releases) 

## ソースコードの所在

ソースコードは 
[https://github.com/neige68/shiki-no-keisan-dll/](https://github.com/neige68/shiki-no-keisan-dll/) 
にあります。

## 今後の予定

* 変数対応

* Arm 対応(実機が入手できたら)

## 連絡先

* [github issues](https://github.com/neige68/shiki-no-keisan-dll/issues)

* mail: shiki-no-keisan-dll@neige@ の2つめの@を .nu で置換してください

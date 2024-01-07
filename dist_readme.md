# shiki-no-keisan-dll 式の計算(計算式評価)DLL バイナリ リリース用 ドキュメント

Windows x86, x64 用の 式の計算(計算式評価)DLL です。

自由に使える x64 用の DLL が無いようなので作成しました。

C++, C, C#, VB.NET のサンプルを添付しています。

C# と VB.NET のサンプルでは、プラットホームに AnyCPU を指定してコンパイルし、
実行時に x86/x64 を判定して呼び出す DLL を切り分けるようにしています。

Arm にはまだ対応していません。

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

Windows 10 以降 (x86, x64)

## ライセンス

バイナリの配布は自由です。

## ソースコード

ソースコードは [https://github.com/neige68/shiki-no-keisan-dll](https://github.com/neige68/shiki-no-keisan-dll) にあります。

## サンプルコードのビルド

CMake 3.24, Visual Studio 2019 (VC14.2), Boost 1.81 を使用しています。用意してください。

VC14.2 の vcvarsall.bat のあるディレクトリを環境変数 VC142 に設定しておいてください。

例:

    set VC142=C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build
    
build.bat を実行してください。

## 今後の予定

* 変数対応

* Arm 対応(実機が入手できたら)

## 連絡先

* [github issues](https://github.com/neige68/shiki-no-keisan-dll/issues)

* mail: shiki-no-keisan-dll@neige@ の2つめの@を .nu で置換してください

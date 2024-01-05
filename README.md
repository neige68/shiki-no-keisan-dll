# shiki-no-keisan-dll

Windows x86, x64 用の 式の計算(計算式評価)DLL です。

CMake 3.24, Visual Studio 2019 (VC14.2), Boost 1.81 の Spirit X3 を使用しています。

C++, C#, VB.NET のサンプルを添付しています。

C# と VB.NET のサンプルでは、プラットホームに AnyCPU を指定してコンパイルし、
実行時に x86/x64 を判定して呼び出す DLL を切り分けるようにしています。

ビルド時には VC14.2 の vcvarsall.bat のあるディレクトリを環境変数 VC142 に設定しておいてください。

    set VC142=C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build

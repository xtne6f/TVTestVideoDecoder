デジタル放送映像復号プログラム実装研究資料
==========================================
デジタル放送映像復号プログラム実装研究資料は、パーソナルコンピュータ上の汎用 OS において、デジタル放送の映像復号を行うプログラムの実装を研究する目的で頒布される研究資料である。

この資料は MPEG-2 映像を復号するための基本的な機能を実装している。
CAS 処理は実装されていないため、一般のテレビ放送の視聴に用いることはできない。


ライセンス
----------
GPL v3


このフォークについて
----------
[DBCTRADO/TVTestVideoDecoder](https://github.com/DBCTRADO/TVTestVideoDecoder) をMSYS2上の [MinGW-w64](https://sourceforge.net/projects/mingw-w64) でビルドできるよう調整します。

[ビルド]
1. [MSYS2](https://www.msys2.org/) の `msys2-i686-日付.exe`(32bitOS用) または `msys2-x86_64-日付.exe`(64bitOS用) をインストール  
   上記サイトに従って`pacman -Syu` →(必要なら)`pacman -Su`でパッケージをアップデート
2. スタートメニューの"MSYS2 MinGW 32-bit"(x64ビルド時は64-bit)を開き、起動した黒窓で以下を実行してmakeとgccとcmakeをインストール  
   `$ pacman -S make mingw-w64-i686-gcc mingw-w64-i686-cmake` (x86ビルド時)  
   `$ pacman -S make mingw-w64-x86_64-gcc mingw-w64-x86_64-cmake` (x64ビルド時)
3. つづけて以下を実行 (この文書が"C:\TVTestVideoDecoder"にある場合)
   ```
   $ cd /c/TVTestVideoDecoder/src
   $ mkdir build
   $ cd build
   $ cmake -G "MSYS Makefiles" -DCMAKE_BUILD_TYPE=Release ..
   ($ cmake -E env CFLAGS=-march=native CXXFLAGS=-march=native cmake -G "MSYS Makefiles" -DCMAKE_BUILD_TYPE=Release .. #ビルド環境に最適化する場合)
   $ make
   ```

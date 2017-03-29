# これは何?

C++勉強用の環境。

|type|name|
|-|-|
|ビルド|CMake|
|テスト|Catch|
|ログ出力|PLog|
|性能評価|Google Benchmark|

# 実行

## *nix

```
$ ./scripts/generate.sh
$ ./build/Tester
```

## Windows

- VisualStudio 2017 (またはより新しいバージョン) にてフォルダを開く。
- 以下を実行する
  - mkdir build
  - cmake ..
  - "C:\Program Files (x86)\MSBuild\14.0\Bin\MSBuild.exe" cpp_study.sln
  - .\Benchmark\Debug\bm.exe
  - .\UnitTest\Debug\Tester.exe

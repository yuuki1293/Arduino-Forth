# Arduino-Forth
ArduinoでForthマシンを動かす。

## セットアップ
arduino-cliがインストールされていない場合、以下のコマンドでインストール。  
(Windows・Linux)
```shell
./setup-arduino-cli
```
(Mac)
```zsh
brew install arduino-cli
```
コンフィグを初期化。
```shell
arduino-cli config init
```
Arduinoが接続されているポートを調べる。
```shell
arduino-cli board list
```
調べたポートをMakefileに書き込む。
```shell
（略）
BOARD = arduino:avr:uno
PORT = Your_port_here
CC = g++
（略）
```

### 検証・アップロード・コンパイル
検証
```shell
make
```
アップロード
```shell
make upload
```
ローカルでの検証用にコンパイル
```shell
make local
```
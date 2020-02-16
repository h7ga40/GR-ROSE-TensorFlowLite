# GR-ROSE: TensorFlow Lite for Microcontrollers

[がじぇるね](https://www.renesas.com/us/ja/products/gadget-renesas.html)で提供されている[GR-ROSE](https://www.renesas.com/us/ja/products/gadget-renesas/boards/gr-rose.html)向けに[TensorFlow Lite for Microcontrollers](https://www.tensorflow.org/lite/microcontrollers)をビルドできるようにしたもので、コンパイラに[gcc](https://gcc-renesas.com/ja/)を使用します。
IDEとして、[e2 Studio](https://www.renesas.com/jp/ja/products/software-tools/tools/ide/e2studio.html)か、[Visual Studio Code](https://code.visualstudio.com/)が使えるようプロジェクトファイルを含んでいます。IDEに設定したgccのバージョンは`8.3.0.201904`です。必要に応じて変更してください。

## プログラム

- [Ｌチカ](free_rtos) - GR-ROSE用のArduinoライブラリの基本的な[サンプル](https://github.com/godzilla-max/rose_sketch)で、FreeRTOSを使った、二つのloopでLEDをタイミングをずらして点滅させるプログラム。
- [Hello World](hello_world) - TensorFlowで用意されている[サンプル](https://github.com/tensorflow/tensorflow/tree/master/tensorflow/lite/micro/examples/hello_world)で、学習したサイン関数の出力でLEDを点滅させるプログラム。
- [Micro speech](micro_speech) - TensorFlowで用意されている[サンプル](https://github.com/tensorflow/tensorflow/tree/master/tensorflow/lite/micro/examples/micro_speech)で、音声認識のプログラム。[SPU0414HR5H-SB使用した超小型シリコンマイクモジュール](http://akizukidenshi.com/catalog/g/gM-08940)をアナログピン0に接続して確認し、"yes"と"no"が判定できた。
- [Magic wand](magic_wand) - TensorFlowで用意されている[サンプル](https://github.com/tensorflow/tensorflow/tree/master/tensorflow/lite/micro/examples/magic_wand)で、加速度センサーでジェスチャーを認識するプログラム。[LSM9DS1 9軸慣性計測ユニット ピッチ変換済みモジュール](https://www.switch-science.com/catalog/2734)をPMODのI2Cに接続してデバイスが動作することを確認。認識は時々するが思い通りに認識しない。ジェスチャー仕方がよくわからない。
- [Person detection](person_detection) - TensorFlowで用意されている[サンプル](https://github.com/tensorflow/tensorflow/tree/master/tensorflow/lite/micro/examples/person_detection)で、人を検知するプログラム。動作確認はしていない。

## LICENSE

以下のソフトを含んでいます。

- [LSM9DS1 Library for Arduino](magic_wand/lib/README.adoc)
- [Arduino Core for Circuitrocks Alora Boards](micro_speech/lib/LICENSE)
- [ArduCAM Library](person_detection/lib/ArduCAM/LICENSE)
- [Arduino JPEGDecoder library](person_detection/lib/JPEGDecoder/license.txt)
- [Arduino](rose_sketch/arduino/license.txt)
- [FreeRTOS](rose_sketch/FreeRTOS)
- [Micro XRCE-DDS Client](rose_sketch/Micro-XRCE-DDS-Client/LICENSE)
- [eProsima Micro CDR](rose_sketch/Micro-XRCE-DDS-Client/thirdparty/microcdr/LICENSE)
- [Adafruit GFX Library](rose_sketch/arduino/lib/AdafruitGFX/license.txt)
- [JSON library for Arduino and embedded C++](rose_sketch/arduino/lib/ArduinoJson/LICENSE.md)
- [ICSlib for Arduino](rose_sketch/arduino/lib/ICS/LICENSE)
- [Arduino WiFi library for ESP8266 modules](rose_sketch/arduino/lib/WiFiEsp/LICENSE)
- [TensorFlow](tensorflow-microlite/LICENSE)
- [Memory Efficient Serialization Library](tensorflow-microlite/third_party/flatbuffers/LICENSE.txt)
- [a small self-contained low-precision GEMM library](tensorflow-microlite/third_party/gemmlowp/LICENSE)
- [a Fast Fourier Transform (FFT) library](tensorflow-microlite/third_party/kissfft/COPYING)

他、各ファイルにあるLICENSE表示に従います。

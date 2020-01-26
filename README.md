# GR-ROSE: TensorFlow Lite for Microcontrollers

[がじぇるね](https://www.renesas.com/us/ja/products/gadget-renesas.html)で提供されている[GR-ROSE](https://www.renesas.com/us/ja/products/gadget-renesas/boards/gr-rose.html)向けに[TensorFlow Lite for Microcontrollers](https://www.tensorflow.org/lite/microcontrollers)をビルドできるようにしたもので、コンパイラに[gcc](https://gcc-renesas.com/ja/)を使用します。
IDEとして、[e2 Studio](https://www.renesas.com/jp/ja/products/software-tools/tools/ide/e2studio.html)か、[Visual Studio Code](https://code.visualstudio.com/)が使えるようプロジェクトファイルを含んでいます。IDEに設定したgccのバージョンは`8.3.0.201904`です。必要に応じて変更してください。

## プログラム

- [Ｌチカ](free_rtos) - GR-ROSE用のArduinoライブラリの基本的な[サンプル](https://github.com/godzilla-max/rose_sketch)で、FreeRTOSを使った、二つのloopでLEDをタイミングをずらして点滅させるプログラム。
- [Hello World](hello_world) - TensorFlowで用意されている[サンプル](https://github.com/tensorflow/tensorflow/tree/master/tensorflow/lite/micro/examples/hello_world)で、学習したサイン関数の出力でLEDを点滅させるプログラム。
- [Micro speech](micro_speech) - TensorFlowで用意されている[サンプル](https://github.com/tensorflow/tensorflow/tree/master/tensorflow/lite/micro/examples/micro_speech)で、音声認識のプログラム。動作確認はしていない。
- [Magic wand](magic_wand) - TensorFlowで用意されている[サンプル](https://github.com/tensorflow/tensorflow/tree/master/tensorflow/lite/micro/examples/magic_wand)で、加速度センサーでジェスチャーを認識するプログラム。動作確認はしていない。
- [Person detection](person_detection) - TensorFlowで用意されている[サンプル](https://github.com/tensorflow/tensorflow/tree/master/tensorflow/lite/micro/examples/person_detection)で、人を検知するプログラム。動作確認はしていない。

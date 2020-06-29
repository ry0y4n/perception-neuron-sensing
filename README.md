# perception-neuron-sensing
`perception neuron` のリサーチリポジトリ

モーションキャプチャからbvhデータとcalculationデータをストリーミングしリアルタイムに出力するプログラムを実装

## commands
bvhデータ
```zsh
g++ bvh.cpp -L./lib/mac -lNeuronDataReader && ./a.out
```

calculationデータ
```zsh
g++ calculation.cpp -L./lib/mac -lNeuronDataReader && ./a.out
```

X・・・右が正方向

Y・・・上が正方向

Z・・・手前が正方向

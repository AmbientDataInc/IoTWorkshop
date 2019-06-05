void setup() {  // 最初に1回だけ実行される
    pinMode(14, OUTPUT);  // ピン14を出力モードにする
}

void loop() {  // 繰り返し実行される
    digitalWrite(14, HIGH);  // ピン14をHIGH(3.3V)にする
    delay(500);                    // 0.5秒待つ
    digitalWrite(14, LOW);   // ピン14をLOW(0V)にする
    delay(500);                    // 0.5秒待つ
}  // 関数の実行が終わると、また呼ばれる

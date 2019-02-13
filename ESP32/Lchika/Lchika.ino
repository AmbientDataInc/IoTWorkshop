void setup() {  // 最初に1回だけ実行される
    pinMode(25, OUTPUT);  // ピン25を出力モードにする
}

void loop() {  // 繰り返し実行される
    digitalWrite(25, HIGH);  // ピン25をHIGH(3.3V)にする
    delay(500);                    // 0.5秒待つ
    digitalWrite(25, LOW);   // ピン25をLOW(0V)にする
    delay(500);                    // 0.5秒待つ
}  // 関数の実行が終わると、また呼ばれる

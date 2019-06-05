#define MULTISAMPLING 10

void setup() {
    Serial.begin(74880);  // 74880baudでシリアル回線を初期化する
    while (!Serial) ;     // シリアル回線が利用可能になるまで待つ
}

void loop() {
    int val = 0;
    for (int i = 0; i < MULTISAMPLING; i++) {
        val += analogRead(A0);  // Toutの電圧を読む
    }
    val /= MULTISAMPLING;
    Serial.println(val);  // 読んだ電圧を出力する
    delay(1000);
}

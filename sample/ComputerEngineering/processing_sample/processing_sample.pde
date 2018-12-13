import processing.serial.*;
Serial myPort;  // myPortのところは好きな名前でOK
String datastr;  // datastrという名前の文字列型変数を宣言(この記事の下の方で出てきます)
PrintWriter output;  // PrintWriter型のオブジェクトを宣言
int count = 1;  // カウンタを宣言して初期化
int wait = 1; //サンプリング周期10ms
int max_count = 1000; // 取得データ数


void setup()
{
  println(Serial.list());  // 使えるポート一覧
  myPort = new Serial(this,"/dev/ttyUSB0", 115200); // myPortを最初のシリアルポート、9600bpsに設定
  myPort.clear();
  output = createWriter("LPF2.csv");  // ファイル名log.txtでファイルを開く
}
 
 float vol,temp;
 
void draw() {
  int tempdata = 0;
  float tempdata_c = 0;

  if (count > max_count) {  // カウンタが100超えていたら終了
    output.flush();  // 出力バッファに残っているデータを全て書き出し
    output.close();  // ファイルを閉じる
    exit();
  }
  count++; // カウントアップ
  
  if ( myPort.available() > 0) {
    delay(wait);
    datastr = myPort.readString();
    tempdata = int(datastr);
    vol = tempdata * (3600.f / 4096.f);
    temp = (vol - 400.f) / 19.5f;
    println(datastr, temp);
    output.println(count + "," + temp); //csvファイルにデータ書き出し
  }
}

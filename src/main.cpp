#include <Arduino.h>
#include <WiFi.h> // ถ้าใช้บอร์ด ESP8266 ให้แก้บรรทัดนี้เป็น #include <ESP8266WiFi.h>

// --- 1. ตั้งค่า Wi-Fi ---
const char* ssid = "Chuckmab";     // ใส่ชื่อ Wi-Fi
const char* password = "000000000"; // ใส่รหัสผ่าน Wi-Fi

// --- 2. ตั้งค่า Node-RED ---
const char* nodeRedIP = " 172.20.10.2"; // ใส่ IP Address ของคอมพิวเตอร์ที่เปิด Node-RED
const int nodeRedPort = 2000;            // พอร์ต 2000 ตามที่อาจารย์ตั้งไว้ใน TCP In

WiFiClient tcpClient;

void setup() {
  Serial.begin(115200);
  
  // เริ่มการเชื่อมต่อ Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");
}

void loop() {
  // จำลองค่าเซนเซอร์ (อุณหภูมิ และ ความชื้น)
  float temp = 25.5; 
  float humid = 60.0;
  
  // เชื่อมต่อไปยัง Node-RED
  if (tcpClient.connect(nodeRedIP, nodeRedPort)) {
    
    // สร้างข้อความแบบคั่นด้วยลูกน้ำ เช่น "25.5,60.0"
    String payload = String(temp) + "," + String(humid); 
    
    // ส่งข้อมูลไป Node-RED (ใช้ println เพื่อให้มีการขึ้นบรรทัดใหม่)
    tcpClient.println(payload); 
    tcpClient.stop(); // ปิดการเชื่อมต่อเมื่อส่งเสร็จ
    
    Serial.println("Sent to Node-RED: " + payload);
    
  } else {
    Serial.println("Connection to Node-RED failed!");
  }

  // ส่งข้อมูลทุกๆ 5 วินาที
  delay(5000); 
}
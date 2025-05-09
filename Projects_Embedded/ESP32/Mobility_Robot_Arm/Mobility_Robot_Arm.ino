#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ESP32Servo.h>

Servo baseServo, upDownServo, forwardBackwardServo, gripperServo;  
const int basePin = 32;  
const int upDownPin = 33;  
const int forwardBackwardPin = 25;  
const int gripperPin = 26;  

// DC Motor Pins (H-Bridge)
#define MOTOR1_DIR1  4   // Forward
#define MOTOR1_DIR2  5   // Backward
#define MOTOR2_DIR1  18  // Forward
#define MOTOR2_DIR2  19  // Backward

const char* apSSID = "ESP32_Controller";  
const char* apPassword = "12345678";  

AsyncWebServer server(80);

void setup() {
    Serial.begin(115200);
    WiFi.softAP(apSSID, apPassword);
    Serial.println("AP Started! Connect to " + String(apSSID));
    Serial.println("Visit: " + WiFi.softAPIP().toString());

    baseServo.attach(basePin);
    upDownServo.attach(upDownPin);
    forwardBackwardServo.attach(forwardBackwardPin);
    gripperServo.attach(gripperPin);

    baseServo.write(90);
    upDownServo.write(90);
    forwardBackwardServo.write(90);
    gripperServo.write(90);
    
    pinMode(MOTOR1_DIR1, OUTPUT);
    pinMode(MOTOR1_DIR2, OUTPUT);
    pinMode(MOTOR2_DIR1, OUTPUT);
    pinMode(MOTOR2_DIR2, OUTPUT);

    Serial.println("Servos & Motors Ready!");

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, "text/html", R"rawliteral(
            <html>
            <head>
                <title>Robot Arm Control</title>
                <style>
                    body { text-align: center; font-family: Arial, sans-serif; background-color: #333; color: white; }
                    button { padding: 10px 20px; margin: 5px; font-size: 18px; }
                    input { width: 80%; }
                    .container { background: #444; padding: 20px; border-radius: 10px; display: inline-block; }
                </style>
            </head>
            <body>
                <h1>Robot Arm & Car Control</h1>

                <div class="container">
                    <h2>Servo Control</h2>
                    <p>Base: <span id="baseAngle">90</span>°</p>
                    <input type="range" id="baseSlider" min="0" max="180" value="90" oninput="updateServo('base', this.value)">

                    <p>Up-Down: <span id="upDownAngle">90</span>°</p>
                    <input type="range" id="upDownSlider" min="15" max="165" value="90" oninput="updateServo('upDown', this.value)">

                    <p>Forward-Backward: <span id="forwardBackwardAngle">90</span>°</p>
                    <input type="range" id="forwardBackwardSlider" min="15" max="165" value="90" oninput="updateServo('forwardBackward', this.value)">

                    <p>Gripper: <span id="gripperAngle">90</span>°</p>
                    <input type="range" id="gripperSlider" min="0" max="180" value="90" oninput="updateServo('gripper', this.value)">
                </div>

                <div class="container">
                    <h2>Motor Control</h2>
                    <button onclick="motorCommand('forward')">Forward</button>
                    <button onclick="motorCommand('backward')">Backward</button>
                    <button onclick="motorCommand('left')">Left</button>
                    <button onclick="motorCommand('right')">Right</button>
                    <button onclick="motorCommand('stop')">Stop</button>
                </div>

                <script>
                    function updateServo(servo, angle) {
                        fetch(/move?servo= + servo + &angle= + angle);
                        document.getElementById(servo + 'Angle').innerText = angle;
                    }

                    function motorCommand(action) {
                        fetch(/motor?action= + action);
                    }
                </script>
            </body>
            </html>
        )rawliteral");
    });

    server.on("/move", HTTP_GET, [](AsyncWebServerRequest *request) {
        if (request->hasParam("servo") && request->hasParam("angle")) {
            String servoName = request->getParam("servo")->value();
            int angle = request->getParam("angle")->value().toInt();
            
            if (angle < 0 || angle > 180) request->send(400, "text/plain", "Invalid angle!");
            else {
                Serial.printf("Moving %s to %d°\n", servoName.c_str(), angle);
                if (servoName == "base") baseServo.write(angle);
                else if (servoName == "upDown") upDownServo.write(constrain(angle, 15, 165));
                else if (servoName == "forwardBackward") forwardBackwardServo.write(constrain(angle, 15, 165));
                else if (servoName == "gripper") gripperServo.write(angle);

                request->send(200, "text/plain", servoName + " moved to " + String(angle) + " degrees");
            }
        } else request->send(400, "text/plain", "Invalid request!");
    });

    server.on("/motor", HTTP_GET, [](AsyncWebServerRequest *request) {
        if (request->hasParam("action")) {
            String action = request->getParam("action")->value();
            Serial.println("Motor Command: " + action);

            if (action == "forward") moveForward();
            else if (action == "backward") moveBackward();
            else if (action == "left") turnLeft();
            else if (action == "right") turnRight();
            else stopMotors();

            request->send(200, "text/plain", "Motor action executed: " + action);
        } else request->send(400, "text/plain", "Invalid motor command!");
    });

    server.begin();
    Serial.println("Web Server Started!");
}

void loop() { delay(100); }

// Motor Control Functions (No PWM, Only Direction)
void moveForward() { digitalWrite(MOTOR1_DIR1, HIGH); digitalWrite(MOTOR1_DIR2, LOW); digitalWrite(MOTOR2_DIR1, HIGH); digitalWrite(MOTOR2_DIR2, LOW); }
void moveBackward() { digitalWrite(MOTOR1_DIR1, LOW); digitalWrite(MOTOR1_DIR2, HIGH); digitalWrite(MOTOR2_DIR1, LOW); digitalWrite(MOTOR2_DIR2, HIGH); }
void turnLeft() { digitalWrite(MOTOR1_DIR1, LOW); digitalWrite(MOTOR1_DIR2, HIGH); digitalWrite(MOTOR2_DIR1, HIGH); digitalWrite(MOTOR2_DIR2, LOW); }
void turnRight() { digitalWrite(MOTOR1_DIR1, HIGH); digitalWrite(MOTOR1_DIR2, LOW); digitalWrite(MOTOR2_DIR1, LOW); digitalWrite(MOTOR2_DIR2, HIGH); }
void stopMotors() { digitalWrite(MOTOR1_DIR1, LOW); digitalWrite(MOTOR1_DIR2, LOW); digitalWrite(MOTOR2_DIR1, LOW); digitalWrite(MOTOR2_DIR2, LOW); }

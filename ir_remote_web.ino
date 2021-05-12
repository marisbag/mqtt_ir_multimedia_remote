#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
// Add this library: https://github.com/markszabo/IRremoteESP8266
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <PubSubClient.h>

#define IR_SEND_PIN D2
#define DELAY_BETWEEN_COMMANDS 1000

const char* mqtt_server = ""; //mqtt server ip address
const char* ssid = "";
const char* password = "";

IRsend irsend(IR_SEND_PIN);
ESP8266WebServer server(80);
WiFiClient espClient;
PubSubClient client(espClient);

const int led = BUILTIN_LED;

String rowDiv = "    <div class=\"row\" style=\"padding-bottom:1em\">\n";
String endDiv = "    </div>\n";

// Buttons are using the bootstrap grid for sizing - http://getbootstrap.com/css/#grid
String generateButton(String colSize, String id, String text, String url) {

  return  "<div class=\"" + colSize + "\" style=\"text-align: center\">\n" +
          "    <button id=\"" + id + "\" type=\"button\" class=\"btn btn-default\" style=\"width: 100%\" onclick='makeAjaxCall(\"" + url + "\")'>" + text + "</button>\n" +
          "</div>\n";
}

void handleRoot() {
  digitalWrite(led, 0);
  String website = "<!DOCTYPE html>\n";
  website = website + "<html>\n";
  website = website + "  <head>\n";
  website = website + "    <meta charset=\"utf-8\">\n";
  website = website + "    <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n";
  website = website + "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n";
  website = website + "    <link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css\">\n";
  website = website + "  </head>\n";
  website = website + "  <body>\n";
  website = website + "    <div class=\"container-fluid\">\n";
  // ------------------------- Power Controls --------------------------
  website = website + rowDiv;
  website = website + generateButton("col-xs-2", "poweron","Power ON", "poweron");
  website = website + generateButton("col-xs-2", "poweroff","Power Off", "poweroff");
  website = website + endDiv;
// ------------------------- Arrow Controls --------------------------
  website = website + rowDiv;
  website = website + generateButton("col-xs-2", "aup","Up", "aup");
  website = website + generateButton("col-xs-2", "adown","Down", "adown");
  website = website + generateButton("col-xs-2", "aleft","Left", "aleft");
  website = website + generateButton("col-xs-2", "aright","Right", "aright");
  website = website + generateButton("col-xs-2", "aok","OK", "aok");
  website = website + endDiv;
  
  // ------------------------- Volume Controls --------------------------
  website = website + rowDiv;
  website = website + generateButton("col-xs-12", "up","Vol Up", "up");
  website = website + endDiv;
  website = website + rowDiv;
  website = website + generateButton("col-xs-12", "down","Vol Down", "down");
  website = website + endDiv;

    // ------------------------- Chanel Controls --------------------------
  website = website + rowDiv;
  website = website + generateButton("col-xs-12", "chup","CH +", "chup");
  website = website + endDiv;
  website = website + rowDiv;
  website = website + generateButton("col-xs-12", "chdown","CH -", "chdown");
  website = website + endDiv;

  website = website + endDiv;
  website = website + "    <script src=\"https://ajax.googleapis.com/ajax/libs/jquery/1.12.4/jquery.min.js\"></script>\n";
  website = website + "    <script src=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js\"></script>\n";
  website = website + "    <script> function makeAjaxCall(url){$.ajax({\"url\": url})}</script>\n";
  website = website + "  </body>\n";
  website = website + "</html>\n";

  server.send(200, "text/html", website);
  digitalWrite(led, 1);
}

void handleNotFound(){
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 1);
}

void setup(void){
  irsend.begin();
  pinMode(led, OUTPUT);
  digitalWrite(led, 1);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS Responder Started");
  }
  client.setServer(mqtt_server, 1884);
  client.setCallback(callback);
  server.on("/", handleRoot);
  server.on("/powerof",[](){ poweroff();  });
  server.on("/poweron", [](){ poweron(); });
  server.on("/aup", [](){ aup(); });
  server.on("/adown", [](){ adown(); });
  server.on("/aleft", [](){ aleft(); });
  server.on("/aright", [](){ aright(); });
  server.on("/aok", [](){ aok(); });
  server.on("/chdown", [](){ chdown(); });
  server.on("/chup", [](){ chup(); });
  server.on("/down", [](){ down(); });
  server.on("/up", [](){ up(); });
  server.on("/sspower", [](){ sspower(); });
  server.on("/sschannel1", [](){ sschannel1(); });
  server.on("/sschannel2", [](){ sschannel2(); });
  server.on("/sschannel3", [](){ sschannel3(); });
  server.on("/sschannel4", [](){ sschannel4(); });
  server.on("/sstvsound", [](){ sstvsound(); });
  server.on("/tvpower", [](){ tvpower(); });
  server.on("/tvsource", [](){ tvsource(); });
  server.on("/togglesource", [](){ togglesource(); });
  server.on("/satpower", [](){ satpower(); });
  server.on("/satok", [](){ satok(); });
  server.on("/satexit", [](){ satexit(); });
  server.on("/satup", [](){ satup(); });
  server.on("/satdown", [](){ satdown(); });
  server.on("/satblue", [](){ satblue(); });
  server.on("/chromecast", [](){ chromecast(); });

  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP Server Started");
}

void loop(void){
  server.handleClient();
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();
  if (String(topic) == "esp32/output") {
    Serial.print("Changing output to ");
    if(messageTemp == "on"){
      Serial.println("on");
    //  digitalWrite(ledPin, HIGH);
    }
    else if(messageTemp == "off"){
      Serial.println("off");

    }
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client", "mqtt", "mqtt")) {
      Serial.println("connected");
      client.subscribe("esp32/remote");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

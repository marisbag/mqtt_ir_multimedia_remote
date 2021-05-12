void poweroff(void) {
  irsend.sendNEC(0x40040100FCFD, 32);
  irsend.sendNEC(0x40040100FCFD, 32);
  irsend.sendNEC(0x40040100FCFD, 32);
  irsend.sendNEC(0x4B36E21D, 32);
  irsend.sendNEC(0x6804847B, 32);
}

//turn on tv, audio receiver, tv receiver and switch sources to default state
void poweron(void) {
  Serial.println("Power ON");
  irsend.sendNEC(0x6746FE57, 32);
  irsend.sendNEC(0x6746FE57, 32);
  irsend.sendNEC(0x400401007C7D, 32);
  irsend.sendNEC(0x6746FE57, 32);
  irsend.sendNEC(0x6746FE57, 32);
  irsend.sendNEC(0x400401007C7D, 32);
  irsend.sendNEC(0x6746FE57, 32);
  irsend.sendNEC(0x6746FE57, 32);
  irsend.sendNEC(0x400401007C7D, 32);
  delay(DELAY_BETWEEN_COMMANDS);
  irsend.sendNEC(0x6804847B, 32);
  irsend.sendNEC(0x4BB620DF, 32);
  delay(DELAY_BETWEEN_COMMANDS);
  irsend.sendNEC(0x400401200D2C, 32);
  irsend.sendNEC(0x400401200D2C, 32);
  delay(DELAY_BETWEEN_COMMANDS);
  irsend.sendNEC(0x4B3631CE, 32);
  server.send(200, "text/plain", "Power ON");
}


void aup(void){
  irsend.sendNEC(0x6804A857, 32);
  server.send(200, "text/plain", "Volume Down");
}

void adown(void){
  irsend.sendNEC(0x68046897, 32);
  server.send(200, "text/plain", "Volume Down");
}

void aleft(void){
  irsend.sendNEC(0x6804E817, 32);
  server.send(200, "text/plain", "Volume Down");
}

 void aright(void){
  irsend.sendNEC(0x680418E7, 32);
  server.send(200, "text/plain", "Volume Down");
}

void aok(void){
  irsend.sendNEC(0x68049867, 32);
  server.send(200, "text/plain", "Volume Down");
}

void chdown(void){
  Serial.println("Sorround Sound Down");
  irsend.sendNEC(0x68042CD3, 32);
  server.send(200, "text/plain", "Volume Down");
}

void chup(void){
  Serial.println("Surround Sound Up");
  irsend.sendNEC(0x6804CC33, 32);
  server.send(200, "text/plain", "Volume Up");
}

void down(void){
  Serial.println("Sorround Sound Down");
  irsend.sendNEC(0x4BB6C03F, 32);
  server.send(200, "text/plain", "Volume Down");
}

void up(void){
  Serial.println("Surround Sound Up");
  irsend.sendNEC(0x4BB640BF, 32);
  server.send(200, "text/plain", "Volume Up");
}

void sspower(void){
  Serial.println("Surround Sound power");
  irsend.sendNEC(0x4B36D32C, 32);
  server.send(200, "text/plain", "Surround Sound Power");
}

void sschannel1(void){
  Serial.println("Surround Sound Channel 1");
  irsend.sendNEC(0x4B3631CE, 32);
  server.send(200, "text/plain", "Surround Sound Channel 1");
}

void sschannel2(void){
  Serial.println("Surround Sound Channel 2");
  irsend.sendNEC(0x4BB6F00F, 32);
  server.send(200, "text/plain", "Surround Sound Channel 2");
}

void sschannel3(void){
  Serial.println("Surround Sound Channel 3");
  irsend.sendNEC(0x4BB6708F, 32);
  server.send(200, "text/plain", "Surround Sound Channel 3");
}

void sschannel4(void){
  Serial.println("Surround Sound Channel 4");
  irsend.sendNEC(0x4BB6B04F, 32);
  server.send(200, "text/plain", "Surround Sound Channel 4");
}

void sstvsound(void){
  Serial.println("Surround Sound sstvsound");
  irsend.sendNEC(0x4BB6906F, 32);
  server.send(200, "text/plain", "Surround Sound sstvsound");
}

void tvpower(void){
  Serial.println("TV power");
  irsend.sendNEC(0x20DF10EF, 32);
  server.send(200, "text/plain", "TV Power");
}

void tvsource(void){
  Serial.println("TV Source");
  irsend.sendNEC(0x20DFD02F, 32);
  server.send(200, "text/plain", "TV Source");
}

void togglesource(void){
  Serial.println("TV Source");
  irsend.sendNEC(0x20DFD02F, 32);
  delay(DELAY_BETWEEN_COMMANDS);
  irsend.sendNEC(0x20DFD02F, 32);
  server.send(200, "text/plain", "TV Source");
}

void satpower(void){
  Serial.println("Sat Power");
  irsend.sendNEC(0xA25D7887, 32);
  server.send(200, "text/plain", "Sat Power");
}

void satok(void){
  Serial.println("Sat Ok");
  irsend.sendNEC(0xA25DFA05, 32);
  server.send(200, "text/plain", "Sat OK");
}

void satexit(){
  Serial.println("Sat Exit");
  irsend.sendNEC(0xA25D06F9, 32);
  server.send(200, "text/plain", "Sat Exit");
}

void satup(void){
  Serial.println("Sat UP");
  irsend.sendNEC(0xA25DC03F, 32);
  server.send(200, "text/plain", "Sat UP");
}

void satdown(void){
  Serial.println("Sat Down");
  irsend.sendNEC(0xA25D7A85, 32);
  server.send(200, "text/plain", "Sat Down");
}

void satblue(void){
  Serial.println("Sat Blue");
  irsend.sendNEC(0xA25D52AD, 32);
  server.send(200, "text/plain", "Sat Blue");
}

void chromecast(void){
  Serial.println("Chromecast");
  irsend.sendNEC(0x20DFD02F, 32);
  delay(DELAY_BETWEEN_COMMANDS);
  irsend.sendNEC(0x20DFD02F, 32);
  delay(DELAY_BETWEEN_COMMANDS);
  irsend.sendNEC(0x4BB6906F, 32);
  server.send(200, "text/plain", "Chromecast");
}

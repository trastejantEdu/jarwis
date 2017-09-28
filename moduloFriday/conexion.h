bool conexionWiFi(const char* ssid,const char* password){
  int progress;
  WiFi.begin(ssid,password);
    
  while ( WiFi.status() != WL_CONNECTED ) {
    progress= progress + 20;
    delay ( 500 );
    Serial.print ( "." );
    //display.print(".");
    if(progress>=100) progress=0;
    display.drawProgressBar(0, 0, 120, 10, progress);
    display.display();
  }

 Serial.println ( "" );
 Serial.print ( "Connected to " );
 Serial.println ( ssid );
 Serial.print ( "IP address: " );
 Serial.println ( WiFi.localIP() );
 return true;
}


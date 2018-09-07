#ifndef _NTP_h_
#define _NTP_h_

class NTP {
  public:
      NTP();
      void begin();
      void begin(int port);
      unsigned long get_unix_time();
      unsigned long get_hour();
      unsigned long get_minutes();
      unsigned long get_secons();
      unsigned long get_hour(int epoch);
      unsigned long get_minutes(int epoch);
      unsigned long get_secons(int epoch);
      String get_timeNow();
      String get_timeNow(int UTC);
      int onTime();
      int get_year();
      int get_month();
      int get_day();
      int ajusteHorario( int dia, int mes, int anyo, int hora, int minuto, int segundo);
  
  private:
      const char* ntpServerName = "time.nist.gov";
      IPAddress timeServerIP;   
      static const int NTP_PACKET_SIZE = 48; // NTP time stamp is in the first 48 bytes of the message
      byte packetBuffer[ NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets
      unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
      unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
      unsigned long secsSince1900 = highWord << 16 | lowWord;
      const unsigned long seventyYears = 2208988800UL;    
      unsigned long epoch = secsSince1900 - seventyYears;
      unsigned int localPort = 2390;// local port to listen for UDP packets
      unsigned long sendNTPpacket(IPAddress& address);
      time_t toTime( int dia, int mes, int anyo, int hora, int minuto, int segundo);
      unsigned int ajusteHorario();
      tmElements_t Fecha;
      int ajuste;     
      time_t cambio_1, cambio_2, fecha_hoy;
  };

#endif

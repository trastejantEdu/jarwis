//Convertir Hexadecimal a Decimal
//Funcion extraida de https://github.com/benrugg/Arduino-Hex-Decimal-Conversion/blob/master/hex_dec.ino
unsigned int hexToDec(String hexString) {
  
  unsigned int decValue = 0;
  int nextInt;
  
  for (int i = 0; i < hexString.length(); i++) {
    
    nextInt = int(hexString.charAt(i));
    if (nextInt >= 48 && nextInt <= 57) nextInt = map(nextInt, 48, 57, 0, 9);
    if (nextInt >= 65 && nextInt <= 70) nextInt = map(nextInt, 65, 70, 10, 15);
    if (nextInt >= 97 && nextInt <= 102) nextInt = map(nextInt, 97, 102, 10, 15);
    nextInt = constrain(nextInt, 0, 15);
    
    decValue = (decValue * 16) + nextInt;
  }
  
  return decValue;
}

/*
 * Reinicia via software y guarda un contador de los reinicios que ha realizado
 */
void restart(){
  //Leer el nu de reset de la EEPRO
  int n_reset=0;
  n_reset++;
  //GUARDARLOS ANTES DE REINICIAR
}


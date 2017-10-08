
void setup() {
   pinMode(LED_BUILTIN, OUTPUT);

}

void loop() {
   int i = 0;
   for (i = 0; i < 255; i++){ //faz um loop loop de 0 a 254
      //acende gradualmente
      analogWrite(LED_BUILTIN, i); //define o brilho do LED
      delay(10); //espera 10ms
    }

    for (i = 255; i > 0; i--); { //faz um loop de 255 a 1
 
      analogWrite(LED_BUILTIN, i); //define o brilho do LED
      delay(10); //aguarda 10ms
    }

}

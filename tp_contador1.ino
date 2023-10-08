#define a 10
#define b 11
#define c 13
#define d 7
#define e 6
#define f 9
#define g 8

#define DISPLAY_UNIDADES A0
#define DISPLAY_DECENAS A1

#define PULSADOR_INCREMENTAR 5 // Pin del pulsador para aumentar el contador
#define PULSADOR_DECREMENTAR 3 // Pin del pulsador para disminuir el contador
#define PULSADOR_REINICIAR 4   // Pin del pulsador para reiniciar el contador a cero

int contador = 0;
int ultimoEstadoIncrementar = HIGH;
int ultimoEstadoDecrementar = HIGH;
int ultimoEstadoReiniciar = HIGH;

void setup() {
  for (int i = 6; i < 14; i++) {
    pinMode(i, OUTPUT);
  }
  pinMode(DISPLAY_UNIDADES, OUTPUT);
  pinMode(DISPLAY_DECENAS, OUTPUT);
  pinMode(PULSADOR_INCREMENTAR, INPUT_PULLUP); 
  pinMode(PULSADOR_DECREMENTAR, INPUT_PULLUP); 
  pinMode(PULSADOR_REINICIAR, INPUT_PULLUP);
  apagarSegmentos(); 
}

void loop() {
  int estadoIncrementar = digitalRead(PULSADOR_INCREMENTAR);//estado actual del pulsador a cada vuelta
  int estadoDecrementar = digitalRead(PULSADOR_DECREMENTAR);//estado actual del pulsador a cada vuelta
  int estadoReiniciar = digitalRead(PULSADOR_REINICIAR);	//estado actual del pulsador a cada vuelta

  if (estadoIncrementar == LOW && ultimoEstadoIncrementar == HIGH) {
    contador++;
    if (contador > 99) {
      contador = 0;
    }
  }

  if (estadoDecrementar == LOW && ultimoEstadoDecrementar == HIGH) {
    contador--;
    if (contador < 0) {
      contador = 99;
    }
  }

  if (estadoReiniciar == LOW && ultimoEstadoReiniciar == HIGH) {
    contador = 0;
  }
  
//El estado anterior del pulsador pasa a tomar el estado actual antes hacer el siguiente loop
  ultimoEstadoIncrementar = estadoIncrementar; 
  ultimoEstadoDecrementar = estadoDecrementar;
  ultimoEstadoReiniciar = estadoReiniciar;

  mostrarNumero(contador % 10, DISPLAY_UNIDADES); // Para quedarme con la unidad
  delay(5); 
  mostrarNumero(contador / 10, DISPLAY_DECENAS); // Para quedarme con la decena
  delay(5); 
}

void apagarSegmentos() {
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}



void mostrarNumero(int numero, int display) 
{
  /*
  	Recibe un numero entero y un display
  */
  apagarSegmentos(); // Apaga todos los segmentos antes de mostrar el número

  // Configuracin del display activo
  if (display == DISPLAY_UNIDADES) {
    digitalWrite(DISPLAY_UNIDADES, HIGH);
    digitalWrite(DISPLAY_DECENAS, LOW);
  } else {
    digitalWrite(DISPLAY_UNIDADES, LOW);
    digitalWrite(DISPLAY_DECENAS, HIGH);
  }


  switch (numero) {
    case 0:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, LOW);
      break;
    case 1:
      digitalWrite(a, LOW);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      digitalWrite(g, LOW);
      break;
    case 2:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, LOW);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, LOW);
      digitalWrite(g, HIGH);
      break;
    case 3:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      digitalWrite(g, HIGH);
      break;
    case 4:
      digitalWrite(a, LOW);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
    case 5:
      digitalWrite(a, HIGH);
      digitalWrite(b, LOW);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, LOW);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
    case 6:
      digitalWrite(a, HIGH);
      digitalWrite(b, LOW);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
    case 7:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      digitalWrite(g, LOW);
      break;
    case 8:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
    case 9:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, LOW);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
  }
}




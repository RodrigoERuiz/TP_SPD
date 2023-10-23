#define a 10
#define b 11
#define c 13
#define d 7
#define e 6
#define f 9
#define g 8

#define giroDer A2
#define giroIzq A3

#define sensorTemp A4

#define DISPLAY_UNIDADES A0
#define DISPLAY_DECENAS A1

#define PULSADOR_INCREMENTAR 5 // Pin del pulsador para aumentar el contador
#define PULSADOR_DECREMENTAR 3 // Pin del pulsador para disminuir el contador
#define PULSADOR_REINICIAR 4   // Pin del pulsador para reiniciar el contador a cero
#define INTERRUPTOR 2 // Pin del interruptor deslizante

int contador = 0;
int ultimoEstadoIncrementar = HIGH;
int ultimoEstadoDecrementar = HIGH;
int ultimoEstadoReiniciar = HIGH;
int ultimoEstadoInterruptor = HIGH;

bool modoNumerosPrimos = false; // Variable para controlar el modo "Números Primos"

void setup() {
  for (int i = 6; i < 14; i++) {
    pinMode(i, OUTPUT);
  }
  pinMode(DISPLAY_UNIDADES, OUTPUT);
  pinMode(DISPLAY_DECENAS, OUTPUT);
  pinMode(PULSADOR_INCREMENTAR, INPUT_PULLUP); 
  pinMode(PULSADOR_DECREMENTAR, INPUT_PULLUP); 
  pinMode(PULSADOR_REINICIAR, INPUT_PULLUP);
  pinMode(INTERRUPTOR, INPUT_PULLUP);
  pinMode(giroDer, OUTPUT);
  pinMode(giroIzq, OUTPUT);
  digitalWrite(giroIzq,LOW);//declaro uno de los pines del motor en LOW para hacer pruebas en refactorizacion
}


void loop() {
  int estadoIncrementar = digitalRead(PULSADOR_INCREMENTAR);
  int estadoDecrementar = digitalRead(PULSADOR_DECREMENTAR);
  int estadoReiniciar = digitalRead(PULSADOR_REINICIAR);
  int estadoInterruptor = digitalRead(INTERRUPTOR);
  int temperaturaActual = map(analogRead(sensorTemp), 0, 1023, -50, 450);
  
  controlarTemperatura(temperaturaActual,giroDer);
  modoNumerosPrimos = verificarModo(estadoInterruptor);

  contador = controlarBotonIncremento(estadoIncrementar,ultimoEstadoIncrementar,modoNumerosPrimos,contador);
  contador = controlarBotonDecremento(estadoDecrementar,ultimoEstadoDecrementar,modoNumerosPrimos,contador);
  contador = controlarBotonReiniciar(estadoReiniciar,ultimoEstadoReiniciar,contador);

  ultimoEstadoIncrementar = estadoIncrementar;
  ultimoEstadoDecrementar = estadoDecrementar;
  ultimoEstadoReiniciar = estadoReiniciar;

  mostrarNumero(contador % 10, DISPLAY_UNIDADES);
  delay(5);
  mostrarNumero(contador / 10, DISPLAY_DECENAS);	
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

bool esPrimo(int n) {
  if (n <= 1) return false;
  if (n <= 3) return true;
  if (n % 2 == 0 || n % 3 == 0) return false;

  for (int i = 5; i * i <= n; i += 6) {
    if (n % i == 0 || n % (i + 2) == 0) return false;
  }
  return true;
}

int siguienteNumeroPrimo(int numero) {
  // Esta función encuentra el siguiente número primo mayor que el número dado.
  // Se utiliza en el modo "Números Primos."
  int siguiente = numero + 1;
  while (!esPrimo(siguiente)) {
    siguiente++;
  }
  return siguiente;
}

int numeroPrimoAnterior(int numero) {
  // Esta función encuentra el número primo anterior al número dado.
  // Se utiliza en el modo "Números Primos."
  if (numero <= 2) return -1; // No hay números primos antes de 2.
  int anterior = numero - 1;
  while (anterior >= 2 && !esPrimo(anterior)) {
    anterior--;
  }
  return anterior;
}

void controlarTemperatura(int temperatura,int pinMotor)
{
  if (temperatura > 30)
  {
    digitalWrite(pinMotor,HIGH);
  }
  else
  {
    digitalWrite(pinMotor,LOW);
  }
}

bool verificarModo(int interruptorDeslizable)
{
  int estadoInterruptor = digitalRead(interruptorDeslizable);
  if (estadoInterruptor == LOW) {
    // Cambiar al modo "Números Primos" si el interruptor está en la posición "0"
    modoNumerosPrimos = true;
  } else {
    // Cambiar al modo "Contador" si el interruptor está en la posición "1"
    modoNumerosPrimos = false;
  }
  return modoNumerosPrimos;
}

int controlarBotonIncremento(int estadoBotonActual,int ultimoEstadoBoton, bool modoNumerosPrimos, int contador)
{
  if (estadoBotonActual == LOW && ultimoEstadoBoton == HIGH && modoNumerosPrimos)
  {
      contador = siguienteNumeroPrimo(contador);
      if (contador == 0 || contador > 97) 
      {
        // Si volvemos a 0 o superamos 97, mostrar "00" y cambiar de nuevo a "Contador"
        contador = 2;
      }
  }
    else if(estadoBotonActual == LOW && ultimoEstadoBoton == HIGH && modoNumerosPrimos == false) 
    {
      // Modo "Contador"
      contador++;
      if (contador > 99) 
      {
        contador = 0;
      }
    }
  return contador;
}

int controlarBotonDecremento(int estadoBotonActual,int ultimoEstadoBoton, bool modoNumerosPrimos, int contador)
{
  if (estadoBotonActual == LOW && ultimoEstadoBoton == HIGH && modoNumerosPrimos)
  {
      contador = numeroPrimoAnterior(contador);
      if (contador < 2)
      {
        contador = 97;
      }
  }
    else if(estadoBotonActual == LOW && ultimoEstadoBoton == HIGH && modoNumerosPrimos == false) 
    {
      // Modo "Contador"
      contador--;
      if (contador < 0) {
        contador = 99;
      }
    }
  return contador;
}

int controlarBotonReiniciar(int estadoBotonActual,int ultimoEstadoBoton, int contador)
{
  if (estadoBotonActual == LOW && ultimoEstadoBoton == HIGH) {
    contador = 0;
  }
  return contador;
}

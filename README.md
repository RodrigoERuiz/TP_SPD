#    Primera Parte TP SPD
---

![portada](Imagenes/imagen_para_portadamd.jpg)

---




##    Contador con dos displays de 7 segmentos




![](https://github.com/RodrigoERuiz/TP_SPD/blob/main/Imagenes/contador_parte_%203.png)


##    Integrantes
* Enzo Jauregui
* Rodrigo Ruiz

##    Descripcion

Nuestro proyecto es un contador con dos displays de 7 segmentos que ofrece una solución sencilla y efectiva para llevar un seguimiento numérico de eventos y conteos de hasta dos dígitos. Permite a los usuarios aumentar, disminuir y restablecer el contador de manera intuitiva, siendo útil en una variedad de aplicaciones, desde el control de inventario hasta juegos y marcadores.
Como función adicional nuestro proyecto cuenta con un modo en el cual, el contador va incrementando o decrementando mostrando únicamente los números primos.

##    Caracteristicas especiales
* El proyecto se encuentra dotado con un sensor de temperatura y un fan conectado a un motor interno. El cual se encarga de controlar la temperatura del sistema
* Un sistema de retroiluminación de la botonera, que se encargará, por medio de una fotoresistencia, de encender un led de color blanco en situaciones en las que la iluminación ambiente no sea la suficiente para su visualización
##    Funciónes Principales:
###    mostrarNumero(int numero, int display) 


Esta función recibe uno de los dos displays con los que cuenta el sistema  y un numero entero (que se tratara de varible contador cuando la funcion sea llamada en el loop principal)
Se encargará de encender el display recibido y apagar el contrario. Ademas reprensetará el número pasado por parametro en dicho display
```csharp=
void mostrarNumero(int numero, int display) 
{
  /*
  	Recibe un numero entero y un display
  */
  apagarSegmentos(); // Apaga todos los segmentos antes de mostrar el número

  // Configuracion del display activo
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

```
##    Acalaración
La función mostrarNumero() será llamada dos veces por cada vuelta del loop.
Una vez recibiendo por parametro el display de las unidades y la otra el de las decenas.
Si bien en ambos llamados la función recibirá el mismo contador. En el llamado de las unidades a ese contador se le aplica el operador modulo de diez para quedarse efectivamente con la unidad del digito a representar.
Mientras que en el llamado de las decenas se le aplica una division por 10 para obtener la decena de la variable entera contador
Tambien colocamos un delay muy breve de 5 ms entre cada uno de los dos llamadas para lograr el efecto de que ambos estan encendidos en simultaneo todo el tiempo

```csharp
  mostrarNumero(contador % 10, DISPLAY_UNIDADES); // Para quedarme con la unidad
  delay(5); 
  mostrarNumero(contador / 10, DISPLAY_DECENAS); // Para quedarme con la decena
  delay(5); 
```
### verificarModo(int interruptorDeslizable)
Se encarga de analizar el estado del interruptor deslizable y retorna el estado actual
```csharp=
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
```
###    controlarBotonIncremento(int estadoBotonActual,int ultimoEstadoBoton, bool modoNumerosPrimos, int contador)
Recibe el estado anterior y actual del boton de incremento del contador, el modo actual y contador con el número a representar.
Se encarga de aumentar el contador según el modo que reciba por parámetro y lo retorna 

```csharp=
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
```



##    Link al proyecto

* [Proyecto en TinkerCAD](https://www.tinkercad.com/things/jGGSoJMYPpE?sharecode=Un-QczG93LEsTBqTcjV5HK3kDNdPSzT0n9gCBV5uKzE)
* [Repositorio GitHub](https://github.com/RodrigoERuiz/TP_SPD.git)

##    Referencias
* [Documentacion oficial Arduino](https://www.arduino.cc/reference/es/)
* [Documentación Markdown](https://markdown.es/sintaxis-markdown/#linkauto)





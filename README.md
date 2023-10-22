#    Primera Parte TP SPD
---

![portada](Imagenes/imagen_para_portadamd.jpg)

---




##    Contador con dos displays de 7 segmentos




![imagen_proyecto](Imagenes/contador_parte_3.png)


##    Integrantes
* Enzo Jauregui
* Rodrigo Ruiz

##    Descripcion

Nuestro proyecto es un contador con dos displays de 7 segmentos que ofrece una solución sencilla y efectiva para llevar un seguimiento numérico de eventos y conteos de hasta dos dígitos. Permite a los usuarios aumentar, disminuir y restablecer el contador de manera intuitiva, siendo útil en una variedad de aplicaciones, desde el control de ingreso a predios hasta marcadores de puntuación en eventos deportivos.

##    Función Principal
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
Mientras que en el llamado de las decenas se le aplica una division por 10 para obtener la decena de la variable entera contador.
Tambien colocamos un delay muy breve de 5 ms entre cada uno de los dos llamadas para lograr el efecto de que ambos estan encendidos en simultaneo todo el tiempo

```csharp=
  mostrarNumero(contador % 10, DISPLAY_UNIDADES); // Para quedarme con la unidad
  delay(5); 
  mostrarNumero(contador / 10, DISPLAY_DECENAS); // Para quedarme con la decena
  delay(5); 
```

##    Link al proyecto

* [Proyecto](https://www.tinkercad.com/things/6kChngbauJc)

##    Referencias
* [Documentacion oficial Arduino](https://www.arduino.cc/reference/es/)
* [Documentación Markdown](https://markdown.es/sintaxis-markdown/#linkauto)





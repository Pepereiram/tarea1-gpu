# Tarea 1
## Computación en GPU 
### José Pereira

Este proyecto implementa la clase `Matrix` que soporta operaciones
con matrices como la asignación, suma, resta, multiplicación,
transposición, y comparación, entre otras. La clase permite la
manipulación eficiente de matrices utilizando punteros inteligentes en C++.

## Requisitos

Este proyecto fue ejecutado con:

- **CMake** (Versión 3.16)
- **GoogleTest**
- **Compilador C++ de MinGW**

## Cómo ejecutar el proyecto


### 1. Abrir el proyecto en CLion

### 2. Cargar el proyecto en CMake

> Si no es detectado automáticamente, hacer clic derecho en CMakeLists.txt en la raíz y hacer clic en 'Load CMake Project' 

### 3. Ejecutar el ejemplo principal

1. Hacer clic derecho en el archivo test/test_matrix.cpp y seleccionar **Run**.
2. CLion mostrará una vista estructurada de los resultados de los tests, indicando qué pruebas pasaron o fallaron.

> Si no aparece la configuración `MatrixTests`, revisa que el archivo `tests/CMakeLists.txt` esté correctamente incluido y CMake haya sido recargado (botón **Reload CMake Project** en la esquina superior derecha si es necesario).


## Preguntas

### ¿Afecta en algo el tipo de dato de su matriz?
Sí, el tipo de dato afecta directamente el comportamiento de las operaciones.
Matrix usa `double`. Si se usara, por ejemplo, `int`, no se podrían representar
fracciones, y además habría que preocuparse de errores por desbordamiento
o resultados truncados.

### ¿Qué pasa si realiza operaciones de multiplicación con tipo de dato `integer` en vez de `double`?
Las operaciones con `int` truncan cualquier parte decimal del resultado,
perdiendo exactitud.

### Si se empezaran a usar números muy pequeños o muy grandes y principalmente números primos, ¿qué ocurre en términos de precisión?

Los números de tipo `double` tiene límites de precisión. Números muy pequeños
pueden redondearse a cero, y números muy grandes pueden sufrir pérdida de 
precisión en los dígitos menos significativos. Al usar números primos o 
valores con gran cantidad de cifras significativas, es más probable notar
errores acumulativos o inexactitudes en las operaciones, especialmente 
después de muchas iteraciones o cálculos compuestos como la multiplicación
de matrices.

### ¿Pueden haber problemas de precisión si se comparan dos matrices idénticas, pero con diferente tipo? (por ejemplo, `Matrix p1 == p2`)

Sí, ya que si las matrices tienen tipos distintos (por ejemplo, una con `int` 
y otra con `double`), aunque los valores representen "lo mismo",
las diferencias en la precisión pueden causar que la comparación falle.
Por ejemplo, `1` como entero y `1.0` como `double` pueden no ser iguales
a la larga (por como se manejan los double).
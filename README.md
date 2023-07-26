# Conway's Game Of Life

La misión es: utilizando únicamente la función point que preparamos, deben implementar el algoritmo de the game of life de Conway. 

El algoritmo de conway es muy simple:
- Una célula tiene 8 vecinos. Para nosotros, una célula es un pixel, los vecinos son los 8 píxeles alrededor. 
- La célula puede estar viva (pintada de blanco, digamos) o muerta (pintada de negro). Pueden usar otros colores, pero esta es la idea.
- Cada "turno" va a ser un frame para nosotros. Pueden hacer un delay entre cada frame para poder mejor visualizar su animación.
- La resolución queda a su discreción, pero les recomiendo trabajar en una resolución muy baja, de como 100x100, y cuando terminen hacer algunas pruebas a resoluciones altas. 

Las reglas son, para cada turno:
- Cualquier célula viva que tenga menos de dos vecinos vivos, muere. (underpopulation)
- Una célula viva que tenga dos o tres vecinos vivos, sobrevive. (survival)
- Cualquier célula viva que tenga más de tres vecinos vivos, muere. (overpopulation)
- Cualquier célula muerta que tenga exactamente tres vecinos vivos, vive. (reproduction) 

![](https://github.com/Sebas021210/Lab2-ConwaysGameOfLife/blob/396ad17ed4d3709221394a73fe1a0758b2f1d9f3/Conway's%20Game%20of%20Life.gif)

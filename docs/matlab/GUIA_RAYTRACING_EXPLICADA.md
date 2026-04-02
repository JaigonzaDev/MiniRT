# 🎨 Guía Completa de Raytracing - De Cero a Experto

> *Una explicación clara y desde cero sobre cómo funcionan las imágenes 3D generadas por computadora*

---

## 📖 Índice

1. [¿Qué es el Raytracing?](#qué-es-el-raytracing)
2. [Los 10 Conceptos Fundamentales](#los-10-conceptos-fundamentales)
3. [El Pipeline Completo](#el-pipeline-completo)
4. [Detalles Técnicos](#detalles-técnicos)
5. [De la Teoría a la Práctica](#de-la-teoría-a-la-práctica)

---

## 🌟 ¿Qué es el Raytracing?

Imagina que estás tomando una fotografía con tu móvil. La luz del sol rebota en los objetos, viaja hasta la cámara de tu teléfono, y ahí se forma la imagen. **El raytracing hace exactamente esto... pero al revés y en una computadora.**

### La Idea Básica

En lugar de simular TODA la luz que sale del sol (que sería imposible de calcular), el raytracing es más inteligente:

1. **Parte de tu ojo** (o la cámara virtual)
2. **Lanza un rayo imaginario** hacia la escena
3. **Ve qué golpea** ese rayo
4. **Calcula el color** de lo que golpeó
5. **Pinta un píxel** con ese color

Repites esto **millones de veces** (una por cada píxel de tu pantalla) y ¡tada! 🎉 tienes una imagen 3D fotorealista.

### ¿Por qué es Especial?

Antes, los videojuegos y películas usaban "trucos" para dibujar las sombras y reflejos. El raytracing **simula la física real de la luz**, por eso las imágenes se ven tan realistas. Es como la diferencia entre una foto y un dibujo a mano.

---

## 🎯 Los 10 Conceptos Fundamentales

Vamos a explicar cada concepto como si estuviéramos tomando un café juntos. Sin prisa, de manera clara.

---

### 1️⃣ El Rayo - Tu Primera Línea Mágica

**¿Qué es?**  
Un rayo es simplemente una **línea recta que parte de un punto** (tu ojo/cámara) y **va en una dirección específica**.

**La Analogía del Puntero Láser:**  
Imagina que tienes un puntero láser. Lo enciendes desde tu mano (punto de origen) y apuntas hacia la pared (dirección). Ese haz de luz roja es exactamente lo que es un rayo en raytracing.

**¿Cómo se describe matemáticamente?**

```
Rayo(t) = Origen + t × Dirección
```

Donde:
- **Origen**: Tu posición (por ejemplo: `[0, 0, 0]`)
- **Dirección**: Hacia dónde apuntas (por ejemplo: `[1, 0, 0]` = hacia la derecha)
- **t**: Distancia (cuántos metros/unidades avanzas)

**Ejemplo Práctico:**  
Si estás en `[0, 0, 0]` y apuntas hacia `[1, 0, 0]`:
- Con `t=0` → Estás en `[0, 0, 0]` (tu posición)
- Con `t=1` → Estás en `[1, 0, 0]` (1 metro adelante)
- Con `t=5` → Estás en `[5, 0, 0]` (5 metros adelante)

**💡 Lo que debes recordar:**  
Un rayo es tu herramienta para "tocar" objetos en la escena. Es como si extiendes un palo infinitamente largo para ver qué tocas.

---

### 2️⃣ Intersección - ¿Dónde Toca el Rayo?

**¿Qué es?**  
Necesitas saber **en qué punto exacto** tu rayo golpea un objeto. Esto requiere resolver una ecuación matemática.

**La Analogía del Dardo:**  
Imagina que lanzas un dardo (el rayo) hacia un globo (una esfera). ¿En qué punto del globo se clava el dardo? Eso es la intersección.

**¿Cómo se Calcula para una Esfera?**

Una esfera se define como "todos los puntos que están a cierta distancia (radio) de un centro". Matemáticamente:

```
|Punto - Centro| = Radio
```

Cuando sustituimos nuestro rayo en esta ecuación, obtenemos:

```
|Origen + t×Dirección - Centro| = Radio
```

Esto se convierte en una **ecuación cuadrática** (como las que hacías en el instituto):

```
a·t² + b·t + c = 0
```

**El Discriminante - La Clave:**

El "discriminante" (Δ = b² - 4ac) te dice:

- **Δ < 0**: El rayo **NO toca** la esfera (pasa de largo) ❌
- **Δ = 0**: El rayo **roza** la esfera (tangente) 👉⚪
- **Δ > 0**: El rayo **atraviesa** la esfera (dos puntos: entrada y salida) ✅

**Ejemplo Visual:**
```
     Rayo →
         
  ❌  →  →  →     ⚪    (No toca)
  
  ✅  →  →  ⚪→  →       (Atraviesa)
          ↑     ↑
       entrada salida
```

**💡 Lo que debes recordar:**  
Resolver una intersección es como resolver un problema de geometría: "Si lanzo algo desde aquí en esta dirección, ¿dónde pega?"

---

### 3️⃣ Oclusión - ¿Cuál Objeto se Ve?

**¿Qué es?**  
Cuando tu rayo atraviesa VARIOS objetos, solo ves el **más cercano** a ti. Los demás quedan ocultos (ocluidos).

**La Analogía de los Árboles del Bosque:**  
Estás en un bosque mirando hacia adelante. Ves el primer árbol claramente, pero no ves los árboles que están detrás de él. Aunque hay 50 árboles en línea, solo percibes el primero.

**¿Cómo Funciona el Algoritmo?**

```
1. Empieza con: distancia_mínima = infinito

2. Para cada objeto en la escena:
   - Calcula dónde intersecta el rayo
   - Si intersecta Y está más cerca que distancia_mínima:
     * Actualiza distancia_mínima
     * Guarda "este es el objeto visible"

3. El objeto con menor distancia es el que VEMOS
```

**Ejemplo Numérico:**
```
Esfera Roja:   t = 3.2 metros  ← MÁS CERCA (visible)
Esfera Verde:  t = 5.8 metros  (oculta detrás de la roja)
Esfera Azul:   t = 8.1 metros  (oculta detrás de ambas)

Resultado: Solo dibujamos la roja ✅
```

**💡 Lo que debes recordar:**  
En la vida real, no ves a través de las cosas. El ordenador tampoco: solo dibuja lo primero que "tocas" con el rayo.

---

### 4️⃣ Normales - El "Arriba" de Cada Superficie

**¿Qué es?**  
La **normal** es un vector (flecha) que apunta **perpendicular** a una superficie. Es como decir "esta es la dirección que sale de este punto".

**La Analogía del Clavo en la Pared:**  
Si clavas un clavo en una pared, el clavo apunta perpendicular a la pared. Esa dirección es la "normal" de ese punto de la pared.

**¿Para Qué Sirve?**  
La normal es **CRÍTICA** para calcular iluminación. Te dice:
- En qué dirección "mira" la superficie
- Cómo la luz rebota en ella
- Si algo está "de frente" o "de espaldas" a la luz

**¿Cómo se Calcula?**

**Para una Esfera:**
```
Normal = (Punto en superficie - Centro de esfera) / Radio
```

Es decir, la flecha va desde el centro hacia afuera, normalizada (longitud = 1).

**Para un Plano:**
```
Normal = Un vector fijo perpendicular al plano
```

Por ejemplo, un suelo horizontal tiene normal `[0, 1, 0]` (apunta hacia arriba).

**Ejemplo Visual:**
```
       ↑ Normal
       |
   ────●──── Superficie
       
El punto ● tiene una flecha ↑ saliendo perpendicular
```

**💡 Lo que debes recordar:**  
La normal es la "cara" de la superficie. Te dice hacia dónde "mira" ese punto.

---

### 5️⃣ Iluminación Difusa - El Brillo Básico

**¿Qué es?**  
Es calcular **qué tan iluminado** está un punto según el ángulo de la luz. Se llama "difusa" porque la luz se dispersa en todas direcciones (como una pared mate).

**La Analogía del Bronceado:**  
Si tomas el sol estando acostado boca arriba (perpendicular al sol), te bronceas mucho. Si estás de costado (paralelo), apenas te bronceas. El ángulo importa.

**La Ley de Lambert:**

```
Intensidad = max(0, Normal · Luz)
```

Donde:
- **Normal**: Dirección de la superficie (↑)
- **Luz**: Dirección hacia la fuente de luz (→)
- **·**: Producto escalar (mide el ángulo entre vectores)

**Interpretación del Resultado:**

| Valor N·L | Ángulo | Significado | Brillo |
|-----------|--------|-------------|--------|
| **1.0** | 0° | Luz perpendicular | Máximo ☀️ |
| **0.5** | 60° | Luz inclinada | Medio 🌤️ |
| **0.0** | 90° | Luz paralela | Nada 🌑 |
| **< 0** | >90° | Luz por detrás | Oscuro ⬛ |

**Ejemplo Visual:**
```
        Luz ☀️
         ↓
    ━━━━━━━━━━  ← Superficie horizontal
    Brillo: 100% (N·L = 1)

        Luz ☀️
         ↙
      ╱╱╱╱╱  ← Superficie inclinada
    Brillo: 50% (N·L ≈ 0.5)
    
        Luz ☀️
           
      ██████  ← Superficie de espaldas
    Brillo: 0% (N·L < 0)
```

**💡 Lo que debes recordar:**  
Cuanto más perpendicular sea la luz a la superficie, más brillante se ve. Es física pura: así funciona en la vida real.

---

### 6️⃣ Sombras - Bloqueando la Luz

**¿Qué es?**  
Una sombra ocurre cuando **algo bloquea el camino** entre un punto y la fuente de luz.

**La Analogía de la Mano y la Linterna:**  
Pones tu mano entre una linterna y la pared. Tu mano bloquea la luz, creando una sombra en la pared. Es exactamente esto.

**El Algoritmo de Shadow Rays:**

```
1. Tienes un punto que quieres iluminar
2. Lanzas un "shadow ray" (rayo de sombra) desde ese punto hacia la luz
3. Si el rayo golpea ALGO antes de llegar a la luz:
   → Hay un objeto en medio → SOMBRA ⚫
4. Si el rayo llega a la luz sin obstáculos:
   → Camino libre → ILUMINADO ☀️
```

**Ejemplo Paso a Paso:**

Tienes un punto P en el suelo y una esfera flotando entre P y la luz:

```
    Luz ☀️
      |
      | Shadow Ray
      ↓
     ⚪ ← Esfera (BLOQUEA)
      ✗
      
    ▪️ Punto P
    
Resultado: P está en SOMBRA
```

Ahora sin la esfera:

```
    Luz ☀️
      ↑
      | Shadow Ray (libre)
      |
      
    ▪️ Punto P
    
Resultado: P está ILUMINADO
```

**Detalle Técnico Importante - Evitar Auto-Intersección:**

Cuando lanzas el shadow ray desde el punto de impacto, debes empezar **ligeramente separado** de la superficie (por ejemplo, 0.001 unidades), sino el rayo intersectaría la propia superficie donde estás parado.

```python
shadow_ray_origin = punto_impacto + 0.001 * normal
```

**💡 Lo que debes recordar:**  
Las sombras son checkers: "¿Hay algo entre yo y la luz? Si sí → sombra. Si no → luz."

---

### 7️⃣ El Píxel Completo - Juntando Todo

**¿Qué es?**  
Ahora combinamos TODOS los conceptos anteriores para calcular el color de **un solo píxel** de la imagen.

**El Pipeline Completo:**

```
PASO 1: Lanzar Rayo Primario
  └─> Desde la cámara, a través del píxel

PASO 2: Buscar Intersección Más Cercana
  └─> ¿Qué objeto golpea? → Plano, Esfera 1, Esfera 2...
  
PASO 3: Calcular Normal en el Punto
  └─> ¿Hacia dónde "mira" la superficie?
  
PASO 4: Lanzar Shadow Ray
  └─> ¿Está en sombra o iluminado?
  
PASO 5: Calcular Color Final
  └─> Color = Luz_Ambiental + (¿sombra? NO : Luz_Difusa)
  
PASO 6: Devolver Color → Pintar el Píxel
```

**Ejemplo Numérico Completo:**

```
Píxel (200, 150) de una imagen 800x600:

1. Rayo: origen=[0,1,-5], dirección=[0.1, 0, 0.8]
2. Intersección: Esfera roja en t=3.2
3. Punto de impacto: [0.32, 1, -2.44]
4. Normal: [0.32, 0, 0.56]  (unitario)
5. Shadow ray: hacia luz [5, 10, -5]
   → NO bloqueado → Iluminado ✅
6. Iluminación:
   - Ambiente: [0.1, 0.02, 0.02]
   - Difusa: [0.8, 0.16, 0.16]
   - Total: [0.9, 0.18, 0.18] → Color ROJO
7. Píxel (200,150) = ROJO
```

**💡 Lo que debes recordar:**  
Un píxel es el resultado de seguir TODO el proceso. Parece complicado, pero es siempre el mismo proceso mecanizado.

---

### 8️⃣ Renderizando una Línea - Escalando

**¿Qué es?**  
En lugar de calcular un píxel, calculamos **200 píxeles seguidos** (una línea horizontal).

**La Realidad:**  
Repetimos el proceso del píxel 200 veces, cambiando solo la dirección del rayo para cada píxel:

```
Píxel 0:   Rayo apunta a [-1.0, 0, 0]
Píxel 1:   Rayo apunta a [-0.99, 0, 0]
Píxel 2:   Rayo apunta a [-0.98, 0, 0]
...
Píxel 100: Rayo apunta a [0, 0, 0]    (centro)
...
Píxel 199: Rayo apunta a [1.0, 0, 0]
```

**Análisis del Resultado:**

Si graficas los colores RGB de cada píxel, verás:
- **Picos de azul**: Píxeles viendo el cielo (sin intersección)
- **Picos de rojo**: Píxeles viendo esfera roja
- **Picos de verde**: Píxeles viendo esfera verde

Es como un "electrocardiograma" de lo que ve cada píxel.

**💡 Lo que debes recordar:**  
Una línea es solo repetir el proceso píxel a píxel. Tedioso para un humano, trivial para un ordenador.

---

### 9️⃣ Escena Completa - La Imagen Final

**¿Qué es?**  
Renderizamos **TODOS** los píxeles de la imagen (por ejemplo, 400×300 = 120,000 píxeles).

**El Doble Bucle:**

```
Para cada fila Y (de 0 a 300):
  Para cada columna X (de 0 a 400):
    Color = CalcularPíxel(X, Y)
    PintarPíxel(X, Y, Color)
```

Simple, ¿verdad? Pero ejecutar esto 120,000 veces lleva tiempo.

**Estadísticas Típicas:**

```
Resolución: 400×300 píxeles
Píxeles totales: 120,000
Tiempo: ~10-15 segundos en MATLAB
Velocidad: ~8,000 píxeles/segundo

Para comparar:
  - Tu GPU moderna: ~100,000,000 px/s
  - Pixar/Películas: ~0.01 px/s (horas por frame)
```

**¿Por qué tan lento en MATLAB?**  
No está optimizado. En C (como tu miniRT), es **100x más rápido**. Con GPU, **10,000x más rápido**.

**💡 Lo que debes recordar:**  
Una escena completa es fuerza bruta: repetir millones de veces lo mismo. Por eso las GPUs (que hacen miles de cálculos en paralelo) son tan importantes.

---

### 🔟 Efectos Avanzados - El Siguiente Nivel

Una vez que dominas lo básico, puedes añadir:

#### **a) Iluminación Especular (Brillos)**

Como el brillo en una bola de billar o un espejo.

```
Intensidad_Especular = (Rayo_Reflejado · Dirección_Cámara)^shininess
```

Donde `shininess` controla qué tan "pulido" es el material:
- `shininess = 5`: Plástico mate
- `shininess = 50`: Metal pulido
- `shininess = 200`: Espejo perfecto

#### **b) Texturas Procedurales**

En lugar de color sólido, calculas patrones matemáticos:

```
Patrón_Ajedrez:
  celda_x = floor(punto.x * escala)
  celda_z = floor(punto.z * escala)
  
  si (celda_x + celda_z) es par:
    color = BLANCO
  sino:
    color = NEGRO
```

Esto crea el efecto de tablero de ajedrez sin necesitar una imagen.

#### **c) Reflexiones**

Cuando el rayo golpea un espejo, lanzas un **segundo rayo** en la dirección reflejada:

```
Dirección_Reflejada = Dirección - 2×(Dirección·Normal)×Normal
```

Y llamas recursivamente al proceso de raytracing con este nuevo rayo.

#### **d) Refracciones (Vidrio)**

Cuando el rayo atraviesa vidrio, se **dobla** según la Ley de Snell:

```
n₁ × sin(θ₁) = n₂ × sin(θ₂)
```

Donde:
- n₁ = índice de refracción del aire (≈1.0)
- n₂ = índice de refracción del material (vidrio≈1.5, agua≈1.33)

#### **e) Corrección Gamma**

Las pantallas no muestran colores linealmente. La corrección gamma ajusta esto:

```
Color_Final = Color_Calculado^(1/2.2)
```

Esto hace que la imagen se vea más natural en tu monitor.

**💡 Lo que debes recordar:**  
Los efectos avanzados son extensiones del proceso básico. Algunos requieren más rayos, otros solo más matemáticas.

---

## 🔄 El Pipeline Completo - Resumen Visual

```
┌─────────────────────────────────────────────────────────┐
│                    INICIO: Píxel (x,y)                  │
└────────────────────┬────────────────────────────────────┘
                     │
                     ▼
┌─────────────────────────────────────────────────────────┐
│  1️⃣ GENERAR RAYO                                        │
│     Rayo = Cámara → Píxel                               │
└────────────────────┬────────────────────────────────────┘
                     │
                     ▼
┌─────────────────────────────────────────────────────────┐
│  2️⃣ BUSCAR INTERSECCIÓN MÁS CERCANA                     │
│     Para cada objeto: calcular t                        │
│     Elegir el menor t > 0                               │
└────────────────────┬────────────────────────────────────┘
                     │
                     ▼
            ¿Hay intersección?
                     │
        ┌────────────┴────────────┐
        │ NO                      │ SÍ
        ▼                         ▼
┌───────────────┐    ┌────────────────────────────────┐
│ 3️⃣ CIELO      │    │ 4️⃣ CALCULAR NORMAL              │
│ Color=Azul    │    │   Normal = func(objeto, punto) │
└───────┬───────┘    └────────────┬───────────────────┘
        │                         │
        │                         ▼
        │            ┌────────────────────────────────┐
        │            │ 5️⃣ SHADOW RAY                   │
        │            │   ¿Bloqueado camino a luz?     │
        │            └────────────┬───────────────────┘
        │                         │
        │                         ▼
        │            ┌────────────────────────────────┐
        │            │ 6️⃣ CALCULAR ILUMINACIÓN         │
        │            │   Ambiente + Difusa + Especular│
        │            └────────────┬───────────────────┘
        │                         │
        └─────────────────────────┘
                     │
                     ▼
┌─────────────────────────────────────────────────────────┐
│             7️⃣ RETORNAR COLOR → PINTAR PÍXEL             │
└─────────────────────────────────────────────────────────┘
```

---

## 🔬 Detalles Técnicos

### Optimizaciones Comunes

#### **1. Estructura de Aceleración (BVH - Bounding Volume Hierarchy)**

En lugar de comprobar intersección con TODOS los objetos:

```
❌ Método ingenuo:
  Para 1000 objetos → 1000 comprobaciones por rayo

✅ Con BVH:
  Para 1000 objetos → ~10 comprobaciones por rayo
```

Se agrupan objetos en cajas jerárquicas y se descartan grupos completos rápidamente.

#### **2. Multi-Threading**

Los píxeles son independientes entre sí. Se pueden calcular en paralelo:

```
1 thread:  10,000 píxeles/segundo
4 threads: 40,000 píxeles/segundo (casi lineal)
```

Tu miniRT usa 4 threads para aprovechar los 4 núcleos de tu CPU.

#### **3. Importance Sampling**

En lugar de lanzar rayos en direcciones aleatorias, se priorizan direcciones hacia las luces:

```
❌ 100 rayos aleatorios → 10 llegan a la luz → Ruidoso
✅ 100 rayos hacia luces → 80 llegan a la luz → Limpio
```

#### **4. Path Tracing vs Raytracing Clásico**

**Raytracing Clásico (tu proyecto):**
- Shadow rays explícitos hacia luces
- Reflexiones/refracciones recursivas
- Rápido, pero solo luz directa

**Path Tracing (Pixar/Disney):**
- Rayos en direcciones aleatorias
- Simula rebotes infinitos de luz
- Lento, pero físicamente correcto (luz indirecta)

---

## 🎓 De la Teoría a la Práctica

### Tu Proyecto miniRT

Tu código en C implementa exactamente estos conceptos:

| Concepto | Archivo en miniRT |
|----------|-------------------|
| **Rayo** | `src/trace/mrt_trace.c` → función `trace()` |
| **Intersección Esfera** | `src/trace/mrt_trace_obj_intersect_1.c` → `intersect_sphere()` |
| **Intersección Plano** | `src/trace/mrt_trace_obj_intersect_1.c` → `intersect_plane()` |
| **Oclusión** | `src/trace/mrt_trace.c` → `calc_hit()` (busca menor t) |
| **Normales** | `src/trace/mrt_trace_obj_normal_1.c` → funciones `normal_*()` |
| **Iluminación** | `src/trace/mrt_trace_diffuse.c` → `diffuse_*()` |
| **Renderizado** | `src/graphic/mrt_graphic_render.c` → `draw_thread()` |

### Comparación MATLAB vs C

```
MATLAB (raytracing_interactivo.m):
  - Educativo y visual
  - ~8,000 píxeles/segundo
  - Código legible y comentado
  
C (miniRT):
  - Producción y optimizado
  - ~800,000 píxeles/segundo (100x más rápido)
  - Código eficiente con multi-threading
```

### Ejercicios Sugeridos

#### **Nivel Principiante:**
1. Cambia la posición de la cámara en MATLAB
2. Añade una esfera de color diferente
3. Mueve la luz y observa cómo cambian las sombras

#### **Nivel Intermedio:**
4. Implementa iluminación especular (brillos)
5. Crea texturas procedurales (rayas, lunares)
6. Añade múltiples luces

#### **Nivel Avanzado:**
7. Implementa reflexiones recursivas
8. Añade refracción para vidrio/agua
9. Implementa anti-aliasing (múltiples samples por píxel)

---

## 📚 Recursos Adicionales

### Libros Recomendados
- **"Ray Tracing in One Weekend"** by Peter Shirley (gratuito online)
- **"Physically Based Rendering"** by Pharr & Humphreys (la biblia)

### Conceptos para Profundizar
- **Monte Carlo Path Tracing**: Simulación estocástica de luz
- **Bidirectional Path Tracing**: Rayos desde cámara Y desde luz
- **Photon Mapping**: Pre-cálculo de luz indirecta
- **Denoising**: Algoritmos para limpiar ruido en pocas muestras

### Aplicaciones Reales
- **Cine**: Pixar, Disney, ILM usan path tracing
- **Videojuegos**: Minecraft RTX, Cyberpunk 2077 (raytracing híbrido)
- **Arquitectura**: Renders fotorealistas de edificios
- **Diseño Industrial**: Visualización de productos

---

## 🎯 Conclusión

El raytracing no es magia. Es **física + geometría + mucha repetición**.

Los conceptos clave son:
1. **Rayos**: Líneas desde la cámara
2. **Intersecciones**: ¿Dónde golpean los objetos?
3. **Iluminación**: ¿Qué tan brillante?
4. **Sombras**: ¿Algo bloquea la luz?
5. **Repetición**: Hacer esto millones de veces

Con paciencia y práctica, pasarás de entender la teoría a crear tus propias escenas 3D impresionantes.

---

## 💬 Preguntas Frecuentes

### ¿Por qué mi renderizado es lento?
Es normal. El raytracing hace MUCHOS cálculos. Una imagen de 800×600 con 100 samples/píxel = 48 millones de rayos. En MATLAB, esto puede tardar minutos.

### ¿Diferencia entre raytracing y rasterización?
- **Rasterización** (videojuegos): Proyecta triángulos a la pantalla. Rápido pero "tramposo" con reflejos/sombras.
- **Raytracing**: Simula física real. Lento pero preciso.

### ¿Puedo hacer raytracing en tiempo real?
Con GPUs modernas (RTX 3080+) sí, pero con trucos:
- Menos rayos por píxel
- Denoising con IA
- Raytracing híbrido (solo para ciertas cosas)

### ¿Qué es el "path tracing"?
Es raytracing "de verdad": los rayos rebotan aleatoriamente simulando luz indirecta. Es lo que usan Pixar/Disney. Requiere miles de muestras para imagen limpia.

---

**¡Felicidades!** 🎉 Ahora entiendes los fundamentos del raytracing. Los scripts de MATLAB te permiten experimentar, y tu proyecto miniRT te da el poder de hacerlo rápido en C.

**Siguiente paso:** Abre `raytracing_interactivo.m` y ejecuta las secciones una por una. Verás estos conceptos en acción.


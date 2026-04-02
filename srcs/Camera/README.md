# Camera Module

Este módulo contiene la implementación de la cámara y el viewport para el proyecto MiniRT.

## Estructuras

### t_camera
Describe la posición de la cámara en la escena:
- `center`: Posición de la cámara
- `normal`: Dirección hacia donde apunta la cámara (normalizado)
- `fov`: Campo de visión (Field Of View) en grados

### t_ray
Representa un rayo en la escena:
- `origin`: Origen del rayo
- `direction`: Dirección del rayo (normalizado)

### t_viewport
Datos del viewport (lo que la cámara puede ver):
- `up`: Vector arriba del viewport
- `right`: Vector derecho del viewport
- `hview`: Altura del viewport
- `wview`: Ancho del viewport

## Funciones

### init_viewport
```c
void init_viewport(t_camera *camera, t_viewport *viewport);
```
Inicializa el viewport basado en la cámara. El viewport está soportado por 3 vectores: up, right y forward. Juntos, estos vectores pueden retornar cualquier punto en el plano.

### canvas_to_viewport
```c
t_vector canvas_to_viewport(int x, int y);
```
Convierte coordenadas de píxel (0 a width-1, 0 a height-1) a factores de viewport (entre -1 y 1). Estos factores se usan con los vectores del viewport para acceder a cualquier punto.

### cast_ray
```c
t_ray cast_ray(t_camera *camera, t_viewport *viewport, t_vector factors);
```
Lanza un rayo infinito en el espacio desde la cámara con la dirección de uno de los puntos del viewport.

### ray_at
```c
t_vector ray_at(t_ray *ray, double t);
```
Retorna el punto en el rayo dado con t vectores de dirección. La ecuación de un rayo es: P = O + tD

Donde:
- P: Punto a t vectores de dirección
- O: Origen del rayo
- t: Factor de distancia
- D: Dirección del rayo

## Macros importantes

- `PI`: 3.1415926535
- `RADIANS(deg)`: Convierte grados a radianes
- `WIDTH`: Ancho de la ventana (1920 en Linux, 1440 en macOS)
- `HEIGHT`: Alto de la ventana (calculado con ratio 16:9)
- `RATIO`: Ratio de aspecto (16:9)
- `UPGUIDE`: Vector guía "arriba" (0, 1, 0)

## Uso

1. Crear una estructura `t_camera` con la posición, dirección y FOV
2. Crear una estructura `t_viewport` vacía
3. Llamar a `init_viewport()` para inicializar el viewport
4. Para cada píxel en la pantalla:
   - Llamar a `canvas_to_viewport()` para obtener los factores
   - Llamar a `cast_ray()` para obtener el rayo desde la cámara
   - Usar el rayo para calcular intersecciones y renderizar

## Ejemplo

```c
t_camera camera;
t_viewport viewport;
t_ray ray;

// Configurar cámara
camera.center = (t_vector){0, 0, -20};
camera.normal = (t_vector){0, 0, 1};
camera.fov = 70;

// Inicializar viewport
init_viewport(&camera, &viewport);

// Para cada píxel
for (int y = 0; y < HEIGHT; y++)
{
    for (int x = 0; x < WIDTH; x++)
    {
        t_vector factors = canvas_to_viewport(x, y);
        ray = cast_ray(&camera, &viewport, factors);
        // Usar ray para intersección y renderizado
    }
}
```

## Código basado en

Este módulo está basado en el proyecto de referencia en `/refe/mandatory/sources/renderer/ray.c` y las estructuras en `/refe/mandatory/includes/structs.h`.

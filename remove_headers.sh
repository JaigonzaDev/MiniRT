#!/bin/bash

# Encuentra todos los archivos .c y .h dentro del directorio srcs/ e include/ y sus subdirectorios
# y elimina las primeras 11 líneas de cada uno.

find srcs include -type f \( -name "*.c" -o -name "*.h" \) | while read -r file; do
    # Usamos sed para borrar desde la línea 1 hasta la 11
    sed -i '1,11d' "$file"
    echo "Header eliminado de $file"
done

echo "¡Completado!"

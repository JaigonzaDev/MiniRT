#!/bin/bash

# Script de test para miniRT
# Compila, ejecuta y verifica el resultado

set -e

echo "================================"
echo "   miniRT - Test Automático"
echo "================================"
echo ""

# Colores para output
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Archivo de test
TEST_FILE="${1:-tests/test1.rt}"
OUTPUT_FILE="output_new.ppm"

# Compilar
echo "📦 Compilando..."
if make; then
    echo -e "${GREEN}✓ Compilación exitosa${NC}"
else
    echo -e "${RED}✗ Error en compilación${NC}"
    exit 1
fi
echo ""

# Limpiar archivo anterior
rm -f "$OUTPUT_FILE"

# Ejecutar
echo "🚀 Ejecutando miniRT con $TEST_FILE..."
if timeout 30 ./bin/miniRT "$TEST_FILE" > /dev/null 2>&1; then
    echo -e "${GREEN}✓ Ejecución completada${NC}"
else
    echo -e "${YELLOW}⚠ Ejecución terminada (timeout o error)${NC}"
fi
echo ""

# Verificar resultado
if [ -f "$OUTPUT_FILE" ]; then
    echo "📊 Resultado:"
    echo "   Archivo: $OUTPUT_FILE"
    ls -lh "$OUTPUT_FILE" | awk '{print "   Tamaño: " $5}'
    
    # Verificar formato
    file "$OUTPUT_FILE" | grep -q "Netpbm" && echo -e "   ${GREEN}✓ Formato PPM válido${NC}"
    
    echo ""
    echo "🎨 Muestra de pixels (primeros con color):"
    od -An -t u1 "$OUTPUT_FILE" | grep -m 3 "204\|205\|206\|207" | head -3
    
    echo ""
    
    # Intentar convertir a PNG si existe ImageMagick
    if command -v convert &> /dev/null; then
        echo "🖼️  Convirtiendo a PNG..."
        if convert "$OUTPUT_FILE" "${OUTPUT_FILE%.ppm}.png" 2>/dev/null; then
            echo -e "${GREEN}✓ PNG generado: ${OUTPUT_FILE%.ppm}.png${NC}"
        else
            echo -e "${YELLOW}⚠ No se pudo convertir a PNG${NC}"
        fi
    fi
else
    echo -e "${RED}✗ No se generó el archivo de salida${NC}"
    exit 1
fi

echo ""
echo "================================"
echo -e "${GREEN}✓ Test completado${NC}"
echo "================================"

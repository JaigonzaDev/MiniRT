% ========================================================================
% RAYTRACING INTERACTIVO - Tutorial Paso a Paso
% ========================================================================
% Este script está diseñado para ejecutarse SECCIÓN POR SECCIÓN
% 
% CÓMO USAR:
% 1. Haz clic en cualquier línea de una sección
% 2. Presiona Ctrl+Enter (Cmd+Enter en Mac) para ejecutar solo esa sección
% 3. Observa los resultados antes de pasar a la siguiente
% 4. Modifica parámetros y vuelve a ejecutar para experimentar
%
% SECCIONES:
%   1. Inicialización
%   2. PARTE 1: El Rayo - Concepto Básico
%   3. PARTE 2: Primera Intersección - Rayo vs Esfera
%   4. PARTE 3: Múltiples Objetos - ¿Cuál se ve?
%   5. PARTE 4: Calculando Normales
%   6. PARTE 5: Iluminación Simple
%   7. PARTE 6: Sombras - Shadow Rays
%   8. PARTE 7: Renderizado de UN Píxel Completo
%   9. PARTE 8: Renderizado de UNA Línea
%  10. PARTE 9: Escena Completa Simplificada
%  11. PARTE 10: Escena Final con Todos los Efectos
% ========================================================================

%% ========================================================================
%  SECCIÓN 1: INICIALIZACIÓN
%  ========================================================================
%  Ejecuta esta sección PRIMERO para limpiar el workspace
% ========================================================================
clear all; close all; clc;

fprintf('\n');
fprintf('╔════════════════════════════════════════════════════════════════╗\n');
fprintf('║     RAYTRACING INTERACTIVO - Tutorial Paso a Paso             ║\n');
fprintf('╚════════════════════════════════════════════════════════════════╝\n');
fprintf('\n');
fprintf('✓ Workspace limpiado\n');
fprintf('✓ Listo para empezar\n\n');
fprintf('→ Ejecuta la siguiente sección (Ctrl+Enter) para continuar\n\n');

%% ========================================================================
%  PARTE 1: EL RAYO - CONCEPTO BÁSICO
%  ========================================================================
%  El rayo es la base del raytracing
%  Ecuación: Ray(t) = Origin + t * Direction
% ========================================================================

fprintf('\n━━━ PARTE 1: El Rayo ━━━\n\n');

% 🎯 PARÁMETROS MODIFICABLES
ray_origin = [0, 0, 0];           % Punto de inicio (cámara)
ray_target = [5, 2, 3];           % Hacia dónde apunta
% ━━━━━━━━━━━━━━━━━━━━━━━━━

% Calcular dirección (normalizada)
ray_direction = ray_target - ray_origin;
ray_direction = ray_direction / norm(ray_direction);

fprintf('📍 Origen del rayo: [%.1f, %.1f, %.1f]\n', ray_origin);
fprintf('🎯 Dirección: [%.2f, %.2f, %.2f]\n', ray_direction);
fprintf('\n');

% Visualización 3D
figure('Name', 'PARTE 1: El Rayo', 'Position', [100 100 900 700]);

% Generar puntos a lo largo del rayo
t_values = linspace(0, 8, 50);
ray_points = zeros(length(t_values), 3);
for i = 1:length(t_values)
    ray_points(i,:) = ray_origin + t_values(i) * ray_direction;
end

% Graficar el rayo
plot3(ray_points(:,1), ray_points(:,2), ray_points(:,3), ...
      'b-', 'LineWidth', 3);
hold on;

% Marcar el origen
plot3(ray_origin(1), ray_origin(2), ray_origin(3), ...
      'ro', 'MarkerSize', 15, 'MarkerFaceColor', 'r');

% Mostrar algunos puntos específicos
t_samples = [0, 2, 4, 6, 8];
colors = ['r', 'g', 'b', 'm', 'c'];
for i = 1:length(t_samples)
    t = t_samples(i);
    point = ray_origin + t * ray_direction;
    plot3(point(1), point(2), point(3), ...
          [colors(i) 'o'], 'MarkerSize', 10, 'MarkerFaceColor', colors(i));
    text(point(1)+0.2, point(2)+0.2, point(3)+0.2, ...
         sprintf('t=%.0f', t), 'FontSize', 11, 'FontWeight', 'bold');
end

grid on;
xlabel('X', 'FontSize', 12, 'FontWeight', 'bold');
ylabel('Y', 'FontSize', 12, 'FontWeight', 'bold');
zlabel('Z', 'FontSize', 12, 'FontWeight', 'bold');
title('Rayo: P(t) = Origin + t × Direction', 'FontSize', 14, 'FontWeight', 'bold');
legend('Trayectoria del rayo', 'Origen (cámara)', 'Location', 'best');
view(45, 25);
axis equal;
grid on;

% Añadir explicación matemática en la figura
annotation('textbox', [0.02 0.75 0.35 0.20], ...
    'String', {['ECUACIÓN PARAMÉTRICA DEL RAYO:'], ...
               '', ...
               'P(t) = Origin + t · Direction', ...
               '', ...
               'Donde:', ...
               '  • t ∈ [0, ∞) es el parámetro', ...
               '  • Origin = punto inicial (cámara)', ...
               '  • Direction = vector unitario', ...
               '', ...
               sprintf('Origin = [%.1f, %.1f, %.1f]', ray_origin), ...
               sprintf('Dir = [%.2f, %.2f, %.2f]', ray_direction)}, ...
    'FontSize', 9, 'FontWeight', 'bold', ...
    'BackgroundColor', [1 1 0.9], 'EdgeColor', 'k', 'LineWidth', 1.5);

fprintf('💡 El parámetro t controla la posición en el rayo\n');
fprintf('   t=0  → Origen (cámara)\n');
fprintf('   t>0  → Puntos más adelante\n');
fprintf('   t=∞  → Infinito en esa dirección\n\n');
fprintf('✅ PARTE 1 completada. Pasa a PARTE 2 →\n\n');

%% ========================================================================
%  PARTE 2: PRIMERA INTERSECCIÓN - RAYO vs ESFERA
%  ========================================================================
%  ¿Dónde golpea nuestro rayo una esfera?
%  Resolvemos: |Origin + t*Dir - Center|² = radius²
% ========================================================================

fprintf('\n━━━ PARTE 2: Intersección Rayo-Esfera ━━━\n\n');

% 🎯 PARÁMETROS MODIFICABLES
ray_origin = [0, 0, 0];
ray_direction = [1, 0.2, 0.1];
ray_direction = ray_direction / norm(ray_direction);

sphere_center = [5, 1, 0];
sphere_radius = 1.5;
% ━━━━━━━━━━━━━━━━━━━━━━━━━

fprintf('🔍 Buscando intersección...\n\n');

% Resolver ecuación cuadrática: at² + bt + c = 0
oc = ray_origin - sphere_center;
a = dot(ray_direction, ray_direction);  % = 1 si está normalizado
b = 2.0 * dot(oc, ray_direction);
c = dot(oc, oc) - sphere_radius^2;

discriminant = b^2 - 4*a*c;

fprintf('   a = %.3f\n', a);
fprintf('   b = %.3f\n', b);
fprintf('   c = %.3f\n', c);
fprintf('   Discriminante = %.3f\n\n', discriminant);

if discriminant < 0
    fprintf('❌ NO HAY INTERSECCIÓN (discriminante < 0)\n');
    fprintf('   El rayo pasa de largo sin tocar la esfera\n\n');
    has_intersection = false;
else
    fprintf('✅ SÍ HAY INTERSECCIÓN\n\n');
    has_intersection = true;
    
    % Calcular ambos puntos de intersección
    t1 = (-b - sqrt(discriminant)) / (2*a);
    t2 = (-b + sqrt(discriminant)) / (2*a);
    
    hit1 = ray_origin + t1 * ray_direction;
    hit2 = ray_origin + t2 * ray_direction;
    
    fprintf('   Punto de ENTRADA (t1 = %.3f):\n', t1);
    fprintf('      → [%.2f, %.2f, %.2f]\n', hit1);
    fprintf('   Punto de SALIDA (t2 = %.3f):\n', t2);
    fprintf('      → [%.2f, %.2f, %.2f]\n\n', hit2);
    
    % Calcular normales
    normal1 = (hit1 - sphere_center) / sphere_radius;
    normal2 = (hit2 - sphere_center) / sphere_radius;
end

% Visualización
figure('Name', 'PARTE 2: Intersección Rayo-Esfera', 'Position', [150 150 900 700]);

% Dibujar esfera
[X,Y,Z] = sphere(40);
X = X*sphere_radius + sphere_center(1);
Y = Y*sphere_radius + sphere_center(2);
Z = Z*sphere_radius + sphere_center(3);
surf(X, Y, Z, 'FaceAlpha', 0.5, 'EdgeAlpha', 0.1, ...
     'FaceColor', 'cyan', 'EdgeColor', [0.3 0.3 0.3]);
hold on;

% Dibujar rayo
t_ray = linspace(-2, 10, 100);
for i = 1:length(t_ray)
    p = ray_origin + t_ray(i) * ray_direction;
    if i == 1
        plot3(p(1), p(2), p(3), 'r.', 'MarkerSize', 15);
    else
        plot3(p(1), p(2), p(3), 'r.', 'MarkerSize', 8);
    end
end

% Origen del rayo
plot3(ray_origin(1), ray_origin(2), ray_origin(3), ...
      'ro', 'MarkerSize', 15, 'MarkerFaceColor', 'r', 'LineWidth', 2);

if has_intersection
    % Puntos de intersección
    plot3(hit1(1), hit1(2), hit1(3), ...
          'go', 'MarkerSize', 20, 'MarkerFaceColor', 'g', 'LineWidth', 3);
    plot3(hit2(1), hit2(2), hit2(3), ...
          'mo', 'MarkerSize', 20, 'MarkerFaceColor', 'm', 'LineWidth', 3);
    
    % Normales en los puntos de intersección
    quiver3(hit1(1), hit1(2), hit1(3), ...
            normal1(1)*1.5, normal1(2)*1.5, normal1(3)*1.5, ...
            'g', 'LineWidth', 3, 'MaxHeadSize', 0.8);
    quiver3(hit2(1), hit2(2), hit2(3), ...
            normal2(1)*1.5, normal2(2)*1.5, normal2(3)*1.5, ...
            'm', 'LineWidth', 3, 'MaxHeadSize', 0.8);
    
    % Etiquetas
    text(hit1(1), hit1(2), hit1(3)+0.5, 'ENTRADA', ...
         'FontSize', 11, 'FontWeight', 'bold', 'Color', 'g');
    text(hit2(1), hit2(2), hit2(3)+0.5, 'SALIDA', ...
         'FontSize', 11, 'FontWeight', 'bold', 'Color', 'm');
end

grid on;
xlabel('X', 'FontSize', 12, 'FontWeight', 'bold');
ylabel('Y', 'FontSize', 12, 'FontWeight', 'bold');
zlabel('Z', 'FontSize', 12, 'FontWeight', 'bold');
title('Intersección: ¿Dónde el rayo golpea la esfera?', 'FontSize', 14, 'FontWeight', 'bold');
view(45, 20);
axis equal;

% Añadir explicación matemática
if has_intersection
    expl_str = {['INTERSECCIÓN RAYO-ESFERA:'], ...
                '', ...
                'Ecuación de la esfera:', ...
                '  |P - C|² = r²', ...
                '', ...
                'Sustituyendo P(t):', ...
                '  |O + t·D - C|² = r²', ...
                '', ...
                'Expandiendo → Ecuación cuadrática:', ...
                '  at² + bt + c = 0', ...
                '', ...
                sprintf('a = %.3f', a), ...
                sprintf('b = %.3f', b), ...
                sprintf('c = %.3f', c), ...
                sprintf('Δ = b² - 4ac = %.3f', discriminant), ...
                '', ...
                'Soluciones:', ...
                sprintf('t₁ = %.3f (ENTRADA)', t1), ...
                sprintf('t₂ = %.3f (SALIDA)', t2)};
else
    expl_str = {['INTERSECCIÓN RAYO-ESFERA:'], ...
                '', ...
                'Ecuación cuadrática:', ...
                '  at² + bt + c = 0', ...
                '', ...
                sprintf('Δ = %.3f < 0', discriminant), ...
                '', ...
                '❌ NO HAY INTERSECCIÓN', ...
                '', ...
                'El rayo pasa sin tocar', ...
                'la esfera'};
end
annotation('textbox', [0.02 0.65 0.32 0.32], ...
    'String', expl_str, ...
    'FontSize', 8.5, 'FontWeight', 'bold', ...
    'BackgroundColor', [1 1 0.9], 'EdgeColor', 'k', 'LineWidth', 1.5);

fprintf('💡 El discriminante decide si hay intersección:\n');
fprintf('   < 0  → No hay intersección\n');
fprintf('   = 0  → Rayo tangente (toca justo)\n');
fprintf('   > 0  → Dos intersecciones (entrada y salida)\n\n');
fprintf('🎮 EXPERIMENTA: Cambia ray_direction o sphere_center y vuelve a ejecutar\n\n');
fprintf('✅ PARTE 2 completada. Pasa a PARTE 3 →\n\n');

%% ========================================================================
%  PARTE 3: MÚLTIPLES OBJETOS - ¿CUÁL SE VE?
%  ========================================================================
%  Cuando un rayo intersecta varios objetos,
%  solo vemos el MÁS CERCANO (menor t > 0)
% ========================================================================

fprintf('\n━━━ PARTE 3: Oclusión - ¿Cuál objeto es visible? ━━━\n\n');

% 🎯 PARÁMETROS MODIFICABLES
ray_origin = [0, 0, 0];
ray_direction = [1, 0, 0];  % Rayo horizontal

% Tres esferas en línea
sphere1 = struct('center', [3, 0, 0], 'radius', 0.8, 'color', [1 0.2 0.2], 'name', 'Roja');
sphere2 = struct('center', [5, 0.3, 0], 'radius', 0.9, 'color', [0.2 1 0.2], 'name', 'Verde');
sphere3 = struct('center', [7, -0.2, 0], 'radius', 0.7, 'color', [0.2 0.2 1], 'name', 'Azul');
spheres = {sphere1, sphere2, sphere3};
% ━━━━━━━━━━━━━━━━━━━━━━━━━

fprintf('🎯 Rayo: origen=[%.1f, %.1f, %.1f], dirección=[%.1f, %.1f, %.1f]\n\n', ...
        ray_origin, ray_direction);

% Buscar intersecciones con TODAS las esferas
min_t = inf;
closest_idx = -1;
all_hits = [];

fprintf('Comprobando intersecciones:\n');
fprintf('─────────────────────────────────────────────────\n');

for i = 1:length(spheres)
    sp = spheres{i};
    
    % Calcular intersección
    oc = ray_origin - sp.center;
    a = 1;
    b = 2.0 * dot(oc, ray_direction);
    c = dot(oc, oc) - sp.radius^2;
    disc = b^2 - 4*a*c;
    
    if disc >= 0
        t = (-b - sqrt(disc)) / (2*a);
        if t > 0
            all_hits = [all_hits; i, t];
            fprintf('   Esfera %s: t = %.3f ', sp.name, t);
            
            if t < min_t
                min_t = t;
                closest_idx = i;
                fprintf('← ✨ MÁS CERCANA\n');
            else
                fprintf('(oculta)\n');
            end
        end
    else
        fprintf('   Esfera %s: sin intersección\n', sp.name);
    end
end

fprintf('─────────────────────────────────────────────────\n\n');

if closest_idx > 0
    fprintf('🏆 RESULTADO: La esfera %s es VISIBLE\n', spheres{closest_idx}.name);
    fprintf('   → t = %.3f (la menor distancia)\n', min_t);
    fprintf('   → Las demás están OCULTAS detrás\n\n');
end

% Visualización
figure('Name', 'PARTE 3: Oclusión', 'Position', [200 200 900 700]);

% Dibujar todas las esferas
for i = 1:length(spheres)
    sp = spheres{i};
    [X,Y,Z] = sphere(30);
    X = X*sp.radius + sp.center(1);
    Y = Y*sp.radius + sp.center(2);
    Z = Z*sp.radius + sp.center(3);
    
    if i == closest_idx
        % Esfera visible: opaca y con borde grueso
        surf(X, Y, Z, 'FaceColor', sp.color, 'FaceAlpha', 0.9, ...
             'EdgeColor', 'k', 'LineWidth', 2);
    else
        % Esferas ocultas: semi-transparentes
        surf(X, Y, Z, 'FaceColor', sp.color, 'FaceAlpha', 0.2, ...
             'EdgeColor', 'none');
    end
    hold on;
end

% Rayo
t_vals = linspace(0, 10, 100);
ray_x = ray_origin(1) + t_vals * ray_direction(1);
ray_y = ray_origin(2) + t_vals * ray_direction(2);
ray_z = ray_origin(3) + t_vals * ray_direction(3);
plot3(ray_x, ray_y, ray_z, 'k-', 'LineWidth', 2.5);

% Origen (cámara)
plot3(ray_origin(1), ray_origin(2), ray_origin(3), ...
      'ko', 'MarkerSize', 15, 'MarkerFaceColor', 'black');

% Punto de impacto visible
if closest_idx > 0
    hit_point = ray_origin + min_t * ray_direction;
    plot3(hit_point(1), hit_point(2), hit_point(3), ...
          'yo', 'MarkerSize', 25, 'MarkerFaceColor', 'yellow', ...
          'LineWidth', 3);
    text(hit_point(1), hit_point(2)+0.5, hit_point(3), '⭐ VISIBLE', ...
         'FontSize', 12, 'FontWeight', 'bold', 'Color', 'k');
end

grid on;
xlabel('X', 'FontSize', 12, 'FontWeight', 'bold');
ylabel('Y', 'FontSize', 12, 'FontWeight', 'bold');
zlabel('Z', 'FontSize', 12, 'FontWeight', 'bold');
title('Oclusión: Solo el objeto MÁS CERCANO es visible', 'FontSize', 14, 'FontWeight', 'bold');
view(0, 0);  % Vista lateral
axis equal;

% Añadir explicación
expl_str = {['ALGORITMO DE OCLUSIÓN:'], ...
            '', ...
            '1. Inicializar: t_min = ∞', ...
            '', ...
            '2. Para cada objeto i:', ...
            '     calcular t_i (distancia)', ...
            '', ...
            '3. Si t_i > 0 Y t_i < t_min:', ...
            '     t_min = t_i', ...
            '     objeto_visible = i', ...
            '', ...
            '4. Resultado:', ...
            '   El objeto con menor t', ...
            '   es el VISIBLE', ...
            '', ...
            sprintf('→ t_min = %.3f', min_t)};
if closest_idx > 0
    expl_str{end+1} = sprintf('→ Objeto: %s', spheres{closest_idx}.name);
end
annotation('textbox', [0.65 .15 0.32 0.38], ...
    'String', expl_str, ...0
    'FontSize', 9, 'FontWeight', 'bold', ...
    'BackgroundColor', [1 1 0.9], 'EdgeColor', 'k', 'LineWidth', 1.5);

fprintf('💡 CONCEPTO CLAVE: En raytracing, siempre elegimos t mínimo\n');
fprintf('   → Esto simula que objetos cercanos tapan a los lejanos\n');
fprintf('   → ¡Igual que en la vida real!\n\n');
fprintf('✅ PARTE 3 completada. Pasa a PARTE 4 →\n\n');

%% ========================================================================
%  PARTE 4: CALCULANDO NORMALES
%  ========================================================================
%  La normal es el vector perpendicular a la superficie
%  Es CRÍTICA para calcular iluminación
% ========================================================================

fprintf('\n━━━ PARTE 4: Normales de Superficie ━━━\n\n');

% 🎯 PARÁMETROS MODIFICABLES
sphere_center = [0, 0, 0];
sphere_radius = 2.0;
% ━━━━━━━━━━━━━━━━━━━━━━━━━

fprintf('Calculando normales en varios puntos de la esfera...\n\n');

% Generar puntos en la superficie
n_samples = 16;
sample_points = [];
sample_normals = [];

for i = 1:n_samples
    theta = 2*pi * i/n_samples;
    phi = pi/3;
    
    % Punto en la superficie (coordenadas esféricas)
    x = sphere_radius * sin(phi) * cos(theta);
    y = sphere_radius * sin(phi) * sin(theta);
    z = sphere_radius * cos(phi);
    point = [x, y, z] + sphere_center;
    
    % Normal para esfera: (punto - centro) / radio
    normal = (point - sphere_center) / sphere_radius;
    
    sample_points = [sample_points; point];
    sample_normals = [sample_normals; normal];
    
    if i <= 3
        fprintf('   Punto %d: [%5.2f, %5.2f, %5.2f]\n', i, point);
        fprintf('   Normal:  [%5.2f, %5.2f, %5.2f]\n\n', normal);
    end
end

% Visualización
figure('Name', 'PARTE 4: Normales', 'Position', [250 250 900 700]);

% Esfera
[X,Y,Z] = sphere(40);
X = X*sphere_radius + sphere_center(1);
Y = Y*sphere_radius + sphere_center(2);
Z = Z*sphere_radius + sphere_center(3);
surf(X, Y, Z, 'FaceAlpha', 0.5, 'EdgeAlpha', 0.1, ...
     'FaceColor', 'cyan', 'EdgeColor', [0.4 0.4 0.4]);
hold on;

% Puntos y normales
for i = 1:size(sample_points, 1)
    point = sample_points(i,:);
    normal = sample_normals(i,:);
    
    % Punto
    plot3(point(1), point(2), point(3), ...
          'ro', 'MarkerSize', 10, 'MarkerFaceColor', 'red');
    
    % Normal (vector)
    quiver3(point(1), point(2), point(3), ...
            normal(1)*1.2, normal(2)*1.2, normal(3)*1.2, ...
            'r', 'LineWidth', 2.5, 'MaxHeadSize', 0.6);
end

grid on;
xlabel('X', 'FontSize', 12, 'FontWeight', 'bold');
ylabel('Y', 'FontSize', 12, 'FontWeight', 'bold');
zlabel('Z', 'FontSize', 12, 'FontWeight', 'bold');
title('Normales: Vectores Perpendiculares a la Superficie', 'FontSize', 14, 'FontWeight', 'bold');
view(45, 30);
axis equal;

% Añadir explicación
annotation('textbox', [0.02 0.70 0.35 0.25], ...
    'String', {['CÁLCULO DE NORMALES:'], ...
               '', ...
               'ESFERA:', ...
               '  N = (P - Centro) / Radio', ...
               '', ...
               'Donde:', ...
               '  • P = punto en superficie', ...
               '  • N = vector unitario', ...
               '  • |N| = 1 (normalizado)', ...
               '', ...
               'PLANO:', ...
               '  N = vector normal fijo', ...
               '', ...
               'La normal es ⊥ a la superficie', ...
               'en cada punto'}, ...
    'FontSize', 8.5, 'FontWeight', 'bold', ...
    'BackgroundColor', [1 1 0.9], 'EdgeColor', 'k', 'LineWidth', 1.5);

fprintf('💡 FÓRMULAS de Normales:\n');
fprintf('   ESFERA:  N = (P - Centro) / Radio\n');
fprintf('   PLANO:   N = Vector normal del plano (constante)\n\n');
fprintf('   La normal siempre tiene longitud = 1 (normalizada)\n\n');
fprintf('✅ PARTE 4 completada. Pasa a PARTE 5 →\n\n');

%% ========================================================================
%  PARTE 5: ILUMINACIÓN SIMPLE
%  ========================================================================
%  Ley de Lambert: Intensidad = max(0, Normal · LuzDirección)
%  Cuanto más perpendicular sea la luz, más brillante
% ========================================================================

fprintf('\n━━━ PARTE 5: Iluminación (Ley de Lambert) ━━━\n\n');

% 🎯 PARÁMETROS MODIFICABLES
light_position = [5, 5, 5];
sphere_center = [0, 0, 0];
sphere_radius = 2;
base_color = [1, 0.3, 0.3];  % Color rojo de la esfera
% ━━━━━━━━━━━━━━━━━━━━━━━━━

fprintf('💡 Luz en posición: [%.1f, %.1f, %.1f]\n\n', light_position);

% Generar puntos en la esfera
[X,Y,Z] = sphere(50);
X = X*sphere_radius + sphere_center(1);
Y = Y*sphere_radius + sphere_center(2);
Z = Z*sphere_radius + sphere_center(3);

% Calcular iluminación para cada punto
colors = zeros(size(X,1), size(X,2), 3);

fprintf('Calculando iluminación en cada punto...\n');

for i = 1:size(X,1)
    for j = 1:size(X,2)
        point = [X(i,j), Y(i,j), Z(i,j)];
        
        % Normal
        normal = (point - sphere_center) / sphere_radius;
        
        % Dirección hacia la luz
        light_dir = light_position - point;
        light_dir = light_dir / norm(light_dir);
        
        % Intensidad difusa (Ley de Lambert)
        intensity = max(0, dot(normal, light_dir));
        
        % Color final
        colors(i,j,:) = base_color * intensity;
    end
end

fprintf('✓ Iluminación calculada\n\n');

% Ejemplos numéricos en puntos específicos
test_points = [
    sphere_radius, 0, 0;   % Derecha
    0, sphere_radius, 0;   % Arriba
    -sphere_radius, 0, 0   % Izquierda
];

fprintf('Ejemplos de intensidad:\n');
fprintf('─────────────────────────────────────────\n');
for i = 1:size(test_points, 1)
    point = test_points(i,:) + sphere_center;
    normal = (point - sphere_center) / sphere_radius;
    light_dir = light_position - point;
    light_dir = light_dir / norm(light_dir);
    
    dot_product = dot(normal, light_dir);
    intensity = max(0, dot_product);
    
    fprintf('Punto [%4.1f, %4.1f, %4.1f]:\n', point);
    fprintf('  N·L = %.3f → Intensidad = %.3f\n\n', dot_product, intensity);
end
fprintf('─────────────────────────────────────────\n\n');

% Visualización
figure('Name', 'PARTE 5: Iluminación', 'Position', [300 300 900 700]);

% Esfera con colores según iluminación
surf(X, Y, Z, colors, 'EdgeColor', 'none', 'FaceLighting', 'none');
hold on;

% Luz
plot3(light_position(1), light_position(2), light_position(3), ...
      'yo', 'MarkerSize', 30, 'MarkerFaceColor', 'yellow', ...
      'MarkerEdgeColor', 'k', 'LineWidth', 2);

% Mostrar algunos vectores
sample_angles = [0, pi/4, pi/2, pi];
for theta = sample_angles
    point = sphere_radius * [cos(theta), sin(theta), 0] + sphere_center;
    normal = (point - sphere_center) / sphere_radius;
    light_dir = light_position - point;
    light_dir = light_dir / norm(light_dir);
    
    % Normal
    quiver3(point(1), point(2), point(3), ...
            normal(1)*1.5, normal(2)*1.5, normal(3)*1.5, ...
            'b', 'LineWidth', 2.5, 'MaxHeadSize', 0.5);
    
    % Dirección a luz
    quiver3(point(1), point(2), point(3), ...
            light_dir(1)*2, light_dir(2)*2, light_dir(3)*2, ...
            'g', 'LineWidth', 2.5, 'MaxHeadSize', 0.5);
end

grid on;
xlabel('X', 'FontSize', 12, 'FontWeight', 'bold');
ylabel('Y', 'FontSize', 12, 'FontWeight', 'bold');
zlabel('Z', 'FontSize', 12, 'FontWeight', 'bold');
title('Iluminación Difusa: I = max(0, N · L)', 'FontSize', 14, 'FontWeight', 'bold');
view(45, 30);
axis equal;
colorbar;

% Añadir explicación
annotation('textbox', [0.02 0.65 0.35 0.30], ...
    'String', {['LEY DE LAMBERT (DIFUSA):'], ...
               '', ...
               'I_difusa = I_luz × max(0, N · L) × C', ...
               '', ...
               'Donde:', ...
               '  • N = normal de superficie', ...
               '  • L = dirección hacia luz', ...
               '  • C = color del objeto', ...
               '  • N · L = producto escalar', ...
               '', ...
               'Casos:', ...
               '  N·L = 1  → luz ⊥ → máx brillo', ...
               '  N·L = 0  → luz ∥ → sin luz', ...
               '  N·L < 0  → luz detrás → oscuro', ...
               '', ...
               sprintf('Luz en [%.1f, %.1f, %.1f]', light_position)}, ...
    'FontSize', 8, 'FontWeight', 'bold', ...
    'BackgroundColor', [1 1 0.9], 'EdgeColor', 'k', 'LineWidth', 1.5);

fprintf('💡 CONCEPTOS CLAVE:\n');
fprintf('   • N·L = 1  (luz perpendicular) → Máximo brillo\n');
fprintf('   • N·L = 0  (luz paralela)      → Sin iluminación\n');
fprintf('   • N·L < 0  (luz por detrás)    → Oscuro\n\n');
fprintf('🎮 EXPERIMENTA: Cambia light_position y observa cómo cambia la iluminación\n\n');
fprintf('✅ PARTE 5 completada. Pasa a PARTE 6 →\n\n');

%% ========================================================================
%  PARTE 6: SOMBRAS - SHADOW RAYS
%  ========================================================================
%  Para saber si un punto está en sombra:
%  1. Lanzar rayo desde punto hacia luz
%  2. Si intersecta algo → SOMBRA
%  3. Si llega a la luz → ILUMINADO
% ========================================================================

fprintf('\n━━━ PARTE 6: Sombras (Shadow Rays) ━━━\n\n');

% 🎯 PARÁMETROS MODIFICABLES
light_position = [0, 5, -2];

% Esfera que bloquea la luz
blocker = struct('center', [-1, 2.5, 0], 'radius', 1.3, 'color', [0.8 0.3 0.3]);

% Puntos en el suelo para testear
test_points_ground = [
    -3, 0, 2;
    -1.5, 0, 2;
    0, 0, 2;
    1.5, 0, 2;
    3, 0, 2
];
% ━━━━━━━━━━━━━━━━━━━━━━━━━

fprintf('Testeando sombras en %d puntos del suelo...\n\n', size(test_points_ground,1));
fprintf('══════════════════════════════════════════════════════\n');

is_shadowed = false(size(test_points_ground, 1), 1);

for i = 1:size(test_points_ground, 1)
    point = test_points_ground(i,:);
    
    % Shadow ray: desde punto hacia luz
    shadow_ray_dir = light_position - point;
    shadow_ray_length = norm(shadow_ray_dir);
    shadow_ray_dir = shadow_ray_dir / shadow_ray_length;
    
    fprintf('Punto %d: [%4.1f, %4.1f, %4.1f]\n', i, point);
    
    % Comprobar si el shadow ray intersecta el bloqueador
    oc = point - blocker.center;
    a = 1;
    b = 2.0 * dot(oc, shadow_ray_dir);
    c = dot(oc, oc) - blocker.radius^2;
    disc = b^2 - 4*a*c;
    
    if disc >= 0
        t = (-b - sqrt(disc)) / (2*a);
        if t > 0.001 && t < shadow_ray_length
            is_shadowed(i) = true;
            fprintf('  Shadow ray: ❌ BLOQUEADO (t=%.2f)\n', t);
            fprintf('  → Punto en SOMBRA\n\n');
        else
            fprintf('  Shadow ray: ✅ Llega a la luz\n');
            fprintf('  → Punto ILUMINADO\n\n');
        end
    else
        fprintf('  Shadow ray: ✅ Llega a la luz\n');
        fprintf('  → Punto ILUMINADO\n\n');
    end
end

fprintf('══════════════════════════════════════════════════════\n\n');
fprintf('📊 Resumen: %d puntos en sombra, %d iluminados\n\n', ...
        sum(is_shadowed), sum(~is_shadowed));

% Visualización
figure('Name', 'PARTE 6: Sombras', 'Position', [350 350 1000 700]);

% Esfera bloqueadora
[X,Y,Z] = sphere(30);
X = X*blocker.radius + blocker.center(1);
Y = Y*blocker.radius + blocker.center(2);
Z = Z*blocker.radius + blocker.center(3);
surf(X, Y, Z, 'FaceColor', blocker.color, 'FaceAlpha', 0.7, ...
     'EdgeColor', 'k', 'LineWidth', 1);
hold on;

% Luz
plot3(light_position(1), light_position(2), light_position(3), ...
      'yo', 'MarkerSize', 35, 'MarkerFaceColor', 'yellow', ...
      'MarkerEdgeColor', 'k', 'LineWidth', 3);

% Puntos y shadow rays
for i = 1:size(test_points_ground, 1)
    point = test_points_ground(i,:);
    
    if is_shadowed(i)
        point_color = [0.2 0.2 0.2];  % Oscuro
        line_style = 'r--';
        line_width = 2;
    else
        point_color = [1 1 0.8];      % Claro
        line_style = 'g-';
        line_width = 2.5;
    end
    
    % Punto
    plot3(point(1), point(2), point(3), ...
          'o', 'MarkerSize', 18, 'MarkerFaceColor', point_color, ...
          'MarkerEdgeColor', 'k', 'LineWidth', 2);
    
    % Shadow ray hacia la luz
    plot3([point(1) light_position(1)], ...
          [point(2) light_position(2)], ...
          [point(3) light_position(3)], ...
          line_style, 'LineWidth', line_width);
end

% Suelo
[X_ground, Y_ground] = meshgrid(-4:0.5:4, -1:0.5:4);
Z_ground = zeros(size(X_ground));
surf(X_ground, Y_ground, Z_ground, 'FaceAlpha', 0.3, ...
     'EdgeColor', [0.5 0.5 0.5], 'FaceColor', [0.6 0.6 0.6]);

grid on;
xlabel('X', 'FontSize', 12, 'FontWeight', 'bold');
ylabel('Y', 'FontSize', 12, 'FontWeight', 'bold');
zlabel('Z', 'FontSize', 12, 'FontWeight', 'bold');
title('Sombras: Shadow Rays hacia la Luz', 'FontSize', 14, 'FontWeight', 'bold');
view(45, 25);
axis equal;

% Añadir explicación
annotation('textbox', [0.65 0.68 0.33 0.28], ...
    'String', {['ALGORITMO DE SOMBRAS:'], ...
               '', ...
               '1. Ray_shadow = P → Luz', ...
               '', ...
               '2. d_luz = distancia a luz', ...
               '', ...
               '3. Para cada objeto:', ...
               '     calcular intersección t', ...
               '', ...
               '4. Si 0 < t < d_luz:', ...
               '     → Objeto BLOQUEA luz', ...
               '     → Punto en SOMBRA ❌', ...
               '', ...
               '5. Si NO hay bloqueo:', ...
               '     → Punto ILUMINADO ✅', ...
               '', ...
               sprintf('Resumen: %d en sombra', sum(is_shadowed))}, ...
    'FontSize', 8, 'FontWeight', 'bold', ...
    'BackgroundColor', [1 1 0.9], 'EdgeColor', 'k', 'LineWidth', 1.5);

fprintf('💡 ALGORITMO de sombras:\n');
fprintf('   1. Desde punto de impacto, lanzar rayo hacia luz\n');
fprintf('   2. Si rayo intersecta algo ANTES de llegar a luz → SOMBRA\n');
fprintf('   3. Si no hay intersección → ILUMINADO\n\n');
fprintf('✅ PARTE 6 completada. Pasa a PARTE 7 →\n\n');

%% ========================================================================
%  PARTE 7: RENDERIZADO DE UN PÍXEL COMPLETO
%  ========================================================================
%  Ahora juntamos TODO: rayo + intersección + iluminación + sombras
%  para calcular el color de UN SOLO PÍXEL
% ========================================================================

fprintf('\n━━━ PARTE 7: Renderizado de UN Píxel ━━━\n\n');

% 🎯 CONFIGURACIÓN DE ESCENA
camera_pos = [0, 1, -5];
camera_lookat = [0, 0, 0];

light_pos = [5, 8, -3];
light_color = [1, 1, 1];
ambient_color = [0.1, 0.1, 0.15];

% Objetos
sphere1 = struct('center', [0, 0, 0], 'radius', 1.0, 'color', [1 0.2 0.2]);
sphere2 = struct('center', [2.5, 0, 1], 'radius', 0.7, 'color', [0.2 1 0.2]);
objects = {sphere1, sphere2};

% Plano (suelo)
plane = struct('point', [0, -1, 0], 'normal', [0, 1, 0], 'color', [0.7 0.7 0.7]);
% ━━━━━━━━━━━━━━━━━━━━━━━━━

fprintf('Renderizando píxel en el CENTRO de la pantalla...\n\n');

% Configurar rayo para el píxel central
forward = camera_lookat - camera_pos;
forward = forward / norm(forward);
up = [0, 1, 0];
right = cross(forward, up);
right = right / norm(right);
up = cross(right, forward);

% Píxel en el centro (u=0.5, v=0.5)
fov = 60;
viewport_height = 2 * tan(deg2rad(fov/2));
viewport_width = viewport_height * (16/9);

pixel_on_plane = camera_pos + forward ...
                 + 0 * viewport_width * right ...
                 + 0 * viewport_height * up;

ray_origin = camera_pos;
ray_dir = pixel_on_plane - camera_pos;
ray_dir = ray_dir / norm(ray_dir);

fprintf('═══════════════════════════════════════════\n');
fprintf('PASO 1: Lanzar rayo primario\n');
fprintf('═══════════════════════════════════════════\n');
fprintf('  Origen:    [%.2f, %.2f, %.2f]\n', ray_origin);
fprintf('  Dirección: [%.2f, %.2f, %.2f]\n\n', ray_dir);

% PASO 2: Encontrar intersección más cercana
fprintf('═══════════════════════════════════════════\n');
fprintf('PASO 2: Buscar intersecciones\n');
fprintf('═══════════════════════════════════════════\n');

min_t = inf;
hit_object = [];
object_type = '';

% Comprobar esferas
for i = 1:length(objects)
    sp = objects{i};
    oc = ray_origin - sp.center;
    a = 1;
    b = 2.0 * dot(oc, ray_dir);
    c = dot(oc, oc) - sp.radius^2;
    disc = b^2 - 4*a*c;
    
    if disc >= 0
        t = (-b - sqrt(disc)) / (2*a);
        fprintf('  Esfera %d: t = %.3f\n', i, t);
        if t > 0 && t < min_t
            min_t = t;
            hit_object = sp;
            object_type = 'sphere';
        end
    else
        fprintf('  Esfera %d: sin intersección\n', i);
    end
end

% Comprobar plano
denom = dot(plane.normal, ray_dir);
if abs(denom) > 1e-6
    t = dot(plane.point - ray_origin, plane.normal) / denom;
    fprintf('  Plano: t = %.3f\n', t);
    if t > 0 && t < min_t
        min_t = t;
        hit_object = plane;
        object_type = 'plane';
    end
else
    fprintf('  Plano: sin intersección\n');
end

fprintf('\n');

if isempty(hit_object)
    fprintf('❌ Sin intersección → Color del cielo\n');
    pixel_color = [0.5, 0.7, 1.0];
else
    fprintf('✅ Intersección encontrada (t=%.3f)\n\n', min_t);
    
    % PASO 3: Calcular punto y normal
    fprintf('═══════════════════════════════════════════\n');
    fprintf('PASO 3: Calcular punto de impacto y normal\n');
    fprintf('═══════════════════════════════════════════\n');
    
    hit_point = ray_origin + min_t * ray_dir;
    fprintf('  Punto: [%.2f, %.2f, %.2f]\n', hit_point);
    
    if strcmp(object_type, 'sphere')
        normal = (hit_point - hit_object.center) / hit_object.radius;
        base_color = hit_object.color;
    else
        normal = plane.normal;
        base_color = plane.color;
    end
    fprintf('  Normal: [%.2f, %.2f, %.2f]\n\n', normal);
    
    % PASO 4: Shadow ray
    fprintf('═══════════════════════════════════════════\n');
    fprintf('PASO 4: Comprobar sombra (shadow ray)\n');
    fprintf('═══════════════════════════════════════════\n');
    
    light_dir = light_pos - hit_point;
    light_distance = norm(light_dir);
    light_dir = light_dir / light_distance;
    
    shadow_ray_origin = hit_point + 0.001 * normal;
    in_shadow = false;
    
    % Comprobar objetos
    for i = 1:length(objects)
        sp = objects{i};
        oc = shadow_ray_origin - sp.center;
        a = 1;
        b = 2.0 * dot(oc, light_dir);
        c = dot(oc, oc) - sp.radius^2;
        disc = b^2 - 4*a*c;
        
        if disc >= 0
            t = (-b - sqrt(disc)) / (2*a);
            if t > 0 && t < light_distance
                in_shadow = true;
                fprintf('  ❌ Shadow ray bloqueado por esfera %d\n', i);
                break;
            end
        end
    end
    
    if ~in_shadow
        fprintf('  ✅ Shadow ray llega a la luz\n');
    end
    fprintf('\n');
    
    % PASO 5: Calcular color final
    fprintf('═══════════════════════════════════════════\n');
    fprintf('PASO 5: Calcular color final\n');
    fprintf('═══════════════════════════════════════════\n');
    
    % Luz ambiental
    pixel_color = ambient_color .* base_color;
    fprintf('  Luz ambiental: [%.2f, %.2f, %.2f]\n', pixel_color);
    
    if ~in_shadow
        % Iluminación difusa
        diff = max(dot(normal, light_dir), 0.0);
        diffuse = diff * light_color .* base_color;
        pixel_color = pixel_color + diffuse;
        fprintf('  + Difusa: [%.2f, %.2f, %.2f]\n', diffuse);
    end
    
    pixel_color = min(pixel_color, 1.0);
    fprintf('  ────────────────────────────────────\n');
    fprintf('  COLOR FINAL: [%.2f, %.2f, %.2f]\n', pixel_color);
end

fprintf('\n═══════════════════════════════════════════\n\n');

% Visualización del color
figure('Name', 'PARTE 7: Color del Píxel', 'Position', [400 400 600 200]);
subplot(1,2,1);
rectangle('Position', [0 0 1 1], 'FaceColor', pixel_color);
axis off;
title(sprintf('Color del Píxel\nRGB: [%.2f, %.2f, %.2f]', pixel_color), ...
      'FontSize', 14, 'FontWeight', 'bold');

subplot(1,2,2);
bar([pixel_color(1), pixel_color(2), pixel_color(3)]);
set(gca, 'XTickLabel', {'R', 'G', 'B'});
ylim([0 1]);
title('Componentes RGB', 'FontSize', 12, 'FontWeight', 'bold');
grid on;

% Añadir explicación del proceso completo
annotation('textbox', [0.05 0.02 0.90 0.15], ...
    'String', {['PIPELINE COMPLETO PARA 1 PÍXEL: '], ...
               ['1) Rayo primario desde cámara  →  2) Buscar intersección más cercana  →  3) Calcular normal en punto  →  '], ...
               ['4) Lanzar shadow ray hacia luz  →  5) Si no hay sombra: Color = Ambiente + Difusa  →  6) Retornar color final']}, ...
    'FontSize', 8, 'FontWeight', 'bold', 'HorizontalAlignment', 'center', ...
    'BackgroundColor', [0.9 0.95 1], 'EdgeColor', [0 0 0.5], 'LineWidth', 2);

fprintf('💡 Este es el proceso COMPLETO para calcular UN píxel\n');
fprintf('   En una imagen 800x600, hacemos esto 480,000 veces!\n\n');
fprintf('✅ PARTE 7 completada. Pasa a PARTE 8 →\n\n');

%% ========================================================================
%  PARTE 8: RENDERIZADO DE UNA LÍNEA
%  ========================================================================
%  Aplicamos el proceso anterior a TODOS los píxeles de una línea
% ========================================================================

fprintf('\n━━━ PARTE 8: Renderizado de UNA Línea ━━━\n\n');

% Configuración
img_width = 200;
line_y = 100;  % Línea horizontal en el medio

fprintf('Renderizando línea de %d píxeles...\n', img_width);
fprintf('(Esto tardará unos segundos)\n\n');

% Configurar cámara
camera_pos = [0, 1, -5];
camera_lookat = [0, 0, 0];
fov = 60;

forward = camera_lookat - camera_pos;
forward = forward / norm(forward);
up = [0, 1, 0];
right = cross(forward, up);
right = right / norm(right);
up = cross(right, forward);

viewport_height = 2 * tan(deg2rad(fov/2));
viewport_width = viewport_height * (img_width / 200);

lower_left = camera_pos + forward - viewport_width/2 * right - viewport_height/2 * up;

% Escena
light_pos = [5, 8, -3];
sphere1 = struct('center', [0, 0, 0], 'radius', 1.0, 'color', [1 0.2 0.2]);
sphere2 = struct('center', [2, 0, 1], 'radius', 0.7, 'color', [0.2 1 0.2]);
objects = {sphere1, sphere2};

% Renderizar línea
line_colors = zeros(img_width, 3);

tic;
for x = 1:img_width
    u = (x-1) / (img_width-1);
    v = 0.5;  % Línea en el medio
    
    pixel_pos = lower_left + u * viewport_width * right + v * viewport_height * up;
    ray_dir = pixel_pos - camera_pos;
    ray_dir = ray_dir / norm(ray_dir);
    
    % Buscar intersección
    min_t = inf;
    hit_object = [];
    
    for i = 1:length(objects)
        sp = objects{i};
        oc = camera_pos - sp.center;
        a = 1;
        b = 2.0 * dot(oc, ray_dir);
        c = dot(oc, oc) - sp.radius^2;
        disc = b^2 - 4*a*c;
        
        if disc >= 0
            t = (-b - sqrt(disc)) / (2*a);
            if t > 0 && t < min_t
                min_t = t;
                hit_object = sp;
            end
        end
    end
    
    % Calcular color
    if isempty(hit_object)
        line_colors(x,:) = [0.5, 0.7, 1.0];  % Cielo
    else
        hit_point = camera_pos + min_t * ray_dir;
        normal = (hit_point - hit_object.center) / hit_object.radius;
        light_dir = light_pos - hit_point;
        light_dir = light_dir / norm(light_dir);
        
        diff = max(dot(normal, light_dir), 0.0);
        line_colors(x,:) = 0.1 * hit_object.color + diff * hit_object.color;
        line_colors(x,:) = min(line_colors(x,:), 1.0);
    end
    
    if mod(x, 50) == 0
        fprintf('  Progreso: %d/%d píxeles\n', x, img_width);
    end
end

elapsed = toc;
fprintf('\n✓ Línea renderizada en %.2f segundos\n\n', elapsed);

% Visualización
figure('Name', 'PARTE 8: Una Línea Renderizada', 'Position', [450 450 900 300]);

% Mostrar la línea
subplot(2,1,1);
image(reshape(line_colors, [1, img_width, 3]));
axis off;
title('Línea Renderizada (200 píxeles)', 'FontSize', 14, 'FontWeight', 'bold');

% Análisis de colores
subplot(2,1,2);
plot(1:img_width, line_colors(:,1), 'r-', 'LineWidth', 2); hold on;
plot(1:img_width, line_colors(:,2), 'g-', 'LineWidth', 2);
plot(1:img_width, line_colors(:,3), 'b-', 'LineWidth', 2);
xlabel('Píxel X', 'FontSize', 11);
ylabel('Intensidad', 'FontSize', 11);
title('Componentes RGB a lo largo de la línea', 'FontSize', 12, 'FontWeight', 'bold');
legend('Rojo', 'Verde', 'Azul');
grid on;

% Añadir explicación
annotation('textbox', [0.55 0.40 0.42 0.18], ...
    'String', {['RENDERIZADO DE LÍNEA:'], ...
               '', ...
               sprintf('Total píxeles: %d', img_width), ...
               sprintf('Tiempo: %.2f s', elapsed), ...
               sprintf('Velocidad: %.0f px/s', img_width/elapsed), ...
               '', ...
               'Proceso repetido para cada píxel:', ...
               'Rayo → Intersección → Iluminación'}, ...
    'FontSize', 8.5, 'FontWeight', 'bold', ...
    'BackgroundColor', [1 1 0.9], 'EdgeColor', 'k', 'LineWidth', 1.5);

fprintf('💡 Observa cómo cambian los colores:\n');
fprintf('   - Azul alto = cielo (sin intersección)\n');
fprintf('   - Rojo alto = esfera roja visible\n');
fprintf('   - Verde alto = esfera verde visible\n\n');
fprintf('✅ PARTE 8 completada. Pasa a PARTE 9 →\n\n');

%% ========================================================================
%  PARTE 9: ESCENA COMPLETA SIMPLIFICADA
%  ========================================================================
%  Renderizado completo en baja resolución (rápido)
% ========================================================================

fprintf('\n━━━ PARTE 9: Escena Completa (Baja Resolución) ━━━\n\n');

% 🎯 PARÁMETROS MODIFICABLES
img_width = 160;
img_height = 120;
% ━━━━━━━━━━━━━━━━━━━━━━━━━

fprintf('Resolución: %dx%d píxeles\n', img_width, img_height);
fprintf('Renderizando...\n\n');

% Escena simple
camera_pos = [0, 1, -5];
camera_lookat = [0, 0, 0];
light_pos = [5, 8, -3];

sphere1 = struct('center', [0, 0, 0], 'radius', 1.0, 'color', [1 0.2 0.2]);
sphere2 = struct('center', [-2, 0, 1], 'radius', 0.8, 'color', [0.2 1 0.2]);
sphere3 = struct('center', [2, 0.5, -0.5], 'radius', 0.6, 'color', [0.2 0.3 1]);
objects = {sphere1, sphere2, sphere3};

% Preparar cámara
forward = camera_lookat - camera_pos;
forward = forward / norm(forward);
up = [0, 1, 0];
right = cross(forward, up);
right = right / norm(right);
up = cross(right, forward);

fov = 60;
viewport_height = 2 * tan(deg2rad(fov/2));
viewport_width = viewport_height * (img_width / img_height);
lower_left = camera_pos + forward - viewport_width/2 * right - viewport_height/2 * up;

% Renderizar
image_data = zeros(img_height, img_width, 3);

tic;
for y = 1:img_height
    for x = 1:img_width
        u = (x-1) / (img_width-1);
        v = (img_height - y) / (img_height-1);
        
        pixel_pos = lower_left + u * viewport_width * right + v * viewport_height * up;
        ray_dir = pixel_pos - camera_pos;
        ray_dir = ray_dir / norm(ray_dir);
        
        % Intersección
        min_t = inf;
        hit_object = [];
        
        for i = 1:length(objects)
            sp = objects{i};
            oc = camera_pos - sp.center;
            a = 1;
            b = 2.0 * dot(oc, ray_dir);
            c = dot(oc, oc) - sp.radius^2;
            disc = b^2 - 4*a*c;
            
            if disc >= 0
                t = (-b - sqrt(disc)) / (2*a);
                if t > 0 && t < min_t
                    min_t = t;
                    hit_object = sp;
                end
            end
        end
        
        % Color
        if isempty(hit_object)
            t = 0.5 * (ray_dir(2) + 1);
            image_data(y,x,:) = (1-t) * [0.5 0.7 1.0] + t * [0.8 0.9 1.0];
        else
            hit_point = camera_pos + min_t * ray_dir;
            normal = (hit_point - hit_object.center) / hit_object.radius;
            light_dir = light_pos - hit_point;
            light_dir = light_dir / norm(light_dir);
            
            diff = max(dot(normal, light_dir), 0.0);
            image_data(y,x,:) = 0.15 * hit_object.color + 0.85 * diff * hit_object.color;
        end
    end
    
    if mod(y, 20) == 0
        fprintf('  Progreso: %d%%\n', round(100*y/img_height));
    end
end

elapsed = toc;

fprintf('\n✓ Renderizado completado en %.2f segundos\n\n', elapsed);

% Mostrar
figure('Name', 'PARTE 9: Escena Completa', 'Position', [500 500 700 600]);
imshow(image_data);
title(sprintf('Escena Renderizada (%dx%d) - %.1fs', img_width, img_height, elapsed), ...
      'FontSize', 14, 'FontWeight', 'bold');

% Añadir explicación y estadísticas
total_pixels = img_width * img_height;
annotation('textbox', [0.02 0.75 0.35 0.22], ...
    'String', {['ESTADÍSTICAS:'], ...
               '', ...
               sprintf('Resolución: %d×%d', img_width, img_height), ...
               sprintf('Píxeles totales: %d', total_pixels), ...
               sprintf('Tiempo total: %.2f s', elapsed), ...
               sprintf('Velocidad: %.0f px/s', total_pixels/elapsed), ...
               '', ...
               'Rayos lanzados:', ...
               sprintf('  • Primarios: %d', total_pixels), ...
               '  • Por píxel: 1 (sin AA)', ...
               '', ...
               'Efectos: Difusa + Gradiente cielo'}, ...
    'FontSize', 8, 'FontWeight', 'bold', ...
    'BackgroundColor', [1 1 0.9], 'EdgeColor', 'k', 'LineWidth', 1.5);

fprintf('💡 Esta es tu primera imagen de raytracing completa!\n');
fprintf('   - 3 esferas de diferentes colores\n');
fprintf('   - Gradiente de cielo\n');
fprintf('   - Iluminación simple\n\n');
fprintf('✅ PARTE 9 completada. Pasa a PARTE 10 (FINAL) →\n\n');

%% ========================================================================
%  PARTE 10: ESCENA FINAL CON TODOS LOS EFECTOS
%  ========================================================================
%  Versión completa con:
%  - Mayor resolución
%  - Sombras
%  - Plano con checkerboard
%  - Iluminación especular
% ========================================================================

fprintf('\n━━━ PARTE 10: ESCENA FINAL (Alta Calidad) ━━━\n\n');

% 🎯 PARÁMETROS MODIFICABLES
img_width = 400;
img_height = 300;
% ━━━━━━━━━━━━━━━━━━━━━━━━━

fprintf('╔════════════════════════════════════════════╗\n');
fprintf('║  RENDERIZADO FINAL - Alta Calidad          ║\n');
fprintf('╚════════════════════════════════════════════╝\n\n');
fprintf('Resolución: %dx%d píxeles\n', img_width, img_height);
fprintf('Efectos: Sombras + Checkerboard + Especular\n');
fprintf('Esto puede tardar 10-30 segundos...\n\n');

% Configuración de escena
camera_pos = [0, 1.5, -6];
camera_lookat = [0, 0.5, 0];
light_pos = [5, 10, -5];
ambient = [0.1, 0.1, 0.15];

% Objetos
sphere1 = struct('center', [0, 0.5, 0], 'radius', 1.0, ...
                 'color', [1 0.2 0.2], 'material', 'diffuse');
sphere2 = struct('center', [-2.5, 0.5, 1], 'radius', 0.8, ...
                 'color', [0.2 1 0.2], 'material', 'specular');
sphere3 = struct('center', [2, 0.4, -1], 'radius', 0.7, ...
                 'color', [0.2 0.3 1], 'material', 'diffuse');
objects = {sphere1, sphere2, sphere3};

plane = struct('point', [0, -0.5, 0], 'normal', [0, 1, 0]);

% Preparar cámara
forward = camera_lookat - camera_pos;
forward = forward / norm(forward);
up = [0, 1, 0];
right = cross(forward, up);
right = right / norm(right);
up = cross(right, forward);

fov = 60;
viewport_height = 2 * tan(deg2rad(fov/2));
viewport_width = viewport_height * (img_width / img_height);
lower_left = camera_pos + forward - viewport_width/2 * right - viewport_height/2 * up;

% Renderizar
image_final = zeros(img_height, img_width, 3);
progress_step = floor(img_height / 10);

tic;
for y = 1:img_height
    for x = 1:img_width
        u = (x-1) / (img_width-1);
        v = (img_height - y) / (img_height-1);
        
        pixel_pos = lower_left + u * viewport_width * right + v * viewport_height * up;
        ray_dir = pixel_pos - camera_pos;
        ray_dir = ray_dir / norm(ray_dir);
        
        % Intersección
        min_t = inf;
        hit_object = [];
        hit_type = '';
        
        % Esferas
        for i = 1:length(objects)
            sp = objects{i};
            oc = camera_pos - sp.center;
            a = 1;
            b = 2.0 * dot(oc, ray_dir);
            c = dot(oc, oc) - sp.radius^2;
            disc = b^2 - 4*a*c;
            
            if disc >= 0
                t = (-b - sqrt(disc)) / (2*a);
                if t > 0 && t < min_t
                    min_t = t;
                    hit_object = sp;
                    hit_type = 'sphere';
                end
            end
        end
        
        % Plano
        denom = dot(plane.normal, ray_dir);
        if abs(denom) > 1e-6
            t = dot(plane.point - camera_pos, plane.normal) / denom;
            if t > 0 && t < min_t
                min_t = t;
                hit_object = plane;
                hit_type = 'plane';
            end
        end
        
        % Calcular color
        if isempty(hit_object)
            % Cielo
            t = 0.5 * (ray_dir(2) + 1);
            image_final(y,x,:) = (1-t) * [0.5 0.7 1.0] + t * [0.8 0.9 1.0];
        else
            hit_point = camera_pos + min_t * ray_dir;
            
            if strcmp(hit_type, 'sphere')
                normal = (hit_point - hit_object.center) / hit_object.radius;
                base_color = hit_object.color;
                material = hit_object.material;
            else
                normal = plane.normal;
                % Checkerboard
                scale = 2.0;
                pattern = mod(floor(scale * hit_point(1)) + floor(scale * hit_point(3)), 2);
                if pattern == 0
                    base_color = [0.2 0.2 0.2];
                else
                    base_color = [0.9 0.9 0.9];
                end
                material = 'diffuse';
            end
            
            % Iluminación
            color = ambient .* base_color;
            
            % Shadow ray
            light_dir = light_pos - hit_point;
            light_dist = norm(light_dir);
            light_dir = light_dir / light_dist;
            
            shadow_origin = hit_point + 0.001 * normal;
            in_shadow = false;
            
            for i = 1:length(objects)
                sp = objects{i};
                oc = shadow_origin - sp.center;
                a = 1;
                b = 2.0 * dot(oc, light_dir);
                c = dot(oc, oc) - sp.radius^2;
                disc = b^2 - 4*a*c;
                
                if disc >= 0
                    t = (-b - sqrt(disc)) / (2*a);
                    if t > 0 && t < light_dist
                        in_shadow = true;
                        break;
                    end
                end
            end
            
            if ~in_shadow
                % Difusa
                diff = max(dot(normal, light_dir), 0.0);
                color = color + diff * base_color;
                
                % Especular
                if strcmp(material, 'specular') && diff > 0
                    reflect_dir = 2 * dot(light_dir, normal) * normal - light_dir;
                    spec = max(dot(reflect_dir, -ray_dir), 0.0)^50;
                    color = color + spec * [1 1 1];
                end
            end
            
            image_final(y,x,:) = min(color, 1.0);
        end
    end
    
    if mod(y, progress_step) == 0
        fprintf('  ▓▓▓▓ %d%% completado\n', round(100*y/img_height));
    end
end

elapsed = toc;

fprintf('\n');
fprintf('╔════════════════════════════════════════════╗\n');
fprintf('║  ✅ RENDERIZADO COMPLETADO                 ║\n');
fprintf('╚════════════════════════════════════════════╝\n\n');
fprintf('Tiempo total: %.2f segundos\n', elapsed);
fprintf('Píxeles renderizados: %d\n', img_width * img_height);
fprintf('Velocidad: %.0f píxeles/segundo\n\n', (img_width*img_height)/elapsed);

% Corrección gamma
gamma = 2.2;
image_final = image_final .^ (1/gamma);
image_final = max(0, min(1, image_final));

% Mostrar resultado
figure('Name', 'PARTE 10: ESCENA FINAL', 'Position', [100 100 900 700]);
imshow(image_final);
title(sprintf('Raytracing Completo (%dx%d) - %.1fs', img_width, img_height, elapsed), ...
      'FontSize', 15, 'FontWeight', 'bold');

% Añadir explicación completa y estadísticas
total_px = img_width * img_height;
annotation('textbox', [0.02 0.60 0.30 0.37], ...
    'String', {['✨ RAYTRACING COMPLETO ✨'], ...
               '', ...
               'FÓRMULA GENERAL:', ...
               'Color = Ambiente + Difusa + Especular', ...
               '', ...
               'I_final = I_amb + Σ(I_luz × BRDF)', ...
               '', ...
               'BRDF = f_r(ω_i, ω_o)', ...
               '  • Lambert: ρ/π × (N·L)', ...
               '  • Phong: (R·V)^n', ...
               '', ...
               'ESTADÍSTICAS:', ...
               sprintf('Píxeles: %d', total_px), ...
               sprintf('Tiempo: %.1f s', elapsed), ...
               sprintf('Rayos primarios: %d', total_px), ...
               '', ...
               'EFECTOS:', ...
               '✓ Sombras (shadow rays)', ...
               '✓ Checkerboard procedural', ...
               '✓ Iluminación Phong', ...
               '✓ Corrección gamma (γ=2.2)'}, ...
    'FontSize', 7.5, 'FontWeight', 'bold', ...
    'BackgroundColor', [0.95 1 0.95], 'EdgeColor', [0 0.5 0], 'LineWidth', 2);

% Añadir leyenda de ecuaciones clave
annotation('textbox', [0.68 0.02 0.30 0.25], ...
    'String', {['ECUACIONES CLAVE:'], ...
               '', ...
               'RAYO:', ...
               '  P(t) = O + t·D', ...
               '', ...
               'ESFERA:', ...
               '  |P(t) - C|² = r²', ...
               '  → at² + bt + c = 0', ...
               '', ...
               'LAMBERT:', ...
               '  I = max(0, N·L)', ...
               '', ...
               'PHONG:', ...
               '  I = (R·V)^shininess', ...
               '', ...
               'GAMMA:', ...
               '  C_out = C_in^(1/2.2)'}, ...
    'FontSize', 7.5, 'FontWeight', 'bold', ...
    'BackgroundColor', [1 0.95 0.9], 'EdgeColor', [0.5 0 0], 'LineWidth', 1.5);

fprintf('🎨 EFECTOS IMPLEMENTADOS:\n');
fprintf('  ✓ Rayos primarios desde cámara\n');
fprintf('  ✓ Intersección rayo-esfera\n');
fprintf('  ✓ Intersección rayo-plano\n');
fprintf('  ✓ Detección del objeto más cercano (oclusión)\n');
fprintf('  ✓ Cálculo de normales\n');
fprintf('  ✓ Iluminación difusa (Lambert)\n');
fprintf('  ✓ Iluminación especular (Phong)\n');
fprintf('  ✓ Sombras (shadow rays)\n');
fprintf('  ✓ Luz ambiental\n');
fprintf('  ✓ Textura procedural (checkerboard)\n');
fprintf('  ✓ Corrección gamma\n\n');

fprintf('━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n');
fprintf('🎉 ¡FELICIDADES! Has completado el tutorial\n');
fprintf('━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n');
fprintf('💡 PRÓXIMOS PASOS:\n');
fprintf('  1. Experimenta cambiando parámetros en cada sección\n');
fprintf('  2. Compara este código con tu proyecto miniRT en C\n');
fprintf('  3. Identifica las mismas funciones y algoritmos\n');
fprintf('  4. Intenta añadir nuevos efectos:\n');
fprintf('     - Más esferas\n');
fprintf('     - Reflexiones\n');
fprintf('     - Diferentes materiales\n');
fprintf('     - Anti-aliasing (múltiples samples por píxel)\n\n');
fprintf('📖 Lee el archivo README_MATLAB.md para más información\n\n');

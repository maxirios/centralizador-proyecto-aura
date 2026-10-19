# Guía de Contribución

¡Gracias por querer contribuir a este proyecto! Para mantener la calidad del código y la organización del historial, sigue estas directrices.

---

## Calidad del Código y Comentarios

Buscamos un código **limpio, legible y autodocumentado**. Escribe código que se explique a sí mismo mediante nombres de variables y funciones descriptivos.

### Reglas de comentarios:

- Comenta **solo si es necesario**.
- Al comentar **No repitas** lo que ya dice el código de manera obvia.

---

## Pull Requests

- No hagas Push Directamente a `main`
- Todos los cambios deben integrarse a través de **Pull Requests (PR)**
- Los PR deben ser revisados y aprobados por el equipo

---

## Convención para el Nombre de Ramas

Las ramas deben seguir una estructura clara según el tipo de cambio que estés introduciendo:

- `feature/nombre-de-la-funcionalidad`: Para el desarrollo de nuevas características.
  - *Ejemplo:* `feature/login-usuario`
- `bugfix/descripcion-del-error`: Para corregir errores o fallos en el código.
  - *Ejemplo:* `bugfix/registro-duplicado`
- `hotfix/descripcion-urgente`: Para correcciones críticas en producción que no pueden esperar.
  - *Ejemplo:* `hotfix/caida-servidor`
- `docs/descripcion-documentacion`: Para cambios exclusivos en la documentación.
  - *Ejemplo:* `docs/actualizar-readme`
- `refactor/descripcion-refactor`: Para cambios en el código que no añaden funcionalidades ni corrigen errores (limpieza, optimización).
  - *Ejemplo:* `refactor/limpieza-variables`

---

## Convención para Mensajes de Commit

Recomendamos usar la convención de **Conventional Commits** para mantener un historial de cambios legible y consistente.

### Formato General:

`tipo: descripción breve en minúsculas y español`

### Tipos permitidos:

- `feat`: Nueva funcionalidad.
  - *Ejemplo:* `feat: agregar formulario de contacto`
- `fix`: Solución de un error.
  - *Ejemplo:* `fix: corregir validacion de correo electronico`
- `docs`: Cambios en la documentación.
  - *Ejemplo:* `docs: crear guia de contribucion`
- `style`: Cambios que no afectan el significado del código (espacios, formateo, punto y coma faltante).
- `refactor`: Cambio de código que no corrige un error ni añade una función.
- `test`: Añadir o modificar pruebas unitarias.
- `chore`: Tareas de mantenimiento, configuración del entorno o herramientas.

### Uso del Cuerpo del Mensaje (Commit Body)

Se recomienda utilizar el **cuerpo del commit** para dar contexto adicional y justificar los cambios cuando sea necesario:
- **Explicar el "por qué":** Argumentar la decisión técnica adoptada frente a otras posibles alternativas.
- **Mantener el título conciso:** El asunto/título debe ser breve, claro y al grano; las explicaciones profundas, notas de compatibilidad o dependencias deben desarrollarse en el cuerpo.
- **Formato:** Deja siempre una línea en blanco entre el título y el cuerpo del commit.

*Ejemplo:*
```text
feat: inicializar pantalla en orientacion portrait

Se configura la rotacion a 480x800 mediante LVGL para operar el panel
Waveshare en vertical, ubicando los buffers de renderizado en PSRAM
para preservar la memoria interna del ESP32-S3.
```

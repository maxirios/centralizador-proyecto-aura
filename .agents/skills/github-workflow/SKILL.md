---
name: github-workflow
description: Reglas e instrucciones para crear ramas, realizar commits con Conventional Commits, abrir Pull Requests (PRs), validar GitHub Actions y utilizar GitHub CLI (gh). Utiliza esta skill siempre que el usuario pida commitear, crear ramas, abrir PRs, revisar checks o mergear cambios.
---

# Flujo de Trabajo en GitHub (GitHub Workflow)

Este documento establece las reglas obligatorias de control de versiones, ramas, commits y Pull Requests para este repositorio. Como agente asistente, **DEBES** seguir estas directrices antes de ejecutar cualquier comando de Git o GitHub CLI (`gh`).

---

## 1. Convenciones de Ramas y Commits (según CONTRIBUTING.md)

Consulta siempre [CONTRIBUTING.md](file:///home/agust/Projects/centralizador-proyecto-aura/CONTRIBUTING.md) como referencia de estilo:

### 1.1 Estructura de Ramas
* `main`: Producción. Solo código estable y probado.
* `develop`: Integración y desarrollo activo.
* Ramas de trabajo (salen **siempre desde `develop`**):
  * `feature/<nombre>`: Nuevas funcionalidades.
  * `bugfix/<nombre>`: Corrección de errores.
  * `hotfix/<nombre>`: Correcciones urgentes para producción.
  * `refactor/<nombre>`: Limpieza y reestructuración sin cambio de funcionalidad.
  * `docs/<nombre>`: Cambios exclusivos de documentación.

> **Regla de oro:** **NUNCA** trabajes ni hagas commits directamente sobre `main` o `develop`.

### 1.2 Formato de Commits (Conventional Commits)
Sigue el formato establecido en `CONTRIBUTING.md`:
```text
tipo: descripción breve en minúsculas y español
```
* **Tipos permitidos:** `feat`, `fix`, `docs`, `style`, `refactor`, `test`, `chore`.
* **Uso del cuerpo del commit (`body`):** Para mantener los títulos concisos y legibles, utiliza el cuerpo del commit para justificar decisiones técnicas, explicar el porqué frente a otras alternativas o detallar la integración. Separa siempre el título del cuerpo con una línea vacía.
* **Ejemplos:**
  * `feat: agregar inicializacion de pantalla en modo portrait`
  * `fix: corregir timeout en recepcion de paquetes json mesh`
  * `docs: actualizar agents.md con enrutador de skills`

---

## 2. Flujo de Pull Requests (PRs)

1. **Destino de los PRs:**
   * Las ramas de trabajo (`feature/*`, `bugfix/*`, etc.) abren PR hacia **`develop`**.
   * Para llevar cambios a producción, el PR se abre exclusivamente de **`develop` hacia `main`**.
2. **Plantilla de PR:**
   * Al crear un PR, utiliza la estructura definida en [.github/PULL_REQUEST_TEMPLATE.md](file:///home/agust/Projects/centralizador-proyecto-aura/.github/PULL_REQUEST_TEMPLATE.md) (Resumen, Cambios, Lista de verificación e Issues relacionados como `Fixes #123`).
3. **Consentimiento Obligatorio:**
   * **SIEMPRE** pide confirmación al usuario antes de hacer `git push`, abrir un PR o ejecutar un merge.
4. **Validación de Checks (CI):**
   * Antes de fusionar (merge), todos los GitHub Actions deben haber finalizado con éxito (`success`).
   * Valida el estado con `gh pr checks`.

---

## 3. Uso de GitHub CLI (`gh`) (Multiplataforma)

El proyecto utiliza GitHub CLI (`gh`) para gestionar PRs desde la terminal de forma agnóstica al sistema operativo:

* **Requisito:** `gh` debe estar instalado y autenticado (`gh auth status` o `gh auth login`).
* **Crear un PR:**
  ```bash
  gh pr create --base develop --title "tipo: título conciso" --body-file .github/PULL_REQUEST_TEMPLATE.md
  # O pasando el body directo respetando las secciones del template:
  gh pr create --base develop --title "feat: pantalla portrait" --body "## Resumen..."
  ```
* **Verificar checks de CI:**
  ```bash
  gh pr checks
  ```
* **Mergear un PR (solo con autorización del usuario y checks en verde):**
  ```bash
  gh pr merge --squash --delete-branch
  ```

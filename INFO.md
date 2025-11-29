# Guía Básica de Git

Este archivo contiene una referencia rápida de los comandos más utilizados de Git para trabajar en este repositorio.

## 1. Configuración Inicial

Antes de empezar, asegúrate de tener tu identidad configurada:

```bash
git config --global user.name "Tu Nombre"
git config --global user.email "tu@email.com"
```

## 2. Clonar el Repositorio

Para descargar una copia local del repositorio:

```bash
git clone https://gitlab.com/university9071543/noob-code.git
```

## 3. Flujo de Trabajo Diario

### Ver el estado de los archivos
Comprueba qué archivos han sido modificados:
```bash
git status
```

### Añadir cambios
Prepara los archivos para guardarlos (stage):
```bash
# Añadir un archivo específico
git add nombre_del_archivo.c

# Añadir todos los archivos modificados
git add .
```

### Guardar cambios (Commit)
Crea un punto de control con los cambios preparados. Es importante usar un mensaje descriptivo:
```bash
git commit -m "Descripción de los cambios realizados"
```

### Subir cambios (Push)
Envía tus commits locales al repositorio remoto:
```bash
git push origin main
```

## 4. Mantenerse Actualizado

Si trabajas en equipo o desde diferentes ordenadores, descarga los cambios más recientes antes de empezar a trabajar:

```bash
git pull origin main
```

## 5. Ramas (Branches)

Es recomendable trabajar en ramas separadas para nuevas funcionalidades:

```bash
# Crear y cambiar a una nueva rama
git checkout -b nombre-nueva-rama

# Volver a la rama principal
git checkout main
```

---
*Esta guía cubre lo esencial para empezar. Para documentación más avanzada, consulta la [documentación oficial de Git](https://git-scm.com/doc).*
# Manual rapido - OrganEyes

## Como abrir la aplicacion

Haz doble clic en `OrganEyes.exe`.

Si quieres ejecutar el codigo fuente directamente:

```powershell
python .\OrganEyes.py
```

## Modo manual

1. Abre la aplicacion.
2. Deja marcado `Manual con selector`.
3. Pulsa `Elegir carpeta`.
4. Elige la carpeta que quieras organizar.
5. Pulsa `Organizar ahora`.

Ese modo ordena una sola vez y no deja nada activo en segundo plano.

## Modo automatico

1. Abre la aplicacion.
2. Marca `Automatico al iniciar Windows`.
3. Pulsa `Agregar carpeta automatica`.
4. Elige una o varias carpetas que quieras organizar automaticamente.
5. Pulsa `Guardar y activar`.

Desde ese momento, al iniciar Windows, OrganEyes revisa esas carpetas, organiza los archivos y se cierra solo.

## Como desactivar el automatico normalmente

1. Abre la aplicacion.
2. Entra en `Automatico al iniciar Windows`.
3. Pulsa `Desactivar inicio automatico`.

Con eso deja de ejecutarse al prender la PC.

## Salida de emergencia

Si algo sale mal al iniciar Windows:

1. Enciende la PC.
2. Cuando estes entrando al escritorio, manten presionada la tecla `Shift`.
3. Sostenla unos segundos.

Si OrganEyes arranca en modo automatico mientras `Shift` esta presionada, cancela ese inicio automatico y no organiza nada en esa sesion.

Eso no lo desactiva para siempre.
Solo lo salta una vez para que puedas entrar y corregir la configuracion.

## Como desactivarlo a mano si no puedes abrir la app

Si necesitas apagarlo manualmente, borra este archivo:

`%APPDATA%\Microsoft\Windows\Start Menu\Programs\Startup\OrganEyes.bat`

Ruta habitual:

`C:\Users\TU_USUARIO\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Startup\OrganEyes.bat`

## Donde guarda la configuracion

La lista de carpetas automaticas se guarda en:

`%APPDATA%\OrganEyes\config.json`

Ruta habitual:

`C:\Users\TU_USUARIO\AppData\Roaming\OrganEyes\config.json`

Si quieres resetear todo, puedes borrar:

1. El `.bat` de inicio automatico.
2. El archivo `config.json`.

## Parametros faciles de modificar en el codigo

En [OrganEyes.py](/C:/Users/igfor/Documents/Codex/2026-05-13/hola-fijate-si-hay-un-archivo/OrganEyes.py) puedes ajustar:

- `MINIMO_PARA_CARPETA_PROPIA = 2`
- `MAXIMO_CARPETAS_PRINCIPALES = 8`
- `NOMBRE_CARPETA_VARIOS = "Varios"`
- `NOMBRE_CARPETA_SIN_EXTENSION = "Sin extension"`
- `VENTANA_CANCELACION_SEGUNDOS = 5`

### Que hace cada una

`MINIMO_PARA_CARPETA_PROPIA`
Cantidad minima de archivos de una extension para merecer una carpeta propia.

`MAXIMO_CARPETAS_PRINCIPALES`
Limita cuantas carpetas por extension puede crear como maximo.

`NOMBRE_CARPETA_VARIOS`
Nombre de la carpeta donde se guardan tipos poco frecuentes.

`NOMBRE_CARPETA_SIN_EXTENSION`
Nombre de la carpeta para archivos sin extension.

`VENTANA_CANCELACION_SEGUNDOS`
Tiempo disponible para cancelar el modo automatico manteniendo `Shift`.

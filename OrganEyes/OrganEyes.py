from __future__ import annotations

"""OrganEyes desktop organizer built with the Python standard library."""

import json
import subprocess
import shutil
import sys
import time
from collections import Counter
import ctypes
from pathlib import Path
import tkinter as tk
from tkinter import filedialog, messagebox, ttk


# Core organization rules.
MINIMO_PARA_CARPETA_PROPIA = 2
MAXIMO_CARPETAS_PRINCIPALES = 8
NOMBRE_CARPETA_VARIOS = "Varios"
NOMBRE_CARPETA_SIN_EXTENSION = "Sin extension"
NOMBRE_APP = "OrganEyes"
MARCA_APP = "By Nani2204 & Codex"
VENTANA_CANCELACION_SEGUNDOS = 5
MOSTRAR_NOTIFICACIONES_AUTOMATICAS = True

# Persistent app data.
APPDATA_DIR = Path.home() / "AppData" / "Roaming"
CONFIG_DIR = APPDATA_DIR / "OrganEyes"
CONFIG_PATH = CONFIG_DIR / "config.json"
STARTUP_DIR = APPDATA_DIR / "Microsoft" / "Windows" / "Start Menu" / "Programs" / "Startup"
STARTUP_BAT = STARTUP_DIR / "OrganEyes.bat"
CARPETAS_SUGERIDAS_USUARIO = ("Downloads", "Descargas")


def nombre_destino_disponible(carpeta_destino: Path, nombre_archivo: str) -> Path:
    """Evita sobreescribir archivos con el mismo nombre."""
    destino = carpeta_destino / nombre_archivo
    if not destino.exists():
        return destino

    stem = Path(nombre_archivo).stem
    suffix = Path(nombre_archivo).suffix
    numero = 1

    while True:
        candidato = carpeta_destino / f"{stem} ({numero}){suffix}"
        if not candidato.exists():
            return candidato
        numero += 1


def detectar_extensiones_principales(archivos: list[Path]) -> set[str]:
    """
    Elige las extensiones mas usadas para crear carpetas propias.
    Las extensiones con pocos archivos van a la carpeta "Varios".
    """
    contador = Counter(
        archivo.suffix.lower().lstrip(".")
        for archivo in archivos
        if archivo.suffix
    )

    extensiones_principales: set[str] = set()
    for extension, cantidad in contador.most_common(MAXIMO_CARPETAS_PRINCIPALES):
        if cantidad >= MINIMO_PARA_CARPETA_PROPIA:
            extensiones_principales.add(extension)

    return extensiones_principales


def organizar_carpeta(ruta_carpeta: str | Path) -> dict[str, int]:
    """
    Ordena una carpeta por tipos principales de archivo.

    - Crea carpetas propias para las extensiones mas usadas.
    - Manda los tipos poco frecuentes a "Varios".
    - Manda los archivos sin extension a "Sin extension".
    - Solo toca archivos del nivel actual, no entra a subcarpetas.
    """
    carpeta = Path(ruta_carpeta).expanduser().resolve()
    if not carpeta.exists():
        raise FileNotFoundError(f"La carpeta no existe: {carpeta}")
    if not carpeta.is_dir():
        raise NotADirectoryError(f"La ruta no es una carpeta: {carpeta}")

    archivos = [item for item in carpeta.iterdir() if item.is_file()]
    if not archivos:
        return {}

    extensiones_principales = detectar_extensiones_principales(archivos)
    resumen: Counter[str] = Counter()

    for archivo in archivos:
        if archivo.suffix:
            extension = archivo.suffix.lower().lstrip(".")
            nombre_carpeta = extension if extension in extensiones_principales else NOMBRE_CARPETA_VARIOS
        else:
            nombre_carpeta = NOMBRE_CARPETA_SIN_EXTENSION

        carpeta_destino = carpeta / nombre_carpeta
        carpeta_destino.mkdir(exist_ok=True)

        destino = nombre_destino_disponible(carpeta_destino, archivo.name)
        shutil.move(str(archivo), str(destino))
        resumen[nombre_carpeta] += 1

    return dict(resumen)


def sugerir_carpeta_usuario() -> Path:
    """
    Devuelve una carpeta comun del usuario para abrir el selector.
    Prioriza Descargas/Downloads si existen; si no, usa la carpeta personal.
    """
    candidatas = [Path.home() / nombre for nombre in CARPETAS_SUGERIDAS_USUARIO]

    for ruta in candidatas:
        if ruta.exists() and ruta.is_dir():
            return ruta

    return Path.home()


def cargar_configuracion() -> dict:
    """Carga la configuracion guardada para el modo automatico."""
    if not CONFIG_PATH.exists():
        return {"carpetas_automaticas": []}

    try:
        return json.loads(CONFIG_PATH.read_text(encoding="utf-8"))
    except (json.JSONDecodeError, OSError):
        return {"carpetas_automaticas": []}


def guardar_configuracion(carpetas: list[str]) -> None:
    """Guarda la lista de carpetas que se ordenaran en modo automatico."""
    CONFIG_DIR.mkdir(parents=True, exist_ok=True)
    data = {"carpetas_automaticas": carpetas}
    CONFIG_PATH.write_text(json.dumps(data, indent=2, ensure_ascii=False), encoding="utf-8")


def obtener_carpetas_automaticas() -> list[Path]:
    """Devuelve las carpetas configuradas para correr automaticamente."""
    data = cargar_configuracion()
    carpetas = data.get("carpetas_automaticas", [])
    return [Path(ruta).expanduser().resolve() for ruta in carpetas]


def crear_inicio_automatico() -> None:
    """
    Crea un .bat en la carpeta de Inicio de Windows.
    Cuando la app arranque con --run-auto, ordena y se cierra sola.
    """
    STARTUP_DIR.mkdir(parents=True, exist_ok=True)

    if getattr(sys, "frozen", False):
        ejecutable = Path(sys.executable).resolve()
        comando = f'"{ejecutable}" --run-auto'
    else:
        script = Path(__file__).resolve()
        comando = f'pythonw "{script}" --run-auto'

    contenido = (
        "@echo off\n"
        f"{comando}\n"
    )
    STARTUP_BAT.write_text(contenido, encoding="utf-8")


def eliminar_inicio_automatico() -> None:
    """Elimina el arranque automatico si ya estaba activado."""
    if STARTUP_BAT.exists():
        STARTUP_BAT.unlink()


def ejecutar_modo_automatico() -> list[str]:
    """
    Corre el organizador sobre las carpetas guardadas.
    Esta funcion esta pensada para el inicio automatico de Windows.
    """
    resultados: list[str] = []

    for carpeta in obtener_carpetas_automaticas():
        if not carpeta.exists():
            resultados.append(f"No existe: {carpeta}")
            continue

        resumen = organizar_carpeta(carpeta)
        if resumen:
            total = sum(resumen.values())
            resultados.append(f"Ordenado: {carpeta} ({total} archivos)")
        else:
            resultados.append(f"Sin cambios: {carpeta}")

    return resultados


def mostrar_notificacion(titulo: str, mensaje: str) -> None:
    """
    Muestra una notificacion simple en Windows.
    Si falla, no interrumpe la ejecucion.
    """
    if not MOSTRAR_NOTIFICACIONES_AUTOMATICAS:
        return

    script = f"""
Add-Type -AssemblyName System.Windows.Forms
Add-Type -AssemblyName System.Drawing
$notify = New-Object System.Windows.Forms.NotifyIcon
$notify.Icon = [System.Drawing.SystemIcons]::Information
$notify.BalloonTipIcon = [System.Windows.Forms.ToolTipIcon]::Info
$notify.BalloonTipTitle = '{titulo.replace("'", "''")}'
$notify.BalloonTipText = '{mensaje.replace("'", "''")}'
$notify.Visible = $true
$notify.ShowBalloonTip(5000)
Start-Sleep -Seconds 6
$notify.Dispose()
"""

    try:
        subprocess.run(
            ["powershell", "-NoProfile", "-WindowStyle", "Hidden", "-Command", script],
            check=False,
            creationflags=0x08000000,
        )
    except Exception:
        pass


def shift_presionado() -> bool:
    """
    Detecta si Shift esta presionado.
    Sirve como salida de emergencia para saltar el modo automatico.
    """
    vk_shift = 0x10
    return bool(ctypes.windll.user32.GetAsyncKeyState(vk_shift) & 0x8000)


def automatico_cancelado_por_usuario() -> bool:
    """
    Da unos segundos para cancelar el arranque automatico manteniendo Shift.
    Esto ayuda si una configuracion molesta al iniciar Windows.
    """
    fin = time.time() + VENTANA_CANCELACION_SEGUNDOS

    while time.time() < fin:
        if shift_presionado():
            return True
        time.sleep(0.1)

    return False


class OrganEyesApp:
    """Interfaz principal de OrganEyes."""

    def __init__(self) -> None:
        self.root = tk.Tk()
        self.root.title(NOMBRE_APP)
        self.root.geometry("980x720")
        self.root.minsize(900, 680)
        self.root.configure(bg="#111827")
        self.root.after(50, self._ajustar_ventana_inicial)

        self.modo = tk.StringVar(value="manual")
        self.carpeta_manual = tk.StringVar(value=str(sugerir_carpeta_usuario()))
        self.estado = tk.StringVar(value="Listo para organizar.")

        self.estilo = ttk.Style()
        self.estilo.theme_use("clam")
        self._configurar_estilos()

        self.frame_manual: ttk.Frame | None = None
        self.frame_automatico: ttk.Frame | None = None
        self.lista_carpetas: tk.Listbox | None = None
        self.cargar_carpetas_automaticas = []

        self._construir_ui()
        self._actualizar_modo()

    def _ajustar_ventana_inicial(self) -> None:
        """
        Abre la ventana maximizada cuando Windows lo permite.
        Si no, la deja centrada en un tamano amplio.
        """
        try:
            self.root.state("zoomed")
            return
        except tk.TclError:
            pass

        ancho = 980
        alto = 720
        pantalla_ancho = self.root.winfo_screenwidth()
        pantalla_alto = self.root.winfo_screenheight()
        x = max((pantalla_ancho - ancho) // 2, 0)
        y = max((pantalla_alto - alto) // 2, 0)
        self.root.geometry(f"{ancho}x{alto}+{x}+{y}")

    def _configurar_estilos(self) -> None:
        self.estilo.configure("App.TFrame", background="#111827")
        self.estilo.configure("Card.TFrame", background="#182235")
        self.estilo.configure("Title.TLabel", background="#111827", foreground="#f9fafb", font=("Segoe UI Semibold", 24))
        self.estilo.configure("Brand.TLabel", background="#111827", foreground="#60a5fa", font=("Segoe UI", 10, "italic"))
        self.estilo.configure("Body.TLabel", background="#182235", foreground="#dbe4f0", font=("Segoe UI", 11))
        self.estilo.configure("Section.TLabel", background="#182235", foreground="#f9fafb", font=("Segoe UI Semibold", 13))
        self.estilo.configure("Status.TLabel", background="#111827", foreground="#cbd5e1", font=("Segoe UI", 10))
        self.estilo.configure("Accent.TButton", background="#2563eb", foreground="#ffffff", borderwidth=0, focusthickness=0, padding=10)
        self.estilo.map("Accent.TButton", background=[("active", "#1d4ed8")])
        self.estilo.configure("Soft.TButton", background="#334155", foreground="#f8fafc", borderwidth=0, focusthickness=0, padding=8)
        self.estilo.map("Soft.TButton", background=[("active", "#475569")])
        self.estilo.configure("Choice.TRadiobutton", background="#182235", foreground="#e5edf7", font=("Segoe UI", 11))
        self.estilo.map("Choice.TRadiobutton", background=[("active", "#182235")], foreground=[("active", "#ffffff")])
        self.estilo.configure("Path.TEntry", fieldbackground="#0f172a", foreground="#f8fafc", padding=8)

    def _construir_ui(self) -> None:
        contenedor = ttk.Frame(self.root, style="App.TFrame", padding=24)
        contenedor.pack(fill="both", expand=True)

        ttk.Label(contenedor, text=NOMBRE_APP, style="Title.TLabel").pack(anchor="w")
        ttk.Label(contenedor, text=MARCA_APP, style="Brand.TLabel").pack(anchor="w", pady=(0, 18))

        tarjeta = ttk.Frame(contenedor, style="Card.TFrame", padding=20)
        tarjeta.pack(fill="both", expand=True)

        ttk.Label(
            tarjeta,
            text="Organiza archivos por sus tipos principales y evita crear carpetas innecesarias para extensiones aisladas.",
            style="Body.TLabel",
            wraplength=650,
        ).pack(anchor="w", pady=(0, 18))

        selector_modo = ttk.Frame(tarjeta, style="Card.TFrame")
        selector_modo.pack(fill="x", pady=(0, 20))

        ttk.Label(selector_modo, text="Modo de uso", style="Section.TLabel").pack(anchor="w")
        ttk.Radiobutton(
            selector_modo,
            text="Manual con selector",
            variable=self.modo,
            value="manual",
            command=self._actualizar_modo,
            style="Choice.TRadiobutton",
        ).pack(anchor="w", pady=(8, 4))
        ttk.Radiobutton(
            selector_modo,
            text="Automatico al iniciar Windows",
            variable=self.modo,
            value="automatico",
            command=self._actualizar_modo,
            style="Choice.TRadiobutton",
        ).pack(anchor="w")

        self.frame_manual = ttk.Frame(tarjeta, style="Card.TFrame")
        self.frame_manual.pack(fill="both", expand=True)
        self._construir_manual(self.frame_manual)

        self.frame_automatico = ttk.Frame(tarjeta, style="Card.TFrame")
        self.frame_automatico.pack(fill="both", expand=True)
        self._construir_automatico(self.frame_automatico)

        pie = ttk.Frame(contenedor, style="App.TFrame")
        pie.pack(fill="x", pady=(14, 0))
        ttk.Label(pie, textvariable=self.estado, style="Status.TLabel").pack(anchor="w")

    def _construir_manual(self, parent: ttk.Frame) -> None:
        ttk.Label(parent, text="Modo manual", style="Section.TLabel").pack(anchor="w")
        ttk.Label(
            parent,
            text="Eliges una carpeta, la ordena una sola vez y termina.",
            style="Body.TLabel",
            wraplength=650,
        ).pack(anchor="w", pady=(4, 14))

        fila = ttk.Frame(parent, style="Card.TFrame")
        fila.pack(fill="x", pady=(0, 12))

        entrada = ttk.Entry(fila, textvariable=self.carpeta_manual, style="Path.TEntry")
        entrada.pack(side="left", fill="x", expand=True, padx=(0, 8))

        ttk.Button(fila, text="Elegir carpeta", command=self._seleccionar_carpeta_manual, style="Soft.TButton").pack(side="left")

        ttk.Button(parent, text="Organizar ahora", command=self._ejecutar_manual, style="Accent.TButton").pack(anchor="w")

    def _construir_automatico(self, parent: ttk.Frame) -> None:
        ttk.Label(parent, text="Modo automatico", style="Section.TLabel").pack(anchor="w")
        ttk.Label(
            parent,
            text="Seleccionas las carpetas con el boton de abajo, las guardas y el programa las ordena solo cada vez que inicia Windows.",
            style="Body.TLabel",
            wraplength=650,
        ).pack(anchor="w", pady=(4, 14))

        ttk.Label(
            parent,
            text="Tip de seguridad: si al arrancar Windows mantienes Shift unos segundos, el modo automatico se salta solo esa vez.",
            style="Body.TLabel",
            wraplength=650,
        ).pack(anchor="w", pady=(0, 12))

        ttk.Button(parent, text="Agregar carpeta automatica", command=self._agregar_carpeta_automatica, style="Accent.TButton").pack(anchor="w", pady=(0, 12))

        ttk.Label(
            parent,
            text="Carpetas automaticas seleccionadas",
            style="Section.TLabel",
        ).pack(anchor="w", pady=(0, 8))

        lista_frame = ttk.Frame(parent, style="Card.TFrame")
        lista_frame.pack(fill="both", expand=True, pady=(0, 12))

        self.lista_carpetas = tk.Listbox(
            lista_frame,
            bg="#0f172a",
            fg="#f8fafc",
            selectbackground="#2563eb",
            selectforeground="#ffffff",
            activestyle="none",
            highlightthickness=0,
            relief="flat",
            font=("Segoe UI", 10),
            height=8,
        )
        self.lista_carpetas.pack(fill="both", expand=True)

        botones = ttk.Frame(parent, style="Card.TFrame")
        botones.pack(fill="x", pady=(0, 12))

        ttk.Button(botones, text="Quitar seleccionada", command=self._quitar_carpeta_automatica, style="Soft.TButton").pack(side="left", padx=(0, 8))
        ttk.Button(botones, text="Probar ahora", command=self._probar_automatico, style="Soft.TButton").pack(side="left")

        acciones = ttk.Frame(parent, style="Card.TFrame")
        acciones.pack(fill="x", pady=(14, 0))

        ttk.Button(acciones, text="Guardar y activar", command=self._guardar_y_activar, style="Accent.TButton").pack(side="left", padx=(0, 8))
        ttk.Button(acciones, text="Desactivar inicio automatico", command=self._desactivar_automatico, style="Soft.TButton").pack(side="left")

        self._refrescar_lista_carpetas()

    def _actualizar_modo(self) -> None:
        if self.frame_manual is None or self.frame_automatico is None:
            return

        if self.modo.get() == "manual":
            self.frame_manual.pack(fill="both", expand=True)
            self.frame_automatico.pack_forget()
            self.estado.set("Modo manual listo.")
        else:
            self.frame_automatico.pack(fill="both", expand=True)
            self.frame_manual.pack_forget()
            self.estado.set("Modo automatico listo.")

    def _seleccionar_carpeta_manual(self) -> None:
        carpeta = filedialog.askdirectory(initialdir=self.carpeta_manual.get() or str(sugerir_carpeta_usuario()))
        if carpeta:
            self.carpeta_manual.set(carpeta)
            self.estado.set(f"Carpeta manual elegida: {carpeta}")

    def _ejecutar_manual(self) -> None:
        ruta = Path(self.carpeta_manual.get()).expanduser()

        try:
            resumen = organizar_carpeta(ruta)
        except (FileNotFoundError, NotADirectoryError) as error:
            messagebox.showerror("Ruta invalida", str(error), parent=self.root)
            self.estado.set("No se pudo organizar la carpeta manual.")
            return
        except Exception as error:
            messagebox.showerror("Error", f"Ocurrio un error inesperado:\n{error}", parent=self.root)
            self.estado.set("Error inesperado en modo manual.")
            return

        if not resumen:
            messagebox.showinfo("Sin cambios", f"No habia archivos para ordenar en:\n{ruta}", parent=self.root)
            self.estado.set("No habia archivos para mover en modo manual.")
            return

        total = sum(resumen.values())
        detalle = "\n".join(f"- {nombre}: {cantidad}" for nombre, cantidad in sorted(resumen.items()))
        messagebox.showinfo("Carpeta ordenada", f"Se ordenaron {total} archivo(s) en:\n{ruta}\n\n{detalle}", parent=self.root)
        self.estado.set(f"Modo manual completo. Archivos movidos: {total}.")

    def _agregar_carpeta_automatica(self) -> None:
        carpeta = filedialog.askdirectory(initialdir=str(sugerir_carpeta_usuario()))
        if not carpeta:
            return

        ruta = str(Path(carpeta).resolve())
        carpetas = self._leer_lista_visual()
        if ruta not in carpetas:
            carpetas.append(ruta)
            self._cargar_lista_visual(carpetas)
            self.estado.set(f"Agregada: {ruta}")

    def _quitar_carpeta_automatica(self) -> None:
        if self.lista_carpetas is None:
            return

        seleccion = self.lista_carpetas.curselection()
        if not seleccion:
            return

        indice = seleccion[0]
        carpetas = self._leer_lista_visual()
        ruta = carpetas.pop(indice)
        self._cargar_lista_visual(carpetas)
        self.estado.set(f"Quitada: {ruta}")

    def _guardar_y_activar(self) -> None:
        carpetas = self._leer_lista_visual()
        if not carpetas:
            messagebox.showwarning("Sin carpetas", "Agrega al menos una carpeta para el modo automatico.", parent=self.root)
            return

        guardar_configuracion(carpetas)
        crear_inicio_automatico()
        self.estado.set("Modo automatico guardado y activado.")
        messagebox.showinfo(
            "Automatico activado",
            "La configuracion se guardo correctamente.\nOrganEyes correra al iniciar Windows y se cerrara solo.",
            parent=self.root,
        )

    def _desactivar_automatico(self) -> None:
        eliminar_inicio_automatico()
        self.estado.set("Inicio automatico desactivado.")
        messagebox.showinfo("Desactivado", "Se desactivo el inicio automatico.", parent=self.root)

    def _probar_automatico(self) -> None:
        carpetas = self._leer_lista_visual()
        if not carpetas:
            messagebox.showwarning("Sin carpetas", "Agrega al menos una carpeta antes de probar.", parent=self.root)
            return

        guardar_configuracion(carpetas)
        resultados = ejecutar_modo_automatico()
        mensaje = "\n".join(resultados) if resultados else "No habia carpetas configuradas."
        messagebox.showinfo("Prueba completada", mensaje, parent=self.root)
        self.estado.set("Prueba del modo automatico terminada.")

    def _refrescar_lista_carpetas(self) -> None:
        carpetas = [str(ruta) for ruta in obtener_carpetas_automaticas()]
        self._cargar_lista_visual(carpetas)

    def _leer_lista_visual(self) -> list[str]:
        if self.lista_carpetas is None:
            return []
        return list(self.lista_carpetas.get(0, tk.END))

    def _cargar_lista_visual(self, carpetas: list[str]) -> None:
        if self.lista_carpetas is None:
            return

        self.lista_carpetas.delete(0, tk.END)
        for carpeta in carpetas:
            self.lista_carpetas.insert(tk.END, carpeta)

    def run(self) -> None:
        self.root.mainloop()


def main() -> None:
    """Punto de entrada principal de la app."""
    if "--run-auto" in sys.argv:
        if automatico_cancelado_por_usuario():
            return
        carpetas = obtener_carpetas_automaticas()
        if not carpetas:
            mostrar_notificacion(NOMBRE_APP, "No hay carpetas automaticas configuradas. No se hizo ningun cambio.")
            return

        resultados = ejecutar_modo_automatico()
        resumen = "\n".join(resultados[:4]) if resultados else "No se hizo ningun cambio."
        mostrar_notificacion(NOMBRE_APP, resumen)
        return

    app = OrganEyesApp()
    app.run()


if __name__ == "__main__":
    main()

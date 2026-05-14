# OrganEyes

OrganEyes is a lightweight Windows desktop app that organizes files by their most common extensions.

It is designed for people who want a quick way to clean folders such as Downloads, Documents, Music, or any custom directory without installing extra dependencies.

## Features

- Manual mode with folder picker
- Automatic mode that runs when Windows starts
- Smart grouping by common file extensions
- Rare extensions grouped into `Varios`
- Files without extension grouped into `Sin extension`
- Emergency skip for automatic mode by holding `Shift` during startup
- Windows notification after automatic runs
- Built only with the Python standard library

## Project files

- [OrganEyes.py](/C:/Users/igfor/Documents/Codex/2026-05-13/hola-fijate-si-hay-un-archivo/OrganEyes.py): source code for the distributable app
- [dist/OrganEyes.exe](/C:/Users/igfor/Documents/Codex/2026-05-13/hola-fijate-si-hay-un-archivo/dist/OrganEyes.exe): compiled Windows executable
- [Manual - OrganEyes.md](/C:/Users/igfor/Documents/Codex/2026-05-13/hola-fijate-si-hay-un-archivo/Manual%20-%20OrganEyes.md): end-user usage guide

## How it organizes files

1. It scans only the selected folder level.
2. It counts the most common file extensions.
3. It creates dedicated folders only for the most repeated extensions.
4. Less common extensions go into `Varios`.
5. Files without extension go into `Sin extension`.
6. Name collisions are resolved safely with `file (1).ext`, `file (2).ext`, and so on.

## Running from source

Requirements:

- Windows
- Python 3.12 or newer recommended

Run:

```powershell
python .\OrganEyes.py
```

## Building the executable

OrganEyes itself uses only the standard library.
To rebuild the `.exe`, install PyInstaller and run:

```powershell
python -m pip install pyinstaller
python -m PyInstaller --onefile --windowed --name OrganEyes .\OrganEyes.py
```

The generated executable will appear in `dist\`.

## Automatic mode

Automatic mode does not guess folders on its own.
The user must explicitly choose which folders should be organized automatically.

If no folders are configured, OrganEyes exits without changing anything and shows a notification.

## Safety notes

- OrganEyes does not recurse into subfolders.
- OrganEyes does not overwrite files with the same name.
- Automatic mode can be skipped for one startup session by holding `Shift` while Windows is loading the desktop.

## Notes

This repository contains the distributable app project only.
The personal organizer script used during development is intentionally not part of this public project.

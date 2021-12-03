# Required if you want to see qDebug() messages
CONFIG += debug

# Place auto-generated files in "invisible" subdirectories
win32 {
    MOC_DIR = _moc
    UI_DIR  = _ui
    OBJECTS_DIR = _obj
} else {
    MOC_DIR = .moc
    UI_DIR  = .ui
    OBJECTS_DIR = .obj
}

# Rules below apply to TEMPLATE=app projects only:
app {
    # Place executable in same folder:
    DESTDIR=$$OUT_PWD

    # Don't place executables in an app bundle on macOS
    # This also permits console apps to work on the mac.
    mac {
        CONFIG -= app_bundle
    }

    # Open a console for stdin, stdout, and stderr Windows:
    win32 {
        CONFIG += console
    }
}
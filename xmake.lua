set_project("To-do List")
set_languages("c++20")
add_rules("mode.debug", "mode.release")

-- Archivos de logica que usan el programa y las pruebas
local logica = {
    "Validaciones y Mensajes/Validaciones.cpp",
    "Validaciones y Mensajes/mensajes.cpp",
    "Clases Tareas/Tarea.cpp",
    "Lista de tareas/Listatareas.cpp",
    "fecha.cpp",
    "tarea_fecha_limite.cpp",
    "tarea_prioritaria.cpp"
}

-- Programa principal: xmake run todo
target("todo")
    set_kind("binary")
    set_default(true)
    add_files("To-do list.cpp", "menu/Menu.cpp")
    add_files(table.unpack(logica))

-- Pruebas, con su propio main: xmake run pruebas
target("pruebas")
    set_kind("binary")
    set_default(false)
    add_files("Validaciones y Mensajes/Pruebas.cpp")
    add_files(table.unpack(logica))

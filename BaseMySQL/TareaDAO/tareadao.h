#pragma once
#include "Clases Tareas/tarea.h"
#include "../basedao.h"
#include <string>
#include <vector>
#include <memory>

using namespace std;

class TareaDAO
{
    private:
        BaseDAO& db;
    
    public:
        TareaDAO(BaseDAO& conexion);

        bool insertar(const Tarea& tarea, int id_usuario);
        unique_ptr<Tarea> buscar_conId(int id, int id_usuario);
        vector<unique_ptr<Tarea>> obtenerTareas(int id_usuario);
        bool actualizarTarea(const Tarea& tarea, int id_usuario);
        bool eliminarTarea(int id, int id_usuario);
};
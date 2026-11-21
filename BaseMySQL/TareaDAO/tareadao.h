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
        bool insertar(const Tarea& tarea);
        unique_ptr<Tarea> buscar_conId(int id);
        vector<unique_ptr<Tarea>> obtenerTareas();
        bool actualizarTarea(const Tarea& tarea);
        bool eliminarTarea(int id);
};
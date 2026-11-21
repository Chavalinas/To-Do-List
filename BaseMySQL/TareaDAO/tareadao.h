#pragma once 
#include "../basedao.h"
#include <string>
#include <memory>

using namespace std;

class TareaDAO
{
    private:
        BaseDAO& db;
    
    public:
        TareaDAO(BaseDAO& conexion);
}
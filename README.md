# Link del Repositorio 


https://github.com/junx21/CasoIntegrador4.git


# Proyecto: Tiny Lisp Intérprete

## Enunciado del Proyecto  

Este proyecto consiste en la implementación de un intérprete de "tiny-lisp" basado en la clase **Variant** y utilizando las capacidades de la **Standard Template Library (STL)** de C++.  

El desarrollo debe realizarse en **CLion**, cumpliendo con los requisitos funcionales y el formato de entrega especificado.  

## Requisitos del Proyecto  

1. **Definir e implementar una clase Variant**:  
   Esta clase deberá ser capaz de representar diferentes tipos de datos, incluyendo símbolos, números, listas y procedimientos.  

2. **Métodos de la clase Variant**:  
   - `to_string()`: Convierte una instancia de la clase en una cadena de texto.  
   - `to_json_string()`: Convierte una instancia de la clase en una representación en formato JSON.  
   - `from_json_string(std::string)`: Método estático que toma una cadena en formato JSON y la convierte en una instancia de la clase Variant.  
   - `parse_json(jsonlib::Json)`: Convierte un objeto JSON en una instancia de la clase Variant.  

## Rúbrica de Evaluación  

| **Aspecto**                       | **Porcentaje** | **Descripción**                                                                                                                                               |  
|------------------------------------|----------------|---------------------------------------------------------------------------------------------------------------------------------------------------------------|  
| Implementación de la clase Variant | 30%            | La clase Variant debe ser implementada correctamente, incluyendo todos los tipos de datos requeridos.                                                          |  
| Método `to_string()`               | 20%            | Devuelve una representación textual adecuada de una instancia de la clase Variant.                                                                             |  
| Método `to_json_string()`          | 20%            | Convierte una instancia en una representación JSON válida.                                                                                                     |  
| Método estático `from_json_string()`| 15%           | Convierte una cadena JSON en una instancia de la clase Variant.                                                                                                |  
| Método `parse_json()`              | 15%            | Convierte un objeto JSON en una instancia de la clase Variant.                                                                                                 |  

## Código de Ejemplo  

El siguiente código implementa la clase **Variant** con los métodos requeridos.  

```cpp
#include <vector>
#include <string>
#include <map>
#include "json11.hpp" // Asegúrate de tener esta biblioteca en tu sistema
#include "jsonlib.hpp" // Asegúrate de tener esta biblioteca en tu sistema

enum variant_type { Symbol, Number, List, Proc, Lambda, Cadena };

struct Entorno;

class Variant {
public:
    typedef Variant(*proc_type)(const std::vector<Variant>&);
    typedef std::vector<Variant>::const_iterator iter;
    typedef std::map<std::string, Variant> map;

    variant_type type;
    std::string val;
    std::vector<Variant> list;
    proc_type proc;
    Entorno* env;

    Variant(variant_type type = Symbol) : type(type), env(0), proc(0) { }
    Variant(variant_type type, const std::string& val) : type(type), val(val), env(0), proc(0) { }
    Variant(proc_type proc) : type(Proc), proc(proc), env(0) { }

    std::string to_string();
    std::string to_json_string();
    static Variant from_json_string(std::string json);
    static Variant parse_json(jsonlib::Json job);  // Verifica la definición correcta de la función
};

std::string Variant::to_string() {
    // Implementación pendiente
}

std::string Variant::to_json_string() {
    // Implementación pendiente
}

Variant Variant::from_json_string(std::string sjson) {
    // Implementación pendiente
}

Variant Variant::parse_json(jsonlib::Json job) {
    // Implementación pendiente
}
```

### Para añadir json11

Primero, descarga json11. Puedes hacerlo clonando el repositorio de GitHub:

git clone https://github.com/dropbox/json11.git

Después de clonar, tendrás una carpeta llamada "json11" en tu proyecto.
Modifica tu CMakeLists.txt para incluir json11. Debería verse así:

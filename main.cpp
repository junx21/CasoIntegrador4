#include "variant/variant.h"
#include <iostream>


int main() {
    // Crear instancias de Variant
    Variant symbol(Symbol, "x");
    Variant number(Number, "3.14");
    Variant list(List);
    list.list.push_back(symbol);
    list.list.push_back(number);

    // Mostrar los resultados
    std::cout << "Symbol: " << symbol.to_string() << std::endl;
    std::cout << "Number: " << number.to_string() << std::endl;
    std::cout << "List: " << list.to_string() << std::endl;

    // Convertir a JSON y mostrar
    std::string json = list.to_json_string();
    std::cout << "JSON: " << json << std::endl;

    // Parsear desde JSON y mostrar
    try {
        Variant parsed = Variant::from_json_string(json);
        std::cout << "Parsed: " << parsed.to_string() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}

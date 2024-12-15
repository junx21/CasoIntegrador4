#ifndef VARIANT_H
#define VARIANT_H

#include <vector>
#include <string>
#include <map>
#include <json11.hpp> // Asegúrate de tener esta biblioteca en tu sistema

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

    Variant(variant_type type = Symbol);
    Variant(variant_type type, const std::string& val);
    Variant(proc_type proc);

    std::string to_string() const;
    std::string to_json_string() const;
    static Variant from_json_string(const std::string& json);
    static Variant parse_json(const json11::Json& parsed);
};

#endif // VARIANT_H

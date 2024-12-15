#include "variant.h"
#include <sstream>
#include <stdexcept>

Variant::Variant(variant_type type) : type(type), env(nullptr), proc(nullptr) {}
Variant::Variant(variant_type type, const std::string& val) : type(type), val(val), env(nullptr), proc(nullptr) {}
Variant::Variant(proc_type proc) : type(Proc), proc(proc), env(nullptr) {}

std::string Variant::to_string() const {
    std::ostringstream oss;
    switch (type) {
        case Symbol:
        case Cadena:
        case Number:
            oss << val;
            break;
        case List:
            oss << "(";
            for (size_t i = 0; i < list.size(); ++i) {
                if (i > 0) oss << " ";
                oss << list[i].to_string();
            }
            oss << ")";
            break;
        case Proc:
        case Lambda:
            oss << "<procedure>";
            break;
    }
    return oss.str();
}

std::string Variant::to_json_string() const {
    json11::Json::object obj;
    obj["type"] = json11::Json(static_cast<int>(type));

    switch (type) {
        case Symbol:
        case Cadena:
        case Number:
            obj["value"] = json11::Json(val);
            break;
        case List: {
            json11::Json::array arr;
            for (const auto& item : list) {
                std::string err; // Variable para almacenar errores
                json11::Json parsed = json11::Json::parse(item.to_json_string(), err); // Cambiado aquí
                if (!err.empty()) {
                    throw std::runtime_error("JSON parsing error: " + err);
                }
                arr.push_back(parsed);
            }
            obj["value"] = arr;
            break;
        }
        case Proc:
        case Lambda:
            obj["value"] = json11::Json("<procedure>");
            break;
    }

    return json11::Json(obj).dump();
}

Variant Variant::from_json_string(const std::string& json) {
    std::string err;
    json11::Json parsed = json11::Json::parse(json, err);
    if (!err.empty()) {
        throw std::runtime_error("JSON parsing error: " + err);
    }
    return parse_json(parsed);
}

Variant Variant::parse_json(const json11::Json& parsed) {
    if (!parsed.is_object()) {
        throw std::runtime_error("Invalid JSON format");
    }

    int type = parsed["type"].int_value();
    Variant result(static_cast<variant_type>(type));

    switch (result.type) {
        case Symbol:
        case Cadena:
        case Number:
            result.val = parsed["value"].string_value();
            break;
        case List:
            for (const auto& item : parsed["value"].array_items()) {
                result.list.push_back(parse_json(item));
            }
            break;
        case Proc:
        case Lambda:
            throw std::runtime_error("Cannot deserialize procedures");
    }

    return result;
}

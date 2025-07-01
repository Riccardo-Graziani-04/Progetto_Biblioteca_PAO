#include "Json.h"
#include "JsonVisitor.h"

namespace JSON {

  Json::Json(JsonReader& reader) : reader(reader) {}

  JsonReader& Json::getReader() const {
    return reader;
  }

  QJsonObject Json::fromObj(const Items::AbstractItem& item) const {
    JsonVisitor jsonVisitor;
    item.accept(jsonVisitor);
    return jsonVisitor.getObj();
  }

  Items::AbstractItem* Json::toObj(const QJsonObject& json) const {
    return reader.read(json);
  }

}

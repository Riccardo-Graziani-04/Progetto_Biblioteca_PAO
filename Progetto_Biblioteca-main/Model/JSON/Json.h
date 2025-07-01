#ifndef JSON_H
#define JSON_H

#include <QJsonObject>

#include "../Items/AbstractItem.h"
#include "JsonReader.h"

namespace JSON {

  class Json {

    private:
      JsonReader& reader;

    public:
      Json(JsonReader& reader);

      JsonReader& getReader() const;
      QJsonObject fromObj(const Items::AbstractItem& item) const;
      Items::AbstractItem* toObj(const QJsonObject& json) const;

};

}
#endif // JSON_H

#ifndef JSONREADER_H
#define JSONREADER_H

#include <QJsonObject>

#include "../Items/AbstractItem.h"

namespace JSON {

  class JsonReader {

    private:
      std::map<unsigned int, Items::AbstractItem*> cachedObj;

      Items::AbstractItem* readBook(const QJsonObject& obj) const;
      Items::AbstractItem* readMovie(const QJsonObject& obj) const;
      Items::AbstractItem* readMusic(const QJsonObject& obj) const;

    public:
      JsonReader();

      Items::AbstractItem* read(const QJsonObject& obj);
      const std::map<unsigned int, Items::AbstractItem*>& getCachedObj() const;
      JsonReader& clear();

  };

}

#endif // JSONREADER_H

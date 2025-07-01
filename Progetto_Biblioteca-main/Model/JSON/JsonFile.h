#ifndef JSONFILE_H
#define JSONFILE_H

#include "../Items/AbstractItem.h"
#include "Json.h"

namespace JSON {

  class JsonFile {

    private:
      std::string path;
      Json& converter;

    public:
      JsonFile(const std::string& path, Json& converter);

      static JsonFile fromPath(const std::string& path);
      const std::string& getPath() const;
      JsonFile& setPath(const std::string& path);
      const Json& getConverter() const;
      JsonFile& store(const std::vector<Items::AbstractItem*> items);
      std::vector<Items::AbstractItem*> load();
  };

}

#endif // JSONFILE_H

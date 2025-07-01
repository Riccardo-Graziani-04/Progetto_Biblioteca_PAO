#ifndef JSONREPOSITORY_H
#define JSONREPOSITORY_H

#include "JsonFile.h"

namespace JSON {

  class JsonRepository {

    private:
      std::map<unsigned int, Items::AbstractItem*> repository;
      JsonFile dataMapper;

    public:
      JsonRepository(JsonFile& dataMapper);
      ~JsonRepository();

      static JsonRepository fromPath(const std::string& path);
      const JsonFile& getDataMapper() const;
      const std::map<unsigned int, Items::AbstractItem*>& getRepository() const;
      const std::string& getPath() const;
      JsonRepository& setPath(const std::string& path);
      JsonRepository& create(Items::AbstractItem* item);
      Items::AbstractItem* read(const unsigned int id) const;
      JsonRepository& update(Items::AbstractItem* item);
      JsonRepository& remove(const unsigned int id);
      std::vector<Items::AbstractItem*> readAll() const;
      JsonRepository& store();

  };

}

#endif // JSONREPOSITORY_H

#include "JsonRepository.h"
#include "JsonReader.h"
#include "Json.h"

namespace JSON {

  JsonRepository::JsonRepository(JsonFile& dataMapper) : dataMapper(dataMapper)
  {
    std::vector<Items::AbstractItem*> items(dataMapper.load());

    for (auto cit = items.begin(); cit != items.end(); ++cit) {
      repository[(*cit)->getID()] = *cit;
    }
  }

  JsonRepository::~JsonRepository() {
    for (auto cit = repository.begin(); cit != repository.end(); ++cit) {
      delete cit->second;
    }
  }

  JsonRepository JsonRepository::fromPath(const std::string& path) {
    JsonReader reader;
    Json converter(reader);
    JsonFile dataMapper(path, converter);
    JsonRepository repository(dataMapper);
    return repository;
  }

  const JsonFile& JsonRepository::getDataMapper() const {
    return dataMapper;
  }

  const std::map<unsigned int, Items::AbstractItem*>& JsonRepository::getRepository() const {
    return repository;
  }

  const std::string& JsonRepository::getPath() const {
    return dataMapper.getPath();
  }

  JsonRepository& JsonRepository::setPath(const std::string& path) {
    dataMapper.setPath(path);
    return *this;
  }

  JsonRepository& JsonRepository::create(Items::AbstractItem* item) {
    repository[item->getID()] = item;
    return *this;
  }

  Items::AbstractItem* JsonRepository::read(const unsigned int id) const {
    std::map<unsigned int, Items::AbstractItem*>::const_iterator cit = repository.find(id);

    if (cit == repository.end()) {
      throw std::out_of_range("Trying to read an undefined id.");
    }

    return cit->second;
  }

  JsonRepository& JsonRepository::update(Items::AbstractItem* item) {
    return create(item);
  }

  JsonRepository& JsonRepository::remove(const unsigned int id) {
    std::map<unsigned int, Items::AbstractItem*>::const_iterator cit = repository.find(id);

    if (cit != repository.end()) {
      repository.erase(cit);
    }

    return *this;
  }

  std::vector<Items::AbstractItem*> JsonRepository::readAll() const {
    std::vector<Items::AbstractItem*> items;

    for (auto cit = repository.begin(); cit != repository.end(); ++cit) {
      items.push_back(cit->second);
    }

    return items;
  }

  JsonRepository& JsonRepository::store() {
    dataMapper.store(readAll());
    return *this;
  }

}

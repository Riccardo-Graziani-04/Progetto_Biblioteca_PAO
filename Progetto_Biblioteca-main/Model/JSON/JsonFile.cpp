#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>

#include "JsonFile.h"
#include "JsonReader.h"

namespace JSON {

  JsonFile::JsonFile(const std::string& path, Json& converter)
  : path(path), converter(converter) {}

  JsonFile JsonFile::fromPath(const std::string& path) {
    JsonReader reader;
    Json converter(reader);
    JsonFile dataMapper(path, converter);
    return dataMapper;
  }

  const std::string& JsonFile::getPath() const {
    return path;
  }

  JsonFile& JsonFile::setPath(const std::string& path) {
    this->path = path;
    return *this;
  }

  const Json& JsonFile::getConverter() const {
    return converter;
  }

  JsonFile& JsonFile::store(const std::vector<Items::AbstractItem*> items) {
    QJsonArray jsonItems;

    for (auto cit = items.begin(); cit != items.end(); ++cit) {
      jsonItems.push_back(converter.fromObj(**cit));
    }

    QJsonDocument document(jsonItems);
    QFile jsonFile(QString::fromStdString(path));
    jsonFile.open(QFile::WriteOnly);
    jsonFile.write(document.toJson());
    jsonFile.close();

    return *this;
  }

  std::vector<Items::AbstractItem*> JsonFile::load() {
    std::vector<Items::AbstractItem*> items;

    QFile jsonFile(QString::fromStdString(path));
    jsonFile.open(QFile::ReadOnly);
    QByteArray data = jsonFile.readAll();
    jsonFile.close();

    QJsonDocument document = QJsonDocument::fromJson(data);
    QJsonArray jsonItems = document.array();

    for (const QJsonValue& val : jsonItems) {
      QJsonObject jsonObj = val.toObject();
      items.push_back(converter.toObj(jsonObj));
    }

    return items;
  }

}

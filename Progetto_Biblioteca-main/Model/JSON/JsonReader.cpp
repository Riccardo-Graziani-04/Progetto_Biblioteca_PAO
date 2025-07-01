#include "JsonReader.h"
#include "../Utility/EnumsConvertions.h"
#include "../Items/Book.h"
#include "../Items/Movie.h"
#include "../Items/Music.h"

namespace JSON {

  JsonReader::JsonReader() {}

  Items::AbstractItem* JsonReader::read(const QJsonObject& obj) {
    QJsonValue objType = obj.value("type");

    if (objType.isUndefined()) {
      throw std::invalid_argument("Item type is missing");
    }

    const unsigned int id = obj.value("id").toInt();

    if (cachedObj.count(id) > 0) {
      return cachedObj[id];
    }
    else if (objType.toString().compare("book") == 0) {
      cachedObj[id] = readBook(obj);
    }
    else if (objType.toString().compare("movie") == 0) {
      cachedObj[id] = readMovie(obj);
    }
    else if (objType.toString().compare("music") == 0) {
      cachedObj[id] = readMusic(obj);
    }
    else {
      throw std::invalid_argument("Unknown item type detected");
    }

    return cachedObj[id];
  }

  const std::map<unsigned int, Items::AbstractItem*>& JsonReader::getCachedObj() const {
    return cachedObj;
  }

  JsonReader& JsonReader::clear() {
    cachedObj.clear();
    return *this;
  }

  Items::AbstractItem* JsonReader::readBook(const QJsonObject& obj) const {
    return new Items::Book(obj.value("title").toString().toStdString(),
                           obj.value("id").toInt(),
                           obj.value("author").toString().toStdString(),
                           obj.value("release_year").toInt(),
                           obj.value("image").toString().toStdString(),
                           obj.value("publisher").toString().toStdString(),
                           obj.value("language").toString().toStdString(),
                           Enums::stringToBookMovieGenre(obj.value("genre").toString().toStdString())
                           );
  }

  Items::AbstractItem* JsonReader::readMovie(const QJsonObject& obj) const {
    return new Items::Movie(obj.value("title").toString().toStdString(),
                           obj.value("id").toInt(),
                           obj.value("author").toString().toStdString(),
                           obj.value("release_year").toInt(),
                           obj.value("image").toString().toStdString(),
                           obj.value("language").toString().toStdString(),
                           obj.value("duration").toInt(),
                           Enums::stringToBookMovieGenre(obj.value("genre").toString().toStdString()),
                           Enums::stringToAgeRating(obj.value("age_rating").toString().toStdString())
                           );
  }

  Items::AbstractItem* JsonReader::readMusic(const QJsonObject& obj) const {
    return new Items::Music(obj.value("title").toString().toStdString(),
                           obj.value("id").toInt(),
                           obj.value("author").toString().toStdString(),
                           obj.value("release_year").toInt(),
                           obj.value("image").toString().toStdString(),
                           obj.value("album").toString().toStdString(),
                           obj.value("duration").toInt(),
                           obj.value("explicit_language").toInt() ? true : false,
                           Enums::stringToMusicGenres(obj.value("genre").toString().toStdString())
                           );
  }

}

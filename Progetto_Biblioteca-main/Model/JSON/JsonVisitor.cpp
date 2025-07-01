#include "JsonVisitor.h"
#include "../Utility/EnumsConvertions.h"

namespace JSON {

  JsonVisitor::JsonVisitor() {}

  QJsonObject JsonVisitor::getObj() const {
    return obj;
  }

  void JsonVisitor::visit(const Items::Book& book) {
    QJsonObject bookObj;

    bookObj.insert("type", QJsonValue::fromVariant("book"));
    bookObj.insert("title", QJsonValue::fromVariant(QString::fromStdString(book.getTitle())));
    bookObj.insert("id", QJsonValue::fromVariant(book.getID()));
    bookObj.insert("author", QJsonValue::fromVariant(QString::fromStdString(book.getAuthor())));
    bookObj.insert("release_year", QJsonValue::fromVariant(book.getReleaseYear()));
    bookObj.insert("image", QJsonValue::fromVariant(QString::fromStdString(book.getImage())));
    bookObj.insert("publisher", QJsonValue::fromVariant(QString::fromStdString(book.getPublisher())));
    bookObj.insert("language", QJsonValue::fromVariant(QString::fromStdString(book.getLanguage())));
    bookObj.insert("genre", QJsonValue::fromVariant(QString::fromStdString(Enums::bookMovieGenresToString(book.getGenre()))));

    obj = bookObj;
  }

  void JsonVisitor::visit(const Items::Movie& movie) {
    QJsonObject movieObj;

    movieObj.insert("type", QJsonValue::fromVariant("movie"));
    movieObj.insert("title", QJsonValue::fromVariant(QString::fromStdString(movie.getTitle())));
    movieObj.insert("id", QJsonValue::fromVariant(movie.getID()));
    movieObj.insert("author", QJsonValue::fromVariant(QString::fromStdString(movie.getAuthor())));
    movieObj.insert("release_year", QJsonValue::fromVariant(movie.getReleaseYear()));
    movieObj.insert("image", QJsonValue::fromVariant(QString::fromStdString(movie.getImage())));
    movieObj.insert("language", QJsonValue::fromVariant(QString::fromStdString(movie.getLanguage())));
    movieObj.insert("duration", QJsonValue::fromVariant(movie.getDuration()));
    movieObj.insert("genre", QJsonValue::fromVariant(QString::fromStdString(Enums::bookMovieGenresToString(movie.getGenre()))));
    movieObj.insert("age_rating", QJsonValue::fromVariant(QString::fromStdString(Enums::movieAgeRatingsToString(movie.getAgeRating()))));

    obj = movieObj;
  }

  void JsonVisitor::visit(const Items::Music& music) {
    QJsonObject musicObj;

    musicObj.insert("type", QJsonValue::fromVariant("music"));
    musicObj.insert("title", QJsonValue::fromVariant(QString::fromStdString(music.getTitle())));
    musicObj.insert("id", QJsonValue::fromVariant(music.getID()));
    musicObj.insert("author", QJsonValue::fromVariant(QString::fromStdString(music.getAuthor())));
    musicObj.insert("release_year", QJsonValue::fromVariant(music.getReleaseYear()));
    musicObj.insert("image", QJsonValue::fromVariant(QString::fromStdString(music.getImage())));
    musicObj.insert("album", QJsonValue::fromVariant(QString::fromStdString(music.getAlbum())));
    musicObj.insert("duration", QJsonValue::fromVariant(music.getDuration()));
    musicObj.insert("explicit_language", QJsonValue::fromVariant((music.isExplicit()) ? "Yes" : "No"));
    musicObj.insert("genre", QJsonValue::fromVariant(QString::fromStdString(Enums::musicGenreToString(music.getGenre()))));

    obj = musicObj;
  }

}

#include "Music.h"

namespace Items {

  Music::Music(String title,
               unsigned int id,
               String author,
               unsigned int releaseYear,
               String image,
               String album,
               unsigned int duration,
               bool explicitLanguage,
               Enums::MusicGenres genre)
  : AbstractItem(title, id, author, releaseYear, image),
    album(album),
    duration(duration),
    explicitLanguage(explicitLanguage),
    genre(genre) {}

  const String& Music::getAlbum() const {
    return album;
  }

  unsigned int Music::getDuration() const {
    return duration;
  }

  bool Music::isExplicit() const {
    return explicitLanguage;
  }

  Enums::MusicGenres Music::getGenre() const {
    return genre;
  }

  Music& Music::setAlbum(const String& album) {
    this->album = album;
    return *this;
  }

  Music& Music::setDuration(unsigned int duration) {
    this->duration = duration;
    return *this;
  }

  Music& Music::setExplicit(bool explicitLanguage) {
    this->explicitLanguage = explicitLanguage;
    return *this;
  }

  Music& Music::setGenre(Enums::MusicGenres genre) {
    this->genre = genre;
    return *this;
  }

  void Music::accept(Visitor::ItemVisitor& visitor) {
    visitor.visit(*this);
  }

  void Music::accept(Visitor::ConstItemVisitor& constVisitor) const {
    constVisitor.visit(*this);
  }

}


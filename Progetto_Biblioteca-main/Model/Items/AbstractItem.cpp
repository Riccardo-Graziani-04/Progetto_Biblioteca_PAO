#include "AbstractItem.h"

namespace Items {

  AbstractItem::AbstractItem(String title,
                             unsigned int id,
                             String author,
                             unsigned int releaseYear,
                             String image)
  : title(title),
    id(id),
    author(author),
    releaseYear(releaseYear),
    image(image) {}

  const String& AbstractItem::getTitle() const {
    return title;
  }

  unsigned int AbstractItem::getID() const {
    return id;
  }

  const String& AbstractItem::getAuthor() const {
    return author;
  }

  unsigned int AbstractItem::getReleaseYear() const {
    return releaseYear;
  }

  const String& AbstractItem::getImage() const {
    return image;
  }

  AbstractItem& AbstractItem::setTitle(const String& title) {
    this->title = title;
    return *this;
  }

  AbstractItem& AbstractItem::setID(unsigned int id) {
    this->id = id;
    return *this;
  }

  AbstractItem& AbstractItem::setAuthor(const String& author) {
    this->author = author;
    return *this;
  }

  AbstractItem& AbstractItem::setReleaseYear(unsigned int releaseYear) {
    this->releaseYear = releaseYear;
    return *this;
  }

  AbstractItem& AbstractItem::setImage(const String& image) {
    this->image = image;
    return *this;
  }

}

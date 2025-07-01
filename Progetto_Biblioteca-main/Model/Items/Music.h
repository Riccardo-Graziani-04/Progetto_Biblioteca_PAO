#ifndef MUSIC_H
#define MUSIC_H

#include "AbstractItem.h"
#include "../Utility/ItemsEnums.h"

namespace Items {

  class Music : public AbstractItem {

    private:
      String album;
      unsigned int duration;
      bool explicitLanguage;
      Enums::MusicGenres genre;

    public:
      Music(String title,
            unsigned int id,
            String author,
            unsigned int releaseYear,
            String image,
            String album,
            unsigned int duration,
            bool explicitLanguage,
            Enums::MusicGenres genre);

      virtual void accept(Visitor::ItemVisitor& visitor) final;
      virtual void accept(Visitor::ConstItemVisitor& constVisitor) const final;

      const String& getAlbum() const;
      unsigned int getDuration() const;
      bool isExplicit() const;
      Enums::MusicGenres getGenre() const;

      Music& setAlbum(const String& album);
      Music& setDuration(unsigned int duration);
      Music& setExplicit(bool explicitLanguage);
      Music& setGenre(Enums::MusicGenres genre);

  };

}


#endif // MUSIC_H

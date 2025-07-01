#ifndef ITEMREPOSITORY_H
#define ITEMREPOSITORY_H

#include <vector>

#include "../Items/AbstractItem.h"

namespace Memory {

  class ItemRepository {

    /*
      Utilizzo del pattern Singleton per condividere la memoria
      in cui gli oggetti creati sono salvati
    */

    private:
      std::vector<const Items::AbstractItem*> itemRepository;

      ItemRepository();
      ~ItemRepository() = default;

    public:
      static ItemRepository& getInstance() {
        static ItemRepository instance;
        return instance;
      }

      ItemRepository(const ItemRepository&) = delete;
      ItemRepository& operator=(const ItemRepository&) = delete;

      ItemRepository& add(const Items::AbstractItem* item);
      bool find(unsigned int id);
      const Items::AbstractItem& get(unsigned int id) const;
      ItemRepository& remove(unsigned int id);
      size_t size() const;
      std::vector<const Items::AbstractItem*>::const_iterator begin() const;
      std::vector<const Items::AbstractItem*>::const_iterator end() const;
      ItemRepository& clear();

  };

}


#endif // ITEMREPOSITORY_H

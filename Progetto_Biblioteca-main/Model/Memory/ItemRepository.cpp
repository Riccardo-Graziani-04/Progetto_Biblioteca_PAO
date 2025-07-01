#include <qdebug.h>
#include "ItemRepository.h"

namespace Memory {

  ItemRepository::ItemRepository() {}

  ItemRepository& ItemRepository::add(const Items::AbstractItem* item) {
    itemRepository.push_back(item);
    return *this;
  }

  // Rimuove e pulisce memoria dinamica
  ItemRepository& ItemRepository::remove(unsigned int id) {
    for (auto it = itemRepository.begin(); it != itemRepository.end(); ++it) {
      if ((*it)->getID() == id) {
        delete *it;
        itemRepository.erase(it);
        return *this;
      }
    }

    return *this;
  }

  // ID viene controllato per essere unique alla creazione degli item
  bool ItemRepository::find(unsigned int id) {
    for (auto cit = itemRepository.begin(); cit != itemRepository.end(); ++cit) {
      if ((*cit)->getID() == id) {
        return true;
      }
    }

    return false;
  }

  const Items::AbstractItem& ItemRepository::get(unsigned int id) const {
    for (auto cit = itemRepository.begin(); cit != itemRepository.end(); ++cit) {
      if ((*cit)->getID() == id) {
        return **cit;
      }
    }

    throw std::out_of_range("Given ID was not found in memory.");
  }

  size_t ItemRepository::size() const {
    return itemRepository.size();
  }

  std::vector<const Items::AbstractItem*>::const_iterator ItemRepository::begin() const {
    return itemRepository.begin();
  }

  std::vector<const Items::AbstractItem*>::const_iterator ItemRepository::end() const {
    return itemRepository.end();
  }

  ItemRepository& ItemRepository::clear() {
    for (auto it = itemRepository.begin(); it != itemRepository.end(); ++it) {
      delete *it;
    }

    itemRepository.clear();
    return *this;
  }

}


#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include "outfit.h"

class Inventory {
private:
    std::vector<Outfit> outfits;

public:
    void AddOutfit(const Outfit& outfit);
    const std::vector<Outfit>& GetOutfits() const;
    std::vector<Outfit>& GetMutableOutfits();
    bool HasStreetStyle() const;
    size_t Size() const;
    int TotalScore() const;
    void Clear() {
        outfits.clear();
    }
};

#endif

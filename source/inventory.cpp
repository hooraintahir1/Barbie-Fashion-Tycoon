#include "inventory.h"

void Inventory::AddOutfit(const Outfit& outfit) {
    outfits.push_back(outfit);
}

const std::vector<Outfit>& Inventory::GetOutfits() const {
    return outfits;
}

bool Inventory::HasStreetStyle() const {
    for (const auto& outfit : outfits) {
        if (outfit.name == "Street Style") {
            return true;
        }
    }
    return false;
}
std::vector<Outfit>& Inventory::GetMutableOutfits() {
    return outfits;
}


size_t Inventory::Size() const {
    return outfits.size();
}

int Inventory::TotalScore() const {
    int total = 0;
    for (const auto& outfit : outfits) {
        total += outfit.score;
    }
    return total;
}

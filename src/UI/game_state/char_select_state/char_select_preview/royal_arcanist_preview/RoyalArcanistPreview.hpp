#ifndef ROYAL_ARCANIST_PREVIEW_HPP
#define ROYAL_ARCANIST_PREVIEW_HPP

#include "../CharSelectPreview.hpp"

class RoyalArcanistPreview : public CharSelectPreview {
public:
    RoyalArcanistPreview();
    RoyalArcanistPreview(bool isLeft);
    ~RoyalArcanistPreview();
    void setSide(bool isLeft);
};

#endif // ROYAL_ARCANIST_PREVIEW_HPP
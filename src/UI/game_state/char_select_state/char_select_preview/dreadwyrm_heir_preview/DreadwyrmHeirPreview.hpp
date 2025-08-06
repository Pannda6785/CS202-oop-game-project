#ifndef DREADWYRM_HEIR_PREVIEW_HPP
#define DREADWYRM_HEIR_PREVIEW_HPP

#include "../CharSelectPreview.hpp"

class DreadwyrmHeirPreview : public CharSelectPreview {
public:
    DreadwyrmHeirPreview();
    DreadwyrmHeirPreview(bool isLeft);
    ~DreadwyrmHeirPreview();
    void setSide(bool isLeft);
};

#endif // DREADWYRM_HEIR_PREVIEW_HPP
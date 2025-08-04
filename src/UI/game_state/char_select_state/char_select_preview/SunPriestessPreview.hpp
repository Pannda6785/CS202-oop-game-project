#ifndef SUN_PRIESTESS_PREVIEW_HPP
#define SUN_PRIESTESS_PREVIEW_HPP

#include "CharSelectPreview.hpp"

class SunPriestessPreview : public CharSelectPreview {
public:
    SunPriestessPreview();
    SunPriestessPreview(bool isLeft);
    ~SunPriestessPreview();
    void setSide(bool isLeft);
};


#endif // SUN_PRIESTESS_PREVIEW_HPP
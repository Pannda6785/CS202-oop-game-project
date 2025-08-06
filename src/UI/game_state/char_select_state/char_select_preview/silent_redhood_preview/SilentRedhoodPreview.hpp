#ifndef SILENT_REDHOOD_PREVIEW_HPP
#define SILENT_REDHOOD_PREVIEW_HPP

#include "../CharSelectPreview.hpp"

class SilentRedhoodPreview : public CharSelectPreview {
public:
    SilentRedhoodPreview();
    SilentRedhoodPreview(bool isLeft);
    ~SilentRedhoodPreview();
    void setSide(bool isLeft);
};

#endif // SILENT_REDHOOD_PREVIEW_HPP
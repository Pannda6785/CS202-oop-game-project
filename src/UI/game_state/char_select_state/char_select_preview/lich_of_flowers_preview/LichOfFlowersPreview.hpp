#ifndef LICH_OF_FLOWERS_PREVIEW_HPP
#define LICH_OF_FLOWERS_PREVIEW_HPP

#include "../CharSelectPreview.hpp"

class LichOfFlowersPreview : public CharSelectPreview {
public:
    LichOfFlowersPreview();
    LichOfFlowersPreview(bool isLeft);
    ~LichOfFlowersPreview();
    void setSide(bool isLeft);
};

#endif // LICH_OF_FLOWERS_PREVIEW_HPP
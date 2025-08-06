#ifndef DEPTH_SECRET_PREVIEW_HPP
#define DEPTH_SECRET_PREVIEW_HPP

#include "../CharSelectPreview.hpp"

class DepthSecretPreview : public CharSelectPreview {
public:
    DepthSecretPreview();
    DepthSecretPreview(bool isLeft);
    ~DepthSecretPreview();
    void setSide(bool isLeft);
};

#endif // DEPTH_SECRET_PREVIEW_HPP
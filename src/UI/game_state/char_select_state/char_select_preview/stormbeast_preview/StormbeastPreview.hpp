#ifndef STORMBEAST_PREVIEW_HPP
#define STORMBEAST_PREVIEW_HPP

#include "../CharSelectPreview.hpp"

class StormbeastPreview : public CharSelectPreview {
public:
    StormbeastPreview();
    StormbeastPreview(bool isLeft);
    ~StormbeastPreview();
    void setSide(bool isLeft);
};

#endif // STORMBEAST_PREVIEW_HPP
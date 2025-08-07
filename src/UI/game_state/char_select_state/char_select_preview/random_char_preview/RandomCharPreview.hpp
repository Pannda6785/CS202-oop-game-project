#ifndef RANDOM_CHAR_PREVIEW_HPP
#define RANDOM_CHAR_PREVIEW_HPP

#include "../CharSelectPreview.hpp"

class RandomCharPreview : public CharSelectPreview {
public:
    RandomCharPreview();
    RandomCharPreview(bool isLeft);
    ~RandomCharPreview();
    void setSide(bool isLeft);
};

#endif // RANDOM_CHAR_PREVIEW_HPP
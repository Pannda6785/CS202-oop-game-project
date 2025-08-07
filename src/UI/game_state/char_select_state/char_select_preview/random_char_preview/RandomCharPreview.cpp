#include "RandomCharPreview.hpp"

RandomCharPreview::RandomCharPreview() {
    setCharName("Random Selected");
    setBackgroundColor({166,157,141,255});
    setRibbonBackgroundColor({20,20,20,255});
    setFrontTileColor({135,135,135,255});
    enter();
}

RandomCharPreview::RandomCharPreview(bool isLeft) : CharSelectPreview() {
    setSide(isLeft);
    setCharName("Random Selected");
    setBackgroundColor({166,157,141,255});
    setRibbonBackgroundColor({20,20,20,255});
    setFrontTileColor({135,135,135,255});
    enter();
}

RandomCharPreview::~RandomCharPreview() = default;

void RandomCharPreview::setSide(bool isLeft) {
    CharSelectPreview::setSide(isLeft);
}
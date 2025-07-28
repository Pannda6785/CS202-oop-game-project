#ifndef CHAR_SELECT_PREVIEW_MANAGER_HPP
#define CHAR_SELECT_PREVIEW_MANAGER_HPP

#include "CharSelectPreview.hpp"
#include <memory>

class CharSelectPreviewManager {
public:
    CharSelectPreviewManager();
    ~CharSelectPreviewManager();

    void init(bool isLeft = true);
    void setPreview(std::string characterName, bool isLeft);
    void update(float dt);

private:
    bool isLeft = true;
    std::shared_ptr<CharSelectPreview> preview = nullptr;
    std::shared_ptr<CharSelectPreview> sunPriestessPreview = nullptr;

};

#endif // CHAR_SELECT_PREVIEW_MANAGER_HPP
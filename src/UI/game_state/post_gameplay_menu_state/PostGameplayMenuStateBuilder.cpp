#include "PostGameplayMenuStateBuilder.hpp"

PostGameplayMenuStateBuilder::PostGameplayMenuStateBuilder(GameStateManager& gsm, PostGameOption& selectedOption) {
    state = std::make_unique<PostGameplayMenuState>(gsm, selectedOption);
}

PostGameplayMenuStateBuilder& PostGameplayMenuStateBuilder::setResumeButton() {
    state->hasResumeButton = true;
    return *this;
}

PostGameplayMenuStateBuilder& PostGameplayMenuStateBuilder::setRestartButton() {
    state->hasRestartButton = true;
    return *this;
}

PostGameplayMenuStateBuilder& PostGameplayMenuStateBuilder::setCharSelectButton() {
    state->hasCharSelectButton = true;
    return *this;
}

PostGameplayMenuStateBuilder& PostGameplayMenuStateBuilder::setMainMenuButton() {
    state->hasMainMenuButton = true;
    return *this;
}

PostGameplayMenuStateBuilder& PostGameplayMenuStateBuilder::setHeaderText(const std::string& text) {
    state->headerText = text;
    return *this;
}

PostGameplayMenuStateBuilder& PostGameplayMenuStateBuilder::setButtonHeight(int height) {
    state->buttonHeight = height;
    return *this;
}

PostGameplayMenuStateBuilder& PostGameplayMenuStateBuilder::setInitialY(int y) {
    state->coordYFirstButton = y;
    return *this;
}

PostGameplayMenuStateBuilder& PostGameplayMenuStateBuilder::setButtonSpacing(int spacing) {
    state->buttonSpacing = spacing;
    return *this;
}

PostGameplayMenuStateBuilder& PostGameplayMenuStateBuilder::setOffset(int offset) {
    state->offset = offset;
    return *this;
}

PostGameplayMenuStateBuilder& PostGameplayMenuStateBuilder::setDeltaOffset(int delta) {
    state->deltaOffset = delta;
    return *this;
}

PostGameplayMenuStateBuilder& PostGameplayMenuStateBuilder::setFontSize(int size) {
    state->fontSize = size;
    return *this;
}

std::unique_ptr<PostGameplayMenuState> PostGameplayMenuStateBuilder::build() {
    state->enter();
    return std::move(state);
}
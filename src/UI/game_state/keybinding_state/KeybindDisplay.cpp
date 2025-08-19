#include "KeybindDisplay.hpp"

// Initialize the static key name map
std::unordered_map<int, std::string> KeybindDisplay::keyNameMap;

KeybindDisplay::KeybindDisplay() 
    : currentKey(0),
      horizontalPadding(10.0f),
      verticalPadding(5.0f),
      fontSize(30),
      fontPath("../assets/fonts/ferrum2.otf"),
      posX(0),
      posY(0) {
    
    // Initialize the static key name map if it hasn't been already
    if (keyNameMap.empty()) {
        initializeKeyNameMap();
    }
    
    // Create the text and background components
    keyText = std::make_unique<GameText>();
    background = std::make_unique<Background>();
    
    // Default text and styling
    keyText->setText("None");
    keyText->loadFont(fontPath);
    keyText->setFontSize(fontSize);
    keyText->setColor(textColor);
    keyText->setOriginRatio({0.5f, 0.5f});
    
    background->setBackgroundColor(backgroundColor);
    
    // Update the background size
    updateBackground();
}

KeybindDisplay::KeybindDisplay(int raylibKey) : KeybindDisplay() {
    setKey(raylibKey);
}

KeybindDisplay::~KeybindDisplay() = default;

void KeybindDisplay::setPosition(int x, int y) {
    posX = x;
    posY = y;
    
    // Update positions for both components
    keyText->setPosition(x, y);
    updateBackground();
}

void KeybindDisplay::setKey(int raylibKey) {
    currentKey = raylibKey;
    
    // Update the text
    keyText->setText(getKeyNameFromMap(raylibKey));
    
    // Update the background size
    updateBackground();
    
    // Update position to reflect new size
    setPosition(posX, posY);
}

void KeybindDisplay::setHover(bool hover) {
    if(hover){
        keyText->setColor(backgroundColor);
        background->setBackgroundColor(textColor);
    } else {
        keyText->setColor(textColor);
        background->setBackgroundColor(backgroundColor);
    }
}

void KeybindDisplay::update(float dt) {
    keyText->update(dt);
}

void KeybindDisplay::setFont(const std::string& path) {
    fontPath = path;
    keyText->loadFont(fontPath);
    updateBackground();
}

void KeybindDisplay::setFontSize(int size) {
    fontSize = size;
    keyText->setFontSize(fontSize);
    updateBackground();
}

void KeybindDisplay::setTextColor(Color color) {
    textColor = color;
    keyText->setColor(textColor);
}

void KeybindDisplay::setBackgroundColor(Color color) {
    backgroundColor = color;
    background->setBackgroundColor(backgroundColor);
}

void KeybindDisplay::setPadding(float horizontal, float vertical) {
    horizontalPadding = horizontal;
    verticalPadding = vertical;
    updateBackground();
}

void KeybindDisplay::setLayer(int layer) {
    keyText->setLayer(layer + 1); // Text should be above background
    background->setLayer(layer);
}

int KeybindDisplay::getKey() const {
    return currentKey;
}

float KeybindDisplay::getWidth() const {
    return keyText->getWidth() + (horizontalPadding * 2);
}

float KeybindDisplay::getHeight() const {
    return keyText->getHeight() + (verticalPadding * 2);
}

std::string KeybindDisplay::getKeyName() const {
    return getKeyNameFromMap(currentKey);
}

void KeybindDisplay::updateBackground() {
    // Calculate size based on text dimensions and padding
    float width = getWidth();
    float height = getHeight();
    
    // Update the background rectangle
    Rectangle rect = {
        static_cast<float>(posX) - width / 2.0f,
        static_cast<float>(posY) - height / 2.0f,
        width,
        height
    };
    background->setBackgroundRect(rect);
}

std::string KeybindDisplay::getKeyNameFromMap(int keyCode) const {
    auto it = keyNameMap.find(keyCode);
    if (it != keyNameMap.end()) {
        return it->second;
    }
    
    // Default for unknown keys
    if (keyCode == 0) {
        return "None";
    }
    return "Key " + std::to_string(keyCode);
}

void KeybindDisplay::initializeKeyNameMap() {
    // Alphabetic keys
    keyNameMap[KEY_A] = "A";
    keyNameMap[KEY_B] = "B";
    keyNameMap[KEY_C] = "C";
    keyNameMap[KEY_D] = "D";
    keyNameMap[KEY_E] = "E";
    keyNameMap[KEY_F] = "F";
    keyNameMap[KEY_G] = "G";
    keyNameMap[KEY_H] = "H";
    keyNameMap[KEY_I] = "I";
    keyNameMap[KEY_J] = "J";
    keyNameMap[KEY_K] = "K";
    keyNameMap[KEY_L] = "L";
    keyNameMap[KEY_M] = "M";
    keyNameMap[KEY_N] = "N";
    keyNameMap[KEY_O] = "O";
    keyNameMap[KEY_P] = "P";
    keyNameMap[KEY_Q] = "Q";
    keyNameMap[KEY_R] = "R";
    keyNameMap[KEY_S] = "S";
    keyNameMap[KEY_T] = "T";
    keyNameMap[KEY_U] = "U";
    keyNameMap[KEY_V] = "V";
    keyNameMap[KEY_W] = "W";
    keyNameMap[KEY_X] = "X";
    keyNameMap[KEY_Y] = "Y";
    keyNameMap[KEY_Z] = "Z";
    
    // Number keys
    keyNameMap[KEY_ZERO] = "0";
    keyNameMap[KEY_ONE] = "1";
    keyNameMap[KEY_TWO] = "2";
    keyNameMap[KEY_THREE] = "3";
    keyNameMap[KEY_FOUR] = "4";
    keyNameMap[KEY_FIVE] = "5";
    keyNameMap[KEY_SIX] = "6";
    keyNameMap[KEY_SEVEN] = "7";
    keyNameMap[KEY_EIGHT] = "8";
    keyNameMap[KEY_NINE] = "9";
    
    // Function keys
    keyNameMap[KEY_F1] = "F1";
    keyNameMap[KEY_F2] = "F2";
    keyNameMap[KEY_F3] = "F3";
    keyNameMap[KEY_F4] = "F4";
    keyNameMap[KEY_F5] = "F5";
    keyNameMap[KEY_F6] = "F6";
    keyNameMap[KEY_F7] = "F7";
    keyNameMap[KEY_F8] = "F8";
    keyNameMap[KEY_F9] = "F9";
    keyNameMap[KEY_F10] = "F10";
    keyNameMap[KEY_F11] = "F11";
    keyNameMap[KEY_F12] = "F12";
    
    // Special keys
    keyNameMap[KEY_SPACE] = "SPACE";
    keyNameMap[KEY_ESCAPE] = "ESC";
    keyNameMap[KEY_ENTER] = "ENTER";
    keyNameMap[KEY_TAB] = "TAB";
    keyNameMap[KEY_BACKSPACE] = "BKSP";
    keyNameMap[KEY_INSERT] = "INS";
    keyNameMap[KEY_DELETE] = "DEL";
    keyNameMap[KEY_RIGHT] = "RIGHT";
    keyNameMap[KEY_LEFT] = "LEFT";
    keyNameMap[KEY_DOWN] = "DOWN";
    keyNameMap[KEY_UP] = "UP";
    keyNameMap[KEY_PAGE_UP] = "PG UP";
    keyNameMap[KEY_PAGE_DOWN] = "PG DN";
    keyNameMap[KEY_HOME] = "HOME";
    keyNameMap[KEY_END] = "END";
    keyNameMap[KEY_CAPS_LOCK] = "CAPS";
    keyNameMap[KEY_SCROLL_LOCK] = "SCRL";
    keyNameMap[KEY_NUM_LOCK] = "NUM";
    keyNameMap[KEY_PRINT_SCREEN] = "PRNT";
    keyNameMap[KEY_PAUSE] = "PAUSE";
    
    // Keypad keys
    keyNameMap[KEY_KP_0] = "NUM 0";
    keyNameMap[KEY_KP_1] = "NUM 1";
    keyNameMap[KEY_KP_2] = "NUM 2";
    keyNameMap[KEY_KP_3] = "NUM 3";
    keyNameMap[KEY_KP_4] = "NUM 4";
    keyNameMap[KEY_KP_5] = "NUM 5";
    keyNameMap[KEY_KP_6] = "NUM 6";
    keyNameMap[KEY_KP_7] = "NUM 7";
    keyNameMap[KEY_KP_8] = "NUM 8";
    keyNameMap[KEY_KP_9] = "NUM 9";
    keyNameMap[KEY_KP_DECIMAL] = "NUM .";
    keyNameMap[KEY_KP_DIVIDE] = "NUM /";
    keyNameMap[KEY_KP_MULTIPLY] = "NUM *";
    keyNameMap[KEY_KP_SUBTRACT] = "NUM -";
    keyNameMap[KEY_KP_ADD] = "NUM +";
    keyNameMap[KEY_KP_ENTER] = "NUM ↵";
    keyNameMap[KEY_KP_EQUAL] = "NUM =";
    
    // Modifier keys
    keyNameMap[KEY_LEFT_SHIFT] = "L SHIFT";
    keyNameMap[KEY_LEFT_CONTROL] = "L CTRL";
    keyNameMap[KEY_LEFT_ALT] = "L ALT";
    keyNameMap[KEY_LEFT_SUPER] = "L SUPER";
    keyNameMap[KEY_RIGHT_SHIFT] = "R SHIFT";
    keyNameMap[KEY_RIGHT_CONTROL] = "R CTRL";
    keyNameMap[KEY_RIGHT_ALT] = "R ALT";
    keyNameMap[KEY_RIGHT_SUPER] = "R SUPER";
    keyNameMap[KEY_KB_MENU] = "MENU";
    
    // Punctuation
    keyNameMap[KEY_APOSTROPHE] = "'";
    keyNameMap[KEY_COMMA] = ",";
    keyNameMap[KEY_MINUS] = "-";
    keyNameMap[KEY_PERIOD] = ".";
    keyNameMap[KEY_SLASH] = "/";
    keyNameMap[KEY_SEMICOLON] = ";";
    keyNameMap[KEY_EQUAL] = "=";
    keyNameMap[KEY_LEFT_BRACKET] = "[";
    keyNameMap[KEY_BACKSLASH] = "\\";
    keyNameMap[KEY_RIGHT_BRACKET] = "]";
    keyNameMap[KEY_GRAVE] = "`";
}
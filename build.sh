#!/bin/bash

OUTPUT="main"
OUTPUT_DIR="bin"
BUILD_DIR="build"
CXX="g++"
CXXFLAGS="-std=c++17 -O2 -pipe -march=native"
LDFLAGS="-lraylib -lwinmm -lgdi32 -luser32 -lkernel32"

# Tạo thư mục nếu chưa có
mkdir -p "$OUTPUT_DIR"
mkdir -p "$BUILD_DIR"

# Tìm tất cả .cpp
SOURCES=$(find . -name "*.cpp")

# Danh sách object file
OBJECTS=()

echo "🔍 Đang tìm và biên dịch các file đã thay đổi..."

for src in $SOURCES; do
    # Tạo đường dẫn object tương ứng trong build/
    obj="$BUILD_DIR/$(basename "${src%.cpp}.o")"
    OBJECTS+=("$obj")

    # Chỉ biên dịch lại nếu file .cpp mới hơn .o hoặc .o chưa tồn tại
    if [[ "$src" -nt "$obj" ]]; then
        echo "🛠️  Compiling: $src → $obj"
        $CXX $CXXFLAGS -c "$src" -o "$obj"
        if [ $? -ne 0 ]; then
            echo "❌ Compilation failed: $src"
            exit 1
        fi
    fi
done

# Liên kết lại
echo "🔗 Linking to $OUTPUT_DIR/$OUTPUT.exe"
$CXX "${OBJECTS[@]}" -o "$OUTPUT_DIR/$OUTPUT.exe" $LDFLAGS

if [ $? -eq 0 ]; then
    echo "✅ Build thành công: $OUTPUT_DIR/$OUTPUT.exe"
else
    echo "❌ Link thất bại"
    exit 1
fi
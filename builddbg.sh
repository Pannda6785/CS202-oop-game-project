#!/bin/bash

OUTPUT="main"
OUTPUT_DIR="bin"
BUILD_DIR="build"
CXX="g++"

# Cờ biên dịch cho Debug:
# -g: Bao gồm thông tin gỡ lỗi (debug symbols) trong file nhị phân. Điều này cho phép debugger ánh xạ mã máy về mã nguồn của bạn.
# -O0: Tắt mọi tối ưu hóa. Tối ưu hóa có thể làm thay đổi thứ tự thực thi mã hoặc loại bỏ mã không sử dụng, làm cho việc gỡ lỗi khó khăn hơn.
# -std=c++17: Vẫn giữ chuẩn C++17.
# -Wall -Wextra -pedantic: Bật tất cả các cảnh báo và kiểm tra chặt chẽ hơn để phát hiện lỗi tiềm ẩn. Rất hữu ích trong quá trình phát triển.
# -D_GLIBCXX_DEBUG: Bật chế độ debug của thư viện chuẩn C++ (libstdc++), giúp phát hiện các lỗi liên quan đến việc sử dụng container (ví dụ: out-of-bounds access).
CXXFLAGS="-std=c++17 -O0 -g -Wall -Wextra -pedantic -D_GLIBCXX_DEBUG"

# Cờ liên kết cho Debug:
# Không cần thay đổi nhiều cho LDFLAGS, nhưng đảm bảo các thư viện cần thiết vẫn được liên kết.
LDFLAGS="-lraylib -lwinmm -lgdi32 -luser32 -lkernel32"

# Tạo thư mục nếu chưa có
mkdir -p "$OUTPUT_DIR"
mkdir -p "$BUILD_DIR"

# Tìm tất cả .cpp
SOURCES=$(find . -name "*.cpp")

# Danh sách object file
OBJECTS=()

echo "🔍 Đang tìm và biên dịch các file đã thay đổi (chế độ DEBUG)..."

for src in $SOURCES; do
    # Tạo đường dẫn object tương ứng trong build/
    obj="$BUILD_DIR/$(basename "${src%.cpp}.o")"
    OBJECTS+=("$obj")

    # Chỉ biên dịch lại nếu file .cpp mới hơn .o hoặc .o chưa tồn tại
    if [[ "$src" -nt "$obj" ]]; then
        echo "🛠️  Compiling: $src → $obj"
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
    echo "✅ Build thành công (DEBUG): $OUTPUT_DIR/$OUTPUT.exe"
else
    echo "❌ Link thất bại"
    exit 1
fi
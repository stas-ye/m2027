ï»¿#include <iostream>
#include <fstream>
#include <cstdint>
#include <vector>
#include <cmath>
#include <ctime>

#pragma pack(push, 1)
struct BMPFileHeader {
    uint16_t fileType{ 0x4D42 };
    uint32_t fileSize{ 0 };
    uint16_t reserved1{ 0 };
    uint16_t reserved2{ 0 };
    uint32_t pixelDataOffset{ 54 };
};

struct BMPInfoHeader {
    uint32_t size{40};
    int32_t width{0};
    int32_t height{0};
    uint16_t planes{1};
    uint16_t bitsPerPixel{24};
    uint32_t compression{0};
    uint32_t imageSize{0};
    int32_t xPixelsPerMeter{0};
    int32_t yPixelsPerMeter{0};
    uint32_t colorsUsed{0};
    uint32_t colorsImportant{0};
};
#pragma pack(pop)

void WriteBMP(const std::string& filename, int width, int height, const auto& result) {
    std::ofstream fout(filename, std::ios::binary);
    if (!fout.is_open()) {
        std::cerr << "Error: Could not open file for writing.\n";
        return;
    }

    int rowSize = (width * 3 + 3) / 4 * 4;
    int padding = rowSize - width * 3;
    int imageSize = rowSize * height;
    int fileSize = 54 + imageSize;

    BMPFileHeader bmpFileHeader;
    bmpFileHeader.fileSize = fileSize;

    BMPInfoHeader bmpInfoHeader;
    bmpInfoHeader.width = width;
    bmpInfoHeader.height = height;
    bmpInfoHeader.imageSize = imageSize;

    fout.write(reinterpret_cast<const char*>(&bmpFileHeader), sizeof(BMPFileHeader));
    fout.write(reinterpret_cast<const char*>(&bmpInfoHeader), sizeof(BMPInfoHeader));

    uint8_t red = 0, green = 0, blue = 0;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int count_not_bool = 4 - (result[y][x] + result[y][x + 1] +
                                        result[y + 1][x] + result[y + 1][x + 1]);
            red = count_not_bool * 255 / 4;
            green = count_not_bool * 255 / 4;
            blue = count_not_bool * 255 / 4;
            fout.write(reinterpret_cast<const char*>(&blue), sizeof(blue));
            fout.write(reinterpret_cast<const char*>(&green), sizeof(green));
            fout.write(reinterpret_cast<const char*>(&red), sizeof(red));
        }
    }
    fout.close();
}

void Step(int x, int y, const std::vector<std::vector<float>>& functions_step,
                auto& points, int& maxx, int& minx, int& maxy, int& miny, bool& first) {
    int random = rand() % 10000 - 1;
    for (const std::vector<float>& function_step : functions_step) {
        random -= function_step[6] * 10000;
        if (random > 0) {
            continue;
        }
        int new_x = x * function_step[0] + y * function_step[1] + function_step[4],
            new_y = x * function_step[2] + y * function_step[3] + function_step[5];
        if (first) {
            first = false;
            maxx = new_x;
            minx = new_x;
            maxy = new_y;
            miny = new_y;
        } else {
            maxx = std::max(maxx, new_x);
            minx = std::min(minx, new_x);
            maxy = std::max(maxy, new_y);
            miny = std::min(miny, new_y);
        }
        points.push_back(std::pair<int, int> (new_y, new_x));
    }
}

void Steps(int steps, auto& result, int width, int height, const auto& functions_step) {
    for (int i = 0; i < steps; ++i) {
        bool first = true;
        int maxx, minx, maxy, miny;
        std::vector<std::vector<bool>> new_result(height + 1, std::vector<bool> (width + 1, 0));
        std::vector<std::pair<int, int>> points;
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                if (result[y][x]) {
                    Step(x, y, functions_step, points, maxx, minx, maxy, miny, first);
                }
            }
        }
        float kx = 1.0f * width / (maxx - minx), ky = 1.0f * height / (maxy - miny);
        for (auto point : points) {
            new_result[(point.first - miny) * ky][(point.second - minx) * kx] = 1;
        }
        std::swap(result, new_result);
    }
}

int main() {
    std::srand(std::time(0));

    int steps = 10;
    int width_all = 1000;
    int height_all = 2000;
    int width, height;
    std::vector<std::vector<bool>> result;
    std::vector<std::vector<float>> functions_step;


    //Koch snowflake
    width = width_all;
    height = height_all / 3;
    result = std::vector<std::vector<bool>>(height + 1, std::vector<bool> (width + 1, 0));
    for (int y = 0; y * 10 < height; ++y) {
        for (int x = 0; x < width; ++x) {
            result[y][x] = 1;
        }
    }
    functions_step = {
        {0.3333, 0.0, 0.0, 0.3333, 0.0, 0.0, 0.25},
        {0.1667, -0.2887, 0.2887, 0.1667, 0.3333f * width, 0.0, 0.25},
        {-0.1667, 0.2887, 0.2887, 0.1667, 0.6666f * width, 0.0, 0.25},
        {0.3333, 0.0, 0.0, 0.3333, 0.6666f * width, 0.0, 0.25}
    };
    Steps(steps, result, width, height, functions_step);
    WriteBMP("KochSnowflake.bmp", width, height, result);


    //Sierpinski triangle
    width = width_all;
    height = height_all;
    result = std::vector<std::vector<bool>>(height + 1, std::vector<bool> (width + 1, 1));
    functions_step = {
        {0.5, 0, 0, 0.5, 0, 0, 0.333333},
        {0.5, 0, 0, 0.5, 0.5f * width, 0, 0.333333},
        {0.5, 0, 0, 0.5, 0.25f * width, 0.5f * height, 0.333333}
    };
    Steps(steps, result, width, height, functions_step);
    WriteBMP("SierpinskiTriangle.bmp", width, height, result);


    //Tree
    width = width_all;
    height = height_all;
    result = std::vector<std::vector<bool>>(height + 1, std::vector<bool> (width + 1, 1));
    functions_step = {
      {0.0, 0.0, 0.0, 0.5, 0.0f * width, 0.0f * height, 0.05},
      {0.42, -0.42, 0.42, 0.42, -0.19f * width, 0.31f * height, 0.4},
      {0.42, 0.42, -0.42, 0.42, -0.21f * width, 0.73f * height, 0.4},
      {0.1, 0.0, 0.0, 0.1, -0.05f * width, 0.5f * height, 0.15}
    };
    /*functions_step = {
        {0.0, 0.0, 0.0, 0.5, 0.0, 0.0, 0.05},
        {0.42, -0.42, 0.42, 0.42, -0.2f * width, 0.3f * height, 0.4},
        {0.42, 0.42, -0.42, 0.42, -0.2f * width, 0.7f * height, 0.4},
        {0.1, 0.0, 0.0, 0.1, 0.0, 0.2f * height, 0.15}
    };*/
    Steps(steps, result, width, height, functions_step);
    WriteBMP("Tree.bmp", width, height, result);


    //Binary
    width = width_all;
    height = height_all;
    result = std::vector<std::vector<bool>>(height + 1, std::vector<bool> (width + 1, 1));
    functions_step = {
      {0.5, 0.0, 0.0, 0.5, 0.0f * width, -0.0f * height, 0.333333},
      {0.5, 0.0, 0.0, 0.5, 0.5f * width, -0.0f * height, 0.333333},
      {0.0, -0.5, 0.5, 0.0, 1.0f * width, 0.5f * height, 0.333333}
    };
    Steps(steps, result, width, height, functions_step);
    WriteBMP("Binary.bmp", width, height, result);
    return 0;
}

//http://www.100byte.ru/stdntswrks/fr/fr.html#lg

// John Catalana
// Professor Kanemoto
// 1/22/2026

#include <iostream>
#include <fstream>

int main() {
    const int WIDTH = 800;
    const int HEIGHT = 600;
    const int MAX_ITER = 300;

    // ✅ Option A: Fixed palette (C-style arrays)
    // Added 1 extra color → PALETTE_SIZE is now 6
    const int PALETTE_SIZE = 6;

    int red[PALETTE_SIZE]   = { 66, 25,  9,   0, 255, 255 };
    int green[PALETTE_SIZE] = { 30,  7,  1,   0, 255, 140 };
    int blue[PALETTE_SIZE]  = { 15, 26, 47, 100, 255,   0 };

    std::ofstream out("mandelbrot.html");
    if (!out) {
        std::cerr << "Error opening HTML output file\n";
        return 1;
    }

    out << "<!DOCTYPE html>\n<html>\n<body>\n";
    out << "<canvas id='c' width='" << WIDTH << "' height='" << HEIGHT << "'></canvas>\n";
    out << "<script>\n";
    out << "const canvas = document.getElementById('c');\n";
    out << "const ctx = canvas.getContext('2d');\n";
    out << "const img = ctx.createImageData(" << WIDTH << ", " << HEIGHT << ");\n";
    out << "let data = img.data;\n\n";

    // ✅ Write C++ palette arrays into JS arrays
    out << "const PALETTE_SIZE = " << PALETTE_SIZE << ";\n";

    out << "const red = [";
    for (int i = 0; i < PALETTE_SIZE; i++) out << red[i] << (i < PALETTE_SIZE - 1 ? ", " : "");
    out << "];\n";

    out << "const green = [";
    for (int i = 0; i < PALETTE_SIZE; i++) out << green[i] << (i < PALETTE_SIZE - 1 ? ", " : "");
    out << "];\n";

    out << "const blue = [";
    for (int i = 0; i < PALETTE_SIZE; i++) out << blue[i] << (i < PALETTE_SIZE - 1 ? ", " : "");
    out << "];\n\n";

    out << "let i = 0;\n";
    out << "for (let y = 0; y < " << HEIGHT << "; y++) {\n";
    out << "  for (let x = 0; x < " << WIDTH << "; x++) {\n";
    out << "    let zx = 0, zy = 0;\n";
    out << "    let cX = (x - " << (WIDTH / 2) << ") / 150;\n";
    out << "    let cY = (y - " << (HEIGHT / 2) << ") / 150;\n";
    out << "    let iter = " << MAX_ITER << ";\n";
    out << "    while (zx*zx + zy*zy < 4 && iter > 0) {\n";
    out << "      let tmp = zx*zx - zy*zy + cX;\n";
    out << "      zy = 2*zx*zy + cY;\n";
    out << "      zx = tmp;\n";
    out << "      iter--;\n";
    out << "    }\n\n";

    // ✅ Use the palette based on iterations used
    out << "    let r, g, b;\n";
    out << "    if (iter === 0) {\n";
    out << "      // Inside the set → black\n";
    out << "      r = 0; g = 0; b = 0;\n";
    out << "    } else {\n";
    out << "      // iterationsUsed goes 0..MAX_ITER\n";
    out << "      let iterationsUsed = " << MAX_ITER << " - iter;\n\n";
    out << "      // Option 1 (banded): let index = iterationsUsed % PALETTE_SIZE;\n";
    out << "      // Option 2 (smooth palette mapping):\n";
    out << "      let index = Math.floor((iterationsUsed / " << MAX_ITER << ") * (PALETTE_SIZE - 1));\n";
    out << "      index = Math.max(0, Math.min(PALETTE_SIZE - 1, index));\n\n";
    out << "      r = red[index];\n";
    out << "      g = green[index];\n";
    out << "      b = blue[index];\n";
    out << "    }\n\n";

    // ✅ Write pixels
    out << "    data[i++] = r;\n";
    out << "    data[i++] = g;\n";
    out << "    data[i++] = b;\n";
    out << "    data[i++] = 255;\n";
    out << "  }\n";
    out << "}\n\n";

    out << "ctx.putImageData(img, 0, 0);\n";
    out << "</script>\n</body>\n</html>\n";

    out.close();
    std::cout << "mandelbrot.html generated — open it in your cloud IDE's browser preview.\n";
    return 0;
}

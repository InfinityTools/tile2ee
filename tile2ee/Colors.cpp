#include <limits>
#include <cmath>
#include <cstring>
#include <memory>
#include "Converter.hpp"
#include "ColorQuant.hpp"
#include "Funcs.hpp"
#include "Colors.hpp"

namespace tc {

Colors::Colors(const Options &options) noexcept
: m_options(options)
{
}

Colors::~Colors() noexcept
{
}

int Colors::palToARGB(uint8_t *src, uint8_t *palette, uint8_t *dst, uint32_t size) noexcept
{
  if (src != nullptr && palette != nullptr && dst != nullptr && size > 0) {
    for (uint32_t i = 0; i < size; i++, src++, dst += 4) {
      uint32_t ofs = (uint32_t)src[0] << 2;
      if (src[0] || get32u_le((uint32_t*)palette) != 0x0000ff00) {
        dst[0] = palette[ofs+0];
        dst[1] = palette[ofs+1];
        dst[2] = palette[ofs+2];
        dst[3] = 255;
      } else {
        dst[0] = dst[1] = dst[2] = dst[3] = 0;
      }
    }
    return size;
  }
  return 0;
}

int Colors::ARGBToPal(uint8_t *src, uint8_t *dst, uint8_t *palette,
                      uint32_t width, uint32_t height) noexcept
{
  if (src != nullptr && dst != nullptr && palette != nullptr && width > 0 && height > 0) {
    uint32_t size = width*height;

    // preparing source pixels
    Converter::ReorderColors(src, size, ColorFormat::ARGB, ColorFormat::ABGR);

    ColorQuant quant;
    if (!quant.setSource(src, width, height)) return 0;
    if (!quant.setTarget(dst, size)) return 0;
    std::memset(palette, 0, 1024);
    if (!quant.setPalette(palette, 1024)) return 0;
    quant.setSpeed(10 - getOptions().getQualityV1());   // speed is defined as "10 - quality"

    if (!quant.quantize()) return 0;
    Converter::ReorderColors(palette, 256, ColorFormat::ABGR, ColorFormat::ARGB);

    return size;
  }
  return 0;
}

}   // namespace tc

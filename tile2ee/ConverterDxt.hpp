#ifndef _CONVERTERDXT_HPP_
#define _CONVERTERDXT_HPP_
#include "Converter.hpp"

namespace tc {

/** Implements a DXTn encoder and decoder. */
class ConverterDxt : public Converter
{
public:
  /** Returns the value expanded to the nearest multiple of 4. */
  static int GetPaddedValue(int v) noexcept { return (v + 3) & ~3; }

public:
  ConverterDxt(const Options& options, Encoding type) noexcept;
  ~ConverterDxt() noexcept;

  bool canEncode() const noexcept { return true; }
  bool canDecode() const noexcept { return true; }
  bool deflateAllowed() const noexcept { return true; }

  /** See Converter::getRequiredSpace() */
  int getRequiredSpace(int width, int height) const noexcept;

  /** See Converter::convert() */
  int convert(uint8_t *palette, uint8_t *indexed, uint8_t *encoded, int width, int height) noexcept;

  /** See Converter::convert() */
  int convert(uint8_t *encoded, uint8_t *argb, int width, int height) noexcept;

private:

  // Performs pixel encoding/decoding on the given graphics data
  int encodeTile(uint8_t *src, uint8_t *dst, int width, int height) noexcept;
  int decodeTile(uint8_t *src, uint8_t *dst, int width, int height) noexcept;

  // Returns squish flags based on type and quality.
  int getFlags() const noexcept;

  // Encode a single DXTn block
  bool compressBlock(uint8_t *src, uint8_t *dst) noexcept;
  // Decode a single DXTn block
  bool decompressBlock(uint8_t *src, uint8_t *dst) noexcept;

  // tileconv's own decoding routines as fallback solution. Decodes into ColorFormat::ARGB.
  bool decodeBlockDxt1(uint8_t *src, uint8_t *dst) noexcept;
  bool decodeBlockDxt3(uint8_t *src, uint8_t *dst) noexcept;
  bool decodeBlockDxt5(uint8_t *src, uint8_t *dst) noexcept;

  // Unpacks two consecutive 16-bit RGB565 colors into 32-bit ColorFormat::ARGB.
  bool unpackColors565(const uint8_t *src, uint8_t *dst) noexcept;
};

}   // namespace tc

#endif		// _CONVERTERDXT_HPP_

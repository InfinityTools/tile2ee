#include "Compression.hpp"

namespace tc {

Compression::Compression() noexcept
: m_defResult(false)
, m_infResult(false)
, m_defStream()
, m_infStream()
{
  // initializing compressor with highest compression level
  m_defStream.zalloc = Z_NULL;
  m_defStream.zfree = Z_NULL;
  m_defStream.opaque = Z_NULL;
  m_defResult = (deflateInit(&m_defStream, 9) == Z_OK);

  // initializing decompressor with highest compression level
  m_infStream.zalloc = Z_NULL;
  m_infStream.zfree = Z_NULL;
  m_infStream.opaque = Z_NULL;
  m_infStream.avail_in = 0;
  m_infStream.next_in = Z_NULL;
  m_infResult = (inflateInit(&m_infStream) == Z_OK);
}

Compression::~Compression() noexcept
{
  // cleaning up
  deflateEnd(&m_defStream);
  inflateEnd(&m_infStream);
}

uint32_t Compression::deflate(uint8_t *src, uint32_t srcSize, uint8_t *dst, uint32_t dstSize) noexcept
{
  if (m_defResult && src != nullptr && dst != nullptr && srcSize > 0 && dstSize > 0) {
    m_defStream.avail_in = srcSize;
    m_defStream.next_in = src;
    m_defStream.avail_out = dstSize;
    m_defStream.next_out = dst;
    m_defResult = (::deflate(&m_defStream, Z_FINISH) != Z_STREAM_ERROR);
    uint32_t retVal = dstSize - m_defStream.avail_out;
    deflateReset(&m_defStream);
    return retVal;
  }
  return 0;
}

uint32_t Compression::inflate(uint8_t *src, uint32_t srcSize, uint8_t *dst, uint32_t dstSize) noexcept
{
  if (m_infResult && src != nullptr && dst != nullptr && srcSize > 0&& dstSize > 0) {
    m_infStream.avail_in = srcSize;
    m_infStream.next_in = src;
    m_infStream.avail_out = dstSize;
    m_infStream.next_out = dst;
    m_defResult = (::inflate(&m_infStream, Z_NO_FLUSH) != Z_STREAM_ERROR);
    uint32_t retVal = dstSize - m_infStream.avail_out;
    inflateReset(&m_infStream);
    return retVal;
  }
  return 0;
}

}   // namespace tc

#include "bitOperations.h"

namespace advcpp
{

#if CHAR_BIT == 8
template<>
std::size_t CountBits(unsigned char _chunk)
{
    // using variation of SWAR algorithm
    _chunk = (_chunk & 0x55) + ((_chunk >> 1) & 0x55);
    _chunk = (_chunk & 0x33) + ((_chunk >> 2) & 0x33);
    _chunk = (_chunk & 0x0f) + ((_chunk >> 4) & 0x0f);
    return _chunk;
}

#endif /* if CHAR_BIT == 8 */

}

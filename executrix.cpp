#include"executrix.h"

std::string str_to_hex(std::string i )
{
  std::stringstream stream;
  stream << "0x" << std::hex << std::stoul(i);
  return stream.str();
}

bool always_included(std::string path, std::vector<archivarius::file> contents) {
    for (archivarius::file con : contents) {
        if (con.fpath() == path) return true;
    }
    return false;
}

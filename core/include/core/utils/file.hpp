#pragma once
#include <core/core.hpp>
#include <fstream>
#include <sstream>
namespace starlight::core::utils {
class FileIO {
    std::fstream handle;

  public:
    std::string readFile();
    FileIO(const std::string& path, const std::ios_base::openmode mode = std::ifstream::in);
    ~FileIO();
    bool isOpen(){return handle.is_open();}
};

} // namespace starlight::core::utils
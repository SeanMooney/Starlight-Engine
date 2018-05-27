#include <core/utils/file.hpp>
#include <core/utils/log.hpp>

namespace starlight::core::utils {
;
FileIO::FileIO(const std::string& path, const std::ios_base::openmode mode) {
    this->handle = std::fstream(path, mode);
#if STARLIGHT_DEBUG
    if (!this->handle.is_open()) {
        std::stringstream error;
        error << "failed to read file: " << path;
        THROW(error.str().c_str());
    }
#endif
}

FileIO::~FileIO() {
    if (this->handle.is_open()) {
        this->handle.close();
    }
}

std::string FileIO::readFile() {
    std::stringstream ss;
    if (this->handle.is_open()) {
        ss << this->handle.rdbuf();
    }
    return ss.str();
}

} // namespace starlight::core::utils
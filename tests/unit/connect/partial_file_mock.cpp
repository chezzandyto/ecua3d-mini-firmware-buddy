#include "transfers/partial_file.hpp"

using namespace transfers;

std::variant<const char *, PartialFile::Ptr> PartialFile::create(const char *path, size_t size) {
    return "not implemented";
}

std::variant<const char *, PartialFile::Ptr> PartialFile::open(const char *path, PartialFile::State state) {
    return "not implemented";
}

bool PartialFile::write(const uint8_t *data, size_t size) {
    return true;
}

bool PartialFile::seek(size_t offset) {
    return true;
}

bool PartialFile::has_valid_head(size_t bytes) const {
    return true;
}

bool PartialFile::has_valid_tail(size_t bytes) const {
    return true;
}

bool PartialFile::sync() {
    return true;
}

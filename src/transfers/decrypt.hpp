#pragma once

#include <array>
#include <cstdint>
#include <cstdlib>
#include <variant>
#include <assert.h>

#include <mbedtls/aes.h>

namespace transfers {

class Decryptor {
public:
    static constexpr uint32_t BlockSize = 16;
    static constexpr uint32_t CtrCounterSize = 4;
    using Block = std::array<uint8_t, BlockSize>;

    class CTR {
        friend class Decryptor;
        Block nonce;

    private:
        void setup_context(mbedtls_aes_context &context, const Block &key);

        void decrypt(mbedtls_aes_context &context, const Block &input, Block &output);

    public:
        CTR(const Block &nonce, uint32_t offset = 0)
            : nonce(nonce) {
            reset(nonce, offset);
        }

        void reset(const Block &nonce, uint32_t offset);

        bool allows_random_access() const {
            return true;
        }
    };

    class CBC {
        friend class Decryptor;
        Block iv;

    private:
        void setup_context(mbedtls_aes_context &context, const Block &key);

        void decrypt(mbedtls_aes_context &context, const Block &input, Block &output);

    public:
        CBC(const Block &iv)
            : iv(iv) {}

        void reset(const Block &iv) {
            this->iv = iv;
        }

        bool allows_random_access() const {
            return false;
        }
    };

    using Mode = std::variant<CTR, CBC>;

private:
    uint32_t size_left;
    // Note:
    // There doesn't seem to be a legal way of moving this thing after it is
    // initialized. At least, memcpy does *not* work. Discovered the hard way.
    //
    // Therefore, the whole Decryptor is not movable _on purpose_.
    mbedtls_aes_context context;
    Mode mode;
    Block leftover;
    uint8_t leftover_size = 0;

public:
    Decryptor(const Block &key, const Mode mode, uint32_t orig_size);
    Decryptor(const Decryptor &other) = delete;
    Decryptor(Decryptor &&other) = delete;
    Decryptor &operator=(const Decryptor &other) = delete;
    Decryptor &operator=(Decryptor &&other) = delete;
    ~Decryptor();
    // Decrypt some data.
    //
    // Decrypts in-place (data is in-out buffer).
    //
    // The return size may differ slightly due to:
    // * The cipher works in blocks. We may have a leftover from the last time.
    //   The output might be up to BlockSize - 1 larger, but it'll never cross a
    //   multiple of BlockSize boundary above the size. That is, if the real
    //   buffer is Block-Size multiple large, it'll never overflow (but if the
    //   amount of data passed in into the function is smaller than this/not of
    //   multiple of block size, it may "round up" to the nearest boundary size).
    // * The first use of the decryptor will never increase the size.
    // * The last block might be smaller (the total that goes out might be
    //   smaller than the total that goes in) due to padding at the end.
    //
    // In other words, to use correctly:
    // * Use a buffer that's a multiple of BlockSize
    // * Pass the data in through that buffer, specifying the amount of data available.
    // * Process the amount returned from the function.
    uint32_t decrypt(uint8_t *data, uint32_t size);

    const Mode &get_mode() const {
        return mode;
    }
};

} // namespace transfers

#include <gflags/gflags.h>
#include <stddef.h>
#include <stdint.h>
#include <unistd.h>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <limits>
#include <regex>
#include <string>
#include <vector>

#include "comp0019.h"
#include "decomp0019.h"

DEFINE_string(type, "both", "One of encode|decode|both");
DEFINE_string(file, "", "File to test/dump tests from");
DEFINE_bool(dump, false,
            "If true will not run tests, but will dump a single test");
DEFINE_uint64(test_index, std::numeric_limits<uint64_t>::max(),
              "If dump is specified this is the index of the test to dump.");

namespace lzw_test {
  using Bytes = std::vector<char>;

  class SingleChunk {
   public:
    SingleChunk(const Bytes* contents, size_t* at) : contents_(contents) {
      size_t& at_ref = *at;
      assert(at_ref < contents->size());
      const uint32_t* bytes_count =
          reinterpret_cast<const uint32_t*>(contents->data() + at_ref);
      count_ = *bytes_count;
      index_ = at_ref + 4;
      at_ref += count_ + 4;
    }

    void WriteToFileOrDie(FILE* out) const {
      size_t n_written = fwrite(contents_->data() + index_, count_, 1, out);
      assert(n_written == 1);
    }

    void WriteToFileOrDie(const std::string& filename) const {
      FILE* file = fopen(filename.c_str(), "w");
      WriteToFileOrDie(file);
      fclose(file);
    }

    Bytes ToBytes() const {
      Bytes out;
      out.resize(count_);
      std::memcpy(out.data(), contents_->data() + index_, count_);
      return out;
    }

    std::string ToString() const {
      Bytes bytes = ToBytes();
      return std::string(reinterpret_cast<char const*>(bytes.data()),
                         bytes.size());
    }

   private:
    const Bytes* contents_;
    size_t index_;
    size_t count_;
  };

  static Bytes ReadFileOrDie(const std::string& name) {
    char buffer[1024];
    FILE* file = fopen(name.c_str(), "rb");
    assert(file != NULL);

    Bytes out;
    while (true) {
      size_t n = fread(buffer, 1, sizeof(buffer), file);
      if (n <= 0) break;

      for (size_t i = 0; i < n; ++i) {
        out.emplace_back(buffer[i]);
      }
    }

    int error = ferror(file);
    assert(fclose(file) == 0);
    assert(error == 0);
    return out;
  }

  static std::string ReadFileToStringOrDie(const std::string& name) {
    Bytes bytes = ReadFileOrDie(name);
    return std::string(reinterpret_cast<char const*>(bytes.data()),
                       bytes.size());
  }

  static Bytes ReadFileOrDie(FILE* file) {
    fseek(file, 0L, SEEK_END);
    long int fsize = ftell(file);
    assert(fsize >= 0);
    rewind(file);

    if (fsize == 0) {
      return {};
    }

    Bytes contents;
    contents.resize(fsize);
    size_t n_read = fread(&(contents[0]), fsize, 1, file);
    assert(n_read == 1);
    return contents;
  }

  static FILE* GetFile() {
    FILE* out = tmpfile();
    if (out == nullptr) {
      perror("Unable to open file");
      abort();
    }

    return out;
  }

  // The following functions independently check encoding and decoding.
  static bool RunEncodeTest(const SingleChunk& model_encoded_output,
                            FILE* input_file, FILE* output_file) {
    bool check = true;

    Encode(input_file, output_file);
    Bytes encoded = ReadFileOrDie(output_file);
    Bytes model_encoded_input_bytes = model_encoded_output.ToBytes();
    if (model_encoded_input_bytes != encoded) {
      std::cout << "Encoder output does not match model output" << std::endl;
      check = false;
    }
    return check;
  }

  static bool RunDecodeTest(const SingleChunk& model_encoded_output,
                            FILE* input_file, FILE* output_file) {
    bool check = true;
    FILE* model_encoded_file = GetFile();

    model_encoded_output.WriteToFileOrDie(model_encoded_file);
    rewind(model_encoded_file);

    Decode(model_encoded_file, output_file);

    Bytes decoded_input = ReadFileOrDie(output_file);
    Bytes encoder_input_bytes = ReadFileOrDie(input_file);
    if (encoder_input_bytes != decoded_input) {
      std::cout << "Decoding does not obtain original input" << std::endl;
      check = false;
    }

    fclose(model_encoded_file);
    return check;
  }

  static void RunInputTest(size_t test_index, const SingleChunk& input,
                           const SingleChunk& expected_output, bool encode) {
    FILE* input_file = tmpfile();
    FILE* output_file = tmpfile();

    std::string test_string = " (decode)";
    if (encode) {
      test_string = " (encode)";
    }
    std::cout << "Will run test at index " << test_index << test_string
              << std::endl;

    input.WriteToFileOrDie(input_file);
    rewind(input_file);

    int fd;
    fpos_t pos;
    fflush(stdout);
    fgetpos(stdout, &pos);
    fd = dup(fileno(stdout));
    freopen("stdout_contents", "w", stdout);

    bool check = true;
    if (encode) {
      check = RunEncodeTest(expected_output, input_file, output_file);
    } else {
      check = RunDecodeTest(expected_output, input_file, output_file);
    }

    fflush(stdout);
    dup2(fd, fileno(stdout));
    close(fd);
    clearerr(stdout);
    fsetpos(stdout, &pos);

    if (!check) {
      std::string output = ReadFileToStringOrDie("stdout_contents");
      std::cout << output;

      std::string regex_string = expected_output.ToString();

      if (regex_string != "") {
        std::regex re(regex_string, std::regex_constants::ECMAScript |
                                        std::regex_constants::icase);
        if (!std::regex_search(output, re)) {
          std::cout << "Output does not match regex." << regex_string
                    << std::endl;
          exit(1);
        }
      }
    }

    fclose(input_file);
    fclose(output_file);
  }

  static void RunAllInputTestsFromFile(const std::string& file, bool encode) {
    Bytes contents = ReadFileOrDie(file);

    size_t test_index = 0;
    size_t at = 0;
    while (at != contents.size()) {
      SingleChunk input(&contents, &at);
      SingleChunk regex(&contents, &at);

      if (FLAGS_test_index == std::numeric_limits<uint64_t>::max() ||
          FLAGS_test_index == test_index) {
        RunInputTest(test_index, input, regex, encode);
      }

      ++test_index;
    }

    if (FLAGS_test_index != std::numeric_limits<uint64_t>::max() &&
        FLAGS_test_index >= test_index) {
      std::cout << "Unable to find test index " << FLAGS_test_index
                << std::endl;
      exit(1);
    }
  }

  // The following functions check if both encoding and decoding are correct.
  // Since it doesn't check encoder and decoder separately, this test will fail
  // whenever either the encoder *OR* the decoder are incorrect.
  static void RunEncodeDecodeTest(size_t test_index,
                                  const SingleChunk& encoder_input,
                                  const SingleChunk& model_encoded_output) {
    FILE* input_file = GetFile();
    FILE* encoded_file = GetFile();
    FILE* output_file = GetFile();

    std::cout << "Will run test at index " << test_index << std::endl;

    encoder_input.WriteToFileOrDie(input_file);
    rewind(input_file);

    Encode(input_file, encoded_file);
    Bytes encoded = ReadFileOrDie(encoded_file);
    Bytes model_encoded_input_bytes = model_encoded_output.ToBytes();
    if (model_encoded_input_bytes != encoded) {
      std::cout << "Encoder output does not match model output" << std::endl;
      exit(1);
    }

    rewind(encoded_file);
    Decode(encoded_file, output_file);
    Bytes decoded_input = ReadFileOrDie(output_file);
    Bytes encoder_input_bytes = encoder_input.ToBytes();
    if (encoder_input_bytes != decoded_input) {
      std::cout << "Decoding does not obtain original input" << std::endl;
      exit(1);
    }

    fclose(input_file);
    fclose(encoded_file);
    fclose(output_file);
  }

  static void RunAllTestsFromFile(const std::string& file) {
    Bytes contents = ReadFileOrDie(file);

    size_t test_index = 0;
    size_t at = 0;
    while (at != contents.size()) {
      SingleChunk encoder_input(&contents, &at);
      SingleChunk model_encoded_input(&contents, &at);

      if (FLAGS_test_index == std::numeric_limits<uint64_t>::max() ||
          FLAGS_test_index == test_index) {
        RunEncodeDecodeTest(test_index, encoder_input, model_encoded_input);
      }

      ++test_index;
    }

    if (FLAGS_test_index != std::numeric_limits<uint64_t>::max() &&
        FLAGS_test_index >= test_index) {
      std::cout << "Unable to find test index " << FLAGS_test_index
                << std::endl;
      exit(1);
    }
  }

  // Dump functions
  static void DumpTest(const std::string& file) {
    Bytes contents = ReadFileOrDie(file);

    size_t test_index = 0;
    size_t at = 0;
    while (at != contents.size()) {
      SingleChunk encoder_input(&contents, &at);
      SingleChunk model_encoded_input(&contents, &at);

      if (test_index == FLAGS_test_index) {
        encoder_input.WriteToFileOrDie("encoder_input");
        std::cout << "Encoder input saved to 'encoder_input'" << std::endl;
        model_encoded_input.WriteToFileOrDie("model_encoded_stream");
        std::cout << "Model encoder output saved to 'model_encoded_stream'"
                  << std::endl;
        return;
      }

      ++test_index;
    }

    std::cout << "Unable to find test index " << test_index;
    abort();
  }

  static void DumpInputTest(const std::string& file, const std::string& type) {
    Bytes contents = ReadFileOrDie(file);

    size_t test_index = 0;
    size_t at = 0;
    while (at != contents.size()) {
      SingleChunk input(&contents, &at);
      SingleChunk regex(&contents, &at);

      if (test_index == FLAGS_test_index) {
        std::string filename = type + "r_input";
        input.WriteToFileOrDie(filename);
        std::cout << "Input saved to " << filename << std::endl;
        std::cout << "Regex is: " << regex.ToString() << std::endl;
        return;
      }

      ++test_index;
    }

    std::cout << "Unable to find test index " << FLAGS_test_index;
    abort();
  }

}  // namespace lzw_test

int main(int argc, char** argv) {
  gflags::ParseCommandLineFlags(&argc, &argv, false);
  if (FLAGS_dump) {
    lzw_test::DumpTest(FLAGS_file);
    
    return 0;
  }

  if (FLAGS_type == "both") {
    lzw_test::RunAllTestsFromFile(FLAGS_file);
  } else if (FLAGS_type == "encode") {
    lzw_test::RunAllInputTestsFromFile(FLAGS_file, true);
  } else if (FLAGS_type == "decode") {
    lzw_test::RunAllInputTestsFromFile(FLAGS_file, false);
  }

  return 0;
}

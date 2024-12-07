#include <iostream>
#include <fstream>
#include <string>

void PatchDLL(const std::string& dllPath) {
    std::fstream file(dllPath, std::ios::in | std::ios::out | std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open " << dllPath << std::endl;
        return;
    }

    // Example: Replace hardcoded key with "ANYTHING-0000"
    const std::string originalKey = "SECRET-1234";
    const std::string patchedKey = "ANYTHING-0000";

    // Read the entire DLL into a string buffer
    std::string buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    size_t pos = buffer.find(originalKey);

    if (pos != std::string::npos) {
        // Go to the position where the key was found
        file.seekp(pos);

        // Write the patched key into the file (ensure that it's the same length or fill the remaining space with NULs)
        file.write(patchedKey.c_str(), patchedKey.size());

        // If the new key is shorter than the original, fill the remaining space with NUL characters
        if (patchedKey.size() < originalKey.size()) {
            file.write("\0", originalKey.size() - patchedKey.size());
        }

        std::cout << "DLL patched successfully!" << std::endl;
    }
    else {
        std::cerr << "Original key not found in DLL." << std::endl;
    }

    file.close();
}

int main() {
    std::string dllPath = "../verify_key.dll";
    PatchDLL(dllPath);
    return 0;
}

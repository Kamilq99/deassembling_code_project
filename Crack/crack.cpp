#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

// Function to replace key in DLL file
void replaceKeyInDll(const std::string& dllPath, const std::string& oldKey, const std::string& newKey) {
    FILE* file = fopen(dllPath.c_str(), "rb");
    if (!file) {
        std::cerr << "Error: Could not open DLL file." << std::endl;
        return;
    }

 /*   std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();
    file.close(); */
    char* data = new char[0x10000];
    int num = fread(data, 1, 0x10000, file);
    fclose(file);
    for (int i = 0; i < num; i++)
    {
        int j = 0;
        if (data[i] == oldKey[j]) {
            for (j = 1; j < oldKey.length(); j++) {
                if (data[i + j] != oldKey[j])
                    break;
            }
            if (data[i + j] == oldKey[j])
            {
                for (j = 0; j < oldKey.length(); j++)
                {
                    data[i + j] = newKey[j];
                }
            }
        }
    }
    
/*
    size_t pos = content.find(oldKey);
    if (pos != std::string::npos) {
        content.replace(pos, oldKey.length(), newKey);

        std::ofstream outFile(dllPath);
        outFile << content;
        outFile.close();

        std::ifstream verifyFile(dllPath);
        std::stringstream verifyBuffer;
        verifyBuffer << verifyFile.rdbuf();
        std::string verifyContent = verifyBuffer.str();
        verifyFile.close();

        if (verifyContent.find(newKey) != std::string::npos) {
            std::cout << "Key successfully replaced in DLL." << std::endl;
        }
        else {
            std::cerr << "Error: Failed to replace key in DLL." << std::endl;
        }
    }
    else {
        std::cerr << "Error: Old key not found in DLL." << std::endl;
    }
    */
    std::ofstream outFile(dllPath, std::ios::binary);
    outFile.write(data, num);
    outFile.close();
}

int main() {
    std::string dllPath = "verify_key.dll";
    std::string oldKey = "SECRET-1234";
    std::string newKey = "ANYTHI-0000";

    replaceKeyInDll(dllPath, oldKey, newKey);

    return 0;
}
//the end
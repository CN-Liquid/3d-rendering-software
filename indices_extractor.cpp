#include <fstream>
#include <string>
#include <vector>
#include <iostream>

void extractVerticesAndIndices(const std::string& objFilePath, const std::string& outputFilePath) {
    std::ifstream objFile(objFilePath);
    std::ofstream outputFile(outputFilePath);

    if (!objFile.is_open() || !outputFile.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
        return;
    }

    std::string line;
    std::vector<std::string> vertices;
    std::vector<std::string> normals;
    std::vector<std::string> indices;

    while (std::getline(objFile, line)) {
        if (line.size() > 1 && line[0] == 'v' && line[1] == ' ') {
            vertices.push_back(line.substr(2)); // Extract vertices (v x y z)

        } else if (line.size() > 1 && line[0] == 'f') {
            size_t spacePos = line.find(' ');
            if (spacePos != std::string::npos) {
                std::string face = line.substr(spacePos + 1);
                std::vector<std::string> faceIndices;
                size_t prevPos = 0;
                size_t pos = face.find(' ');
                while (pos != std::string::npos) {
                    faceIndices.push_back(face.substr(prevPos, pos - prevPos));
                    prevPos = pos + 1;
                    pos = face.find(' ', prevPos);
                }
                faceIndices.push_back(face.substr(prevPos));

                for (const std::string& index : faceIndices) {
                    size_t slashPos = index.find('/');
                    if (slashPos != std::string::npos) {
                        indices.push_back(index.substr(0, slashPos));
                    } else {
                        indices.push_back(index);
                    }
                }
            }
        }
    }

    // Write vertices to output file
    for (const std::string& vertex : vertices) {
        outputFile << "v " << vertex << '\n';
    }


    // Write indices to output file
    for (size_t i = 0; i < indices.size(); i += 3) {
        outputFile <<"f "<< indices[i] << ' ' << indices[i + 1] << ' ' << indices[i + 2] << '\n';
    }

    objFile.close();
    outputFile.close();
}

int main() {
    std::string objFilePath = "cottage_obj.obj";
    std::string outputFilePath = "vertices_indices.obj";
    extractVerticesAndIndices(objFilePath, outputFilePath);
    return 0;
}
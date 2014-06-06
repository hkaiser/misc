#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

class SimpleDomain
{
public:

    SimpleDomain(const int id = 0, const int np = 0) :
        id(id),
        np(np)
    {}
    
    int id;
    int np;
};


class ADCIRCInitializer
{
public:
    ADCIRCInitializer(const std::string& meshDir) :
        meshDir(meshDir)
    {
        grid();
    }
    
    virtual void grid()
    {
        std::ifstream meshFile;
        openMeshFile(meshFile);
        
        int numberOfDomains;
        
        readHeader(meshFile, &numberOfDomains);
    }

    
private:
    std::string meshDir;

    void openMeshFile(std::ifstream& meshFile)
    {
        std::string meshFileName = meshDir;
        meshFileName.append("/fort.80");
        meshFile.open(meshFileName.c_str());
        if (!meshFile) {
            throw std::runtime_error("could not open fort.80 file"+meshFileName);
        }    
    }

    void readHeader(std::ifstream& meshFile, int *numberOfDomains)
    {
        int numberOfElements;
        int numberOfPoints;

        std::string buffer(1024, ' ');
        //Discard first 3 lines:
        std::getline(meshFile, buffer);
        std::getline(meshFile, buffer);
        std::getline(meshFile, buffer);

        meshFile >> numberOfElements;
        meshFile >> numberOfPoints;
        
        //Discard rest of line
        std::getline(meshFile, buffer);

        meshFile >> *numberOfDomains;

        std::cerr << "number of elements: " << numberOfElements << "\n"
                  << "number of points: " << numberOfPoints << "\n"
                  << "number of domains: " << *numberOfDomains << "\n";

        //Discard rest of the line:
        std::getline(meshFile, buffer);

        //Discard next 8 lines:
        std::getline(meshFile, buffer);
        std::getline(meshFile, buffer);
        std::getline(meshFile, buffer);
        std::getline(meshFile, buffer);
        std::getline(meshFile, buffer);
        std::getline(meshFile, buffer);
        std::getline(meshFile, buffer);
        std::getline(meshFile, buffer);
        
        std::cerr << buffer << "\n";

        for (int domain = 0; domain < *numberOfDomains; ++domain) {
            int buf;
            int numNodes;
            meshFile >> buf;
            if (buf != domain) {
                throw std::runtime_error("buf does not match domain");
            }
            meshFile >> numNodes;
            //Discard rest of the line
            std::getline(meshFile, buffer);
            
            std::cerr << "Domain: " << domain << " numNodes: " << numNodes << "\n";
            
            for (int node = 0; node < numNodes; ++node) {
                int nodeNum;
                meshFile >> nodeNum;
                
                std::cerr << "Domain: " << domain << " Node: " << nodeNum << "\n";
            }
            
            // throw away the rest of the line
            std::getline(meshFile, buffer);
        }
        // Throw away another line
        std::getline(meshFile, buffer);
        std::vector<int> ownerID;
        for (int node = 0; node < numberOfPoints; node++) {
            int global_label;
            int local_label;
            int owner;
            meshFile >> global_label;
            meshFile >> owner;
            meshFile >> local_label;
            
            std::getline(meshFile, buffer);//discard rest of line
            
            ownerID.push_back(owner);
        }

        for (int i=0; i< numberOfPoints; i++){
            std::cerr << i << " " << ownerID[i] << "\n";
        }
            
    }    
};

    
int main(int argc, char* argv[])
{
    ADCIRCInitializer("/home/zbyerly/misc/parallel_qah");
}

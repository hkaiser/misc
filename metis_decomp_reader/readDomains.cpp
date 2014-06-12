#include <libgeodecomp.h>
#include <libgeodecomp/storage/multicontainercell.h>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>

using namespace LibGeoDecomp;

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
        std::ifstream fort80File;

        double maxDiameter;
        
        int numberOfDomains;
        int numberOfElements;
        int numberOfPoints;
        std::vector<int> ownerID;
        std::vector<neighborTable> myNeighborTables;
        openfort80File(fort80File);
        readfort80(fort80File, &numberOfDomains, &numberOfElements, &numberOfPoints, &ownerID);
        
        std::vector<FloatCoord<2> > centers;

        for (int i=0; i< numberOfDomains; i++){
            neighborTable myNeighborTable;
            std::ifstream fort18File;
            int numberOfNeighbors;
            openfort18File(fort18File, i);
            readfort18(fort18File, &numberOfNeighbors, &i, &myNeighborTable);            
//            std::cerr << "Domain: " << i << " number of neighbors: " << numberOfNeighbors << "\n";
            myNeighborTables.push_back(myNeighborTable);

            //Read fort.14 file for each domain
            int numberOfPoints;
            int numberOfElements;
            std::ifstream fort14File;
            openfort14File(fort14File, i);
            readFort14Header(fort14File, &numberOfElements, &numberOfPoints);
            std::vector<FloatCoord<3> > points;
            readFort14Points(fort14File, &points, numberOfPoints);            
            FloatCoord<2> center = determineCenter(&points);
            center /= numberOfPoints;
            
            centers.push_back(center);
        }
        

        std::cerr << centers << "\n";

        maxDiameter = determineMaximumDiameter(&centers, &myNeighborTables);
        
        std::cerr << "myNeighborTables.size() = " << myNeighborTables.size() << "\n";
        for(int i=0; i<myNeighborTables.size(); i++){
            std::cerr << "myNeighborTables[" << i << "].myNeighbor.size() = " << myNeighborTables[i].myNeighbor.size() << "\n";
            for (int j=0; j<myNeighborTables[i].myNeighbor.size(); j++){
                std::cerr << "myNeighborTables[" << i << "].myNeighbor[" << j << "].neighborID = " 
                          << myNeighborTables[i].myNeighbor[j].neighborID << "\n";
                std::cerr << "myNeighborTables[" << i << "].myNeighbor[" << j << "].recvNodes.size() = " 
                          << myNeighborTables[i].myNeighbor[j].recvNodes.size() << "\n";
                std::cerr << "myNeighborTables[" << i << "].myNeighbor[" << j << "].sendNodes.size() = " 
                          << myNeighborTables[i].myNeighbor[j].sendNodes.size() << "\n";
            }
            
        }
        

    }
    
    
    
    
    
private:
    std::string meshDir;
    
    struct neighbor
    {
        int neighborID;
        std::vector<int> sendNodes;
        std::vector<int> recvNodes;
    };

    struct neighborTable 
    {
        std::vector<neighbor> myNeighbor;
    };

    FloatCoord<2> determineCenter(std::vector<FloatCoord<3> > *points) 
    {
        FloatCoord<2> center;
//        std::cerr << "points->size() = " << points->size() << "\n";
        for (int i=0; i < points->size(); i++){
//            std::cerr << "points[0][" << i << "][0] = " << points[0][i][0] << "\n";
//            std::cerr << "points[1][" << i << "] = " << points[1][i] << "\n";
//            std::cerr << "points[" << i << "][0] = " << points[i][0] << "\n";
//            std::cerr << "points[" << i << "][1] = " << points[i][1] << "\n";
            FloatCoord<2> coord(points[0][i][0],points[0][i][1]);
            center += coord;
        }
        return center;
    }
    
    double determineMaximumDiameter(
        const std::vector<FloatCoord<3> > points,
        const std::vector<neighborTable> neighborTables)
    {
        double maxDiameter = 0;

        int numPoints = points.size();
        std::cerr << "numPoints = " << numPoints << "\n";
        for (int point = 0; point < 1; ++point) {
            //int numNeighbors = neighbor;
            FloatCoord<2> minPoint(
                std::numeric_limits<double>::max(),
                std::numeric_limits<double>::max());
            FloatCoord<2> maxPoint(
                -std::numeric_limits<double>::max(),
                -std::numeric_limits<double>::max());

            //maxDiameter = std::max(maxDiameter, diameter);
        }
        
        return maxDiameter;
    }

        
    void openfort80File(std::ifstream& meshFile)
    {
        std::string meshFileName = meshDir;
        meshFileName.append("/fort.80");
        meshFile.open(meshFileName.c_str());
        if (!meshFile) {
            throw std::runtime_error("could not open fort.80 file"+meshFileName);
        }    
    }
        
    void readfort80(std::ifstream& meshFile, int *numberOfDomains, int *numberOfElements, int *numberOfPoints, std::vector<int> *ownerID)
    {
        std::string buffer(1024, ' ');
        //Discard first 3 lines:
        std::getline(meshFile, buffer);
        std::getline(meshFile, buffer);
        std::getline(meshFile, buffer);
            
        meshFile >> *numberOfElements;
        meshFile >> *numberOfPoints;
            
        //Discard rest of line
        std::getline(meshFile, buffer);
            
        meshFile >> *numberOfDomains;
            
//        std::cerr << "number of elements: " << *numberOfElements << "\n"
//                  << "number of points: " << *numberOfPoints << "\n"
//                  << "number of domains: " << *numberOfDomains << "\n";    
            
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
        
//        std::cerr << buffer << "\n";

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
            
//            std::cerr << "Domain: " << domain << " numNodes: " << numNodes << "\n";
            
            for (int node = 0; node < numNodes; ++node) {
                int nodeNum;
                meshFile >> nodeNum;
                
//                std::cerr << "Domain: " << domain << " Node: " << nodeNum << "\n";
            }
            
            // throw away the rest of the line
            std::getline(meshFile, buffer);
        }
        // Throw away another line
        std::getline(meshFile, buffer);
        for (int node = 0; node < *numberOfPoints; node++) {
            int global_label;
            int local_label;
            int owner;
            meshFile >> global_label;
            meshFile >> owner;
            meshFile >> local_label;
            
            std::getline(meshFile, buffer);//discard rest of line
            
            ownerID->push_back(owner);
        }            
    }    

    void openfort18File(std::ifstream& meshFile, int domainID)
    {
        std::string meshFileName = meshDir;
        meshFileName.append("/PE");
        std::stringstream buf;
        buf.width(4);
        buf.fill('0');
        buf << domainID;
        meshFileName.append(buf.str());
        meshFileName.append("/fort.18");
//        std::cerr << meshFileName << "\n";
        meshFile.open(meshFileName.c_str());
        if (!meshFile) {
            throw std::runtime_error("could not open fort.18 file"+meshFileName);
        }    
    }


    void readfort18(std::ifstream& meshFile, int *numberOfNeighbors, const int *domainID, neighborTable *myNeighborTable)
    {
        int numberOfElements;
        int numberOfNodes;
        int domainIDFromFile;
        int numberOfResNodes;
        std::vector<int> residentNodes;        

        std::string buffer(1024, ' ');
        //Discard first line:
        std::getline(meshFile, buffer);

        //Discard first three entries of line 2:
        meshFile >> buffer;
        meshFile >> buffer;
        meshFile >> buffer;
        
        meshFile >> numberOfElements;
        std::getline(meshFile, buffer); //Discard the rest of the line

        for (int i=0; i<numberOfElements; i++){std::getline(meshFile, buffer);}

        //Discard first three entries of next line:
        meshFile >> buffer;
        meshFile >> buffer;
        meshFile >> buffer;        
        meshFile >> numberOfNodes;
        std::getline(meshFile, buffer); //Discard the rest of the line
        for (int i=0; i<numberOfNodes; i++){std::getline(meshFile, buffer);}

        //NFLUXF line: manually discard for now.  May need to do
        //something more robust later.
        std::getline(meshFile, buffer);

        //Discard first three entries of next line:        
        meshFile >> buffer;
        meshFile >> buffer;
        meshFile >> buffer;        
        int NETA;
        meshFile >> NETA;
        std::getline(meshFile, buffer); //Discard the rest of the line
        for (int i=0; i<NETA; i++){std::getline(meshFile, buffer);}

        //Discard first three entries of next line:        
        meshFile >> buffer;
        meshFile >> buffer;
        meshFile >> buffer;        
        int NSTAE;
        meshFile >> NSTAE;
        std::getline(meshFile, buffer); //Discard the rest of the line
        for (int i=0; i<NSTAE; i++){std::getline(meshFile, buffer);}

        //Discard first three entries of next line:        
        meshFile >> buffer;
        meshFile >> buffer;
        meshFile >> buffer;        
        int NSTAV;
        meshFile >> NSTAV;
        std::getline(meshFile, buffer); //Discard the rest of the line
        for (int i=0; i<NSTAV; i++){std::getline(meshFile, buffer);}
        
        //Discard NSTAM and NSTAC lines manually
        std::getline(meshFile, buffer);        
        std::getline(meshFile, buffer);
        
        //RES NODE line:
        meshFile >> buffer;
        meshFile >> buffer;
        meshFile >> domainIDFromFile;
        meshFile >> numberOfResNodes;
        
        for (int i=0; i<numberOfResNodes; i++)
        {
            int node;
            
            meshFile >> node;
            residentNodes.push_back(node);
        }        
        std::getline(meshFile, buffer); //Discard remainder of the
                                        //line.

        //COMM PE line
        meshFile >> buffer; //COMM
        meshFile >> buffer; //PE
        meshFile >> *numberOfNeighbors;
        std::getline(meshFile, buffer);//discard rest of the line

        for (int i=0; i<*numberOfNeighbors; i++){
            neighbor neighbor;
            int numberOfRecvNodes;
            meshFile >> buffer; //RECV
            meshFile >> buffer; //PE
            meshFile >> neighbor.neighborID;
            meshFile >> numberOfRecvNodes;
            std::getline(meshFile, buffer);//discard rest of the line

            //Assemble arrays of nodes to be received
            for (int j=0; j<numberOfRecvNodes; j++){
                int receiveNode;
                meshFile >> receiveNode;   
                neighbor.recvNodes.push_back(receiveNode);
            }
            std::getline(meshFile, buffer);//discard rest of the line
            myNeighborTable->myNeighbor.push_back(neighbor);
        }
        
        for (int i=0; i<*numberOfNeighbors; i++){
            int neighbor;
            int numberOfSendNodes;
            meshFile >> buffer; //SEND
            meshFile >> buffer; //PE
            meshFile >> neighbor;
            meshFile >> numberOfSendNodes;
            std::getline(meshFile, buffer);//discard rest of the line
            //Assemble arrays of nodes to be sent
            for (int j=0; j<numberOfSendNodes; j++){
                int sendNode;
                meshFile >> sendNode;                
                myNeighborTable->myNeighbor[i].sendNodes.push_back(sendNode);
            }
            std::getline(meshFile, buffer);//discard rest of the line
        }
        
    }    

    void openfort14File(std::ifstream& meshFile, int domainID)
    {
        std::string meshFileName = meshDir;
        meshFileName.append("/PE");
        std::stringstream buf;
        buf.width(4);
        buf.fill('0');
        buf << domainID;
        meshFileName.append(buf.str());
        meshFileName.append("/fort.14");
//        std::cerr << meshFileName << "\n";
        meshFile.open(meshFileName.c_str());
        if (!meshFile) {
            throw std::runtime_error("could not open fort.14 file "+meshFileName);
        }    
    }



    void readFort14Header(std::ifstream& meshFile, int *numberOfElements, int *numberOfPoints)
    {
        std::string buffer(1024, ' ');
        // discard first line, which only holds comments anyway
        std::getline(meshFile, buffer);

        meshFile >> *numberOfElements;
        meshFile >> *numberOfPoints;

        // discard remainder of line
        std::getline(meshFile, buffer);

//        std::cerr << "numberOfElements: " << *numberOfElements << "\n"
//                  << "numberOfPoints: " << *numberOfPoints << "\n";

        if (!meshFile.good()) {
            throw std::logic_error("could not read header");
        }
    }

    void readFort14Points(std::ifstream& meshFile, std::vector<FloatCoord<3> > *points, const int numberOfPoints)
    {
        std::string buffer(1024, ' ');

        for (int i = 0; i < numberOfPoints; ++i) {
            FloatCoord<3> p;
            int buf;

            meshFile >> buf;
            meshFile >> p[0];
            meshFile >> p[1];
            meshFile >> p[2];
            std::getline(meshFile, buffer);

            *points << p;
        }

        if (!meshFile.good()) {
            throw std::runtime_error("could not read points");
        }
    }


};

    
int main(int argc, char* argv[])
{
    ADCIRCInitializer("/home/zbyerly/misc/parallel_qah");
}

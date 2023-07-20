
#include <stdio.h>

#include<array>
#include<algorithm>
#include<iostream>
#include<sstream>
#include<fstream>

struct Color{
    int red=0;
    int green=0;
    int blue=0;
};

bool handleSTOI(const std::string str,int &num)
{
try {
        num = std::stoi(str);
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument: " << e.what() << std::endl;
    }
    catch (const std::out_of_range& e) {
        std::cerr << "Out of range: " << e.what() << std::endl;
    }
    catch(...)
    {
        return false;
    }
    return true;
}
bool parseTuple(const std::string &tupleStr,Color &color)
{
  size_t commaCount=std::count(tupleStr.begin(),tupleStr.end(),',');  
    std::array<int,3> rgbValues={0,0,0};
  
  if(commaCount!=2)
    {
  std::cout<<"Invalid comma count in tuble "<<tupleStr<<"\n";
        return false;
    }

    size_t start=0;
    size_t stop=tupleStr.find(',');
    int bred=handleSTOI(tupleStr.substr(start+1,stop-1),rgbValues[0]);
    start=stop;
    stop=tupleStr.find(',');
  bool bgreen=handleSTOI(tupleStr.substr(start+1,stop-1),rgbValues[1]);
  int bblue=handleSTOI(tupleStr.substr(stop+1),rgbValues[2]);
  if(bred&&bgreen&&bblue)
  {
    for(int val:rgbValues)
        {
            if(val>255)
            {
                std::cout<<"Color value of "<<val<<"Is greatere than 255\n";
                return false;
            }
        }
    }
  color.red=rgbValues[0];
  color.green=rgbValues[1];
  color.blue=rgbValues[2];
  std::cout<<"Valid tuple ("<<rgbValues[0]<<","<<rgbValues[1]<<","<<rgbValues[2]<<"),"<<" found\n";
  return true;
}
// Main code
int main(int, char**)
{
        std::array<std::array<Color,10>,10> grid;

        std::ifstream stream;
        stream.open("test_file.txt");
        std::string line;
        std::stringstream file;
        if(stream.is_open())
        {
        while(std::getline(stream,line))
        {
           file<<line; 
        }
        std::string fileString=file.str();
        size_t start=fileString.find("FRAME,");
        size_t stop=fileString.find("END");
        if(stop==std::string::npos)
        {
            std::cout<<"Error, missing END";
            return EXIT_FAILURE;
        }
        if(start==std::string::npos)
        {
            std::cout<<"Error, missing FRAME";
            return EXIT_FAILURE;
        }
        std::string token;
        size_t tokenStart=fileString.find(',',start);
        //remove spaces
        fileString.erase(std::remove_if(fileString.begin(), fileString.end(), ::isspace), fileString.end());
        int count=0;
        while(tokenStart!=std::string::npos)
            {

            tokenStart=fileString.find(',',tokenStart);
            size_t tagStart=fileString.find('<',tokenStart);
            size_t tagEnd=fileString.find('>',tagStart);
            if(tagEnd>tagStart &&tagStart!=std::string::npos)
            {
            Color color={0,0,0};

            if(parseTuple(fileString.substr(tagStart+1,tagEnd-tagStart-1),color))
            {
                int row=count/10;
                int col=count%10;
                std::cout<<"Setting color for row "<<row<<" col "<<col<<"\n";
                grid[row][col]=color;
            } 
            }
            tokenStart=tagEnd;
            count++;
            }
        stream.close();
        }
    return EXIT_SUCCESS;
}

#include "../includes/evantSwitch.hpp"

void EvantSwitch::addEvant(std::string EvantName, FunctionPtr funtionPointer){
    evantsMap.insert({EvantName,funtionPointer});
}
std::string EvantSwitch::getCleanTarget(std::string_view target){
    std::string tmp;
    std::back_insert_iterator<std::string> ins(tmp);
   
    std::string_view::iterator start = target.begin();
    std::string_view::iterator end = target.end();
   

    while(start != end && *start != '?'){
        ins = *start;
        start++;
    }
    return tmp;
}

FunctionPtr EvantSwitch::getEvantHendler(request& request){
     std::string cleanTarget =  this->getCleanTarget(request.target());
        
     FunctionPtr functionPointer = evantsMap[cleanTarget];
     void* ptr = (void*)functionPointer;
     if(!functionPointer){
        std::cout << "clean target = " << cleanTarget << std::endl;
        assert(false && "Can Not Find evant hendle pointer");
     }
    return functionPointer;
     

}
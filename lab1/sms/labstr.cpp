#include "labstr.h"
#include <iostream>
#ifdef _MSC_VER
#pragma warning(disable: 4355)
#endif
Labstr::Labstr()
#ifdef CRTP
: isAcceptable(false), count(0), smscase(0)
#else
        : _fsm(*this),
          isAcceptable(false), count(0), smscase(0)
#endif
{
#ifdef FSM_DEBUG
    #ifdef CRTP
    setDebugFlag(true);
#else
    _fsm.setDebugFlag(true);
#endif
#endif
}
// компиляция java


bool Labstr::CheckString(const std::string& thestr, proj::NumAnalitics & store)
{
#ifdef CRTP
    enterStartState();
    for (int i = 0; i < thestr.length(); i++)
    {
        if ((thestr[i] >= 'A' && thestr[i] <= 'Z') || (thestr[i] >= 'a' && thestr[i] <= 'z'))
        {
            Letter(thestr[i]);
        }
        else if ((thestr[i] >= '0') && (thestr[i] <= '9')) {
            Digit(thestr[i]);
        }
        else if ((thestr[i] == ' ') || (thestr[i] == '\t')) {
            SpaceOrTab();
        }
        else if ((thestr[i] >= '!' && thestr[i] <= '/') || (thestr[i] >= ':' && thestr[i] <= '@'))
        {
            PunctMark(thestr[i])
        }
        else{
           Unknown();
        }
    }
    EOS();
#else
    _fsm.enterStartState();
    for (int i = 0; i < thestr.length(); i++)
    {
        if ((thestr[i] >= 'A' && thestr[i] <= 'Z') || (thestr[i] >= 'a' && thestr[i] <= 'z'))
        {
            _fsm.Letter(thestr[i]);
        }
        else if ((thestr[i] >= '0') && (thestr[i] <= '9')) {
            _fsm.Digit(thestr[i]);
        }
        else if ((thestr[i] == ' ') || (thestr[i] == '\t')) {
            _fsm.SpaceOrTab();
        }
        else if ((thestr[i] >= '!' && thestr[i] <= '/') || (thestr[i] >= ':' && thestr[i] <= '@'))
        {
            _fsm.PunctMark(thestr[i]);
        }
        else{
            _fsm.Unknown();
        }
    }
    _fsm.EOS();
#endif
    if(isAcceptable){
        while(bufnums.size()){
            store.add(bufnums.back());
            bufnums.pop_back();
        }
    }
    else{
        while(bufnums.size()){
            bufnums.pop_back();
        }
    }
    return isAcceptable;
}
int Labstr::getCount() const {// nodiscard - нужен для того чтобы результат вызова функции использовался
    return count;
}
bool Labstr::isSms(){
    std::string sms = "sms";
    if(buffer == sms){
        smscase = 1;
        return true;
    }
    return false;
}
bool Labstr::isTelorFax(){
    std::string tel = "tel";
    if(buffer == tel){
        return true;
    }
    std::string fax = "fax";
    if(buffer == fax){
        return true;
    }
    return false;
}
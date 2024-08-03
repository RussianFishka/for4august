//
// ex: set ro:
// DO NOT EDIT.
// generated by smc (http://smc.sourceforge.net/)
// from file : labstr.sm
//

#ifndef LABSTR_SM_H
#define LABSTR_SM_H


#define SMC_USES_IOSTREAMS

#include "statemap.h"

// Forward declarations.
class Map1;
class Map1_Start;
class Map1_Parsing;
class Map1_Message;
class Map1_Unacceptable;
class Map1_Default;
class LabstrState;
class labstrContext;
class Labstr;

class LabstrState :
    public statemap::State
{
public:

    LabstrState(const char * const name, const int stateId)
    : statemap::State(name, stateId)
    {};

    virtual void Entry(labstrContext&) {};
    virtual void Exit(labstrContext&) {};

    virtual void Digit(labstrContext& context, char pdigit);
    virtual void EOS(labstrContext& context);
    virtual void Letter(labstrContext& context, char symb);
    virtual void PunctMark(labstrContext& context, char symb);
    virtual void SpaceOrTab(labstrContext& context);
    virtual void Unknown(labstrContext& context);

protected:

    virtual void Default(labstrContext& context);
};

class Map1
{
public:

    static Map1_Start Start;
    static Map1_Parsing Parsing;
    static Map1_Message Message;
    static Map1_Unacceptable Unacceptable;
};

class Map1_Default :
    public LabstrState
{
public:

    Map1_Default(const char * const name, const int stateId)
    : LabstrState(name, stateId)
    {};

};

class Map1_Start :
    public Map1_Default
{
public:
    Map1_Start(const char * const name, const int stateId)
    : Map1_Default(name, stateId)
    {};

    virtual void Digit(labstrContext& context, char pdigit);
    virtual void EOS(labstrContext& context);
    virtual void Letter(labstrContext& context, char symb);
    virtual void PunctMark(labstrContext& context, char symb);
    virtual void SpaceOrTab(labstrContext& context);
    virtual void Unknown(labstrContext& context);
};

class Map1_Parsing :
    public Map1_Default
{
public:
    Map1_Parsing(const char * const name, const int stateId)
    : Map1_Default(name, stateId)
    {};

    virtual void Digit(labstrContext& context, char pdigit);
    virtual void EOS(labstrContext& context);
    virtual void Letter(labstrContext& context, char symb);
    virtual void PunctMark(labstrContext& context, char symb);
    virtual void SpaceOrTab(labstrContext& context);
    virtual void Unknown(labstrContext& context);
};

class Map1_Message :
    public Map1_Default
{
public:
    Map1_Message(const char * const name, const int stateId)
    : Map1_Default(name, stateId)
    {};

    virtual void Digit(labstrContext& context, char pdigit);
    virtual void EOS(labstrContext& context);
    virtual void Letter(labstrContext& context, char symb);
    virtual void PunctMark(labstrContext& context, char symb);
    virtual void SpaceOrTab(labstrContext& context);
    virtual void Unknown(labstrContext& context);
};

class Map1_Unacceptable :
    public Map1_Default
{
public:
    Map1_Unacceptable(const char * const name, const int stateId)
    : Map1_Default(name, stateId)
    {};

    virtual void Digit(labstrContext& context, char pdigit);
    virtual void EOS(labstrContext& context);
    virtual void Letter(labstrContext& context, char symb);
    virtual void PunctMark(labstrContext& context, char symb);
    virtual void SpaceOrTab(labstrContext& context);
    virtual void Unknown(labstrContext& context);
};

class labstrContext :
    public statemap::FSMContext
{
public:

    explicit labstrContext(Labstr& owner)
    : FSMContext(Map1::Start),
      _owner(owner)
    {};

    labstrContext(Labstr& owner, const statemap::State& state)
    : FSMContext(state),
      _owner(owner)
    {};

    virtual void enterStartState()
    {
        getState().Entry(*this);
        return;
    }

    inline Labstr& getOwner()
    {
        return (_owner);
    };

    inline LabstrState& getState()
    {
        if (_state == NULL)
        {
            throw statemap::StateUndefinedException();
        }

        return dynamic_cast<LabstrState&>(*_state);
    };

    inline void Digit(char pdigit)
    {
        getState().Digit(*this, pdigit);
    };

    inline void EOS()
    {
        getState().EOS(*this);
    };

    inline void Letter(char symb)
    {
        getState().Letter(*this, symb);
    };

    inline void PunctMark(char symb)
    {
        getState().PunctMark(*this, symb);
    };

    inline void SpaceOrTab()
    {
        getState().SpaceOrTab(*this);
    };

    inline void Unknown()
    {
        getState().Unknown(*this);
    };

private:
    Labstr& _owner;
};


#endif // LABSTR_SM_H

//
// Local variables:
//  buffer-read-only: t
// End:
//
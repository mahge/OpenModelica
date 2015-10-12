#pragma once



//#include "FactoryExport.h"
//#include <Core/Utils/extension/logger.hpp>

class IPropertyReader
{
  public:
    IPropertyReader() {}
    virtual ~IPropertyReader() {}


    virtual void readInitialValues(IContinuous& system, boost::shared_ptr<ISimVars> sim_vars) = 0;
    virtual std::string getPropertyFile()= 0;
    virtual void setPropertyFile(std::string file)= 0;
	virtual const output_int_vars_t& getIntOutVars()  = 0;
	virtual const output_real_vars_t& getRealOutVars()= 0;
	virtual const output_bool_vars_t& getBoolOutVars()= 0;

};

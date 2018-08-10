#ifndef ABSTRACTLOGOBJECT_H_
#define ABSTRACTLOGOBJECT_H_

#include <string>
#include <set>
#include <map>
#include <vector>

///////////////////////////////////////////////////////////////////////////////////////////
/// \brief Provides an interface for a class to store internal state of some values, for example
///        to log them in a file afterwards.
///
///        See each method documentation to understand the full behavior.
///////////////////////////////////////////////////////////////////////////////////////////
class AbstractLogObject
{
public:
	///////////////////////////////////////////////////////////////////////////////////////
	/// \brief Constructor, set the name of the object.
	/// \details Each instance of a class that is derived from this Abstract class will have
	///          a name that is used to identify it in the column headers.
	///
	/// \param[in] name: name of the instance of the class.
	///////////////////////////////////////////////////////////////////////////////////////
	explicit AbstractLogObject(std::string const& name);



	///////////////////////////////////////////////////////////////////////////////////////
	/// \brief format the column headers for each values that have to be logged
	/// \details For each value that has been registered using registerValue(),
	///          it will append in the header string "prefix.name.field\t".
	///          It should be called successively on the same string.
	///			 Then it will be recursive on each complex objects of the descendant class.
	///          A derived class can reimplement it to perform custom operations.
	///
	/// \param[out] header: the resulting header, tab separated values.
	/// \param[in] prefix: the prefix that would be printed before each values to log.
	/// (Caution : prefix can be "", but if not it has to finish with a dot "." !)
	///////////////////////////////////////////////////////////////////////////////////////
	virtual const void formatHeader(std::string &header, std::string const& prefix);

	///////////////////////////////////////////////////////////////////////////////////////
	/// \brief   Get the current values of each data that has been registered using addField()
	///			AND that has to be printed
	///
	/// \details For each value that has been registered using addField(),
	///			 AND THAT HAS TO BE PRINTED
	///          it will append in the vector the current value of the data.
	///          The current value is changed only after logValue() has been called.
	///          A derived class can reimplement it to perform custom operations.
	///
	/// \param[out] values: the values to log.
	///////////////////////////////////////////////////////////////////////////////////////
	virtual void getCurrentValues(std::vector<int>& values);

	///////////////////////////////////////////////////////////////////////////////////////
	/// \brief   call the getCurrentValues method for each attributes
	///
	/// \param[out] values: the values to log.
	///////////////////////////////////////////////////////////////////////////////////////
	virtual void getCurrentAttributesValues(std::vector<int>& values);

	///////////////////////////////////////////////////////////////////////////////////////
	/// \brief   Run a simulation step of the simulator.
	///
	/// \details
	///          Each derived class must call this method at each step of the simulation.
	///          Basically it should update attributes of the class and then log the new values
	///          of these attributes using logValue().
	///			 If this method isn't redefine, it will just call the method computeAttributes
	///
	/// \param[in] timeMs: The current simulation step, in milliseconds.
	///////////////////////////////////////////////////////////////////////////////////////
	virtual void compute(int const timeMs);

	///////////////////////////////////////////////////////////////////////////////////////
	/// \brief   Run a simulation step of the simulator.
	///
	/// \details It is called to compute the attributes of the class.
	///			 It is called during the compute method.
	///
	/// \param[in] timeMs: The current simulation step, in milliseconds.
	///////////////////////////////////////////////////////////////////////////////////////
	virtual void computeAttributes(int const timeMs);

	///////////////////////////////////////////////////////////////////////////////////////
	/// \brief   Initialise the maps isToLog_ and optional_ in fonction of the option.
	///
	/// \details It is called by the main with the chosen option.
	///
	/// \param[in] option: the option chosen
	///////////////////////////////////////////////////////////////////////////////////////
	virtual void initialiseIsToLog(int const option);




protected:
	///////////////////////////////////////////////////////////////////////////////////////
	/// \brief   Register a name of a variable to be logged.
	///
	/// \details Store the unique name of the value so that it can be logged.
	///
	/// \param[in] name: The name of the variable to register.
	///////////////////////////////////////////////////////////////////////////////////////
	void registerValue(std::string const& name, bool isOptional);

	///////////////////////////////////////////////////////////////////////////////////////
	/// \brief   Update the value of a variable to log
	///
	/// \details This should be called at each simulation step, if not the same value
	///          will be logged each time.
	///
	/// \param[in] name: The name of the value to register.
	///////////////////////////////////////////////////////////////////////////////////////
	void logValue(std::string const& field, int const value);

	virtual ~AbstractLogObject();

private:
	std::set<std::string> headers_;  ///< List of the headers of the variables to log.
	std::map<std::string, int> values_;  ///< Current values of the variables to log.


protected:
	std::string const name_;  ///< Name of the object.
	std::set<AbstractLogObject*> complexObects_ ;  ///< Complex objects from
																/// the descendant class.
	std::map<std::string, bool> optional_;	///< True if the variables are optional.
	std::map<std::string, bool> isToLog_;	///< True if the values must be log.
				/// For this variable, the value for a key not optional is necessary 'True'.
				/// So it was not necessary to set the value for all the variables,
				/// but I prefer inform for all the variables in order to check only in this map.
};

#endif /* ABSTRACTLOGOBJECT_H_ */

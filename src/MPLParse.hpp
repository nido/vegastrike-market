#ifndef H_MPLPARSE
#define H_MPLPARSE

#include <fstream>
#include <vector>

#include "CargoType.hpp"

/** Class for parsing the Master Part List
 */
class MPLParse {
public:
  /** Create a Master Part List parses for the master part list on the
   * default location
   */
  MPLParse();

  /** Copy another parser
   * @param that the MPLParse to copy
   */
  MPLParse(const MPLParse& that);

  /** Create a MPLParse for a certain file
   * @param fileName the file to parse
   */
  MPLParse(std::string fileName);

  /** Regular deconstructor
   */
  ~MPLParse();

  /** Parse all CargoTypes from the Master Part List and put them in a
   * vector to return
   * @return vector of all CargoType in the Master Part List
   */
  std::vector<CargoType> Parse();

  /** Assign that MPLParse to this one
   * @param that the MPLParse to copy
   * @return reference to this MPLParse
   */
  MPLParse& operator=(const MPLParse& that);

  /**Parse a string into a CargoType
   * @param line a line of XML code containing a CargoType
   * @return a pointer to the CargoType represented by the XML, NULL
   * when no such CargoType can be constructed
   */
  static CargoType* ParseLine(std::string line);

  /** Parse a file into a Cargo Type Vector
   * @param fileName the path of the file to parse
   * @return vector of CargoTypes defined in said file
   */
  static std::vector<CargoType> ParseFile(std::string fileName);

private:
  /** Initialises the ifstream bases on the filename given */
  void initStream();

  /** The name of the file to parse */
  std::string filename;

  /** Datastructure representing file input */
  std::ifstream file;
};

#endif //H_MPLPARSE

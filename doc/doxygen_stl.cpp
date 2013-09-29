/** Definitions for Doxygen so it knows of STL stuff and make proper diagrams.
 */
namespace std {
  /*! STL vector class */
  template<class T> class vector { public: T element; };

  template<class K, class V> class map { public: K key; V value; };

}

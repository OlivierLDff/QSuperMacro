/**
 * \file QQmlHelpersCommon.h
 * \brief Common define for every properties macros
 */

#ifndef QQMLHELPERSCOMMON_H
#define QQMLHELPERSCOMMON_H

#include <QtGlobal>

#include <QSuperMacros.h>

/**
 * \defgroup QQML_HELPER_COMMON Common
 * \brief Macros to generate Getter/Setter/Signals/Attribute in Qt or non Qt naming convention
 */

QSUPER_MACROS_NAMESPACE_START

// NOTE : SFINAE trickery to find which type is the cheapest between T and const T &

/** SFINAE trickery to find which type is the cheapest between T and const T & */
template<typename T> struct CheapestType          { typedef const T & type_def; };
/** SFINAE trickery to find which type is the cheapest between T and const T & */
template<>           struct CheapestType<bool>    { typedef bool      type_def; };
/** SFINAE trickery to find which type is the cheapest between T and const T & */
template<>           struct CheapestType<quint8>  { typedef quint8    type_def; };
/** SFINAE trickery to find which type is the cheapest between T and const T & */
template<>           struct CheapestType<quint16> { typedef quint16   type_def; };
/** SFINAE trickery to find which type is the cheapest between T and const T & */
template<>           struct CheapestType<quint32> { typedef quint32   type_def; };
/** SFINAE trickery to find which type is the cheapest between T and const T & */
template<>           struct CheapestType<quint64> { typedef quint64   type_def; };
/** SFINAE trickery to find which type is the cheapest between T and const T & */
template<>           struct CheapestType<qint8>   { typedef qint8     type_def; };
/** SFINAE trickery to find which type is the cheapest between T and const T & */
template<>           struct CheapestType<qint16>  { typedef qint16    type_def; };
/** SFINAE trickery to find which type is the cheapest between T and const T & */
template<>           struct CheapestType<qint32>  { typedef qint32    type_def; };
/** SFINAE trickery to find which type is the cheapest between T and const T & */
template<>           struct CheapestType<qint64>  { typedef qint64    type_def; };
/** SFINAE trickery to find which type is the cheapest between T and const T & */
template<>           struct CheapestType<float>   { typedef float     type_def; };
/** SFINAE trickery to find which type is the cheapest between T and const T & */
template<>           struct CheapestType<double>  { typedef double    type_def; };
/** SFINAE trickery to find which type is the cheapest between T and const T & */
template<typename T> struct CheapestType<T *>     { typedef T *       type_def; };

// NOTE : Functions declaration Trick

/** 
 * \def QSM_MAKE_ATTRIBUTE_NAME(name, Name) 
 * \ingroup QQML_HELPER_COMMON
 * \hideinitializer
 * \brief 
 * * Create an attribute in the Qt-ish form `m_<name>` if `QSUPER_MACROS_USE_QT_PREFIX` is set
 * * Otherwise create an attribute in the form `_<name>`
 * \param name Attribute name in lowerCamelCase
 * \param Name Attribute name in UpperCamelCase
 */
#ifdef QSUPER_MACROS_USE_QT_PREFIX
#	define QSM_MAKE_ATTRIBUTE_NAME(name, Name) m_##name
#else
#	define QSM_MAKE_ATTRIBUTE_NAME(name, Name) _##name
#endif

/** 
 * \def QSM_MAKE_GETTER_NAME(name, Name) 
 * \brief 
 * * Use the Qt-ish Getter Name convention `<name>` if `QSUPER_MACROS_USE_QT_GETTERS` is defined by build system
 * * Use the Getter Name convention `Get<Name>` if `QSUPER_MACROS_USE_QT_GETTERS` is not defined
 * \ingroup QQML_HELPER_COMMON
 * \hideinitializer
 * \param name Attribute name in lowerCamelCase
 * \param Name Attribute name in UpperCamelCase
 */
#ifdef QSUPER_MACROS_USE_QT_GETTERS
#   define QSM_MAKE_GETTER_NAME(name, Name) name
#else
#   define QSM_MAKE_GETTER_NAME(name, Name) Get##Name
#endif

/** 
 * \def QSM_MAKE_SETTER_NAME(name, Name) 
 * \ingroup QQML_HELPER_COMMON
 * \hideinitializer
 * \brief 
 * * Create an Setter in the Qt-ish form `set<Name>` if `QSUPER_MACROS_USE_QT_SETTERS` is set
 * * Otherwise create an attribute in the form `Set<Name>`
 * \param name Attribute name in lowerCamelCase
 * \param Name Attribute name in UpperCamelCase
 */
#ifdef QSUPER_MACROS_USE_QT_SETTERS
#   define QSM_MAKE_SETTER_NAME(name, Name) set##Name
#else
#   define QSM_MAKE_SETTER_NAME(name, Name) Set##Name
#endif

/** 
 * \def QSM_MAKE_SIGNAL_NAME(name, Name) 
 * \ingroup QQML_HELPER_COMMON
 * \hideinitializer
 * \brief 
 * * Create an Signal in the Qt-ish form `<name>Changed` if `QSUPER_MACROS_USE_QT_SETTERS` is set
 * * Otherwise create an attribute in the form `<Name>Changed`
 * \param name Attribute name in lowerCamelCase
 * \param Name Attribute name in UpperCamelCase
 * \note It isn't recommended to use this because QML Connection don't 
 * handle C++ signal starting with capital letter
 */
#ifdef QSUPER_MACROS_USE_QT_SIGNALS
#   define QSM_MAKE_SIGNAL_NAME(name, Name) name##Changed
#else
#   define QSM_MAKE_SIGNAL_NAME(name, Name) Name##Changed
#endif

/** 
 * \def QSM_MAKE_RESET_NAME(name, Name) 
 * \ingroup QQML_HELPER_COMMON
 * \hideinitializer
 * \brief Create a reset function name in the qt naming convention `resetName` if `QSUPER_MACROS_USE_QT_RESET` is set
 * or non qt `ResetName`
 * \param name Attribute name in lowerCamelCase
 * \param Name Attribute name in UpperCamelCase
 */
#ifdef QSUPER_MACROS_USE_QT_RESETS
#   define QSM_MAKE_RESET_NAME(name, Name) reset##Name
#else
#   define QSM_MAKE_RESET_NAME(name, Name) Reset##Name
#endif

/**
 * \def QSM_REGISTER_OBJ_TO_QML_WITH_NAME(Type) 
 * \ingroup QQML_HELPER_COMMON
 * \hideinitializer
 * \brief Create a function to easily register a QObject to the qml system
 * \param Type Class Name
 * 
 * To use this macro simply call it into your QObject derived class
 * \code
 * class MyQObject : public QObject
 * {
 *     Q_OBJECT
 *     QSM_REGISTER_OBJ_TO_QML_WITH_NAME(MyQObject)
 * };
 * \endcode
 * Then to register the class :
 * \code
 * // Regular Naming convetion
 * MyQObject::RegisterToQml("MyUri", 1, 0, "MyQObjectQmlName");
 * \endcode
 *    
 */
#define QSM_REGISTER_OBJ_TO_QML_WITH_NAME(Type) \
public: \
	static void RegisterToQml(const char * uri, const int majorVersion, const int minorVersion, const char * name) { \
			qmlRegisterType<Type>(uri, majorVersion, minorVersion, name); \
	} \
private:

 /**
  * \def QSM_REGISTER_OBJ_TO_QML_NO_NAME(Type)
  * \ingroup QQML_HELPER_COMMON
  * \hideinitializer
  * \brief Create a function to easily register a QObject to the qml system
  * \param Type Class Name
  *
  * To use this macro simply call it into your QObject derived class
  * \code
  * class MyQObject : public QObject
  * {
  *     Q_OBJECT
  *     QSM_REGISTER_OBJ_TO_QML_NO_NAME(MyQObject)
  * };
  * \endcode
  * Then to register the class :
  * \code
  * // Regular Naming convetion
  * MyQObject::RegisterToQml("MyUri", 1, 0);
  * \endcode
  *
  */
#define QSM_REGISTER_OBJ_TO_QML_NO_NAME(Type) \
public: \
	static void RegisterToQml(const char * uri, const int majorVersion, const int minorVersion) { \
			qmlRegisterType<Type>(uri, majorVersion, minorVersion, #Type ); \
	} \
private:

  /**
   * \def QSM_REGISTER_OBJ_TO_QML(Type)
   * \ingroup QQML_HELPER_COMMON
   * \hideinitializer
   * \brief Create a function to easily register a QObject to the qml system
   * \param Type Class Name
   *
   * To use this macro simply call it into your QObject derived class
   * \code
   * class MyQObject : public QObject
   * {
   *     Q_OBJECT
   *     QSM_REGISTER_OBJ_TO_QML(MyQObject)
   * };
   * \endcode
   * Then to register the class :
   * \code
   * // Regular Naming convetion
   * MyQObject::RegisterToQml("MyUri", 1, 0);
   * // or
   * MyQObject::RegisterToQml("MyUri", 1, 0, "MyQObjectQmlName");
   * \endcode
   *
   */
#define QSM_REGISTER_OBJ_TO_QML(Type) \
	QSM_REGISTER_OBJ_TO_QML_WITH_NAME(Type); \
	QSM_REGISTER_OBJ_TO_QML_NO_NAME(Type)\
private:

QSUPER_MACROS_NAMESPACE_END

#endif // QQMLHELPERSCOMMON_H

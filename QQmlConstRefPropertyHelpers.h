#ifndef QQMLCONSTREFPROPERTYHELPERS
#define QQMLCONSTREFPROPERTYHELPERS
#include <QObject>

#define QML_WRITABLE_CSTREF_PROPERTY(type, name) \
    protected: \
        Q_PROPERTY (type name READ get_##name WRITE set_##name NOTIFY name##Changed) \
    private: \
        type m_##name; \
    public: \
        const type & get_##name (void) const { \
            return m_##name ; \
        } \
    public Q_SLOTS: \
        bool set_##name (const type & name) { \
            bool ret = false; \
            if ((ret = m_##name != name)) { \
                m_##name = name; \
                emit name##Changed (m_##name); \
            } \
            return ret; \
        } \
    Q_SIGNALS: \
        void name##Changed (const type & name); \
    private:

#define QML_READONLY_CSTREF_PROPERTY(type, name) \
    protected: \
        Q_PROPERTY (type name READ get_##name NOTIFY name##Changed) \
    private: \
        type m_##name; \
    public: \
        const type & get_##name (void) const { \
            return m_##name ; \
        } \
        bool update_##name (const type & name) { \
            bool ret = false; \
            if ((ret = m_##name != name)) { \
                m_##name = name; \
                emit name##Changed (m_##name); \
            } \
            return ret; \
        } \
    Q_SIGNALS: \
        void name##Changed (const type & name); \
    private:

#define QML_CONSTANT_CSTREF_PROPERTY(type, name) \
    protected: \
        Q_PROPERTY (type name READ get_##name CONSTANT) \
    private: \
        type m_##name; \
    public: \
        const type & get_##name (void) const { \
            return m_##name ; \
        } \
    private:

class _QmlCstRefProperty_ : public QObject {
    Q_OBJECT
    QML_WRITABLE_CSTREF_PROPERTY (int,     var1)
    QML_READONLY_CSTREF_PROPERTY (bool,    var2)
    QML_CONSTANT_CSTREF_PROPERTY (QString, var3)
};

#endif // QQMLCONSTREFPROPERTYHELPERS
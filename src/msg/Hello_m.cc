//
// Generated file, do not edit! Created by nedtool 5.6 from Hello.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include "Hello_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

namespace {
template <class T> inline
typename std::enable_if<std::is_polymorphic<T>::value && std::is_base_of<omnetpp::cObject,T>::value, void *>::type
toVoidPtr(T* t)
{
    return (void *)(static_cast<const omnetpp::cObject *>(t));
}

template <class T> inline
typename std::enable_if<std::is_polymorphic<T>::value && !std::is_base_of<omnetpp::cObject,T>::value, void *>::type
toVoidPtr(T* t)
{
    return (void *)dynamic_cast<const void *>(t);
}

template <class T> inline
typename std::enable_if<!std::is_polymorphic<T>::value, void *>::type
toVoidPtr(T* t)
{
    return (void *)static_cast<const void *>(t);
}

}

namespace inet {

// forward
template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec);

// Template rule to generate operator<< for shared_ptr<T>
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const std::shared_ptr<T>& t) { return out << t.get(); }

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// operator<< for std::vector<T>
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');

    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

EXECUTE_ON_STARTUP(
    omnetpp::cEnum *e = omnetpp::cEnum::find("inet::NodeStatus");
    if (!e) omnetpp::enums.getInstance()->add(e = new omnetpp::cEnum("inet::NodeStatus"));
    e->insert(UNLABELED, "UNLABELED");
    e->insert(LABELED, "LABELED");
)

EXECUTE_ON_STARTUP(
    omnetpp::cEnum *e = omnetpp::cEnum::find("inet::HelloMessageType");
    if (!e) omnetpp::enums.getInstance()->add(e = new omnetpp::cEnum("inet::HelloMessageType"));
    e->insert(REQ, "REQ");
    e->insert(REP, "REP");
)

Register_Class(Hello)

Hello::Hello() : ::inet::FieldsChunk()
{
    this->setChunkLength(B(54));

}

Hello::Hello(const Hello& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

Hello::~Hello()
{
}

Hello& Hello::operator=(const Hello& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void Hello::copy(const Hello& other)
{
    for (size_t i = 0; i < 20; i++) {
        this->label[i] = other.label[i];
    }
    this->type = other.type;
    this->status = other.status;
    this->srcMacAddress = other.srcMacAddress;
    this->destMacAddress = other.destMacAddress;
    this->x = other.x;
    this->y = other.y;
}

void Hello::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimArrayPacking(b,this->label,20);
    doParsimPacking(b,this->type);
    doParsimPacking(b,this->status);
    doParsimPacking(b,this->srcMacAddress);
    doParsimPacking(b,this->destMacAddress);
    doParsimPacking(b,this->x);
    doParsimPacking(b,this->y);
}

void Hello::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimArrayUnpacking(b,this->label,20);
    doParsimUnpacking(b,this->type);
    doParsimUnpacking(b,this->status);
    doParsimUnpacking(b,this->srcMacAddress);
    doParsimUnpacking(b,this->destMacAddress);
    doParsimUnpacking(b,this->x);
    doParsimUnpacking(b,this->y);
}

size_t Hello::getLabelArraySize() const
{
    return 20;
}

const char * Hello::getLabel(size_t k) const
{
    if (k >= 20) throw omnetpp::cRuntimeError("Array of size 20 indexed by %lu", (unsigned long)k);
    return this->label[k].c_str();
}

void Hello::setLabel(size_t k, const char * label)
{
    if (k >= 20) throw omnetpp::cRuntimeError("Array of size 20 indexed by %lu", (unsigned long)k);
    handleChange();
    this->label[k] = label;
}

inet::HelloMessageType Hello::getType() const
{
    return this->type;
}

void Hello::setType(inet::HelloMessageType type)
{
    handleChange();
    this->type = type;
}

inet::NodeStatus Hello::getStatus() const
{
    return this->status;
}

void Hello::setStatus(inet::NodeStatus status)
{
    handleChange();
    this->status = status;
}

const MacAddress& Hello::getSrcMacAddress() const
{
    return this->srcMacAddress;
}

void Hello::setSrcMacAddress(const MacAddress& srcMacAddress)
{
    handleChange();
    this->srcMacAddress = srcMacAddress;
}

const MacAddress& Hello::getDestMacAddress() const
{
    return this->destMacAddress;
}

void Hello::setDestMacAddress(const MacAddress& destMacAddress)
{
    handleChange();
    this->destMacAddress = destMacAddress;
}

double Hello::getX() const
{
    return this->x;
}

void Hello::setX(double x)
{
    handleChange();
    this->x = x;
}

double Hello::getY() const
{
    return this->y;
}

void Hello::setY(double y)
{
    handleChange();
    this->y = y;
}

class HelloDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_label,
        FIELD_type,
        FIELD_status,
        FIELD_srcMacAddress,
        FIELD_destMacAddress,
        FIELD_x,
        FIELD_y,
    };
  public:
    HelloDescriptor();
    virtual ~HelloDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(HelloDescriptor)

HelloDescriptor::HelloDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Hello)), "inet::FieldsChunk")
{
    propertynames = nullptr;
}

HelloDescriptor::~HelloDescriptor()
{
    delete[] propertynames;
}

bool HelloDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Hello *>(obj)!=nullptr;
}

const char **HelloDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *HelloDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int HelloDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 7+basedesc->getFieldCount() : 7;
}

unsigned int HelloDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISEDITABLE,    // FIELD_label
        FD_ISEDITABLE,    // FIELD_type
        FD_ISEDITABLE,    // FIELD_status
        0,    // FIELD_srcMacAddress
        0,    // FIELD_destMacAddress
        FD_ISEDITABLE,    // FIELD_x
        FD_ISEDITABLE,    // FIELD_y
    };
    return (field >= 0 && field < 7) ? fieldTypeFlags[field] : 0;
}

const char *HelloDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "label",
        "type",
        "status",
        "srcMacAddress",
        "destMacAddress",
        "x",
        "y",
    };
    return (field >= 0 && field < 7) ? fieldNames[field] : nullptr;
}

int HelloDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'l' && strcmp(fieldName, "label") == 0) return base+0;
    if (fieldName[0] == 't' && strcmp(fieldName, "type") == 0) return base+1;
    if (fieldName[0] == 's' && strcmp(fieldName, "status") == 0) return base+2;
    if (fieldName[0] == 's' && strcmp(fieldName, "srcMacAddress") == 0) return base+3;
    if (fieldName[0] == 'd' && strcmp(fieldName, "destMacAddress") == 0) return base+4;
    if (fieldName[0] == 'x' && strcmp(fieldName, "x") == 0) return base+5;
    if (fieldName[0] == 'y' && strcmp(fieldName, "y") == 0) return base+6;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *HelloDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_label
        "inet::HelloMessageType",    // FIELD_type
        "inet::NodeStatus",    // FIELD_status
        "inet::MacAddress",    // FIELD_srcMacAddress
        "inet::MacAddress",    // FIELD_destMacAddress
        "double",    // FIELD_x
        "double",    // FIELD_y
    };
    return (field >= 0 && field < 7) ? fieldTypeStrings[field] : nullptr;
}

const char **HelloDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case FIELD_type: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        case FIELD_status: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *HelloDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case FIELD_type:
            if (!strcmp(propertyname, "enum")) return "inet::HelloMessageType";
            return nullptr;
        case FIELD_status:
            if (!strcmp(propertyname, "enum")) return "inet::NodeStatus";
            return nullptr;
        default: return nullptr;
    }
}

int HelloDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    Hello *pp = (Hello *)object; (void)pp;
    switch (field) {
        case FIELD_label: return 20;
        default: return 0;
    }
}

const char *HelloDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Hello *pp = (Hello *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string HelloDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Hello *pp = (Hello *)object; (void)pp;
    switch (field) {
        case FIELD_label: return oppstring2string(pp->getLabel(i));
        case FIELD_type: return enum2string(pp->getType(), "inet::HelloMessageType");
        case FIELD_status: return enum2string(pp->getStatus(), "inet::NodeStatus");
        case FIELD_srcMacAddress: return pp->getSrcMacAddress().str();
        case FIELD_destMacAddress: return pp->getDestMacAddress().str();
        case FIELD_x: return double2string(pp->getX());
        case FIELD_y: return double2string(pp->getY());
        default: return "";
    }
}

bool HelloDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    Hello *pp = (Hello *)object; (void)pp;
    switch (field) {
        case FIELD_label: pp->setLabel(i,(value)); return true;
        case FIELD_type: pp->setType((inet::HelloMessageType)string2enum(value, "inet::HelloMessageType")); return true;
        case FIELD_status: pp->setStatus((inet::NodeStatus)string2enum(value, "inet::NodeStatus")); return true;
        case FIELD_x: pp->setX(string2double(value)); return true;
        case FIELD_y: pp->setY(string2double(value)); return true;
        default: return false;
    }
}

const char *HelloDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *HelloDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    Hello *pp = (Hello *)object; (void)pp;
    switch (field) {
        case FIELD_srcMacAddress: return toVoidPtr(&pp->getSrcMacAddress()); break;
        case FIELD_destMacAddress: return toVoidPtr(&pp->getDestMacAddress()); break;
        default: return nullptr;
    }
}

} // namespace inet


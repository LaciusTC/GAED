//
// Generated file, do not edit! Created by nedtool 5.6 from LabelerPacket.msg.
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
#include "LabelerPacket_m.h"

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
    omnetpp::cEnum *e = omnetpp::cEnum::find("inet::LabelerPacketType");
    if (!e) omnetpp::enums.getInstance()->add(e = new omnetpp::cEnum("inet::LabelerPacketType"));
    e->insert(REQ, "REQ");
    e->insert(OTHER, "OTHER");
)

EXECUTE_ON_STARTUP(
    omnetpp::cEnum *e = omnetpp::cEnum::find("inet::NodeStatus");
    if (!e) omnetpp::enums.getInstance()->add(e = new omnetpp::cEnum("inet::NodeStatus"));
    e->insert(UNKNOWN, "UNKNOWN");
    e->insert(LABELED, "LABELED");
    e->insert(UNLABELED, "UNLABELED");
)

Register_Class(LabelerPacket)

LabelerPacket::LabelerPacket() : ::inet::FieldsChunk()
{
    this->setChunkLength(B(56));

}

LabelerPacket::LabelerPacket(const LabelerPacket& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

LabelerPacket::~LabelerPacket()
{
}

LabelerPacket& LabelerPacket::operator=(const LabelerPacket& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void LabelerPacket::copy(const LabelerPacket& other)
{
    this->src = other.src;
    this->dest = other.dest;
    this->type = other.type;
    this->status = other.status;
    this->seqNumber = other.seqNumber;
    this->ttl = other.ttl;
}

void LabelerPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->src);
    doParsimPacking(b,this->dest);
    doParsimPacking(b,this->type);
    doParsimPacking(b,this->status);
    doParsimPacking(b,this->seqNumber);
    doParsimPacking(b,this->ttl);
}

void LabelerPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->src);
    doParsimUnpacking(b,this->dest);
    doParsimUnpacking(b,this->type);
    doParsimUnpacking(b,this->status);
    doParsimUnpacking(b,this->seqNumber);
    doParsimUnpacking(b,this->ttl);
}

const L3Address& LabelerPacket::getSrc() const
{
    return this->src;
}

void LabelerPacket::setSrc(const L3Address& src)
{
    handleChange();
    this->src = src;
}

const L3Address& LabelerPacket::getDest() const
{
    return this->dest;
}

void LabelerPacket::setDest(const L3Address& dest)
{
    handleChange();
    this->dest = dest;
}

inet::LabelerPacketType LabelerPacket::getType() const
{
    return this->type;
}

void LabelerPacket::setType(inet::LabelerPacketType type)
{
    handleChange();
    this->type = type;
}

inet::NodeStatus LabelerPacket::getStatus() const
{
    return this->status;
}

void LabelerPacket::setStatus(inet::NodeStatus status)
{
    handleChange();
    this->status = status;
}

long LabelerPacket::getSeqNumber() const
{
    return this->seqNumber;
}

void LabelerPacket::setSeqNumber(long seqNumber)
{
    handleChange();
    this->seqNumber = seqNumber;
}

long LabelerPacket::getTtl() const
{
    return this->ttl;
}

void LabelerPacket::setTtl(long ttl)
{
    handleChange();
    this->ttl = ttl;
}

class LabelerPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_src,
        FIELD_dest,
        FIELD_type,
        FIELD_status,
        FIELD_seqNumber,
        FIELD_ttl,
    };
  public:
    LabelerPacketDescriptor();
    virtual ~LabelerPacketDescriptor();

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

Register_ClassDescriptor(LabelerPacketDescriptor)

LabelerPacketDescriptor::LabelerPacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::LabelerPacket)), "inet::FieldsChunk")
{
    propertynames = nullptr;
}

LabelerPacketDescriptor::~LabelerPacketDescriptor()
{
    delete[] propertynames;
}

bool LabelerPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<LabelerPacket *>(obj)!=nullptr;
}

const char **LabelerPacketDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *LabelerPacketDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int LabelerPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 6+basedesc->getFieldCount() : 6;
}

unsigned int LabelerPacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_src
        0,    // FIELD_dest
        FD_ISEDITABLE,    // FIELD_type
        FD_ISEDITABLE,    // FIELD_status
        FD_ISEDITABLE,    // FIELD_seqNumber
        FD_ISEDITABLE,    // FIELD_ttl
    };
    return (field >= 0 && field < 6) ? fieldTypeFlags[field] : 0;
}

const char *LabelerPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "src",
        "dest",
        "type",
        "status",
        "seqNumber",
        "ttl",
    };
    return (field >= 0 && field < 6) ? fieldNames[field] : nullptr;
}

int LabelerPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 's' && strcmp(fieldName, "src") == 0) return base+0;
    if (fieldName[0] == 'd' && strcmp(fieldName, "dest") == 0) return base+1;
    if (fieldName[0] == 't' && strcmp(fieldName, "type") == 0) return base+2;
    if (fieldName[0] == 's' && strcmp(fieldName, "status") == 0) return base+3;
    if (fieldName[0] == 's' && strcmp(fieldName, "seqNumber") == 0) return base+4;
    if (fieldName[0] == 't' && strcmp(fieldName, "ttl") == 0) return base+5;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *LabelerPacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::L3Address",    // FIELD_src
        "inet::L3Address",    // FIELD_dest
        "inet::LabelerPacketType",    // FIELD_type
        "inet::NodeStatus",    // FIELD_status
        "long",    // FIELD_seqNumber
        "long",    // FIELD_ttl
    };
    return (field >= 0 && field < 6) ? fieldTypeStrings[field] : nullptr;
}

const char **LabelerPacketDescriptor::getFieldPropertyNames(int field) const
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

const char *LabelerPacketDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case FIELD_type:
            if (!strcmp(propertyname, "enum")) return "inet::LabelerPacketType";
            return nullptr;
        case FIELD_status:
            if (!strcmp(propertyname, "enum")) return "inet::NodeStatus";
            return nullptr;
        default: return nullptr;
    }
}

int LabelerPacketDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    LabelerPacket *pp = (LabelerPacket *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *LabelerPacketDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    LabelerPacket *pp = (LabelerPacket *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string LabelerPacketDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    LabelerPacket *pp = (LabelerPacket *)object; (void)pp;
    switch (field) {
        case FIELD_src: return pp->getSrc().str();
        case FIELD_dest: return pp->getDest().str();
        case FIELD_type: return enum2string(pp->getType(), "inet::LabelerPacketType");
        case FIELD_status: return enum2string(pp->getStatus(), "inet::NodeStatus");
        case FIELD_seqNumber: return long2string(pp->getSeqNumber());
        case FIELD_ttl: return long2string(pp->getTtl());
        default: return "";
    }
}

bool LabelerPacketDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    LabelerPacket *pp = (LabelerPacket *)object; (void)pp;
    switch (field) {
        case FIELD_type: pp->setType((inet::LabelerPacketType)string2enum(value, "inet::LabelerPacketType")); return true;
        case FIELD_status: pp->setStatus((inet::NodeStatus)string2enum(value, "inet::NodeStatus")); return true;
        case FIELD_seqNumber: pp->setSeqNumber(string2long(value)); return true;
        case FIELD_ttl: pp->setTtl(string2long(value)); return true;
        default: return false;
    }
}

const char *LabelerPacketDescriptor::getFieldStructName(int field) const
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

void *LabelerPacketDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    LabelerPacket *pp = (LabelerPacket *)object; (void)pp;
    switch (field) {
        case FIELD_src: return toVoidPtr(&pp->getSrc()); break;
        case FIELD_dest: return toVoidPtr(&pp->getDest()); break;
        default: return nullptr;
    }
}

} // namespace inet


//
// Generated file, do not edit! Created by nedtool 5.1 from veins/modules/application/icarnew/messages/ICMessage.msg.
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
#include "ICMessage_m.h"

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
    for (int i=0; i<n; i++) {
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
    for (int i=0; i<n; i++) {
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
    for (int i=0; i<n; i++) {
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


// forward
template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec);

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

Register_Class(ICMessage)

ICMessage::ICMessage(const char *name, short kind) : ::WaveShortMessage(name,kind)
{
    this->numMsg = 0;
    this->msgType = 0;
    this->sourceId = 0;
    this->destinationId = 0;
    this->antecessorId = 0;
    this->nextId = 0;
    this->sourceX = 0;
    this->sourceY = 0;
    this->sourceZ = 0;
    this->antecessorX = 0;
    this->antecessorY = 0;
    this->antecessorZ = 0;
    this->nextX = 0;
    this->nextY = 0;
    this->nextZ = 0;
    this->destinationX = 0;
    this->destinationY = 0;
    this->destinationZ = 0;
    this->sourceMaxSpeed = 0;
    this->antecessorMaxSpeed = 0;
    this->nextMaxSpeed = 0;
    this->destinationMaxSpeed = 0;
    this->sourceAngle = 0;
    this->antecessorAngle = 0;
    this->nextAngle = 0;
    this->destinationAngle = 0;
    this->sourceAceleration = 0;
    this->antecessorAceleration = 0;
    this->nextAceleration = 0;
    this->destinationAceleration = 0;
    this->sourceSpeed = 0;
    this->antecessorSpeed = 0;
    this->nextSpeed = 0;
    this->destinationSpeed = 0;
    this->anteNextValidityTimeStamp = 0;
    this->sourceMsgTimeStamp = 0;
    this->antecessorMsgTimeStamp = 0;
    this->msgLifeTime = 0;
    this->AntecessoPosTimeStamp = 0;
    this->SourcePosTimeStamp = 0;
    this->nextPosTimeStamp = 0;
    this->destinationPosTimeStamp = 0;
    this->validityDataTimeStamp = 0;
    this->hopNumber = 0;
}

ICMessage::ICMessage(const ICMessage& other) : ::WaveShortMessage(other)
{
    copy(other);
}

ICMessage::~ICMessage()
{
}

ICMessage& ICMessage::operator=(const ICMessage& other)
{
    if (this==&other) return *this;
    ::WaveShortMessage::operator=(other);
    copy(other);
    return *this;
}

void ICMessage::copy(const ICMessage& other)
{
    this->numMsg = other.numMsg;
    this->msgType = other.msgType;
    this->sourceId = other.sourceId;
    this->destinationId = other.destinationId;
    this->antecessorId = other.antecessorId;
    this->nextId = other.nextId;
    this->sourceX = other.sourceX;
    this->sourceY = other.sourceY;
    this->sourceZ = other.sourceZ;
    this->antecessorX = other.antecessorX;
    this->antecessorY = other.antecessorY;
    this->antecessorZ = other.antecessorZ;
    this->nextX = other.nextX;
    this->nextY = other.nextY;
    this->nextZ = other.nextZ;
    this->destinationX = other.destinationX;
    this->destinationY = other.destinationY;
    this->destinationZ = other.destinationZ;
    this->sourceMaxSpeed = other.sourceMaxSpeed;
    this->antecessorMaxSpeed = other.antecessorMaxSpeed;
    this->nextMaxSpeed = other.nextMaxSpeed;
    this->destinationMaxSpeed = other.destinationMaxSpeed;
    this->sourceAngle = other.sourceAngle;
    this->antecessorAngle = other.antecessorAngle;
    this->nextAngle = other.nextAngle;
    this->destinationAngle = other.destinationAngle;
    this->sourceAceleration = other.sourceAceleration;
    this->antecessorAceleration = other.antecessorAceleration;
    this->nextAceleration = other.nextAceleration;
    this->destinationAceleration = other.destinationAceleration;
    this->sourceSpeed = other.sourceSpeed;
    this->antecessorSpeed = other.antecessorSpeed;
    this->nextSpeed = other.nextSpeed;
    this->destinationSpeed = other.destinationSpeed;
    this->anteNextValidityTimeStamp = other.anteNextValidityTimeStamp;
    this->sourceMsgTimeStamp = other.sourceMsgTimeStamp;
    this->antecessorMsgTimeStamp = other.antecessorMsgTimeStamp;
    this->msgLifeTime = other.msgLifeTime;
    this->AntecessoPosTimeStamp = other.AntecessoPosTimeStamp;
    this->SourcePosTimeStamp = other.SourcePosTimeStamp;
    this->nextPosTimeStamp = other.nextPosTimeStamp;
    this->destinationPosTimeStamp = other.destinationPosTimeStamp;
    this->validityDataTimeStamp = other.validityDataTimeStamp;
    this->hopNumber = other.hopNumber;
}

void ICMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::WaveShortMessage::parsimPack(b);
    doParsimPacking(b,this->numMsg);
    doParsimPacking(b,this->msgType);
    doParsimPacking(b,this->sourceId);
    doParsimPacking(b,this->destinationId);
    doParsimPacking(b,this->antecessorId);
    doParsimPacking(b,this->nextId);
    doParsimPacking(b,this->sourceX);
    doParsimPacking(b,this->sourceY);
    doParsimPacking(b,this->sourceZ);
    doParsimPacking(b,this->antecessorX);
    doParsimPacking(b,this->antecessorY);
    doParsimPacking(b,this->antecessorZ);
    doParsimPacking(b,this->nextX);
    doParsimPacking(b,this->nextY);
    doParsimPacking(b,this->nextZ);
    doParsimPacking(b,this->destinationX);
    doParsimPacking(b,this->destinationY);
    doParsimPacking(b,this->destinationZ);
    doParsimPacking(b,this->sourceMaxSpeed);
    doParsimPacking(b,this->antecessorMaxSpeed);
    doParsimPacking(b,this->nextMaxSpeed);
    doParsimPacking(b,this->destinationMaxSpeed);
    doParsimPacking(b,this->sourceAngle);
    doParsimPacking(b,this->antecessorAngle);
    doParsimPacking(b,this->nextAngle);
    doParsimPacking(b,this->destinationAngle);
    doParsimPacking(b,this->sourceAceleration);
    doParsimPacking(b,this->antecessorAceleration);
    doParsimPacking(b,this->nextAceleration);
    doParsimPacking(b,this->destinationAceleration);
    doParsimPacking(b,this->sourceSpeed);
    doParsimPacking(b,this->antecessorSpeed);
    doParsimPacking(b,this->nextSpeed);
    doParsimPacking(b,this->destinationSpeed);
    doParsimPacking(b,this->anteNextValidityTimeStamp);
    doParsimPacking(b,this->sourceMsgTimeStamp);
    doParsimPacking(b,this->antecessorMsgTimeStamp);
    doParsimPacking(b,this->msgLifeTime);
    doParsimPacking(b,this->AntecessoPosTimeStamp);
    doParsimPacking(b,this->SourcePosTimeStamp);
    doParsimPacking(b,this->nextPosTimeStamp);
    doParsimPacking(b,this->destinationPosTimeStamp);
    doParsimPacking(b,this->validityDataTimeStamp);
    doParsimPacking(b,this->hopNumber);
}

void ICMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::WaveShortMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->numMsg);
    doParsimUnpacking(b,this->msgType);
    doParsimUnpacking(b,this->sourceId);
    doParsimUnpacking(b,this->destinationId);
    doParsimUnpacking(b,this->antecessorId);
    doParsimUnpacking(b,this->nextId);
    doParsimUnpacking(b,this->sourceX);
    doParsimUnpacking(b,this->sourceY);
    doParsimUnpacking(b,this->sourceZ);
    doParsimUnpacking(b,this->antecessorX);
    doParsimUnpacking(b,this->antecessorY);
    doParsimUnpacking(b,this->antecessorZ);
    doParsimUnpacking(b,this->nextX);
    doParsimUnpacking(b,this->nextY);
    doParsimUnpacking(b,this->nextZ);
    doParsimUnpacking(b,this->destinationX);
    doParsimUnpacking(b,this->destinationY);
    doParsimUnpacking(b,this->destinationZ);
    doParsimUnpacking(b,this->sourceMaxSpeed);
    doParsimUnpacking(b,this->antecessorMaxSpeed);
    doParsimUnpacking(b,this->nextMaxSpeed);
    doParsimUnpacking(b,this->destinationMaxSpeed);
    doParsimUnpacking(b,this->sourceAngle);
    doParsimUnpacking(b,this->antecessorAngle);
    doParsimUnpacking(b,this->nextAngle);
    doParsimUnpacking(b,this->destinationAngle);
    doParsimUnpacking(b,this->sourceAceleration);
    doParsimUnpacking(b,this->antecessorAceleration);
    doParsimUnpacking(b,this->nextAceleration);
    doParsimUnpacking(b,this->destinationAceleration);
    doParsimUnpacking(b,this->sourceSpeed);
    doParsimUnpacking(b,this->antecessorSpeed);
    doParsimUnpacking(b,this->nextSpeed);
    doParsimUnpacking(b,this->destinationSpeed);
    doParsimUnpacking(b,this->anteNextValidityTimeStamp);
    doParsimUnpacking(b,this->sourceMsgTimeStamp);
    doParsimUnpacking(b,this->antecessorMsgTimeStamp);
    doParsimUnpacking(b,this->msgLifeTime);
    doParsimUnpacking(b,this->AntecessoPosTimeStamp);
    doParsimUnpacking(b,this->SourcePosTimeStamp);
    doParsimUnpacking(b,this->nextPosTimeStamp);
    doParsimUnpacking(b,this->destinationPosTimeStamp);
    doParsimUnpacking(b,this->validityDataTimeStamp);
    doParsimUnpacking(b,this->hopNumber);
}

unsigned long ICMessage::getNumMsg() const
{
    return this->numMsg;
}

void ICMessage::setNumMsg(unsigned long numMsg)
{
    this->numMsg = numMsg;
}

unsigned int ICMessage::getMsgType() const
{
    return this->msgType;
}

void ICMessage::setMsgType(unsigned int msgType)
{
    this->msgType = msgType;
}

long ICMessage::getSourceId() const
{
    return this->sourceId;
}

void ICMessage::setSourceId(long sourceId)
{
    this->sourceId = sourceId;
}

long ICMessage::getDestinationId() const
{
    return this->destinationId;
}

void ICMessage::setDestinationId(long destinationId)
{
    this->destinationId = destinationId;
}

long ICMessage::getAntecessorId() const
{
    return this->antecessorId;
}

void ICMessage::setAntecessorId(long antecessorId)
{
    this->antecessorId = antecessorId;
}

long ICMessage::getNextId() const
{
    return this->nextId;
}

void ICMessage::setNextId(long nextId)
{
    this->nextId = nextId;
}

float ICMessage::getSourceX() const
{
    return this->sourceX;
}

void ICMessage::setSourceX(float sourceX)
{
    this->sourceX = sourceX;
}

float ICMessage::getSourceY() const
{
    return this->sourceY;
}

void ICMessage::setSourceY(float sourceY)
{
    this->sourceY = sourceY;
}

float ICMessage::getSourceZ() const
{
    return this->sourceZ;
}

void ICMessage::setSourceZ(float sourceZ)
{
    this->sourceZ = sourceZ;
}

float ICMessage::getAntecessorX() const
{
    return this->antecessorX;
}

void ICMessage::setAntecessorX(float antecessorX)
{
    this->antecessorX = antecessorX;
}

float ICMessage::getAntecessorY() const
{
    return this->antecessorY;
}

void ICMessage::setAntecessorY(float antecessorY)
{
    this->antecessorY = antecessorY;
}

float ICMessage::getAntecessorZ() const
{
    return this->antecessorZ;
}

void ICMessage::setAntecessorZ(float antecessorZ)
{
    this->antecessorZ = antecessorZ;
}

float ICMessage::getNextX() const
{
    return this->nextX;
}

void ICMessage::setNextX(float nextX)
{
    this->nextX = nextX;
}

float ICMessage::getNextY() const
{
    return this->nextY;
}

void ICMessage::setNextY(float nextY)
{
    this->nextY = nextY;
}

float ICMessage::getNextZ() const
{
    return this->nextZ;
}

void ICMessage::setNextZ(float nextZ)
{
    this->nextZ = nextZ;
}

float ICMessage::getDestinationX() const
{
    return this->destinationX;
}

void ICMessage::setDestinationX(float destinationX)
{
    this->destinationX = destinationX;
}

float ICMessage::getDestinationY() const
{
    return this->destinationY;
}

void ICMessage::setDestinationY(float destinationY)
{
    this->destinationY = destinationY;
}

float ICMessage::getDestinationZ() const
{
    return this->destinationZ;
}

void ICMessage::setDestinationZ(float destinationZ)
{
    this->destinationZ = destinationZ;
}

float ICMessage::getSourceMaxSpeed() const
{
    return this->sourceMaxSpeed;
}

void ICMessage::setSourceMaxSpeed(float sourceMaxSpeed)
{
    this->sourceMaxSpeed = sourceMaxSpeed;
}

float ICMessage::getAntecessorMaxSpeed() const
{
    return this->antecessorMaxSpeed;
}

void ICMessage::setAntecessorMaxSpeed(float antecessorMaxSpeed)
{
    this->antecessorMaxSpeed = antecessorMaxSpeed;
}

float ICMessage::getNextMaxSpeed() const
{
    return this->nextMaxSpeed;
}

void ICMessage::setNextMaxSpeed(float nextMaxSpeed)
{
    this->nextMaxSpeed = nextMaxSpeed;
}

float ICMessage::getDestinationMaxSpeed() const
{
    return this->destinationMaxSpeed;
}

void ICMessage::setDestinationMaxSpeed(float destinationMaxSpeed)
{
    this->destinationMaxSpeed = destinationMaxSpeed;
}

float ICMessage::getSourceAngle() const
{
    return this->sourceAngle;
}

void ICMessage::setSourceAngle(float sourceAngle)
{
    this->sourceAngle = sourceAngle;
}

float ICMessage::getAntecessorAngle() const
{
    return this->antecessorAngle;
}

void ICMessage::setAntecessorAngle(float antecessorAngle)
{
    this->antecessorAngle = antecessorAngle;
}

float ICMessage::getNextAngle() const
{
    return this->nextAngle;
}

void ICMessage::setNextAngle(float nextAngle)
{
    this->nextAngle = nextAngle;
}

float ICMessage::getDestinationAngle() const
{
    return this->destinationAngle;
}

void ICMessage::setDestinationAngle(float destinationAngle)
{
    this->destinationAngle = destinationAngle;
}

float ICMessage::getSourceAceleration() const
{
    return this->sourceAceleration;
}

void ICMessage::setSourceAceleration(float sourceAceleration)
{
    this->sourceAceleration = sourceAceleration;
}

float ICMessage::getAntecessorAceleration() const
{
    return this->antecessorAceleration;
}

void ICMessage::setAntecessorAceleration(float antecessorAceleration)
{
    this->antecessorAceleration = antecessorAceleration;
}

float ICMessage::getNextAceleration() const
{
    return this->nextAceleration;
}

void ICMessage::setNextAceleration(float nextAceleration)
{
    this->nextAceleration = nextAceleration;
}

float ICMessage::getDestinationAceleration() const
{
    return this->destinationAceleration;
}

void ICMessage::setDestinationAceleration(float destinationAceleration)
{
    this->destinationAceleration = destinationAceleration;
}

float ICMessage::getSourceSpeed() const
{
    return this->sourceSpeed;
}

void ICMessage::setSourceSpeed(float sourceSpeed)
{
    this->sourceSpeed = sourceSpeed;
}

float ICMessage::getAntecessorSpeed() const
{
    return this->antecessorSpeed;
}

void ICMessage::setAntecessorSpeed(float antecessorSpeed)
{
    this->antecessorSpeed = antecessorSpeed;
}

float ICMessage::getNextSpeed() const
{
    return this->nextSpeed;
}

void ICMessage::setNextSpeed(float nextSpeed)
{
    this->nextSpeed = nextSpeed;
}

float ICMessage::getDestinationSpeed() const
{
    return this->destinationSpeed;
}

void ICMessage::setDestinationSpeed(float destinationSpeed)
{
    this->destinationSpeed = destinationSpeed;
}

::omnetpp::simtime_t ICMessage::getAnteNextValidityTimeStamp() const
{
    return this->anteNextValidityTimeStamp;
}

void ICMessage::setAnteNextValidityTimeStamp(::omnetpp::simtime_t anteNextValidityTimeStamp)
{
    this->anteNextValidityTimeStamp = anteNextValidityTimeStamp;
}

::omnetpp::simtime_t ICMessage::getSourceMsgTimeStamp() const
{
    return this->sourceMsgTimeStamp;
}

void ICMessage::setSourceMsgTimeStamp(::omnetpp::simtime_t sourceMsgTimeStamp)
{
    this->sourceMsgTimeStamp = sourceMsgTimeStamp;
}

::omnetpp::simtime_t ICMessage::getAntecessorMsgTimeStamp() const
{
    return this->antecessorMsgTimeStamp;
}

void ICMessage::setAntecessorMsgTimeStamp(::omnetpp::simtime_t antecessorMsgTimeStamp)
{
    this->antecessorMsgTimeStamp = antecessorMsgTimeStamp;
}

::omnetpp::simtime_t ICMessage::getMsgLifeTime() const
{
    return this->msgLifeTime;
}

void ICMessage::setMsgLifeTime(::omnetpp::simtime_t msgLifeTime)
{
    this->msgLifeTime = msgLifeTime;
}

::omnetpp::simtime_t ICMessage::getAntecessoPosTimeStamp() const
{
    return this->AntecessoPosTimeStamp;
}

void ICMessage::setAntecessoPosTimeStamp(::omnetpp::simtime_t AntecessoPosTimeStamp)
{
    this->AntecessoPosTimeStamp = AntecessoPosTimeStamp;
}

::omnetpp::simtime_t ICMessage::getSourcePosTimeStamp() const
{
    return this->SourcePosTimeStamp;
}

void ICMessage::setSourcePosTimeStamp(::omnetpp::simtime_t SourcePosTimeStamp)
{
    this->SourcePosTimeStamp = SourcePosTimeStamp;
}

::omnetpp::simtime_t ICMessage::getNextPosTimeStamp() const
{
    return this->nextPosTimeStamp;
}

void ICMessage::setNextPosTimeStamp(::omnetpp::simtime_t nextPosTimeStamp)
{
    this->nextPosTimeStamp = nextPosTimeStamp;
}

::omnetpp::simtime_t ICMessage::getDestinationPosTimeStamp() const
{
    return this->destinationPosTimeStamp;
}

void ICMessage::setDestinationPosTimeStamp(::omnetpp::simtime_t destinationPosTimeStamp)
{
    this->destinationPosTimeStamp = destinationPosTimeStamp;
}

::omnetpp::simtime_t ICMessage::getValidityDataTimeStamp() const
{
    return this->validityDataTimeStamp;
}

void ICMessage::setValidityDataTimeStamp(::omnetpp::simtime_t validityDataTimeStamp)
{
    this->validityDataTimeStamp = validityDataTimeStamp;
}

unsigned int ICMessage::getHopNumber() const
{
    return this->hopNumber;
}

void ICMessage::setHopNumber(unsigned int hopNumber)
{
    this->hopNumber = hopNumber;
}

class ICMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    ICMessageDescriptor();
    virtual ~ICMessageDescriptor();

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

Register_ClassDescriptor(ICMessageDescriptor)

ICMessageDescriptor::ICMessageDescriptor() : omnetpp::cClassDescriptor("ICMessage", "WaveShortMessage")
{
    propertynames = nullptr;
}

ICMessageDescriptor::~ICMessageDescriptor()
{
    delete[] propertynames;
}

bool ICMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<ICMessage *>(obj)!=nullptr;
}

const char **ICMessageDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *ICMessageDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int ICMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 44+basedesc->getFieldCount() : 44;
}

unsigned int ICMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<44) ? fieldTypeFlags[field] : 0;
}

const char *ICMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "numMsg",
        "msgType",
        "sourceId",
        "destinationId",
        "antecessorId",
        "nextId",
        "sourceX",
        "sourceY",
        "sourceZ",
        "antecessorX",
        "antecessorY",
        "antecessorZ",
        "nextX",
        "nextY",
        "nextZ",
        "destinationX",
        "destinationY",
        "destinationZ",
        "sourceMaxSpeed",
        "antecessorMaxSpeed",
        "nextMaxSpeed",
        "destinationMaxSpeed",
        "sourceAngle",
        "antecessorAngle",
        "nextAngle",
        "destinationAngle",
        "sourceAceleration",
        "antecessorAceleration",
        "nextAceleration",
        "destinationAceleration",
        "sourceSpeed",
        "antecessorSpeed",
        "nextSpeed",
        "destinationSpeed",
        "anteNextValidityTimeStamp",
        "sourceMsgTimeStamp",
        "antecessorMsgTimeStamp",
        "msgLifeTime",
        "AntecessoPosTimeStamp",
        "SourcePosTimeStamp",
        "nextPosTimeStamp",
        "destinationPosTimeStamp",
        "validityDataTimeStamp",
        "hopNumber",
    };
    return (field>=0 && field<44) ? fieldNames[field] : nullptr;
}

int ICMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='n' && strcmp(fieldName, "numMsg")==0) return base+0;
    if (fieldName[0]=='m' && strcmp(fieldName, "msgType")==0) return base+1;
    if (fieldName[0]=='s' && strcmp(fieldName, "sourceId")==0) return base+2;
    if (fieldName[0]=='d' && strcmp(fieldName, "destinationId")==0) return base+3;
    if (fieldName[0]=='a' && strcmp(fieldName, "antecessorId")==0) return base+4;
    if (fieldName[0]=='n' && strcmp(fieldName, "nextId")==0) return base+5;
    if (fieldName[0]=='s' && strcmp(fieldName, "sourceX")==0) return base+6;
    if (fieldName[0]=='s' && strcmp(fieldName, "sourceY")==0) return base+7;
    if (fieldName[0]=='s' && strcmp(fieldName, "sourceZ")==0) return base+8;
    if (fieldName[0]=='a' && strcmp(fieldName, "antecessorX")==0) return base+9;
    if (fieldName[0]=='a' && strcmp(fieldName, "antecessorY")==0) return base+10;
    if (fieldName[0]=='a' && strcmp(fieldName, "antecessorZ")==0) return base+11;
    if (fieldName[0]=='n' && strcmp(fieldName, "nextX")==0) return base+12;
    if (fieldName[0]=='n' && strcmp(fieldName, "nextY")==0) return base+13;
    if (fieldName[0]=='n' && strcmp(fieldName, "nextZ")==0) return base+14;
    if (fieldName[0]=='d' && strcmp(fieldName, "destinationX")==0) return base+15;
    if (fieldName[0]=='d' && strcmp(fieldName, "destinationY")==0) return base+16;
    if (fieldName[0]=='d' && strcmp(fieldName, "destinationZ")==0) return base+17;
    if (fieldName[0]=='s' && strcmp(fieldName, "sourceMaxSpeed")==0) return base+18;
    if (fieldName[0]=='a' && strcmp(fieldName, "antecessorMaxSpeed")==0) return base+19;
    if (fieldName[0]=='n' && strcmp(fieldName, "nextMaxSpeed")==0) return base+20;
    if (fieldName[0]=='d' && strcmp(fieldName, "destinationMaxSpeed")==0) return base+21;
    if (fieldName[0]=='s' && strcmp(fieldName, "sourceAngle")==0) return base+22;
    if (fieldName[0]=='a' && strcmp(fieldName, "antecessorAngle")==0) return base+23;
    if (fieldName[0]=='n' && strcmp(fieldName, "nextAngle")==0) return base+24;
    if (fieldName[0]=='d' && strcmp(fieldName, "destinationAngle")==0) return base+25;
    if (fieldName[0]=='s' && strcmp(fieldName, "sourceAceleration")==0) return base+26;
    if (fieldName[0]=='a' && strcmp(fieldName, "antecessorAceleration")==0) return base+27;
    if (fieldName[0]=='n' && strcmp(fieldName, "nextAceleration")==0) return base+28;
    if (fieldName[0]=='d' && strcmp(fieldName, "destinationAceleration")==0) return base+29;
    if (fieldName[0]=='s' && strcmp(fieldName, "sourceSpeed")==0) return base+30;
    if (fieldName[0]=='a' && strcmp(fieldName, "antecessorSpeed")==0) return base+31;
    if (fieldName[0]=='n' && strcmp(fieldName, "nextSpeed")==0) return base+32;
    if (fieldName[0]=='d' && strcmp(fieldName, "destinationSpeed")==0) return base+33;
    if (fieldName[0]=='a' && strcmp(fieldName, "anteNextValidityTimeStamp")==0) return base+34;
    if (fieldName[0]=='s' && strcmp(fieldName, "sourceMsgTimeStamp")==0) return base+35;
    if (fieldName[0]=='a' && strcmp(fieldName, "antecessorMsgTimeStamp")==0) return base+36;
    if (fieldName[0]=='m' && strcmp(fieldName, "msgLifeTime")==0) return base+37;
    if (fieldName[0]=='A' && strcmp(fieldName, "AntecessoPosTimeStamp")==0) return base+38;
    if (fieldName[0]=='S' && strcmp(fieldName, "SourcePosTimeStamp")==0) return base+39;
    if (fieldName[0]=='n' && strcmp(fieldName, "nextPosTimeStamp")==0) return base+40;
    if (fieldName[0]=='d' && strcmp(fieldName, "destinationPosTimeStamp")==0) return base+41;
    if (fieldName[0]=='v' && strcmp(fieldName, "validityDataTimeStamp")==0) return base+42;
    if (fieldName[0]=='h' && strcmp(fieldName, "hopNumber")==0) return base+43;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *ICMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned long",
        "unsigned int",
        "long",
        "long",
        "long",
        "long",
        "float",
        "float",
        "float",
        "float",
        "float",
        "float",
        "float",
        "float",
        "float",
        "float",
        "float",
        "float",
        "float",
        "float",
        "float",
        "float",
        "float",
        "float",
        "float",
        "float",
        "float",
        "float",
        "float",
        "float",
        "float",
        "float",
        "float",
        "float",
        "simtime_t",
        "simtime_t",
        "simtime_t",
        "simtime_t",
        "simtime_t",
        "simtime_t",
        "simtime_t",
        "simtime_t",
        "simtime_t",
        "unsigned int",
    };
    return (field>=0 && field<44) ? fieldTypeStrings[field] : nullptr;
}

const char **ICMessageDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *ICMessageDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int ICMessageDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    ICMessage *pp = (ICMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *ICMessageDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    ICMessage *pp = (ICMessage *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string ICMessageDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    ICMessage *pp = (ICMessage *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getNumMsg());
        case 1: return ulong2string(pp->getMsgType());
        case 2: return long2string(pp->getSourceId());
        case 3: return long2string(pp->getDestinationId());
        case 4: return long2string(pp->getAntecessorId());
        case 5: return long2string(pp->getNextId());
        case 6: return double2string(pp->getSourceX());
        case 7: return double2string(pp->getSourceY());
        case 8: return double2string(pp->getSourceZ());
        case 9: return double2string(pp->getAntecessorX());
        case 10: return double2string(pp->getAntecessorY());
        case 11: return double2string(pp->getAntecessorZ());
        case 12: return double2string(pp->getNextX());
        case 13: return double2string(pp->getNextY());
        case 14: return double2string(pp->getNextZ());
        case 15: return double2string(pp->getDestinationX());
        case 16: return double2string(pp->getDestinationY());
        case 17: return double2string(pp->getDestinationZ());
        case 18: return double2string(pp->getSourceMaxSpeed());
        case 19: return double2string(pp->getAntecessorMaxSpeed());
        case 20: return double2string(pp->getNextMaxSpeed());
        case 21: return double2string(pp->getDestinationMaxSpeed());
        case 22: return double2string(pp->getSourceAngle());
        case 23: return double2string(pp->getAntecessorAngle());
        case 24: return double2string(pp->getNextAngle());
        case 25: return double2string(pp->getDestinationAngle());
        case 26: return double2string(pp->getSourceAceleration());
        case 27: return double2string(pp->getAntecessorAceleration());
        case 28: return double2string(pp->getNextAceleration());
        case 29: return double2string(pp->getDestinationAceleration());
        case 30: return double2string(pp->getSourceSpeed());
        case 31: return double2string(pp->getAntecessorSpeed());
        case 32: return double2string(pp->getNextSpeed());
        case 33: return double2string(pp->getDestinationSpeed());
        case 34: return simtime2string(pp->getAnteNextValidityTimeStamp());
        case 35: return simtime2string(pp->getSourceMsgTimeStamp());
        case 36: return simtime2string(pp->getAntecessorMsgTimeStamp());
        case 37: return simtime2string(pp->getMsgLifeTime());
        case 38: return simtime2string(pp->getAntecessoPosTimeStamp());
        case 39: return simtime2string(pp->getSourcePosTimeStamp());
        case 40: return simtime2string(pp->getNextPosTimeStamp());
        case 41: return simtime2string(pp->getDestinationPosTimeStamp());
        case 42: return simtime2string(pp->getValidityDataTimeStamp());
        case 43: return ulong2string(pp->getHopNumber());
        default: return "";
    }
}

bool ICMessageDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    ICMessage *pp = (ICMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setNumMsg(string2ulong(value)); return true;
        case 1: pp->setMsgType(string2ulong(value)); return true;
        case 2: pp->setSourceId(string2long(value)); return true;
        case 3: pp->setDestinationId(string2long(value)); return true;
        case 4: pp->setAntecessorId(string2long(value)); return true;
        case 5: pp->setNextId(string2long(value)); return true;
        case 6: pp->setSourceX(string2double(value)); return true;
        case 7: pp->setSourceY(string2double(value)); return true;
        case 8: pp->setSourceZ(string2double(value)); return true;
        case 9: pp->setAntecessorX(string2double(value)); return true;
        case 10: pp->setAntecessorY(string2double(value)); return true;
        case 11: pp->setAntecessorZ(string2double(value)); return true;
        case 12: pp->setNextX(string2double(value)); return true;
        case 13: pp->setNextY(string2double(value)); return true;
        case 14: pp->setNextZ(string2double(value)); return true;
        case 15: pp->setDestinationX(string2double(value)); return true;
        case 16: pp->setDestinationY(string2double(value)); return true;
        case 17: pp->setDestinationZ(string2double(value)); return true;
        case 18: pp->setSourceMaxSpeed(string2double(value)); return true;
        case 19: pp->setAntecessorMaxSpeed(string2double(value)); return true;
        case 20: pp->setNextMaxSpeed(string2double(value)); return true;
        case 21: pp->setDestinationMaxSpeed(string2double(value)); return true;
        case 22: pp->setSourceAngle(string2double(value)); return true;
        case 23: pp->setAntecessorAngle(string2double(value)); return true;
        case 24: pp->setNextAngle(string2double(value)); return true;
        case 25: pp->setDestinationAngle(string2double(value)); return true;
        case 26: pp->setSourceAceleration(string2double(value)); return true;
        case 27: pp->setAntecessorAceleration(string2double(value)); return true;
        case 28: pp->setNextAceleration(string2double(value)); return true;
        case 29: pp->setDestinationAceleration(string2double(value)); return true;
        case 30: pp->setSourceSpeed(string2double(value)); return true;
        case 31: pp->setAntecessorSpeed(string2double(value)); return true;
        case 32: pp->setNextSpeed(string2double(value)); return true;
        case 33: pp->setDestinationSpeed(string2double(value)); return true;
        case 34: pp->setAnteNextValidityTimeStamp(string2simtime(value)); return true;
        case 35: pp->setSourceMsgTimeStamp(string2simtime(value)); return true;
        case 36: pp->setAntecessorMsgTimeStamp(string2simtime(value)); return true;
        case 37: pp->setMsgLifeTime(string2simtime(value)); return true;
        case 38: pp->setAntecessoPosTimeStamp(string2simtime(value)); return true;
        case 39: pp->setSourcePosTimeStamp(string2simtime(value)); return true;
        case 40: pp->setNextPosTimeStamp(string2simtime(value)); return true;
        case 41: pp->setDestinationPosTimeStamp(string2simtime(value)); return true;
        case 42: pp->setValidityDataTimeStamp(string2simtime(value)); return true;
        case 43: pp->setHopNumber(string2ulong(value)); return true;
        default: return false;
    }
}

const char *ICMessageDescriptor::getFieldStructName(int field) const
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

void *ICMessageDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    ICMessage *pp = (ICMessage *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}



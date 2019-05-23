//
// Generated file, do not edit! Created by nedtool 5.1 from veins/modules/application/icarnew/messages/ChannelMonitor.msg.
//

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#ifndef __CHANNELMONITOR_M_H
#define __CHANNELMONITOR_M_H

#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0501
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



/**
 * Class generated from <tt>veins/modules/application/icarnew/messages/ChannelMonitor.msg:19</tt> by nedtool.
 * <pre>
 * //
 * // TODO generated message class
 * //
 * message ChannelMonitor
 * {
 *     unsigned long source;
 *     unsigned long destination;
 * }
 * </pre>
 */
class ChannelMonitor : public ::omnetpp::cMessage
{
  protected:
    unsigned long source;
    unsigned long destination;

  private:
    void copy(const ChannelMonitor& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const ChannelMonitor&);

  public:
    ChannelMonitor(const char *name=nullptr, short kind=0);
    ChannelMonitor(const ChannelMonitor& other);
    virtual ~ChannelMonitor();
    ChannelMonitor& operator=(const ChannelMonitor& other);
    virtual ChannelMonitor *dup() const override {return new ChannelMonitor(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual unsigned long getSource() const;
    virtual void setSource(unsigned long source);
    virtual unsigned long getDestination() const;
    virtual void setDestination(unsigned long destination);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const ChannelMonitor& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, ChannelMonitor& obj) {obj.parsimUnpack(b);}


#endif // ifndef __CHANNELMONITOR_M_H


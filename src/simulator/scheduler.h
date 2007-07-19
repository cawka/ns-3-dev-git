/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2005 INRIA
 * All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Mathieu Lacage <mathieu.lacage@sophia.inria.fr>
 */

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>
#include "event-id.h"

namespace ns3 {

class EventImpl;

/**
 * \brief Maintain the event list
 *
 * This base class specifies the interface used to maintain the 
 * event list. If you want to provide a new event list scheduler, 
 * you need to create a subclass of this base class and implement 
 * all the private pure virtual methods defined here. Namely:
 *   - ns3::Scheduler::realInsert
 *   - ns3::Scheduler::realIsEmpty
 *   - ns3::Scheduler::realPeekNext
 *   - ns3::Scheduler::realPeekNextKey
 *   - ns3::Scheduler::realRemoveNext
 *   - ns3::Scheduler::realRemove
 *
 * If you need to provide a new event list scheduler without
 * editing the main simulator class, you need to also implement
 * a subclass of the ns3::SchedulerFactory base class and
 * feed it to ns3::Simulator::setExternal.
 * The simplest example of a scheduler is the linked-list
 * scheduler included in ns3: see the files 
 * src/simulator/scheduler-list.h and src/simulator/scheduler-list.cc
 */
class Scheduler {
 public:
  struct EventKey {
      uint64_t m_ts;
      uint32_t m_uid;
  };

  virtual ~Scheduler () = 0;

  void Insert (EventId id);
  bool IsEmpty (void) const;
  EventId PeekNext (void) const;
  void RemoveNext (void);
  bool Remove (EventId);

private:
  /**
   * \param id the event id to store.
   *
   */
  virtual void RealInsert (EventId id) = 0;
  /**
   * \returns true if the event list is empty and false otherwise.
   */
  virtual bool RealIsEmpty (void) const = 0;
  /**
   * \returns a the next earliest event.
   *
   * This method cannot be invoked if the list is empty.
   */
  virtual EventId RealPeekNext (void) const = 0;
  /**
   * This method cannot be invoked if the list is empty.
   * Remove the next earliest event from the event list.
   */
  virtual void RealRemoveNext (void) = 0;
  /**
   * \param id the id of the event to remove
   * \returns true if the event was found and removed
   *          successfully, false otherwise.
   *
   * This methods cannot be invoked if the list is empty.
   */
  virtual bool RealRemove (EventId id) = 0;
};

}; // namespace ns3


#endif /* SCHEDULER_H */

// this is for emacs file handling -*- mode: c++; indent-tabs-mode: nil -*-

// -- BEGIN LICENSE BLOCK ----------------------------------------------
// This file is part of FZIs ic_workspace.
//
// This program is free software licensed under the LGPL
// (GNU LESSER GENERAL PUBLIC LICENSE Version 3).
// You can find a copy of this license in LICENSE folder in the top
// directory of the source code.
//
// © Copyright 2016 FZI Forschungszentrum Informatik, Karlsruhe, Germany
//
// -- END LICENSE BLOCK ------------------------------------------------

//----------------------------------------------------------------------
/*!\file
 *
 * \author  Klaus Uhl <uhl@fzi.de>
 * \date    2009-11-29
 */
//----------------------------------------------------------------------
#include "SemaphoreImplLxrt35.h"

#include <errno.h>

#include "Common.h"

#include <iostream>

namespace icl_core {
namespace thread {

SemaphoreImplLxrt35::SemaphoreImplLxrt35(size_t initial_value)
  : m_semaphore(NULL)
{
  m_semaphore = new sem_t;
  sem_init_rt(m_semaphore, PTHREAD_PROCESS_PRIVATE, initial_value);
}

SemaphoreImplLxrt35::~SemaphoreImplLxrt35()
{
  if (m_semaphore != NULL)
  {
    sem_destroy_rt(m_semaphore);
    delete m_semaphore;
    m_semaphore = 0;
  }
}

void SemaphoreImplLxrt35::post()
{
  sem_post_rt(m_semaphore);
}

bool SemaphoreImplLxrt35::tryWait()
{
  int res = sem_trywait_rt(m_semaphore);
  return (res == 0);
}

bool SemaphoreImplLxrt35::wait()
{
  int res = sem_wait_rt(m_semaphore);
  return (res == 0);
}

bool SemaphoreImplLxrt35::wait(const icl_core::TimeSpan& timeout)
{
  return wait(impl::getAbsoluteTimeout(timeout));
}

bool SemaphoreImplLxrt35::wait(const icl_core::TimeStamp& timeout)
{
  struct timespec timeout_spec = timeout.systemTimespec();
  int res = sem_timedwait_rt(m_semaphore, &timeout_spec);
  return (res == 0);
}

}
}

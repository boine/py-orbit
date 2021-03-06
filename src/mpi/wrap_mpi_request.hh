#ifndef WRAP_ORBIT_MPI_REQUEST_H
#define WRAP_ORBIT_MPI_REQUEST_H

///////////////////////////////////////////////////////////////////////////
//
// This is a wrapper for the MPI_Request data type from MPI
//
///////////////////////////////////////////////////////////////////////////
#include "orbit_mpi.hh"

#ifdef __cplusplus
extern "C" {
#endif

  namespace wrap_orbit_mpi_request{
    void init_orbit_mpi_request(PyObject* module);
  }

#ifdef __cplusplus
}
#endif

///////////////////////////////////////////////////////////////////////////
//
// END OF FILE
//
///////////////////////////////////////////////////////////////////////////

#endif

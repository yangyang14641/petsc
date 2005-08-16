// 
// File:          TOPS_Solver_Structured_Impl.hh
// Symbol:        TOPS.Solver_Structured-v0.0.0
// Symbol Type:   class
// Babel Version: 0.10.8
// Description:   Server-side implementation for TOPS.Solver_Structured
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// babel-version = 0.10.8
// 

#ifndef included_TOPS_Solver_Structured_Impl_hh
#define included_TOPS_Solver_Structured_Impl_hh

#ifndef included_sidl_cxx_hh
#include "sidl_cxx.hh"
#endif
#ifndef included_TOPS_Solver_Structured_IOR_h
#include "TOPS_Solver_Structured_IOR.h"
#endif
// 
// Includes for all method dependencies.
// 
#ifndef included_TOPS_Matrix_hh
#include "TOPS_Matrix.hh"
#endif
#ifndef included_TOPS_Solver_Structured_hh
#include "TOPS_Solver_Structured.hh"
#endif
#ifndef included_TOPS_System_hh
#include "TOPS_System.hh"
#endif
#ifndef included_TOPS_Vector_hh
#include "TOPS_Vector.hh"
#endif
#ifndef included_sidl_BaseInterface_hh
#include "sidl_BaseInterface.hh"
#endif
#ifndef included_sidl_ClassInfo_hh
#include "sidl_ClassInfo.hh"
#endif


// DO-NOT-DELETE splicer.begin(TOPS.Solver_Structured._includes)
#include "petscdmmg.h"
#include "TOPS_SystemComputeResidual.hh"
#include "TOPS_SystemComputeInitialGuess.hh"
#include "TOPS_SystemComputeJacobian.hh"
#include "TOPS_SystemComputeRightHandSide.hh"
// DO-NOT-DELETE splicer.end(TOPS.Solver_Structured._includes)

namespace TOPS { 

  /**
   * Symbol "TOPS.Solver_Structured" (version 0.0.0)
   */
  class Solver_Structured_impl
  // DO-NOT-DELETE splicer.begin(TOPS.Solver_Structured._inherits)
  // Insert-Code-Here {TOPS.Solver_Structured._inherits} (optional inheritance here)
  // DO-NOT-DELETE splicer.end(TOPS.Solver_Structured._inherits)
  {

  private:
    // Pointer back to IOR.
    // Use this to dispatch back through IOR vtable.
    Solver_Structured self;

    // DO-NOT-DELETE splicer.begin(TOPS.Solver_Structured._implementation)
    DMMG           *dmmg;
    DA             da;
    int            M,N,P,m,n,p,dim,s,levels,bs;
    DAStencilType  stencil_type;
    DAPeriodicType wrap;
    TOPS::System   system;
    int            startedpetsc;
    // DO-NOT-DELETE splicer.end(TOPS.Solver_Structured._implementation)

  private:
    // private default constructor (required)
    Solver_Structured_impl() 
    {} 

  public:
    // sidl constructor (required)
    // Note: alternate Skel constructor doesn't call addref()
    // (fixes bug #275)
    Solver_Structured_impl( struct TOPS_Solver_Structured__object * s ) : 
      self(s,true) { _ctor(); }

    // user defined construction
    void _ctor();

    // virtual destructor (required)
    virtual ~Solver_Structured_impl() { _dtor(); }

    // user defined destruction
    void _dtor();

    // static class initializer
    static void _load();

  public:

    /**
     * user defined non-static method.
     */
    void
    Initialize (
      /* in */ ::sidl::array< ::std::string> args
    )
    throw () 
    ;

    /**
     * user defined non-static method.
     */
    void
    setSystem (
      /* in */ ::TOPS::System system
    )
    throw () 
    ;

    /**
     * user defined non-static method.
     */
    ::TOPS::System
    getSystem() throw () 
    ;
    /**
     * user defined non-static method.
     */
    void
    solve() throw () 
    ;
    /**
     * user defined non-static method.
     */
    void
    setBlockSize (
      /* in */ int32_t bs
    )
    throw () 
    ;

    /**
     * user defined non-static method.
     */
    ::TOPS::Vector
    getRightHandSize (
      /* in */ int32_t level
    )
    throw () 
    ;

    /**
     * user defined non-static method.
     */
    ::TOPS::Vector
    getSolution (
      /* in */ int32_t Level
    )
    throw () 
    ;

    /**
     * user defined non-static method.
     */
    void
    getJacobian (
      /* in */ int32_t Level,
      /* out */ ::TOPS::Matrix& J,
      /* out */ ::TOPS::Matrix& B
    )
    throw () 
    ;

    /**
     * user defined non-static method.
     */
    void
    setDimension (
      /* in */ int32_t dim
    )
    throw () 
    ;

    /**
     * user defined non-static method.
     */
    int32_t
    getDimension() throw () 
    ;
    /**
     * user defined non-static method.
     */
    void
    setDimensionX (
      /* in */ int32_t dim
    )
    throw () 
    ;

    /**
     * user defined non-static method.
     */
    int32_t
    getDimensionX() throw () 
    ;
    /**
     * user defined non-static method.
     */
    void
    setDimensionY (
      /* in */ int32_t dim
    )
    throw () 
    ;

    /**
     * user defined non-static method.
     */
    int32_t
    getDimensionY() throw () 
    ;
    /**
     * user defined non-static method.
     */
    void
    setDimensionZ (
      /* in */ int32_t dim
    )
    throw () 
    ;

    /**
     * user defined non-static method.
     */
    int32_t
    getDimensionZ() throw () 
    ;
    /**
     * user defined non-static method.
     */
    void
    setStencilWidth (
      /* in */ int32_t width
    )
    throw () 
    ;

    /**
     * user defined non-static method.
     */
    int32_t
    getStencilWidth() throw () 
    ;
    /**
     * user defined non-static method.
     */
    void
    setLevels (
      /* in */ int32_t levels
    )
    throw () 
    ;

  };  // end class Solver_Structured_impl

} // end namespace TOPS

// DO-NOT-DELETE splicer.begin(TOPS.Solver_Structured._misc)
// Insert-Code-Here {TOPS.Solver_Structured._misc} (miscellaneous things)
// DO-NOT-DELETE splicer.end(TOPS.Solver_Structured._misc)

#endif

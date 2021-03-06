
/*
   This private file should not be included in users' code.
   Defines the fields shared by all vector implementations.

*/

#ifndef __VECIMPL_H
#define __VECIMPL_H

#include <petscvec.h>
#include <petsc/private/petscimpl.h>
#include <petscviewer.h>

PETSC_EXTERN PetscBool VecRegisterAllCalled;
PETSC_EXTERN PetscErrorCode VecRegisterAll(void);

PETSC_EXTERN PetscBool VecScatterRegisterAllCalled;
PETSC_EXTERN PetscErrorCode VecScatterRegisterAll(void);

/* ----------------------------------------------------------------------------*/

typedef struct _VecOps *VecOps;
struct _VecOps {
  PetscErrorCode (*duplicate)(Vec,Vec*);         /* get single vector */
  PetscErrorCode (*duplicatevecs)(Vec,PetscInt,Vec**);     /* get array of vectors */
  PetscErrorCode (*destroyvecs)(PetscInt,Vec[]);           /* free array of vectors */
  PetscErrorCode (*dot)(Vec,Vec,PetscScalar*);             /* z = x^H * y */
  PetscErrorCode (*mdot)(Vec,PetscInt,const Vec[],PetscScalar*); /* z[j] = x dot y[j] */
  PetscErrorCode (*norm)(Vec,NormType,PetscReal*);        /* z = sqrt(x^H * x) */
  PetscErrorCode (*tdot)(Vec,Vec,PetscScalar*);             /* x'*y */
  PetscErrorCode (*mtdot)(Vec,PetscInt,const Vec[],PetscScalar*);/* z[j] = x dot y[j] */
  PetscErrorCode (*scale)(Vec,PetscScalar);                 /* x = alpha * x   */
  PetscErrorCode (*copy)(Vec,Vec);                     /* y = x */
  PetscErrorCode (*set)(Vec,PetscScalar);                        /* y = alpha  */
  PetscErrorCode (*swap)(Vec,Vec);                               /* exchange x and y */
  PetscErrorCode (*axpy)(Vec,PetscScalar,Vec);                   /* y = y + alpha * x */
  PetscErrorCode (*axpby)(Vec,PetscScalar,PetscScalar,Vec);      /* y = alpha * x + beta * y*/
  PetscErrorCode (*maxpy)(Vec,PetscInt,const PetscScalar*,Vec*); /* y = y + alpha[j] x[j] */
  PetscErrorCode (*aypx)(Vec,PetscScalar,Vec);                   /* y = x + alpha * y */
  PetscErrorCode (*waxpy)(Vec,PetscScalar,Vec,Vec);         /* w = y + alpha * x */
  PetscErrorCode (*axpbypcz)(Vec,PetscScalar,PetscScalar,PetscScalar,Vec,Vec);   /* z = alpha * x + beta *y + gamma *z*/
  PetscErrorCode (*pointwisemult)(Vec,Vec,Vec);        /* w = x .* y */
  PetscErrorCode (*pointwisedivide)(Vec,Vec,Vec);      /* w = x ./ y */
  PetscErrorCode (*setvalues)(Vec,PetscInt,const PetscInt[],const PetscScalar[],InsertMode);
  PetscErrorCode (*assemblybegin)(Vec);                /* start global assembly */
  PetscErrorCode (*assemblyend)(Vec);                  /* end global assembly */
  PetscErrorCode (*getarray)(Vec,PetscScalar**);            /* get data array */
  PetscErrorCode (*getsize)(Vec,PetscInt*);
  PetscErrorCode (*getlocalsize)(Vec,PetscInt*);
  PetscErrorCode (*restorearray)(Vec,PetscScalar**);        /* restore data array */
  PetscErrorCode (*max)(Vec,PetscInt*,PetscReal*);      /* z = max(x); idx=index of max(x) */
  PetscErrorCode (*min)(Vec,PetscInt*,PetscReal*);      /* z = min(x); idx=index of min(x) */
  PetscErrorCode (*setrandom)(Vec,PetscRandom);         /* set y[j] = random numbers */
  PetscErrorCode (*setoption)(Vec,VecOption,PetscBool );
  PetscErrorCode (*setvaluesblocked)(Vec,PetscInt,const PetscInt[],const PetscScalar[],InsertMode);
  PetscErrorCode (*destroy)(Vec);
  PetscErrorCode (*view)(Vec,PetscViewer);
  PetscErrorCode (*placearray)(Vec,const PetscScalar*);     /* place data array */
  PetscErrorCode (*replacearray)(Vec,const PetscScalar*);     /* replace data array */
  PetscErrorCode (*dot_local)(Vec,Vec,PetscScalar*);
  PetscErrorCode (*tdot_local)(Vec,Vec,PetscScalar*);
  PetscErrorCode (*norm_local)(Vec,NormType,PetscReal*);
  PetscErrorCode (*mdot_local)(Vec,PetscInt,const Vec[],PetscScalar*);
  PetscErrorCode (*mtdot_local)(Vec,PetscInt,const Vec[],PetscScalar*);
  PetscErrorCode (*load)(Vec,PetscViewer);
  PetscErrorCode (*reciprocal)(Vec);
  PetscErrorCode (*conjugate)(Vec);
  PetscErrorCode (*setlocaltoglobalmapping)(Vec,ISLocalToGlobalMapping);
  PetscErrorCode (*setvalueslocal)(Vec,PetscInt,const PetscInt *,const PetscScalar *,InsertMode);
  PetscErrorCode (*resetarray)(Vec);      /* vector points to its original array, i.e. undoes any VecPlaceArray() */
  PetscErrorCode (*setfromoptions)(PetscOptionItems*,Vec);
  PetscErrorCode (*maxpointwisedivide)(Vec,Vec,PetscReal*);      /* m = max abs(x ./ y) */
  PetscErrorCode (*pointwisemax)(Vec,Vec,Vec);
  PetscErrorCode (*pointwisemaxabs)(Vec,Vec,Vec);
  PetscErrorCode (*pointwisemin)(Vec,Vec,Vec);
  PetscErrorCode (*getvalues)(Vec,PetscInt,const PetscInt[],PetscScalar[]);
  PetscErrorCode (*sqrt)(Vec);
  PetscErrorCode (*abs)(Vec);
  PetscErrorCode (*exp)(Vec);
  PetscErrorCode (*log)(Vec);
  PetscErrorCode (*shift)(Vec,PetscScalar);
  PetscErrorCode (*create)(Vec);
  PetscErrorCode (*stridegather)(Vec,PetscInt,Vec,InsertMode);
  PetscErrorCode (*stridescatter)(Vec,PetscInt,Vec,InsertMode);
  PetscErrorCode (*dotnorm2)(Vec,Vec,PetscScalar*,PetscScalar*);
  PetscErrorCode (*getsubvector)(Vec,IS,Vec*);
  PetscErrorCode (*restoresubvector)(Vec,IS,Vec*);
  PetscErrorCode (*getarrayread)(Vec,const PetscScalar**);
  PetscErrorCode (*restorearrayread)(Vec,const PetscScalar**);
  PetscErrorCode (*stridesubsetgather)(Vec,PetscInt,const PetscInt[],const PetscInt[],Vec,InsertMode);
  PetscErrorCode (*stridesubsetscatter)(Vec,PetscInt,const PetscInt[],const PetscInt[],Vec,InsertMode);
  PetscErrorCode (*viewnative)(Vec,PetscViewer);
  PetscErrorCode (*loadnative)(Vec,PetscViewer);
  PetscErrorCode (*getlocalvector)(Vec,Vec);
  PetscErrorCode (*restorelocalvector)(Vec,Vec);
  PetscErrorCode (*getlocalvectorread)(Vec,Vec);
  PetscErrorCode (*restorelocalvectorread)(Vec,Vec);
};

/*
    The stash is used to temporarily store inserted vec values that
  belong to another processor. During the assembly phase the stashed
  values are moved to the correct processor and
*/

typedef struct {
  PetscInt      nmax;                   /* maximum stash size */
  PetscInt      umax;                   /* max stash size user wants */
  PetscInt      oldnmax;                /* the nmax value used previously */
  PetscInt      n;                      /* stash size */
  PetscInt      bs;                     /* block size of the stash */
  PetscInt      reallocs;               /* preserve the no of mallocs invoked */
  PetscInt      *idx;                   /* global row numbers in stash */
  PetscScalar   *array;                 /* array to hold stashed values */
  /* The following variables are used for communication */
  MPI_Comm      comm;
  PetscMPIInt   size,rank;
  PetscMPIInt   tag1,tag2;
  MPI_Request   *send_waits;            /* array of send requests */
  MPI_Request   *recv_waits;            /* array of receive requests */
  MPI_Status    *send_status;           /* array of send status */
  PetscInt      nsends,nrecvs;          /* numbers of sends and receives */
  PetscScalar   *svalues,*rvalues;      /* sending and receiving data */
  PetscInt      *sindices,*rindices;
  PetscInt      rmax;                   /* maximum message length */
  PetscInt      *nprocs;                /* tmp data used both during scatterbegin and end */
  PetscInt      nprocessed;             /* number of messages already processed */
  PetscBool     donotstash;
  PetscBool     ignorenegidx;           /* ignore negative indices passed into VecSetValues/VetGetValues */
  InsertMode    insertmode;
  PetscInt      *bowners;
} VecStash;

struct _p_Vec {
  PETSCHEADER(struct _VecOps);
  PetscLayout            map;
  void                   *data;     /* implementation-specific data */
  PetscBool              array_gotten;
  VecStash               stash,bstash; /* used for storing off-proc values during assembly */
  PetscBool              petscnative;  /* means the ->data starts with VECHEADER and can use VecGetArrayFast()*/
  PetscInt               lock;   /* vector is locked to read only */
#if defined(PETSC_HAVE_VIENNACL) || defined(PETSC_HAVE_VECCUDA)
  PetscOffloadFlag       valid_GPU_array;    /* indicates where the most recently modified vector data is (GPU or CPU) */
  void                   *spptr; /* this is the special pointer to the array on the GPU */
#endif
};

PETSC_EXTERN PetscLogEvent VEC_SetRandom;
PETSC_EXTERN PetscLogEvent VEC_View;
PETSC_EXTERN PetscLogEvent VEC_Max;
PETSC_EXTERN PetscLogEvent VEC_Min;
PETSC_EXTERN PetscLogEvent VEC_Dot;
PETSC_EXTERN PetscLogEvent VEC_MDot;
PETSC_EXTERN PetscLogEvent VEC_TDot;
PETSC_EXTERN PetscLogEvent VEC_MTDot;
PETSC_EXTERN PetscLogEvent VEC_Norm;
PETSC_EXTERN PetscLogEvent VEC_Normalize;
PETSC_EXTERN PetscLogEvent VEC_Scale;
PETSC_EXTERN PetscLogEvent VEC_Copy;
PETSC_EXTERN PetscLogEvent VEC_Set;
PETSC_EXTERN PetscLogEvent VEC_AXPY;
PETSC_EXTERN PetscLogEvent VEC_AYPX;
PETSC_EXTERN PetscLogEvent VEC_WAXPY;
PETSC_EXTERN PetscLogEvent VEC_MAXPY;
PETSC_EXTERN PetscLogEvent VEC_AssemblyEnd;
PETSC_EXTERN PetscLogEvent VEC_PointwiseMult;
PETSC_EXTERN PetscLogEvent VEC_SetValues;
PETSC_EXTERN PetscLogEvent VEC_Load;
PETSC_EXTERN PetscLogEvent VEC_ScatterBegin;
PETSC_EXTERN PetscLogEvent VEC_ScatterEnd;
PETSC_EXTERN PetscLogEvent VEC_ReduceArithmetic;
PETSC_EXTERN PetscLogEvent VEC_ReduceCommunication;
PETSC_EXTERN PetscLogEvent VEC_ReduceBegin;
PETSC_EXTERN PetscLogEvent VEC_ReduceEnd;
PETSC_EXTERN PetscLogEvent VEC_Swap;
PETSC_EXTERN PetscLogEvent VEC_AssemblyBegin;
PETSC_EXTERN PetscLogEvent VEC_DotNorm2;
PETSC_EXTERN PetscLogEvent VEC_AXPBYPCZ;
PETSC_EXTERN PetscLogEvent VEC_Ops;
PETSC_EXTERN PetscLogEvent VEC_ViennaCLCopyToGPU;
PETSC_EXTERN PetscLogEvent VEC_ViennaCLCopyFromGPU;
PETSC_EXTERN PetscLogEvent VEC_CUDACopyToGPU;
PETSC_EXTERN PetscLogEvent VEC_CUDACopyFromGPU;
PETSC_EXTERN PetscLogEvent VEC_CUDACopyToGPUSome;
PETSC_EXTERN PetscLogEvent VEC_CUDACopyFromGPUSome;

PETSC_EXTERN PetscErrorCode VecView_Seq(Vec,PetscViewer);
#if defined(PETSC_HAVE_VIENNACL)
PETSC_EXTERN PetscErrorCode VecViennaCLAllocateCheckHost(Vec v);
PETSC_EXTERN PetscErrorCode VecViennaCLCopyFromGPU(Vec v);
#endif
#if defined(PETSC_HAVE_VECCUDA)
PETSC_EXTERN PetscErrorCode VecCUDAAllocateCheckHost(Vec v);
PETSC_EXTERN PetscErrorCode VecCUDACopyFromGPU(Vec v);
#endif


/*
     Common header shared by array based vectors,
   currently Vec_Seq and Vec_MPI
*/
#define VECHEADER                          \
  PetscScalar *array;                      \
  PetscScalar *array_allocated;                        /* if the array was allocated by PETSc this is its pointer */  \
  PetscScalar *unplacedarray;                           /* if one called VecPlaceArray(), this is where it stashed the original */

/* Default obtain and release vectors; can be used by any implementation */
PETSC_EXTERN PetscErrorCode VecDuplicateVecs_Default(Vec,PetscInt,Vec *[]);
PETSC_EXTERN PetscErrorCode VecDestroyVecs_Default(PetscInt,Vec []);
PETSC_INTERN PetscErrorCode VecLoad_Binary(Vec, PetscViewer);
PETSC_EXTERN PetscErrorCode VecLoad_Default(Vec, PetscViewer);

PETSC_EXTERN PetscInt  NormIds[7];  /* map from NormType to IDs used to cache/retreive values of norms */

/* --------------------------------------------------------------------*/
/*                                                                     */
/* Defines the data structures used in the Vec Scatter operations      */

typedef enum { VEC_SCATTER_SEQ_GENERAL,VEC_SCATTER_SEQ_STRIDE,
               VEC_SCATTER_MPI_GENERAL,VEC_SCATTER_MPI_TOALL,
               VEC_SCATTER_MPI_TOONE} VecScatterFormat;

#define VECSCATTER_IMPL_HEADER \
      VecScatterFormat format;

typedef struct {
  VECSCATTER_IMPL_HEADER
} VecScatter_Common;

/* A plan to optimize individual memory copies (e.g., pack/unpack to/from send/recv buffers, or local scatters)
   in VecScatter. Currently, a scatter to a neighbor processor may be transformed into 1) multiple (including one)
   contiguous memory copies, e.g., memcpy; OR 2) one strided memory copies.

    For brevity, we call them memory copies. In reality, the optimization applies not only to INSERT_VALUES, but also to ADD_VALUES, etc.
 */
typedef struct {
  PetscInt  n;                /* number of processors */
  PetscBool *optimized;       /* [n] is the scatter to procs[i] optimized? */
  PetscInt  *copy_offsets;    /* [n+1] we number all copies. Scatter to procs[i] is optimized into copies in [copy_offsets[i],copy_offsets[i+1]) */
  PetscInt  *copy_starts;     /* [*] j-th copy starts at index copy_starts[j] of the vector */
  PetscInt  *copy_lengths;    /* [*] with length copy_lengths[j] in bytes */
  PetscInt  *stride_first;    /* [n] if optimized[i] is TRUE but copy_offsets[i] = copy_offsets[i+1], then scatter to procs[i] is strided. The first */
  PetscInt  *stride_step;     /* [n]   index is stride_first[i], step is stride_step[i], */
  PetscInt  *stride_n;        /* [n]   and total stride_n[i] steps */
  PetscBool same_copy_starts; /* used only by VecScatterMemcpyPlanCreate_SGToSG(). If true, to's copy_starts[] values
                                 are as same as from's. Used to quickly test if we are doing a self-copy */
} VecScatterMemcpyPlan;

/*
   These scatters are for the purely local case.
*/
typedef struct {
  VECSCATTER_IMPL_HEADER
  PetscInt       n;                    /* number of components to scatter */
  PetscInt       *vslots;              /* locations of components */
  /*
       The next three fields are used in parallel scatters, they contain
       optimization in the special case that the "to" vector and the "from"
       vector are the same, so one only needs copy components that truly
       copies instead of just y[idx[i]] = y[jdx[i]] where idx[i] == jdx[i].
  */
  PetscBool      nonmatching_computed;
  PetscInt       n_nonmatching;        /* number of "from"s  != "to"s */
  PetscInt       *slots_nonmatching;   /* locations of "from"s  != "to"s */
  VecScatterMemcpyPlan memcpy_plan;    /* a plan to optimize pack/unpack with memcpy */
} VecScatter_Seq_General;

typedef struct {
  VECSCATTER_IMPL_HEADER
  PetscInt       n;
  PetscInt       first;
  PetscInt       step;
} VecScatter_Seq_Stride;

/*
   This scatter is for a global vector copied (completely) to each processor (or all to one)
*/
typedef struct {
  VECSCATTER_IMPL_HEADER
  PetscMPIInt    *count;        /* elements of vector on each processor */
  PetscMPIInt    *displx;
  PetscScalar    *work1;
  PetscScalar    *work2;
} VecScatter_MPI_ToAll;

/*
   This is the general parallel scatter
*/
typedef struct {
  VECSCATTER_IMPL_HEADER
  PetscInt               n;        /* number of processors to send/receive */
  PetscInt               *starts;  /* starting point in indices and values for each proc*/
  PetscInt               *indices; /* list of all components sent or received */
  PetscMPIInt            *procs;   /* processors we are communicating with in scatter */
  VecScatterMemcpyPlan   memcpy_plan; /* a plan to optimize pack/unpack/scatter */
  MPI_Request            *requests,*rev_requests;
  PetscScalar            *values;  /* buffer for all sends or receives */
  VecScatter_Seq_General local;    /* any part that happens to be local */
  MPI_Status             *sstatus,*rstatus;
  PetscBool              use_readyreceiver;
  PetscInt               bs;
  PetscBool              sendfirst;
  PetscBool              contiq;
  /* for MPI_Alltoallv() approach */
  PetscBool              use_alltoallv;
  PetscMPIInt            *counts,*displs;
  /* for MPI_Alltoallw() approach */
  PetscBool              use_alltoallw;
#if defined(PETSC_HAVE_MPI_ALLTOALLW)
  PetscMPIInt            *wcounts,*wdispls;
  MPI_Datatype           *types;
#endif
  PetscBool              use_window;    /* these uses windows for communication across all MPI processes */
#if defined(PETSC_HAVE_MPI_WIN_CREATE_FEATURE)
  MPI_Win                window;
  PetscInt               *winstarts;    /* displacements in the processes I am putting to */
#endif
#if defined(PETSC_HAVE_MPI_WIN_CREATE_FEATURE)      /* these uses windows for communication only within each node */
  PetscMPIInt            msize,sharedcnt;           /* total to entries that are going to processes with the same shared memory space */
  PetscScalar            *sharedspace;              /* space each process puts data to be read from other processes; allocated by MPI */
  PetscScalar            **sharedspaces;            /* [msize] space other processes put data to be read from this processes. */
  PetscInt               *sharedspacesoffset;       /* [msize] offset into sharedspaces, that I will read from */
  PetscInt               *sharedspacestarts;        /* [msize+1] for each shared memory partner this maps to the part of sharedspaceindices of that partner */
  PetscInt               *sharedspaceindices;       /* [] for each shared memory partner contains indices where values are to be copied to */
  MPI_Win                sharedwin;                 /* Window that owns sharedspace */
  PetscInt               notdone;                   /* used by VecScatterEndMPI3Node() */
#endif
} VecScatter_MPI_General;

/* Routines to create, copy, destroy or execute a memcpy plan */

/* Create a memcpy plan based on a list of indices */
PETSC_INTERN PetscErrorCode VecScatterMemcpyPlanCreate_Index(PetscInt,const PetscInt*,const PetscInt*,PetscInt,VecScatterMemcpyPlan*);
/* Create a memcpy plan for a SG (sequential general vector) to SG scatter */
PETSC_INTERN PetscErrorCode VecScatterMemcpyPlanCreate_SGToSG(PetscInt,VecScatter_Seq_General*,VecScatter_Seq_General*);
PETSC_INTERN PetscErrorCode VecScatterMemcpyPlanCopy(const VecScatterMemcpyPlan*,VecScatterMemcpyPlan*);
PETSC_INTERN PetscErrorCode VecScatterMemcpyPlanDestroy(VecScatterMemcpyPlan*);
/* Create/copy/destroy a memcpy plan for a P (parallel vector) to P scatter */
PETSC_INTERN PetscErrorCode VecScatterMemcpyPlanCreate_PtoP(VecScatter_MPI_General*,VecScatter_MPI_General*);
PETSC_INTERN PetscErrorCode VecScatterMemcpyPlanCopy_PtoP(const VecScatter_MPI_General*,const VecScatter_MPI_General*,VecScatter_MPI_General*,VecScatter_MPI_General*);
PETSC_INTERN PetscErrorCode VecScatterMemcpyPlanDestroy_PtoP(VecScatter_MPI_General*,VecScatter_MPI_General*);

/* Pack data from x to y according to the i-th memcpy plan in xplan */
PETSC_STATIC_INLINE PetscErrorCode VecScatterMemcpyPlanExecute_Pack(PetscInt i,const PetscScalar *PETSC_RESTRICT x,const VecScatterMemcpyPlan *xplan,PetscScalar *PETSC_RESTRICT y,InsertMode addv,PetscInt bs)
{
  PetscErrorCode    ierr;
  PetscInt          j,k,len,step,n;
  const PetscScalar *xv;
  PetscBool         strided;

  PetscFunctionBegin;
  strided = (xplan->copy_offsets[i] == xplan->copy_offsets[i+1]) ? PETSC_TRUE : PETSC_FALSE;
  if (strided) {
    xv   = x+xplan->stride_first[i];
    step = xplan->stride_step[i];
    n    = xplan->stride_n[i];
  }

  if (addv == INSERT_VALUES) {
    if (strided) {
      for (j=0; j<n; j++)
        for (k=0; k<bs; k++) y[j*bs+k] = xv[j*step+k];
    } else {
      for (j=xplan->copy_offsets[i]; j<xplan->copy_offsets[i+1]; j++) {
        len  = xplan->copy_lengths[j];
        ierr = PetscMemcpy(y,x+xplan->copy_starts[j],len);CHKERRQ(ierr);
        y    = (PetscScalar*)((PetscChar*)y + len);
      }
    }
  } else if (addv == ADD_VALUES) {
    if (strided) {
      for (j=0; j<n; j++)
        for (k=0; k<bs; k++) y[j*bs+k] += xv[j*step+k];
    } else {
      for (j=xplan->copy_offsets[i]; j<xplan->copy_offsets[i+1]; j++) {
        len  = xplan->copy_lengths[j]/sizeof(PetscScalar);
        xv   = x+xplan->copy_starts[i];
        for (k=0; k<len; k++) y[k] += xv[k];
        y   += len;
      }
    }
  }
#if !defined(PETSC_USE_COMPLEX)
  else if (addv == MAX_VALUES) {
    if (strided) {
      for (j=0; j<n; j++)
        for (k=0; k<bs; k++) y[j*bs+k] = PetscMax(y[j*bs+k],xv[j*step+k]);
    } else {
      for (j=xplan->copy_offsets[i]; j<xplan->copy_offsets[i+1]; j++) {
        len  = xplan->copy_lengths[j]/sizeof(PetscScalar);
        xv   = x+xplan->copy_starts[i];
        for (k=0; k<len; k++) y[k] = PetscMax(y[k],xv[k]);
        y   += len;
      }
    }
  }
#endif
  else {
    SETERRQ1(PETSC_COMM_SELF, PETSC_ERR_ARG_WRONG, "Cannot handle insert mode %d in packing",addv);
  }
  PetscFunctionReturn(0);
}

/* Unpack data from x to y according to the i-th memcpy plan in yplan */
PETSC_STATIC_INLINE PetscErrorCode VecScatterMemcpyPlanExecute_Unpack(PetscInt i,const PetscScalar *PETSC_RESTRICT x,PetscScalar *PETSC_RESTRICT y,const VecScatterMemcpyPlan *yplan,InsertMode addv,PetscInt bs)
{
  PetscErrorCode ierr;
  PetscInt       j,k,len,step,n;
  PetscScalar    *yv;
  PetscBool      strided;

  PetscFunctionBegin;
  strided = (yplan->copy_offsets[i] == yplan->copy_offsets[i+1]) ? PETSC_TRUE : PETSC_FALSE;
  if (strided) {
    yv   = y+yplan->stride_first[i];
    step = yplan->stride_step[i];
    n    = yplan->stride_n[i];
  }

  if (addv == INSERT_VALUES) {
    if (strided) {
      for (j=0; j<n; j++)
        for (k=0; k<bs; k++) yv[j*step+k] = x[j*bs+k];
    } else {
      for (j=yplan->copy_offsets[i]; j<yplan->copy_offsets[i+1]; j++) {
        len  = yplan->copy_lengths[j];
        ierr = PetscMemcpy(y+yplan->copy_starts[j],x,len);CHKERRQ(ierr);
        x    = (PetscScalar*)((PetscChar*)x + len);
      }
    }
  } else if (addv == ADD_VALUES) {
    if (strided) {
      for (j=0; j<n; j++)
        for (k=0; k<bs; k++) yv[j*step+k] += x[j*bs+k];
    } else {
      for (j=yplan->copy_offsets[i]; j<yplan->copy_offsets[i+1]; j++) {
        len  = yplan->copy_lengths[j]/sizeof(PetscScalar);
        yv   = y+yplan->copy_starts[j];
        for (k=0; k<len; k++) yv[k] += x[k];
        x   += len;
      }
    }
  }
#if !defined(PETSC_USE_COMPLEX)
  else if (addv == MAX_VALUES) {
    if (strided) {
      for (j=0; j<n; j++)
        for (k=0; k<bs; k++) yv[j*step+k] = PetscMax(yv[j*step+k],x[j*bs+k]);
    } else {
      for (j=yplan->copy_offsets[i]; j<yplan->copy_offsets[i+1]; j++) {
        len  = yplan->copy_lengths[j]/sizeof(PetscScalar);
        yv   = y+yplan->copy_starts[j];
        for (k=0; k<len; k++) yv[k] = PetscMax(yv[k],x[k]);
        x   += len;
      }
    }
  }
#endif
  else {
    SETERRQ1(PETSC_COMM_SELF, PETSC_ERR_ARG_WRONG, "Cannot handle insert mode %d in unpacking",addv);
  }
  PetscFunctionReturn(0);
}

/* Scatter data from piece-wise contiguous x to (conforming) piece-wise contiguous y according to the i-th memcpy plan in xplan and yplan respectively */
PETSC_STATIC_INLINE PetscErrorCode VecScatterMemcpyPlanExecute_Scatter(PetscInt i,const PetscScalar *PETSC_RESTRICT x,const VecScatterMemcpyPlan *xplan,PetscScalar *PETSC_RESTRICT y,const VecScatterMemcpyPlan *yplan,InsertMode addv)
{
  PetscErrorCode    ierr;
  PetscInt          j,k,len;
  const PetscScalar *xv;
  PetscScalar       *yv;

  PetscFunctionBegin;
  if (addv == INSERT_VALUES) {
    for (j=xplan->copy_offsets[i]; j<xplan->copy_offsets[i+1]; j++) {
      ierr = PetscMemcpy(y+yplan->copy_starts[j],x+xplan->copy_starts[j],xplan->copy_lengths[j]);CHKERRQ(ierr);
    }
  } else if (addv == ADD_VALUES) {
    for (j=xplan->copy_offsets[i]; j<xplan->copy_offsets[i+1]; j++) {
      len = xplan->copy_lengths[j]/sizeof(PetscScalar);
      xv  = x+xplan->copy_starts[j];
      yv  = y+yplan->copy_starts[j];
      for (k=0; k<len; k++) yv[k] += xv[k];
    }
  }
#if !defined(PETSC_USE_COMPLEX)
  else if (addv == MAX_VALUES) {
    for (j=xplan->copy_offsets[i]; j<xplan->copy_offsets[i+1]; j++) {
      len = xplan->copy_lengths[j]/sizeof(PetscScalar);
      xv  = x+xplan->copy_starts[j];
      yv  = y+yplan->copy_starts[j];
      for (k=0; k<len; k++) yv[k] = PetscMax(yv[k],xv[k]);
    }
  }
#endif
  else {
    SETERRQ1(PETSC_COMM_SELF, PETSC_ERR_ARG_WRONG, "Cannot handle insert mode %d in scattering",addv);
  }
  PetscFunctionReturn(0);
}

PETSC_INTERN PetscErrorCode VecScatterGetTypes_Private(VecScatter,VecScatterFormat*,VecScatterFormat*);
PETSC_INTERN PetscErrorCode VecScatterIsSequential_Private(VecScatter_Common*,PetscBool*);

typedef struct _VecScatterOps *VecScatterOps;
struct _VecScatterOps {
  PetscErrorCode (*begin)(VecScatter,Vec,Vec,InsertMode,ScatterMode);
  PetscErrorCode (*end)(VecScatter,Vec,Vec,InsertMode,ScatterMode);
  PetscErrorCode (*copy)(VecScatter,VecScatter);
  PetscErrorCode (*destroy)(VecScatter);
  PetscErrorCode (*view)(VecScatter,PetscViewer);
  PetscErrorCode (*viewfromoptions)(VecScatter,const char prefix[],const char name[]);
  PetscErrorCode (*remap)(VecScatter,PetscInt *,PetscInt*);
  PetscErrorCode (*getmerged)(VecScatter,PetscBool *);
};

struct _p_VecScatter {
  PETSCHEADER(struct _VecScatterOps);
  PetscInt       to_n,from_n;
  PetscBool      inuse;                /* prevents corruption from mixing two scatters */
  PetscBool      beginandendtogether;  /* indicates that the scatter begin and end  function are called together, VecScatterEnd()
                                          is then treated as a nop */
  PetscBool      packtogether;         /* packs all the messages before sending, same with receive */
  PetscBool      reproduce;            /* always receive the ghost points in the same order of processes */
  void           *fromdata,*todata;
  void           *spptr;
  PetscBool      is_duplicate;         /* IS has duplicate indices, would cause writing error in the case StoP of VecScatterEndMPI3Node */
  Vec            to_v,from_v;          /* used in VecScatterCreate() */
  IS             to_is,from_is;        /* used in VecScatterCreate() */
};

PETSC_INTERN PetscErrorCode VecScatterCreate_Seq(VecScatter);
PETSC_INTERN PetscErrorCode VecScatterCreate_MPI1(VecScatter);
PETSC_INTERN PetscErrorCode VecScatterCreate_MPI3(VecScatter);
PETSC_INTERN PetscErrorCode VecScatterCreate_MPI3Node(VecScatter);

PETSC_INTERN PetscErrorCode VecStashCreate_Private(MPI_Comm,PetscInt,VecStash*);
PETSC_INTERN PetscErrorCode VecStashDestroy_Private(VecStash*);
PETSC_EXTERN PetscErrorCode VecStashExpand_Private(VecStash*,PetscInt);
PETSC_INTERN PetscErrorCode VecStashScatterEnd_Private(VecStash*);
PETSC_INTERN PetscErrorCode VecStashSetInitialSize_Private(VecStash*,PetscInt);
PETSC_INTERN PetscErrorCode VecStashGetInfo_Private(VecStash*,PetscInt*,PetscInt*);
PETSC_INTERN PetscErrorCode VecStashScatterBegin_Private(VecStash*,PetscInt*);
PETSC_INTERN PetscErrorCode VecStashScatterGetMesg_Private(VecStash*,PetscMPIInt*,PetscInt**,PetscScalar**,PetscInt*);
PETSC_INTERN PetscErrorCode VecStashSortCompress_Private(VecStash*);
PETSC_INTERN PetscErrorCode VecStashGetOwnerList_Private(VecStash*,PetscLayout,PetscMPIInt*,PetscMPIInt**);

/*
  VecStashValue_Private - inserts a single value into the stash.

  Input Parameters:
  stash  - the stash
  idx    - the global of the inserted value
  values - the value inserted
*/
PETSC_STATIC_INLINE PetscErrorCode VecStashValue_Private(VecStash *stash,PetscInt row,PetscScalar value)
{
  PetscErrorCode ierr;
  /* Check and see if we have sufficient memory */
  if (((stash)->n + 1) > (stash)->nmax) {
    ierr = VecStashExpand_Private(stash,1);CHKERRQ(ierr);
  }
  (stash)->idx[(stash)->n]   = row;
  (stash)->array[(stash)->n] = value;
  (stash)->n++;
  return 0;
}

/*
  VecStashValuesBlocked_Private - inserts 1 block of values into the stash.

  Input Parameters:
  stash  - the stash
  idx    - the global block index
  values - the values inserted
*/
PETSC_STATIC_INLINE PetscErrorCode VecStashValuesBlocked_Private(VecStash *stash,PetscInt row,PetscScalar *values)
{
  PetscInt       jj,stash_bs=(stash)->bs;
  PetscScalar    *array;
  PetscErrorCode ierr;
  if (((stash)->n+1) > (stash)->nmax) {
    ierr = VecStashExpand_Private(stash,1);CHKERRQ(ierr);
  }
  array = (stash)->array + stash_bs*(stash)->n;
  (stash)->idx[(stash)->n]   = row;
  for (jj=0; jj<stash_bs; jj++) { array[jj] = values[jj];}
  (stash)->n++;
  return 0;
}

PETSC_INTERN PetscErrorCode VecStrideGather_Default(Vec,PetscInt,Vec,InsertMode);
PETSC_INTERN PetscErrorCode VecStrideScatter_Default(Vec,PetscInt,Vec,InsertMode);
PETSC_INTERN PetscErrorCode VecReciprocal_Default(Vec);
PETSC_INTERN PetscErrorCode VecStrideSubSetGather_Default(Vec,PetscInt,const PetscInt[],const PetscInt[],Vec,InsertMode);
PETSC_INTERN PetscErrorCode VecStrideSubSetScatter_Default(Vec,PetscInt,const PetscInt[],const PetscInt[],Vec,InsertMode);

#if defined(PETSC_HAVE_MATLAB_ENGINE)
PETSC_EXTERN PetscErrorCode VecMatlabEnginePut_Default(PetscObject,void*);
PETSC_EXTERN PetscErrorCode VecMatlabEngineGet_Default(PetscObject,void*);
#endif

PETSC_EXTERN PetscErrorCode PetscSectionGetField_Internal(PetscSection, PetscSection, Vec, PetscInt, PetscInt, PetscInt, IS *, Vec *);
PETSC_EXTERN PetscErrorCode PetscSectionRestoreField_Internal(PetscSection, PetscSection, Vec, PetscInt, PetscInt, PetscInt, IS *, Vec *);

#define VecCheckSameLocalSize(x,ar1,y,ar2)                                 \
  if ((x)->map->n != (y)->map->n) SETERRQ4(PETSC_COMM_SELF,PETSC_ERR_ARG_INCOMP,"Incompatible vector local lengths parameter # %d local size %D != parameter # %d local size %D", ar1,(x)->map->n, ar2,(y)->map->n);

#define VecCheckSameSize(x,ar1,y,ar2)                                      \
  if ((x)->map->N != (y)->map->N) SETERRQ4(PetscObjectComm((PetscObject)x),PETSC_ERR_ARG_INCOMP,"Incompatible vector global lengths parameter # %d global size %D != paramter # %d global size %D", ar1,(x)->map->N, ar2,(y)->map->N);\
  VecCheckSameLocalSize(x,ar1,y,ar2);
  
#define VecCheckLocalSize(x,ar1,n)                                         \
  if ((x)->map->n != n) SETERRQ3(PETSC_COMM_SELF,PETSC_ERR_ARG_INCOMP,"Incorrect vector local size: parameter # %d local size %D != %D",ar1,(x)->map->n,n);
  
#define VecCheckSize(x,ar1,n,N)                                            \
  if ((x)->map->N != N) SETERRQ(PetscObjectComm((PetscObject)x),PETSC_ERR_ARG_INCOMP,"Incorrect vector global size: parameter # %d global size %D != %D",ar1,(x)->map->N, N);\
  VecCheckLocalSize(x,ar1,n);

typedef struct _VecTaggerOps *VecTaggerOps;
struct _VecTaggerOps {
  PetscErrorCode (*create) (VecTagger);
  PetscErrorCode (*destroy) (VecTagger);
  PetscErrorCode (*setfromoptions) (PetscOptionItems*,VecTagger);
  PetscErrorCode (*setup) (VecTagger);
  PetscErrorCode (*view) (VecTagger,PetscViewer);
  PetscErrorCode (*computeboxes) (VecTagger,Vec,PetscInt *,VecTaggerBox **);
  PetscErrorCode (*computeis) (VecTagger,Vec,IS *);
};
struct _p_VecTagger {
  PETSCHEADER(struct _VecTaggerOps);
  void      *data;
  PetscInt  blocksize;
  PetscBool invert;
  PetscBool setupcalled;
};

PETSC_EXTERN PetscBool      VecTaggerRegisterAllCalled;
PETSC_EXTERN PetscErrorCode VecTaggerRegisterAll(void);
PETSC_EXTERN PetscErrorCode VecTaggerComputeIS_FromBoxes(VecTagger,Vec,IS*);
PETSC_EXTERN PetscMPIInt Petsc_Reduction_keyval;

#endif

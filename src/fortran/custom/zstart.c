#ifndef lint
static char vcid[] = "$Id: zstart.c,v 1.5 1996/05/28 21:29:31 balay Exp bsmith $";
#endif

/*
  This file contains Fortran stubs for PetscInitialize and Finalize.
  These are not generated automatically since they require passing strings
  between Fortran and C.
*/

/*
    This is to prevent the Cray T3D version of MPI (University of Edinburgh)
  from stupidly redefining MPI_INIT(). They put this in to detect errors
  in C code, but here I do want to be calling the Fortran version from a
  C subroutine. I think their act goes against the philosophy of MPI 
  and their mpi.h file should be declared not up to the standard.
*/
#define T3DMPI_FORTRAN
#include "zpetsc.h" 
#include "sys.h"
#include <stdio.h>
#include "pinclude/pviewer.h"
#include "pinclude/petscfix.h"
extern int          PetscBeganMPI;

#ifdef HAVE_FORTRAN_CAPS
#define petscfinalize_                PETSCFINALIZE
#define petscsetcommonblock_          PETSCSETCOMMONBLOCK
#define petscinitialize_              PETSCINITIALIZE
#define iargc_                        IARGC
#define getarg_                       GETARG
#define mpi_init_                     MPI_INIT
#define petscinitializefortran_       PETSCINITIALIZEFORTRAN
#elif !defined(HAVE_FORTRAN_UNDERSCORE)
#define petscfinalize_                petscfinalize
#define petscsetcommonblock_          petscsetcommonblock
#define petscinitialize_              petscinitialize
#define mpi_init_                     mpi_init
#define petscinitializefortran_       petscinitializefortran
/*
    HP-UX does not have Fortran underscore but iargc and getarg 
  do have underscores????
*/
#if !defined(PARCH_hpux)
#define iargc_                        iargc
#define getarg_                       getarg
#endif

#endif

int OptionsCheckInitial_Private(),
    OptionsCreate_Private(int*,char***,char*),
    OptionsSetAlias_Private(char *,char *);

/*
    The extra _ is because the f2c compiler puts an
  extra _ at the end if the original routine name 
  contained any _.
*/
#if defined(HAVE_FORTRAN_UNDERSCORE_UNDERSCORE)
#define mpi_init_             mpi_init__
#endif

#if defined(__cplusplus)
extern "C" {
#endif
extern void mpi_init_(int*);
extern void petscsetcommonblock_(int*,int*,int*);
extern int  iargc_();
extern void getarg_(int*,char*,int);
#if defined(PARCH_t3d)
extern void PXFGETARG(int *,_fcd,int*,int*);
#endif
#if defined(__cplusplus)
}
#endif

/*
    Reads in Fortran command line argments and sends them to 
  all processors and adds them to Options database.
*/

int PETScParseFortranArgs_Private(int *argc,char ***argv)
{
  int  i, warg = 256,rank;
  char *p;

  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  if (!rank) {
    *argc = 1 + iargc_();
  }
  MPI_Bcast(argc,1,MPI_INT,0,MPI_COMM_WORLD);

  *argv = (char **) PetscMalloc((*argc+1)*(warg*sizeof(char)+sizeof(char*))); 
  CHKPTRQ(*argv);
  (*argv)[0] = (char*) (*argv + *argc + 1);

  if (!rank) {
    PetscMemzero((*argv)[0],(*argc)*warg*sizeof(char));
    for ( i=0; i<*argc; i++ ) {
      (*argv)[i+1] = (*argv)[i] + warg;
#if defined(PARCH_t3d)
      {char *tmp = (*argv)[i]; 
       int  ierr,ilen;
       PXFGETARG(&i, _cptofcd(tmp,warg),&ilen,&ierr); CHKERRQ(ierr);
       tmp[ilen] = 0;
      } 
#else
      getarg_( &i, (*argv)[i], warg );
#endif
      /* zero out garbage at end of each argument */
      p = (*argv)[i] + warg-1;
      while (p > (*argv)[i]) {
        if (*p == ' ') *p = 0; 
        p--;
      }
    }
  }
  MPI_Bcast((*argv)[0],*argc*warg,MPI_CHAR,0,MPI_COMM_WORLD);  
  if (rank) {
    for ( i=0; i<*argc; i++ ) {
      (*argv)[i+1] = (*argv)[i] + warg;
    }
  } 
  return 0;   
}

#if defined(__cplusplus)
extern "C" {
#endif

extern int PetscInitializedCalled;

void petscinitialize_(CHAR filename,int *__ierr,int len)
{
  int  flag,argc = 0;
  char **args = 0,*t1;
  *__ierr = 1;

  if (PetscInitializedCalled) {*__ierr = 0; return;}
  PetscInitializedCalled = 1;

  MPI_Initialized(&flag);
  if (!flag) {
    mpi_init_(__ierr);
    if (*__ierr) {fprintf(stderr,"PetscInitialize:");return;}
    PetscBeganMPI = 1;
  }
  PetscInitializeFortran();
#if defined(PETSC_COMPLEX)
  MPI_Type_contiguous(2,MPI_DOUBLE,&MPIU_COMPLEX);
  MPI_Type_commit(&MPIU_COMPLEX);
#endif
  PETScParseFortranArgs_Private(&argc,&args);
  FIXCHAR(filename,len,t1);
  *__ierr = OptionsCreate_Private(&argc,&args,t1); 
  FREECHAR(filename,t1);
  if (*__ierr) { fprintf(stderr,"PETSC ERROR: PetscInitialize:");return;}
  PetscFree(args);
  *__ierr = OptionsCheckInitial_Private(); 
  if (*__ierr) { fprintf(stderr,"PETSC ERROR: PetscInitialize:");return;}
  *__ierr = ViewerInitialize_Private(); 
  if (*__ierr) { fprintf(stderr,"PETSC ERROR: PetscInitialize:");return;}

  if (PetscBeganMPI) {
    int rank,size;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    PLogInfo(0,"[%d] PETSc successfully started: procs %d\n",rank,size);
  }
  *__ierr = 0;
}

void petscfinalize_(int *__ierr){
  *__ierr = PetscFinalize();
}


#if defined(__cplusplus)
}
#endif




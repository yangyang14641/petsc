#ifdef PETSC_RCS_HEADER
static char vcid[] = "$Id: f90_rs6000.c,v 1.4 1998/04/03 23:49:19 balay Exp balay $";
#endif

/*
         This file contains the code to map between Fortran 90 
  pointers and traditional C pointers for the NAG F90 compiler.
*/
#if defined(HAVE_XLF90)
#include "src/fortran/f90/zf90.h"

/* --------------------------------------------------------*/
/*
    PetscF90Create1dArrayScalar - Given a C pointer to a one dimensional
  array and its length; this fills in the appropriate Fortran 90
  pointer data structure.

  Input Parameters:
.   array - regular C pointer (address)
.   len - length of array (in items)

  Output Parameters:
.   ptr - Fortran 90 pointer
*/ 
int PetscF90Create1dArrayScalar(Scalar *array,int len, array1d *ptr)
{
  ptr->addr          = (void *)array;
  ptr->id            = F90_DOUBLE_ID;
  ptr->cookie        = F90_COOKIE;
  ptr->sd            = sizeof(Scalar);
  ptr->ndim          = 1;
  ptr->dim[0].extent = len;
  ptr->dim[0].mult   = sizeof(Scalar);
  ptr->dim[0].lower  = 1;
  ptr->sum_d         = -(ptr->dim[0].lower*ptr->dim[0].mult);

  return 0;
}

/*
    PetscF90Get1dArrayScalar - Gets the address for the data 
       stored in a Fortran pointer array.

  Input Parameters:
.   ptr - Fortran 90 pointer

  Output Parameters:
.   array - regular C pointer (address)

*/ 
int PetscF90Get1dArrayScalar(array1d *ptr,Scalar **array)
{
  *array = (void *) ptr->addr;
  return 0;
}

/*
    PetscF90Destroy1dArrayScalar - Deletes a Fortran pointer.

  Input Parameters:
.   ptr - Fortran 90 pointer
*/ 
int PetscF90Destroy1dArrayScalar(array1d *ptr)
{
  ptr->addr = (void *)0;
  return 0;
}
/* --------------------------------------------------------*/
/*
    PetscF90Create2dArrayScalar - Given a C pointer to a two dimensional
  array and its length; this fills in the appropriate Fortran 90
  pointer data structure.

  Input Parameters:
.   array - regular C pointer (address)
.   m - number of rows in array
.   n - number of columns in array

  Output Parameters:
.   ptr - Fortran 90 pointer
*/ 
int PetscF90Create2dArrayScalar(Scalar *array,int m,int n, array2d *ptr)
{
  ptr->addr          = (void *)array;
  ptr->id            = F90_DOUBLE_ID;
  ptr->cookie        = F90_COOKIE;
  ptr->sd            = sizeof(Scalar);
  ptr->ndim          = 2;
  ptr->dim[1].extent = m;
  ptr->dim[1].mult   = sizeof(Scalar);
  ptr->dim[1].lower  = 1;
  ptr->dim[0].extent = n;
  ptr->dim[0].mult   = m*sizeof(Scalar);
  ptr->dim[0].lower  = 1;
  ptr->sum_d         = -(ptr->dim[0].lower*ptr->dim[0].mult+ptr->dim[1].lower*ptr->dim[1].mult);

  return 0;
}

/*
    PetscF90Get2dArrayScalar - Gets the address for the data 
       stored in a 2d Fortran pointer array.

  Input Parameters:
.   ptr - Fortran 90 pointer

  Output Parameters:
.   array - regular C pointer (address)

*/ 
int PetscF90Get2dArrayScalar(array2d *ptr,Scalar **array)
{
  *array = (void *) ptr->addr;
  return 0;
}

/*
    PetscF90Destroy2dArrayScalar - Deletes a Fortran pointer.

  Input Parameters:
.   ptr - Fortran 90 pointer
*/ 
int PetscF90Destroy2dArrayScalar(array2d *ptr)
{
  ptr->addr  = (void *)0;
  return 0;
}
/* -----------------------------------------------------------------*/

/*
    PetscF90Create1dArrayInt - Given a C pointer to a one dimensional
  array and its length; this fills in the appropriate Fortran 90
  pointer data structure.

  Input Parameters:
.   array - regular C pointer (address)
.   len - length of array (in items)

  Output Parameters:
.   ptr - Fortran 90 pointer
*/ 
int PetscF90Create1dArrayInt(int *array,int len, array1d *ptr)
{
  ptr->addr          = (void *)array;
  ptr->id            = F90_INT_ID;
  ptr->cookie        = F90_COOKIE;
  ptr->sd            = sizeof(int);
  ptr->ndim          = 1;
  ptr->dim[0].extent = len;
  ptr->dim[0].mult   = sizeof(int);
  ptr->dim[0].lower  = 1;
  ptr->sum_d         = -(ptr->dim[0].lower*ptr->dim[0].mult);

  return 0;
}

/*
    PetscF90Get1dArrayInt - Gets the address for the data 
       stored in a Fortran pointer array.

  Input Parameters:
.   ptr - Fortran 90 pointer

  Output Parameters:
.   array - regular C pointer (address)

*/ 
int PetscF90Get1dArrayInt(array1d *ptr,int **array)
{
  *array = (void *) ptr->addr;
  return 0;
}

/*
    PetscF90Destroy1dArrayInt - Deletes a Fortran pointer.

  Input Parameters:
.   ptr - Fortran 90 pointer
*/ 
int PetscF90Destroy1dArrayInt(array1d *ptr)
{
  ptr->addr  = (void *)0;
  return 0;
}
/* -----------------------------------------------------------------*/

/*
    PetscF90Create1dArrayPetscFortranAddr - Given a C pointer to a one dimensional
  array and its length; this fills in the appropriate Fortran 90
  pointer data structure.

  Input Parameters:
.   array - regular C pointer (address)
.   len - length of array (in items)

  Output Parameters:
.   ptr - Fortran 90 pointer
*/ 
int PetscF90Create1dArrayPetscFortranAddr(PetscFortranAddr *array,int len, array1d *ptr)
{
  ptr->addr          = (void *)array;
  ptr->id            = F90_INT_ID;
  ptr->cookie        = F90_COOKIE;
  ptr->sd            = sizeof(PetscFortranAddr);
  ptr->ndim          = 1;
  ptr->dim[0].extent = len;
  ptr->dim[0].mult   = sizeof(PetscFortranAddr);
  ptr->dim[0].lower  = 1;
  ptr->sum_d         = -(ptr->dim[0].lower*ptr->dim[0].mult);

  return 0;
}

/*
    PetscF90Get1dArrayPetscFortranAddr - Gets the address for the data 
       stored in a Fortran pointer array.

  Input Parameters:
.   ptr - Fortran 90 pointer

  Output Parameters:
.   array - regular C pointer (address)

*/ 
int PetscF90Get1dArrayPetscFortranAddr(array1d *ptr,PetscFortranAddr **array)
{
  *array = (void *) ptr->addr;
  return 0;
}

/*
    PetscF90Destroy1dArrayPetscFortranAddr - Deletes a Fortran pointer.

  Input Parameters:
.   ptr - Fortran 90 pointer
*/ 
int PetscF90Destroy1dArrayPetscFortranAddr(array1d *ptr)
{
  ptr->addr  = (void *)0;
  return 0;
}

#else
/*
     Dummy function so that compilers won't complain about 
  empty files.
*/
int F90_rs600_Dummy(int dummy)
{
  return 0;
}

#endif

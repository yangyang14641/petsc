
#if !defined(__is_h)
#define __is_h

#include <petscsf.h>
#include <petsc/private/matimpl.h>

typedef struct {
  Mat        A;             /* the local Neumann matrix */
  VecScatter ctx;           /* update local vectors for matrix vector product */
  Vec        x,y;           /* work space for matrix vector product */
  PetscBool  pure_neumann;
  PetscSF    sf;
  PetscInt   sf_nroots,sf_nleaves;
  PetscInt   *sf_rootdata,*sf_leafdata;
} Mat_IS;

PETSC_EXTERN PetscErrorCode MatISSetMPIXAIJPreallocation_Private(Mat,Mat,PetscBool);
#endif





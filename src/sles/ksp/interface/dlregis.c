/*$Id: dlregis.c,v 1.20 2001/03/23 23:23:29 balay Exp $*/

#include "petscsles.h"

#undef __FUNCT__  
#define __FUNCT__ "SLESInitializePackage"
/*@C
  SLESInitializePackage - This function initializes everything in the SLES package. It is called
  from PetscDLLibraryRegister() when using dynamic libraries, and on the first call to SLESCreate()
  when using static libraries.

  Input Parameter:
  path - The dynamic library path, or PETSC_NULL

  Level: developer

.keywords: SLES, initialize, package
.seealso: PetscInitialize()
@*/
int SLESInitializePackage(const char path[]) {
  static PetscTruth initialized = PETSC_FALSE;
  char              logList[256];
  char             *className;
  PetscTruth        opt;
  int               ierr;

  PetscFunctionBegin;
  if (initialized == PETSC_TRUE) PetscFunctionReturn(0);
  initialized = PETSC_TRUE;
  /* Register Classes */
  ierr = PetscLogClassRegister(&KSP_COOKIE,  "Krylov Solver");                                            CHKERRQ(ierr);
  ierr = PetscLogClassRegister(&PC_COOKIE,   "Preconditioner");                                           CHKERRQ(ierr);
  ierr = PetscLogClassRegister(&SLES_COOKIE, "SLES");                                                     CHKERRQ(ierr);
  /* Register Constructors and Serializers */
  ierr = KSPRegisterAll(path);                                                                            CHKERRQ(ierr);
  ierr = PCRegisterAll(path);                                                                             CHKERRQ(ierr);
  /* Register Events */
  ierr = PetscLogEventRegister(&PC_SetUp,                   "PCSetUp",          PC_COOKIE);               CHKERRQ(ierr);
  ierr = PetscLogEventRegister(&PC_SetUpOnBlocks,           "PCSetUpOnBlocks",  PC_COOKIE);               CHKERRQ(ierr);
  ierr = PetscLogEventRegister(&PC_Apply,                   "PCApply",          PC_COOKIE);               CHKERRQ(ierr);
  ierr = PetscLogEventRegister(&PC_ApplyCoarse,             "PCApplyCoarse",    PC_COOKIE);               CHKERRQ(ierr);
  ierr = PetscLogEventRegister(&PC_ApplyMultiple,           "PCApplyMultiple",  PC_COOKIE);               CHKERRQ(ierr);
  ierr = PetscLogEventRegister(&PC_ApplySymmetricLeft,      "PCApplySymmLeft",  PC_COOKIE);               CHKERRQ(ierr);
  ierr = PetscLogEventRegister(&PC_ApplySymmetricRight,     "PCApplySymmRight", PC_COOKIE);               CHKERRQ(ierr);
  ierr = PetscLogEventRegister(&PC_ModifySubMatrices,       "PCModifySubMatri", PC_COOKIE);               CHKERRQ(ierr);
  ierr = PetscLogEventRegister(&KSP_GMRESOrthogonalization, "KSPGMRESOrthog",   KSP_COOKIE);              CHKERRQ(ierr);
  ierr = PetscLogEventRegister(&SLES_SetUp,                 "SLESSetup",        SLES_COOKIE);             CHKERRQ(ierr);
  ierr = PetscLogEventRegister(&SLES_Solve,                 "SLESSolve",        SLES_COOKIE);             CHKERRQ(ierr);
  /* Process info exclusions */
  ierr = PetscOptionsGetString(PETSC_NULL, "-log_info_exclude", logList, 256, &opt);                      CHKERRQ(ierr);
  if (opt == PETSC_TRUE) {
    ierr = PetscStrstr(logList, "sles", &className);                                                      CHKERRQ(ierr);
    if (className) {
      ierr = PetscLogInfoDeactivateClass(KSP_COOKIE);                                                     CHKERRQ(ierr);
      ierr = PetscLogInfoDeactivateClass(PC_COOKIE);                                                      CHKERRQ(ierr);
      ierr = PetscLogInfoDeactivateClass(SLES_COOKIE);                                                    CHKERRQ(ierr);
    }
    ierr = PetscStrstr(logList, "ksp", &className);                                                       CHKERRQ(ierr);
    if (className) {
      ierr = PetscLogInfoDeactivateClass(KSP_COOKIE);                                                     CHKERRQ(ierr);
    }
    ierr = PetscStrstr(logList, "pc", &className);                                                        CHKERRQ(ierr);
    if (className) {
      ierr = PetscLogInfoDeactivateClass(PC_COOKIE);                                                      CHKERRQ(ierr);
    }
  }
  /* Process summary exclusions */
  ierr = PetscOptionsGetString(PETSC_NULL, "-log_summary_exclude", logList, 256, &opt);                   CHKERRQ(ierr);
  if (opt == PETSC_TRUE) {
    ierr = PetscStrstr(logList, "sles", &className);                                                      CHKERRQ(ierr);
    if (className) {
      ierr = PetscLogEventDeactivateClass(KSP_COOKIE);                                                    CHKERRQ(ierr);
      ierr = PetscLogEventDeactivateClass(PC_COOKIE);                                                     CHKERRQ(ierr);
      ierr = PetscLogEventDeactivateClass(SLES_COOKIE);                                                   CHKERRQ(ierr);
    }
    ierr = PetscStrstr(logList, "ksp", &className);                                                       CHKERRQ(ierr);
    if (className) {
      ierr = PetscLogEventDeactivateClass(KSP_COOKIE);                                                    CHKERRQ(ierr);
    }
    ierr = PetscStrstr(logList, "pc", &className);                                                        CHKERRQ(ierr);
    if (className) {
      ierr = PetscLogEventDeactivateClass(PC_COOKIE);                                                     CHKERRQ(ierr);
    }
  }
  PetscFunctionReturn(0);
}

#ifdef PETSC_USE_DYNAMIC_LIBRARIES
EXTERN_C_BEGIN
#undef __FUNCT__  
#define __FUNCT__ "PetscDLLibraryRegister"
/*
  PetscDLLibraryRegister - This function is called when the dynamic library it is in is opened.

  This one registers all the KSP and PC methods that are in the basic PETSc libpetscsles
  library.

  Input Parameter:
  path - library path
 */
int PetscDLLibraryRegister(char *path)
{
  int ierr;

  ierr = PetscInitializeNoArguments(); if (ierr) return 1;

  PetscFunctionBegin;
  /*
      If we got here then PETSc was properly loaded
  */
  ierr = SLESInitializePackage(path);                                                                     CHKERRQ(ierr);
  PetscFunctionReturn(0);
}
EXTERN_C_END

/* --------------------------------------------------------------------------*/
static char *contents = "PETSc Krylov subspace method and preconditioner library.\n\
     GMRES, PCG, Bi-CG-stab, ...\n\
     Jacobi, ILU, Block Jacobi, LU, Additive Schwarz, ...\n";
static char *authors  = PETSC_AUTHOR_INFO;

#include "src/sys/src/utils/dlregis.h"

#endif /* PETSC_USE_DYNAMIC_LIBRARIES */

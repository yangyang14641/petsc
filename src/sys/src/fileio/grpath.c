#ifdef PETSC_RCS_HEADER
static char vcid[] = "$Id: grpath.c,v 1.17 1998/05/08 16:12:44 bsmith Exp bsmith $";
#endif

#include "petsc.h"
#include "sys.h"
#if defined(HAVE_PWD_H)
#include <pwd.h>
#endif
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#if defined(HAVE_UNISTD_H)
#include <unistd.h>
#endif
#if defined(HAVE_STDLIB_H)
#include <stdlib.h>
#endif
#if !defined(PARCH_nt)
#include <sys/param.h>
#include <sys/utsname.h>
#endif
#if defined(PARCH_nt)
#include <windows.h>
#include <io.h>
#include <direct.h>
#endif
#if defined (PARCH_nt_gnu)
#include <windows.h>
#endif
#if defined(HAVE_SYS_SYSTEMINFO_H)
#include <sys/systeminfo.h>
#endif
#include "pinclude/petscfix.h"

#ifndef MAXPATHLEN
#define MAXPATHLEN 1024
#endif


#undef __FUNC__  
#define __FUNC__ "PetscGetRealPath"
/*@C
   PetscGetRealPath - Get the path without symbolic links etc. and in absolute form.

   Not Collective

   Input Parameter:
.  path - path to resolve

   Output Parameter:
.  rpath - resolved path

   Notes: 
   rpath is assumed to be of length MAXPATHLEN.

   Systems that use the automounter often generate absolute paths
   of the form "/tmp_mnt....".  However, the automounter will fail to
   mount this path if it isn't already mounted, so we remove this from
   the head of the line.  This may cause problems if, for some reason,
   /tmp_mnt is valid and not the result of the automounter.

.keywords, system, get, real, path

.seealso: PetscGetFullPath()
@*/
int PetscGetRealPath(char * path, char *rpath )
{
  char tmp3[MAXPATHLEN];

#if defined(HAVE_REALPATH)
  PetscFunctionBegin;
  realpath( path, rpath );
#elif defined (PARCH_nt)
  PetscFunctionBegin;
  PetscStrcpy( rpath, path );
#elif !defined(HAVE_READLINK)
  PetscFunctionBegin;
  PetscStrcpy( rpath, path );
#else
  char tmp1[MAXPATHLEN], tmp4[MAXPATHLEN], *tmp2;
  int  n, m, N;
  PetscFunctionBegin;

  /* Algorithm: we move through the path, replacing links with the real paths.   */
  PetscStrcpy( rpath, path );
  N = PetscStrlen(rpath);
  while (N) {
    PetscStrncpy(tmp1,rpath,N); tmp1[N] = 0;
    n = readlink(tmp1,tmp3,MAXPATHLEN);
    if (n > 0) {
      tmp3[n] = 0; /* readlink does not automatically add 0 to string end */
      if (tmp3[0] != '/') {
        tmp2 = PetscStrchr(tmp1,'/');
        m = PetscStrlen(tmp1) - PetscStrlen(tmp2);
        PetscStrncpy(tmp4,tmp1,m); tmp4[m] = 0;
        PetscStrncat(tmp4,"/",MAXPATHLEN - PetscStrlen(tmp4));
        PetscStrncat(tmp4,tmp3,MAXPATHLEN - PetscStrlen(tmp4));
        PetscGetRealPath(tmp4,rpath);
        PetscStrncat(rpath,path+N,MAXPATHLEN - PetscStrlen(rpath));
        PetscFunctionReturn(0);
      } else {
        PetscGetRealPath(tmp3,tmp1);
        PetscStrncpy(rpath,tmp1,MAXPATHLEN);
        PetscStrncat(rpath,path+N,MAXPATHLEN - PetscStrlen(rpath));
        PetscFunctionReturn(0);
      }
    }  
    tmp2 = PetscStrchr(tmp1,'/');
    if (tmp2) N = PetscStrlen(tmp1) - PetscStrlen(tmp2);
    else N = PetscStrlen(tmp1);
  }
  PetscStrncpy(rpath,path,MAXPATHLEN);
#endif
  /* remove garbage some automounters put at the beginning of the path */
  if (PetscStrncmp( "/tmp_mnt/", rpath, 9 ) == 0) {
    PetscStrcpy( tmp3, rpath + 8 );
    PetscStrcpy( rpath, tmp3 );
  }
  PetscFunctionReturn(0);
}

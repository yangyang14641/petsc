CFLAGS	         =
FFLAGS	         =
CPPFLAGS         =
FPPFLAGS         =
LOCDIR           = src/ksp/ksp/examples/tutorials/
DIRS             = network
EXAMPLESC        = ex1.c ex2.c ex3.c ex5.c ex6.c ex7.c ex8.c ex9.c \
                ex10.c ex11.c ex12.c ex13.c ex15.c ex16.c ex18.c ex23.c \
                ex25.c ex27.c ex28.c ex29.c ex30.c ex32.c ex34.c \
                ex41.c ex42.c ex43.c \
                ex45.c ex46.c  ex49.c ex50.c ex51.c ex52.c ex53.c \
                ex54.c ex55.c ex56.c ex58.c ex62.c ex63.cxx ex64.c ex65.c ex66.c ex67.c ex68.c ex69.c ex70.c ex72.c ex100.c
EXAMPLESF        = ex1f.F90 ex2f.F90 ex6f.F90 ex11f.F90 ex13f90.F90 ex14f.F90 ex15f.F90 ex21f.F90 ex22f.F90 ex44f.F90 ex45f.F90 \
                   ex52f.F90 ex54f.F90 ex61f.F90 ex100f.F90
MANSEC           = KSP
CLEANFILES       = rhs.vtk solution.vtk
NP               = 1

include ${PETSC_DIR}/lib/petsc/conf/variables
include ${PETSC_DIR}/lib/petsc/conf/rules

testex100: ex100.PETSc
	-@if [ "${PETSC_WITH_BATCH}" != "" ]; then \
           echo "Running with batch filesystem; to test run src/ksp/ksp/examples/tutorials/ex100 with" ; \
           echo "your systems batch system"; \
        elif [ "${MPIEXEC}" = "/bin/false" ]; then \
           echo "*mpiexec not found*. Please run src/ksp/ksp/examples/tutorials/ex100 manually"; \
	elif [ -f ex100 ]; then \
           ${MPIEXEC} -n 1 ./ex100 -test  > ex100_1.tmp 2>&1; \
	   if (${DIFF} output/ex100_1.testout ex100_1.tmp > /dev/null 2>&1) then \
           echo "C/C++ example src/ksp/ksp/examples/tutorials/ex100 run successfully with 1 MPI process"; \
	   else echo "Possible error running C/C++ src/ksp/ksp/examples/tutorials/ex100 with 1 MPI process"; \
           echo "See http://www.mcs.anl.gov/petsc/documentation/faq.html";\
           cat ex100_1.tmp; fi; \
        ${RM} -f ex100_1.tmp; fi

include ${PETSC_DIR}/lib/petsc/conf/test

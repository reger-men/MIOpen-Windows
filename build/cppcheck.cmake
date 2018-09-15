
        file(GLOB_RECURSE GSRCS  C:/Users/Adil/Desktop/MLOpen-1-1.5.x/addkernels/*.cpp C:/Users/Adil/Desktop/MLOpen-1-1.5.x/addkernels/*.hpp C:/Users/Adil/Desktop/MLOpen-1-1.5.x/addkernels/*.cxx C:/Users/Adil/Desktop/MLOpen-1-1.5.x/addkernels/*.c C:/Users/Adil/Desktop/MLOpen-1-1.5.x/addkernels/*.h C:/Users/Adil/Desktop/MLOpen-1-1.5.x/include/*.cpp C:/Users/Adil/Desktop/MLOpen-1-1.5.x/include/*.hpp C:/Users/Adil/Desktop/MLOpen-1-1.5.x/include/*.cxx C:/Users/Adil/Desktop/MLOpen-1-1.5.x/include/*.c C:/Users/Adil/Desktop/MLOpen-1-1.5.x/include/*.h C:/Users/Adil/Desktop/MLOpen-1-1.5.x/src/*.cpp C:/Users/Adil/Desktop/MLOpen-1-1.5.x/src/*.hpp C:/Users/Adil/Desktop/MLOpen-1-1.5.x/src/*.cxx C:/Users/Adil/Desktop/MLOpen-1-1.5.x/src/*.c C:/Users/Adil/Desktop/MLOpen-1-1.5.x/src/*.h C:/Users/Adil/Desktop/MLOpen-1-1.5.x/test/*.cpp C:/Users/Adil/Desktop/MLOpen-1-1.5.x/test/*.hpp C:/Users/Adil/Desktop/MLOpen-1-1.5.x/test/*.cxx C:/Users/Adil/Desktop/MLOpen-1-1.5.x/test/*.c C:/Users/Adil/Desktop/MLOpen-1-1.5.x/test/*.h)
        set(CPPCHECK_COMMAND
            CPPCHECK_EXE-NOTFOUND
            -q
            # -v
            # --report-progress
            --force
            --cppcheck-build-dir=C:/Users/Adil/Desktop/MLOpen-1-1.5.x/build/cppcheck-build
            --platform=native
            "--template={file}:{line}: {severity}: {message} [{id}]"
            --error-exitcode=1
            -j 8
             -DMIOPEN_USE_MIOPENGEMM=1
            
             -IC:/Users/Adil/Desktop/MLOpen-1-1.5.x/include -IC:/Users/Adil/Desktop/MLOpen-1-1.5.x/build/include -IC:/Users/Adil/Desktop/MLOpen-1-1.5.x/src/include
            --enable=all
            --inline-suppr
            --suppressions-list=C:/Users/Adil/Desktop/MLOpen-1-1.5.x/build/cppcheck-supressions
             ${GSRCS}
        )
        string(REPLACE ";" " " CPPCHECK_SHOW_COMMAND "${CPPCHECK_COMMAND}")
        message("${CPPCHECK_SHOW_COMMAND}")
        execute_process(
            COMMAND ${CPPCHECK_COMMAND}
            WORKING_DIRECTORY C:/Users/Adil/Desktop/MLOpen-1-1.5.x
            RESULT_VARIABLE RESULT
        )
        if(NOT RESULT EQUAL 0)
            message(FATAL_ERROR "Cppcheck failed")
        endif()

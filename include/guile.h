#pragma once

#include <libguile.h>
#include <string>

using namespace std;

namespace Guile
{
    inline void init()
    {
        scm_init_guile();

        /* Define some Guile variables from C */
        //scm_c_define("my-age", scm_int2num(32));
        //scm_c_define("my-height", scm_long2num(184));
        //scm_c_define("my-weight", scm_double2num(170.0));

        /* Run a script that prints out the variables */
        //scm_c_primitive_load("script.scm");

        //SCM func_symbol = scm_c_lookup("do-hello");
        //SCM func = scm_variable_ref(func_symbol);
        //scm_call_0(func);
    };


    inline bool symbolExists(string name)
    {
        SCM sym;
        SCM var;

        sym = scm_str2symbol(name.c_str());

        /* Check to see if the symbol exists */
        var = scm_sym2var(sym,
                          scm_current_module_lookup_closure(),
                          SCM_BOOL_F
                         );

        if (var != SCM_BOOL_F) {
            return true;
        }

        return false;
    };
};
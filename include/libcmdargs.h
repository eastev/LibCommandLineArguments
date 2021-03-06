/**
 * SPDX-License-Identifier: BSD-3-Clause
 * Copyright © 2022 Alexander Elunin <https://github.com/eastev>
 * 
 * 
 * Project: LibCommandLineArguments
 * Module: Library
 * File: libcmdargs.h
 *
 * Command line arguments parsing library interface.
 * Command line commands options and parameters (option have - or -- prefix):
 * <command> -<cmdoption1> -<cmdoption2> --<cmdoption3> ...
 * <command> -<cmdoption1> <parameter1> -<cmdoption2> <parameter2> ...
 * <command> <cmdparameter1> <cmdparameter2> ... 
 * <command> -<cmdoption1> <parameter> ... <cmdparameter1> <cmdparameter2> ...
*/


#ifndef __LIBCMDARGS_H__
#define __LIBCMDARGS_H__


#include <stdint.h>
#include <stddef.h>


#ifdef __cplusplus
namespace LibCmdArgs {
    extern "C" {
#endif


/**
 * @brief Constants for flags and return values
*/
enum libcmdargs_consts
{
    LIBCMDARGS_ERROR = -1,                      /* Operation returned error */
    LIBCMDARGS_NOT_PRESENT,                     /* No suitable values found */
    LIBCMDARGS_PRESENT                          /* Suitable value is present */
};


/**
 * @brief Command line option representation structure
*/
typedef struct cmdopt
{
    char*       option;                         /* Command line option */
    char*       parameter;                      /* Option parameter */
} cmdopt_t;

/**
 * @brief Command line parameter representation structure
*/
typedef struct cmdparam
{
    char*       parameter;                      /* Command line parameter */
} cmdparam_t;

/**
 * @brief Command line options and parameters representations structure
*/
typedef struct cmdargs
{
    cmdopt_t*   options;                        /* Command line options */
    size_t      options_count;                  /* Number of options */
    cmdparam_t* parameters;                     /* Command line parameters */
    size_t      parameters_count;               /* Number of parameters */
} cmdargs_t;


/**
 * @brief Parse command line arguments into struct of options and parameters
 * @param argc Number of command line arguments
 * @param argv Command line arguments array
 * @return Pointer to command line options and parameters structure
*/
const cmdargs_t* const libcmdargs_parse(int argc, const char** const argv);

/**
 * @brief Free memory allocated for options and parameters representations
 * @param cmdargs Pointer to command line options and parameters structure
*/
void libcmdargs_free(cmdargs_t* cmdargs);

/**
 * @brief Resolves if command line option is present in arguments
 * @param args Command line arguments representation structure
 * @param opt Option to search for
 * @return @c 1 if option is present, @c 0 if not present and @c -1 on error
*/
int libcmdargs_isopt(const cmdargs_t* const args, const char* const opt);

/**
 * @brief Resolves if command line parameter is present in arguments
 * @param args Command line arguments representation structure
 * @param param Command line paramerter to search for
 * @return @c 1 if parameter is present, @c 0 if not present and @c -1 on error
*/
int libcmdargs_isparam(const cmdargs_t* const args, const char* const param);

/**
 * @brief Get command line option's parameter
 * @param args Command line arguments respresentation structure
 * @param opt Option to get argument from
 * @return Option's parameter or @c NULL if no parameter or option present
*/
const char* const libcmdargs_getoptparam(const cmdargs_t* const args, const char* const opt);

/**
 * @brief Make options strings unified (delete unnecessary dashes)
 * @param string String to process
 * @return String without unnecessary dashes
*/
const char* const __libcmdargs_strunify(const char* string);

/**
 * @brief Check wether options are equals
 * @param cmdopt Command line option representation structure
 * @param opt String contains option
 * @return @c true if options are equal and @c false if not
*/
int __libcmdargs_is_opts_equal(const cmdopt_t* const cmdopt, const char* const opt);

/**
 * @brief Check wether parameters are equals
 * @param cmdopt Command line parameter representation structure
 * @param opt String contains parameter
 * @return @c true if parameters are equal and @c false if not
*/
int __libcmdargs_is_params_equal(const cmdparam_t* const cmdparam, const char* const param);


#ifdef __cplusplus
    }
}
#endif


#endif

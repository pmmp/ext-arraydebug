/* arraydebug extension for PHP */

#ifndef PHP_ARRAYDEBUG_H
# define PHP_ARRAYDEBUG_H

extern zend_module_entry arraydebug_module_entry;
# define phpext_arraydebug_ptr &arraydebug_module_entry

# define PHP_ARRAYDEBUG_VERSION "0.1.0"

# if defined(ZTS) && defined(COMPILE_DL_ARRAYDEBUG)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

#endif	/* PHP_ARRAYDEBUG_H */

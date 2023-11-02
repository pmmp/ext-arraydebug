/* arraydebug extension for PHP */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "php_arraydebug.h"
#include "arraydebug_arginfo.h"


/* {{{ */
PHP_FUNCTION(array_debuginfo) {
	HashTable* ht;

	ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
		Z_PARAM_ARRAY_HT(ht)
	ZEND_PARSE_PARAMETERS_END();

	array_init(return_value);

#define add_output(field_name) add_assoc_long(return_value, #field_name, ht->field_name)

	add_output(nTableMask);
	add_output(nNumUsed);
	add_output(nNumOfElements);
	add_output(nTableSize);
	add_output(nInternalPointer);
	add_output(nNextFreeElement);

#undef add_output
}

static void array_hash_distribution(zval* return_value, HashTable* ht) {
	uint32_t nTableMask;
	Bucket* bucket;
	uint32_t actualIndex;

	//ignore table mask for packed arrays, it's not used
	nTableMask = HT_FLAGS(ht) & HASH_FLAG_PACKED ? 0 : ht->nTableMask;

	array_init(return_value);

	ZEND_HASH_FOREACH_BUCKET(ht, bucket) {
		HashTable* hKeys;

		actualIndex = bucket->h | nTableMask;
		zval *zExistingKeys = zend_hash_index_find(Z_ARRVAL_P(return_value), actualIndex);

		if (zExistingKeys != NULL) {
			hKeys = Z_ARRVAL_P(zExistingKeys);
		} else {
			zval zNewKeys;
			array_init(&zNewKeys);
			zend_hash_index_add(Z_ARRVAL_P(return_value), actualIndex, &zNewKeys);
			hKeys = Z_ARRVAL(zNewKeys);
		}
		zval zv;
		ZVAL_COPY(&zv, &bucket->val);
		if (bucket->key != NULL) {
			zend_hash_add(hKeys, bucket->key, &zv);
		} else {
			zend_hash_index_add(hKeys, bucket->h, &zv);
		}
	} ZEND_HASH_FOREACH_END();
}

/* {{{ */
PHP_FUNCTION(array_hash_distribution) {
	HashTable* ht;

	ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
		Z_PARAM_ARRAY_HT(ht)
	ZEND_PARSE_PARAMETERS_END();

	array_hash_distribution(return_value, ht);
} /* }}} */

PHP_FUNCTION(array_load_factor) {
	HashTable* ht;
	zval distribution;

	ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
		Z_PARAM_ARRAY_HT(ht)
	ZEND_PARSE_PARAMETERS_END();

	array_hash_distribution(&distribution, ht);

	RETVAL_DOUBLE(((double)zend_array_count(ht)) / ((double) zend_array_count(Z_ARRVAL(distribution))));

	zval_dtor(&distribution);
}

/* {{{ PHP_RINIT_FUNCTION */
PHP_RINIT_FUNCTION(arraydebug)
{
#if defined(ZTS) && defined(COMPILE_DL_ARRAYDEBUG)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION */
PHP_MINFO_FUNCTION(arraydebug)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "arraydebug support", "enabled");
	php_info_print_table_end();
}
/* }}} */

/* {{{ arraydebug_module_entry */
zend_module_entry arraydebug_module_entry = {
	STANDARD_MODULE_HEADER,
	"arraydebug",					/* Extension name */
	ext_functions,					/* zend_function_entry */
	NULL,							/* PHP_MINIT - Module initialization */
	NULL,							/* PHP_MSHUTDOWN - Module shutdown */
	PHP_RINIT(arraydebug),			/* PHP_RINIT - Request initialization */
	NULL,							/* PHP_RSHUTDOWN - Request shutdown */
	PHP_MINFO(arraydebug),			/* PHP_MINFO - Module info */
	PHP_ARRAYDEBUG_VERSION,		/* Version */
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_ARRAYDEBUG
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(arraydebug)
#endif
